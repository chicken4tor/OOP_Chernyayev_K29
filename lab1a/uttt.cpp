#include "uttt.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>


using namespace std;

bool has_moves(const int (&mini_board)[BOARD_SIZE * BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        if (mini_board[i] == FREE_CELL)
        {
            return true;
        }
    }

    return false;
}

int has_winner(const int (&mini_board)[BOARD_SIZE * BOARD_SIZE])
{
    // Check rows
    int winner = FREE_CELL;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (mini_board[i * BOARD_SIZE] == PLAYER_X || mini_board[i * BOARD_SIZE] == PLAYER_O)
        {
            winner = mini_board[i * BOARD_SIZE];

            for (int j = 1; j < BOARD_SIZE; j++)
            {
                if (winner != mini_board[i * BOARD_SIZE + j])
                {
                    winner = FREE_CELL;
                    break;
                }
            }

            if (winner != FREE_CELL)
            {
                return winner;
            }
        }
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (mini_board[i] == PLAYER_X || mini_board[i] == PLAYER_O)
        {
            winner = mini_board[i];

            for (int j = 1; j < BOARD_SIZE; j++)
            {
                if (winner != mini_board[j * BOARD_SIZE + i])
                {
                    winner = FREE_CELL;
                    break;
                }
            }

            if (winner != FREE_CELL)
            {
                return winner;
            }
        }
    }

    // Check diagonals
    if (mini_board[0] != FREE_CELL)
    {
        winner = mini_board[0];
        for (int i = 1; i < BOARD_SIZE; i++)
        {
            if (mini_board[i * BOARD_SIZE + i] != winner)
            {
                winner = FREE_CELL;
                break;
            }
        }

        if (winner != FREE_CELL)
        {
            return winner;
        }
    }

    if (mini_board[BOARD_SIZE - 1] != FREE_CELL)
    {
        winner = mini_board[BOARD_SIZE - 1];
        for (int i = 1; i < BOARD_SIZE; i++)
        {
            if (mini_board[(i + 1) * BOARD_SIZE - i - 1] != winner)
            {
                winner = FREE_CELL;
                break;
            }
        }

        if (winner != FREE_CELL)
        {
            return winner;
        }
    }

    // No winner
    return FREE_CELL;
}

/// Build big board
void build_bb(const board &b, int (&big_board)[BOARD_SIZE * BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        big_board[i] = has_winner(b[i]);

        if (big_board[i] == FREE_CELL && !has_moves(b[i]))
        {
            big_board[i] = DRAW_STATE;
        }
    }
}

/// Print game board state
void print_board(const board &b)
{
    // Build sidebar
    int big_board[BOARD_SIZE * BOARD_SIZE] = {};

    build_bb(b, big_board);

    vector<string> sidebar;

    // Total lines
    sidebar.resize(BOARD_SIZE * BOARD_SIZE + (BOARD_SIZE - 1));

    for (int i = 0 ; i < BOARD_SIZE; i++)
    {
        sidebar[i].append("   ");
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            char visualize = ' ';

            switch (big_board[i * BOARD_SIZE + j])
            {
            case PLAYER_X:
                visualize = 'X';
                break;
            case PLAYER_O:
                visualize = 'O';
                break;
            case DRAW_STATE:
                visualize = '-';
                break;
            default:
                break;
            }

            sidebar[i].append(&visualize, 1);

            if (j != BOARD_SIZE - 1)
            {
                sidebar[i].append(" ");
            }
        }
    }

    int winner = has_winner(big_board);

    if (winner != FREE_CELL)
    {
        if (winner == PLAYER_X)
        {
            sidebar[BOARD_SIZE + BOARD_SIZE / 2].append("  Player X wins");
        }
        else
        {
            sidebar[BOARD_SIZE + BOARD_SIZE / 2].append("  Player O wins");
        }
    }
    else
    {
        if (!has_moves(big_board))
        {
            sidebar[BOARD_SIZE + BOARD_SIZE / 2].append("  Friendship wins");
        }
    }

    // Mini boards
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                for (int l = 0; l < BOARD_SIZE; l++)
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

            cout << sidebar[i * BOARD_SIZE + j] << endl;
        }

        if (i < BOARD_SIZE - 1)
        {
            cout << "------+-------+------";
            // cout << setfill('-') << setw(BOARD_SIZE * 2 + 1) << '+';
        }
        cout << endl;
    }
}

