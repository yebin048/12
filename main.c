#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	srand((unsigned) (time (NULL)) );
	
	//opening
	printf("===============================================\n");
	printf("===@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@===\n");
	printf("===			SHARK ISLAND GAME START			===\n");
	printf("===@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@===\n");
	printf("===============================================\n");

	//ending
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("===============================================\n");
	printf("===@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@===\n");
	printf("===			SHARK ISLAND GAME END			===\n");
	printf("===@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@===\n");
	printf("===============================================\n\n");
	
	system("PAUSE");
	return 0;
}
