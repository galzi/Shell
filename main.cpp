#define EXIT_SUCCESS 0

#include "REPL.h"

int main(int argc, char **argv) {
    REPL::Instance().loop();

    return EXIT_SUCCESS;
}
