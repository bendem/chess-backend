#ifndef CHESS_BACKEND_BOARD_HPP
#define CHESS_BACKEND_BOARD_HPP

#include <cassert>
#include <cstdint>
#include <cstring>

namespace chess {


enum class piece: uint8_t {
    NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};


enum class color: bool {
    WHITE = false, BLACK = true
};


struct board_piece {
    board_piece(uint8_t x, uint8_t y, enum color color)
        : _x(x), _y(y), _color(static_cast<uint8_t>(color)) {
        assert(x < 8);
        assert(y < 8);
    }

    uint8_t x() const {
        return _x;
    }

    uint8_t y() const {
        return _y;
    }

    enum color color() const {
        return static_cast<enum color>(_color);
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

    uint8_t from_x() const {
        return _from_x;
    }

    uint8_t from_y() const {
        return _from_y;
    }

    uint8_t to_x() const {
        return _to_x;
    }

    uint8_t to_y() const {
        return _to_y;
    }

private:
    uint8_t _from_x: 3;
    uint8_t _from_y: 3;
    uint8_t _to_x: 3;
    uint8_t _to_y: 3;
};


struct piece_and_color {
    piece_and_color() : piece_and_color(piece::NONE, color::WHITE) {}
    piece_and_color(enum piece piece, enum color color)
        : _piece(static_cast<uint8_t>(piece)), _color(static_cast<uint8_t>(color)) {}

    enum piece piece() const {
        return static_cast<enum piece>(_piece);
    }

    enum color color() const {
        return static_cast<enum color>(_color);
    }

    piece_and_color& piece(enum piece piece) {
        this->_piece = static_cast<uint8_t>(piece);
        return *this;
    }

    piece_and_color& color(enum color color) {
        this->_color = static_cast<uint8_t>(color);
        return *this;
    }

    piece_and_color& set(enum piece _piece, enum color _color) {
        this->_piece = static_cast<uint8_t>(_piece);
        this->_color = static_cast<uint8_t>(_color);
        return *this;
    }

private:
    uint8_t _piece: 4;
    uint8_t _color: 1;
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
    board_column operator[](uint8_t x);

private:
    friend struct board_column;

    piece_and_color _pieces[8][8];
};


}

#endif
