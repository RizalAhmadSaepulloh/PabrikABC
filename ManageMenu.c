#include "Peminjaman.h"
#include <stdio.h>
/*
Function Oleh: 162022054 Muhammad Ardhie Abdul Ghani
Tanggal Dibuat: 3 Juni
Tanggal Selesai: Belum Selesai
*/
void ManageMenu(){
	int choice;
	do {
		system("cls");
		printf("--------------------------------------\n");
		printf("Aplikasi Peminjaman Barang Pabrik ABC \n");
		printf("--------------------------------------\n");
		printf("[1]Kelola Data Karyawan\n");
		printf("[2]Kelola Data Barang\n");
		printf("[3]Kelola Data Peminjaman\n");
		printf("[4]Kelola Data Pengembalian\n");
		printf("[0]Log Out\n");
		printf("--------------------------------------\n\n");
		printf("Silahkan Pilih: ");
		scanf("%d",&choice);
		switch (choice){
		case 1:
			CRUDKaryawan();
			//MENCARI, MENAMBAH, MENGHAPUS, MENGEDIT, DAN MELIHAT SEMUA KARYAWAN 
			break;
		case 2:
			CRUDBarang();
			//MENCARI, MENAMBAH, MENGHAPUS, MENGEDIT, DAN MELIHAT SEMUA BARANG SERTA STATUS KESEDIAANNYA.
			break;
		case 3:
			CRUDPeminjaman();
			break;
		case 4:
			Pengembalian();
			break;
		case 0:
			main();
			break;
		default:
			printf("Masukan Anda Salah. Silahkan Ulangi.\n");
			break;
		}
	}while (choice != 4);
}