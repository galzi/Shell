#ifndef COURSESHELL_EXIT_H
#define COURSESHELL_EXIT_H

#include <iostream>

#include "BuiltIn.h"

using namespace std;

class EXIT : public BuiltIn {
public:
    EXIT(string *args, int size) : BuiltIn(args, size) {}
    bool Do() override;
};
#endif //COURSESHELL_EXIT_H
