#include <iostream>

#include "board.hpp"
#include "chess.hpp"
#include "commands.hpp"
#include "protocol.hpp"

using namespace std::string_literals;

int main(int argc, char** argv) {
    bool debug = argc > 1 && argv[1] == "-v"s;
    if(debug) {
        std::cout << "debug active" << std::endl;
    }

    chess::board board = chess::starting_board();
    chess::protocol proto(std::cin, std::cout, debug);

    do {
        if(debug) {
            chess::dump_board(board);
        }
    } while(proto.handle_next_command(board));

    if(debug) {
        chess::dump_board(board);
    }

    return 0;
}
