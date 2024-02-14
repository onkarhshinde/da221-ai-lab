#include <bits/stdc++.h>


using namespace std;
using namespace std::chrono;
int kp =0;int sum=0;
const int SIZE = 3;

// Function to display the Tic-Tac-Toe board
void displayBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] ;
            if(j<2){
                cout<<" | ";
            }
        }

        cout << endl;
        if(i<2){
        cout<<"--  --  --"<<endl;}
    }
    sum+=kp;
    cout<<kp<<endl;
}

// Function to check if a player has won
bool checkWin(char board[SIZE][SIZE], char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

// Function to check if the board is full
bool isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Function to evaluate the static score of the board
int evaluateBoard(char board[SIZE][SIZE]) {
    if (checkWin(board, 'X'))
        return 1;  // AI wins
    else if (checkWin(board, 'O'))
        return -1; // Human wins
    else
        return 0;  // Draw
}


// Minimax algorithm without alpha-beta pruning
int minimax(char board[SIZE][SIZE], int depth, bool isMaximizing) {
    int score = evaluateBoard(board);
   kp++;
    if (score == 1 || score == -1)
        return score;

    if (isBoardFull(board))
        return 0; // Draw

    if (isMaximizing) {
        int maxEval = INT_MIN;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int eval = minimax(board, depth + 1, false);
                    maxEval = max(maxEval, eval);
                
                    board[i][j] = ' ';
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int eval = minimax(board, depth + 1, true);
                    minEval = min(minEval, eval);
                    
                    board[i][j] = ' ';
                }
            }
        }
        return minEval;
    }
}

// Function to make the AI move using the Minimax algorithm
void makeAIMove(char board[SIZE][SIZE]) {
    kp=0;
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                int moveScore = minimax(board, 0, false);
                board[i][j] = ' ';

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = {i, j};
                }
            }
        }
    }

    board[bestMove.first][bestMove.second] = 'X';
    
}

// Function to play the Tic-Tac-Toe game
void playTicTacToe() {
    char board[SIZE][SIZE] = {{' ', ' ', ' '},
                              {' ', ' ', ' '},
                              {' ', ' ', ' '}};

    while (true) {
        // Human's turn
        kp =0;
        int row, col;
        cout << "Enter your move (row and column, separated by space): ";
        cin >> row >> col;
        cout<<endl;
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row][col] = 'O';
        displayBoard(board);

        if (checkWin(board, 'O')) {
            cout << "You win!" << endl;
            break;
        }

        if (isBoardFull(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        // AI's turn
        makeAIMove(board);
        cout << "AI's move:" << endl;
        displayBoard(board);

        if (checkWin(board, 'X')) {
            cout << "AI wins!" << endl;
            break;
        }

        if (isBoardFull(board)) {
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    auto start = high_resolution_clock::now();
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    playTicTacToe();
    cout<<sum;
     auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout <<"  " <<duration.count() << endl;
    return 0;
}
