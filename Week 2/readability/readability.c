#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string str);
int count_words(string str);
int count_sentences(string str);
float coleman_Liau_index(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int index = round(coleman_Liau_index(letters, words, sentences));
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    return (0);
}

float coleman_Liau_index(int letters, int words, int sentences)
{
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return (index);
}

int count_letters(string str)
{
    int letters = 0;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (isalnum(str[i]))
        {
            letters++;
        }
    }
    return (letters);
}

int count_sentences(string str)
{
    int sentences = 0;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (str[i] == '.' || str[i] == '?' || str[i] == '!')
        {
            sentences++;
        }
    }
    return (sentences);
}

int count_words(string str)
{
    int words = 0;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (str[i] == ' ')
        {
            words++;
        }
    }
    if (words == 0)
    {
        return (words);
    }
    else
    {
        return (words + 1);
    }
}
