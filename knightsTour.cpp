/*
Author- Kaevin Barta
Version- .1
file- KnightsTour.snl

The program should:
     1.use a 5x5 board (the size should be easily reconfigurable with a single constant change)
     2.start with the knight in the middle
     3.Print out all solutions, and the total # of solutions found
*/

#include <iostream>

//the size of the board
const int BOARD_SIZE = 5;

//the array for game board
struct Board {
    int board[BOARD_SIZE][BOARD_SIZE] = {};//intialize all of board to 0s
};

/*
 * Recursively solves the knights tour using brute force
 * Prints any solutions it finds.
 *
 * @param b - the board we’re working with (contains all moves-to-date)
 * @param row   - row we’re going to attempt to place the knight on this move.
 * @param col   - column we’re going to attempt to place the knight on this move.
 * @param currentMoveNum - the move# we’re making (1=first move)
 *
 * @return The number of solutions the given board and move leads to
 */
int solveKnightsTour(Board b, int row, int col, int currentMoveNum);
//Prints the state of the board when currentMoveNum is the area of the board @param b- board
void printBoard(Board b);

int main() {
    Board b;
    int startRow = BOARD_SIZE / 2;
    int startCol = BOARD_SIZE / 2;//middle of board, its 3, so i just plus one for the right number
    int numSolutions;
    
    std::cout << "Welcome to the Knight's Tour solver!\n";
    std::cout << "Board size: " << BOARD_SIZE << std::endl
    << "Starting position (row, col): " << startRow + 1 << "," << startCol + 1 << std::endl;//plus 1 for real middle
    std::cout << std::endl;
    numSolutions = solveKnightsTour(b, startRow, startCol, 1);//start at first move
    std::cout << "Total Solutions: " << numSolutions << std::endl;

    return 1;
}


void printBoard(Board b) {
    for (int i = 0; i < BOARD_SIZE; i++) {//itterate through rows
        for (int j = 0; j < BOARD_SIZE; j++) {//itterate through cols
            std::cout << b.board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int solveKnightsTour(Board b, int row, int col, int currentMoveNum) {
    // Check if row and col are valid
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || b.board[row][col] != 0) {//check if we visted that postion,that would be invalid. or if its off board
        return 0;
    }

    // Place the knight on the board
    b.board[row][col] = currentMoveNum;

    // Check if the board is full
    if (currentMoveNum == BOARD_SIZE * BOARD_SIZE) {
        printBoard(b);
        return 1;//base case
    }

    // Make 8 recursive calls, one for each possible next move
    int totalSolutions = 0;//counts the soultions
    int rowOffsets[] = { -2, -1, 1, 2, 2, 1, -1, -2 };//matches the 8 pairs of moves possible the knight can make
    int colOffsets[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    for (int i = 0; i < 8; i++) {//it goes through each off set to check if it is valid
        int nextRow = row + rowOffsets[i];//calling the same spot in the arrays of offsets matches them up. 
        int nextCol = col + colOffsets[i];
        totalSolutions += solveKnightsTour(b, nextRow, nextCol, currentMoveNum + 1);//returning true gives us a one, so it adds one each time, also add one to the move count
    }//recursivly calling this untill the base case 

    // Remove the knight from the board
    b.board[row][col] = 0;

    //return the sum
    return totalSolutions;
}

