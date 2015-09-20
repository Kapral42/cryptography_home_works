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

long int gcd(long int a, long int b, long int *x, long int *y)
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
    if (x != NULL && y != NULL) {
        *x = U[1];
        *y = U[2];
    }
    return U[0];
}  

bool ferma(long int x)
{
    long int a;
 //   srand(time(NULL));

    if(!(x % 2)) {
        return false;
    }
    for(int i = 0; i < 100; i++){
        a = (rand() % (x - 2)) + 2;
        if (gcd(a, x, NULL, NULL) != 1)
            return false;           
        if( expo_mod(a, x - 1, x) != 1)       
            return false;           
    }
    return true;
}

long int simple_rand()
{
    long int rand_v;
    
//    srand(time(NULL));
    while (1){
        rand_v = rand();
        if (ferma(rand_v)) {
            return rand_v;
        }
    }
    return -1; 
}

/*
*   User A  |  User B
*   a, g, p |    b
*   A=g^a%p |
*        (g,p)->
*           |  B=g^b%p
*          (A)->
*        <-(B)
*   K=B^a%p | K=A^b%p
*/

long int DH_A_1(long int *a, long int *g, long int *p)
{
    *a = simple_rand();
    *g = simple_rand();
    *p = simple_rand();
    if (*a == -1 || *g == -1 || *p == -1) return -1;
    long int A  = expo_mod(*g, *a, *p);
    return A;
}

long int DH_B_1(long int *b, long int g, long int p)
{
    *b = simple_rand();
    if (*b == -1) return -1;
    long int B  = expo_mod(g, *b, p);
    return B;
}

long int DH_AB_2(long int AB, long int ab, long int p)
{
    /* return Key */
    return expo_mod(AB, ab, p); 
}

