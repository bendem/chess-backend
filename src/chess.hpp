#ifndef CHESS_BACKEND_CHESS_HPP
#define CHESS_BACKEND_CHESS_HPP

#include <iostream>

#include "board.hpp"

namespace chess {

board starting_board();

void dump_board(const board&);


}

#endif
