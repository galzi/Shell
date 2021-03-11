#include "BuiltInFactory.h"

    BuiltIn *BuiltInFactory::create(const string &str, string *args, int size) {
        if (str == "cd")
            return new CD(args, size);
        if (str == "exit")
            return new EXIT(args, size);
        return NULL;
    }