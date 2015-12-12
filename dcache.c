#include "decl.h"

#define N_NOMIN 9
#define N_BILS 100
#define B_RAND_MAX 1000000

int nomin[N_NOMIN] = {1, 2, 5, 10, 50, 100, 500, 1000, 5000};

struct t_safe {
    int bils_count[N_NOMIN];
    int c;
    int P;
    int Q;
};

struct t_bils {
    size_t count;
    crypto_int *list;
};

crypto_int bank_N, bank_d[N_NOMIN];

static void MD5 (crypto_int x, MD5_CTX *mdContext)
{
  int bytes = sizeof(crypto_int);

  MD5Init (mdContext);
  MD5Update (mdContext, (unsigned char*)&x, bytes);
  MD5Final (mdContext);
//  MDPrint (mdContext);
}

crypto_int bank(crypto_int stage, crypto_int arg1, crypto_int arg2, crypto_int arg3)
{
    int i, bil_i;

    /* Safe */
    //static struct t_bils bils_count[N_NOMIN];
  //  int bils_count[N_NOMIN];
    static int custom_cache;
    static crypto_int P, Q, fi, n_, n, s, h;
    static crypto_int c[N_NOMIN];

    switch (stage) {
        case B_INIT:
          /*  for (i = 0; i < N_NOMIN; i++) {
                bils_count[i] = 100;
                for (j = 0; j < N_BILS; j++) {
                    bils_count[i].list[j] = 0;
                }
            }*/
            custom_cache = (int) arg1;
            P = simple_rand_lim(RSA_RAND_LIM);
            Q = simple_rand_lim(RSA_RAND_LIM);
            bank_N = P * Q;
            fi = (P - 1)*(Q - 1);
            for (i = 0; i < N_NOMIN; i++) {
                inversion(&c[i], &bank_d[i], fi);
            }
            break;
        case B_SGN:
            n_ = arg1;
            bil_i = (int) arg2;
            if (bil_i >= 0 && custom_cache >= nomin[bil_i]) {
                    custom_cache -= nomin[bil_i];
                    return expo_mod(n_, c[bil_i], bank_N);
            }
            return -1;
        case B_CHECK:
            n = arg1;
            s = arg2;
            bil_i = arg3;

            MD5_CTX mdContext;
            MD5(n, &mdContext);
            h = 0;
            for (int k = 0; k < 16; k++) {
                h += mdContext.digest[k];
            }

            if (bil_i >= 0 && h == expo_mod(s, bank_d[bil_i], bank_N)) {
                return 0;
            }
            return 1;
    }
    return 0;
}

int store(crypto_int n, crypto_int s, crypto_int nomin)
{
    if (!bank(B_CHECK, n, s, nomin)) {
        printf("Transaction is completed successfully (%ld %ld)\n", n, s);
        return 0;
    } else {
        printf("Transaction failed (%ld %ld)\n", n, s);
    }
    return 1;
}

int buyer()
{
    int money, i, j;
    int bils[N_NOMIN];
    crypto_int n, n_, r, r_, s_, s, h;

    printf("How much money will you spend? : ");
    scanf("%d", &money);
    printf("And that's all? Spend more!!!\n");

    for (i = 0; i < N_NOMIN; i++) {
        bils[i] = 0;
    }
    i = N_NOMIN - 1;
    while (money != 0) {
        bils[i] = 0;
        bils[i] = money / nomin[i];
        if (bils[i]) {
            money -= bils[i] * nomin[i];
        }
        i--;
    }

    printf("Nominations:\n");
    for (i = 0; i < N_NOMIN; i++) {
        if (bils[i] != 0)
            printf("%d:(%d) ", nomin[i], bils[i]);
    }
    printf("\n");

    for (i = N_NOMIN - 1; i >= 0; i--) {
        for (j = 0; j < bils[i]; j++) {
            printf("__________________________%d$__________________________\n", nomin[i]);
            n = random() % B_RAND_MAX;
            inversion(&r, &r_, bank_N);

            MD5_CTX mdContext;
            MD5(n, &mdContext);
            h = 0;
            for (int k = 0; k < 16; k++) {
                h += mdContext.digest[k];
            }

            n_ = (h * expo_mod(r, bank_d[i], bank_N)) % bank_N;
            s_ = bank(B_SGN, n_, (crypto_int) i, 0);
            if (s_ < 0) {
                printf("Payment of the money from bank faild\n");
                return 1;
            }
            printf("Payment of the money from bank successfully\n");
            s = s_* r_ % bank_N;
            printf("Bank note: %d$ (%d) No(%ld %ld)\n", nomin[i], j + 1, n, s);
          //  printf("n_ %ld\n", n_);
          //  printf("s^d %ld\n", expo_mod(s, bank_d[i], bank_N));
            store(n, s, (crypto_int) i);
            printf("_________________________________________________________\n\n");
        }
    }

    return 0;
}

