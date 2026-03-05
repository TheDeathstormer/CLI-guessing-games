char* retrievedWord ();
void displayWord(char* hiddenWord, bool guessedLetters[]);
void drawHangman(int attempts);

//Game beginning:
void hangman()
{
    printf("\nHangman:\nA random word is chosen by the computer. You win if you guess its letters correctly. \n"
           "For each wrong guess, a head, torso, or limb of the hangman is drawn. Once all 6 parts have been "
           "drawn, you will be out of turns. \n");
    if (menuExit())
    {
        return;
    }

    do //for menuExit
    {
        int attempts = 6;
        char guessedWord[10] = {0};                 //letters won't be more than 10. Tracks correctly guessed letters
        bool guessedLetters[26] = { false };        //tracks all guessed letters
        char* hiddenWord = retrievedWord();         //pointer to random word from word bank
        int totalLetters = strlen(hiddenWord);      //counts letters in selected word

        while (attempts != 0) 
        {
            displayWord(hiddenWord, guessedLetters);
            drawHangman(attempts);

            printf("\nEnter a letter: ");
            char guess;
            while (!scanf(" %c", &guess) || !isalpha(guess) ) //ensures only accepting letters
            {
                while (getchar() != '\n');  
                    
                printf("Invalid input. Enter a letter: ");
            }

            guess = toupper(guess);

            if (guessedLetters[guess - 'A']) 
            {
                printf("You've already guessed that letter. Try again.\n");
                continue;
            }
            guessedLetters[guess - 'A'] = true; //guessed letter is stored (toggled)

            bool correctGuess = false;
            for (int i = 0; i < totalLetters; i++) //for all letters of hiddenWord:
            {
                if (hiddenWord[i] == guess)        //check if they're equal to the guessed letter
                {
                    correctGuess = true;
                    guessedWord[i] = guess;
                }
            }

            if (correctGuess) 
            {
                printf("Good guess!\n");
            }
            else 
            {
                printf("The letter '%c' is not in the word.\n", guess);
                --attempts;
            }

            if (strcmp(hiddenWord, guessedWord) == 0) //compares strings to check if equal
            {
                printf("\nCongratulations! You've guessed the word: %s\n", hiddenWord);
                break;
            }
        }

        if (attempts == 0) 
        {
            printf("\nYou are out of turns. The word was '%s'\n", hiddenWord);
        }
        
        int scoreMult = 10;
        int sessionScore = scoreMult * attempts; 
        activePlayer.hangman.score += sessionScore;
        activePlayer.hangman.totalSessions++;
    } while (!menuExit()); 

    return;
}

void displayWord(char* hiddenWord, bool guessedLetters[])   //displays the current progress of the guessedWord
{
    printf("Word: ");
    for (int i = 0; hiddenWord[i] != '\0'; i++)             //checks all letters of hiddenWord
    {
        if (guessedLetters[hiddenWord[i] - 'A'])            //if a letter in hiddenWord, is in guessedLetters: 
        {
            printf("%c ", hiddenWord[i]);
        }
        else 
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void drawHangman(int attempts) {
    char *drawingSegment[] = 
    {
                                            "       +--------+",
                                            "       |        |",
                                            "       |        ",
                                            "       |        ",
                                            "       |        ",
                                            "       |        ",
                                            "       |        ",
                                            "     ========="
    };

    if (attempts <= 5) drawingSegment[2] =  "       |        O";
    if (attempts <= 4) drawingSegment[3] =  "       |        |";
    if (attempts <= 3) drawingSegment[3] =  "       |       /|";
    if (attempts <= 2) drawingSegment[3] =  "       |       /|\\";
    if (attempts <= 1) drawingSegment[4] =  "       |       /";
    if (attempts == 0) drawingSegment[4] =  "       |       / \\";

    for (int i = 0; i < 8; i++) 
    { 
        printf("%s\n", drawingSegment[i]);
    }
}

char* retrievedWord () //retrieves random word from word bank
{

    const char *wordBank[] =   {"BEHAVED", "AGAINST", "OFFENCE", "PICTURE", "ANOTHER", "COUNTRY",
                                "EXAMPLE", "SURFACE", "WHETHER", "SOMEONE", "THOUSAND", "BECAUSE",
                                "CRYSTAL", "CENTURY", "SPECIAL", "PERHAPS", "TOGETHER", "PROBLEM",
                                "POSSIBLE", "CERTAIN", "WONDERS", "AFFECTS", "DECIDED", "RELEASE",
                                "APPEARS", "NATURAL", "WRITING", "REMAINS", "PROBABLY", "VISIBLE",
                                "BROUGHT", "MOMENTS", "SILENCE", "ALLOWED", "CLOSER", "REFUSED",
                                "REACHED", "STRANGE", "QUICKLY", "OBJECTS", "CREATED", "EXPLAIN",
                                "MEMBERS", "PERFECT", "FORWARD", "CONTAIN", "SUBJECT", "OFFICER",
                                "RECORDS", "GRADUAL", "HAPPENS", "SERIOUS", "DIFFER", "REPLIED",
                                "SERVING", "TRAFFIC", "ARRIVED", "PROMISE", "CHARGED", "BELIEVE",
                                "REFLECT", "FOREVER", "FASHION", "RELATED", "DEMAND", "INVOLVE",
                                "PRESENT", "WESTERN", "FINALLY", "SUPPORT", "REASON", "EXPECT",
                                "REPEATED", "DEVELOP", "HIMSELF", "SUCCESS", "REACHING", "CHAPTER",
                                "NOTHING", "THINKER", "SLIGHTLY", "CLEARED", "COMFORT", "WIDELY",
                                "JOURNEY", "CONCERN", "PRODUCE", "VISIBLE", "SLIGHT", "ACTUALLY"};

    return wordBank[rand() % 90];
}