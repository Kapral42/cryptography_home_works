#include "decl.h"

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    printf("Test expo_mod:\n");
    {
        long int res = expo_mod(3, 100, 7);
        printf("res: %ld\n", res);
    }

    printf("\nTest gcd:\n");
    {
        long int x, y, z, a, b, res;
        a = 35; b = 18;
        z = gcd(35, 18, &x, &y);
        printf("gcd: 35 18 x=%ld y=%ld gcd=%ld\n", x, y, z);
        printf("x y check: %ld\n", a*x + b*y);
        a = 19; b = 3;
        z = gcd(19, 3, &x, &y);
        printf("gcd:19 3 x=%ld y=%ld gcd=%ld\n", x, y, z);
        printf("x y check: %ld\n", a*x + b*y);
        a = 18; b = 6;
        z = gcd(18, 6, &x, &y);
        printf("gcd: 18 6 x=%ld y=%ld gcd=%ld\n", x, y, z);
        printf("x y check: %ld\n", a*x + b*y);
        for (int i = 0; i < 5; i++) {
            a = simple_rand();
            b = simple_rand();
            res = gcd(a, b, &x, &y);
            printf("gcd: %ld, %ld  x=%ld y=%ld gcd=%ld\n", a, b, x, y, res);
            printf("x y check: %ld\n", a*x + b*y);
        }
        for (int i = 0; i < 5; i++) {
            b = simple_rand();
            a = a * 2;
            res = gcd(a, b, &x, &y);
            printf("gcd: %ld, %ld  x=%ld y=%ld gcd=%ld\n", a, b, x, y, res);
            printf("x y check: %ld\n", a*x + b*y);
        }
        for (int i = 0; i < 5; i++) {
            a = simple_rand() - 1;
            b = simple_rand() - 1;
            b = a * b;
            a++;
            res = gcd(a, b, &x, &y);
            printf("gcd: %ld, %ld  x=%ld y=%ld gcd=%ld\n", a, b, x, y, res);
            printf("x y check: %ld\n", a*x + b*y);
        }
    }

    printf("\nTest definrd MAX, MIN:\n");
    printf("max 6 8: %d\n", MAX(6,8));
    printf("min 6 8: %d\n", MIN(6,8));

    printf("\nTest ferma:\n");
    printf("27 : %d\n", ferma(27));
    printf("7 : %d\n", ferma(7));
    printf("21252211 : %d\n", ferma(21252211));
    printf("21252212 : %d\n", ferma(21252212));
    printf("4033 : %d\n", ferma(4033));
    printf("561 : %d\n", ferma(561));
    printf("41041 : %d\n", ferma(41041));

    printf("\nTest simple_rand:\n");
    for (int i = 0; i < 10; i++) {
        printf("rand: %ld\n", simple_rand());
    }
    
    {
        printf("\nTest Diffie-Hellman:\n");
        long int a, b, A, B, g, p; 
        for (int i = 0; i < 10; i++) {
            A = DH_A_1(&a, &g, &p);
            printf("g: %ld p: %ld\n", g, p);
            B = DH_B_1(&b, g, p);
            printf("Key A: %ld\n", DH_AB_2(B, a, p));
            printf("Key B: %ld\n...\n", DH_AB_2(A, b, p));
        }
    }
    
    printf("\nTest baby-step giant-step:\n");
    printf("2^x = 28 mod 37, x = %ld\n", bsgs(2, 28, 37));
    printf("6^x = 7531 mod 8101, x = %ld\n", bsgs(6, 7531, 8101));

    printf("Inversion\n");
    {
        long int x, y, g;
        for (int i = 0; i < 5; i++) {
            g = simple_rand();
            printf("%ld * %ld mod %ld = %ld\n", x, y, g, inversion(&x, &y, g));
        }
        for (int i = 0; i < 5; i++) {
            g = simple_rand();
            g *= g;
            printf("%ld * %ld mod %ld = %ld\n", x, y, g, inversion(&x, &y, g));
        }
    }

    return 0;
}
