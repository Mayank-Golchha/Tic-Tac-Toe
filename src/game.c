#include <stdio.h>

void PrintGame(char arr[][3]){
    for (int i = 0;i<3;i++){
        for (int j = 0;j<3;j++){
            printf("%c ",arr[i][j]);
        }
        printf("\n");
    }
}

void Set(char arr[][3], char elem, int row, int col) {
    arr[row][col] = elem;
}

void Copy(char src[][3], char dest[][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            dest[i][j] = src[i][j];
}

int Win(char arr[][3],char elem){
    int w = 0;
    for (int i = 0;i<3;i++){
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] == elem) w++;
    }
    for (int i = 0;i<3;i++){
        if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] == elem) w++;
    }

    if (arr[0][0] == arr[1][1] && arr[2][2] == arr[1][1] && arr[0][0] == elem) w++;

    if (arr[0][2] == arr[1][1] && arr[2][0] == arr[1][1] && arr[0][2] == elem) w++;


    return w;
}
int Together(char arr[][3],char elem){
    int count = 0;
    for (int i = 0;i<3;i++){
        for (int j = 0;j<3;j++){
            if (arr[i][j] == '.'){
                char new_arr[3][3];
                int w = 0,w1 = 0;
                Copy(arr,new_arr);
                // Set(new_arr,elem,3*i+j);
                Set(new_arr,elem,i,j);
                w = Win(arr,elem);
                w1 = Win(new_arr,elem);
                if (w1 > w) count++;
            }
        }
    }
    return count;
}

char swap(char elem){
    char new_elem = (elem == 'X')?'O':'X';
    return new_elem;
}

int empty(char arr[][3]){
    int c = 0;
    for (int i = 0;i<3;i++){
        for (int j = 0;j<3;j++){
            if (arr[i][j] == '.') c++;
        }
    }
    return c;
}


int Evaluation(char arr[][3],char elem){
    int eval = 0;
    int c = 0;

    int e = empty(arr);
    if (e == 0) return -70;

    if (Win(arr,elem)) return 100;
    else if (Win(arr,swap(elem))) return -100;

    //corners
    if (arr[1][1] != '.'){
        if (arr[1][1] == elem) eval += 3;
        else eval -= 3;
        c++;
    }

    if (arr[0][0] != '.'){
        if (arr[0][0] == elem) eval += 1;
        else eval -= 1;
        c++;
    }
    if (arr[0][2] != '.'){
        if (arr[0][2] == elem) eval += 1;
        else eval -= 1;
        c++;
    }

    if (arr[2][0] != '.'){
        if (arr[2][0] == elem) eval += 1;
        else eval -= 1;
        c++;
    }

    if (arr[2][2] != '.'){
        if (arr[2][2] == elem) eval += 1;
        else eval -= 1;
        c++;
    }

    //middles
    if (arr[0][1] != '.'){
        if (arr[0][1] == elem) eval += 0.5;
        else eval -= 0.5;
        c++;
    }

    if (arr[1][0] != '.'){
        if (arr[1][0] == elem) eval += 0.5;
        else eval -= 0.5;
        c++;
    }
    if (arr[1][2] != '.'){
        if (arr[1][2] == elem) eval += 0.5;
        else eval -= 0.5;
        c++;
    }

    if (arr[2][1] != '.'){
        if (arr[2][1] == elem) eval += 0.5;
        else eval -= 0.5;
        c++;
    }

    eval += (Together(arr,elem) - Together(arr,swap(elem)))*3;

    return eval;
}

int Best_Move(char arr[][3],int o_turn,int turn,int depth){
    int elem = (turn == 0)?'X':'O';
    if (depth == 0){
        if (o_turn == turn){
            return Evaluation(arr,elem);
        }
        else return -Evaluation(arr,elem);
    }
    //moves
    if (turn == o_turn){
        int max_e = -100;

        for (int i = 0;i<3;i++){
            for (int j = 0;j<3;j++){
                if (arr[i][j] == '.'){
                    char new_board[3][3];
                    Copy(arr,new_board);
                    // Set(new_board,elem,3*i+j);
                    Set(new_board,elem,i,j);
                    if (Win(new_board,elem)) return 10000;
                    int m = Best_Move(new_board,o_turn,(turn+1)%2,depth-1);
                    max_e = (max_e<m)?m:max_e;
                }
            }
        }
        return max_e;
    }
    else {
        int min_e = 100;

        for (int i = 0;i<3;i++){
            for (int j = 0;j<3;j++){
                if (arr[i][j] == '.'){
                    char new_board[3][3];
                    Copy(arr,new_board);
                    Set(new_board,elem,i,j);
                    if (Win(new_board,elem)) return -10000;
                    int m = Best_Move(new_board,o_turn,(turn+1)%2,depth-1);
                    min_e = (min_e < m)?min_e:m;
                }
            }
        }
        return min_e;
    }

}



int Top_Move(char arr[][3],int o_turn,int turn,int depth){
    int elem = (turn == 0)?'X':'O';
    int max_eval = -1000;
    int b_move = 0;

    for (int i = 0;i<3;i++){
        for (int j = 0;j<3;j++){
            if (arr[i][j] == '.'){
                char new_board[3][3];
                Copy(arr,new_board);
                Set(new_board,elem,i,j);
                if (Win(new_board,elem)) return 3*i+j;
                int eval = Best_Move(new_board,o_turn,(turn+1)%2,depth-1);
                if (eval > max_eval){
                    max_eval = eval;
                    b_move = 3*i+j;
                }
            }
        }
    }
    return b_move;
}


void Game(){
    char board[3][3] = {{'.' , '.' , '.'},
                        {'.' , '.' , '.'},
                        {'.' , '.' , '.'},
                        };
    char player = 'X';
    int turn = 0;
    printf("Player 1 (X/O) : ");
    scanf("%c",&player);
    printf("\nPlayer 2 will be : %c\n",swap(player));

    int e_turn = 0,depth = 4,full=0,win=0;

    if (player == 'X'){
        e_turn = 1;
    }
    else {
        e_turn = 0;
    }

    while (!win && (full != 9)){
        int index = 0;
        full++;
        if (turn != e_turn){
            printf("\nPlayer %d move (x y): ",turn+1);
            int x = 0,y = 0;
            scanf("%d",&x);
            scanf("%d",&y);
            index = y*3+x;
        }
        else {
            index = Top_Move(board,turn,turn,depth);
        }

        Set(board,player,index/3,index%3);

        win = Win(board,player);
        PrintGame(board);

        if (win){
            printf("Player %d wins the game",turn+1);
            break;
        }
        if (full == 9){
            printf("Draw !!");
            break;
        }
        player = swap(player);
        turn++;
        turn = turn%2;
        printf("\n");
    }
}


int main(){
    char board[3][3] = {{'O' , 'X' , '.'},
                        {'.' , 'X' , 'O'},
                        {'.' , 'X' , 'O'},
                        };
    Game();

}
