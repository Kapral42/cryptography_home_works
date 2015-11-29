#include "decl.h"

#define N_CARDS 52

int poker_init(int n_players)
{
    if (n_players * 2 + 5 > N_CARDS) {
        printf("POKER ERROR: need more cards;\n");
        return 1;
    }

    players = malloc(sizeof(struct t_players) * n_players);
    cards = malloc(sizeof(struct t_cards) * n_players);

    if (players == NULL || cards == NULL) {
        return 1;
    }

    for (int i = 2; i <= N_CARDS + 1; i++) {
        cards[i - 1].id = i;
        cards[i - 1].free = 1;
    }

    p = simple_rand();

    return 0;
}

void poker_print_card(crypto_int id)
{
    if (id > N_CARDS || id <= 0) {
        printf("POKER PRINT ERROR: incorrect id card\n");
        return;
    }

    //char *colors_list[] = {"Spades" ,"Hearts", "Clubs", "Diamonds"};
    char *capture_list[] = {"♠ " ,"♥ ", "♣ ", "♦ "};
    char *name_list[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    id -= 2;
    crypto_int color = id / 13;
    crypto_int name = id % 13;

    printf("------------------\n");
    printf("\n\t%s\n",capture_list[color]);
    printf("\n\t%s\n",name_list[name]);
    printf("------------------\n");
}

void poker_shuffle()
{
    int index;
    crypto_int swap_id;
    bool swap_free;
    for (int i = 0; i < N_CARDS; i++) {
        index = (int) random() % N_CARDS;
        swap_id = cards[i].id;
        swap_free = cards[i].free;
        cards[i].id = cards[index].id;
        cards[i].free = cards[index].free;
        cards[index].id = swap_id;
        cards[index].free = swap_free;
    }
}

/* S - start
 * F - shuffle
 * D - distribution
 * R - recovery
 */
crypto_int poker_distrib(int p_id, char task, int index)
{
    int i;
    switch (task) {
        case 'S':
            inversion(&players[p_id].crypt, &players[p_id].decrypt, p - 1);
            break;
        case 'F':
            for (i = 0; i < N_CARDS; i++) {
                cards[i].id = expo_mod(cards[i].id, players[p_id].crypt, p);
            }
            poker_shuffle();
            break;
        case 'D':
            do {
            i = (int) random() % N_CARDS;
            } while (!cards[i].free);
            cards[i].free = 0;
            return i;
            break;
        case 'R':
            if (cards[index].free) {
                printf("POKER RECOVERY ERROR: this card is free\n");
            }
            cards[index].id = expo_mod(cards[index].id, players[p_id].decrypt, p);
            return cards[index].id;
            break;
    }
    return 0;
}


