#include "catch.hpp"
#include "board.hpp"

TEST_CASE("Board pieces", "[board]") {
    game::board_piece piece(2, 3, game::WHITE);

    REQUIRE(piece.get_x() == 2);
    REQUIRE(piece.get_y() == 3);
    REQUIRE(piece.get_color() == game::WHITE);

    piece = game::board_piece(7, 0, game::BLACK);
    REQUIRE(piece.get_x() == 7);
    REQUIRE(piece.get_y() == 0);
    REQUIRE(piece.get_color() == game::BLACK);
}

TEST_CASE("Board moves", "[board]") {
    game::move move(2, 3, 5, 7);

    REQUIRE(move.get_from_x() == 2);
    REQUIRE(move.get_from_y() == 3);
    REQUIRE(move.get_to_x() == 5);
    REQUIRE(move.get_to_y() == 7);
}

TEST_CASE("Board access", "[board]") {
    game::board board;

    for(int x = 0; x < 8; ++x) {
        for(int y = 0; y < 8; ++y) {
            INFO("x,y: " << x << ',' << y);
            REQUIRE(board[x][y].piece == game::NONE);

            board[x][y].set(game::PAWN, game::WHITE);

            REQUIRE(board[x][y].piece == game::PAWN);
            REQUIRE(board[x][y].color == game::WHITE);
        }
    }

    board[2][4].color = game::BLACK;

    for(int x = 0; x < 8; ++x) {
        for(int y = 0; y < 8; ++y) {
            if(x == 2 && y == 4) {
                REQUIRE(board[x][y].color == game::BLACK);
                continue;
            }

            REQUIRE(board[x][y].color == game::WHITE);
        }
    }
}

TEST_CASE("Structures are memory friendly", "[board]") {
    REQUIRE(sizeof(game::board_piece) == 1);
    REQUIRE(sizeof(game::move) <= 2);
}
