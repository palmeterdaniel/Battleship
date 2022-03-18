#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SHIP{
    int row, column, length;
    char direction;
} SHIP;

typedef struct ATTACK{
    int row, column;
} ATTACK;

int main(int argc, char *argv[] ) {

    // verify command line parameters
    if(argc != 2){
        printf("expected usage: %s <save_game_file>", argv[0]);
        exit(1);
    }

    int rows=0, columns=0, ship_count=0, attack_count=0;

    printf("Reading Save Game File\n");
    FILE *input = fopen(argv[1], "r");
    if(!input){
        printf("INPUT File open failed\n");
        exit(1);
    }

    // skip the board size line
    char skip_this_text[1000];
    if (!fgets(skip_this_text, 1000, input)) {
        printf("Error reading board size");
        exit(1);}

    // read the board size
    fscanf(input, "%d", &rows);
    fscanf(input, "%d", &columns);
    fgets(skip_this_text, 1000, input); // read the newline character
    printf("Board Size = (%d, %d)\n",rows, columns);

    // skip the number of ships line
    if (!fgets(skip_this_text, 1000, input)){
	    printf("Error reading ship count");
	    exit(1);}

    // read the ship count
    fscanf(input, "%d", &ship_count);
    fgets(skip_this_text, 1000, input); // read the newline character
    printf("Number of Ships = %d\n", ship_count); 

    struct SHIP ships[ship_count]; // to hold all ships

    // adds all ships to array
    for(int i=0; i < ship_count; i++){
	
	fscanf(input, "%d", &ships[i].row); // reads in the row
	fscanf(input, "%d", &ships[i].column); // reads in the column
	fscanf(input, "%d", &ships[i].length); // reads in the length
	fscanf(input, "%c", &ships[i].direction); // reads space
	fscanf(input, "%c", &ships[i].direction); // reads in direction
	
	// prints out information to screen
	printf("Ship %d: (%d, %d), length = %d, direction %c\n", i, ships[i].row, ships[i].column, ships[i].length, ships[i].direction);

	fgets(skip_this_text, 1000, input); // reads newline character
    }

    // skip the number of attacks line
    if (!fgets(skip_this_text, 1000, input)){
	    printf("Error reading attack count");
	    exit(1);}

    // read the attack count
    fscanf(input, "%d", &attack_count);
    fgets(skip_this_text, 1000, input); // read the newline character
    printf("Number of Attacks = %d\n", attack_count);

    struct ATTACK attacks[attack_count]; // to hold all attacks

    // adds all attacks to array
    for(int i=0; i < attack_count; i++){

	fscanf(input, "%d", &attacks[i].row);
	fscanf(input, "%d", &attacks[i].column);
	printf("Attack %d: (%d, %d)\n", i, attacks[i].row, attacks[i].column);

    }

    fclose(input);

    // allocates memory on the heap for the board and then initializes it all periods by default
    char *board;
    board = (char *) malloc(rows*columns*sizeof(char)); // allocates space for chars
    strcpy(board, ""); // initializes empty string
    
    for(int i = 0; i < rows*columns; i++){ // makes the string all periods

	strcat(board, ".");

    } 

    printf("\nInitializing Board\n");

    // prints out board
    for(int i=0; i < rows; i++){

	for(int j = 0; j < columns; j++){
		
		printf("%c",*(board + i));
		
	}

	printf("\n");

    }


    printf("\nAdding Ships\n");

    // adds ships
    for(int i = 0; i < ship_count; i++){

	if(ships[i].direction == 'V'){ // if vertical

	 if((ships[i].length + ships[i].row) > rows || ships[i].row < 0 || ships[i].column < 0){ // any aspects out of bounds
		
		printf("Ship %d is out of bounds - skipping\n", i);
	
	   }

	   else{

		int check = 1; // to check for overlap

		for(int j = 0; j < ships[i].length; j++){ // to check for overlapping shipss

		   if(*(board + ships[i].row*columns + ships[i].column + j*columns) == 'S'){ // if there is overlap

			check = 0; // so ship will not be added
			printf("Ship %d overlaps another ship - skipping\n", i);
			break;	

		   }

		}
		
		if(check == 1){ // ship does not overlap

		for(int j = 0; j < ships[i].length; j++){ // adds ships

		    *(board + ships[i].row*columns + ships[i].column + j*columns) = 'S';

		}

		}

	   }

	}

	if(ships[i].direction == 'H'){ // if horizontal

	    if((ships[i].length + ships[i].column) > columns || ships[i].column < 0 || ships[i].row < 0){ // any aspects out of bounds

		printf("Ship %d is out of bounds - skipping\n", i);

	    }

	    else{
	
                int check = 1; // to check for overlap

                for(int j = 0; j < ships[i].length; j++){ // to check for overlapping shipss

                   if(*(board + ships[i].row*columns + ships[i].column + j) == 'S'){ // if there is overlap

                        check = 0; // so ship will not be added
                        printf("Ship %d overlaps another ship - skipping\n", i);
                        break;

                   }

                }
		
		if(check == 1){ // ship does not overlap

		for(int j = 0; j < ships[i].length; j++){ // adds ships

		    *(board + ships[i].row*columns + ships[i].column + j) = 'S';

		}

		}

	    }
	}	
   
    }



    // prints out board
    for(int i=0; i < rows*columns; i++){

        if(i % columns == 0 && i != 0){

                printf("\n");

        }

	printf("%c", *(board + i));

    }

   printf("\n\nProcessing Attacks\n");

   // processes attacks
   for(int i = 0; i < attack_count; i++){

	int inbounds = 0;

	if(attacks[i].row > rows || attacks[i].row < 0 || attacks[i].column > columns || attacks[i].column < 0){
		inbounds = 1;
	}

	if(inbounds == 0){

	if(*(board + attacks[i].row*columns + attacks[i].column) == 'S'){
		*(board + attacks[i].row*columns + attacks[i].column) = 'H';
	}

        if(*(board + attacks[i].row*columns + attacks[i].column) == '.'){
                *(board + attacks[i].row*columns + attacks[i].column) = 'M';
        }
	}
	else{
		printf("Attack %d is out of bounds - skipping\n", i);
	}	

   }

    // prints out board
    for(int i=0; i < rows*columns; i++){

        if(i % columns == 0 && i != 0){

                printf("\n");

        }

        printf("%c", *(board + i));

    }

   // checks if game is over
   
	int over = 0;

   for(int i = 0; i < rows*columns; i++){

	if(*(board + i) == 'S'){

		over = 1;

	}

   }

  if(over == 0){
	printf("\n\nAll ships have been sunk - game over\n\n");
  } 

  else{
       printf("\n\nShips remain afloat - game on\n\n");
  }

  // frees allocated memory
  free(board);

}

