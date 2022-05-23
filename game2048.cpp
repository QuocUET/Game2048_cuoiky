#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define MARGIN_TOP 1
#define MARGIN_LEFT 2
#define SIZE 6

using namespace std;

const int MAX=2048;
static int score;

//di chuyen con tro den vi tri bat ki trong Console
void gotoxy(short x, short y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

//Ham thay doi textcolor va backgroundcolor
void setColor(short x) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}

short countNumbers(int x) {
	short count=0;
	do{
		count++;
		x=x/10;
	} while(x>0);
	return count;
}
//Tao so ngau nhien tren console
void randomNumber(int vt[4][4]) {
	int pos1,pos2;
	srand(time(0));
	do {
		pos1=rand()%4;
		pos2=rand()%4;
	} while(vt[pos1][pos2]!=0);

	do{
		vt[pos1][pos2]=2+rand()%3;
	} while(vt[pos1][pos2]==3);
}

bool gameChanged(int a[4][4], int b[4][4]) {
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			if(a[i][j]!=b[i][j]) {
				return true;
			}
		}
	}
	return false;
}
int winGame(int vt[4][4]){
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            if(vt[x][y]==MAX){
                return 1;
            }
        }
    }
    return 0;
}

int gameOver(int vt[4][4]){
    int is_game_over=1;
    for(int x=0;x<4;x++){
        for(int y=0;y<3;y++){
            if(vt[x][y]==0||vt[x][y+1]==0||vt[x][y]==vt[x][y+1]){
                is_game_over=0;
                break;
            }
        }
    }
    for(int y=0;y<4;y++){
        for(int x=0;x<3;x++){
            if(vt[x][y]==0||vt[x+1][y]==0||vt[x][y]==vt[x+1][y]){
                is_game_over=0;
                break;
            }
        }
    }
    return is_game_over;
}
int highscore(int vt[4][4]){
    double sum=0;
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            sum=sum+vt[x][y];
        }
    }
    return sum;
}
//Di chuyen len tren
void goUp(int vt[4][4]) {

	// fill spaces
	for (int x= 0;x<4;x++) {
		for (int y=0;y<4;y++) {
			if (!vt[x][y]) {
				for (int z= y+1;z<4;z++) {
					if (vt[x][z]) {
						vt[x][y]=vt[x][z];
						vt[x][z]=0;
						break;
					}
				}
			}
		}
	}

	// update values
	for (int x=0;x<4;x++) {
		for (int y=0; y < 3; y++) {
			if (vt[x][y]==vt[x][y+1]) {
				vt[x][y]*=2;
				vt[x][y+1]=0;
			}
		}
	}
}
//di chuyen xuong duoi
void goDown(int vt[4][4]) {
	// fill spaces
	for (int x=0;x<4;x++) {
		for (int y=3;y>0;y--) {
			if (!vt[x][y]) {
				for (int z=y-1; z>=0;z--) {
					if (vt[x][z]) {
						vt[x][y]=vt[x][z];
						vt[x][z]=0;
						break;
					}
				}
			}
		}
	}

	// update values
	for (int x=3;x>=0;x--) {
		for (int y=3;y>0;y--) {
			if (vt[x][y]==vt[x][y-1]) {
				vt[x][y]*=2;
				vt[x][y-1]=0;
			}
		}
	}
}

void goLeft(int vt[4][4]) {
	// fill spaces
	for (int x=0;x<4;x++) {
		for (int y=0;y<4;y++) {
			if (!vt[y][x]) {
				for (int z=y+1;z<4;z++) {
					if (vt[z][x]) {
						vt[y][x]=vt[z][x];
						vt[z][x]=0;
						break;
					}
				}
			}
		}
	}

	// update values
	for (int x=0;x<4;x++) {
		for (int y=0;y<3;y++) {
			if (vt[y][x]==vt[y+1][x]) {
				vt[y][x]*= 2;
				vt[y+1][x]= 0;
			}
		}
	}
}

