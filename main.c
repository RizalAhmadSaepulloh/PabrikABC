#include <stdio.h>
#include <stdlib.h>
#include "Peminjaman.h"
#include "ManageMenu.c"
#include "Login.c"
#include "Registration.c"
#include "KelolaKaryawan.c"
#include "KelolaPinjam.c"
#include "KelolaBarang.c"
#include "KelolaPengembalian.c"

int main(){
	int choice;
	do{
		system("cls");
		printf("--------------------------------------\n");
		printf("Aplikasi Peminjaman Barang Pabrik ABC\n");
		printf("--------------------------------------\n");
		printf("[1] Registrasi\n");
		printf("[2] Login\n");
		printf("[3] Exit\n");
		printf("--------------------------------------\n\n");
		printf("Silahkan Pilih: ");
		scanf("%d",&choice);
		switch (choice){
		case 1:
			Registration();
			break;
		case 2:
			Login();
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("Pilihan Salah. Coba lagi\n\n");
			break;
		}
	}while (choice != 3);
	return 0;
}