#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int evaluate();

int getnum() {
    int num = 0;
    char c;
    while ((c = getchar()) != EOF && isdigit(c)) 
        num = num * 10 + (c - '0');
    ungetc(c, stdin);
    return num;
}

int factor() {
    char c = getchar();
    if (c == '(') {
        int result = evaluate();
        getchar(); // пропустить ')'
        return result;
    }
    ungetc(c, stdin);
    return getnum();
}

int term() {
    int result = factor();
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '*') result *= factor();
        else if (c == '/') result /= factor();
        else {
            ungetc(c, stdin);
            break;
        }
    }
    return result;
}

int evaluate() {
    int result = term();
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '+') result += term();
        else if (c == '-') result -= term();
        else {
            ungetc(c, stdin);
            break;
        }
    }
    return result;
}

int main() {
    printf("%d\n", evaluate());
    return 0;
}
