#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//there are smarter methods to get terminal window size, i hard corded for speed
int width = 210;
int height = 50;

void gotoxy( short x, short y )
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;

    SetConsoleCursorPosition( hStdout, position ) ;
}

struct Point
{
	int x, y;
};

struct Point newPoint(int a, int b)
{
	struct Point p;
	p.x = a;
	p.y = b;
	return p;
}

struct List
{
	struct List *next;
	struct Point p;
} *SnakeFront = NULL, *SnakeEnd = NULL;

void push_front(struct Point P)
{
	gotoxy(P.x, P.y);
	printf("#");

	struct List *temp = (struct List *)malloc(sizeof(struct List));
	temp->p = newPoint(P.x, P.y);
	temp->next = NULL;

	//add P to front of list
	if (SnakeFront == NULL)
    {
		SnakeFront = SnakeEnd = temp;
	}
	else
	{
		temp->next = SnakeFront;
		SnakeFront = temp;
	}
}

void pop_back()
{
	gotoxy(SnakeEnd->p.x, SnakeEnd->p.y);
	printf(" ");

	struct List *temp = SnakeFront;
	//remove last element from list
	while(temp->next->next != NULL) temp = temp->next;
	SnakeEnd = temp;
	SnakeEnd->next = NULL;
}

struct Point createApple()
{
	//generate random (x, y) position
	int x = rand()%width;
	int y = rand()%height;
	while(1)
    {
		int inList = 0;
		struct List *temp = SnakeFront;
		while(temp != NULL)
		{
			if (temp->p.x == x && temp->p.y == y)
            {
				inList = 1;
				break;
			}
			temp = temp->next;
		}

		if (inList == 0) break;
	}
	gotoxy(x, y);
	printf("*");
	return newPoint(x, y);
	//check if that (x, y) lies in Snake body list
	//if it doesn't, Print something at (x, y) and return the position
	//else choose another random (x, y) and repeat
}

int checkHeadAtApple(struct Point P)
{
	return (P.x == SnakeFront->p.x && P.y == SnakeFront->p.y);
}

struct Point front()
{
	return SnakeFront->p;
}

void scoreboards()
{
    FILE *f;
    int i;
    char ch;
    f=fopen("yourscore.txt","r");
    if(f==NULL)
    {
        exit(0);
    }
    system("cls");
    for(i=0;i<118;i++)
    {
        printf("-");
    }
    printf("\n");
    printf("Welcome to the leaderboard:\n");
    while(!feof(f))
    {
        ch=fgetc(f);
        printf("%c",ch);
    }
    printf("\n");
    for(i=0;i<118;i++)
    {
        printf("-");
    }
fclose(f);
getch();
}

void rules()
{
    printf("\t\t\tRules:\n");
    printf("\t\t\t1. One game one life, so play wisely.\n");
    printf("\t\t\t2. You will lose as soon as the snake tries to eat the wall.\n");
    printf("\t\t\t3. Eat as much as you can and get fat :p.\n");
}

void buffer()
{
int i,j;
printf("\t\t\t\tLoading...");
for(i=0;i<1000000000;i++){}//delay loop
printf("\n\t\t\t\t#");
for(j=0;j<10;j++)
{
for(i=0;i<100000000;i++){}//delay loop
printf("#");
}
printf("\n");
}

void result(char name[50],int r)
{
    time_t t;
    time(&t);
    FILE *f;
    setcolor(10);
    f=fopen("yourscore.txt","a+");
    system("cls");
    printf("\n\nPlease wait while we set our database for your computer!!");
    printf("Process completed press any key to continue!!\n");
    getch();

    printf("\n\n\t\tYOU LOSE\n");
    printf("\t\tBETTER LUCK NEXT TIME!!\n");
    printf("\t\t* Name:%s\n",name);
    printf("\t\t* Score:%d\n\n",r);
    printf("\t\tThe game was played at:%s\n",ctime(&t));
    fprintf(f,"NAME:%s",name);
    fprintf(f,"\t");
    fprintf(f,"SCORE:%d",r);
    fprintf(f,"\t");
    fprintf(f,"\tThe game was played at:%s",ctime(&t));
    fprintf(f,"\n\n");
    fclose(f);
    printf("GAME OVER. GG.");
    buffer1();
}

void buffer1()
{
    int i,j;
for(i=0;i<1000000000;i++){}//delay loop
for(j=0;j<10;j++)
{
for(i=0;i<100000000;i++){}//delay loop
}
}

