#include "decl.h"

int main(int argc, const char *argv[])
{
    printf("\nRSA signature\n");
    char f_name_rsa[] = "files/test_file";
    if (sgn_RSA_create(f_name_rsa)) {
        printf("RSA create signature ERROR\n");
    }
    f_name_rsa[15] = '\0';
    if (sgn_RSA_check(f_name_rsa)) {
        printf("RSA check signature ERROR\n");
    } else {
        printf("PASSED\n");
    }

    printf("\nEl Gamal signature\n");
    char f_name_lgm[] = "files/test_file";
    if (sgn_elgamal_create(f_name_lgm)) {
        printf("El Gamal create signature ERROR\n");
    }
    f_name_lgm[15] = '\0';
    if (sgn_elgamal_check(f_name_lgm)) {
        printf("El Gamal check signature ERROR\n");
    } else {
        printf("PASSED\n");
    }

    printf("\nGOST signature\n");
    char f_name_gst[] = "files/test_file";
    if (sgn_gost_create(f_name_gst)) {
        printf("GOST create signature ERROR\n");
    }
    f_name_gst[15] = '\0';
    if (sgn_gost_check(f_name_gst)) {
        printf("GOST check signature ERROR\n");
    } else {
        printf("PASSED\n");
    }

    return 0;
}
