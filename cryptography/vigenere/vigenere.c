#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool argv_check(string argv);
int shift(char c);
int main(int argc, string argv[])
{
    // Checks for command line arguments to be 2 and non-numeric
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else if (argv_check(argv[1]))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else
    {
        string plain = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int j = -1, i = 0, str = strlen(plain); i < str; i++)
        {
            // Get an iteration inside the loop for the shiftkey
            int len = strlen(argv[1]);
            if ((plain[i] >= 'a' && plain[i] <= 'z') || (plain[i] >= 'A' && plain[i] <= 'Z'))
            {
                j++;
            }
            if (i >= len && ((plain[i] >= 'a' && plain[i] <= 'z') || (plain[i] >= 'A' && plain[i] <= 'Z')))
            {
                j = j % len;
            }
            int key = shift(argv[1][j]);

            // Shift every charackter and print out
            if (plain[i] >= 'A' && plain[i] <= 'Z')
            {
                int uppercase = plain[i] + key % ('Z' - 'A' + 1);
                if (uppercase > 'Z')
                {
                    printf("%c", uppercase - ('Z' - 'A' + 1));
                }
                else
                {
                    printf("%c", uppercase);
                }
            }
            else if (plain[i] >= 'a' && plain[i] <= 'z')
            {
                int lowercase = plain[i] + key % ('z' - 'a' + 1);
                if (lowercase > 'z')
                {
                    printf("%c", lowercase - ('z' - 'a' + 1));
                }
                else
                {
                    printf("%c", lowercase);
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

// Checks every single char in argv to be non-number
bool argv_check(string argv)
{
    bool check = false;
    for (int i = 0, s = strlen(argv); i < s; i++)
    {
        if (argv[i] >= '0' && argv[i] <= '9')
        {
            check = true;
        }
    }
    return check;
}

// Makes input charackter a number key to shift the plaintext
int shift(char c)
{
    int keynum;
    if (c >= 'a' && c <= 'z')
    {
        keynum = c - 'a';
    }
    else
    {
        keynum = c - 'A';
    }
    return keynum;
}