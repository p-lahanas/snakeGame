#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define HEIGHT 20
#define WIDTH 50

//ASCII numbers for chosen snake head symbols
#define RIGHT 62 
#define LEFT 60 
#define UP 94 
#define DOWN 118 

typedef struct coordinates{
	int x;
	int y;
	int dir; //one of the direction constants
}coordinate;

void keyboardInput(coordinate *head){
	int key_code;

	if (_kbhit()){
		key_code = getch();
		
		//GET RID OF THESE MAGIC NUMBERS
		if(key_code == 'a'){
			head->dir = LEFT;}
		else if (key_code == 'd'){
			head->dir = RIGHT;}
		else if (key_code == 'w'){
			head->dir = UP;}
		else if (key_code == 's'){
			head->dir = DOWN;}
	}
}

void updateSnake(coordinate *head){

	int direction = head->dir;
	
	if (direction == RIGHT){
		head->x ++;}
	else if (direction == LEFT){
		head->x --;}
	else if (direction == UP){
		head->y --;}
	else if (direction == DOWN){
		head->y ++;}
}

int printSegment(int i, int j, coordinate segments[], int snakeLength)
{
	for(int k = 1; k <= snakeLength; k++){ //only start looping for one after the head
			
					if(segments[k-1].x == i && segments[k-1].y ==j){
						return 1;}
				}
	return 0;

}

void printGame(coordinate *head, coordinate *fruit, coordinate segments[], int snakeLength){
	
	for (int j = 0; j<HEIGHT; j++){

		for (int i=0; i<WIDTH; i++){
					
			if(j == 0 || j == HEIGHT-1){
				printf("!");}
			else if (i == 0 || i == WIDTH-1){
				printf("!");}
			else if (head->x == i && head->y ==j){ //head should never be in boundary so else if 
				printf("%c", head->dir);}
			else if(printSegment(i, j, segments, snakeLength)){ //should also never be in boundary
				printf("o");}
			else if (fruit->x == i && fruit->y == j){ //this will not fire if head and fruit are in the same coor (which means both won't print in the same cycle)
				printf("F"); }
			else {
				printf(" ");}
		}
		printf("\n");
	}
	printf("Score: %d\n", snakeLength);
	printf("\n\n"); //helps smooth out background drawing
}

void updateFruit(coordinate *fruit){
	//rand() produces random number between 0 and RAND_MAX where RANDMAX is system dependent
	int updateX = (rand() % (WIDTH-2))+1; 
	int updateY = (rand() % (HEIGHT-2))+1;
	fruit->x = updateX;
	fruit->y = updateY;
}

int collisionManagement(coordinate *head, coordinate *fruit, int *snakeLength, coordinate segments[]){
	
	if(head->x == fruit->x && head->y == fruit->y){
		updateFruit(fruit);
		*snakeLength = *snakeLength + 1;}
		
	if(head->x >= WIDTH-2 || head->x <= 0 || head->y <= 0 || head->y >= HEIGHT-2)
		return 1;

	for(int i = 0; i < *snakeLength; i++){
		if(head->x == segments[i].x && head->y == segments[i].y)
			return 1;}

	return 0;
}

void updateSegments(coordinate segments[], int snakeLength, coordinate *head){

	for(int i = snakeLength; i >= 1; i--){ //only start looping for one after the head
		
		if(i == 1){
			segments[i-1].x = head->x;
			segments[i-1].y = head->y;
		}
		else{
			segments[i-1].x = segments[i-2].x;
			segments[i-1].y = segments[i-2].y;
		}
	}
}

void loadingScreen(){
	int loadWait;
	printf("WELCOME TO SNAKE BY PETER LAHANAS! (Windows Version)\n\n\n");
	//ASCII ART FROM https://www.asciiart.eu/animals/reptiles/snakes
	printf("           /^\\/^\\");
	printf("\n         _|__|  O|");
	printf("\n\\/     /~     \\_/ \\");
	printf("\n \\____|__________/  \\");
	printf("\n        \\_______      \\");
	printf("\n                `\\     \\                 \\");
	printf("\n                  |     |                  \\");
	printf("\n                 /      /                    \\");
	printf("\n                /     /                       \\\\");
	printf("\n              /      /                         \\ \\");
	printf("\n             /     /                            \\  \\");
	printf("\n            /     /             _----_            \\   \\");
	printf("\n           /     /           _-~      ~-_         |   |");
	printf("\n          (      (        _-~    _--_    ~-_     _/   |");
	printf("\n          \\      ~-____-~    _-~    ~-_    ~-_-~    /");
	printf("\n            ~-_           _-~          ~-_       _-~");
	printf("\n              ~--______-~                ~-___-~");
	printf("\n__________________________________________________________");

	printf("\nPress 's' followed by 'enter' to begin...");
	scanf("%d", &loadWait);
}

int main(){
	srand(time(0)); //use current time for random number seed
	int gameOver = 0;
	int snakeLength = 0;

	coordinate *headPointer, *fruitPointer;
	coordinate head, fruit;
    coordinate *segmentPointer = (coordinate*) malloc((WIDTH-1)*(HEIGHT-1)*sizeof(coordinate));
	
	
	head.x = WIDTH/2;
	head.y = HEIGHT/2;
	head.dir = RIGHT;
	headPointer = &head;
	fruitPointer = &fruit;
	
	updateFruit(fruitPointer);
	
	loadingScreen();

	while(!gameOver){
		
		system("cls");//fix this to make refresh smoother

		keyboardInput(headPointer);
		updateSnake(headPointer);
		printGame(headPointer, fruitPointer, segmentPointer, snakeLength);
		gameOver = collisionManagement(headPointer, fruitPointer, &snakeLength, segmentPointer);
		updateSegments(segmentPointer, snakeLength, headPointer);
	}
	free(segmentPointer);
	system("cls"); //clear screen for GAMOVER screen

	printf("                 ____");
	printf("\n                / . .\\");
	printf("\n                \\  ---<");
	printf("\n                 \\  /");
	printf("\n       __________/ /");
	printf("\n    -=:___________/");

	printf("\n__________________________\n");
	printf("\nGAMEOVER\n");
	printf("___________________________\n");
	printf("\tYour score was: %d \n", snakeLength);
	system("pause");
	

	return 0;
}
