#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "hashtab.h"
#include "md5.h"

#define bool char
#define true 1
#define false 0
#define crypto_int long int
#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)<(y)?(x):(y)

#define RSA_RAND_LIM 50000

/* core */
crypto_int expo_mod(crypto_int x, crypto_int ex, crypto_int p);
crypto_int gcd(crypto_int a, crypto_int b, crypto_int *x, crypto_int *y);
bool ferma(crypto_int x);
crypto_int simple_rand();
crypto_int simple_rand_lim(crypto_int lim);
crypto_int random();
crypto_int DH_A_1(crypto_int *a, crypto_int *g, crypto_int *p);
crypto_int DH_B_1(crypto_int *b, crypto_int g, crypto_int p);
crypto_int DH_AB_2(crypto_int AB, crypto_int ab, crypto_int p);
crypto_int bsgs(crypto_int a, crypto_int b, crypto_int p);
crypto_int part_lint(void *m, crypto_int *len);
crypto_int inversion(crypto_int *c, crypto_int *d, crypto_int p);

/* ciphers */
crypto_int shamir(crypto_int m);
int vernam_e(char *in_file_name);
int vernam_d(char *in_file_name);
crypto_int elgamal_e(char *in_file_name);
crypto_int elgamal_d(char *in_file_name);
crypto_int RSA_e(char *in_file_name);
crypto_int RSA_d(char *in_file_name);

/* signatures */
int MDFile (FILE* inFile, MD5_CTX *mdContext);
int sgn_RSA_create(char *in_file_name);
int sgn_RSA_check(char *in_file_name);
int sgn_elgamal_create(char* in_file_name);
int sgn_elgamal_check(char* in_file_name);
int sgn_gost_create(char* in_file_name);
int sgn_gost_check(char* in_file_name);

/* poker */
struct t_players {
    crypto_int cards[2];
    int index[2];
    crypto_int crypt;
    crypto_int decrypt;
} *players;

struct t_cards {
    crypto_int id;
    bool free;
} *cards;
crypto_int p;

int poker_init(int n_players);
void poker_print_card(crypto_int id);
crypto_int poker_distrib(int p_id, char task, int index);

/* digital cache */
#define B_INIT 0
#define B_SGN 1
#define B_CHECK 2

crypto_int bank(crypto_int stage, crypto_int arg1, crypto_int arg2, crypto_int arg3);
int store(crypto_int x, crypto_int y, crypto_int z);
int buyer();

/* graph */
int graph_owner(char *fname, int a);
int graph_checker(int stage, crypto_int argsi[]);


#endif
