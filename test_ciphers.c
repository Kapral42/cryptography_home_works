#include "decl.h"

int main(int argc, const char *argv[])
{
    long int x, y, g;

    printf("Shamir\n");
    for (int i = 0; i < 5; i++) {
        x = simple_rand();
        y = shamir(x);
        printf("sent:%ld, received:%ld %s\n", x, y, x == y ? "PASSED" : "FAILED");
    }

    printf("\nVernam\n");
    char f_name[] = "files/test_file";
    if (vernam_e(f_name)) {
        printf("Vernam encode ERROR\n");
    }
    f_name[15] = '\0';
    if (vernam_d(f_name)) {
        printf("Vernam decode ERROR\n");
    }
    if (!system("diff files/test_file files/test_file.vrm.key.s > /dev/null")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }

    printf("\nEl Gamal\n");
    for (int i = 0; i < 5; i++) {
        x = random() % 256;
        y = elgamal(x);
        printf("sent:%ld, received:%ld %s\n", x, y, x == y ? "PASSED" : "FAILED");
    }

    printf("\nRSA\n");
    char f_name_rsa[] = "files/test_file";
    if (RSA_e(f_name_rsa)) {
        printf("RSA encode ERROR\n");
    }
    f_name_rsa[15] = '\0';
    if (RSA_d(f_name_rsa)) {
        printf("RSA decode ERROR\n");
    }
    if (!system("diff files/test_file files/test_file.rsa.s > /dev/null")) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }

    return 0;
}
