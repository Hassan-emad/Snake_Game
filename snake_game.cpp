#include "graphics.h"
#include<queue>
#include <ctime>
using namespace std;

const int EMPTY=0;
const int BODY=1;
const int APPLE=2;
const int WALL=3;
int score = 0;

enum Directions{UP,DOWN,LEFT,RIGHT};
Directions snakeDirection = DOWN;
bool isGameEnd = false;


struct Location{
    int row;
    int col;
};

bool isFireStarted;
Location fireLocation;
Directions fireDirection;

queue<Location> snakeBody;

int board[35][35]={
{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
};

void drawWelcomeScreen() {
    cleardevice(); 
    setcolor(WHITE);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    char buffer1[] = "Welcome to Snake Game!";
    outtextxy(getmaxx() / 2, getmaxy() / 2 - 50,buffer1);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    char buffer2[] = "Press any key to start...";
    outtextxy(getmaxx() / 2, getmaxy() / 2 +50, buffer2);
    getch();
}

void clearWelcomeScreen() 
{
    cleardevice();
}

void drawGate(int row,int col)
{
    int x = col*18 ,y = row*18;
    setfillstyle(SOLID_FILL , BLACK);
    bar(x , y , x+18 , y+18);
}

void drawFire(int row,int col)
{
    int x = col*18 ,y = row*18;

    setfillstyle(SOLID_FILL , LIGHTCYAN);
    if(board[row][col] == APPLE || board[row][col] == BODY)
    return;
    if(board[row][col]==WALL)
    {
        board[row][col]=EMPTY , drawGate(row,col);
        if(row==34)
        board[0][col]=EMPTY , drawGate(0,col);
        else if(row==0)
        board[34][col]=EMPTY  , drawGate(34,col);
        
        else if(col==34)
        board[row][0]=EMPTY , drawGate(row,0);
        else if(col==0)
        board[row][34]=EMPTY  , drawGate(row,34);
        return;
    }
    else
    bar(x+2 , y+2 , x+15 , y+15);
}

void eraseFire(int row,int col)
{
    int x = col*18 ,y = row*18;
    setfillstyle(SOLID_FILL , BLACK);
    if(board[row][col] == APPLE || board[row][col] == BODY)
    return;
    bar(x , y , x+18 , y+18);
}

void eraseSnakeBody(int row,int col)
{
    int x = col*18 ,y = row*18;

    setfillstyle(SOLID_FILL , BLACK);
    bar(x , y , x+18 , y+18);

}

void drawSnakeBody(int row,int col)
{
    int x = col*18 ,y = row*18;

    setfillstyle(SOLID_FILL , LIGHTBLUE);
    bar(x+1 , y+1 , x+17 , y+17);

}

void drawApple(int row,int col)
{
    int x = col*18 ,y = row*18;

    readimagefile( "anapple.ico" , x+1 ,y+1 ,x+16 ,y+16);

}

void drawWall(int row,int col)
{
    int x = col*18 ,y = row*18;
    setfillstyle(SOLID_FILL , LIGHTRED);
    bar(x , y , x+18 , y+18);

    setcolor(BLACK);
    setlinestyle(SOLID_LINE,1,NORM_WIDTH);
    line(x+0 , y+0 , x+18 ,y+0);
    line(x+0 , y+9 , x+18 ,y+9);
    line(x+0 , y+18 , x+18 ,y+18);
    
    line(x+12 , y+0 , x+12 ,y+9);
    line(x+6 , y+9 , x+6 ,y+18);

}


void drawBoard()
{
    for(int row=0 ;row<35 ;row++)
    for(int col=0;col<35;col++)
    {
        switch(board[row][col])
        {
            case EMPTY:
            break;
            case BODY:
            drawSnakeBody(row,col);
            break;
            case APPLE:
            drawApple(row,col);
            break;
            case WALL:
            drawWall(row,col);
            break;
        }
    }

}

void initSnake()
{
    Location loc;
    loc.row =2;
    loc.col = 10;

    for(int i=0 ; i<=4 ;i++)
    {
        snakeBody.push(loc);
        board[loc.row][loc.col]=1;
        loc.row +=1;
    }
}

Location getNextFire()
{
    Location nextFireLoc = fireLocation;
    switch(fireDirection)
    {
        case UP:
        nextFireLoc.row -=1; break;
        case DOWN:
        nextFireLoc.row +=1; break;
        case LEFT:
        nextFireLoc.col -=1; break;
        case RIGHT:
        nextFireLoc.col +=1; break;
    }
    return nextFireLoc;
}

Location getNextHead()
{
    Location head = snakeBody.back();
    switch(snakeDirection)
    {
        case UP:
        head.row -=1;
        if(head.row <0) head.row = 34; 
        break;
        case DOWN:
        head.row +=1;
        if(head.row >34) head.row = 0;
        break;
        case LEFT:
        head.col -=1;
        if(head.col <0) head.col = 34;
        break;
        case RIGHT:
        head.col +=1;
        if(head.col >34) head.col = 0;
        break;
    }
    return head;
}

void generateNextApple()
{
    int row ,col;
    do
    {
        row = rand()%35;
        col = rand()%35;
    }while(board[row][col] !=EMPTY);

    board[row][col] =APPLE;
    drawApple(row,col);
}

void moveSnakeToNextLocation(Location nextHead)
{
    snakeBody.push(nextHead);
    drawSnakeBody(nextHead.row ,nextHead.col);
    board[nextHead.row][nextHead.col]=1;

    Location tail = snakeBody.front();
    snakeBody.pop();
    eraseSnakeBody(tail.row , tail.col);
    board[tail.row][tail.col]=0;
}

void moveAndGrowSnake(Location nextHead)
{
    snakeBody.push(nextHead);
    drawSnakeBody(nextHead.row ,nextHead.col);
    board[nextHead.row][nextHead.col]=1;
}

void gameOver()
{
    isGameEnd = true;
    PlaySound(TEXT("game_over.wav"), NULL, SND_ASYNC);
    setcolor(WHITE);
    settextjustify(CENTER_TEXT , CENTER_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR ,4);
    char buffer[] = "Game Over";
    outtextxy(getmaxx()/2 , getmaxy()/2 , buffer);
    
    settextstyle(TRIPLEX_FONT,HORIZ_DIR ,2);
    char scoreBuffer[20];
    sprintf(scoreBuffer, "Your Score: %d", score);
    outtextxy(getmaxx()/2 , getmaxy()/2 + 50 , scoreBuffer);
}


void moveSnake()
{
    Location nextHead = getNextHead();
    switch(board[nextHead.row][nextHead.col])
    {
        case EMPTY: moveSnakeToNextLocation(nextHead); break;
        case APPLE:
        PlaySound(TEXT("eat_apple.wav"), NULL, SND_ASYNC);
        moveAndGrowSnake(nextHead);
        generateNextApple();
        score += 10;
        break;
        case WALL:case BODY: gameOver(); break;
    }
}

void changeSnakeDirection(char ch)
{
    switch(ch)
    {
        case KEY_UP:
        if(snakeDirection == DOWN)
        return;
        else
        {
            snakeDirection = UP;
            break;
        }
        
        case KEY_DOWN:
        if(snakeDirection == UP)
        return;
        else
        {
            snakeDirection = DOWN;
            break;
        }
        
        case KEY_LEFT:
        if(snakeDirection == RIGHT)
        return;
        else
        {
            snakeDirection = LEFT;
            break;
        }
        
        case KEY_RIGHT:
        if(snakeDirection == LEFT)
        return;
        else
        {
            snakeDirection = RIGHT;
            break;
        }
    }
}


void startFire()
{
    isFireStarted = true;
    fireLocation = getNextHead();
    fireDirection = snakeDirection;
    drawFire(fireLocation.row , fireLocation.col);
    PlaySound(TEXT("fire_sound.wav"), NULL, SND_ASYNC);
}

void stopFire()
{
    isFireStarted = false;
    eraseFire(fireLocation.row , fireLocation.col);
}

void moveFire()
{
    if(isFireStarted)
    {
        Location nextFireLoc = getNextFire();
        
        if(nextFireLoc.row > 35 || nextFireLoc.row < 0 || nextFireLoc.col > 35 || nextFireLoc.col < 0)
        {
            stopFire();
            return;
        }

        drawFire(nextFireLoc.row ,nextFireLoc.col);
        eraseFire(fireLocation.row , fireLocation.col);
        fireLocation = nextFireLoc;
    }
}

void checkKeyInput()
{
    char ch;
    if(kbhit())
    {
        ch = getch();

        if(ch ==0)
        {
            ch = getch();
            changeSnakeDirection(ch);
        }
        else if(ch == 32)
        {
            if(!isFireStarted)
            startFire();
        }
    }
}

void drawScore()
{
    setcolor(WHITE);
    settextjustify(LEFT_TEXT , TOP_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR ,2);
    char scoreBuffer[20];
    sprintf(scoreBuffer, "Score: %d", score);
    outtextxy(10, 10, scoreBuffer);
}

int main()
{
    
    isGameEnd= false;
    initwindow(630,630 , "Snake Game");

    drawWelcomeScreen();
        
    clearWelcomeScreen();
    initSnake();
    drawBoard();
    moveSnake();
    int gametimer =0;

    while(!isGameEnd)
    {
        if(gametimer == INT_MAX)
        gametimer =0;

        if(gametimer%1000000 ==0)
        moveFire();
        if(gametimer%6000000 ==0)
        {
            moveSnake();
            
            drawScore();
        }
        
        gametimer++;

        checkKeyInput();
    }

    while(!kbhit());
    return 0;
}