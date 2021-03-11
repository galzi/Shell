#ifndef COURSESHELL_LAUNCHER_H
#define COURSESHELL_LAUNCHER_H

#include <cstddef>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <regex>
#include <cmath>
#include <list>

#include "BuiltIn.h"
#include "BuiltInFactory.h"
#include "Prompt.h"

using namespace std;

class Launcher {
private:
    string *args;
    int size;
    static int exitCode;
    bool bg;
    static list<int> PID;

    bool launch();
    void preprocess();
public:
    Launcher(string *args, int size);
    int execute();

    friend class BuiltIn;
    friend class REPL;
};
#endif //COURSESHELL_LAUNCHER_H
