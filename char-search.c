#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MIN_VALID_ASCII_NUM = 32;
const int MAX_VALID_ASCII_NUM = 126;
const int HEX_STRING_SIZE = 9;
const int INPUT_LENGTH = 2; // Allow for 1 char & null terminator

enum Mode
{
    INT = 0,
    HEX = 1
};

int random_integer(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

enum Mode random_mode()
{
    return (enum Mode)random_integer(0, 1);
}

void int_to_hex_string(char *hex_string, int number)
{
    snprintf(hex_string, HEX_STRING_SIZE, "%x", number);
}

void print_guess_message(enum Mode mode, int wanted_num)
{
    if (mode == INT)
    {
        printf("Guess char from int: %d\n", wanted_num);
    }
    else if (mode == HEX)
    {
        char hex_string[HEX_STRING_SIZE];
        int_to_hex_string(hex_string, wanted_num);
        printf("Guess char from hex: 0x%s\n", hex_string);
    }
}

int get_user_input(char *input_char)
{
    printf("Your guess: ");

    if (fgets(input_char, sizeof(input_char), stdin) == NULL)
    {
        if (feof(stdin))
        {
            printf("\nEOF, exiting\n");
            exit(0);
        }
        else
        {
            printf("Error reading input.\n");
            return 0;
        }
    }

    if (input_char[0] == '\n')
    {
        printf("Invalid input. Please enter a printable ASCII character.\n\n");
        return 0;
    }

    if (input_char[1] != '\n' && input_char[1] != '\0')
    {
        printf("Invalid input. Please enter only one character.\n\n");
        return 0;
    }

    int input_num = input_char[0];

    if (input_num < MIN_VALID_ASCII_NUM || input_num > MAX_VALID_ASCII_NUM)
    {
        printf("Invalid input.\n");
        return 0;
    }

    return 1;
}

void evaluate_result(int wanted_num, int input_num)
{

    if (input_num == wanted_num)
    {
        printf("\033[32mCorrect!\033[0m\n\n");
    }
    else
    {
        char wanted_char = wanted_num;
        printf("\033[31mWrong!\033[0m Solution: %c\n\n", wanted_char);
    }
}

int main()
{
    // Combine coarse (time) and fine (clock) time data via XOR for better seed
    srand((unsigned int)time(NULL) ^ (unsigned int)clock());

    while (1)
    {
        enum Mode mode = random_mode();
        int wanted_num = random_integer(MIN_VALID_ASCII_NUM, MAX_VALID_ASCII_NUM);

        print_guess_message(mode, wanted_num);

        char input_char[INPUT_LENGTH];

        if (get_user_input(input_char) == 0)
        {
            continue;
        }

        int input_num = input_char[0];

        evaluate_result(wanted_num, input_num);
    }
}
