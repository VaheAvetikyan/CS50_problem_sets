#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Get user input
    string text = get_string("Text: ");

    float letters = 0, words = 0, sentences = 0;

    // Count the letters
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
    }

    // Count the words
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    // For the last word, as ther is no space after the last sentence
    words++;

    // Count the sentences
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

    // Implement the Coleman-Liau index computing formula
    float L = letters * 100 / words;
    float S = sentences * 100 / words;
    float index_float = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(index_float);

    // Setting grade limits from first to last grades in US school system
    int first_grade = 1, last_grade = 16;

    if (index < first_grade)
    {
        printf("Before Grade %i\n", first_grade);
    }
    else if (index > last_grade)
    {
        printf("Grade %i+\n", last_grade);
    }
    else
    {
        printf("Grade %i\n", index);
    }
}