#ifndef COURSESHELL_BUILTINFACTORY_H
#define COURSESHELL_BUILTINFACTORY_H

#include <string>
#include <cstddef>

#include "BuiltIn.h"

#include "CD.h"
#include "EXIT.h"

using namespace std;

class BuiltInFactory {
public:
    static BuiltIn *create(const string &str, string *args, int size);
};

#endif //COURSESHELL_BUILTINFACTORY_H
