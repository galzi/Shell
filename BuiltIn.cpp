#include "BuiltIn.h"

#include "Launcher.h"

BuiltIn::BuiltIn(string *args, int size) {
    this->args = args;
    this->c_args = NULL;
    this->size = size;
}

void BuiltIn::updateExitCode(int exitCode) {
    Launcher::exitCode = exitCode;
}

void BuiltIn::convertArgs() {
    if (this->c_args != NULL)
        return;

    char **args;
    args = new char*[this->size + 1];

    for (int i = 0; i < this->size; i++) {
        args[i] = new char[this->args[i].length()];
        strcpy(args[i], this->args[i].c_str());
    }

    args[this->size] = NULL;

    this->c_args = args;
}

BuiltIn::~BuiltIn() {
    if (this->c_args != NULL)
        delete this->c_args;
}