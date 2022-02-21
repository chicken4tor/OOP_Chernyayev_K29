#ifndef UTTT_H_SEEN
#define UTTT_H_SEEN

#include <tuple>

/// \file

/// Cell or board states
enum { FREE_CELL, PLAYER_X, PLAYER_O, DRAW_STATE, };

/// Board size
const int BOARD_SIZE = 3;

/// Position on game board
typedef std::tuple<int, int> game_move;

/// Position with score
typedef std::tuple<int, game_move> scored_move;

/// Full game board
typedef int board[BOARD_SIZE * BOARD_SIZE][BOARD_SIZE * BOARD_SIZE];

/// Print game board state
void print_board(const board &b);

/// Check win condition
int has_winner(const int (&mini_board)[BOARD_SIZE * BOARD_SIZE]);

/// Self-enjoy
void play();

#endif  // UTTT_H_SEEN
