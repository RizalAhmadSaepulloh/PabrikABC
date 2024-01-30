#include <stdio.h>
#include <string.h>
#include "Peminjaman.h"

void Login()
{
    system("cls");
    FILE *fptr;
    int akun = 0;
    fptr = fopen("Adminlist.txt", "r+");
    char user[50], pass[10];
    int i = 0;
    int pilihan;
    printf("===Selamat Datang===\nSilahkan login akun admin\n");
    printf("username : ");
    scanf("%s", user);
    printf("password : ");
    scanf("%s", pass);
    while (fscanf(fptr, "%d %s %s %s", &admin[akun].kode, admin[akun].nama, admin[akun].username,
                  admin[akun].password) != EOF)
    {
        if (strcmp(user, admin[akun].username) == 0 && strcmp(pass, admin[akun].password) == 0)
        {
            printf("\nAnda berhasil login\n");
            akun++;
            ManageMenu();
            break;
        }
    }
    while (akun == 0)
    {
        printf("Login gagal. Ussername atau Password salah.\n");
        printf("Silahkan login ulang\n");
        printf("Belum Punya Akun? Silahkan Registrasi\n[1]Login ulang\n[2]Buat Akun\nPilih: ");
        scanf("%d", &pilihan);
        switch (pilihan)
        {
        case 1:
            Login();
            break;
        case 2:
            Registration();
            break;
        default:
            printf("Pilihan Anda Salah.\n");
            break;
        }
    }

    fclose(fptr);
}