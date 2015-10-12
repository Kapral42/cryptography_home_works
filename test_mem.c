#include "decl.h"

int main(int argc, const char *argv[])
{
    long int mas[2] = {1111111111, 1222222222};
    long int x;
    long int size = sizeof(long int) * 2;

    printf("size long int: %ld\n", sizeof(long int));
    printf("size int: %ld\n", sizeof(int));
    printf("size char: %ld\n", sizeof(char));

    x = part_lint((void*) mas, &size);
    printf("1:\"%ld\"", x);
    x = part_lint((void*) mas, &size);
    printf("2:\"%ld\" \n", x);
    return 0;
}
