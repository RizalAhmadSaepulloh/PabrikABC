#include "Peminjaman.h"
#include <stdio.h>
#include <string.h>

void CRUDBarang(){
    int pilihan;
    do {
        system("cls");
        printf("\nSilakan pilih :\n");
        printf("1. EDIT data barang\n");
        printf("2. HAPUS data barang\n");
        printf("3. TAMBAH data barang\n");
        printf("4. LIHAT data barang\n");
        printf("5. CARI data barang\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda : ");
        scanf("%d", &pilihan);

        switch (pilihan){
            case 1:
                ganti_barang();
                break;
            case 2:
                hapus_barang();
                break;
            case 3:
                tambah_barang();
                break;
            case 4:
                lihat_barang();
                break;
            case 5:
                search_barang();
                break;
            case 0:
                ManageMenu();
            default:
                printf("PILIHAN TIDAK VALID\n");
                break;
        }
        printf("Tekan Enter Untuk Melanjutkan");
        getchar();
        getchar();
    }while (pilihan != 0);
}

void lihat_barang(){
    FILE *fptr;
    fptr = fopen("databarang.txt","r");
    int e;
    i = 0;

    while (fscanf(fptr,"%d %s %d %s %d %d",&barang[i].ID, barang[i].Nama, &barang[i].Qty, barang[i].Status,
        &barang[i].Rak,&barang[i].Durasi) != EOF){
        i++;
    }
    puts(""); //Newline
    printf("-------------------------------------------\n");
    printf("DATA - DATA BARANG\n");
    printf("-------------------------------------------\n");
    for (e = 0; e < i; e++){
        printf("-------------------------------------------\n");
        printf("ID Barang: %d\n",barang[e].ID);
        printf("Nama Barang: %s\n",barang[e].Nama);
        printf("Jumlah Tersedia: %d\n",barang[e].Qty);
        printf("Status Kesediaan: %s\n",barang[e].Status);
        printf("Nomor Rak: %d\n",barang[e].Rak);
        printf("Maksimal Lama Peminjaman (dalam hari): %d\n",barang[e].Durasi);
        printf("-------------------------------------------\n\n");
    }
    fclose(fptr);
}

void tambah_barang(){
    FILE *fptr;
    fptr = fopen("databarang.txt","a+");
    int i = 0;
    while (fscanf(fptr,"%d %s %d %s %d %d",&barang[i].ID, barang[i].Nama, &barang[i].Qty, barang[i].Status,
        &barang[i].Rak,&barang[i].Durasi) != EOF){
        i++; //Membaca Barang dan Menghitung Jumlah Barang.
    }
    int ID, e;
    printf("\nMasukkan ID Baru: ");
    scanf("%d",&ID);
    for (e = 0; e < i; e++){
        retry:
        if (ID == barang[e].ID){
            printf("ID Sudah digunakan.\n");
            printf("Masukkan ID Baru: ");
            scanf("%d",&ID);
            goto retry;
        }
    }
    barang[i].ID = ID;
    printf("Masukkan Nama Barang: ");
    scanf("%s",barang[i].Nama);
    printf("Jumlah Barang: ");
    scanf("%d",&barang[i].Qty);

    if (barang[i].Qty > 0){
        strcpy(barang[i].Status, "Tersedia");
    }
    else {
        strcpy(barang[i].Status, "Kosong");
    }
    printf("Masukkan Nomor Rak Barang: ");
    scanf("%d",&barang[i].Rak);
    printf("Masukkan Batas Waktu Peminjaman (Dalam Hari): ");
    scanf("%d",&barang[i].Durasi);

    fprintf(fptr,"%d %s %d %s %d %d\n",barang[i].ID,barang[i].Nama,barang[i].Qty,barang[i].Status,barang[i].Rak,barang[i].Durasi);
    printf("Penambahan Data Baru Berhasil\n");
    fclose(fptr);
}

