#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

int** init_board()
{
    int** t = new int* [5];
    for (int i = 0; i < 5; i++)
    {
        t[i] = new int[5];
        if (i == 0)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = 1;
        }
        if (i == 4)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = -1;
        }
    }
    t[1][0] = 1; t[1][4] = 1; t[2][0] = 1;
    t[2][4] = -1; t[3][0] = -1; t[3][4] = -1;
    return t;
}

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

void print_board(int** board)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[4 - i][j] == 1)
                cout << "X ";
            else if (board[4 - i][j] == -1)
                cout << "O ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

struct Position
{
    int x; int y;
    Position() { x = y = 0; }
    Position(int a, int b)
    {
        x = a; y = b;
    }
};

struct Move
{
    Position pos_start, pos_end;
    Move(Position s, Position e)
    {
        pos_start = s; pos_end = e;
    }
};

vector<Position> neighbor(int** board, Position p, int player) {
    vector<Position> kq;
    int x = p.x, y = p.y;
    if (x > 0 && board[x - 1][y] == player) kq.push_back(Position(x - 1, y));
    if (x < 4 && board[x + 1][y] == player) kq.push_back(Position(x + 1, y));
    if (y > 0 && board[x][y - 1] == player) kq.push_back(Position(x, y - 1));
    if (y < 4 && board[x][y + 1] == player) kq.push_back(Position(x, y + 1));
    if ((x + y) % 2 == 0) {
        if (x > 0 && y > 0 && board[x - 1][y - 1] == player) kq.push_back(Position(x - 1, y - 1));
        if (x < 4 && y > 0 && board[x + 1][y - 1] == player) kq.push_back(Position(x + 1, y - 1));
        if (x < 4 && y < 4 && board[x + 1][y + 1] == player) kq.push_back(Position(x + 1, y + 1));
        if (x > 0 && y < 4 && board[x - 1][y + 1] == player) kq.push_back(Position(x - 1, y + 1));
    }
    return kq;
}

bool isErrorMove(int** board, Move m, int player) {
    bool dk1 = (m.pos_start.x == m.pos_end.x && m.pos_start.y == m.pos_end.y);
    bool dk2 = (board[m.pos_end.x][m.pos_end.y] == 1 || board[m.pos_end.x][m.pos_end.y] == -1);
    bool dk4 = (m.pos_end.x > m.pos_start.x + 1 || m.pos_end.y > m.pos_start.y + 1);
    bool dk3 = (m.pos_start.x < 0 || m.pos_start.x > 4 || m.pos_start.y < 0 || m.pos_start.y > 4 || m.pos_end.x < 0 || m.pos_end.x > 4 || m.pos_end.y < 0 || m.pos_end.y > 4);
    return (dk1 || dk2 || dk3 || dk4);
}

vector<Position> ganh(int** board, Move m, int player) {
    vector<Position> kq;
    if (isErrorMove(board, m, player)) return kq;
    int x = m.pos_end.x, y = m.pos_end.y;
    if (x > 0 && x < 4 && board[x + 1][y] == -player && board[x - 1][y] == -player) {
        kq.push_back(Position(x + 1, y));
        kq.push_back(Position(x - 1, y));
    }
    if (y > 0 && y < 4 && board[x][y + 1] == -player && board[x][y - 1] == -player) {
        kq.push_back(Position(x, y + 1));
        kq.push_back(Position(x, y - 1));
    }
    if ((x == 1 && y == 1) || (x == 1 && y == 3) || (x == 2 && y == 2) || (x == 3 && y == 1) || (x == 3 && y == 3)) {
        if (board[x - 1][y - 1] == -player && board[x + 1][y + 1] == -player) {
            kq.push_back(Position(x - 1, y - 1));
            kq.push_back(Position(x + 1, y + 1));
        }
        if (board[x + 1][y - 1] == -player && board[x - 1][y + 1] == -player) {
            kq.push_back(Position(x + 1, y - 1));
            kq.push_back(Position(x - 1, y + 1));
        }
    }
    return kq;
};

bool isEmptyPosition(int** board, Position p) {
    if (board[p.x][p.y] != 1 && board[p.x][p.y] != -1)
        return 1;
    return 0;
}

