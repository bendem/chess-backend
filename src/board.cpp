#include "board.hpp"

namespace chess {


board_column::board_column(board& board, uint8_t x) : _board(board), _x(x) {
}

piece_and_color& board_column::operator[](uint8_t y) {
    return _board._pieces[_x][y];
}


board_column board::operator[](uint8_t x) {
    return board_column(*this, x);
}


}
