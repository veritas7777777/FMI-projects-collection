#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int MAX_ROW = 20;
const int MAX_COL = 20;

int Getnum(int min, int max) {
    int num;
    do {
        num = rand() % (max - min + 1) + min;
    } while (num % 3 != 0);
    return num;
}

void GenerateLayer(char layer[MAX_ROW][MAX_COL], char *Symbols, int numberoftiles) {
    srand(time(NULL)); //https://cplusplus.com/reference/cstdlib/rand/

    for (size_t i = 0; i < MAX_ROW; ++i) {
        for (size_t j = 0; j < MAX_COL; ++j) {
            layer[i][j] =' ';
        }
    }

    for (size_t i = 0; i < numberoftiles; ++i) {
        int numTiles = Getnum(3, MAX_ROW);
        for (size_t j = 0; j < numTiles; ++j) {
            int row, col;
            do {
                row = rand() % MAX_ROW;
                col = rand() % MAX_COL;
            } while (layer[row][col] !=' ');

            layer[row][col] = Symbols[i];
        }
    }
}

void PrintLayer(char(&Layer)[MAX_ROW][MAX_COL], int row, int col) {
    for (size_t i = 0; i < row; ++i) {
        cout << "| ";
        for (size_t j = 0; j < col; ++j) {
            cout << Layer[i][j] << ' ';
        }
        cout << "|" << endl;
    }
    cout << endl;
}

void MatchSymbols(char* CombineBar) {
    for (size_t i = 0; i < 6; ++i) {
        if (CombineBar[i] != ' ' && CombineBar[i] == CombineBar[i + 1] && CombineBar[i] == CombineBar[i + 2]) {
            CombineBar[i] = ' ';
            CombineBar[i + 1] = ' ';
            CombineBar[i + 2] = ' ';
        }
    }

    size_t index = 0;
    for (size_t i = 0; i < 8; ++i) {
        if (CombineBar[i] != ' ') {
            CombineBar[index++] = CombineBar[i];
        }
    }

    for (; index < 8; ++index) {
        CombineBar[index] = ' ';
    }
}

void InputSymbols(char* Symbols, int numberoftiles) { 
    for (size_t i = 0; i < numberoftiles; ++i)
    {
        cout << "Input symbol " << i << ": ";
        cin >> Symbols[i];
    }
    cout << endl;
}

bool MoveSymbols(int x, int y, char* CombineBar, char (&layer)[MAX_ROW][MAX_COL]) {
    for (size_t i = 0; i < 8; ++i)
    {
        if (CombineBar[i] != ' ') continue;
        else {
            CombineBar[i] = layer[x][y];
            layer[x][y] = ' ';
            return true;
        }
    }
    return false;
}

bool IsWin(char layer[MAX_ROW][MAX_COL]) {
    for (size_t i = 0; i < MAX_ROW; ++i) {
        for (size_t j = 0; j < MAX_COL; ++j) {
            if (layer[i][j] != ' ') {
                return false;
            }
        }
    }
    return true;
}

void PrintBar(char* CombineBar) {
    cout << "| ";
    for (size_t i = 0; i < 8; ++i) {
        cout << CombineBar[i] << ' ';
    }
    cout << "|" << endl;
    cout << endl;
}

bool IsValid(int x, int y, char layer[MAX_ROW][MAX_COL]) {
    if (layer[x][y] == ' ')return false;
    else {
        cout << "Enter tile with symbol in it !" << endl;
        return true; }
}

bool IsEmpty(char* CombineBar) {
    for (size_t i = 0; i < 8; ++i) {
        if (CombineBar[i] == ' ')continue;
        else { return false; }
    }
    return true;
}

void Restart(char layer[MAX_ROW][MAX_COL], char* Symbols, int numberoftiles, char* CombineBar) {
    for (size_t i = 0; i < MAX_ROW; ++i) {
        for (size_t j = 0; j < MAX_COL; ++j) {
            layer[i][j] = ' ';
        }
    }

    for (size_t i = 0; i < 8; ++i) {
        CombineBar[i] = ' ';
    }

    GenerateLayer(layer, Symbols, numberoftiles);
}

int main()
{
    bool lost = false;
    bool valid = true;
    bool running = true;
    int numberoftiles, x, y;

    cout << "How many tiles: ";
    cin >> numberoftiles;
    cout << endl;

    if (numberoftiles < 8 || numberoftiles > 20) {
        throw out_of_range("Number of tiles must be between 8 and 20. ");
        return 1;
    }

    char *Symbols = new char[numberoftiles];
    char layer[MAX_ROW][MAX_COL];
    char CombineBar[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    InputSymbols(Symbols, numberoftiles);
    GenerateLayer(layer, Symbols, numberoftiles);
    PrintLayer(layer, MAX_ROW, MAX_COL);
    PrintBar(CombineBar);

    while (running) {
        do {
            cout << "Input coordinate x: ";
            cin >> x;
            cout << endl;
            cout << "Input coordinate y: ";
            cin >> y;
            cout << endl;
            IsValid(x, y, layer);
        } while (!valid);


        if (MoveSymbols(x, y, CombineBar, layer)) {
            MatchSymbols(CombineBar);
            PrintLayer(layer, MAX_ROW, MAX_COL);
            PrintBar(CombineBar);
        }
        else { cout << "Bar is full, you lost !";
        cout << endl;
        PrintLayer(layer, MAX_ROW, MAX_COL);
        PrintBar(CombineBar);
        lost = true;
        };

        if (IsWin(layer) && IsEmpty(CombineBar)) { 
        cout << "You won !!!"; 
        cout << endl;
        running = false;
        }

        if (lost) {
            bool answer;
            bool restart = false;
            cout << "Do you want to restart, type 1 for yes, type 0 for no";
            do {
                cin >> answer;

                if (answer == 0 || answer == 1) {
                    restart = true;
                }
                else {
                    cout << "Enter 1 or 0 for restart or quit ";
                }
            } while (!restart);

            if (answer) {
                Restart(layer, Symbols, numberoftiles, CombineBar);
                lost = false;
            }
            else {
                running = false;
            }
        }
    }
   
    delete[] Symbols;

    return 0;
}