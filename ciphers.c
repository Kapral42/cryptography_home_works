#include "decl.h"

crypto_int shamir(crypto_int m)
{
    crypto_int c1, d1, x, p;

    /* A1 */
    do {
        p = simple_rand();
    } while (p <= m);
    inversion(&c1, &d1, p - 1);

    x = expo_mod(m, c1, p);

    /* B1 */
    crypto_int c2, d2;
    inversion(&c2, &d2, p - 1);
    x = expo_mod(x, c2, p);

    /* A2 */
    x = expo_mod(x, d1, p);

    /* B2 */
    x = expo_mod(x, d2, p);

    return x;
}

crypto_int elgamal_e(char* in_file_name)
{
    FILE* in_file = fopen(in_file_name, "rb");

    char* file_name = strcat(in_file_name, ".pelg");
    FILE* s_keys_file = fopen(in_file_name, "wb");
    file_name[strlen(in_file_name) - 5] = '\0';

    char* file_name = strcat(in_file_name, ".selg");
    FILE* s_keys_file = fopen(in_file_name, "wb");
    file_name[strlen(in_file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".elg");
    FILE* out_file = fopen(in_file_name, "wb");
    unsigned char byte;
    crypto_int secret_a, secret_b, g, p;
    crypto_int free_a, free_b;

    /* KEY DISTRIB */
    /* A */
    free_a = DH_A_1(&secret_a, &g, &p);
    /* B */
    free_b = DH_B_1(&secret_b, g, p);
    fwrite(&secret_b, 8, 1, s_keys_file);
    fwrite(&g, 8, 1, p_keys_file);
    fwrite(&p, 8, 1, p_keys_file);

    /* MSG SENDING */
    /* A */
    crypto_int k, r, e;

    while (!feof(in_file)) {
        if (m >= p ) { return -1; }
        k = random() % (p - 2);
        fread(&byte, 1, 1, in_file);
        if (feof(in_file)) {
            break;
        }
        r = expo_mod(g, k, p);
        e = m * expo_mod(free_b, k, p) % p;
        fwrite(&r, 8, 1, out_file);
        fwrite(&e, 8, 1, out_file);
    }

    /* Sending e and r to B */

   // printf("k = %ld\n", k);
   // printf("e = %ld\n", e);
    fclose(out_file);
    fclose(in_file);
    fclose(s_keys_file);
    fclose(p_keys_file);
    return e * expo_mod(r, p - 1 - secret_b, p) % p;
}

crypto_int elgamal_d(char *in_file_name)
{
    char *file_name = strcat(in_file_name, ".elg");
    FILE* in_file = fopen(file_name, "rb");
    file_name[strlen(file_name) - 4] = '\0';

    file_name = strcat(in_file_name, ".selg");
    FILE* s_keys_file = fopen(file_name, "rb+");
    file_name[strlen(file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".elg.s");
    FILE* out_file = fopen(file_name, "wb");
    unsigned char byte;

    crypto_int buf, r, e, g, p, secret_b;
    fread(&g, 8, 1, p_keys_file);
    fread(&p, 8, 1, p_keys_file);
    fread(&secret_b, 8, 1, s_keys_file);
    while (!feof(in_file)) {
        fread(&r, 8, 1, in_file);
        fread(&e, 8, 1, in_file);
        if (feof(in_file)) {
            break;
        }
        buf = e * expo_mod(r, p - 1 - secret_b, p) % p;
        byte = (unsigned char) buf;
        fwrite(&byte, 1, 1, out_file);
    }

    fclose(out_file);
    fclose(in_file);
    fclose(s_keys_file);
    fclose(p_keys_file);
    return 0;
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
        //rand
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

crypto_int RSA_e(char *in_file_name)
{
    FILE* in_file = fopen(in_file_name, "rb");
    char* file_name = strcat(in_file_name, ".pkey");
    FILE* p_keys_file = fopen(in_file_name, "wb");
    file_name[strlen(in_file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".skey");
    FILE* s_keys_file = fopen(in_file_name, "wb");
    file_name[strlen(in_file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".rsa");
    FILE* out_file = fopen(in_file_name, "wb");
    unsigned char byte;

    /* A */
    crypto_int p1, q1, n1, fi1, d1, c1;

    p1 = simple_rand_lim(RSA_RAND_LIM);
    q1 = simple_rand_lim(RSA_RAND_LIM);
    n1 = p1 * q1;
    fi1 = (p1 - 1)*(q1 - 1);
    inversion(&c1, &d1, fi1);
    /* B */
    crypto_int p2, q2, n2, fi2, d2, c2;

    p2 = simple_rand_lim(RSA_RAND_LIM);
    q2 = simple_rand_lim(RSA_RAND_LIM);
    n2 = p2 * q2;
    fi2 = (p2 - 1)*(q2 - 1);
    inversion(&c2, &d2, fi2);
    fwrite(&c2, 8, 1, s_keys_file);
    fwrite(&n2, 8, 1, p_keys_file);
    fwrite(&d2, 8, 1, p_keys_file);


    /* A */
    crypto_int e;
    while (!feof(in_file)) {
        fread(&byte, 1, 1, in_file);
        if (feof(in_file)) {
            break;
        }
        e = expo_mod((crypto_int)byte, d2, n2);
        fwrite(&e, 8, 1, out_file);
    }
    fclose(out_file);
    fclose(in_file);
    fclose(s_keys_file);
    fclose(p_keys_file);
    return 0;
}

crypto_int RSA_d(char *in_file_name)
{
    char *file_name = strcat(in_file_name, ".rsa");
    FILE* in_file = fopen(file_name, "rb");
    file_name[strlen(file_name) - 4] = '\0';

    file_name = strcat(in_file_name, ".pkey");
    FILE* p_keys_file = fopen(file_name, "rb+");
    file_name[strlen(file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".skey");
    FILE* s_keys_file = fopen(file_name, "rb+");
    file_name[strlen(file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".rsa.s");
    FILE* out_file = fopen(file_name, "wb");
    unsigned char byte;

    crypto_int buf, c, n;
    fread(&c, 8, 1, s_keys_file);
    fread(&n, 8, 1, p_keys_file);
    while (!feof(in_file)) {
        fread(&buf, 8, 1, in_file);
        if (feof(in_file)) {
            break;
        }
        buf = expo_mod(buf, c, n);
        byte = (unsigned char) buf;
        fwrite(&byte, 1, 1, out_file);
    }

    fclose(out_file);
    fclose(in_file);
    fclose(s_keys_file);
    fclose(p_keys_file);
    return 0;
}
