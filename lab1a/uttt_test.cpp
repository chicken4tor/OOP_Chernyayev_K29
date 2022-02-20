#include "uttt.h"

using namespace std;

#include <gtest/gtest.h>

TEST(MiniBoard, HasWinner) {

    int result;

    // Winner at row
    int pos1[BOARD_SIZE * BOARD_SIZE] = {
        PLAYER_X, PLAYER_X, PLAYER_X,
        FREE_CELL, FREE_CELL, FREE_CELL,
        FREE_CELL, FREE_CELL, FREE_CELL,
    };

    result = has_winner(pos1);

    EXPECT_EQ(result, PLAYER_X);

    // Winner at column
    int pos2[BOARD_SIZE * BOARD_SIZE] = {
        FREE_CELL, PLAYER_O, FREE_CELL,
        FREE_CELL, PLAYER_O, FREE_CELL,
        FREE_CELL, PLAYER_O, FREE_CELL,
    };

    result = has_winner(pos2);

    EXPECT_EQ(result, PLAYER_O);

    // Diagonal winner
    int pos3[BOARD_SIZE * BOARD_SIZE] = {
        PLAYER_X, FREE_CELL, FREE_CELL,
        FREE_CELL, PLAYER_X, FREE_CELL,
        FREE_CELL, FREE_CELL, PLAYER_X,
    };

    result = has_winner(pos3);

    EXPECT_EQ(result, PLAYER_X);

    int pos4[BOARD_SIZE * BOARD_SIZE] = {
        FREE_CELL, FREE_CELL, PLAYER_X,
        FREE_CELL, PLAYER_X, FREE_CELL,
        PLAYER_X, FREE_CELL, FREE_CELL,
    };

    result = has_winner(pos4);

    EXPECT_EQ(result, PLAYER_X);

    // No winner
}
