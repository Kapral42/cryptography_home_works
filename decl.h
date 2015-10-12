#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "hashtab.h"

#define bool char
#define true 1
#define false 0
#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)<(y)?(x):(y)

/* core */
long int expo_mod(long int x, long int ex, long int p);
long int gcd(long int a, long int b, long int *x, long int *y);
bool ferma(long int x);
long int simple_rand();
long int DH_A_1(long int *a, long int *g, long int *p);
long int DH_B_1(long int *b, long int g, long int p);
long int DH_AB_2(long int AB, long int ab, long int p);
long int bsgs(long int a, long int b, long int p);
long int part_lint(void *m, long int *len);
long int inversion(long int *c, long int *d, long int p);

/* ciphers */
long int shamir(long int m);
int vernam_e(char *in_file_name);
int vernam_d(char *in_file_name);
long int elgamal(long int m);
long int RSA(long int m);

#endif
