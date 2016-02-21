#ifndef CHESS_BACKEND_BOARD_HPP
#define CHESS_BACKEND_BOARD_HPP

#include <cassert>
#include <cstdint>
#include <cstring>

namespace chess {

enum piece: uint8_t {
    NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum color: bool {
    WHITE = false, BLACK = true
};

struct board_piece {
    board_piece(uint8_t x, uint8_t y, color color)
        : _x(x), _y(y), _color(color) {
        assert(x < 8);
        assert(y < 8);
    }

    uint8_t get_x() const {
        return _x;
    }

    uint8_t get_y() const {
        return _y;
    }

    color get_color() const {
        return static_cast<color>(_color);
    }

private:
    uint8_t _x: 3;
    uint8_t _y: 3;
    uint8_t _color: 1;
};

struct move {
    move(uint8_t from_x, uint8_t from_y, uint8_t to_x, uint8_t to_y)
        : _from_x(from_x), _from_y(from_y), _to_x(to_x), _to_y(to_y) {
        assert(from_x < 8);
        assert(from_y < 8);
        assert(to_x < 8);
        assert(to_y < 8);
    }

    uint8_t get_from_x() const {
        return _from_x;
    }

    uint8_t get_from_y() const {
        return _from_y;
    }

    uint8_t get_to_x() const {
        return _to_x;
    }

    uint8_t get_to_y() const {
        return _to_y;
    }

private:
    uint8_t _from_x: 3;
    uint8_t _from_y: 3;
    uint8_t _to_x: 3;
    uint8_t _to_y: 3;
};

struct piece_and_color {
    enum piece piece;
    enum color color;

    piece_and_color& set(enum piece _piece, enum color _color) {
        piece = _piece;
        color = _color;
        return *this;
    }
};

struct board;

struct board_column {
    board_column(board& board, uint8_t x);

    piece_and_color& operator[](uint8_t y);

private:
    board& _board;
    uint8_t _x;
};

struct board {
    board();

    board_column operator[](uint8_t x);

private:
    friend struct board_column;

    piece_and_color _pieces[8][8];
};

}

#endif
