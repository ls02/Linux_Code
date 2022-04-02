#include <stdio.h>

void Hanoi(char a, char b, char c, int n )
{
    if (0 == n)
    {
        return;
    }
    else
    {
        Hanoi(a, c, b, n - 1);

        printf("%c->%c\n", a, c);
        Hanoi(b, a, c, n - 1);
    }

}

int main(void)
{
    Hanoi('a', 'b', 'c', 3);

    return 0;
}
