#include "functions.h"

long int expo_mod(long int x, long int ex, long int p)
{
   long int result = 1;
   for (long int na = abs(ex); na > 0; na >>= 1) {
       if (na % 2 == 1) {
           result = (result * x) % p;
       }
       x = (x * x) % p;
   }
   return result % p;
}

int gcd(long int a, long int b, long int *x, long int *y, long int *res)
{
    long int U_array[] = {a, 1, 0};
    long int V_array[] = {b, 0, 1};
    long int T_array[3];
    long int q, *swop_p, *U, *V, *T;

    U = U_array;
    V = V_array;
    T = T_array;
    while (V[0] != 0) {
        q = U[0] / V[0];
        T[0] = U[0] % V[0];
        T[1] = U[1] - q * V[1]; 
        T[2] = U[2] - q * V[2]; 
        swop_p = U;
        U = V;
        V = T;
        T = swop_p;
    }
    *res = U[0];
    *x = U[1];
    *y = U[2];
    return 0;
}  

long int simple_rand()
{
    srand(time(NULL));
    int flg = 0;
    while (!flg){
        long int rand_v = rand() * 4;
        for (long int i = 2; i < log(rand_v); i++) {
            if (rand_v % i == 0) {
                flg = 1;
                break;
            }
        }
        if (!flg) {
            return rand_v;
        } else {
            flg = 0;
        }
    }
    return -1; 
}

long int DH_A_1(long int *a long int *g, long int *p)
{
    *a = simple_rand();
    *g = simple_rand();
    *p = simple_rand();
    if (a == -1 || *g == -1 || *p == -1) return -1;
    long int A  = expo_mod(g,a,p);
    return A;
}

long int DH_A_2(long int B)
{
    return expo_mod(B, )
}

