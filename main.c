#include "functions.h"

int main(int argc, const char *argv[])
{
    long int res = expo_mod(3, 100, 7);
    printf("res: %ld\n", res);


    long int x, y, z;
    gcd(35, 18, &x, &y, &z);
    printf("gcd: x=%ld y=%ld gcd=%ld\n", x, y, z);
    gcd(19, 3, &x, &y, &z);
    printf("gcd: x=%ld y=%ld gcd=%ld\n", x, y, z);
    gcd(18, 6, &x, &y, &z);
    printf("gcd: x=%ld y=%ld gcd=%ld\n", x, y, z);
    
    return 0;
}