void goRight(int vt[4][4]) {
	// fill spaces
	for (int x=0;x<4;x++) {
		for (int y=3;y>=0;y--) {
			if (!vt[y][x]) {
				for (int z=y-1;z>=0;z--) {
					if (vt[z][x]) {
						vt[y][x]=vt[z][x];
						vt[z][x]=0;
						break;
					}
				}
			}
		}
	}

	for (int x=0;x<4;x++) {
		for (int y=3;y>=0;y--) {
			if (vt[y][x]==vt[y-1][x]) {
				vt[y-1][x]*= 2;
				vt[y][x]= 0;
			}
		}
	}
}
void drawTable(int vt[4][4], short &curCol, short &curRow) {

	curCol = MARGIN_LEFT;
	curRow = MARGIN_TOP;

	gotoxy(curCol,curRow);
	cout<<char(218);
	for (short i=1;i<32;i++) {
		if(i%8==0) {
			cout<<char(194);
		} else {
			cout<<char(196);
		}

	}
	cout<<char(191);
	curRow++;

	for (short i=1;i<16;i++) {
		curCol = MARGIN_LEFT;
		if (i==4||i==8||i==12) {
			curCol = MARGIN_LEFT;
			gotoxy(curCol, curRow);
			cout<<char(195);
			for (short j=1;j<32; j++) {
				if (j%8==0) {
					cout<<char(197);    // dau chu thap '+'
				} else {
					cout<<char(196);    // dau gach ngang '-'
				}
			}
			cout<<char(180);
		} else if (i==2||i==6||i==10||i==14) {
			curCol = MARGIN_LEFT;
			gotoxy(curCol,curRow);
			cout<<char(179);
			for (short j= 1;j<32;j++) {
				if (j==8||j==16||j==24) {
					curCol++;
					gotoxy(curCol,curRow);
					cout<<char(179); // dau gach dung '|'
				} else if(j==4||j==12||j==20||j==28) {
					// Ve so
					curCol++;
					gotoxy(curCol,curRow);

					short x,y;
					if (i==2)	y = 0;
					if (i==6)   y = 1;
					if (i==10)  y = 2;
					if (i==14)  y = 3;
					if (j==4)  x = 0;
					if (j==12) x = 1;
					if (j==20) x = 2;
					if (j==28) x = 3;

					int number=vt[x][y];
					if (number!= 0) {

					if (number==2) setColor(53);
					if (number==4) setColor(30);
					if (number==8) setColor(214);
					if (number==16) setColor(28);
					if (number==32) setColor(38);
					if (number==64) setColor(125);
					if (number==128) setColor(204);
					if (number==256) setColor(57);
					if (number==512) setColor(18);
					if (number==1024) setColor(7);
					if (number==2048) setColor(226);
					if (number==4096) setColor(190);
					if (number==8192) setColor(206);
					if (number==16384) setColor(222);
					if (number==32768) setColor(223);

						switch(countNumbers(number)) {
							case 1:
								curCol-=4;
								cout<<" "<<vt[x][y]<<" ";
								curCol+=4;
								break;
							case 2:
								curCol--;
								gotoxy(curCol,curRow);
								cout <<" "<<vt[x][y]<<" ";
								curCol++;
								break;
							case 3:
								curCol-=2;
								gotoxy(curCol,curRow);
								cout <<" "<<vt[x][y]<<" ";
								curCol+=2;
								break;
							case 4:
								curCol-=5;
								gotoxy(curCol,curRow);
								cout<<" "<<vt[x][y]<<" ";
								curCol+=5;
								break;
							default:
								curCol-=3;
								gotoxy(curCol,curRow);
								cout<<" "<<vt[x][y]<<" ";
								curCol+=3;
						}
						setColor(15);
					}
				} else {
					curCol++;
					gotoxy(curCol,curRow);
				}
			}
			curCol++;
			gotoxy(curCol, curRow);
			cout<<char(179);
		} else if(i==1||i==3||i==5||i==7||i==9||i==11||i==13||i==15) {
			for (short j=0;j<=32;j++) {
				if (j==0||j==8||j==16||j==24||j==32) {
					gotoxy(curCol,curRow);
					cout<<char(179);
					curCol++;
				} else {
					curCol++;
					gotoxy(curCol,curRow);
				}
			}
		}
		curRow++;
	}

	curCol = MARGIN_LEFT;
	gotoxy(curCol,curRow);
	cout<<char(192);
	for (short i=1;i<32;i++) {
		if ( i%8==0) {
			cout<<char(193);
		} else {
			cout<<char(196);
		}
	}
	cout<<char(217);
	curRow++;
}

int main(int argc, char** argv) {

	int vt[4][4];
	int a[4][4];
	int question=0;

	for(short i=0;i<4;i++) {
		for (short j=0;j<4;j++) {
			vt[i][j]=0;
		}
	}

	vt[0][0]=2;
	vt[1][3]=2;
	vt[2][2]=2;
	vt[3][0]=4;

	short curCol = MARGIN_LEFT;
	short curRow = MARGIN_TOP;

	system("cls");
	drawTable(vt,curCol,curRow);

	while (true) {
        cout<<"\n Huong dan:";
        cout<<"\n - Phim UP de di chuyen len tren";
        cout<<"\n - Phim DOWN de di chuyen xuong duoi";
        cout<<"\n - Phim LEFT de di chuyen sang trai";
        cout<<"\n - Phim RIGHT de di chuyen sang phai";
		memcpy(a,vt,sizeof(vt));
		int key=getch();
		system("cls");

        if(winGame(vt) && !question){
            question = !question;
            cout<<"BAN THANG";
            cout<<"Tiep tuc? (y/n)";
            exit(1);
        }

        if(gameOver(vt)){
            cout<<"~~~~~~~~~~~~~~~~~~GAME OVER~~~~~~~~~~~~~~~~~~";
            cout<<"\n<<<Cam on ban da tham gia tro choi cua toi>>>";
            exit(2);
        }

		if (key==224) {
			int k=getch();
			// UP
			if (k==72) {
				goUp(vt);
				gotoxy(MARGIN_LEFT, curRow);
				cout<<"UP";
			}
			// LEFT
			if (k==75) {
				goLeft(vt);
				gotoxy(MARGIN_LEFT,curRow);
				cout<<"LEFT";
			}
			// RIGHT
			if (k==77) {
				goRight(vt);
				gotoxy(MARGIN_LEFT,curRow);
				cout << "RIGHT";
			}
			// DOWN
			if (k==80) {
				goDown(vt);
				gotoxy(MARGIN_LEFT,curRow);
				cout << "DOWN";
			}

			if (gameChanged(vt,a)) {
				randomNumber(vt);
			}
			drawTable(vt, curCol, curRow);
			cout<<"\n\nDiem cao: "<<highscore(vt);
		} else {
			exit(EXIT_SUCCESS);
		}
	};
	return 0;
}
