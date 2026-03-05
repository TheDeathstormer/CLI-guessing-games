#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "func.h"  
#include "profile management.h"  
#include "numberGuess.h"
#include "hangman.h"
#include "mysteryCode.h"


int main (void)
{
	int profileCount = signIn();
	
	printf ("Press Enter to play!\n");
	getchar(); // Consumes the newline character left by the previous scanf
	getchar(); // Wait for the user to input a character by pressing Enter

	
	srand(time(NULL));
	
	while (1) //loop menu
	{
	    titleAsciiArt ();
	    int i; //userinput
	
	    printf("Select a game to play! Press:\n [1] Number Guess\n [2] Hangman\n [3] Mystery Code\n\n\n\n [4] Player scoreboard\n [0] Save progress and Quit\n\n");
	    while (!scanf("%i", &i)) 
			{ 
				integerOnly();
			}

	    switch (i) //game selection
	    {
	        case 1:
	        	numberGuess ();
	            break;
	        case 2:
	            hangman ();
	            break;
	        case 3:
	            mysteryCode ();
	            break;
	        case 4:
	            showScoreboard(profiles, profileCount);
	            break;
	        case 0:
			    //Update player in profile list from activePlayer
				for (int i = 0; i < profileCount; i++) 
				{
					if (strcmp(profiles[i].username, activePlayer.username) == 0) 
					{
						profiles[i] = activePlayer;
						break;
					}
				}

				save_profiles(profiles, profileCount);
				printf("Goodbye, %s!\n", activePlayer.username);
	            return 0;
	        default:
	            printf ("Invalid input. Please try again.\n");
	    }
    }
	
}


void titleAsciiArt () //GUESSQUEST
{
    printf(
"                                                                                                                      ,----,\n"
"                                                                                                                    ,/   .`|\n"
"  ,----..                     ,---,.  .--.--.    .--.--.       ,----..                       ,---,.  .--.--.      ,`   .'  :\n"
" /   /   \\           ,--,   ,'  .' | /  /    '. /  /    '.    /   /   \\             ,--,   ,'  .' | /  /    '.  ;    ;     /\n"
"|   :     :        ,'_ /| ,---.'   ||  :  /`. /|  :  /`. /   /   .     :          ,'_ /| ,---.'   ||  :  /`. /.'___,/    ,' \n"
".   |  ;. /   .--. |  | : |   |   .';  |  |--` ;  |  |--`   .   /   ;.  \\    .--. |  | : |   |   .';  |  |--` |    :     |  \n"
".   ; /--`  ,'_ /| :  . | :   :  |-,|  :  ;_   |  :  ;_    .   ;   /  ` ;  ,'_ /| :  . | :   :  |-,|  :  ;_   ;    |.';  ;  \n"
";   | ;  __ |  ' | |  . . :   |  ;/| \\  \\    `. \\  \\    `. ;   |  ; \\ ; |  |  ' | |  . . :   |  ;/| \\  \\    `.`----'  |  |  \n"
"|   : |.' .'|  | ' |  | | |   :   .'  `----.   \\ `----.   \\|   :  | ; | '  |  | ' |  | | |   :   .'  `----.   \\   '   :  ;  \n"
".   | '_.' ::  | | :  ' ; |   |  |-,  __ \\  \\  | __ \\  \\  |.   |  ' ' ' :  :  | | :  ' ; |   |  |-,  __ \\  \\  |   |   |  '  \n"
"'   ; : \\  ||  ; ' |  | ' '   :  ;/| /  /`--'  //  /`--'  /'   ;  \\; /  |  |  ; ' |  | ' '   :  ;/| /  /`--'  /   '   :  |  \n"
"'   | '/  .':  | : ;  ; | |   |    \\'--'.     /'--'.     /  \\   \\  ',  . \\ :  | : ;  ; | |   |    \\'--'.     /    ;   |.'   \n"
"|   :    /  '  :  `--'   \\|   :   .'  `--'---'   `--'---'    ;   :      ; |'  :  `--'   \\|   :   .'  `--'---'     '---'     \n"
" \\   \\ .'   :  ,      .-./|   | ,'                            \\   \\ .'`--\" :  ,      .-./|   | ,'                           \n"
"  `---`      `--`----'    `----'                               `---`        `--`----'    `----'                            \n"
    );
}