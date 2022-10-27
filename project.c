#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * File    : project.c
 * Author  : sandeep,aditya,anadi mishra,harsh vardhan,shivant
 * Date    : 27-Oct-2022
 * Purpose : design of maze game
 *         : An example of eylabyrinth game
*******************************************************************************/

#define MAX_ROW 25
#define MAX_COL 25   
#define LINE_BUFFER 400

int ans[MAX_ROW][MAX_COL];
int var=0, temp=0;
int row=0, col=0;
int mode=0, count=0, run=1, lock=0;
int a, b, type;
FILE *reportfile;


int max(int q,int r){
    if(q>r){
        return q;
    }
    return r;
}
void report(){
    reportfile = fopen("report.txt","w");
        if(reportfile == NULL)
        {
            printf("Error in opening the report file");   
            exit(1);             
        }
    return;
}
void printmaze(){
        printf("\nit's a %d*%d maze\n\n",var,temp) ; 
        
    for(int h=1;h<=var;h++){
    for(int q=1;q<=temp;q++){
        
     printf("%d ",ans[h][q]) ; 
    }
    printf("\n") ; 
   }

   printf("\n") ; 

}
int readMazeCSV(char* fileName)
{
    char buffer[LINE_BUFFER] ;
    char *record,*line;
   
    FILE *fstream = fopen(fileName,"r");
        if(fstream == NULL)
            {
                printf("\n file opening failed ");
                return -1 ;
            }

    row=1;
    col=0;
   
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
        {
            record = strtok(line,",");
            col++;
            
            while(record != NULL)
            {
                ans[row][col] = atoi(record) ;
                record = strtok(NULL,",");
                temp=max(col,temp);
                col++;
            }

            col=0;   
            var=max(row,var);
            row++;
        }

    return 0;
 }
void options(){

        printf("\n1-easy maze\n");
        printf("2-medium maze\n");
        printf("3-hard maze\n");
        printf("9-quit the game and exit\n\n");
        return ;
}
void square(){
        switch (mode)
            {
                case 1:
                if (EXIT_FAILURE ==  readMazeCSV("square easymaze.csv")){
                printf(" easy maze.\n\n");
                }
                    printf("\nU choose easy level , can do better \n");
                    break;

                case 2:
                if (EXIT_FAILURE ==  readMazeCSV("square mediummaze.csv")){
                printf("medium maze.\n\n");
                }
                    printf("\nU choose medium level (keep going:)\n");
                    break;

                case 3:
                if (EXIT_FAILURE ==  readMazeCSV("square hardmaze.csv")){
                printf("hard maze.\n\n");
                }
                    printf("\nu choose hard level wow\n");
                    break;

                case 9:
                EXIT_SUCCESS;

                default:
                break;
            }
}
void rectangle(){
        switch (mode)
            {
                case 1:
                if (EXIT_FAILURE ==  readMazeCSV("rectangle easymaze.csv")){
                printf(" easy maze.\n\n");
                }
                    printf("\nU choose easy level (can do better:)\n");
                    break;

                case 2:
                if (EXIT_FAILURE ==  readMazeCSV("rectangle mediummaze.csv")){
                printf("medium maze.\n\n");
                }
                    printf("\nU choose medium level (keep going:)\n");
                    break;

                case 3:
                if (EXIT_FAILURE ==  readMazeCSV("rectangle hardmaze.csv")){
                printf("hard maze.\n\n");
                }
                    printf("\nU choose hardmaze level (keep it up:)\n");
                    break;

                case 9:
                EXIT_SUCCESS;

                default:
                break;
            }
}
void readfile(){
        switch (type)
            {
            case 1:
            square();
            break;

            case 2:
            rectangle();
            break;

            default:
            break;
            }
    return;
}
void score(){
    if(a==var&&b==temp&&lock==0){
        printf("u have used %d number of moves to complete the game\n",count);
        }
    else{
        printf("u exitted out of the game - no score\n");
        }
}
void win(){
    if(a==var&&b==temp&&lock==0){
        printf("u have reached the end block but u dont have any key. go back and collect the key \n");
        }
    else if(a==var&&b==temp&&lock==1){
        printf("congo u have won the game\n");
        exit(1);
        }
    return;
}
void hint(){
    printmaze();
}
void showdirections(){
    printf("0-top\n");
    printf("1-bottom\n");
    printf("2-left\n");
    printf("3-right\n");
    printf("4-exit\n");
    printf("5-hint\n\n");
}
void printdirections(){
    
    printf("\nu have the following ways\n");
    printf("\n");
    printf("  ");
        if(ans[a][b]%2==0){
            printf("   ^ ");
        }
        else{
        printf("   o ");
        }

    printf("  \n");
    printf("\n");
    printf("     O\n");

        if(ans[a][b]%5==0){
            printf("< ");
        }
        else{
            printf("o ");
        }

    printf("  /");
    printf("|");
    printf("\\  ");

        if(ans[a][b]%7==0){
        printf(" >\n");
        }
        else{
        printf(" o\n");
        }

    printf("  ");
    printf("  /");
    printf("|");
    printf("\\  ");

    printf("\n");
    printf("\n");
    printf("  ");
        if(ans[a][b]%3==0){
        printf("   V \n");
        }
        else{
        printf("   o \n");
        }

    printf("\nenter the direction u want to move :: \n");
    return;
}
void key(){
    
    if(ans[a][b]%13==0&&lock==0){
        printf("u have got the key");
        lock=1;
    }
    return;
}
void bombsuggest(){
    int run=ans[a][b];
        if(run%19==0){
        printf("\ncautious !!!!! bomb a head");
        }
    return;
}
void dead(){
    if(ans[a][b]%11==0){
        printf("\nU have touched the bomb - u failed the game");
        exit(0);
    }
}
void move(){
    int choice;
    scanf("%d",&choice);

    int x=a;
    int y=b;
    int value=ans[x][y];
    
    switch (choice)
        {
        case 0:
            if(value%2==0){
            x=x-1;
            }
            else{
                printf("invalid move");
            }
        break;

        case 1:
            if(value%3==0){
            x=x+1; 
            }
            else{
                printf("invalid move");
            }
        break;

        case 2:
            if(value%5==0){
            y=y-1;
            }
            else{
                printf("invalid move");
            }
        break;

        case 3:
            if(value%7==0){
            y=y+1;
            }
            else{
                printf("invalid move");
            }
        break;

        case 4:
            exit(1);
        

        case 5:
            hint();
            printf("use this hint to go further\n");
        break;

        default:
                printf("wrong choice\n");
        break;
}
        a=x;
        b=y; 
        return ;
}
void mazetype(){

        printf("choose the mazetype u want to play");
        printf("\nsquare maze - 1\n");
        printf("rectangular maze - 2\n");
        scanf("%d",&type);

    switch (type)
        {
        case 1:
            printf("\nu choose square maze");
        break;

        case 2:
            printf("\nu choose rectangular maze");
        break;

        default:
            printf("invalid input");
            mazetype();
            break;
        }
}
void rungame(){
    a=1;
    b=1;

    while(1){
        printf("\nu r currently at position of %d,%d",a,b);

        key();
        bombsuggest();
        printdirections();
        showdirections();
        move();
        dead();
        win();
        printf("   \n\n\n     ---------    \n\n    ");
        count++;
       }

}
int main()
{
       report();
       mazetype();
       options();
       printf("\nenter the level u want to play \n");
       fprintf(reportfile, "\nenter the level u want to play \n");
       scanf("%d",&mode);
       readfile();
       printmaze();
       rungame();
       score();
       fclose(reportfile);
       return 0;
}