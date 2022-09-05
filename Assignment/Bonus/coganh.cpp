#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

struct Position
{
    int x;
    int y;
    Position() { x = y = 0; }
    Position(int a, int b)
    {
        x = a;
        y = b;
    }
};

struct Move {
    Position pos_start, pos_end;
    Move(Position s, Position e) {
        pos_start = s;
        pos_end = e;
    }
};

int** copy_board(int** board)
{
    int** n_b = new int* [5];
    for (int i = 0; i < 5; i++)
    {
        n_b[i] = new int[5];
        for (int j = 0; j < 5; j++)
        {
            n_b[i][j] = board[i][j];
        }
    }
    return n_b;
}

bool isNotMove(int** board, Move mov, int player) {
    bool cond1 = (mov.pos_start.x == mov.pos_end.x && mov.pos_start.y == mov.pos_end.y);
    bool cond2 = (board[mov.pos_end.x][mov.pos_end.y] == 1 || board[mov.pos_end.x][mov.pos_end.y] == -1);
    bool cond3 = (mov.pos_end.x > mov.pos_start.x + 1 || mov.pos_end.y > mov.pos_start.y + 1);
    bool cond4 = (mov.pos_start.x < 0 || mov.pos_start.x > 4 || mov.pos_start.y < 0 || mov.pos_start.y > 4 || mov.pos_end.x < 0 || mov.pos_end.x > 4 || mov.pos_end.y < 0 || mov.pos_end.y > 4);
    return (cond1 || cond2 || cond3 || cond4);
}

vector<Position> ganh(int** board, Move m, int player) {
    vector<Position> res_vec;
    if (isNotMove(board, m, player)) return res_vec;
    int x = m.pos_end.x, y = m.pos_end.y;
    if (x > 0 && x < 4 && board[x + 1][y] == -player && board[x - 1][y] == -player) {
        res_vec.push_back(Position(x + 1, y));
        res_vec.push_back(Position(x - 1, y));
    }
    if (y > 0 && y < 4 && board[x][y + 1] == -player && board[x][y - 1] == -player) {
        res_vec.push_back(Position(x, y + 1));
        res_vec.push_back(Position(x, y - 1));
    }
    if ((x == 1 && y == 1) || (x == 1 && y == 3) || (x == 2 && y == 2) || (x == 3 && y == 1) || (x == 3 && y == 3)) {
        if (board[x - 1][y - 1] == -player && board[x + 1][y + 1] == -player) {
            res_vec.push_back(Position(x - 1, y - 1));
            res_vec.push_back(Position(x + 1, y + 1));
        }
        if (board[x + 1][y - 1] == -player && board[x - 1][y + 1] == -player) {
            res_vec.push_back(Position(x + 1, y - 1));
            res_vec.push_back(Position(x - 1, y + 1));
        }
    }
    return res_vec;
};


bool isEmptyPosition(int** board, Position p) {
    if (board[p.x][p.y] != 1 && board[p.x][p.y] != -1)
        return 1;
    return 0;
}

vector<Position> canMoveTo(int** board, Position p, int player) {
    vector<Position> res_vec;
    int x = p.x, y = p.y;
    if (board[x][y] == player) {
        if (x > 0 && isEmptyPosition(board, Position(x - 1, y))) res_vec.push_back(Position(x - 1, y));
        if (x < 4 && isEmptyPosition(board, Position(x + 1, y))) res_vec.push_back(Position(x + 1, y));
        if (y > 0 && isEmptyPosition(board, Position(x, y - 1))) res_vec.push_back(Position(x, y - 1));
        if (y < 4 && isEmptyPosition(board, Position(x, y + 1))) res_vec.push_back(Position(x, y + 1));
        if ((x + y) % 2 == 0) {
            if (x > 0 && y > 0 && isEmptyPosition(board, Position(x - 1, y - 1))) res_vec.push_back(Position(x - 1, y - 1));
            if (x < 4 && y > 0 && isEmptyPosition(board, Position(x + 1, y - 1))) res_vec.push_back(Position(x + 1, y - 1));
            if (x < 4 && y < 4 && isEmptyPosition(board, Position(x + 1, y + 1))) res_vec.push_back(Position(x + 1, y + 1));
            if (x > 0 && y < 4 && isEmptyPosition(board, Position(x - 1, y + 1))) res_vec.push_back(Position(x - 1, y + 1));
        }
    }
    return res_vec;
}

vector<Position> vay(int** board, Move m, int player) {
    vector<Position> res_vec;
    if (isNotMove(board, m, player)) return res_vec;
    int** bc = copy_board(board);
    bc[m.pos_start.x][m.pos_start.y] = 0;
    bc[m.pos_end.x][m.pos_end.y] = player;

    removeFree:
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (bc[i][j] == -player && canMoveTo(bc, Position(i, j), -player).size()) {
                bc[i][j] = 0;
                goto removeFree;
            }
        }
    }

    for (int m = 0; m < 5; m++) {
        for (int n = 0; n < 5; n++) {
            if (bc  [m][n] == -player) res_vec.push_back(Position(m, n));
        }
    }

    delete[] bc;
    return res_vec;
};