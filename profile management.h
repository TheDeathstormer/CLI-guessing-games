#define USERNAME_SIZE_MAX 40
#define MAX_PLAYERS 30

struct gameStats 
{
    int score;
    int totalSessions;
};

struct playerProfile 
{
    char username[USERNAME_SIZE_MAX];
    struct gameStats numberGuess, hangman, mysteryCode;
} activePlayer; //Global player in session

struct playerProfile profiles[MAX_PLAYERS]; //array of player profiles

//Read profiles from file into array, return profileCount
int loadProfiles(struct playerProfile profiles[]) 
{
    FILE *filePtr = fopen("profiles.dat", "rb");
    if (!filePtr) //if no accounts created yet
    {
        return 0;
    }
    int profileCount = fread(profiles, sizeof(struct playerProfile), MAX_PLAYERS, filePtr);
    fclose(filePtr);
    return profileCount;
}

//Save profiles array back to file
void save_profiles(struct playerProfile profiles[], int profileCount) {
    FILE *filePtr = fopen("profiles.dat", "wb");
    if (!filePtr)     //null pointer check
    {
        printf("Error: Unable to save profiles\n");
        return;
    }
    fwrite(profiles, sizeof(struct playerProfile), profileCount, filePtr);
    fclose(filePtr);
}

//Find or create player by username
int signIn() 
{
    int profileCount = loadProfiles(profiles);
    char newUsername[USERNAME_SIZE_MAX];
    int choice;

    while (1) 
    {
        printf("Press:\n[1] Sign in\n[2] Create an account\n");
        while (!scanf("%i", &choice) || choice != 1 && choice != 2) 
            { 
                integerOnly();
            }
        printf("Enter username: ");
        scanf("%39s", newUsername); // for USERNAME_SIZE_MAX = 40

        if (choice == 1) 
        {
            for (int i = 0; i < profileCount; i++)  
            {
                if (strcmp(profiles[i].username, newUsername) == 0) 
                {
                    activePlayer = profiles[i];
                    printf("Signed in as %s\n", activePlayer.username);
                    return profileCount;
                }
            }
            printf("Username not found. Please try again.\n");
            continue;
        } 
        else if (choice == 2) 
        {
            
            int exists = 0; // Check for duplicate username
            for (int i = 0; i < profileCount; i++) 
            {
                if (strcmp(profiles[i].username, newUsername) == 0)
                {
                    exists = 1;
                    break;
                }
            }
            if (exists) {
                printf("Username already exists. Please choose a different username.\n");
                continue;
            }

            if (profileCount >= MAX_PLAYERS) 
            {
                printf("Maximum number of profiles reached.\n");
                continue;
            }
            activePlayer = (struct playerProfile) 
            {
                .numberGuess = {0, 0},
                .hangman = {0, 0},
                .mysteryCode = {0, 0}
            };
            strcpy(activePlayer.username, newUsername);
            profiles[profileCount] = activePlayer;
            profileCount++;
            save_profiles(profiles, profileCount);
            printf("Account created for %s\n", activePlayer.username);
            return profileCount;
        } 
        else
        {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }
}

// Comparison function for qsort: compares two playerProfile structs by username (alphabetical order)
int comp(const void *a, const void *b) 
{
    // Cast the void pointers to playerProfile pointers
    const struct playerProfile *pa = (const struct playerProfile *)a;
    const struct playerProfile *pb = (const struct playerProfile *)b;
    // Use strcmp to compare usernames
    return strcmp(pa->username, pb->username);
}

void showScoreboard(struct playerProfile profiles[], int profileCount) 
{
    if (profileCount == 0) 
    {
        printf("No profiles to display.\n");
        return;
    }

    // Make a copy of the profiles array so sorting does not affect the original order
    struct playerProfile sortedProfiles[MAX_PLAYERS];
    memcpy(sortedProfiles, profiles, profileCount * sizeof(struct playerProfile));

    // Sort the copied array alphabetically by username
    qsort(sortedProfiles, profileCount, sizeof(struct playerProfile), comp);

    printf("\n%-40s | %-18s | %-20s | %-15s | %-17s | %-18s | %-20s\n", 
        "Username", 
        "Number Guess Score", "Number Guess Sessions", 
        "Hangman Score", "Hangman Sessions", 
        "Mystery Code Score", "Mystery Code Sessions");

    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Print each player's data in aligned columns
    for (int i = 0; i < profileCount; i++) {
        printf("%-40s | %-18d | %-20d | %-15d  | %-17d | %-18d | %-20d\n",
            sortedProfiles[i].username,
            sortedProfiles[i].numberGuess.score, sortedProfiles[i].numberGuess.totalSessions,
            sortedProfiles[i].hangman.score, sortedProfiles[i].hangman.totalSessions,
            sortedProfiles[i].mysteryCode.score, sortedProfiles[i].mysteryCode.totalSessions
        );
    }
    printf("\nPress any key to return to the main menu.\n");

    // Clear any leftover input in the buffer
    while (getchar() != '\n');
    // Wait for user input before returning
    getchar();
    printf("\n");
    
    return;
}