#include "board.hpp"

namespace game {

board_column::board_column(board& board, uint8_t x) : _board(board), _x(x) {
}

piece_and_color& board_column::operator[](uint8_t y) {
    return _board._pieces[_x][y];
}

board::board() {
    memset(_pieces, 0, sizeof(piece_and_color) * 8 * 8);
}

board_column board::operator[](uint8_t x) {
    return board_column(*this, x);
}

}
