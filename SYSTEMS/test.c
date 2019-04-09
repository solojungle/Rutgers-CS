#include <stdio.h>
#include <stdlib.h>

void printMap(int length, int colorRange, int colorOffset) {
	int i = 0;
	char * colorArr[] = {"\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[34m", "\x1B[35m", "\x1B[36m", "\x1B[37m"};
	if ((colorRange + colorOffset) > 7) {
		fprintf(stderr, "ERROR: Invalid colors");
		return;	
	}
	while(i < length) {
		char randomLetter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"[random () % 36];
		char * randomColor = colorArr[(random() % colorRange) + colorOffset];
		printf("%s%c", randomColor, randomLetter);
		i += 1;
	}
}

void rainbow(int length) {
	int i = 0;
	char * colorArr[] = {"\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[34m", "\x1B[35m", "\x1B[36m", "\x1B[37m"};
	 while(i < length) {
		char randomLetter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"[random () % 36];
		char * randomColor = colorArr[i % 6];
		printf("%s%c", randomColor, randomLetter);
		i += 1;
	}
}

int main(int argc, char ** argv) {
	while(1){
	printMap(15000, 3, 0);
}
	return(0);
}
