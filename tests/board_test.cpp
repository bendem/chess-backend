#include "catch.hpp"
#include "board.hpp"

TEST_CASE("Board pieces", "[board]") {
    chess::board_piece piece(2, 3, chess::WHITE);

    REQUIRE(piece.get_x() == 2);
    REQUIRE(piece.get_y() == 3);
    REQUIRE(piece.get_color() == chess::WHITE);

    piece = chess::board_piece(7, 0, chess::BLACK);
    REQUIRE(piece.get_x() == 7);
    REQUIRE(piece.get_y() == 0);
    REQUIRE(piece.get_color() == chess::BLACK);
}

TEST_CASE("Board moves", "[board]") {
    chess::move move(2, 3, 5, 7);

    REQUIRE(move.get_from_x() == 2);
    REQUIRE(move.get_from_y() == 3);
    REQUIRE(move.get_to_x() == 5);
    REQUIRE(move.get_to_y() == 7);
}

TEST_CASE("Board get/set", "[board]") {
    chess::board board;

    for(int x = 0; x < 8; ++x) {
        for(int y = 0; y < 8; ++y) {
            INFO("x,y: " << x << ',' << y);
            REQUIRE(board[x][y].piece == chess::NONE);

            board[x][y].set(chess::PAWN, chess::WHITE);

            REQUIRE(board[x][y].piece == chess::PAWN);
            REQUIRE(board[x][y].color == chess::WHITE);
        }
    }

    board[2][4].color = chess::BLACK;

    for(int x = 0; x < 8; ++x) {
        for(int y = 0; y < 8; ++y) {
            if(x == 2 && y == 4) {
                REQUIRE(board[x][y].color == chess::BLACK);
                continue;
            }

            REQUIRE(board[x][y].color == chess::WHITE);
        }
    }
}

TEST_CASE("Structures are memory friendly", "[board]") {
    REQUIRE(sizeof(chess::board_piece) == 1);
    REQUIRE(sizeof(chess::move) <= 2);
}
