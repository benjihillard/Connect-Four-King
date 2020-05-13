#include <stdio.h>
#include <stdlib.h>

// LIST OF FUNCTIONS
void display(char screen[7][8]);
struct Position rowfiller(char rowletter, char player, char screen[7][8]);
struct Position move(char player,char screen[7][8]);
char check(char player,char screen[7][8]);
char ai(char screen[7][8]);

// structure holding all the info of a move
struct Position{
	int row; //row based on number
	int stackheight; // number from the bottom starting a 1 to the top of the stack
	char rowletter; // letter representation of the row
	char player; // X or O based on who put the token into postion
	int seqwarn; // out of bounds warning
};



// prints the screen[7][8]
void display(char screen[7][8]){
	printf("\n");
	for(int i = 0; i<7; i++){
		printf(" %3c  %3c  %3c  %3c  %3c  %3c  %3c  %3c \n \n ",screen[i][0],screen[i][1],screen[i][2],screen[i][3],screen[i][4],screen[i][5],screen[i][6],screen[i][7]);
	}
}


// places the token in the chosen row where rowletter is the chosen row
struct Position rowfiller(char rowletter, char player, char screen[7][8]){
	char choices[7] = "ABCDEFG"; // reference for number to letter conversion
	int row = 0;
	struct Position pos;
	for (int i=0; i < 7 ; i++) {  // loop converts letter entered in param to workable number
		if (choices[i]==rowletter){
			row = i+1;
			pos.rowletter = choices[i];
		}
	}
	for (int i = 7; i > 0; i--) { // loop places correct token in next availble spot in desired row
		if(screen[i][row] == '.'){
			screen[i][row] = player;
			pos.row = row;          //package
			pos.stackheight = i;    //position data
			pos.player = player;		// for export
			pos.seqwarn = 0;
			return pos;
		}
	}
	pos.seqwarn = 1;
	return pos;
}

// called to retrive choice, interally processes choice, returns postion data on choice
struct Position move(char player, char screen[7][8]){
	char choice;
	char choices[7] = "ABCDEFG";
	if (player == 'X'){ //human choice
		printf("Player 1, Please choose a row (A,B,C,D,E,F or G): " );
		scanf(" %c", &choice );
	}
	if (player == 'O'){ // ai choice
		choice = ai(screen);
	}

  switch (choice) { // fills row based on choice
    case 'A':
      return rowfiller('A',player,screen);
			break;
		case 'B':
			return rowfiller('B',player,screen);
			break;
		case 'C':
			return rowfiller('C',player,screen);
			break;
		case 'D':
			return rowfiller('D',player,screen);
			break;
		case 'E':
			return rowfiller('E',player,screen);
			break;
		case 'F':
			return rowfiller('F',player,screen);
			break;
		case 'G':
			return rowfiller('G',player,screen);
			break;

		default:
			if(player == 'X'){ // lets human know they didnt enter a valid letter
				printf("\n");
				printf("Sorry thats not an option, try (A,B,C,D,E,F or G) \n");
				printf("      Make sure you using capital letters\n");
				printf("\n");
				return move(player,screen);
			}
  }
}
// there are 8 ways to get Connect 4 from any postion this checks them in a clock wise motion
//nested loop to get all 42 postions
// returns r for reject if no winner
// returns the char of the winning play if there is one
char check(char player,char screen[7][8]){
	char choices[7] = "ABCDEFG";
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 8; j++) {
			if(i-3 >= 0){ //up
				if(screen[i][j] == player && screen[i-1][j] == player && screen[i-2][j] == player && screen[i-3][j] == player){
					//printf("Winning moves are %c %i | %c %i | %c %i | %c %i \n", choices[j],i ,choices[j],i-1 ,choices[j],i-2 ,choices[j],i-3 );
					return player;
				}
			}
			if(i-3 >= 0 && j+3 < 8){ // up and right
				if(screen[i][j] == player && screen[i-1][j+1] == player && screen[i-2][j+2] == player && screen[i-3][j+3] == player){
					//printf("Winning moves are %c %i | %c %i | %c %i | %c %i \n", choices[j],i ,choices[j+1],i-1 ,choices[j+2],i-2 ,choices[j+3],i-3 );
					return player;
				}
			}
			if(j+3 < 8){ // right
				if(screen[i][j] == player && screen[i][j+1] == player && screen[i][j+2] == player && screen[i][j+3] == player){
					//printf("Winning moves are %c %i | %c %i | %c %i | %c %i \n", choices[j],i ,choices[j+1],i ,choices[j+2],i ,choices[j+3],i );
					return player;
				}
			}
			if(i+3 < 7 && j+3 < 8){ // down and right
				if(screen[i][j] == player && screen[i+1][j+1] == player && screen[i+2][j+2] == player && screen[i+3][j+3] == player){
					//printf("Winning moves are %c %i | %c %i | %c %i | %c %i \n", choices[j],i ,choices[j+1],i+1 ,choices[j+2],i+2 ,choices[j+3],i+3 );
					return player;
				}
			}
			if(i+3 < 7){ //down
				if(screen[i][j] == player && screen[i+1][j] == player && screen[i+2][j] == player && screen[i+3][j] == player){
					//printf("Winning moves are %c %i | %c %i | %c %i | %c %i \n", choices[j],i ,choices[j],i+1 ,choices[j],i+2 ,choices[j],i+3 );
					return player;
				}
			}
			if(i+3 < 7 && j-3 >+ 0){ // down and left
				if(screen[i][j] == player && screen[i+1][j-1] == player && screen[i+2][j-2] == player && screen[i+3][j-3] == player){
					//printf("Winning moves are %c %i | %c %i | %c %i | %c %i \n", choices[j],i ,choices[j-1],i+1 ,choices[j-2],i+2 ,choices[j-3],i+3 );
					return player;
				}
			}
			if(j-3 >= 0){ // left
				if(screen[i][j] == player && screen[i][j-1] == player && screen[i][j-2] == player && screen[i][j-3] == player){
					//printf("Winning moves are %c %i | %c %i | %c %i | %c %i \n", choices[j],i ,choices[j-1],i ,choices[j-2],i ,choices[j-3],i );
					return player;
				}
			}
			if(i-3 >= 0 && j-3 >= 0){ // up and left
				if(screen[i][j] == player && screen[i-1][j-1] == player && screen[i-2][j-2] == player && screen[i-3][j-3] == player){
					//printf("Winning moves are %c %i | %c %i | %c %i | %c %i \n", choices[j],i ,choices[j-1],i-1 ,choices[j-2],i-2 ,choices[j-3],i-3 );
					return player;
				}
			}
		}
	}
	return 'r';
}
char ai(char screen[7][8]){
	char choices[7] = "ABCDEFG";
	int arr[7] = {7,7,7,7,7,7,7}; //list of availble moves all availble now
	for (int i = 0; i < 7; i++) {  //checks all rows
		struct Position pos = rowfiller(choices[i],'O',screen); // temp places O
		if(pos.seqwarn == 1){continue;} //skips if the row doesnt fill
		if(check('O',screen) == 'X'){ //for winning move
			screen[pos.stackheight][pos.row] = '.'; //reset
			return pos.rowletter; // return winning move
		}
		for (int j = 0; j < 7; j++) {// checks all rows from player perspective based on all 7 possible moves
			struct Position pos2 = rowfiller(choices[j],'X',screen); //temp places X
			if(pos2.seqwarn == 1){continue;} //skips if the row doesnt fill
			if(check('X',screen) == 'X'){// check to see if the move sets the other player up for a win
				arr[i]=i; // removes row i from availble choices
			}
			screen[pos2.stackheight][pos2.row] = '.'; //reset board of Xs
		}
		screen[pos.stackheight][pos.row] = '.'; //resets board of Os
	}
	for (int i = 0; i < 7; i++) { // loop looking for blocking moves, perticularly blocking 3 in a row
		struct Position pos = rowfiller(choices[i],'X',screen);
		if(pos.seqwarn == 1){continue;} //skips if the row doesnt fill
		if(check('X',screen) == 'X'){
			screen[pos.stackheight][pos.row] = '.';
			return pos.rowletter;
		}
		screen[pos.stackheight][pos.row] = '.'; //reset
	}

	return choices[(rand()%7)];
}

