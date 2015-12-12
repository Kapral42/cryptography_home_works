#include "decl.h"

#define RUN 0
#define CHECK 1

struct pair {
    int first;
    int second;
} *edges;

struct t_vert {
    crypto_int r;
    crypto_int N;
    crypto_int c;
    crypto_int d;
    crypto_int Z;
    int color;
    //ddbool *edges;
};

static int V, E;

int graph_owner(char *fname, int a)
{
    static struct t_vert *verts;
    crypto_int P, Q, fi;

    FILE* file = fopen(fname, "r");
    fscanf(file, "%d %d", &V, &E);
    edges = malloc(sizeof(struct pair) * E);
    verts = malloc(sizeof(struct t_vert) * V);

    //init adges
    for (int i = 0; i < V; i++) {
    //    verts[i].edges = (bool*) calloc(V, sizeof(bool));
        verts[i].r = random() % RSA_RAND_LIM;
        P = simple_rand_lim(RSA_RAND_LIM);
        Q = simple_rand_lim(RSA_RAND_LIM);
        verts[i].N = P * Q;
        fi = (P - 1)*(Q - 1);
        inversion(&verts[i].c, &verts[i].d, fi);
    }

    //read edges
    for (int i = 0; i < E; i++) {
        fscanf(file, "%d %d", &edges[i].first ,&edges[i].second);
        edges[i].first--;
        edges[i].second--;
 //       verts[edges[i].first].edges[edges[i].second] = 1;
   //     verts[edges[i].second].edges[edges[i].first] = 1;
        printf("Edge %d : %d <----> %d\n", i, edges[i].first, edges[i].second);
    }

    //read colors
    printf("Colors:       ");
    for (int i = 0; i < V; i++) {
        fscanf(file, "%d", &verts[i].color);
        printf("%d[%d] ", i, verts[i].color);
    }
    printf("\n");
    fclose(file);

    //call checker
    int current_e, v1, v2;
    crypto_int args[6];
    for (int i = 0; i < a * E; i++) {
        //shufle colors
        printf("Mixed colors: ");
        int colors_masks[6][3] = { {0,1,2}, {0,2,1}, {1,0,2},
                                 {1,2,0}, {2,0,1}, {2,1,0} };
        int mask = random() % 3;
        for (int i = 0; i < V; i++) {
            verts[i].color = colors_masks[mask][verts[i].color];
            crypto_int r = verts[i].r;
            r = r >> 2;
            r = r << 2;
            r += (crypto_int) verts[i].color;
            //      printf("(V %d r=%ld)\n", i, r);
            verts[i].Z = expo_mod(r, verts[i].d, verts[i].N);
            verts[i].r = r;
            printf("%d[%d] ", i, verts[i].color);
        }
        printf("\n");

        current_e = graph_checker(RUN, NULL);
        v1 = edges[current_e].first;
        v2 = edges[current_e].second;
        args[0] = verts[v1].Z;
        args[1] = verts[v1].c;
        args[2] = verts[v1].N;
        args[3] = verts[v2].Z;
        args[4] = verts[v2].c;
        args[5] = verts[v2].N;
        if (graph_checker(CHECK, args)){
            printf("Edge %d check \033[31mfailed\033[0m\n", current_e);
            return 1;
        }
        printf("Edge %d check \033[32msuccess\033[0m\n", current_e);
    }

    return 0;
}

int graph_checker(int stage, crypto_int args[])
{
    crypto_int Z1, Z2;

    switch (stage) {
        case RUN:
            return random() % E;
        case CHECK:
            Z1 = expo_mod(args[0], args[1], args[2]);
            Z2 = expo_mod(args[3], args[4], args[5]);
          //  printf("(Z1=%ld)\n", Z1);
          //  printf("(Z2=%ld)\n", Z2);
            Z1 &= 3;
            Z2 &= 3;
          //  printf("C1 %ld C2 %ld\n", Z1, Z2);
            if (Z1 == Z2)
                return 1;
            return 0;
    }
    return 0;
}
