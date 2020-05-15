#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool letter_check(char *argv);
bool duplicates_check(char *argv);
int main(int argc, string argv[])
{
    // Checks for command line arguments to be 2 and non-numeric
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (letter_check(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (duplicates_check(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        string plain = get_string("plaintext: ");
        printf("ciphertext: ");

        for (int i = 0, n = strlen(plain); i < n; i++)
        {
            int j = 0;
            if (plain[i] >= 'A' && plain[i] <= 'Z')
            {
                j = plain[i] - 'A';
                if (argv[1][j] >= 'A' && argv[1][j] <= 'Z')
                {
                    printf("%c", argv[1][j]);
                }
                else
                {
                    printf("%c", argv[1][j] - ('a' - 'A'));
                }
            }
            else if (plain[i] >= 'a' && plain[i] <= 'z')
            {
                j = plain[i] - 'a';
                if (argv[1][j] >= 'a' && argv[1][j] <= 'z')
                {
                    printf("%c", argv[1][j]);
                }
                else
                {
                    printf("%c", argv[1][j] + ('a' - 'A'));
                }
            }
            else
            {
                printf("%c", plain[i]);
            }
        }
        printf("\n");
        return 0;
    }
}

// Checks every single char in argv to be letter
bool letter_check(char *argv)
{
    bool check = false;
    for (int i = 0, s = strlen(argv); i < s; i++)
    {
        if (!(argv[i] >= 'a' && argv[i] <= 'z') && !(argv[i] >= 'A' && argv[i] <= 'Z'))
        {
            check = true;
        }
    }
    return check;
}

// Checks if there are any duplicates in the key
bool duplicates_check(char *argv)
{
    bool check = false;
    for (int i = 0, n = strlen(argv); i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (argv[i] == argv[j])
            {
                check = true;
            }
        }
    }
    return check;
}
