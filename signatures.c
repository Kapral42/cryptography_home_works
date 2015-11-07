#include "decl.h"
#include "md5.h"

int MDFile (FILE* inFile, MD5_CTX *mdContext)
{
    int bytes;
    unsigned char data[1024];

    if (inFile == NULL) {
        return 1;
    }

    MD5Init (mdContext);
    while ((bytes = fread (data, 1, 1024, inFile)) != 0)
        MD5Update (mdContext, data, bytes);
    MD5Final (mdContext);
 //   MDPrint (mdContext);
 //   printf("\n");
    return 0;
}

int sgn_RSA_create(char *in_file_name)
{
    FILE* in_file = fopen(in_file_name, "rb");
    char* file_name = strcat(in_file_name, ".pkey");
    FILE* p_keys_file = fopen(in_file_name, "wb");
    file_name[strlen(in_file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".rsa_sgn");
    FILE* sgn_file = fopen(in_file_name, "wb");

    crypto_int p, q, n, fi, d, c;
    crypto_int s[16];

    p = simple_rand_lim(RSA_RAND_LIM);
    q = simple_rand_lim(RSA_RAND_LIM);
    n = p * q;
    fi = (p - 1) * (q - 1);
    inversion(&c, &d, fi);
    fwrite(&d, 8, 1, p_keys_file);
    fwrite(&n, 8, 1, p_keys_file);
  //  printf("d: %ld, n: %ld\n", d, n);

    MD5_CTX md_context;
    if (MDFile(in_file, &md_context)) {
        return 1;
    }

    for (int i = 0; i < 16; i++) {
        s[i] = expo_mod((crypto_int) md_context.digest[i], c, n);
        fwrite(&s[i], 8, 1, sgn_file);
   //     printf("s[%d] %ld ", i, s[i]);
    }
  //  printf("\n");

    fclose(sgn_file);
    fclose(in_file);
    fclose(p_keys_file);
    return 0;
}

int sgn_RSA_check(char *in_file_name)
{
    FILE* in_file = fopen(in_file_name, "rb");
    char* file_name = strcat(in_file_name, ".pkey");
    FILE* p_keys_file = fopen(in_file_name, "rb");
    file_name[strlen(in_file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".rsa_sgn");
    FILE* sgn_file = fopen(in_file_name, "rb");

    crypto_int n, d, s[16];

    MD5_CTX md_context;
    if (MDFile(in_file, &md_context)) {
        return 1;
    }

    fread(&d, 8, 1, p_keys_file);
    fread(&n, 8, 1, p_keys_file);
   // printf("d: %ld, n: %ld\n", d, n);


    int flg = 0;
    for (int i = 0; i < 16; i++) {
        fread(&s[i], 8, 1, sgn_file);
     //   printf("s[%d] %ld ", i, s[i]);
        if (md_context.digest[i] != expo_mod(s[i], d, n)) {
            flg = 1;
            break;
        }
    }

    fclose(sgn_file);
    fclose(in_file);
    fclose(p_keys_file);

    if (flg) {
        return 1;
    }

    return 0;
}


int sgn_elgamal_create(char* in_file_name)
{
    FILE* in_file = fopen(in_file_name, "rb");

    char* file_name = strcat(in_file_name, ".pelg");
    FILE* p_keys_file = fopen(in_file_name, "wb");
    file_name[strlen(in_file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".selg");
    FILE* s_keys_file = fopen(in_file_name, "wb");
    file_name[strlen(in_file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".sgn_elg");
    FILE* out_file = fopen(in_file_name, "wb");
    crypto_int secret_a, g, p;
    crypto_int free_a;

    free_a = DH_A_1(&secret_a, &g, &p);
    fwrite(&secret_a, 8, 1, s_keys_file);
    fwrite(&free_a, 8, 1, p_keys_file);
    fwrite(&g, 8, 1, p_keys_file);
    fwrite(&p, 8, 1, p_keys_file);

    crypto_int k, k_inv, r, h, s, u;

    MD5_CTX md_context;
    if (MDFile(in_file, &md_context)) {
        return 1;
    }

    inversion(&k, &k_inv, p - 1);
    for (int i = 0; i < 16; i++) {
        h = (crypto_int) md_context.digest[i];
        if ((crypto_int) h >= p ) { return -1; }
        r = expo_mod(g, k, p);
        u = (h - secret_a * r) % (p - 1);
        u += u < 0 ? p - 1 : 0;
        s = (k_inv * u) % (p - 1);
        fwrite(&r, 8, 1, out_file);
        fwrite(&s, 8, 1, out_file);
    }

    fclose(out_file);
    fclose(in_file);
    fclose(s_keys_file);
    fclose(p_keys_file);
    return 0;
}

int sgn_elgamal_check(char* in_file_name)
{
    FILE* in_file = fopen(in_file_name, "rb");

    char* file_name = strcat(in_file_name, ".pelg");
    FILE* p_keys_file = fopen(in_file_name, "rb");
    file_name[strlen(in_file_name) - 5] = '\0';

    file_name = strcat(in_file_name, ".sgn_elg");
    FILE* out_file = fopen(in_file_name, "rb");
    crypto_int g, p;
    crypto_int free_a;

    fread(&free_a, 8, 1, p_keys_file);
    fread(&g, 8, 1, p_keys_file);
    fread(&p, 8, 1, p_keys_file);

    crypto_int r, h, s;

    MD5_CTX md_context;
    if (MDFile(in_file, &md_context)) {
        return 1;
    }

    crypto_int left, right;
    int flg = 0;
    for (int i = 0; i < 16; i++) {
        h = (crypto_int) md_context.digest[i];
        if ((crypto_int) h >= p ) { return -1; }
        fread(&r, 8, 1, out_file);
        fread(&s, 8, 1, out_file);
        left = (expo_mod(free_a, r, p) * expo_mod(r, s, p)) % p;
        right = expo_mod(g, h, p);
        if (left != right) {
            flg = 1;
            break;
        }
    }

    fclose(out_file);
    fclose(in_file);
    fclose(p_keys_file);

    if (flg)
        return 1;
    return 0;
}

