#include "Prompt.h"

    Prompt::Prompt() {
        char *t = getenv("HOME");
        this->homeDir = t != NULL ? string(t) : NULL;
    }

    string Prompt::getTildeForm() {
        char *t = getcwd(NULL, 0);
        this->currDir = t;
        delete t;
        if (currDir.find(homeDir) == 0)
            return "~" + currDir.substr(homeDir.length(), currDir.length());
        else
            return currDir;
    }

    Prompt &Prompt::Instance() {
        static Prompt instance;
        return instance;
    }

    string Prompt::printPrompt() {
        return string("OS SHell: " + getTildeForm() + "> ");
    }

    const string &Prompt::getHome() const {
        return this->homeDir;
    }