/// Moves on small board
void small_board_moves(const board &b, int board_index, vector<game_move> &moves)
{
    if (has_winner(b[board_index]) != FREE_CELL)
    {
        return;
    }

    div_t a = div(board_index, BOARD_SIZE);

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        if (b[board_index][i] == FREE_CELL)
        {
            div_t j = div(i, BOARD_SIZE);
            moves.push_back(make_tuple(a.quot * BOARD_SIZE + j.quot, a.rem * BOARD_SIZE + j.rem));
        }
    }
}

struct game_state
{
    board b;
    game_move last_move;
    int player;
};

const int AB_MIN = -numeric_limits<int>::max();
const int AB_MAX =  numeric_limits<int>::max();
const int AB_DEPTH = 2;

/// Get all valid moves
void available_moves(const game_state &s, vector<game_move> &moves)
{
    moves.clear();

    if (get<0>(s.last_move) == -1 && get<1>(s.last_move) == -1)
    {
        // Перший крок - можливо все
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
        {
            small_board_moves(s.b, i, moves);
        }
    }
    else
    {
        int move_index = (get<0>(s.last_move) % BOARD_SIZE) * BOARD_SIZE + get<1>(s.last_move) % BOARD_SIZE;

        if (has_winner(s.b[move_index]) == FREE_CELL && has_moves(s.b[move_index]))
        {
            small_board_moves(s.b, move_index, moves);
        }
        else
        {
            // Додаємо всі доступні дошки
            for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
            {
                small_board_moves(s.b, i, moves);
            }
        }
    }
}


///
/// Game position heuristic
///

const int BOARD_WIN = 100;
const int DRAW = 0;
const int CLOSE_TO_WIN = 75;
const int BIG_BOARD_WEIGHT = 20;

const int CELL_SCORE[] = {
    30, 20, 30,
    20, 50, 20,
    30, 20, 30,
    };

const vector<game_move> BLOCKING_OPTIONS[] = {
    { make_pair(1, 2), make_pair(3, 6), make_pair(4, 8), },
    { make_pair(0, 2), make_pair(4, 7), },
    { make_pair(0, 1), make_pair(4, 6), make_pair(5, 8), },
    { make_pair(0, 6), make_pair(5, 4), },
    { make_pair(0, 8), make_pair(2, 6), make_pair(1, 7), make_pair(3, 5), },
    { make_pair(2, 8), make_pair(3, 4), },
    { make_pair(0, 3), make_pair(7, 8), make_pair(2, 4), },
    { make_pair(6, 8), make_pair(1, 4), },
    { make_pair(6, 7), make_pair(2, 5), make_pair(0, 4), },
};

int assess_mini(const int (&mini_board)[BOARD_SIZE * BOARD_SIZE], int last_index , int player)
{
    int winner = has_winner(mini_board);

    if (winner != FREE_CELL)
    {
        if (winner == player)
        {
            return BOARD_WIN;
        }
        else
        {
            return -BOARD_WIN;
        }
    }

    if (!has_moves(mini_board))
    {
        return DRAW;
    }

    for (auto &block_move : BLOCKING_OPTIONS[last_index])
    {
        if (mini_board[get<0>(block_move)] == player)
        {
            if (mini_board[get<0>(block_move)] == mini_board[get<1>(block_move)])
            {
                return CLOSE_TO_WIN;
            }
        }
    }

    return CELL_SCORE[last_index];
}

int evaluate(const game_state &s)
{
    int position_score = 0;

    int big_board[BOARD_SIZE * BOARD_SIZE] = {};

    int move_index = (get<0>(s.last_move) % BOARD_SIZE) * BOARD_SIZE + get<1>(s.last_move) % BOARD_SIZE;
    int board_index = (get<0>(s.last_move) / BOARD_SIZE) * BOARD_SIZE + get<1>(s.last_move) / BOARD_SIZE;

    // Evaluate miniboards
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        position_score += assess_mini(s.b[i], move_index, s.player);

        big_board[i] = has_winner(s.b[i]);
    }

    // Evaluate entire position
    position_score += assess_mini(big_board, board_index, s.player) * BIG_BOARD_WEIGHT;

    return position_score;
}

int opponent(int player)
{
    if (player == PLAYER_X)
    {
        return PLAYER_O;
    }
    else
    {
        return PLAYER_X;
    }
}

