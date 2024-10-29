#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    const int *lens;
    int num_lens;
    const int *starts;
    int num_starts;
} CardInfo;

bool len_check(int len, const CardInfo *card_info);
bool start_check(int start, const CardInfo *card_info);
bool card_check(int len, int start, const CardInfo *card_info);
int sum_indices(const char *str, bool even);
int multiply_and_sum(const char *str, bool even);
void validate_card(const char *str, int len, int start, const CardInfo *amex_info,
                   const CardInfo *master_info, const CardInfo *visa_info);

int main(void)
{
    const int amex_lens[] = {15};
    const int amex_starts[] = {34, 37};
    const int master_lens[] = {16};
    const int master_starts[] = {51, 52, 53, 54, 55};
    const int visa_lens[] = {13, 16};
    const int visa_starts[] = {40, 41, 42, 43, 44, 45, 46, 47, 48, 49};

    CardInfo amex_info = {.lens = amex_lens,
                          .num_lens = sizeof(amex_lens) / sizeof(amex_lens[0]),
                          .starts = amex_starts,
                          .num_starts = sizeof(amex_starts) / sizeof(amex_starts[0])};
    CardInfo master_info = {.lens = master_lens,
                            .num_lens = sizeof(master_lens) / sizeof(master_lens[0]),
                            .starts = master_starts,
                            .num_starts = sizeof(master_starts) / sizeof(master_starts[0])};
    CardInfo visa_info = {.lens = visa_lens,
                          .num_lens = sizeof(visa_lens) / sizeof(visa_lens[0]),
                          .starts = visa_starts,
                          .num_starts = sizeof(visa_starts) / sizeof(visa_starts[0])};
    long long num;
    char str[50];
    do
    {
        num = get_long_long("Number: ");
    }
    while (num < 0);

    sprintf(str, "%lld", num);
    int len = strlen(str);
    int start = (str[0] - '0') * 10 + (str[1] - '0');

    validate_card(str, len, start, &amex_info, &master_info, &visa_info);
    return 0;
}

bool len_check(int len, const CardInfo *card_info)
{
    for (int i = 0; i < card_info->num_lens; i++)
    {
        if (len == card_info->lens[i])
        {
            return (true);
        }
    }
    return (false);
}

bool start_check(int start, const CardInfo *card_info)
{
    for (int i = 0; i < card_info->num_starts; i++)
    {
        if (start == card_info->starts[i])
        {
            return (true);
        }
    }
    return (false);
}

bool card_check(int len, int start, const CardInfo *card_info)
{
    return (len_check(len, card_info) && start_check(start, card_info));
}

int sum_indices(const char *str, bool even)
{
    int sum = 0;
    int len = strlen(str);
    for (int i = even ? 0 : 1; i < len; i += 2)
    {
        sum += str[i] - '0';
    }
    return (sum);
}

int multiply_and_sum(const char *str, bool even)
{
    int sum = 0;
    int len = strlen(str);
    for (int i = even ? 0 : 1; i < len; i += 2)
    {
        int multiply = (str[i] - '0') * 2;
        if (multiply > 9)
        {
            multiply = (multiply / 10) + (multiply % 10);
        }
        sum += multiply;
    }
    return (sum);
}

void validate_card(const char *str, int len, int start, const CardInfo *amex_info,
                   const CardInfo *master_info, const CardInfo *visa_info)
{
    int mulandsum = 0;
    int othersum = 0;

    if (card_check(len, start, amex_info))
    {
        mulandsum = multiply_and_sum(str, false);
        othersum = sum_indices(str, true);

        if ((mulandsum + othersum) % 10 == 0)
        {
            printf("AMEX\n");
            return;
        }
    }
    if (card_check(len, start, master_info))
    {
        mulandsum = multiply_and_sum(str, true);
        othersum = sum_indices(str, false);

        if ((mulandsum + othersum) % 10 == 0)
        {
            printf("MASTERCARD\n");
            return;
        }
    }
    if (card_check(len, start, visa_info))
    {
        if (len == 13)
        {
            mulandsum = multiply_and_sum(str, false);
            othersum = sum_indices(str, true);
        }
        else if (len == 16)
        {
            mulandsum = multiply_and_sum(str, true);
            othersum = sum_indices(str, false);
        }

        if ((mulandsum + othersum) % 10 == 0)
        {
            printf("VISA\n");
            return;
        }
    }
    printf("INVALID\n");
    return;
}
