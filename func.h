int menuExit()
{	
    char input;
    printf("\nPress [0] to exit to the main menu, or any other key to keep playing:\n");
    while(  getchar() != '\n');

    scanf("%c", &input); 
    if (input == '0')
        return 1;
    else
        return 0;
}

int integerOnly() //Ensures that only integers are accepted
{
    while(  getchar() != '\n');   // Clear the input buffer

    printf("There was an error receiving the number. Enter it again: ");
}