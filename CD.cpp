#include "CD.h"

    bool CD::Do() {
        if (this->size == 2) {
            if (this->args[1] == "") {
                cerr << "shell: expected argument to \"cd\"\n";
                updateExitCode(1);
            } else {
                if (chdir(args[1].c_str()) != 0) {
                    cerr << "OS SHell: cd: " << strerror(errno) << endl; // perror("shell");
                    updateExitCode(1);
                }
            }
        } else {
            cerr << "shell: expected argument to \"cd\"\n";
            updateExitCode(1);
        }

        return true;
    }
