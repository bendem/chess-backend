#include "catch.hpp"
#include "board.hpp"

TEST_CASE("Board pieces", "[board]") {
    chess::board_piece piece(2, 3, chess::color::WHITE);

    REQUIRE(piece.x() == 2);
    REQUIRE(piece.y() == 3);
    REQUIRE(piece.color() == chess::color::WHITE);

    piece = chess::board_piece(7, 0, chess::color::BLACK);
    REQUIRE(piece.x() == 7);
    REQUIRE(piece.y() == 0);
    REQUIRE(piece.color() == chess::color::BLACK);
}

TEST_CASE("Board moves", "[board]") {
    chess::move move(2, 3, 5, 7);

    REQUIRE(move.from_x() == 2);
    REQUIRE(move.from_y() == 3);
    REQUIRE(move.to_x() == 5);
    REQUIRE(move.to_y() == 7);
}

TEST_CASE("Board get/set", "[board]") {
    chess::board board;

    for(int x = 0; x < 8; ++x) {
        for(int y = 0; y < 8; ++y) {
            INFO("x,y: " << x << ',' << y);
            REQUIRE(board[x][y].piece() == chess::piece::NONE);

            board[x][y].set(chess::piece::PAWN, chess::color::WHITE);

            REQUIRE(board[x][y].piece() == chess::piece::PAWN);
            REQUIRE(board[x][y].color() == chess::color::WHITE);
        }
    }

    board[2][4].color(chess::color::BLACK);

    for(int x = 0; x < 8; ++x) {
        for(int y = 0; y < 8; ++y) {
            if(x == 2 && y == 4) {
                REQUIRE(board[x][y].color() == chess::color::BLACK);
                continue;
            }

            REQUIRE(board[x][y].color() == chess::color::WHITE);
        }
    }
}

TEST_CASE("Structures are memory friendly", "[board]") {
    REQUIRE(sizeof(chess::board_piece) == 1);
    REQUIRE(sizeof(chess::move) <= 2);
    REQUIRE(sizeof(chess::board) <= 64);
}
