#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool digits(string v);

int main(int argc, string argv[])
{
    // Check that program was run with one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (digits(argv[1]) == true)
    {
        // Prompt user for a string
        string plaintext = get_string("plaintext: ");
        // Convert string argv to int
        int k = atoi(argv[1]);
        printf("ciphertext: ");
        // Loop for every charackter of the length of plaintext
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            // Debugging printf("n = %i\n i = %i\n", n, i);
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            {
                int uppercase = plaintext[i] + k % ('Z' - 'A' + 1);
                if (uppercase > 'Z')
                {
                    printf("%c", uppercase - ('Z' - 'A' + 1));
                }
                else
                {
                    printf("%c", uppercase);
                }
            }
            else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            {
                int lowercase = plaintext[i] + k % ('z' - 'a' + 1);
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
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool digits(string v)
{
    bool finalCheck;

    for (int i = 0, c = strlen(v); i < c; i++)
    {
        if (v[i] >= '0' && v[i] <= '9')
        {
            finalCheck = true;
            // Debugging printf("%i, %s\n", v[i], finalCheck?"True":"False");
        }
        else
        {
            finalCheck = false;
            // Debugging printf("%c, %s\n", v[i], finalCheck?"True":"False");
            break;
        }
    }
    return finalCheck;
}