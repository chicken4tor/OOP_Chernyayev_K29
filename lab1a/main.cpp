#include <iostream>
#include <iomanip>
#include <tuple>
#include <vector>

using namespace std;

enum { FREE_CELL, PLAYER_X, PLAYER_O, DRAW_STATE, };

const int BOARD_SIZE = 3;

typedef tuple<int, int> game_move;

typedef tuple<int, game_move> scored_move;

typedef int board[BOARD_SIZE * BOARD_SIZE][BOARD_SIZE * BOARD_SIZE];
typedef int result[BOARD_SIZE][BOARD_SIZE];

void print_board(board &b)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            for (int k = 0; k < BOARD_SIZE; ++k)
            {
                for (int l = 0; l < BOARD_SIZE; ++l)
                {
                    char visualize;

                    switch (b[BOARD_SIZE * i + k][BOARD_SIZE * j + l])
                    {
                    case PLAYER_X:
                        visualize = 'x';
                        break;
                    case PLAYER_O:
                        visualize = 'o';
                        break;
                    default:
                        visualize = '-';
                        break;
                    }

                    cout << visualize;

                    if (l < BOARD_SIZE - 1)
                    {
                        cout << " ";
                    }
                }

                if (k < BOARD_SIZE - 1)
                {
                    cout << " | ";
                }
            }
            cout << endl;
        }

        if (i < BOARD_SIZE - 1)
        {
            cout << "------+-------+------";
            // cout << setfill('-') << setw(BOARD_SIZE * 2 + 1) << '+';
        }
        cout << endl;
    }
}

void single_board_moves(const board &b, int board_x, int board_y, vector<game_move> &moves)
{
    for (int i = board_x * BOARD_SIZE; i < board_x * BOARD_SIZE + BOARD_SIZE; ++i)
    {
        for (int j = board_y * BOARD_SIZE; j < board_x * BOARD_SIZE + BOARD_SIZE; ++j)
        {
            if (b[i][j] == FREE_CELL)
            {
                moves.push_back(make_tuple(i, j));
            }
        }
    }
}

void available_moves(const board &b, const result &r, game_move last, vector<game_move> &moves)
{
    moves.clear();

    if (get<0>(last) == -1 && get<1>(last) == -1)
    {
        // Перший крок - можливо все
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                single_board_moves(b, i, j, moves);
            }
        }
    }
    else
    {
        int board_x = get<0>(last) % BOARD_SIZE;
        int board_y = get<1>(last) % BOARD_SIZE;

        if (r[board_x][board_y] == FREE_CELL)
        {
            single_board_moves(b, board_x, board_y, moves);
        }
        else
        {
            // Шукаємо доступні дошки
            for (int i = 0; i < BOARD_SIZE; ++i)
            {
                for (int j = 0; j < BOARD_SIZE; ++j)
                {
                    if (r[i][j] == FREE_CELL)
                    {
                        single_board_moves(b, i, j, moves);
                    }
                }
            }
        }
    }
}

scored_move minimax(board &b, result &r, char player, double alpha, double beta)
{
    vector<game_move> moves;

    available_moves(b, r, make_tuple(-1, -1), moves);

    if (moves.empty())
    {
    }

    return make_tuple(-1, make_tuple(-1, -1));
}

int main()
{
    board b = {};
    result r = {};

    print_board(b);
}