// prints the moves of the game
void gamehistoryprinter(struct Position moves[42],int gamecounter){
	for (int i = 0; i < gamecounter; i++) {
		printf("%i %c, ", ((6-moves[i].stackheight)+1) , moves[i].rowletter );
	}
	printf("\n");
}
/* contains gameloop */
void main(){
  char exit = 'r'; // hold r until a winner is chosen then hold the char of the winner
	char begin; // holds Y or N for wether the player wants to start first
	char first; // char of player1
	char second; // char of player2
	int gamecounter = 0; // counts the amount of moves made
	struct Position moves[42]; // an array of positions for recording game history
	char screen[7][8] = {{' ','A','B','C','D','E','F','G'},{'6','.','.','.','.','.','.','.',},{'5','.','.','.','.','.','.','.',},{'4','.','.','.','.','.','.','.',},{'3','.','.','.','.','.','.','.',},{'2','.','.','.','.','.','.','.',},{'1','.','.','.','.','.','.','.',}};
  printf(" Welcome to Connect Four!\n");
	printf("--------------------------\n");
	printf("would you like to go first (Y/N): ");
	scanf("%c",&begin);
	if (begin == 'Y' || begin == 'y'){ //assigning players
		first = 'X';
		second = 'O';
	}
	else if (begin == 'N'|| begin == 'n'){ //assigning players
		first = 'O';
		second = 'X';
	}else{
		printf("sorry its a yes or no question\n");
		return 0;
	}
  while(1 == 1){
    display(screen);													//display screen
		moves[gamecounter] = move(first,screen);	//fetches move
		gamecounter++;														//incrms game
		if (check(first,screen) == first){				//checks for winner
			exit = first;														//lets game know who won for display
			break;																	//
		}
		display(screen);													//
		moves[gamecounter] = move(second,screen);	//
		gamecounter++;														//
		if (check(second,screen) == second){			//
			exit = second;													//
			break;																	//player 2 loop
		}

  }
  if(exit == 'X'){//if human wins
		display(screen);
    printf("         Cograulations You Win!\n");
  }
  if(exit == 'O'){// if AI wins
		display(screen);
    printf("   Sorry AI wins, Better Luck Next Time.\n");
  }
  if(gamecounter == 42){// if DRAW
		display(screen);
    printf("                 DRAW!!!\n");
  }
	printf("\n");
	printf("		Game History\n");
	gamehistoryprinter(moves,gamecounter);

}
