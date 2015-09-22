#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "hashtab.h"

#define bool char
#define true 1
#define false 0
#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)<(y)?(x):(y)

long int expo_mod(long int x, long int ex, long int p);
long int gcd(long int a, long int b, long int *x, long int *y);
bool ferma(long int x);
long int simple_rand();
long int DH_A_1(long int *a, long int *g, long int *p);
long int DH_B_1(long int *b, long int g, long int p);
long int DH_AB_2(long int AB, long int ab, long int p);
long int bsgs(long int a, long int b, long int p);

#endif
