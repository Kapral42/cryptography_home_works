#include "decl.h"

int main(int argc, const char *argv[])
{
    int a;
/*
    printf("bit test 1\n");
    int x = 7;
    x = x >> 2;
    x = x << 2;
    printf("%d\n",x);
    x += 2;
    printf("%d\n",x);
    x &= 3;
    printf("%d\n",x);
*/
    printf("Case 1\n");
    scanf("%d", &a);
    graph_owner("files/graph1", a);

    printf("\nCase 2\n");
    scanf("%d", &a);
    graph_owner("files/graph2", a);

    return 0;
}
