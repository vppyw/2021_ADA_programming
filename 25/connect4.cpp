// reference: https://github.com/KeithGalli/Connect4-Python/blob/master/connect4_with_ai.py
#include "connect4.h"
#include <bits/stdc++.h>

// The columns are numbered from 0 to 6
int board[6][7];
int board_ptr[7] = {0};
int row_num = 6;
int col_num = 7;

void init() {
    for (int i = 0; i < col_num; i++) {
        board_ptr[i] = 0;
        for (int j = 0; j < row_num; j++) board[j][i] = 0;
    }
}

int eval_count(int *count) {
    int score = 0;
    if (count[1] == 3 && count[0] == 1) return 9;
    else if (count[1] == 2 && count[0] == 2) return 4;
    else if (count[1] == 1 && count[0] == 3) return 1;
    else if (count[2] == 3 && count[0] == 1) return -9;
    else if (count[2] == 2 && count[0] == 2) return -4;
    else if (count[2] == 1 && count[0] == 3) return -1;
    return score;
}

int eval() {
    int count[3];
    int ret = 0;
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 4; c++) {
            count[0] = 0, count[1] = 0, count[2] = 0;
            count[board[r][c]] += 1;
            count[board[r][c + 1]] += 1;
            count[board[r][c + 2]] += 1;
            count[board[r][c + 3]] += 1;
            ret += eval_count(count);
        }
    }
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 7; c++) {
            count[0] = 0, count[1] = 0, count[2] = 0;
            count[board[r][c]] += 1;
            count[board[r + 1][c]] += 1;
            count[board[r + 2][c]] += 1;
            count[board[r + 3][c]] += 1;
            ret += eval_count(count);
        }
    }
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 4; c++) {
            count[0] = 0, count[1] = 0, count[2] = 0;
            count[board[r][c]] += 1;
            count[board[r + 1][c + 1]] += 1;
            count[board[r + 2][c + 2]] += 1;
            count[board[r + 3][c + 3]] += 1;
            ret += eval_count(count);
        }
    }
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 4; c++) {
            count[0] = 0, count[1] = 0, count[2] = 2;
            count[board[r + 3][c]] += 1;
            count[board[r + 2][c + 1]] += 1;
            count[board[r + 1][c + 2]] += 1;
            count[board[r][c + 3]] += 1;
            ret += eval_count(count);
        }
    }
    return ret;
}

int win(int pid) {
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == pid &&
                board[r][c + 1] == pid &&
                board[r][c + 2] == pid &&
                board[r][c + 3] == pid) {
                return 1;
            }
        }
    }
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 7; c++) {
            if (board[r][c] == pid &&
                board[r + 1][c] == pid &&
                board[r + 2][c] == pid &&
                board[r + 3][c] == pid) {
                return 1;
            }
        }
    }
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == pid &&
                board[r + 1][c + 1] == pid &&
                board[r + 2][c + 2] == pid &&
                board[r + 3][c + 3] == pid) {
                return 1;
            }
        }
    }
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r + 3][c] == pid &&
                board[r + 2][c + 1] == pid &&
                board[r + 1][c + 2] == pid &&
                board[r][c + 3] == pid) {
                return 1;
            }
        }
    }
    return 0;
}

std::pair<int, int>minimax(int depth, int alpha, int beta, int mx) {
    int val, get_minimax, mv = -1;
    for (int i = 0; i < 7; i++) {
        if (board_ptr[i] != 6) {
            mv = i;
            break;
        }
    }
    if (mv == -1) {
        return std::pair{-1, 0};
    }
    if (win(2)) return std::pair{mv, -100000000};
    else if (win(1)) return std::pair{mv, 100000000};
    if (depth == 0) {
        return std::pair{-1, eval()};
    }
    if (mx) {
        val = INT_MIN;
        for (int i = 0; i < 7; i++) {
            if (board_ptr[i] < 6) {
                board[board_ptr[i]][i] = 1;
                board_ptr[i] += 1;
                get_minimax = minimax(depth - 1, alpha, beta, 0).second;
                board_ptr[i] -= 1;
                board[board_ptr[i]][i] = 0;
                if (get_minimax > val) {
                    val = get_minimax;
                    mv = i;
                }
                if (val > alpha) alpha = val;
                if (alpha >= beta) break;
            }
        }
        return std::pair{mv, val};
    }
    else {
        val = INT_MAX;
        for (int i = 0; i < 7; i++) {
            if (board_ptr[i] < 6) {
                board[board_ptr[i]][i] = 2;
                board_ptr[i] += 1;
                get_minimax = minimax(depth - 1, alpha, beta, 1).second;
                board_ptr[i] -= 1;
                board[board_ptr[i]][i] = 0;
                if (get_minimax < val) {
                    val = get_minimax;
                    mv = i;
                }
                if (val < beta) beta = val;
                if (alpha >= beta) break;
            }
        }
        return std::pair{mv, val};
    }
}

int decide(int yp_move) {
    int mv;
    std::pair<int, int> p;
    if (yp_move == -1) {
        // A new game starts
        // TODO: Please remember to reset everything here (if needed)
        init();
        p = minimax(5, INT_MIN, INT_MAX, 1);
        mv = p.first;
        board[board_ptr[mv]][mv] = 1;
        board_ptr[mv] += 1;
        return mv;
    }
    else {
        // YP placed his piece at column `yp_move` 
        board[board_ptr[yp_move]][yp_move] = 2;
        board_ptr[yp_move] += 1;
        p = minimax(5, INT_MIN, INT_MAX, 1);
        mv = p.first;
        board[board_ptr[mv]][mv] = 1;
        board_ptr[mv] += 1;
        return mv;
    }
    return 6; // always place at the rightmost column7}
}
