#include "PEMINJAMAN.h"
#include <stdio.h>
#include <string.h>

void CRUDKaryawan()
{
    int pilihan;
    do
    {
        system("cls");
        printf("\nSilakan pilih :\n");
        printf("1. EDIT karyawan\n");
        printf("2. HAPUS karyawan\n");
        printf("3. TAMBAH karyawan\n");
        printf("4. VIEW karyawan\n");
        printf("5. SEARCH karyawan\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda : ");
        scanf("%d", &pilihan);
        switch (pilihan)
        {
        case 1:
            ganti_karyawan();
            break;
        case 2:
            hapus_karyawan();
            break;
        case 3:
            tambah_karyawan();
            break;
        case 4:
            lihat_karyawan();
            break;
        case 5:
            search_karyawan();
            break;
        case 0:
            printf("ANDA KELUAR\n");
            ManageMenu();
            break;
        default:
            printf("PILIHAN TIDAK VALID\n");
        }
        printf("\nTekan Enter untuk Melanjutkan");
        getchar();
        getchar();
    } while (pilihan != 6);
}

void ganti_karyawan()
{
    int e = 0;
    FILE *baca = fopen("karyawan.txt", "r");
    while (fscanf(baca, "%d %s %s %s %d\n", &employees[e].ID, employees[e].Nama, employees[e].NomorHP, employees[e].Alamat,&employees[e].Denda) != EOF)
    {
        e++;
    }

    fclose(baca);

    FILE *edit = fopen("edit.txt", "w");
    if (edit == NULL)
    {
        printf("Gagal membuka file\n");
        return;
    }

    int ID;
    char nohp[50];
    char alamat[50];

    printf("masukkan kode yang akan diedit : ");
    scanf("%d", &ID);

    for (i = 0; i < e; i++)
    {
        if (ID == employees[i].ID)
        {
            int pilih;
            printf("masukkan pilihan yang akan di edit : \n[1]Nomor Kontak\n[2]Alamat\nPilih >>>");
            scanf("%d", &pilih);

            switch (pilih)
            {
            case 1:
                printf("Masukkan No HP : ");
                scanf("%s", nohp);
                fprintf(edit, "%d %s %s %s %d\n", employees[i].ID, employees[i].Nama, nohp, employees[i].Alamat, employees[i].Denda);
                break;
            case 2:
                printf("Masukkan Alamat: ");
                scanf("%s", alamat);
                fprintf(edit, "%d %s %s %s %d\n", employees[i].ID, employees[i].Nama, employees[i].NomorHP, alamat, employees[i].Denda);
                break;
            default:
                printf("pilihan tidak valid\n");
                i--;
                break;
            }
        }
        else
        {
            fprintf(edit, "%d %s %s %s %d\n", employees[i].ID, employees[i].Nama, employees[i].NomorHP, employees[i].Alamat, employees[i].Denda);
        }
    }

    fclose(edit);
    remove("karyawan.txt");
    rename("edit.txt", "karyawan.txt");
}

void hapus_karyawan()
{
    int ID;
    int j;
    printf("Masukkan ID karyawan yang akan dihapus : ");
    scanf("%d", &ID);

    FILE *view = fopen("karyawan.txt", "r");

    int i = 0;
    while (fscanf(view, "%d %s %s %s %d\n", &employees[i].ID, employees[i].Nama, employees[i].NomorHP, employees[i].Alamat, &employees[i].Denda) != EOF)
    {
        i++;
    }

    fclose(view);

    FILE *rewrite = fopen("hapus.txt", "w");
    if (rewrite == NULL)
    {
        printf("Gagal membuka file\n");
        return;
    }
    int e;
    for (e = 0; e < i; e++)
    {
        if (ID != employees[e].ID)
        {
            fprintf(rewrite, "%d %s %s %s %d\n", employees[e].ID, employees[e].Nama, employees[e].NomorHP, employees[e].Alamat, employees[e].Denda);
        }
    }

    fclose(rewrite);
    remove("karyawan.txt");
    rename("hapus.txt", "karyawan.txt");
}

void tambah_karyawan()
{
    FILE *add = fopen("karyawan.txt", "a");
    if (add == NULL)
    {
        printf("Gagal membuka file\n");
        return;
    }

    int ID;
    char nama[50];
    char nohp[50];
    char alamat[50];
    int i = 0;
    while (fscanf(add, "%d %s %s %s %d\n", &employees[i].ID, employees[i].Nama, employees[i].NomorHP, employees[i].Alamat, &employees[i].Denda) != EOF)
    {
        i++;
    }
    int j;
addID:
    printf("masukkan ID : ");
    scanf("%d", &ID);

    // Check if ID already exists
    for (j = 0; j < i; j++)
    {
        if (ID == employees[j].ID)
        {
            printf("ID sudah ada. Masukkan ID lain.\n");
            goto addID;
        }
    }

    printf("masukkan nama : ");
    scanf("%s", nama);
    printf("Masukkan No HP : ");
    scanf("%s", nohp);
    printf("Masukkan Alamat: ");
    scanf("%s", alamat);

    fprintf(add, "%d %s %s %s 0\n", ID, nama, nohp, alamat);
    fclose(add);
}

void lihat_karyawan()
{
    int e;
    FILE *baca = fopen("karyawan.txt", "r");
    if (baca == NULL)
    {
        printf("Gagal membuka file\n");
        return;
    }

    int i = 0;
    while (fscanf(baca, "%d %s %s %s %d\n", &employees[i].ID, employees[i].Nama, employees[i].NomorHP, employees[i].Alamat, &employees[i].Denda) != EOF)
    {
        i++;
    }

    printf("-------------------------------------------\n");
    printf("DATA - DATA KARYAWAN\n");
    printf("-------------------------------------------\n");
    for (e = 0; e < i; e++)
    {
        printf("-------------------------------------------\n");
        printf("ID Pegawai: %d\n", employees[e].ID);
        printf("Nama Pegawai: %s\n", employees[e].Nama);
        printf("Nomor Kontak: %s\n", employees[e].NomorHP);
        printf("Alamat Rumah: %s\n", employees[e].Alamat);
        printf("Denda (Rp.): %d\n", employees[e].Denda);
        printf("-------------------------------------------\n");
    }
    fclose(baca);
}

void search_karyawan()
{
    FILE *baca = fopen("karyawan.txt", "r");
    if (baca == NULL)
    {
        printf("Gagal membuka file\n");
        return;
    }

    int i = 0;
    int e;
    while (fscanf(baca, "%d %s %s %s %d\n", &employees[i].ID, employees[i].Nama, employees[i].NomorHP, employees[i].Alamat ,&employees[i].Denda) != EOF)
    {
        i++;
    }

    int ID;
    printf("masukkan kode yang akan dicari : ");
    scanf("%d", &ID);

    for (e = 0; e < i; e++)
    {
        if (ID == employees[e].ID)
        {
            printf("-------------------------------------------\n");
            printf("ID Pegawai: %d\n", employees[e].ID);
            printf("Nama Pegawai: %s\n", employees[e].Nama);
            printf("Nomor Kontak: %s\n", employees[e].NomorHP);
            printf("Alamat Rumah: %s\n", employees[e].Alamat);
            printf("Denda (Rp.): %d\n", employees[e].Denda);
            printf("-------------------------------------------\n");
        }
    }

    fclose(baca);
}