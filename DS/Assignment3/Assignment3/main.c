#include <stdio.h>
#include <stdlib.h>

struct nodetype{
    char game_state[3][3];
    int EP;
};

typedef struct nodetype EP_node;

// Check if the character 'ch' is the winner
int check_win_state(char g_state[][3],char ch){
    int i=0;

    for(i=0;i<3;i++)
        if(g_state[i][0]==ch && g_state[i][1]==ch && g_state[i][2]==ch)
            return 1;

    for(i=0;i<3;i++)
        if(g_state[0][i]==ch && g_state[1][i]==ch && g_state[2][i]==ch)
            return 1;

    if(g_state[0][2]==ch && g_state[1][1]==ch && g_state[2][0]==ch)
       return 1;

    if(g_state[0][0]==ch && g_state[1][1]==ch && g_state[2][2]==ch)
        return 1;

    return 0;
}

// Function to find the evaluation function of a particular configuration of game state

int find_eval_func(char g_state[][3],char ch){
    int i=0;
    int count=0;

    if(check_win_state(g_state,ch))
        return 8;

    for(i=0;i<3;i++)
        if((g_state[i][0]=='X'||g_state[i][1]=='X'||g_state[i][2]=='X')&&!(g_state[i][0]=='O'||g_state[i][1]=='O'||g_state[i][2]=='O'))
            count++;

    for(i=0;i<3;i++)
        if((g_state[0][i]=='X'||g_state[1][i]=='X'||g_state[2][i]=='X')&&!(g_state[0][i]=='O'||g_state[1][i]=='O'||g_state[2][i]=='O'))
            count++;

    if((g_state[0][2]=='X'||g_state[1][1]=='X'||g_state[2][0]=='X')&&!(g_state[0][2]=='O'||g_state[1][1]=='O'||g_state[2][0]=='O'))
        count++;

    if((g_state[0][0]=='X'||g_state[1][1]=='X'||g_state[2][2]=='X')&&!(g_state[0][0]=='O'||g_state[1][1]=='O'||g_state[2][2]=='O'))
        count++;


    for(i=0;i<3;i++)
        if((g_state[i][0]=='O'||g_state[i][1]=='O'||g_state[i][2]=='O')&&!(g_state[i][0]=='X'||g_state[i][1]=='X'||g_state[i][2]=='X'))
            count--;

    for(i=0;i<3;i++)
        if((g_state[0][i]=='O'||g_state[1][i]=='O'||g_state[2][i]=='O')&&!(g_state[0][i]=='X'||g_state[1][i]=='X'||g_state[2][i]=='X'))
            count--;

    if((g_state[0][2]=='O'||g_state[1][1]=='O'||g_state[2][0]=='O')&&!(g_state[0][2]=='X'||g_state[1][1]=='X'||g_state[2][0]=='X'))
        count--;

    if((g_state[0][0]=='O'||g_state[1][1]=='O'||g_state[2][2]=='O')&&!(g_state[0][0]=='X'||g_state[1][1]=='X'||g_state[2][2]=='X'))
        count--;

    if(ch=='X')
        return count;

    return count*(-1);
}


// Printing the game state
void print_game_state(char g_state[][3]){
    int i=0,j=0;

    for(i=0;i<3;i++){
        for(j=0;j<3;j++)
            printf(" %c",g_state[i][j]);

        printf("\n");
    }
    //return 0;
}
// Check if the two game state g_state are equal
int isEqual(char g_state1[][3],char g_state2[][3]){
    int i=0,j=0;

    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(g_state1[i][j]!=g_state2[i][j])
                return 0;

    return 1;
}

EP_node find_next_move(char(*)[3],int,char,char,char,int);
int isMovesLeft(char(*)[3]);

