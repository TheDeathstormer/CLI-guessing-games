void numberGuess ()
{
    do
    {
        printf 
        (
            "\nNumber guessing game:\nA random number is chosen by the computer. You win if you guess it correctly.\nDifficulties available:\n"
            "    +------------+-----------+---------------------+--------------------+\n"
            "    | Difficulty |  Range    |    Max Attempts     | Score Multiplier   |\n"
            "    +------------+-----------+---------------------+--------------------+\n"
            "[1] | Easy       |   1-50    | Unlimited           |        0           |\n"
            "[2] | Medium     |  1-100    | 10                  |        5           |\n"
            "[3] | Hard       |  1-500    | 5                   |        65          |\n"
            "    +------------+-----------+---------------------+--------------------+\n"
        );

        if (menuExit())
        {
            return;
        }

        int difficulty, uppLim = 50, scoreMult = 0, attempts = 1; //default values for easy difficulty
        printf ("Press 1, 2, or 3 to select a difficulty:\n");
        while (1)
        {
            while (!scanf("%i", &difficulty)) 
            { 
                integerOnly();
            }
            switch (difficulty)
            {
                case 1:
                    break;
                case 2:
                    uppLim = 100, scoreMult = 5, attempts = 10;
                    break;
                case 3:
                    uppLim = 500, scoreMult = 65, attempts = 5;
                    break;
                default:
                    printf ("Invalid input. Enter a number from 1 to 3.\n");
                    continue;
            }
            break;
        } 
        
        //game beginning
        int guess = 0, hintLim = uppLim / 10, truth = rand() % uppLim + 1; 
        printf ("\n\nEnter a number from 1 to %i to guess the correct number:\n", uppLim);
        
        
        while (guess != truth)
        {
            while (!scanf("%i", &guess)) 
            { 
                integerOnly();
            }
            if (guess >= truth + hintLim && guess <= uppLim)
            {
                printf ("Too high. Try again:\n");               
            }
            else if (guess <= truth - hintLim && guess >= 1)
            {
                printf ("Too low. Try again:\n");
            }
            else if (guess < truth + hintLim && guess > truth - hintLim && guess != truth)
            {
                printf ("Almost there. Try again:\n");
            }
            else if (guess < 1 || guess > uppLim)
            {
                printf ("Invalid input. Enter a number from 1 to %i:\n", uppLim);
            }

            if (difficulty != 1) //Medium or Hard difficulty
            {
                --attempts;
                if (attempts == 0)
                {
                    break; //ends game loop
                }
                printf ("You have %i attempts left.\n", attempts);
            }
            else //Easy difficulty
            {
                ++attempts;
                if (attempts % 4 == 0 && guess != truth) //prompts exit every 4-5 attempts
                {
                    if (menuExit())
                    {
                        return;
                    }
                    else
                    {
                        printf ("Try another number:\n");
                    }   
                }
            }
        }

        if (guess == truth)
        {
            printf ("Congratulations! You guessed the correct number.\n");
        }
        else
        {
            printf ("You are out of attempts. The correct number was %i.\n", truth);
        }

        int sessionScore = scoreMult * attempts; 
        activePlayer.numberGuess.score += sessionScore;
        activePlayer.numberGuess.totalSessions++;
    } while (!menuExit());
    
    return;
}
