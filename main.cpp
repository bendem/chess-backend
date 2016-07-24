#include <iostream>

#include "board.hpp"
#include "chess.hpp"
#include "commands.hpp"
#include "protocol.hpp"

int main() {
    chess::board board = chess::starting_board();
    chess::protocol proto(std::cin, std::cout);
    chess::command_handler command_handler;

    chess::dump_board(board);

    while(true) {
        auto command = proto.next_command();
        if(command.command_type == chess::command_type::INVALID) {
            continue;
        }
        if(command.command_type == chess::command_type::EXIT) {
            break;
        }


        command_handler.handle(command, board);
        chess::dump_board(board);
    }

    return 0;
}
