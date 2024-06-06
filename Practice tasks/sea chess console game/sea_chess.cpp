#include <iostream>
#include <cassert>

using std::cout;
using std::cin;
using std::endl;

const unsigned int MAX_N = 100;
const char sign1 = 'O';
const char sign2 = 'X';
const char sign3 = '_';

//functions for checking if someone wins

bool checkRows(char board[MAX_N][MAX_N], unsigned int sizeBoard) {
    for (int i = 0; i < sizeBoard; i++) {
        unsigned int counter1 = 0;
        unsigned int counter2 = 0;
        for (int j = 0; j < sizeBoard; j++) {
            if (board[i][j] == sign1) counter1++;
            if (board[i][j] == sign2) counter2++;
        }
        if (counter1 == sizeBoard || counter2 == sizeBoard) return true;
    }
    return false;
}

bool checkCols(char board[MAX_N][MAX_N], unsigned int sizeBoard) {
    for (int i = 0; i < sizeBoard; i++) {
        unsigned int counter1 = 0;
        unsigned int counter2 = 0;
        for (int j = 0; j < sizeBoard; j++) {
            if (board[j][i] == sign1) counter1++;
            if (board[j][i] == sign2) counter2++;
        }
        if (counter1 == sizeBoard || counter2 == sizeBoard) return true;
    }
    return false;
}

bool checkMainDiagonal(char board[MAX_N][MAX_N], unsigned int sizeBoard) {
    unsigned int counter1 = 0;
    unsigned int counter2 = 0;
    for (int i = 0, j = i; i < sizeBoard; i++) {
        if (board[i][j] == sign1)counter1++;
        if (board[i][j] == sign2)counter2++;
        
    }
    if (counter1 == sizeBoard || counter2 == sizeBoard)return true;
    else {
        return false;
    }
}

bool checkOppositeDiagonal(char board[MAX_N][MAX_N], unsigned int sizeBoard) {
    unsigned int counter1 = 0;
    unsigned int counter2 = 0;
    for (int i = 0; i < sizeBoard; i++) {
        for (int j = sizeBoard - 1; j >= 0;j--) {
            if (board[i][j] == sign1)counter1++;
            if (board[i][j] == sign2)counter2++;
        }
    }
    if (counter1 == sizeBoard || counter2 == sizeBoard)return true;
    else {
        return false;
    }
}

void printBoard(char board[MAX_N][MAX_N], unsigned int sizeBoard) {
    cout << "\n";
    cout << "   ";
    for (int j = 0; j < sizeBoard; j++) {
        cout << j + 1 << " ";
    }
    cout << endl;

    for (int i = 0; i < sizeBoard; i++) {
        cout << i + 1 << "  ";

        for (int j = 0; j < sizeBoard; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void player1(char board[MAX_N][MAX_N], unsigned int sizeBoard) {
    unsigned short index1;
    unsigned short index2;

    cout << "Player 1's turn " << endl;
    cout << "\n";
    cout << "Enter coordinate row: " << endl;
    cin >> index1;
    cout << "\n";
    cout << "Enter coordinate col: " << endl;
    cin >> index2;
    cout << "\n";
    assert(index1 <= sizeBoard && index2 <= sizeBoard);

    while (board[index1 - 1][index2 - 1] != sign3) {
        cout << "Space is already used, try a different one" << endl;
        cout << "Enter coordinate row: " << endl;
        cin >> index1;
        cout << "Enter coordinate col: " << endl;
        cin >> index2;
    }

    board[index1 - 1][index2 - 1] = sign1;

}

void player2(char board[MAX_N][MAX_N], unsigned int sizeBoard) {
    unsigned short index1;
    unsigned short index2;

    cout << "Player 2's turn " << endl;
    cout << "\n";
    cout << "Enter coordinate row: " << endl;
    cin >> index1;
    cout << "\n";
    cout << "Enter coordinate col: " << endl;
    cin >> index2;
    cout << "\n";
    assert(index1 <= sizeBoard && index2 <= sizeBoard);

    while (board[index1 - 1][index2 - 1] != sign3) {
        cout << "Space is already used, try a different one" << endl;
        cout << "Enter coordinate row: " << endl;
        cin >> index1;
        cout << "Enter coordinate col: " << endl;
        cin >> index2;
    }

    board[index1 - 1][index2 - 1] = sign2;
}

bool endGame(char board[MAX_N][MAX_N], unsigned int sizeBoard) {
    unsigned int check = sizeBoard;
    for (int i = 0; i < sizeBoard; i++) {
        for (int j = 0; j < sizeBoard; j++) {
            if (board[i][j] != sign3)check--;
        }
    }
    if (check == 0)return true;
}

int main()
{
    //create the board
    unsigned int sizeBoard;
    char board[MAX_N][MAX_N];
    cout << "Enter size of board: " << endl;
    cin >> sizeBoard;
    assert(sizeBoard <= MAX_N);
    cout << "*--------------------------------*" << endl;

    for (int i = 0; i < sizeBoard; i++) {
        for (int j = 0; j < sizeBoard; j++) {
            board[i][j] = sign3;
        }
    }

    //player's turns and progressing the game
    bool check1 = false;
    bool check2 = false;
    bool check3 = false;
    bool check4 = false;
    bool check5 = false;
    bool check6 = false;
    bool check7 = false;
    bool check8 = false;
    bool check9 = false;

    while (check1 != true || check2 != true || check3 != true || check4 != true ||
        check5 != true || check6 != true || check7 != true || check8 != true
        ) {
        printBoard(board, sizeBoard);
        cout << "\n";
        player1(board, sizeBoard);
        check1 = checkMainDiagonal(board, sizeBoard);
        check2 = checkOppositeDiagonal(board, sizeBoard);
        check3 = checkRows(board, sizeBoard);
        check4 = checkCols(board, sizeBoard);
        if (check1 == true || check2 == true || check3 == true || check4 == true) {
            cout << "Player 1 wins! " << "\n";
            printBoard(board, sizeBoard);
            cout << "\n";
            break;
        }
        
        printBoard(board, sizeBoard);
        cout << "\n";
        player2(board, sizeBoard);
        check5 = checkMainDiagonal(board, sizeBoard);
        check6 = checkOppositeDiagonal(board, sizeBoard);
        check7 = checkRows(board, sizeBoard);
        check8 = checkCols(board, sizeBoard);
        if (check1 == true || check2 == true || check3 == true || check4 == true) {
            cout << "Player 2 wins! " << "\n";
            printBoard(board, sizeBoard);
            cout << "\n";
            break;
        }
        check9 = endGame(board, sizeBoard);
        if (check9 == true) {
            cout << "Draw !" << endl;
            break;
        }
    }
}