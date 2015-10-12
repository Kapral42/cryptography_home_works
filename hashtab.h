#ifndef HASHTAB_H
#define HASHTAB_H

struct node
{
    long int val;
    long int index;
    struct node* next;
};

struct hashtab
{
    struct node **tab;
    long int size;
};


struct hashtab *hashtab_init(long int n);
int hashtab_push(struct hashtab *h_tab, long int index, long int val);
long int hashtab_get_index(struct hashtab *h_tab, long int val);
int hashtab_free(struct hashtab *h_tab);

#endif
