#include "decl.h"

long int shamir(long int m)
{
    long int c1, d1, x, p;

    /* A1 */
    do {
        p = simple_rand();
    } while (p <= m);
    inversion(&c1, &d1, p - 1);

    x = expo_mod(m, c1, p);

    /* B1 */
    long int c2, d2;
    inversion(&c2, &d2, p - 1);
    x = expo_mod(x, c2, p);

    /* A2 */
    x = expo_mod(x, d1, p);

    /* B2 */
    x = expo_mod(x, d2, p);

    return x;
}

long int elgamal(long int m)
{
    long int secret_a, secret_b, g, p;
    long int free_a, free_b;

    /* KEY DISTRIB */
    /* A */
    free_a = DH_A_1(&secret_a, &g, &p);
    /* B */
    free_b = DH_B_1(&secret_b, g, p);

    p = 23;
    g = 5;
    secret_a = 19;
    secret_b = 11;
    free_b = expo_mod(g, secret_a, p);
    free_b = expo_mod(g, secret_b, p);
//    free_a = DH_AB_2(free_a, secret_b, p);
//    free_b = DH_AB_2(free_b, secret_a, p);

    /* MSG SENDING */
    /* A */
    if (m >= p ) { return -1; }
    long int k, r, e;
/*    do {
        k = simple_rand();
    } while (k > p - 2);*/
    k = 11;
    r = expo_mod(g, k, p);
    e = m * expo_mod(free_b, k, p);

    /* Sending e and r to B */

    /* B */
    printf("k = %ld\n", k);
    printf("e = %ld\n", e);
    return e * expo_mod(r, p - 1 - secret_b, p);
}

int vernam_e(char *in_file_name)
{
    FILE* in_file = fopen(in_file_name, "rb");
    char *file_name = strcat(in_file_name, ".vrm");
    FILE* encoded_file = fopen(file_name, "wb");
    file_name = strcat(in_file_name, ".key");
    FILE* keys_file = fopen(file_name, "wb");
    unsigned char byte, key, e;

    if (in_file == NULL || encoded_file == NULL || keys_file == NULL) {
        printf("\nIO file ERROR\n");
        return 1;
    }

    while (!feof(in_file)) {
        fread(&byte, 1, 1, in_file);
        if (feof(in_file)) {
            break;
        }
        key = simple_rand() % 256;
        e = byte ^ key;
        fwrite(&e, 1, 1, encoded_file);
        fwrite(&key, 1, 1, keys_file);
    }
    fclose(in_file);
    fclose(encoded_file);
    fclose(keys_file);
    return 0;
}

int vernam_d(char *in_file_name)
{
    char *file_name = strcat(in_file_name, ".vrm");
    FILE* encoded_file = fopen(file_name, "rb");
    file_name = strcat(in_file_name, ".key");
    FILE* keys_file = fopen(file_name, "rb");
    file_name = strcat(in_file_name, ".s");
    FILE* out_file = fopen(file_name, "wb");
    unsigned char byte, key, e;

    if (out_file == NULL || encoded_file == NULL || keys_file == NULL) {
        printf("\nIO file ERROR\n");
        return 1;
    }

    while (!feof(encoded_file) && !feof(keys_file)) {
        fread(&e, 1, 1, encoded_file);
        fread(&key, 1, 1, keys_file);
        if (feof(encoded_file) || feof(keys_file)) {
            break;
        }
        byte = e ^ key;
        fwrite(&byte, 1, 1, out_file);
    }
    fclose(out_file);
    fclose(encoded_file);
    fclose(keys_file);
    return 0;
}

long int RSA(long int m)
{
    /* A */
    long int p1, q1, n1, fi1, d1, c1;

    p1 = simple_rand();
    q1 = simple_rand();
    n1 = p1 * q1;
    fi1 = (p1 - 1)*(q1 - 1);
    long int res = inversion(&c1, &d1, fi1);
    printf("mod = %ld", res);
    /* B */
    long int p2, q2, n2, fi2, d2, c2;

    p2 = simple_rand();
    q2 = simple_rand();
    n2 = p2 * q2;
    fi2 = (p2 - 1)*(q2 - 1);
    inversion(&c2, &d2, fi2);

    /* A */
    long int e = expo_mod(m, d2, n2);

    /* B */
    return expo_mod(e, c2, n2);
}
