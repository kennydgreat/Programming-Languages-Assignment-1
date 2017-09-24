// ProgrammingLanguagesAssignment1.c : Defines the entry point for the console application.
/*
	This program implements a guessing game where the user has to guess a letter
*/
//

#include "stdafx.h"
#include "stdlib.h"
#include <sys/types.h>
#include <time.h>

char *user_greating_messag = "Hi there, I am thinking of a letter, What's your guess\n"; 
char *guess_too_high_message = "Your guess is too high.\nTry again. What's your guess?\n";
char *guess_too_low_message = "Your guess is too low.\nTry again. What's your guess?\n" ;
char *guess_right_message = "*** Congratulations! You got it right! ***\n";
char *input_too_low_message = "Your input is too long. Please enter only one letter.\n";
char *input_not_letter = "Your input is not a letter please enter a letter (A-Z or a-z)\n"; 
char *play_again_question = "If you to play again press 'p'\nIf you want to quit the program press 'q'\n";
char *play_again_message = "Alright let's play again. I am thinking of a letter, What's your guess\n";
char *wrong_optoin_message = "Wrong letter. Remember, If you to play again press 'p'\nIf you want to quit the program press 'q'\n";

//Determines how good the user's guess is and returns a high or low
void how_good_is_guess(char user_inut, char letter, int number_of_tries, int * right_or_wrong );

//returns the position of the letter in the alphabet 
int get_offset(char letter);

//Checks if input is good
int input_handler(char * user_input);

//Intialiates new game
void start_new_game(char *letter);

//Checks if input after program asks for new  game  options is 
// correct
int game_options_input_handler(char * user_input);


int get_offset(char letter) {
	if (isupper(letter)) {
		return letter - 'A';
	}
	else return letter - 'a';
}

int input_handler(char * user_input) {
	if (strlen(user_input) > 2)
	{
		printf(input_too_low_message);
		return 0;
	}
	else
	{
		if (!isupper(user_input[0]) && !islower(user_input[0]))
		{
			printf(input_not_letter);
			return 0;
		}
		else return 1;
	}
}
void start_new_game(char * letter) {
	// gets a new letter
	int offset = rand() % 25;
	*letter = 'A' + offset;
	printf(play_again_message);
}

int game_options_input_handler(char * user_input) {
	//If there is more that 2 characters (letter and new line)
	if (strlen(user_input) > 2)
	{
		printf(input_too_low_message);
		return 0;
	}
	else
	{
		if ((user_input[0] != 'p') && (user_input[0] != 'q'))
		{
			printf(wrong_optoin_message);
			return 0;
		}
		else return 1;
	}
}

void how_good_is_guess(char user_input,char letter,  int number_of_tries, int * right_or_wrong) {
	// sets the position of the letter in the alphabet
	int offset_letter = get_offset(letter);
	int offset_user_input = get_offset(user_input);
	// Returning a response depending whether the user's input is 
	// higher, lower or matches the position of the letter generated
	if (offset_letter != offset_user_input) {
		if (offset_user_input > offset_letter) printf(guess_too_high_message);
		else printf(guess_too_low_message);
		*right_or_wrong = 0;
	}
	else { 
		printf("%sThe letter is %c\nIt took you %d tries to get it!\n", guess_right_message, letter, number_of_tries); 
		//printf(play_again_message);
		*right_or_wrong = 1;
	}
	

}

int main()
{
	printf(user_greating_messag);
	//Setting a random number generator seed, 
	//using the time for randomness, that is
	// so the letter generated first time around is random
	srand(time(NULL)); 

	//Getting a random letter (rand() % 25 gets a number from 0-25)
	int offset = rand() % 25;
	char letter = 'A'+ offset;
	char int_user_input[100];
	char user_input = 'b';
	int number_of_tries = 0;
	int right_or_wrong = 0;

	int_user_input[0] = 'A';

	//Getting user input
	while (fgets(int_user_input, sizeof(int_user_input), stdin)) {
		//Feeds it to the input_handler to ensure the input is correct if it isn't 
		// it displays a message depending on the nature of the user's input.
		//if the user's input is good it will return q
		if (input_handler(int_user_input))
		{
			//Letter input to the first character in the user's input which is the letter
			//if the user's input is correct
			user_input = int_user_input[0];
			//This determines all good the user's guest in and displays a message depending
			//on how good.
			how_good_is_guess(user_input, letter, number_of_tries, &right_or_wrong );
			//Increment the number of tries
			number_of_tries++;
			//If the user guess correct it goes in the new game sequence
			if (right_or_wrong)
			{
				printf(play_again_question);
				//Get user's input for the play game options
				while (fgets(int_user_input, sizeof(int_user_input), stdin))
				{
					//Checks if the user input for this sequence is correct
					if (game_options_input_handler(int_user_input)) {

						//if correct it gets their input which is the first letter in the sequence 
						switch (int_user_input[0])
						{
						case 'p':
							//Gets a new random letter for the new game
							start_new_game(&letter);
							number_of_tries = 0;
							break;
						case 'q':
							//Quits the program
							return 0;	
						default:
							break;
						}
						
					}
					if (int_user_input[0] == 'p') { break; } //gets out of the while loop to stop asking for user inout
				}
				
			}
		}
		else {}
		
	}
    return 0;
}

