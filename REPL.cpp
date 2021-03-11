#define TOK_DELIM {' ', '\t', '\r', '\n', '\a'}
#define TOK_DELIM_SIZE 5

#include "REPL.h"

    void REPL::loop() {
        int size, status;
        string line, *args;

        cout << "Welcome to OS SHell!" << endl;

        do {
            for (auto it = Launcher::PID.begin(); it != Launcher::PID.end();) {
                if (waitpid(*it, &status, WNOHANG) != 0) {
                    cout << "[" << *it << "] : exited, status=" << WEXITSTATUS(status) << endl;
                    it = Launcher::PID.erase(it);
                } else {
                    ++it;
                }
            }

            cout << Prompt::Instance().printPrompt();
            line = this->read_line();
            args = this->tokenize(line, &size);
            this->status = Launcher(args, size).execute();

            if (size != 1)
                delete[] args;
            else
                delete args;
        } while (this->status && this->eof);
        cout << "C ya!" << endl;
    }

    REPL &REPL::Instance() {
        static REPL instance;
        return instance;
    }

    REPL::REPL() {
        this->status = true;
        this->eof = true;
        this->delimiter = new char[TOK_DELIM_SIZE] TOK_DELIM;
    }

    REPL::~REPL() {
        delete[] this->delimiter;
    }

    string REPL::read_line(void) {
        string str;

        getline(cin, str);
        if (!cin)
            if (cin.eof())
                this->eof = false;

        return str;
    }

    string *REPL::tokenize(string line, int *s) {
        bool f;
        int i, c = 0;
        string::iterator it;

        for (it = line.begin(); it < line.end(); it++) {
            f = false;
            for (i = 0; !f && i < TOK_DELIM_SIZE; f = delimiter[i] == *it, i++);
            c += f ? 1 : 0;
        }

        *s = c + 1;
        if (!c) {
            return new string(line);
        }

        size_t pos, prevPos;
        string *arr;

        for (i = 0, prevPos = 0, arr = new string[c + 1]; i <= c; i++, prevPos = pos + 1) {
            pos = minPos(line, prevPos);
            if (pos == string::npos) pos = line.length();
            arr[i] = line.substr(prevPos, pos - prevPos);
        }

        return arr;
    }

    size_t REPL::minPos(string s, int init) {
        size_t pos = string::npos, tmp;
        int i;

        for (i = 0; i < TOK_DELIM_SIZE; i++) {
            tmp = s.find(this->delimiter[i], init);
            if ((tmp != string::npos && pos != string::npos && tmp < pos) || (pos == string::npos && tmp != string::npos))
                pos = tmp;
        }
        return pos;
    }