int main(){
    char choice=0;
    char g_state[3][3]={{'-','-','-'},{'-','-','-'},{'-','-','-'}};
    int i=0,j=0;
    int turn=4;
    char flag='p';
    EP_node p;
    int row,col,depth;
    char temp;

    printf("Enter the look-ahead value (2 or 4):");
    scanf("%d",&depth);
    while(!(depth==2||depth==4))
    {
    	printf("Invalid Input!\n");
    	printf("Enter the look-ahead value (2 or 4):");
    	scanf("%d",&depth);
    }

    printf("\nX:Player 1\nO:Player 2\n");
    printf("Enter the player whose turn is (Choose either X or O): ");
    scanf(" %c",&choice);
    printf("Entered value: %c\n",choice);

    if(choice!='X'&&choice!='O'){
        printf("Invalid Input. Please enter either X or O.\n");
        return 0;
    }

    printf("\nInput board position (For blank spaces use character '-'):\n");
    for(i=0;i<3;i++)
        for(j=0;j<3;j++){
            printf("Matrix[%d][%d]: ",i+1,j+1);
            scanf(" %c",&temp);

            while(temp!='X' && temp!='O' && temp!='-'){
                printf("\nPlease enter X, O or -\n");
                printf("Value at Position[%d][%d]: ",i+1,j+1);
                scanf(" %c",&temp);
            }
            g_state[i][j]=temp;
        }

    printf("\nStatus of the game:\n");
    print_game_state(g_state);

    if(check_win_state(g_state,'X'))
        printf("\nIn the given state, X is already a winner\n");

    if(check_win_state(g_state,'O'))
        printf("\nIn the given state, O is already a winner\n");

    while(!(check_win_state(g_state,'X')) && !(check_win_state(g_state,'O')) && isMovesLeft(g_state)){

        p=find_next_move(g_state,turn,choice,flag,choice,depth);

        if(isEqual(g_state,p.game_state)){
            if(choice=='X')
                printf("\nIn the given state, O is already a winner\n");
            else
                printf("\nIn the given state, X is already a winner\n");

            return 0;
        }

        printf("\nNext best move for the player %c:\n",choice);
        print_game_state(p.game_state);

        if(check_win_state(p.game_state,'X')){
            printf("\nX is the winner\n");
            return 0;
        }

        if(check_win_state(p.game_state,'O')){
            printf("\nO is the winner\n");
            return 0;
        }

        if(!(isMovesLeft(p.game_state))){
            printf("\nMatch Drawn\n");
            return 0;
        }

        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                g_state[i][j]=p.game_state[i][j];

        if(choice=='X')
            choice='O';
        else
            choice='X';

        while(1){
            printf("Please enter the move (in index 1,2,3) of player %c:\n",choice);
            printf("\nHorizontal game state value index: ");
            scanf(" %d",&row);
            printf("Vertical game state value index: ");
            scanf(" %d",&col);
            printf("Entered horizontal index and vertical index: %d, %d\n",row,col);

            if(g_state[row-1][col-1]!='-')
                printf("\nA previous value can't be changed and the input should be valid index\n");
            else
                break;
        }

        g_state[row-1][col-1]=choice;

        if(choice=='X')
            choice='O';
        else
            choice='X';
    }

    if(!(isMovesLeft(g_state))){
        printf("\nMatch Drawn\n");
        return 0;
    }

    return 0;
}

int isMovesLeft(char g_state[][3]){
    int i=0,j=0;

    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(g_state[i][j]=='-')
                return 1;
    return 0;
}

EP_node find_next_move(char g_state[][3],int turn,char ch,char flag,char start_ch,int depth){
    int i=0,j=0,k=0,l=0,EPmax=-8,EPmin=8,EP=0;
    char next_flag=' ';
    struct nodetype p,p_end;
    char opponent=' ';

    for(k=0;k<3;k++)
        for(l=0;l<3;l++)
            p.game_state[k][l]=g_state[k][l];

    for(k=0;k<3;k++)
        for(l=0;l<3;l++)
            p_end.game_state[k][l]=g_state[k][l];

    if(check_win_state(g_state,start_ch)){
        if(flag=='n'){
            p.EP=8;

            for(k=0;k<3;k++)
                for(l=0;l<3;l++)
                    p.game_state[k][l]=g_state[k][l];

            return p;

        }
    }

    if(start_ch=='X')
        opponent='O';
    else
        opponent='X';

    if(check_win_state(g_state,opponent)){
        if(flag=='p'){
            p.EP=-8;

            for(k=0;k<3;k++)
                for(l=0;l<3;l++)
                    p.game_state[k][l]=g_state[k][l];

            return p;
        }
    }

    if(!(isMovesLeft(g_state))){
        p.EP=0;

        for(k=0;k<3;k++)
            for(l=0;l<3;l++)
                p.game_state[k][l]=g_state[k][l];

        return p;
    }

    if(turn==1||depth==1){
        for(i=0;i<3;i++)
            for(j=0;j<3;j++){
                if(g_state[i][j]=='-'){
                    g_state[i][j]=ch;

                    EP=find_eval_func(g_state,start_ch);

                    if(flag=='p'){
                        if(EPmax<EP){
                            EPmax=EP;

                            for(k=0;k<3;k++)
                                for(l=0;l<3;l++)
                                    p.game_state[k][l]=g_state[k][l];
                        }
                    }
                    else{
                        if(EPmin>EP){
                            EPmin=EP;

                            for(k=0;k<3;k++)
                                for(l=0;l<3;l++)
                                    p.game_state[k][l]=g_state[k][l];
                        }
                    }

                    g_state[i][j]='-';
                }
            }

        if(flag=='p')
            p.EP=EPmax;
        else
            p.EP=EPmin;

        return p;
    }

    for(i=0;i<3;i++)
        for(j=0;j<3;j++){
            if(g_state[i][j]=='-'){
                g_state[i][j]=ch;


                if(flag=='p')
                    next_flag='n';
                else
                    next_flag='p';

                if(ch=='X')
                    p=find_next_move(g_state,turn-1,'O',next_flag,start_ch,depth-1);
                else
                    p=find_next_move(g_state,turn-1,'X',next_flag,start_ch,depth-1);


                if(flag=='p'){
                    if(EPmax<p.EP){
                        EPmax=p.EP;

                        for(k=0;k<3;k++)
                            for(l=0;l<3;l++)
                                p_end.game_state[k][l]=g_state[k][l];
                    }
                }
                else{
                    if(EPmin>p.EP){
                        EPmin=p.EP;

                        for(k=0;k<3;k++)
                            for(l=0;l<3;l++)
                                p_end.game_state[k][l]=g_state[k][l];
                    }
                }


                g_state[i][j]='-';
            }
        }

    if(flag=='p')
        p_end.EP=EPmax;
    else
        p_end.EP=EPmin;

    return p_end;
}

