#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;
int **init_board()
{
    int **t = new int *[5];
    for (int i = 0; i < 5; i++)
    {
        t[i] = new int[5];
        if (i == 0)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = 1;
        }
        else if (i == 4)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = -1;
        }
        else
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = 0;
        }
    }
    t[1][0] = 1;
    t[1][4] = 1;
    t[2][0] = 1;
    t[2][4] = -1;
    t[3][0] = -1;
    t[3][4] = -1;

    return t;
}
int **copy_board(int **board)
{
    int **n_b = new int *[5];
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
void print_board(int **board)
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
    int x;
    int y;
    Position() { x = y = 0; }
    Position(int a, int b)
    {
        x = a;
        y = b;
    }
};
struct Move
{
    Position pos_start, pos_end;
    Move(Position s, Position e)
    {
        pos_start = s;
        pos_end = e;
    }
};
void changeBoard(int **board, vector<Position> pos, int value)
{
    vector<Position>::iterator i;
    Position xy;
    i = pos.begin();
    for (; i != pos.end(); ++i)
    {
        xy = *i;
        board[xy.x][xy.y] = value;
    }
}
void deleteBoard(int **board)
{
    for (int i = 0; i < 5; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}
void copyBoard(int **board, int **newBoard)
{
    for (int i = 0, j = 0; i < 5; i++, j++)
    {
        for (int j = 0; j < 5; j++)
        {
            newBoard[i][j] = board[i][j];
        }
    }
}
void gen_move(Position pop_start, int **board, vector<Position> &dest_list)
{
    int x = pop_start.x;
    int y = pop_start.y;
    Position dest;
    if (x + 1 < 5)
    {
        dest.x = x + 1;
        dest.y = y;
        if (board[x + 1][y] != 1 && board[x + 1][y] != -1)
        {
            dest_list.push_back(dest);
        }
    }
    if (x - 1 >= 0)
    {
        dest.x = x - 1;
        dest.y = y;
        if (board[x - 1][y] != 1 && board[x - 1][y] != -1)
        {
            dest_list.push_back(dest);
        }
    }
    if (y + 1 < 5)
    {
        dest.x = x;
        dest.y = y + 1;
        if (board[x][y + 1] != 1 && board[x][y + 1] != -1)
        {
            dest_list.push_back(dest);
        }
    }
    if (y - 1 >= 0)
    {
        dest.x = x;
        dest.y = y - 1;
        if (board[x][y - 1] != 1 && board[x][y - 1] != -1)
        {
            dest_list.push_back(dest);
        }
    }
    if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
    {
        if (x + 1 < 5 && y + 1 < 5)
        {
            dest.x = x + 1;
            dest.y = y + 1;
            if (board[x + 1][y + 1] != 1 && board[x + 1][y + 1] != -1)
            {
                dest_list.push_back(dest);
            }
        }
        if (x - 1 >= 0 && y - 1 >= 0)
        {
            dest.x = x - 1;
            dest.y = y - 1;
            if (board[x - 1][y - 1] != 1 && board[x - 1][y - 1] != -1)
            {
                dest_list.push_back(dest);
            }
        }
        if (x - 1 >= 0 && y + 1 < 5)
        {
            dest.x = x - 1;
            dest.y = y + 1;
            if (board[x - 1][y + 1] != 1 && board[x - 1][y + 1] != -1)
            {
                dest_list.push_back(dest);
            }
        }
        if (x + 1 < 5 && y - 1 >= 0)
        {
            dest.x = x + 1;
            dest.y = y - 1;
            if (board[x + 1][y - 1] != 1 && board[x + 1][y - 1] != -1)
            {
                dest_list.push_back(dest);
            }
        }
    }
};
vector<Position> ganh(int **board, Move m, int player)
{
    vector<Position> ganhList;
    int destX = m.pos_end.x;
    int destY = m.pos_end.y;
    if (destX - 1 >= 0 && destX + 1 < 5)
    {
        if (board[destX - 1][destY] == -player && board[destX + 1][destY] == -player)
        {
            ganhList.push_back(Position(destX - 1, destY));
            ganhList.push_back(Position(destX + 1, destY));
        }
    }
    if (destY - 1 >= 0 && destY + 1 < 5)
    {
        if (board[destX][destY - 1] == -player && board[destX][destY + 1] == -player)
        {
            ganhList.push_back(Position(destX, destY - 1));
            ganhList.push_back(Position(destX, destY + 1));
        }
    }
    if ((destX % 2 == 0 && destY % 2 == 0) || (destX % 2 == 1 && destY % 2 == 1))
    {
        if (destX - 1 >= 0 && destY - 1 >= 0 && destX + 1 < 5 && destY + 1 < 5)
        {
            if (board[destX - 1][destY - 1] == -player && board[destX + 1][destY + 1] == -player)
            {
                ganhList.push_back(Position(destX - 1, destY - 1));
                ganhList.push_back(Position(destX + 1, destY + 1));
            }
        }
        if (destX + 1 < 5 && destY - 1 >= 0 && destX - 1 >= 0 && destY + 1 < 5)
        {
            if (board[destX - 1][destY + 1] == -player && board[destX + 1][destY - 1] == -player)
            {
                ganhList.push_back(Position(destX - 1, destY + 1));
                ganhList.push_back(Position(destX + 1, destY - 1));
            }
        }
    }
    return ganhList;
};
vector<Position> DSlienKe(Position pos, int **board, int neighbour)
{
    int destX = pos.x;
    int destY = pos.y;
    vector<Position> neighbourList;
    if (destX - 1 >= 0)
    {
        if (board[destX - 1][destY] == neighbour)
        {
            neighbourList.push_back(Position(destX - 1, destY));
        }
    }
    if (destX + 1 < 5)
    {
        if (board[destX + 1][destY] == neighbour)
        {
            neighbourList.push_back(Position(destX + 1, destY));
        }
    }
    if (destY - 1 >= 0)
    {
        if (board[destX][destY - 1] == neighbour)
        {
            neighbourList.push_back(Position(destX, destY - 1));
        }
    }
    if (destY + 1 < 5)
    {
        if (board[destX][destY + 1] == neighbour)
        {
            neighbourList.push_back(Position(destX, destY + 1));
        }
    }
    if ((destX % 2 == 0 && destY % 2 == 0) || (destX % 2 == 1 && destY % 2 == 1))
    {
        if (destX - 1 >= 0 && destY + 1 < 5)
        {
            if (board[destX - 1][destY + 1] == neighbour)
            {
                neighbourList.push_back(Position(destX - 1, destY + 1));
            }
        }
        if (destX + 1 < 5 && destY + 1 < 5)
        {
            if (board[destX + 1][destY + 1] == neighbour)
            {
                neighbourList.push_back(Position(destX + 1, destY + 1));
            }
        }
        if (destX - 1 >= 0 && destY - 1 >= 0)
        {
            if (board[destX - 1][destY - 1] == neighbour)
            {
                neighbourList.push_back(Position(destX - 1, destY - 1));
            }
        }
        if (destX + 1 < 5 && destY - 1 >= 0)
        {
            if (board[destX + 1][destY - 1] == neighbour)
            {
                neighbourList.push_back(Position(destX + 1, destY - 1));
            }
        }
    }
    return neighbourList;
}
void checkVay(Position quanDich, int visited[][5], int **board, bool &flag, vector<Position> &DSvayCheck)
{
    int x = quanDich.x;
    int y = quanDich.y;
    visited[x][y] = 1;
    vector<Position> dongDoi;
    vector<Position> empty_Pos;
    DSvayCheck.push_back(quanDich);
    dongDoi = DSlienKe(quanDich, board, board[x][y]);
    empty_Pos = DSlienKe(quanDich, board, 0);
    if (dongDoi.empty() && empty_Pos.empty())
    {
    }
    else if (!empty_Pos.empty())
    {
        flag = true;
    }
    vector<Position>::iterator i;
    i = dongDoi.begin();
    for (; i != dongDoi.end(); ++i)
    {
        Position xy = *i;
        if (visited[xy.x][xy.y] == 1)
        {
            continue;
        }
        else
        {
            checkVay(xy, visited, board, flag, DSvayCheck);
        }
    }
    return;
}
vector<Position> vay(int **board, Move m, int player)
{
    vector<Position> neighbourList;
    vector<Position> DSvayTotal;
    vector<Position> DSvayCheck;
    vector<Position> ganhList;
    bool flag;
    int **nextBoard = new int *[5];
    for (int i = 0; i < 5; i++)
    {
        nextBoard[i] = new int[5];
        for (int j = 0; j < 5; j++)
        {
            nextBoard[i][j] = 0;
        }
    }
    copyBoard(board, nextBoard);
    ganhList = ganh(board, m, player);
    nextBoard[m.pos_start.x][m.pos_start.y] = 0;
    nextBoard[m.pos_end.x][m.pos_end.y] = player;

    if (!ganhList.empty())
    {
        changeBoard(nextBoard, ganhList, player);
    }
    ganhList.push_back(m.pos_end);
    neighbourList.clear();
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (nextBoard[i][j] == -player)
            {
                neighbourList.push_back(Position(i, j));
            }
        }
    }
    int visited[5][5] = {0};
    vector<Position>::iterator i;
    i = neighbourList.begin();
    for (; i != neighbourList.end(); ++i)
    {
        Position xy = *i;
        if (visited[xy.x][xy.y] == 1)
        {
            continue;
        }
        flag = false;
        checkVay(*i, visited, nextBoard, flag, DSvayCheck);
        if (!flag)
        {
            if (!DSvayCheck.empty())
            {
                DSvayTotal.insert(DSvayTotal.end(), DSvayCheck.begin(), DSvayCheck.end());
            }
        }
        DSvayCheck.clear();
    }
    deleteBoard(nextBoard);
    return DSvayTotal;
};
vector<Move> bay_or_mo(int **current_board, int **previous_board, int player)
{
    int num1Prev = 0;
    int num1Curr = 0;
    vector<Position> mayBeTrap;
    vector<Move> moveList;
    if (previous_board == nullptr || current_board == nullptr)
        return moveList;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (current_board[i][j] == 1)
            {
                num1Curr++;
            }
            if (previous_board[i][j] == 1)
            {
                num1Prev++;
            }
            if (previous_board[i][j] == -player && current_board[i][j] != -player)
            {
                mayBeTrap.push_back(Position(i, j));
            }
            if (current_board[i][j] == player)
            {
                vector<Position> destList;
                Position pos_start = Position(i, j);
                gen_move(pos_start, current_board, destList);
                if (destList.size() != 0)
                {
                    vector<Position>::iterator i = destList.begin();
                    for (; i != destList.end(); ++i)
                    {
                        Move movePoint = Move(pos_start, *i);
                        moveList.push_back(movePoint);
                    }
                }
            }
        }
    }
    vector<Position> trapList;
    if (num1Curr == num1Prev)
    {
        vector<Position>::iterator i;
        i = mayBeTrap.begin();
        Position pos;
        int destX, destY;
        for (; i != mayBeTrap.end(); ++i)
        {
            pos = *i;
            destX = pos.x;
            destY = pos.y;
            if (destX - 1 >= 0 && destX + 1 < 5)
            {
                if (current_board[destX - 1][destY] == -player && current_board[destX + 1][destY] == -player)
                {
                    trapList.push_back(Position(destX, destY));
                    continue;
                }
            }
            if (destY - 1 >= 0 && destY + 1 < 5)
            {
                if (current_board[destX][destY - 1] == -player && current_board[destX][destY + 1] == -player)
                {
                    trapList.push_back(Position(destX, destY));
                    continue;
                }
            }
            if ((destX % 2 == 0 && destY % 2 == 0) || (destX % 2 == 1 && destY % 2 == 1))
            {
                if (destX - 1 >= 0 && destY - 1 >= 0 && destX + 1 < 5 && destY + 1 < 5)
                {
                    if (current_board[destX - 1][destY - 1] == -player && current_board[destX + 1][destY + 1] == -player)
                    {
                        trapList.push_back(Position(destX, destY));
                        continue;
                    }
                }
                if (destX - 1 >= 0 && destY + 1 < 5 && destX + 1 < 5 && destY - 1 >= 0)
                {
                    if (current_board[destX - 1][destY + 1] == -player && current_board[destX + 1][destY - 1] == -player)
                    {
                        trapList.push_back(Position(destX, destY));
                        continue;
                    }
                }
            }
        }
    }
    vector<Move>::iterator i;
    vector<Position>::iterator j;
    vector<Move> forceMove;
    for (j = trapList.begin(); j != trapList.end(); ++j)
    {
        for (i = moveList.begin(); i != moveList.end(); ++i)
        {
            Position des = *j;
            Move checkMove = *i;
            if (des.x == checkMove.pos_end.x && des.y == checkMove.pos_end.y)
            {
                forceMove.push_back(checkMove);
            }
        }
    }
    return forceMove;
};
vector<Move> get_valid_moves(int **current_board, int **previous_board, int player)
{
    vector<Move> moveList;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (current_board[i][j] == player)
            {
                vector<Position> destList;
                Position pos_start = Position(i, j);
                gen_move(pos_start, current_board, destList);
                if (destList.size() != 0)
                {
                    vector<Position>::iterator i = destList.begin();
                    for (; i != destList.end(); ++i)
                    {
                        Move movePoint = Move(pos_start, *i);
                        moveList.push_back(movePoint);
                    }
                }
            }
        }
    }
    vector<Move> forceMove = bay_or_mo(current_board, previous_board, player);
    if (forceMove.empty())
    {
        return moveList;
    }
    return forceMove;
};

