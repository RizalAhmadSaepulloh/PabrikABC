#include <stdio.h>
#include <string.h>
#include "Peminjaman.h"

void Registration()
{

    FILE *fptr;
    int akun = 0;
    fptr = fopen("Adminlist.txt", "a+");
    char nama[50], username[10], password[10];
    int kode, stop;

    do
    {
        while (fscanf(fptr, "%d %s %s %s", &admin[akun].kode, admin[akun].nama, admin[akun].username,
                      admin[akun].password) != EOF)
        {
            akun++; //
        }
        printf("\nSilahkan Mendaftarkan akun\n===Daftar akun===\nID Admin: ");
        scanf("%i", &kode);
        printf("Nama Admin: ");
        scanf("%s", nama);
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        fprintf(fptr, "%i %s %s %s\n", kode, nama, username, password);

        printf("\nApakah anda ingin registrasi lagi\n1. Lanjut\n2. Kembali ke Main\nMasukan pilihan : ");
        scanf("%i", &stop);
    } while (stop != 2);
    fclose(fptr);
}