void setcolor(int ForgC)
{ WORD wColor;
HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
{
	wColor=(csbi.wAttributes & 0xB0)+(ForgC & 0x0B);
//	SetConsoleTextAttributes(hStdOut,wColor);
	SetConsoleTextAttribute(hStdOut,wColor);
}
}
void display()
{

    setcolor(25);
    printf("\n\n\n\n");
	printf("\t\t -------------------------------------------------------------------------\n");
	printf("\t\t|                                                                         |\n");
	printf("\t\t|  OOOOOO   OOOOOO OOOOOO OOOOOO OOOOOO OOOOOO O     O OOOOOOOO OOOOOO    |\n");
	printf("\t\t|  O        O    O O      O        O      O    O O   O O        O         |\n");
	printf("\t\t|  O  OOOOO OOOOOO OOOOO  OOOO     O      O    O  O  O O   OOOO OOOOOO    |\n");
	printf("\t\t|  O    O O O  O   O      O        O      O    O   O O O    O O      O    |\n");
	printf("\t\t|  OOOOOO O O   O  OOOOOO OOOOOO   O    OOOOOO O     O OOOOOO O OOOOOO    |\n");
	printf("\t\t|                                                                         |\n");
	printf(" \t\t-------------------------------------------------------------------------\n");
 	printf("\t\t\t*************************************************\n");
	printf("\t\t\t*                                               *\n");
	printf("\t\t\t*       -----------------------------           *\n");
	printf("\t\t\t*           WELCOME TO SNAKE BITE               *\n");
	printf("\t\t\t*       -----------------------------           *\n");
	printf("\t\t\t*                                               *\n");
	printf("\t\t\t*                                               *\n");
	printf("\t\t\t*************************************************\n\n\n");
	printf("\n\n\t\t Press any key to continue:");
	getch();
	system("cls");
	int i;
	printf("\n\n\n\n\n");
	printf("\n\t\t\t\t");
}

int main (void)
{
    char name[50];
    int n,j=0,r=0,k=0,p=0;
    double s=200;

    display();
	system("cls");
    printf("\n\n\t\tEnter your name:");
	gets(name);

    L1:
    rules();
    printf("\n\t\tWhat do you want to do?\n");
    printf("\t\t* Press 1 to play:\n\t\t* Press 2 to view scoreboard:\n");
    scanf("%d",&n);
    L2:
    j=0;
    switch(n)
    {
    case 1:
        j++;
        r=0;s=200;
        buffer();
        system("cls");
        break;
    case 2:
        k++;
        scoreboards();
        break;
    default:
        {
            printf("You choose the wrong option\n");
            goto L1;
        }
    }
    // Denotes directions 	UP		RIGHT	DOWN	LEFT
    // corresponding to		Arrow Keys
    if(j>0)
    {
    // set console mode for no enter input (unbuffered)
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hstdin, 0);//0 means unbuffered, for real time accessibility

    // Denotes directions 	UP		RIGHT	DOWN	LEFT
    // corresponding to     Arrow keys
    int dir = 1;
    struct Point delta[] = { newPoint(0, -1), newPoint(1, 0), newPoint(0, 1), newPoint(-1, 0) };

    //Snake default body
    if(p==0)
    {
    push_front(newPoint(width/2, height/2 + 2));	//tail
    push_front(newPoint(width/2, height/2 + 1));	//mid
    push_front(newPoint(width/2, height/2));
    }		//head
    //gotoxy(width/2, height/2 - 2);
    struct Point Apple = createApple();
    int ateApple = 0;

    int maxIters = 60;
    while(1)
    {
    	Sleep(s);

    	// update direction
        if (GetAsyncKeyState(VK_UP)) dir = 0;
        else if (GetAsyncKeyState(VK_RIGHT)) dir = 1;
        else if (GetAsyncKeyState(VK_DOWN)) dir = 2;
        else if (GetAsyncKeyState(VK_LEFT)) dir = 3;
    	// current head
    	struct Point head = front();//Goes to the front of the list.
    	// get new head
    	struct Point newHead = newPoint(head.x + delta[dir].x, head.y + delta[dir].y);
    	// check for collisions
    	if (newHead.x >= width || newHead.x < 0) break;
    	if (newHead.y >= height || newHead.y < 0) break;
    	// check for apple
    	//printf("Here2.");
    	push_front(newHead);
    	ateApple = checkHeadAtApple(Apple);
    	// add new head to list (moving forwards)


    	if (ateApple == 1)
        {
            r=r+10;
            if(s>25)
                s=s/2;
    		// if apple was found, do nothing with tail (snake grew)
    		//create new apple
    		Apple = createApple();
    		ateApple = 0;
    	}
    	else
        {
	    	// else, remove last element of list (didn't grow, so we delete tail)
	    	pop_back();
    	}
        //printf("Here3.");
    }
    }
    system("cls");
    printf("\n\n\t\t\t* Enter 1 to play again:\n\t\t\t* Enter 2 to view scoreboard\n\t\t\t* Enter 0 to continue:");
    scanf("%d",&n);
    if(n>0)
    {
        p++;
        goto L2;
    }
    system("cls");
    result(name,r);
    return 0;
}