vector<Position> canMoveTo(int** board, Position p, int player) {
    vector<Position> kq;
    int x = p.x, y = p.y;
    if (board[x][y] == player) {
        if (x > 0 && isEmptyPosition(board, Position(x - 1, y))) kq.push_back(Position(x - 1, y));
        if (x < 4 && isEmptyPosition(board, Position(x + 1, y))) kq.push_back(Position(x + 1, y));
        if (y > 0 && isEmptyPosition(board, Position(x, y - 1))) kq.push_back(Position(x, y - 1));
        if (y < 4 && isEmptyPosition(board, Position(x, y + 1))) kq.push_back(Position(x, y + 1));
        if ((x + y) % 2 == 0) {
            if (x > 0 && y > 0 && isEmptyPosition(board, Position(x - 1, y - 1))) kq.push_back(Position(x - 1, y - 1));
            if (x < 4 && y > 0 && isEmptyPosition(board, Position(x + 1, y - 1))) kq.push_back(Position(x + 1, y - 1));
            if (x < 4 && y < 4 && isEmptyPosition(board, Position(x + 1, y + 1))) kq.push_back(Position(x + 1, y + 1));
            if (x > 0 && y < 4 && isEmptyPosition(board, Position(x - 1, y + 1))) kq.push_back(Position(x - 1, y + 1));
        }
    }
    return kq;
}

vector<Position> vay(int** board, Move m, int player) {
    vector<Position> kq;
    if (isErrorMove(board, m, player)) return kq;
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
            if (bc  [m][n] == -player) kq.push_back(Position(m, n));
        }
    }

    delete[] bc;
    return kq;
};

vector<Move> bay_or_mo(int** current_board, int** previous_board, int player) {
    vector<Move> kq;
    int preCountPlayer = 0, preCountOpp = 0, curCountPlayer = 0, curCountOpp = 0;
    Position target;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (previous_board[i][j] == player) preCountPlayer++;
            if (previous_board[i][j] == -player) preCountOpp++;
            if (current_board[i][j] == player) curCountPlayer++;
            if (current_board[i][j] == -player) curCountOpp++;
        }
    }

    for (int m = 0; m < 5; m++) {
        for (int n = 0; n < 5; n++) {
            if (previous_board[m][n] == -player && current_board[m][n] == 0) {
                target = Position(m, n);
                break;
            }
        }
    }

    if ((preCountPlayer == curCountPlayer) && (preCountOpp == curCountOpp)) {
        vector<Position> oppNeighbor = neighbor(current_board, target, player);
        if (!oppNeighbor.size())
            return kq;
        else {
            for (Position item : oppNeighbor) {
                if (ganh(current_board, Move(item, target), player).size()) 
                    kq.push_back(Move(item, target));
            }
        }
    } 
    return kq;
};

vector<Move> get_valid_moves(int** current_board, int** previous_board, int player) {
    vector<Move> kq;
    vector<Move> trap = bay_or_mo(current_board, previous_board, player);
    if (trap.size())
        kq = trap;
    else {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (current_board[i][j] == player) {
                    vector<Position> avaiMove = canMoveTo(current_board, Position(i, j), player);
                    for (Position item : avaiMove)
                        kq.push_back(Move(Position(i, j), item));
                }
            }
        }
    }
    return kq;
};

int evaluate(int** board, int player) {
    int score = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == player)
                score++;
            if (board[i][j] == -player)
                score--;
        }
    }
    return score;
}

