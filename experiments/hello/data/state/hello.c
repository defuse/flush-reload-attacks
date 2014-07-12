#include <stdio.h>
#include <stdlib.h>

void foo() {
    int x = 3;
    int y = 4;
    x += y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    for (int i = 0; i < 300; i++) {
        x *= y;
        x += y;
        x *= y;
        x *= y;
    }
    x *= y;
    x += y;
    x *= y;
    x *= y;
    printf("H%d\n", x);
}

void bar() {
    int x = 3;
    int y = 4;
    x += y;
    x += y;
    x += y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    for (int i = 0; i < 300; i++) {
        x *= y;
        x += y;
        x *= y;
        x *= y;
    }
    x *= y;
    x += y;
    x *= y;
    x *= y;
    printf("E%d\n", x);
}

void baz() {
    int x = 3;
    int y = 4;
    x += y;
    x += y;
    x += y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    for (int i = 0; i < 300; i++) {
        x *= y;
        x += y;
        x *= y;
        x *= y;
    }
    x *= y;
    x += y;
    x *= y;
    x *= y;
    printf("L%d\n", x);
}

void barf() {
    int x = 3;
    int y = 4;
    x += y;
    x += y;
    x += y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    x += y;
    x *= y;
    x *= y;
    x += y;
    x *= y;
    for (int i = 0; i < 300; i++) {
        x *= y;
        x += y;
        x *= y;
        x *= y;
    }
    x *= y;
    x += y;
    x *= y;
    x *= y;
    printf("O%d\n", x);
}

int main(int argc, char **argv)
{
    char input[16];
    for(int i = 0; i < 1000; i++) {
        printf("Enter either H, E, L, or O:\n");
        fgets(input, 16, stdin);
        if (input[0] == 'H') {
            foo();
        } else if (input[0] == 'E') {
            bar();
        } else if (input[0] == 'L') {
            baz();
        } else if (input[0] == 'O') {
            barf();
        } else if (input[0] == 'Q') {
            exit(0);
        } else {
            printf("You're doing it wrong   x.x\n");
        }
    }
}
