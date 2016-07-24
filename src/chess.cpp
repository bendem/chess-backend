#include "chess.hpp"

namespace chess {

board starting_board() {
    board b;

    b[0][0].set(piece::ROOK, color::BLACK);
    b[0][7].set(piece::ROOK, color::BLACK);
    b[7][0].set(piece::ROOK, color::WHITE);
    b[7][7].set(piece::ROOK, color::WHITE);

    b[0][1].set(piece::KNIGHT, color::BLACK);
    b[0][6].set(piece::KNIGHT, color::BLACK);
    b[7][1].set(piece::KNIGHT, color::WHITE);
    b[7][6].set(piece::KNIGHT, color::WHITE);

    b[0][2].set(piece::BISHOP, color::BLACK);
    b[0][5].set(piece::BISHOP, color::BLACK);
    b[7][2].set(piece::BISHOP, color::WHITE);
    b[7][5].set(piece::BISHOP, color::WHITE);

    b[0][3].set(piece::QUEEN, color::BLACK);
    b[7][3].set(piece::QUEEN, color::WHITE);

    b[0][4].set(piece::KING, color::BLACK);
    b[7][4].set(piece::KING, color::WHITE);

    for(int i = 0; i < 8; ++i) {
        b[1][i].set(piece::PAWN, color::BLACK);
        b[6][i].set(piece::PAWN, color::WHITE);
    }

    return b;
}

void dump_board(const board& b) {
    const std::string fg_black = "\x1b[38;5;246m";
    const std::string fg_white = "\x1b[38;5;255m";
    const std::string bg_black = "\x1b[48;5;233m";
    const std::string bg_white = "\x1b[48;5;241m";
    const std::string reset = "\x1b[0m";

    color current = color::WHITE;

    for(int i = 0; i < 8; ++i) {
        std::cout << ' ';
        for(int j = 0; j < 8; ++j) {
            const piece_and_color& square = b[i][j];

            std::cout << (current == color::WHITE ? bg_white : bg_black);
            std::cout << (square.color() == color::WHITE ? fg_white : fg_black);

            std::cout << ' ';
            switch(square.piece()) {
                case piece::NONE: std::cout << ' '; break;
                case piece::PAWN: std::cout << 'P'; break;
                case piece::ROOK: std::cout << 'R'; break;
                case piece::KNIGHT: std::cout << 'k'; break;
                case piece::BISHOP: std::cout << 'B'; break;
                case piece::QUEEN: std::cout << 'Q'; break;
                case piece::KING: std::cout << 'K'; break;
            }
            std::cout << ' ';
            std::cout << reset;
            current = current == color::WHITE ? color::BLACK : color::WHITE;
        }
        current = current == color::WHITE ? color::BLACK : color::WHITE;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

}