/// Execute move
bool move_execute(game_state &s, const game_move &m, int player)
{
    int move_index = (get<0>(m) % BOARD_SIZE) * BOARD_SIZE + get<1>(m) % BOARD_SIZE;
    int board_index = (get<0>(m) / BOARD_SIZE) * BOARD_SIZE + get<1>(m) / BOARD_SIZE;

    if (s.b[board_index][move_index] == FREE_CELL)
    {
        s.last_move = m;

        s.b[board_index][move_index] = player;

        s.player = opponent(player);

        return true;
    }

    return false;
}

/// Undo move
void move_undo(game_state &s)
{
    int move_index = (get<0>(s.last_move) % BOARD_SIZE) * BOARD_SIZE + get<1>(s.last_move) % BOARD_SIZE;
    int board_index = (get<0>(s.last_move) / BOARD_SIZE) * BOARD_SIZE + get<1>(s.last_move) / BOARD_SIZE;

    s.b[board_index][move_index] = FREE_CELL;
    s.last_move = make_pair(-1, -1);
    s.player = opponent(s.player);
}

bool is_terminal_state(const game_state &s)
{
    int big_board[BOARD_SIZE * BOARD_SIZE] = {};

    build_bb(s.b, big_board);

    if (has_winner(big_board) != FREE_CELL)
    {
        return true;
    }

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        if (has_winner(s.b[i]) == FREE_CELL && has_moves(s.b[i]))
        {
            return false;
        }
    }

    return true;
}

int max_val(const game_state &s, int depth, int alpha, int beta);

int min_val(const game_state &s, int depth, int alpha, int beta)
{
    if (is_terminal_state(s) || depth == 0)
    {
        return evaluate(s);
    }

    int val = AB_MAX;

    vector<game_move> moves;

    available_moves(s, moves);

    game_state ss = s;

    for (auto &m : moves)
    {
        move_execute(ss, m, s.player);

        val = min(val, max_val(ss, depth - 1, alpha, beta));

        if (val <= alpha)
        {
            return val;
        }

        beta = min(beta, val);

        move_undo(ss);
    }

    return val;
}

int max_val(const game_state &s, int depth, int alpha, int beta)
{
    if (is_terminal_state(s) || depth == 0)
    {
        return evaluate(s);
    }

    int val = AB_MIN;

    vector<game_move> moves;

    available_moves(s, moves);

    game_state ss = s;

    for (auto &m : moves)
    {
        move_execute(ss, m, s.player);

        val = max(val, min_val(ss, depth, alpha, beta));

        if (val >= beta)
        {
            return val;
        }

        alpha = max(alpha, val);

        move_undo(ss);
    }

    return val;
}

static random_device rd;
static mt19937 gen(rd());

/// Minimax (AlphaBeta) implementation
game_move minimax(game_state &s, int player, int depth, int alpha, int beta)
{
    vector<game_move> moves;
    vector<scored_move> evaluated_moves;
    vector<scored_move> best_moves;

    available_moves(s, moves);

    for (auto &m : moves)
    {
        move_execute(s, m, player);

        int res = min_val(s, depth, alpha, beta);

        evaluated_moves.push_back(make_pair(res, m));

        move_undo(s);
    }

    auto it = max_element(begin(evaluated_moves), end(evaluated_moves), [] (const auto &a, const auto &b) { return get<0>(a) < get<0>(b); });

    if (it != end(evaluated_moves))
    {
        int max_val = get<0>(*it);

        auto last_max = remove_if(begin(evaluated_moves), end(evaluated_moves), [max_val] (const auto &a) { return get<0>(a) != max_val; });

        uniform_int_distribution<> random_element(0, static_cast<int>(distance(begin(evaluated_moves), last_max)) - 1);

        return get<1>(evaluated_moves.at(random_element(gen)));
    }
    else
    {
        return make_tuple(-1, -1);
    }
}

/// Self-enjoy
void play()
{
    game_state s = {};

    s.player = PLAYER_X;
    s.last_move = make_pair(-1, -1);

    while (!is_terminal_state(s))
    {
        game_move m = minimax(s, s.player, AB_DEPTH, AB_MIN, AB_MAX);

        if (get<0>(m) == -1 && get<1>(m) == -1)
        {
            cout << "Invalid move" << endl;

            return;
        }

        move_execute(s, m, s.player);

        print_board(s.b);
    }
}