void search_barang(){
    int e;
    int search;
    FILE *fptr;
    fptr = fopen("databarang.txt","r");
    while (fscanf(fptr,"%d %s %d %s %d %d",&barang[i].ID, barang[i].Nama, &barang[i].Qty, barang[i].Status,
        &barang[i].Rak,&barang[i].Durasi) != EOF){
        i++; //Membaca Barang dan Menghitung Jumlah Barang.
    }
    printf("\nMasukkan ID Barang yang Dicari: ");
    scanf("%d",&search);
    int found = 0;
    printf("Hasil Pencarian:\n");
    for (e = 0; e < i; e++){
        if (barang[e].ID == search){
            found = 1;
            printf("-------------------------------------------\n");
            printf("ID Barang: %d\n",barang[e].ID);
            printf("Nama Barang: %s\n",barang[e].Nama);
            printf("Jumlah Tersedia: %d\n",barang[e].Qty);
            printf("Status Kesediaan: %s\n",barang[e].Status);
            printf("Nomor Rak: %d\n",barang[e].Rak);
            printf("Maksimal Lama Peminjaman (dalam hari): %d\n",barang[e].Durasi);
            printf("-------------------------------------------\n\n");
            break;
        }
    }
    if (found != 1){
        printf("Tidak Ditemukan.\n");
    }
    fclose(fptr);
}
void ganti_barang(){
    FILE *fptr;
    FILE *temp;

    fptr = fopen("databarang.txt","r");
    temp = fopen("temp.txt","a+");
    
    lihat_barang();
    printf("Pilih ID Barang yang ingin diganti: ");
    int select;
    scanf("%d",&select);
    i = 0;
    int choice;
    int newrak;
    int newqty;
    int newduration;
    while (fscanf(fptr,"%d %s %d %s %d %d",&barang[i].ID, barang[i].Nama, &barang[i].Qty, barang[i].Status,
        &barang[i].Rak,&barang[i].Durasi) != EOF){
        if (barang[i].ID == select){
            retry:
            printf("\n[1]Nomor Rak\n[2]Jumlah Barang\n[3]Maks Peminjaman\n\n");
            printf("Data yang ingin diubah: ");
            scanf("%d",&choice);
            switch (choice){
                case 1:
                    printf("Masukkan Nomor Rak Baru: ");
                    scanf("%d",&newrak);
                    fprintf(temp,"%d %s %d %s %d %d\n",barang[i].ID, barang[i].Nama, barang[i].Qty,
                        barang[i].Status, newrak, barang[i].Durasi);
                    printf("Data Rak Berhasil Diubah.\n");
                    break;
                case 2:
                    printf("Masukkan Jumlah Barang Baru: ");
                    scanf("%d",&newqty);
                    fprintf(temp,"%d %s %d %s %d %d\n",barang[i].ID, barang[i].Nama, newqty,
                        barang[i].Status, barang[i].Rak, barang[i].Durasi);
                    break;
                case 3:
                    printf("Masukkan Maksimal Peminjaman Baru: ");
                    scanf("%d",&newduration);
                    fprintf(temp,"%d %s %d %s %d %d\n",barang[i].ID, barang[i].Nama, barang[i].Qty,
                        barang[i].Status, barang[i].Rak, newduration);
                    break;
                default:
                    printf("Masukkan Salah. Silakan Ulangi Lagi.\n");
                    goto retry;
                    break;
            }
        }
        else {
            fprintf(temp,"%d %s %d %s %d %d\n",barang[i].ID, barang[i].Nama, barang[i].Qty, barang[i].Status,
        barang[i].Rak, barang[i].Durasi);
        }
        i++;
    }
    fclose(fptr);
    fclose(temp);
    remove("databarang.txt");
    rename("temp.txt","databarang.txt");
}

void hapus_barang(){
    FILE *fptr;
    FILE *temp;
    fptr = fopen("databarang.txt","r");
    temp = fopen("temp.txt","a");
    i = 0;
    lihat_barang();
    printf("\nPilih ID yang ingin dihapus: ");
    int choice;
    scanf("%d",&choice);
    i = 0;
    while (fscanf(fptr,"%d %s %d %s %d %d",&barang[i].ID, barang[i].Nama, &barang[i].Qty, barang[i].Status,
        &barang[i].Rak,&barang[i].Durasi) != EOF){
        if (barang[i].ID != choice){
            fprintf(temp,"%d %s %d %s %d %d\n",barang[i].ID, barang[i].Nama, barang[i].Qty, barang[i].Status,
            barang[i].Rak, barang[i].Durasi);
        }
        i++;
    }
    fclose(fptr);
    fclose(temp);
    remove("databarang.txt");
    rename("temp.txt", "databarang.txt");
    lihat_barang();
}