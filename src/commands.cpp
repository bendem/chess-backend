#include "commands.hpp"

namespace chess {

void command_handler::handle(const command& command, board& board) {
    switch(command.command_type) {
        case command_type::RESET:
            board = chess::board();
            break;
        case command_type::UNSERIALIZE:
            break;
        case command_type::SERIALIZE:
            break;
        case command_type::GENERATE:
            break;
        case command_type::MOVE:
            break;
        case command_type::CHECK:
            break;
        case command_type::INVALID:
        case command_type::EXIT:
            assert(false);
    }
}

}
