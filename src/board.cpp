#include "board.hpp"

namespace chess {


board_column::board_column(board& board, uint8_t x) : _board(board), _x(x) {
}

piece_and_color& board_column::operator[](uint8_t y) {
    return _board._pieces[_x][y];
}


const_board_column::const_board_column(const board& board, uint8_t x) : _board(board), _x(x) {
}

const piece_and_color& const_board_column::operator[](uint8_t y) const {
    return _board._pieces[_x][y];
}


board_column board::operator[](uint8_t x) {
    return board_column(*this, x);
}

const_board_column board::operator[](uint8_t x) const {
    return const_board_column(*this, x);
}


}
