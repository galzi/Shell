#ifndef COURSESHELL_CD_H
#define COURSESHELL_CD_H

#include <iostream>
#include <cstddef>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "BuiltIn.h"

class CD : public BuiltIn {
public:
    CD(string *args, int size) : BuiltIn(args, size) {}
    bool Do() override;
};
#endif //COURSESHELL_CD_H
