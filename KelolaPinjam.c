#include "Peminjaman.h"
#include <stdio.h>
#include <string.h>

void CRUDPeminjaman()
{
    int pilihan;
    do
    {
        system("cls");
        printf("Silakan pilih:\n");
        printf("1. EDIT data peminjaman\n");
        printf("2. TAMBAH data peminjaman\n");
        printf("3. LIHAT data peminjaman\n");
        printf("4. CARI data peminjaman\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            ganti_peminjam();
            break;
        case 2:
            tambah_peminjam();
            break;
        case 3:
            lihat_peminjam();
            break;
        case 4:
            search_peminjam();
            break;
        case 0:
            ManageMenu();
            break;
        default:
            printf("PILIHAN TIDAK VALID\n");
            break;
        }
        printf("\nTekan Enter untuk Melanjutkan");
        getchar();
        getchar();
    } while (pilihan != 0);
}

void tambah_peminjam()
{
    FILE *add;
    add = fopen("databarang.txt", "r");
    FILE *fptr;
    fptr = fopen("datapinjam.txt", "a+");
    FILE *employe;
    employe = fopen("karyawan.txt", "r");
    FILE *temp;
    temp = fopen("temp.txt", "a+");

    int i = 0;
    while (fscanf(add, "%d %s %d %s %d %d", &barang[i].ID, barang[i].Nama, &barang[i].Qty, barang[i].Status,
                  &barang[i].Rak, &barang[i].Durasi) != EOF)
    {
        i++; // Membaca Barang dan Menghitung Jumlah Barang.
    }

    int k = 0;
    while (fscanf(employe, "%d %s %s %s %d", &employees[k].ID, employees[k].Nama,
                  employees[k].NomorHP, employees[k].Alamat, &employees[k].Denda) != EOF)
    {
        k++;
    }
    if (i == 0 || k == 0)
    {
        printf("Data yang diperlukan tidak mencukupi.\n");
        ManageMenu();
    }
    int x = 0;
    while (fscanf(fptr, "%d %d %s %d %s %d %d %d", &dipinjam[x].IDPinjam, &dipinjam[x].IDPeminjam, dipinjam[x].Nama,
                  &dipinjam[x].IDBrg, dipinjam[x].NamaBrg, &dipinjam[x].Qty,
                  &dipinjam[x].TGLpinjam, &dipinjam[x].TGLkembali) != EOF)
    {
        x++; // 0, 1
    }

    int IDemployee;
    int IDBarang;
    int found = 0;
    int L;
    int j;
    int valid;

invalid:
    valid = 0;
    puts("");
    system("cls");
    lihat_karyawan();
    printf("Pilih ID Karyawan yang meminjam: ");
    scanf("%d", &IDemployee);
    for (L = 0; L < k; L++)
    {
        if (IDemployee == employees[L].ID)
        {
            printf("ID Karyawan Ditemukan.\n");
            break;
        }
    }
    system("cls");
    lihat_barang();
    printf("Pilih ID Barang yang dipinjam: ");
    scanf("%d", &IDBarang);
    for (j = 0; j < i; j++)
    {
        if (IDBarang == barang[j].ID)
        {
            valid = 1;
            break;
        }
    }
    if (valid != 1)
    {
        printf("ID Karyawan atau ID Barang Tidak Valid. Tolong Ulangi.\n");
        goto invalid;
    }
    int ID;
    printf("ID Karyawan dan ID Barang Valid!");
    while (found == 0)
    {
        printf("\nBuat ID Pinjam Baru: ");
        scanf("%d", &ID);
        found = 1;
        for (L = 0; L < x; L++)
        {
            if (ID == dipinjam[L].IDPinjam)
            {
                printf("ID Sudah Dipakai\nCoba Lagi\n");
                found = 0;
            }
        }
    }
    dipinjam[x].IDPinjam = ID;
    dipinjam[x].IDBrg = barang[j].ID;
    dipinjam[x].IDPeminjam = employees[L].ID;
    strcpy(dipinjam[x].Nama, employees[L].Nama);
    strcpy(dipinjam[x].NamaBrg, barang[j].Nama);
    printf("Masukkan Jumlah yang Dipinjam: ");

notvalid:
    scanf("%d", &dipinjam[x].Qty);
    if (dipinjam[x].Qty > barang[j].Qty)
    {
        printf("Jumlah Dipinjam Melebihi Jumlah Tersedia.\nCoba Lagi.\n");
        goto notvalid;
    }
    barang[j].Qty = barang[j].Qty - dipinjam[x].Qty;
    if (barang[j].Qty == 0)
    {
        strcpy(barang[j].Status, "Kosong");
    }
    printf("Masukkan Tanggal Peminjaman: ");
    scanf("%d", &dipinjam[x].TGLpinjam);
    dipinjam[x].TGLkembali = 0;

    fprintf(fptr, "%d %d %s %d %s %d %d %d\n", dipinjam[x].IDPinjam, dipinjam[x].IDPeminjam, dipinjam[x].Nama,
            dipinjam[x].IDBrg, dipinjam[x].NamaBrg, dipinjam[x].Qty,
            dipinjam[x].TGLpinjam, dipinjam[x].TGLkembali);

    int e;
    for (e = 0; e < i; e++)
    {
        fprintf(temp, "%d %s %d %s %d %d\n", barang[e].ID, barang[e].Nama, barang[e].Qty, barang[e].Status,
                barang[e].Rak, barang[e].Durasi);
    }
    fclose(temp);
    fclose(fptr);
    fclose(add);
    fclose(employe);
    remove("databarang.txt");
    rename("temp.txt", "databarang.txt");
}

