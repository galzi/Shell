#ifndef COURSESHELL_BUILTIN_H
#define COURSESHELL_BUILTIN_H

#include <string>

class Launcher;

using namespace std;

class BuiltIn {
public:
    BuiltIn(string *args, int size);
    virtual ~BuiltIn();
    virtual bool Do() = 0;
protected:
    void updateExitCode(int exitCode);
    void convertArgs();

    string *args;
    char **c_args;
    int size;
};
#endif //COURSESHELL_BUILTIN_H
