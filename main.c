#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

Stack* create_stack(int initial_size) {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->capacity = initial_size;
    s->top = -1;
    s->data = (int*)malloc(s->capacity * sizeof(int));
    return s;
}

void push(Stack *s, int value) {
    if (s->top == s->capacity - 1) {
        s->capacity *= 2;
        s->data = realloc(s->data, s->capacity * sizeof(int));
    }
    s->data[++s->top] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        fprintf(stderr, "Ошибка: стек пуст\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

int peek(const Stack *s) {
    return s->data[s->top];
}

int precedence(char op) {
    switch(op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

int evaluate(const char *expr) {
    Stack *values = create_stack(10);
    Stack *ops = create_stack(10);

    for (int i = 0; expr[i]; i++) {
        if (expr[i] == ' ') continue;

        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            push(values, num);
        } else if (expr[i] == '(') {
            push(ops, '(');
        } else if (expr[i] == ')') {
            while (peek(ops) != '(') {
                int b = pop(values);
                int a = pop(values);
                char op = pop(ops);
                switch(op) {
                    case '+': push(values, a + b); break;
                    case '-': push(values, a - b); break;
                    case '*': push(values, a * b); break;
                    case '/': push(values, a / b); break;
                }
            }
            pop(ops);
        } else {
            while (ops->top != -1 && precedence(peek(ops)) >= precedence(expr[i])) {
                int b = pop(values);
                int a = pop(values);
                char op = pop(ops);
                switch(op) {
                    case '+': push(values, a + b); break;
                    case '-': push(values, a - b); break;
                    case '*': push(values, a * b); break;
                    case '/': push(values, a / b); break;
                }
            }
            push(ops, expr[i]);
        }
    }

    while (ops->top != -1) {
        int b = pop(values);
        int a = pop(values);
        char op = pop(ops);
        switch(op) {
            case '+': push(values, a + b); break;
            case '-': push(values, a - b); break;
            case '*': push(values, a * b); break;
            case '/': push(values, a / b); break;
        }
    }

    int result = pop(values);
    free(values->data);
    free(ops->data);
    free(values);
    free(ops);
    return result;
}

int main() {
    char input[1024];
    if (fgets(input, sizeof(input), stdin) { 
        fprintf(stderr, "Ошибка чтения ввода\n");
        return 1;
    }

    char cleaned[1024];
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (!isspace(input[i]) {
            cleaned[j++] = input[i];
        }
    }
    cleaned[j] = '\0';

    printf("%d\n", evaluate(cleaned));
    return 0;
}
