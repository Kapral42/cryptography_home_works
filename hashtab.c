#include <stdlib.h>

#include "hashtab.h"

int hashtab_init(long int n)
{
    if (n < 1) {
        return 1;
    }
    tab = (struct node**) malloc(sizeof(struct node*) * n);
    if (tab == NULL) {
        return 1;
    }
    N = n;
    return 0; 
}

int hashtab_push(long int index, long int val)
{
    long int i;
    struct node *tmp_node;

    tmp_node = (struct node*) malloc(sizeof(struct node));
    if (tmp_node == NULL) {
        return 1;
    }
    tmp_node->val = val;
    tmp_node->index = index;
    tmp_node->next = NULL;

    i = val % N;
    if (tab[i] == NULL) {
        tab[i] = tmp_node;
    } else {
       /* do {
            tmp_node = tab[i]->next
        } while (tmp_node->next != NULL);*/
        tmp_node->next = tab[i];
        tab[i] = tmp_node;
    }
    return 0;
}

long int hashtab_get_index(long int val)
{
    long int i;
    struct node *tmp_node;

    i = val % N;
    tmp_node = tab[i];
    while(tmp_node != NULL) {
        if (tmp_node->val == val) {
            return tmp_node->index;
        }
        tmp_node = tmp_node->next;
    }
    return -1;
}

int hashtab_free()
{
    long int i;
    struct node *tmp_node;

    for (i = 0; i < N; i++) {
        while(tab[i] != NULL) {
            tmp_node = tab[i];
            tab[i] = tab[i]->next;
            free(tmp_node);
        }
    }
    free(tab);
    return 0;
}
