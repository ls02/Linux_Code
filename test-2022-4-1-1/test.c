#include <stdio.h>

void HanNuoTa(char a, char b, char c, int n )
{
    if (0 == n)
    {
        return;
    }
    else
    {
        HanNuoTa(a, c, b, n - 1);

        printf("%c->%c\n", a, c);
        HanNuoTa(b, a, c, n - 1);
    }

}

int main(void)
{
    HanNuoTa('a', 'b', 'c', 3);

    return 0;
}
