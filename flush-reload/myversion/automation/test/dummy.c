#include <stdio.h>
#include <unistd.h>

int foo()
{
    printf("Foo\n");
}

int bar()
{
    printf("Bar\n");
}

int main()
{
    int i;
    for(i = 0; i < 20; i++) {
        foo();
        bar();
        sleep(1);
    }
    return 0;
}
