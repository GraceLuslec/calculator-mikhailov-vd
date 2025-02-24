#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int parse_expression();
int parse_term();
int parse_factor();


char *input;
int position = 0;


void next_char() {
    position++;
}


int parse_expression() {
    int result = parse_term();
    while (input[position] == '+' || input[position] == '-') {
        char op = input[position];
        next_char();
        int term = parse_term();
        if (op == '+') result += term;
        else result -= term;
    }
    return result;
}


int parse_term() {
    int result = parse_factor();
    while (input[position] == '*' || input[position] == '/') {
        char op = input[position];
        next_char();
        int factor = parse_factor();
        if (op == '*') result *= factor;
        else result /= factor;
    }
    return result;
}


int parse_factor() {
    int result;
    if (input[position] == '(') {
        next_char();
        result = parse_expression();
        if (input[position] != ')') {
            fprintf(stderr, "Ошибка: ожидалась закрывающая скобка\n");
            exit(1);
        }
        next_char();
    } else if (isdigit(input[position])) {
        result = 0;
        while (isdigit(input[position])) {
            result = result * 10 + (input[position] - '0');
            next_char();
        }
    } else {
        fprintf(stderr, "Ошибка: неверный символ '%c'\n", input[position]);
        exit(1);
    }
    return result;
}

int main() {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Ошибка чтения ввода\n");
        return 1;
    }


    input = buffer;
    position = 0;
    while (input[position] != '\0') {
        if (isspace(input[position])) {
            next_char();
        } else {
            break;
        }
    }

    int result = parse_expression();
    printf("%d\n", result);
    return 0;
}
