#include "Launcher.h"

    int Launcher::exitCode = 0;
    list<int> Launcher::PID = {};

    Launcher::Launcher(string *args, int size) {
        this->args = args;
        this->size = size;
        this->bg = false;
    }

    int Launcher::execute() {
        if (this->args[0] == "") {
            // An empty command was entered.
            return 1;
        }

        this->preprocess();

        BuiltIn *b = BuiltInFactory::create(this->args[0], this->args, this->size);

        if (b != NULL) {
            bool result = (*b).Do();
            delete b;
            return result;
        }

        return this->launch();
    }

    bool Launcher::launch() {
        pid_t pid;
        int status, i;
        char **args;

        pid = fork();
        if (pid == 0) {
            // Child process

            args = new char*[this->size + 1];

            for (i = 0; i < this->size; i++) {
                args[i] = new char[this->args[i].length()];
                strcpy(args[i], this->args[i].c_str());
            }

            args[this->size] = NULL;

            if (execvp(this->args[0].c_str(), args) == -1) {
                cerr << "Error: " << strerror(errno) << endl; // perror("shell");
                Launcher::exitCode = 127;
            }

            for (i = 0; i < this->size; i++) {
                delete args[i];
            }

            delete[] args;

            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Error forking
            cerr << "Error: " << strerror(errno) << endl; // perror("shell");
        } else {
            // Parent process
            do {
                if (!this->bg) {
                    waitpid(pid, &status, WUNTRACED);
                    if (WIFEXITED(status)) {
                        Launcher::exitCode = WEXITSTATUS(status);
                    } else if (WIFSIGNALED(status)) {
                        Launcher::exitCode = WTERMSIG(status) + 128;
                    }
                } else {
                    Launcher::exitCode = 0;
                    cout << "[" << pid << "]" << endl;
                    this->PID.push_front(pid);
                }
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }

        return true;
    }

    void Launcher::preprocess() {
        int i, newPos;
        unsigned int j, size, *positions, tildeSym, exitSym, regexSym;
        size_t pos;
        string exit = to_string(Launcher::exitCode), *str;
        char *tmp;
        list<string> l = {};

        for (i = 0; i < this->size; i++) {
            regex words_regex("\\$[a-zA-Z_][a-zA-Z0-9_]*");

            auto words_begin = sregex_iterator(this->args[i].begin(), this->args[i].end(), words_regex);
            auto words_end = sregex_iterator();

            j = 0;
            size = distance(words_begin, words_end);

            positions = new unsigned int[size];
            str = new string[size];

            for (sregex_iterator it = words_begin; it != words_end; ++it) {
                positions[j] = it->position();
                str[j] = it->str();
                j++;
            }

            for (j = 0, pos = 0; pos < this->args[i].length();) {
                tildeSym = this->args[i].find("~", pos) != string::npos ? this->args[i].find("~", pos) : this->args[i].length();
                exitSym = this->args[i].find("$?", pos) != string::npos ? this->args[i].find("$?", pos) : this->args[i].length();
                regexSym = j < size ? positions[j] : this->args[i].length();

                if ((tildeSym < exitSym) && (tildeSym < regexSym)) {
                    l.push_back(this->args[i].substr(pos, tildeSym - pos));
                    pos = tildeSym + 1;
                    l.push_back(Prompt::Instance().getHome());
                } else if (exitSym < regexSym) {
                    l.push_back(this->args[i].substr(pos, exitSym - pos));
                    pos = exitSym + 2;
                    l.push_back(exit);
                } else if (pos == positions[j]) {
                    tmp = getenv(str[j].substr(1, str[j].length()).c_str());
                    if (tmp != NULL)
                        l.push_back(tmp);
                    pos += str[j].length();
                    j++;
                } else {
                    tildeSym = this->args[i].find("~", pos) != string::npos ? this->args[i].find("~", pos) : this->args[i].length();
                    exitSym = this->args[i].find("$?", pos) != string::npos ? this->args[i].find("$?", pos) : this->args[i].length();
                    regexSym = j < size ? positions[j] : this->args[i].length();

                    newPos = tildeSym < exitSym && tildeSym < regexSym ? tildeSym : (tildeSym > exitSym && tildeSym < regexSym ? exitSym : regexSym);
                    l.push_back(this->args[i].substr(pos, newPos));
                    pos = newPos;
                }
            }
            delete[] positions;
            delete[] str;

            string cmd = "";
            for (auto &k : l) {
                cmd += k;
            }
            this->args[i] = cmd;
            l.clear();
        }

        if (this->args[this->size - 1] == "&") {
            this->bg = true;
            this->size--;
        }
    }
