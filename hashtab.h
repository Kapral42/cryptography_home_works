#ifndef HASHTAB_H
#define HASHTAB_H

struct node
{
    long int val;
    long int index;
    struct node* next;
};

int N;
struct node **tab;

int hashtab_init(long int n);
int hashtab_push(long int index, long int val);
long int hashtab_get_index(long int val);
int hashtab_free();

#endif
