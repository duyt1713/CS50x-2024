#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_LENGTH 26

bool is_string_digit(string s);
string caesar_algorithm(string s, unsigned int k);

int main(int argc, string argv[])
{
    if (argc != 2 || !is_string_digit(argv[1]))
    {
        printf("Usage: %s key\n", argv[0]);
        return (1);
    }
    unsigned int k = (atoi(argv[1]));
    string in = get_string("plaintext:  ");
    string out = caesar_algorithm(in, k);
    printf("ciphertext: %s\n", out);
    return (0);
}

bool is_string_digit(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!(isdigit(s[i])))
        {
            return (false);
        }
    }
    return (true);
}

string caesar_algorithm(string s, unsigned int k)
{
    int len = strlen(s);
    if (len == 0)
    {
        return (s);
    }
    for (int i = 0; i < len; i++)
    {
        if (isupper(s[i]))
        {
            s[i] = 'A' + (s[i] - 'A' + k % ALPHABET_LENGTH) % ALPHABET_LENGTH;
        }
        else if (islower(s[i]))
        {
            s[i] = 'a' + (s[i] - 'a' + k % ALPHABET_LENGTH) % ALPHABET_LENGTH;
        }
    }
    return (s);
}
