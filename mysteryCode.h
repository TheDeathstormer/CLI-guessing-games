void mysteryCode()
{
    printf("\nMystery Code:\nA random 4-digit code, with digits in between and including 0 and 9, is created by the computer.\n"
           "You win if you guess the entire code correctly. \nTen tries are provided.\n");
    if (menuExit())
    {
        return;
    }

    do //for menuExit
    {
        int attempts = 10;

        int code[4];                                //array to store the 4-digit code
        for (int i = 0; i < 4; i++)                 //generates a random 4-digit code
        {
            code[i] = rand() % 10;
        }

        int guess[4] = {0};                         //array to store the guessed code
        printf("The code has been generated. You have 10 attempts to guess it.\n");

        while (attempts != 0) 
        {
            printf("\nGuess the 4-digit code: ");
            for (int i = 0; i < 4; i++) 
            {
                while ( !scanf("%i", &guess[i]) ) 
                {
                    integerOnly();
                }
                if (guess[i] < 0 || guess[i] > 9) 
                {
                    printf("Invalid input. Separate the 4 digits when entering them:\n");
                    i--;
                }
            }

            int correctGuesses = 0;
            int displacedGuesses = 0;
            bool codeMatched[4] = {false}; 
            bool guessMatched[4] = {false};

            for (int i = 0; i < 4; i++)  //check if the guessed digit is in a correct position
            {
                if (code[i] == guess[i]) 
                {
                    ++correctGuesses;
                    codeMatched[i] = true;
                    guessMatched[i] = true;
                }
            }

            for (int i = 0; i < 4; i++) //to compare each digit of the guess against the code
            {
                for (int j = 0; j < 4; j++) 
                {
                    if ( code[j] == guess[i] && !codeMatched[j] && !guessMatched[i] ) //if digits match for the first time
                    {
                        ++displacedGuesses;
                        codeMatched[j] = true;
                        guessMatched[i] = true;   
                        break;
                    }
                }
            }
            if (correctGuesses == 4) 
            {
                printf("\nCongratulations! You've guessed the code.");
                break;
            }

            printf("%i digit(s) is correct.\n%i of the digit(s) is present somewhere in the true code, but it is currently in the wrong location.\n", correctGuesses, displacedGuesses);
            --attempts;
            printf("You have %i attempts left.\n", attempts);
        }

        if (attempts == 0) 
        {
            printf("\nYou are out of turns. The code was ");
                for (int i = 0; i < 4; i++) {
                    printf("%d ", code[i]);
                }
                printf("\n");
        }

        int scoreMult = 5;
        int sessionScore = scoreMult * attempts; 
        activePlayer.mysteryCode.score += sessionScore;
        activePlayer.mysteryCode.totalSessions++;
    } while (!menuExit()); 

    return;
}
