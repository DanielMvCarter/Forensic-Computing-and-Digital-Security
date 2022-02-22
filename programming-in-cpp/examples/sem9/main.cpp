#include <iostream>

const int TILES_WIDE = 4;
const int TILES_HIGH = 4;
const int EMPTY_CELL = 0;
//Create a 2D array of ints to represent the board and init to a fixed

int gBoard[TILES_WIDE][TILES_HIGH] = {{0,2,2,0},{2,0,2,2},{2,2,2,4},
{4,0,0,4}};
// <----------------------------DrawBoard---------------------------->
void drawBoard(int b[TILES_WIDE][TILES_HIGH]) {
    for (size_t x = 0; x < TILES_HIGH; x++) {
         for (size_t y = 0; y < TILES_WIDE; y++) {
            std::cout << "| " << b[x][y] << " |";
        }
        std::cout << '\n';
    }
}

// <---------------------Implement these Functions--------------------->
void mergeLeft(int board[TILES_WIDE][TILES_HIGH]) {
    // For every Row
    for (int row = 0; row < TILES_HIGH; row++) {
        // For one less than every Column
        for (int column = 0; column<TILES_WIDE; column++) {
            // If the current tile is same as the next tile
            if ((board[row][column] == board[row][column-1])&&(board[row][column]!=0)&&(column-1>-1)) {
                //Double the current tile
                board[row][column-1] = board[row][column]*2;
                //Set the next tile to be empty
                board[row][column] = 0; 
            }
        }
    }
}

void packLeft(int board[TILES_WIDE][TILES_HIGH]) {
    //For every Row
    for (int row = 0; row < TILES_HIGH; row++) {
        //For every Column
        for (int column = 0; column<TILES_WIDE; column++) {
            //If the current tile is empty
            if (board[row][column] == 0) {
                //Iterate through the row
                for (int nextColumn = column+1; nextColumn <TILES_WIDE; nextColumn++) {
                    //If the next cell is notEmpty
                    if (board[row][nextColumn] !=0) {
                        //Swap current(empty) tile with the next notEmpty tile
                        board[row][column]= board[row][nextColumn];
                        board[row][nextColumn]=0;
                        break;
                    }
                }
            }
        }
    }
}

void shiftLeft(int board[TILES_WIDE][TILES_HIGH]) {
    packLeft(board);
    mergeLeft(board);
    packLeft(board);
}

void mergeRight(int board[TILES_WIDE][TILES_HIGH]) {
    // For every Row
    for (int row = 0; row < TILES_HIGH; row++) {
        // For one less than every Column
        for (int column = TILES_WIDE; column>0; column--) {
            // If the current tile is same as the next tile
            if ((board[row][column] == board[row][column+1])&&(board[row][column]!=0)&&(column+1<4)) {
                //Double the current tile
                board[row][column+1] = board[row][column]*2;
                //Set the next tile to be empty
                board[row][column] = 0;
            }
        }
    }
}

void packRight(int board[TILES_WIDE][TILES_HIGH]) {
    //For every Row
    for (int row = 0; row < TILES_HIGH; row++) {
        //For every Column
        for (int column = 0; column < TILES_WIDE; column++) {
            //If the current tile is empty
            if (board[row][column] ==0) {
                //Iterate through the row
                for (int nextColumn = 0; nextColumn < TILES_WIDE; nextColumn++) {
                    //If the next cell is notEmpty
                    if (board[row][nextColumn] !=0) {
                        //Swap current(empty) tile with the next notEmpty tile
                        board[row][column]= board[row][nextColumn];
                        board[row][nextColumn]=0;
                        break;
                    }
                }
            }
        }
    }
}

void shiftRight(int board[TILES_WIDE][TILES_HIGH]) {
    packRight(board);
    mergeRight(board);
    packRight(board);
}

void mergeDown(int board[TILES_WIDE][TILES_HIGH]){
    // For every Column
    for (int column = 0; column < TILES_WIDE; column++) {
        // For one less than every Column
        for (int row = TILES_HIGH; row>0; row--) {
            // If the current tile is same as the next tile
            if ((board[row][column] == board[row+1][column])&&(board[row][column]!=0)&&(row+1<4)) {
                //Double the current tile
                board[row+1][column] = board[row][column]*2;
                //Set the next tile to be empty
                board[row][column] = 0;
            }
        }
    }
}

void packDown(int board[TILES_WIDE][TILES_HIGH]) {
    //For every Column
    for (int column = 0; column < TILES_WIDE; column++) {
        //For every row
        for (int row = 0; row < TILES_HIGH; row++) {
            //If the current tile is empty
            if (board[row][column] ==0) {
                //Iterate through the column
                for (int nextRow = 0; nextRow < TILES_HIGH; nextRow++) {
                    //If the next cell is notEmpty
                    if (board[nextRow][column] !=0) {
                        //Swap current(empty) tile with the next notEmpty tile
                        board[row][column]= board[nextRow][column];
                        board[nextRow][column]=0;
                        break;
                    }
                }
            }
        }
    }
}

void shiftDown(int board[TILES_WIDE][TILES_HIGH]) {
    packDown(board);
    mergeDown(board);
    packDown(board);
}

void mergeUp(int board[TILES_WIDE][TILES_HIGH]) {
    // For every Column
    for (int column = 0; column < TILES_HIGH; column++) {
        // For one less than every Row
        for (int row = 0; row<TILES_WIDE; row++) {
            // If the current tile is same as the next tile
            if ((board[row][column] == board[row-1][column])&&(board[row][column]!=0)&&(row-1>-1)) {
                //Double the current tile
                board[row-1][column] = board[row][column]*2;
                //Set the next tile to be empty
                board[row][column] = 0; 
            }
        }
    }
}

void packUp(int board[TILES_WIDE][TILES_HIGH]) {
    //For every Column
    for (int column = 0; column < TILES_HIGH; column++) {
        //For every Row
        for (int row = 0; row<TILES_WIDE; row++) {
            //If the current tile is empty
            if (board[row][column] == 0) {
                //Iterate through the row
                for (int nextRow = row+1; nextRow <TILES_WIDE; nextRow++) {
                    //If the next cell is notEmpty
                    if (board[nextRow][column] !=0) {
                        //Swap current(empty) tile with the next notEmpty tile
                        board[row][column]= board[nextRow][column];
                        board[nextRow][column]=0;
                        break;
                    }
                }
            }
        }
    }
}

void shiftUp(int board[TILES_WIDE][TILES_HIGH]) {
    packUp(board);
    mergeUp(board);
    packUp(board);
}

// <------------------------------MAIN------------------------------->
int main() {
 drawBoard(gBoard);
 shiftUp(gBoard);
 std::cout << "\n\n\n\n";
 drawBoard(gBoard);
 return 0;
}
