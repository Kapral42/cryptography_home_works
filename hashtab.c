#include <stdlib.h>

#include "hashtab.h"

struct hashtab *hashtab_init(long int n)
{
    struct hashtab *h_tab;

    if (n < 1) {
        return NULL;
    }
    h_tab = malloc(sizeof(struct hashtab));
    if (h_tab == NULL) {
        return NULL;
    }
    h_tab->tab = (struct node**) malloc(sizeof(struct node*) * n);
    if (h_tab->tab == NULL) {
        return NULL;
    }
    h_tab->size = n;
    return h_tab;
}

int hashtab_push(struct hashtab *h_tab, long int index, long int val)
{
    long int i;
    struct node *tmp_node;
    struct node **tab = h_tab->tab;

    tmp_node = (struct node*) malloc(sizeof(struct node));
    if (tmp_node == NULL) {
        return 1;
    }
    tmp_node->val = val;
    tmp_node->index = index;
    tmp_node->next = NULL;

    i = val % h_tab->size;
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

long int hashtab_get_index(struct hashtab *h_tab, long int val)
{
    long int i;
    struct node *tmp_node;
    struct node **tab = h_tab->tab;

    i = val % h_tab->size;
    tmp_node = tab[i];
    while(tmp_node != NULL) {
        if (tmp_node->val == val) {
            return tmp_node->index;
        }
        tmp_node = tmp_node->next;
    }
    return -1;
}

int hashtab_free(struct hashtab *h_tab)
{
    long int i;
    struct node *tmp_node;
    struct node **tab = h_tab->tab;

    for (i = 0; i < h_tab->size; i++) {
        while(tab[i] != NULL) {
            tmp_node = tab[i];
            tab[i] = tab[i]->next;
            free(tmp_node);
        }
    }
    free(tab);
    free(h_tab);
    return 0;
}
