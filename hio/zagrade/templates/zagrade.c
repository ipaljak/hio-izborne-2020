#include <stdio.h>

int main() {
    int n, odgovor;
    scanf("%d", &n);

    printf("? 1 6\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("? 1 2\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("? 2 4\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("? 2 5\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("? 3 4\n");
    fflush(stdout);
    scanf("%d", &odgovor);

    printf("! ((()))\n");
    fflush(stdout);

    return 0;
}