void act_move(int **current_board, Move m, int player)
{
    int destX = m.pos_end.x;
    int destY = m.pos_end.y;
    int srcX = m.pos_start.x;
    int srcY = m.pos_start.y;
    current_board[srcX][srcY] = 0;
    current_board[destX][destY] = player;
    vector<Position> ganhList = ganh(current_board, m, player);
    vector<Position> vayList = vay(current_board, m, player);
    ganhList.insert(ganhList.end(), vayList.begin(), vayList.end());
    changeBoard(current_board, ganhList, player);
    return;
};
int countDie(int **board, int player)
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == player)
            {
                count++;
            }
        }
    }
    return count;
}
class AI
{
private:
    clock_t start = clock();

public:
    bool timeOut()
    {
        clock_t end = clock();
        double totalTime = double(end - start) / double(CLOCKS_PER_SEC);
        if (totalTime > 2.8)
            return true;
        return false;
    }
    vector<Move> alphaBeteAI(int **current_board, int **pre_board, int player)
    {
        int bestValue;
        if (player == 1)
        {
            bestValue = -99999;
        }
        else
        {
            bestValue = 99999;
        }
        int beta = 99999;
        vector<Move> bestMoves;
        vector<Move> movesList = get_valid_moves(current_board, pre_board, player);
        int doiThu = demQuan(current_board, -player);
        if (doiThu == 1)
        {
            Position DTpos = viTriDoiThu(current_board, -player);
            vector<Move>::iterator i = movesList.begin();
            vector<Move> newMovesList;
            for (; i != movesList.end(); ++i)
            {
                Move checkMove = *i;
                if ((checkMove.pos_start.x <= (DTpos.x + 2) && checkMove.pos_start.x >= (DTpos.x - 2)) && (checkMove.pos_start.y <= (DTpos.y + 2) && checkMove.pos_start.y >= (DTpos.y - 2)))
                {
                    newMovesList.push_back(checkMove);
                }
            }
            if (!newMovesList.empty())
            {
                movesList = newMovesList;
            }
        }
        if (movesList.empty())
        {
            return bestMoves;
        }
        int numOfMove = movesList.size();
        if (numOfMove == 1)
        {
            return movesList;
        }
        int depth = 1;
        vector<Move>::iterator i = movesList.begin();
        int **newBoard = new int *[5];
        for (int i = 0; i < 5; i++)
        {
            newBoard[i] = new int[5];
        }
        int value;
        vector<int> bestValueList;
        while (!timeOut())
        {
            i = movesList.begin();
            for (; i != movesList.end(); ++i)
            {
                copyBoard(current_board, newBoard);
                act_move(newBoard, *i, player);
                if (player == 1)
                {
                    value = get_min(newBoard, current_board, bestValue, beta, depth - 1, -player);
                    if (value >= bestValue)
                    {
                        bestValue = value;
                        bestMoves.push_back(*i);
                        bestValueList.push_back(value);
                    }
                    if (value > 9999)
                    {
                        bestMoves.clear();
                        bestMoves.push_back(*i);
                        deleteBoard(newBoard);
                        return bestMoves;
                    }
                }
                else
                {
                    value = get_max(newBoard, current_board, bestValue, beta, depth - 1, -player);
                    if (value <= bestValue)
                    {
                        bestValue = value;
                        bestMoves.push_back(*i);
                        bestValueList.push_back(value);
                    }
                    if (value < -9999)
                    {
                        bestMoves.clear();
                        bestMoves.push_back(*i);
                        deleteBoard(newBoard);
                        return bestMoves;
                    }
                }
            }
            depth += 1;
        }
        i = bestMoves.begin();
        vector<int>::iterator j = bestValueList.begin();
        vector<Move> chooseBestMove;
        for (; i != bestMoves.end(); ++i)
        {
            if (*j == bestValue)
            {
                chooseBestMove.push_back(*i);
            }
            ++j;
        }
        deleteBoard(newBoard);
        return chooseBestMove;
    }
    int get_min(int **current_board, int **pre_board, int alpha, int beta, int depth, int player)
    {
        if (depth == 0 || timeOut())
        {
            return getValue(current_board, pre_board, -player);
        }
        int value = 99999;
        int **newBoard = new int *[5];
        for (int i = 0; i < 5; i++)
        {
            newBoard[i] = new int[5];
        }
        int getMax;
        int soQuanAn;
        vector<Move> movesList = get_valid_moves(current_board, pre_board, player);
        vector<Move>::iterator i = movesList.begin();
        for (; i != movesList.end(); ++i)
        {
            copyBoard(current_board, newBoard);
            act_move(newBoard, *i, player);
            soQuanAn = anQuan(player, newBoard, current_board) * player;
            getMax = get_max(newBoard, current_board, alpha, beta, depth - 1, -player);
            getMax = soQuanAn + getMax;
            if (value > getMax)
            {
                value = getMax;
            }
            if (value <= alpha)
            {
                deleteBoard(newBoard);
                return value;
            }
            if (beta > value)
            {
                beta = value;
            }
            if (timeOut())
            {
                break;
            }
        }
        deleteBoard(newBoard);
        return value;
    }
    int get_max(int **current_board, int **pre_board, int alpha, int beta, int depth, int player)
    {
        if (depth == 0 || timeOut())
        {
            return getValue(current_board, pre_board, -player);
        }
        int value = -99999;
        int **newBoard = new int *[5];
        for (int i = 0; i < 5; i++)
        {
            newBoard[i] = new int[5];
        }
        int getMin;
        int soQuanAn;
        vector<Move> movesList = get_valid_moves(current_board, pre_board, player);
        vector<Move>::iterator i = movesList.begin();
        for (; i != movesList.end(); ++i)
        {
            copyBoard(current_board, newBoard);
            act_move(newBoard, *i, player);
            soQuanAn = anQuan(player, newBoard, current_board) * player;
            getMin = get_min(newBoard, current_board, alpha, beta, depth - 1, -player);
            getMin = soQuanAn + getMin;
            if (value < getMin)
            {
                value = getMin;
            }
            if (value >= beta)
            {
                deleteBoard(newBoard);
                return value;
            }
            if (beta < value)
            {
                beta = value;
            }
            if (timeOut())
            {
                break;
            }
        }
        deleteBoard(newBoard);
        return value;
    }
    int getValue(int **current_board, int **pre_board, int player)
    {
        int quanX = demQuan(current_board, 1);
        int quan0 = demQuan(current_board, -1);
        if (player == 1)
        {
            if (quanX == 0)
            {
                return -99999;
            }
            else if (quan0 == 0)
            {
                return 99999;
            }
            return quanX - quan0;
        }
        if (player == -1)
        {
            if (quanX == 0)
            {
                return -99999;
            }
            else if (quan0 == 0)
            {
                return 99999;
            }
            return -(quan0 - quanX);
        }
        return 0;
    }
    int demQuan(int **board, int player)
    {
        int count = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (board[i][j] == player)
                {
                    count++;
                }
            }
        }
        return count;
    }
    int anQuan(int player, int **current_board, int **pre_board)
    {
        return demQuan(current_board, player) - demQuan(pre_board, player);
    }
    Position viTriDoiThu(int **board, int player)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (board[i][j] == player)
                {
                    return Position(i, j);
                }
            }
        }
        return Position(1,2);
    }
};
Move select_move(int **current_board, int **previous_board, int player)
{
    AI AIchoose;
    vector<Move> finalBestMoves = AIchoose.alphaBeteAI(current_board, previous_board, player);
    srand(time(NULL));
    int index = rand() % finalBestMoves.size();
    return finalBestMoves[index];
};
void play(int first)
{
    int count = 0, limit = 70;
    int player;
    if (first == 1)
        player = 1;
    else
        player = -1;

    int **board = init_board();
    int **pre_board = nullptr;
    print_board(board);
    while (count < limit)
    {

        count++;
        vector<Move> valid_moves = get_valid_moves(board, pre_board, player);
        if (valid_moves.size() != 0)
        {
            if (player == 1)
            {
                srand(time(NULL));
                int index = rand() % valid_moves.size();
                Move new_move = valid_moves[index];
                pre_board = copy_board(board);
                act_move(board, new_move, player);
            }
            else
            {
                Move m = select_move(board, pre_board, player);
                pre_board = copy_board(board);
                act_move(board, m, player);
            }
        }
        else
        {
            break;
        }

        player *= -1;
    }

}
int main()
{
    play(1);
    return 0;
}