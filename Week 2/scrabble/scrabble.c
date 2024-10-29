#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string str_toupper(string str);
int calculate_score(string str);
int calculate_point(char str);

int main(void)
{
    string word1 = str_toupper(get_string("Player 1: "));
    string word2 = str_toupper(get_string("Player 2: "));

    int score1 = calculate_score(word1);
    int score2 = calculate_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    return (0);
}

string str_toupper(string str)
{
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        str[i] = toupper(str[i]);
    }
    return (str);
}

int calculate_score(string str)
{
    int score = 0;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        score += calculate_point(str[i]);
    }
    return (score);
}

int calculate_point(char c)
{
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int points[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                          1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int point = 0;
    for (int i = 0, n = strlen(alphabet); i < n; i++)
    {
        if (c == alphabet[i])
        {
            point += points[i];
        }
    }
    return (point);
}
