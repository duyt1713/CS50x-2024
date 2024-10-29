#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define ALPHABET_LENGTH 26

bool is_key_valid(string key);
string substitution(string s, string key);

int main(int argc, string argv[])
{
    if (argc != 2 || !is_key_valid(argv[1]))
    {
        printf("Usage: %s key\n", argv[0]);
        return (1);
    }
    string key = argv[1];
    string in = get_string("plaintext:  ");
    string out = substitution(in, key);
    printf("ciphertext: %s\n", out);
}

bool is_key_valid(string key)
{
    int n = strlen(key);
    if (n != ALPHABET_LENGTH)
    {
        return (false);
    }
    for (int i = 0; i < n; i++)
    {
        if (!(isalpha(key[i])))
        {
            return (false);
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                return (false);
            }
        }
    }
    return (true);
}

string substitution(string s, string key)
{
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        for (int j = 0; j < ALPHABET_LENGTH; j++)
        {
            if (isupper(s[i]) && s[i] == toupper(alphabet[j]))
            {
                s[i] = toupper(key[j]);
                break;
            }
            else if (islower(s[i]) && s[i] == tolower(alphabet[j]))
            {
                s[i] = tolower(key[j]);
                break;
            }
        }
    }
    return (s);
}
