#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <list>
using namespace std;

void gotoxy(int x, int y);
void hideCursor(void);
void drawBorders(void);
void cls(void);
void endAnimation(void);

class Person{
private:
	void move(int direction);
	void collition(void);
	int body = 30;
public:
	int x, y;
	int delay, counter = 0;
	Person(int _x, int _y, int d){
		x = _x;
		y = _y;
		delay = d;
	}
	~Person(void){
		Sleep(200);gotoxy(x,y);printf("*");
		Sleep(200);gotoxy(x,y);printf(" ");
	}
	void keyMove(void);
	void botMove(int ex, int ey);
	bool inHitBox(int X, int Y);
};
void Person::move(int direction){
	gotoxy(x,y);printf(" ");
	if(counter == delay){
		switch(direction){
			case 119:y--;body=30;break;
			case 115:y++;body=31;break;
			case 97:x--;body=17;break;
			case 100:x++;body=16;break;
		}
		collition();
		counter = 0;
	}
	else{
		counter += 1;
	}	
	gotoxy(x,y);printf("%c",body);
	return;
}
void Person::collition(void){
	if(x >= 78){x--;}
	if(x <= 2){x++;}
	if(y >= 22){y--;}
	if(y<=2){y++;}
	return;
}
void Person::keyMove(void){
	char key = 'p';
	if(kbhit()){
		key = getch();
	}
	move(key);
	return;
}

void Person::botMove(int ex, int ey){
	int key = 0;
	if(ey != y){
		if(y < ey){
			key = 115;
		}
		else{
			key = 119;
		}
	}
	else{
		if(x > ex){
			key = 97;
		}
		else{
			key = 100; 
		}
	}
	move(key);
	return;
}

bool Person::inHitBox(int X, int Y){
	if((X >= x-1 && X <= x+1) && (Y >= y-1 && Y <= y+1)){
		return true;
	} 
	return false;
}
int main(){
	cls();
	hideCursor();
	drawBorders();
	Person mc (39, 19, 0);
	list<Person*> bots;
	list<Person*>::iterator bit;
	bots.push_back(new Person(39, 8, 2));
	bots.push_back(new Person(13,4, 3));
	bots.push_back(new Person(65,4, 3));
	bool notTag = true;
	while(notTag){
		mc.keyMove();
		for(bit=bots.begin();bit!=bots.end();bit++){
			(*bit)->botMove(mc.x, mc.y);
			if(mc.inHitBox((*bit)->x, (*bit)->y)){
				notTag = false;
			}
		}
		
		Sleep(100);
	}
	for(bit=bots.begin();bit!=bots.end();bit++){
		delete(*bit);
		bit = bots.erase(bit);
	}
	delete &mc;
	endAnimation();
	return 0;
}

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
	return;
}

void hideCursor(void){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 0;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
	return;
}

void drawBorders(void){
	int x,y;
	for(x=2;x<=78;x++){
		gotoxy(x,2);printf("#");
		gotoxy(x,22);printf("#");
	}
	for(y=2;y<=22;y++){
		gotoxy(2,y);printf("#");
		gotoxy(78,y);printf("#");
	}
	return;
}

void cls(void){
	int x, y;
	gotoxy(0,0);
	for(y=0;y<=24;y++){
		for(x=0;x<=80;x++){
			printf(" ");
		}
	}
	gotoxy(0,0);
	return;
}

void endAnimation(void){
	cls();
	drawBorders();
	int i = 0;
	for(i;i<5;i++){
		gotoxy(37,11);printf("GAME OVER");
		Sleep(500);
		gotoxy(37,11);printf("         ");
		Sleep(500);
	}
	return;
}