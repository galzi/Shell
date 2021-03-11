#ifndef COURSESHELL_REPL_H
#define COURSESHELL_REPL_H

#include <iostream>
#include <string>

#include "Launcher.h"
#include "Prompt.h"

using namespace std;

class REPL {

public:
    void loop(void);
    static REPL &Instance();
private:
    bool status;
    bool eof;
    char *delimiter;

    string read_line(void);
    string *tokenize(string line, int *s);
    size_t minPos(string s, int init);

    REPL();
    REPL(const REPL &old); // disallow copy constructor
    const REPL &operator=(const REPL &old); // disallow assignment operator
    ~REPL();
};

#endif //COURSESHELL_REPL_H
