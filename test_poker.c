#include "decl.h"

int main(int argc, const char *argv[])
{
    printf("\n Poker\n");

    if (argc == 1) {
        printf("ERROR: Please writen user count\n");
        return 1;
    }
    int users = atoi(argv[1]);
    int i, k, j;
    if (poker_init(users))
        return 1;

    /* USERS */

    for (i = 0; i < users; i++) {
        poker_distrib(i, 'S', 0);
    }
    for (i = 0; i < users; i++) {
        poker_distrib(i, 'F', 0);
    }
    for (k = 0; k < 2; k++) {
        for (i = 0; i < users; i++) {
            int d_us = (int) random() % users;
            int index = (int) poker_distrib(d_us, 'D', 0);
            for (j = 0; j < users; j++) {
                if (j != i) {
                    poker_distrib(j, 'R', index);
                }
            }
            players[i].cards[k] = poker_distrib(i, 'R', index);
        }
    }

    crypto_int table[5];
    for (i = 0; i < 5; i++) {
        int d_us = (int) random() % users;
        int index = (int) poker_distrib(d_us, 'D', 0);
        for (j = 0; j < users; j++) {
            table[i] = poker_distrib(j, 'R', index);
        }
    }

    for (i = 0; i < users; i++) {
        printf("Player %d:\n", i + 1);
        poker_print_card(players[i].cards[0]);
        poker_print_card(players[i].cards[1]);
    }

    printf("Table cards:\n");
    for (i = 0; i < 5; i++) {
        poker_print_card(table[i]);
    }

    for (i = 0; i < users; i++) {
        printf("Player %d: card1=%ld\n", i, players[i].cards[0]);
        printf("Player %d: card2=%ld\n", i, players[i].cards[1]);
    }

    for (i = 0; i < 5; i++) {
        printf("Table card %d = %ld\n", i, table[i]);
    }

    return 0;
}