void lihat_peminjam()
{
    FILE *buka;
    buka = fopen("datapinjam.txt", "r");
    printf("===========================================================\n");
    printf("            DATA BARANG YANG SEDANG DIPINJAM               \n");
    printf("===========================================================\n");

    int x = 0;
    while (fscanf(buka, "%d %d %s %d %s %d %d %d", &dipinjam[x].IDPinjam, &dipinjam[x].IDPeminjam, dipinjam[x].Nama, &dipinjam[x].IDBrg, dipinjam[x].NamaBrg, &dipinjam[x].Qty, &dipinjam[x].TGLpinjam, &dipinjam[x].TGLkembali) != EOF)
    {
        x++;
    }
    int i;
    for (i = 0; i < x; i++)
    {
        printf("------------------------------------------------------------\n");
        printf("ID PEMINJAMAN : %d\n", dipinjam[i].IDPinjam);
        printf("ID KARYAWAN : %d\n", dipinjam[i].IDPeminjam);
        printf("NAMA KARYAWAN : %s\n", dipinjam[i].Nama);
        printf("ID BARANG : %d\n", dipinjam[i].IDBrg);
        printf("NAMA BARANG : %s\n", dipinjam[i].NamaBrg);
        printf("STOK BARANG : %d\n", dipinjam[i].Qty);
        printf("TANGGAL MEMINJAM : %d\n", dipinjam[i].TGLpinjam);
        printf("------------------------------------------------------------\n\n");
    }
    fclose(buka);
}

void search_peminjam()
{
    FILE *buka = fopen("datapinjam.txt", "r");
    int x = 0;
    while (fscanf(buka, "%d %d %s %d %s %d %d %d", &dipinjam[x].IDPinjam, &dipinjam[x].IDPeminjam, dipinjam[x].Nama,
                  &dipinjam[x].IDBrg, dipinjam[x].NamaBrg, &dipinjam[x].Qty, &dipinjam[x].TGLpinjam, &dipinjam[x].TGLkembali) != EOF)
    {
        x++;
    }
    fclose(buka);
    int CariID;
    printf("Masukkan ID Peminjaman yang akan dicari: ");
    scanf("%d", &CariID);
    printf("Hasil Pencarian: \n");
    int i;
    int found = 0;
    for (i = 0; i < x; i++)
    {
        if (CariID == dipinjam[i].IDPinjam)
        {
            found = 1;
            printf("-------------------------------------------\n");
            printf("ID PEMINJAMAN : %d\n", dipinjam[i].IDPinjam);
            printf("ID KARYAWAN : %d\n", dipinjam[i].IDPeminjam);
            printf("NAMA KARYAWAN : %s\n", dipinjam[i].Nama);
            printf("ID BARANG : %d\n", dipinjam[i].IDBrg);
            printf("NAMA BARANG : %s\n", dipinjam[i].NamaBrg);
            printf("JUMLAH DIPINJAM : %d\n", dipinjam[i].Qty);
            printf("TANGGAL MEMINJAM : %d\n", dipinjam[i].TGLpinjam);
            printf("-------------------------------------------\n\n");
            break;
        }
    }
    if (found != 1)
    {
        printf("ID Tidak Ditemukan");
    }
}

void ganti_peminjam()
{
    FILE *buka = fopen("datapinjam.txt", "r");
    int x = 0;
    while (fscanf(buka, "%d %d %s %d %s %d %d %d", &dipinjam[x].IDPinjam, &dipinjam[x].IDPeminjam, dipinjam[x].Nama, &dipinjam[x].IDBrg, dipinjam[x].NamaBrg, &dipinjam[x].Qty, &dipinjam[x].TGLpinjam, &dipinjam[x].TGLkembali) != EOF)
    {
        x++;
    }
    fclose(buka);
    int pilihID;
    printf("Masukkan ID Peminjaman yang akan diedit : \n");
    scanf("%d", &pilihID);
    FILE *edit = fopen("editpinjam.txt", "w");
    for (i = 0; i < x; i++)
    {
        if (pilihID == dipinjam[i].IDPinjam)
        {
            printf("Masukkan Tanggal Peminjaman baru: ");
            int tgl;
            scanf("%d", &tgl);
            fprintf(edit, "%d %d %s %d %s %d %d %d\n", dipinjam[i].IDPinjam, dipinjam[i].IDPeminjam, dipinjam[i].Nama,
                    dipinjam[i].IDBrg, dipinjam[i].NamaBrg, dipinjam[i].Qty, tgl, dipinjam[i].TGLkembali);
        }
        else
        {
            fprintf(edit, "%d %d %s %d %s %d %d %d\n", dipinjam[i].IDPinjam, dipinjam[i].IDPeminjam, dipinjam[i].Nama,
                    dipinjam[i].IDBrg, dipinjam[i].NamaBrg, dipinjam[i].Qty,
                    dipinjam[i].TGLpinjam, dipinjam[i].TGLkembali);
        }
    }
    fclose(edit);
    remove("datapinjam.txt");
    rename("editpinjam.txt", "datapinjam.txt");
}
