#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAXLENGTH	30
#define MAX_DIE		6
#define N_PLAYER	3

#define PLAYERSTATUS_LIVE		0
#define PLAYERSTATUS_DIE		1
#define PLAYERSTATUS_END		2



char player_name[N_PLAYER] [MAXLENGTH];
int player_position [N_PLAYER];
int player_coin [N_PLAYER];
int player_status [N_PLAYER];
char player_statusString [3] [MAXLENGTH]= {"LIVE", "DIE", "END"};

void printfPlayerPosition(int player)
{
	int i;
	for (i=0; i < N_BOARD; i++)
	{
		printf("|");
		if (i == player_position [player ] )
		{
			printf("%c", player_name [player] [0]);
		}
		else
		{
			if (board_getBoardStatus(i) == BOARDSTATUS_OK)
				printf(" ");
			else
				printf("X");
		}
		
	}
	printf("|\n");
}

void printPlayerStatus (void)
{
	int i;
	for (i=0; i<N_PLAYER; i++)
	{
		printf ("%s : pos %i, coin %i, status %s\n", 
						player_name[i],
						player_position[i],
						player_coin[i],
						player_statusString [player_status[i]] );
		printfPlayerPosition(i);
	}
}

void initPlayer(void)
{
	int i;
	for (i=0; i<N_PLAYER; i++)
	{
		player_position [i] = 0;
		player_coin [i] = 0;
		player_status [i] = PLAYERSTATUS_LIVE;
		printf("Player %i's name: ", i);
		scanf("%s", player_name[i]);
		fflush(stdin);
	}
}

int getAlivePlayer (void)
{
	int i;
	int count = 0;
	
	for (i=0; i<N_PLAYER; i++)
	{
		if (player_status[i] == PLAYERSTATUS_LIVE ||
			player_status[i] == PLAYERSTATUS_END)
			count++;
	}
	return count;
 } 
 
 int getWinner (void)
 {
 	int i;
 	int max_coin = -1;
 	int max_player = -1;
 	
 	for (i=0; i<N_PLAYER; i++)
 	{
 		if (player_status[i] == PLAYERSTATUS_LIVE ||
		 	player_status[i] == PLAYERSTATUS_END)
		 	{
		 		if (player_coin [i] > max_coin)
		 		{
		 			max_coin = player_coin[i];
		 			max_player = i;
				 }
			 }
	 }
	 return max_player;
 }


int gameEnd (void)
{
	int i;
	int flag_end=1;
	for (i=0; i<N_PLAYER; i++)
	{
		if (player_status[i] == PLAYERSTATUS_LIVE)
			flag_end = 0;
	}
	return flag_end;
}

void checkDie (void)
{
	int i;
	for (i=0; i<N_PLAYER; i++)
	{
		if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
		{
			player_status[i] = PLAYERSTATUS_DIE;
			printf("So sad! %s died at position %i\n", player_name[i], player_position[i]);
		}
	}
}

int rolldie (void)
{
	return rand() %MAX_DIE+1;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int turn;
	int dum;

	srand((unsigned) (time (NULL)) );
	
	//opening
	printf("===================================================\n");
	printf("===@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@===\n");
	printf("================SHARK ISLAND GAME START============\n");
	printf("===@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@===\n");
	printf("===================================================\n");

	//step.1
	board_initBoard();
	initPlayer();
	
	//step.2
	turn=0;

	do{
		int die_result;
		
		if (player_status [turn] != PLAYERSTATUS_LIVE)
		{
			turn = (turn+1) %N_PLAYER;
			continue;
		}
		
		board_printBoardStatus();
		
		printPlayerStatus();
		
		printf("%s turn!!", player_name [turn]);
		printf("Press any key to roll a die!\n");
		scanf("%d", &dum);
		fflush(stdin);
		
		die_result = rolldie();
		
		player_position [turn] += die_result;
		
		if (player_position [turn] >= N_BOARD-1)
		{
			player_position [turn] = N_BOARD-1;
			player_status[turn] = PLAYERSTATUS_END;
		}
		
	
		printf("Die result : %i, %s moved to %i\n", die_result, player_name[turn], player_position[turn]);
		
		player_coin [turn] += board_getBoardCoin(player_position[turn]);
		printf("Lucky! %s got %i coins\n", player_name[turn], player_coin [turn]);
		 
		turn = (turn+1) %N_PLAYER;
		
		if (turn == 0)
		{
			int shark_pos = board_stepShark();
			printf("Shark moved to %i\n", shark_pos);
			checkDie ();
		}
	
	} while(gameEnd() == 0);

	int alive = getAlivePlayer();
	int winner = getWinner();
	
	printf("Alive players : %d\n", alive);
	printf("Winner : %s with %d coins!\n",
			player_name [winner], player_coin[winner]);
	

	//ending
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("===================================================\n");
	printf("===@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@===\n");
	printf("================SHARK ISLAND GAME END==============\n");
	printf("===@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@+@===\n");
	printf("===================================================\n\n");
	
	system("PAUSE");
	return 0;
}
