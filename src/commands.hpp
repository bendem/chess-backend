#ifndef CHESS_BACKEND_COMMANDS_HPP
#define CHESS_BACKEND_COMMANDS_HPP

#include "board.hpp"
#include "protocol.hpp"

namespace chess {


class command_handler {
public:
    void handle(const command& command, board& board);
};


}

#endif
