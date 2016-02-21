#include <iostream>

#include <unistd.h>

#include "board.hpp"

int main() {
    chess::board_piece piece(1, 3, chess::WHITE);

    if(!isatty(STDIN_FILENO)) {
        std::cout << "not a ";
    }
    std::cout << "tty" << std::endl;

    return 0;
}
