#ifndef COURSESHELL_PROMPT_H
#define COURSESHELL_PROMPT_H

#include <string>
#include <unistd.h>

using namespace std;

class Prompt {
private:
    string homeDir;
    string currDir;

    string getTildeForm();

    Prompt();
    Prompt(const Prompt &old); // disallow copy constructor
    const Prompt &operator=(const Prompt &old); // disallow assignment operator
    ~Prompt() {}
public:
    static Prompt &Instance();
    string printPrompt();
    const string &getHome() const;
};

#endif //COURSESHELL_PROMPT_H