bool startCheck(int** curBoard, int** preBoard) {
    bool flag = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (curBoard[i][j] != preBoard[i][j]) {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}

void act_move(int** current_board, Move m, int player);

int maxValue(int** curBoard, int** preBoard, int player, int depth, int alpha, int beta);

int minValue(int** curBoard, int** preBoard, int player, int depth, int alpha, int beta) {
    vector<Move> moves = get_valid_moves(curBoard, preBoard, player);
    if (depth == 0 || !moves.size())
        return evaluate(curBoard, -player);
    int value = 16;
    for (Move item : moves) {
        int** clone = copy_board(curBoard);
        act_move(clone, item, player);
        value = min(value, maxValue(clone, curBoard, -player, depth - 1, alpha, beta));
        if (value <= alpha)
            return value;
        beta = min(beta, value);
        delete[] clone;
    }
    return value;
};

int maxValue(int** curBoard, int** preBoard, int player, int depth, int alpha, int beta) {
    vector<Move> moves = get_valid_moves(curBoard, preBoard, player);
    if (depth == 0 || !moves.size())
        return evaluate(curBoard, -player);
    int value = 0;
    for (Move item : moves) {
        int** clone = copy_board(curBoard);
        act_move(clone, item, player);
        value = max(value, minValue(clone, curBoard, -player, depth - 1, alpha, beta));
        if (value >= alpha)
            return value;
        alpha = max(alpha, value);
        delete[] clone;
    }
    return value;
};

Move select_move(int** current_board, int** previous_board, int player) {
    Move bestMove = Move(Position(-1, -1), Position(-1, -1));
    vector<Move> moves = get_valid_moves(current_board, previous_board, player);
    vector<Move> kq;
    vector<int> kqval;
    if (startCheck(current_board, previous_board)) {
        srand(time(0));
        return moves.at(rand() % moves.size());
    }
    else {
        if (!moves.size())
            return bestMove;
        else if (moves.size() == 1)
            return moves[0];
        else {
            bestMove = moves[0];
            int bestValue = -16, beta = 16, depth = 4;
            for (Move item : moves) {
                int** clone = copy_board(current_board);
                act_move(clone, item, player);
                int value = minValue(clone, current_board, -player, depth, bestValue, beta);
                if (value >= bestValue) {
                    bestValue = value;
                    kq.push_back(item);
                    kqval.push_back(value);
                }
                delete[] clone;
            }
            
            if (kq.size() == 1)
                return kq[0];
            else {
                int s = kqval.size();
                for (int i = 0; i < s; i++) {
                    if (kqval[i] < bestValue) {
                        kq.erase(kq.begin() + i);
                        s--;
                    }
                }
                srand(time(0));
                bestMove = kq[rand() % kq.size()];
            }
        }
    }
    return bestMove;
};

Move shallow_select_move(int** current_board, int** previous_board, int player) {
    Move bestMove = Move(Position(-1, -1), Position(-1, -1));
    vector<Move> moves = get_valid_moves(current_board, previous_board, player);
    vector<Move> kq;
    vector<int> kqval;
    if (startCheck(current_board, previous_board)) {
        srand(time(0));
        return moves.at(rand() % moves.size() - 1 + 1);
    }
    else {
        if (!moves.size())
            return bestMove;
        else if (moves.size() == 1)
            return moves[0];
        else {
            int bestValue = -100;
            bestMove = moves[0];
            for (Move item : moves) {
                int** clone = copy_board(current_board);
                act_move(clone, item, player);
                int value = evaluate(clone, player);
                if (value >= bestValue) {
                    bestValue = value;
                    kq.push_back(item);
                    kqval.push_back(value);
                }
                delete[] clone;
            }

            if (kq.size() == 1)
                return kq[0];
            else {
                int s = kqval.size();
                for (int i = 0; i < s; i++) {
                    if (kqval[i] < bestValue) {
                        kq.erase(kq.begin() + i);
                        s--;
                    }
                }
                srand(time(0));
                bestMove = kq[rand() % kq.size()];
            }
        }
    }
    return bestMove;
}

void act_move(int** current_board, Move m, int player) {
    if (isErrorMove(current_board, m, player))
        cout << "Error Move!";
    else {
        vector<Position> g = ganh(current_board, m, player);
        if (g.size()) {
            for (Position item : g)
                current_board[item.x][item.y] = player;
        }
        vector<Position> v = vay(current_board, m, player);
        if (v.size()) {
            for (Position item : v)
                current_board[item.x][item.y] = player;
        }
        current_board[m.pos_start.x][m.pos_start.y] = 0;
        current_board[m.pos_end.x][m.pos_end.y] = player;
    }
};

void play(int first)
{
    int count = 0, limit = 25;
    int player;
    if (first == 1)
        player = 1;
    else
        player = -1;

    int** board = init_board();
    int** pre_board = copy_board(board);
    cout << "Initial Board\n";
    print_board(board);
    cout << "\n";
    while (count < limit)
    {
        count++;
        Move move = Move(Position(-1, -1), Position(-1, -1));
        if (player == 1) {
            move = select_move(board, pre_board, player);
            if (move.pos_start.x != -1 && move.pos_start.y != -1 && move.pos_end.x != -1 && move.pos_end.y != -1) {
                pre_board = copy_board(board);
                act_move(board, move, player);
            }  
            else
                break;
        }
        else {
            move = shallow_select_move(board, pre_board, player);
            if (move.pos_start.x != -1 && move.pos_start.y != -1 && move.pos_end.x != -1 && move.pos_end.y != -1) {
                pre_board = copy_board(board);
                act_move(board, move, player);
            }
            else
                break;
        }
        cout << "Turn " << count << " (" << player << "): (";
        cout << move.pos_start.x << ", " << move.pos_start.y << ")->(" << move.pos_end.x << ", " << move.pos_end.y << ")\n";
        cout << "Current Score: " << evaluate(board, player) << "\n";
        print_board(board);
        cout << "\n";
        player *= -1;
    }

    int score1 = evaluate(board, 1);
    int score2 = evaluate(board, -1);
    if (score1 > score2)
        cout << "Player 1 win! Score: " << score1;
    else if (score1 < score2)
        cout << "Player -1 win! Score: " << score2;
    else
        cout << "Draw!";
}

int main()
{
    play(1);
    return 0;
}