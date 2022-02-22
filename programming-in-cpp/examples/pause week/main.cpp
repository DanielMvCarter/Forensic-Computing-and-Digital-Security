//Win condition for horizontal X
void horizontalXWin(){
    if ((Board[0][0]== 'x'&&(Board[0][1]== 'x' &&(Board[0][2]== 'x')||(Board[1][0]== 'x'&&(Board[1][1]== 'x' &&(Board[1][2]== 'x')||(Board[2][0]== 'x'&&(Board[2][1]== 'x' &&(Board[2][2]== 'x')){
        cout << "Crosses win\n";
        return;
    }
}
//Win condition for horizontal o
void horizontalOWin(){
    if ((Board[0][0]== 'o'&&(Board[0][1]== 'o' &&(Board[0][2]== 'o')||(Board[1][0]== 'o'&&(Board[1][1]== 'o' &&(Board[1][2]== 'o')||(Board[2][0]== 'o'&&(Board[2][1]== 'o' &&(Board[2][2]== 'o')){
        cout << "Naughts win\n";
        return;
    }
}
//Win condition for vertical X
void verticalXWin(){
    if ((Board[0][0]== 'x'&&(Board[1][0]== 'x' &&(Board[2][0]== 'x')||(Board[0][1]== 'x'&&(Board[1][1]== 'x' &&(Board[2][1]== 'x')||(Board[0][2]== 'x'&&(Board[1][2]== 'x' &&(Board[2][2]== 'x')){
        cout << "Crosses win\n";
        return;
    }
}
//Win condition for vertical o
void verticalOWin(){
    if ((Board[0][0]== 'o'&&(Board[1][0]== 'o' &&(Board[2][0]== 'o')||(Board[0][1]== 'o'&&(Board[1][1]== 'o' &&(Board[2][1]== 'o')||(Board[0][2]== 'o'&&(Board[1][2]== 'o' &&(Board[2][2]== 'o')){
        cout << "Crosses win\n";
        return;
    }
}
//Win condition for diagonal X
void diagonalXWin(){
    if ((Board[0][0]== 'x'&&(Board[1][1]== 'x' &&(Board[2][2]== 'x')||(Board[0][2]== 'x'&&(Board[1][1]== 'x' &&(Board[2][0]== 'x')){
        cout << "Crosses win\n";
        return;
    }
}
//Win condition for diagonal o
void diagonalOWin(){
    if ((Board[0][0]== 'o'&&(Board[1][1]== 'o' &&(Board[2][2]== 'o')||(Board[0][2]== 'o'&&(Board[1][1]== 'o' &&(Board[2][0]== 'o')){
        cout << "Crosses win\n";
        return;
    }
}