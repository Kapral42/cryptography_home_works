#include "decl.h"

crypto_int expo_mod(crypto_int x, crypto_int ex, crypto_int p)
{
   crypto_int result = 1;
   for (crypto_int na = abs(ex); na > 0; na >>= 1) {
       if (na % 2 == 1) {
           result = (result * x) % p;
       }
       x = (x * x) % p;
   }
   return result % p;
}

crypto_int gcd(crypto_int a, crypto_int b, crypto_int *x, crypto_int *y)
{
    crypto_int U_array[] = {MAX(a, b), 1, 0};
    crypto_int V_array[] = {MIN(a, b), 0, 1};
    crypto_int T_array[3];
    crypto_int q, *swop_p, *U, *V, *T;

    q = MAX(a, b);
    if (q != a) {
        swop_p = x;
        x = y;
        y = swop_p;
    }

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
    if (x != NULL) {
        *x = U[1];
    }
    if (y != NULL) {
        *y = U[2];
    }
    return U[0];
}

bool ferma(crypto_int x)
{
    crypto_int a;

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

crypto_int simple_rand()
{
    crypto_int rand_v;

    srand(clock());
    while (1){
        rand_v = rand() + 1;
        if (ferma(rand_v)) {
            return rand_v;
        }
    }
    return -1;
}

crypto_int simple_rand_lim(crypto_int lim)
{
    crypto_int rand_v;

    srand(clock());
    while (1){
        rand_v = rand() % lim + 1;
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

crypto_int DH_A_1(crypto_int *a, crypto_int *g, crypto_int *p)
{
    crypto_int q = 0;
    while (!q) {
        *p = simple_rand();
        if (ferma((*p - 1) / 2)) {
            q = (*p - 1) / 2;
        }
    }
    *g = 0;
    while (!*g) {
        *g = simple_rand();
        if (*g >= *p - 1 || expo_mod(*g, q, *p) == 1) {
           *g = 0;
        }
    }
    do {
        *a = simple_rand();
    } while (*a >= *p - 1);

    if (*a == -1 || *g == -1 || *p == -1) return -1;
    crypto_int A  = expo_mod(*g, *a, *p);
    return A;
}

crypto_int DH_B_1(crypto_int *b, crypto_int g, crypto_int p)
{
    do {
        *b = simple_rand();
    } while (*b >= p - 1);
    if (*b == -1) return -1;
    crypto_int B  = expo_mod(g, *b, p);
    return B;
}

crypto_int DH_AB_2(crypto_int AB, crypto_int ab, crypto_int p)
{
    /* return Key */
    return expo_mod(AB, ab, p);
}

crypto_int bsgs(crypto_int a, crypto_int b, crypto_int p)
{
    crypto_int n = (int) sqrt (p + .0) + 1;
    crypto_int b_step, i, j, x;
    struct hashtab *h_tab;

    h_tab = hashtab_init(n + 1);
    if (h_tab == NULL) {
        return -1;
    }

    for (i = 1; i <= n; i++) {
        hashtab_push(h_tab, i, expo_mod(a, i * n, p));
    }
    for (i = 0; i <= n; ++i) {
        b_step = (expo_mod(a, i, p) * b) % p;
        j = hashtab_get_index(h_tab, b_step);
        if (j >= 0) {
            x = j * n - i;
            if (x < p)
                hashtab_free(h_tab);
                return x;
        }
    }
    hashtab_free(h_tab);
    return -1;
}

crypto_int part_lint(void *m, crypto_int *len)
{
    unsigned char *mas;
    unsigned char byte;
    crypto_int res = 0;
    int size = sizeof(crypto_int);

    if (*len < 1) {
        return -1;
    }
    mas = (unsigned char*) m;
    for (int i = 0; i < size / 2 && *len > 0; i++) {
        byte = mas[0];
        mas++;
        *len--;
        res = res << 8;
        res += byte;
    }
    return res;
}

crypto_int inversion(crypto_int *c, crypto_int *d, crypto_int p)
{
    crypto_int x, y;
    crypto_int big_c, big_d, big_p;

    do {
        *c = simple_rand();
    } while (gcd(*c, p, &x, &y) != 1);

    big_c = *c;
    big_p = p;

 //   *d = y < 0 ? p + y : y;
    *d = x < 0 ? p + x : x;
    big_d = *d;

    return (big_c * big_d) % big_p;
}
