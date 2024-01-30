#include <stdio.h>
#include <string.h>
#include "Peminjaman.h"

void Pengembalian(){
	int choice;
	do{
		system("cls");
		int ID;
		printf("Masukkan ID Pinjaman yang akan dikembalikan: ");
		scanf("%d",&ID);

		FILE *data = fopen("karyawan.txt","r");
		FILE *brg = fopen("databarang.txt","r");
		FILE *pinjam = fopen("datapinjam.txt", "r");
		FILE *fptr = fopen("datakembalian.txt","a");
		
		FILE *temp = fopen("temp.txt","a");
		FILE *temp2 = fopen("temp2.txt","a");
		FILE *temp3 = fopen("temp3.txt","a");

		int x = 0;
		while(fscanf(pinjam,"%d %d %s %d %s %d %d %d",&dipinjam[x].IDPinjam,&dipinjam[x].IDPeminjam, dipinjam[x].Nama,
        	&dipinjam[x].IDBrg, dipinjam[x].NamaBrg, &dipinjam[x].Qty, 
        	&dipinjam[x].TGLpinjam, &dipinjam[x].TGLkembali) != EOF){
        	x++;//MEMBACA DATA PEMINJAMAN DAN MENGHITUNG JUMLAH PEMINJAM
    	}
    	if (x == 0){
    		ManageMenu();
    	}
    	int i = 0;
    	while (fscanf(brg,"%d %s %d %s %d %d",&barang[i].ID, barang[i].Nama, &barang[i].Qty, barang[i].Status,
				&barang[i].Rak,&barang[i].Durasi) != EOF)
		{
			i++;
		}
		int j = 0;
		while (fscanf(data, "%d %s %s %s %d\n", &employees[j].ID, 
			employees[j].Nama, employees[j].NomorHP, employees[j].Alamat, &employees[j].Denda) != EOF){
    	    j++; //MEMBACA DATA KARYAWAN DAN MENGHITUNG JUMLAH KARYAWAN
    	}
    	int found = 0;
    	int denda;
    	int hasil = 0;
	    int baru = 0;
	    int kembali;
	    int k;

	    //MENCARI DATA PINJAM
    	for (k = 0; k < x; k++){
    		if (ID == dipinjam[k].IDPinjam){
    			found = 1;
    			printf("-------------------------------------------\n");
				printf("ID PEMINJAMAN : %d\n", dipinjam[k].IDPinjam);
				printf("ID KARYAWAN : %d\n", dipinjam[k].IDPeminjam);
				printf("NAMA KARYAWAN : %s\n", dipinjam[k].Nama);
				printf("ID BARANG : %d\n", dipinjam[k].IDBrg);
				printf("NAMA BARANG : %s\n", dipinjam[k].NamaBrg);
				printf("STOK BARANG : %d\n", dipinjam[k].Qty);
				printf("TANGGAL PEMINJAMAN : %d\n", dipinjam[k].TGLpinjam);
				printf("-------------------------------------------\n");
				printf("Masukkan Tanggal barang Dikembalikan: ");
				scanf("%d",&dipinjam[k].TGLkembali);
				printf("-------------------------------------------\n\n");
				break; //MENGAMBIL POSISI INDEKS UNTUK MENGAMBIL POSISI DATUM.
    		}
    	}
    	int z;
     	int idx;
     	int indx;

    	if (found == 1 /*PENCARIAN IDPINJAM BERHASIL*/ ){
    		//MENGUBAH ISI DATA BARANG
			for (z = 0; z < i; z++){
				if (barang[z].ID == dipinjam[k].IDBrg){
					barang[z].Qty = barang[z].Qty + dipinjam[k].Qty;
					strcpy(barang[z].Status, "Tersedia");
					idx = z; //MENGAMBIL POSISI DATA BARANG UNTUK PENENTUAN DENDA
				}
				fprintf(temp3,"%d %s %d %s %d %d\n",barang[z].ID, barang[z].Nama, barang[z].Qty, barang[z].Status,
					barang[z].Rak, barang[z].Durasi);
					//MEMBACA DATA BARANG DAN MENGHITUNG JUMLAH DATA
			}

    		//MEMBERI DENDA PADA KARYAWAN (JIKA ADA)
			for (z = 0; z < j; z++){
				if (employees[z].ID == dipinjam[k].IDPeminjam){
    				hasil = (dipinjam[k].TGLkembali - dipinjam[k].TGLpinjam);
    				if (hasil > barang[idx].Durasi){
    					hasil = hasil - barang[idx].Durasi;
    					employees[z].Denda = employees[z].Denda + (hasil*15000);
    					indx = z;
    				}
    				else {
    					indx = z;
    					employees[indx].Denda = employees[indx].Denda + 0;
    				}
    			}
    			fprintf(temp2, "%d %s %s %s %d\n", employees[z].ID,
    			employees[z].Nama, employees[z].NomorHP, employees[z].Alamat, employees[indx].Denda);
			}

			//MENCATAT HISTORI PENGEMBALIAN
    		fprintf(fptr,"%d %d %s %d %s %d %d %d %d\n",dipinjam[k].IDPinjam,dipinjam[k].IDPeminjam, dipinjam[k].Nama,
        		dipinjam[k].IDBrg, dipinjam[k].NamaBrg, dipinjam[k].Qty, 
        		dipinjam[k].TGLpinjam, dipinjam[k].TGLkembali,employees[indx].Denda);

    		printf("-------------------------------------------\n");
			printf("       DATA YANG DIKEMBALIKAN OLEH ANDA	   \n");
			printf("-------------------------------------------\n");
			printf("ID PEMINJAMAN : %d\n", dipinjam[k].IDPinjam);
			printf("ID KARYAWAN : %d\n", dipinjam[k].IDPeminjam);
			printf("NAMA KARYAWAN : %s\n", dipinjam[k].Nama);
			printf("ID BARANG : %d\n", dipinjam[k].IDBrg);
			printf("NAMA BARANG : %s\n", dipinjam[k].NamaBrg);
			printf("KUANTITAS KEMBALI : %d\n", dipinjam[k].Qty);
			printf("TANGGAL PEMINJAMAN : %d\n", dipinjam[k].TGLpinjam);
			printf("TANGGAL KEMBALI : %d\n",dipinjam[k].TGLkembali);
			printf("DENDA : %d\n",employees[indx].Denda);
			printf("-------------------------------------------\n");

    		for (j = 0; j < x; j++){
    		//MENGHAPUS DATA PEMINJAMAN KARENA SUDAH DIKEMBALIKAN
    			if (dipinjam[j].IDPinjam != dipinjam[k].IDPinjam){
    				fprintf(temp,"%d %d %s %d %s %d %d %d\n", dipinjam[j].IDPinjam, dipinjam[j].IDPeminjam, dipinjam[j].Nama,
        				dipinjam[j].IDBrg, dipinjam[j].NamaBrg, dipinjam[j].Qty, dipinjam[j].TGLpinjam, dipinjam[j].TGLkembali);
    			}
    		}
    	}
    	else{
    		printf("ID Tidak Ditemukan.\n");
    	}
    	fclose(data);
    	fclose(brg);
    	fclose(pinjam);
    	fclose(fptr);
    	fclose(temp);
    	fclose(temp2);
    	fclose(temp3);

    	if (found == 1){
    		remove("datapinjam.txt");
    		remove("karyawan.txt");
    		remove("databarang.txt");

    		rename("temp.txt","datapinjam.txt");
    		rename("temp3.txt","databarang.txt");
    		rename("temp2.txt","karyawan.txt");
    	}
    	printf("[1]Tambah Data Pengembalian Baru\n[2]Selesai\nPilih: ");
    	scanf("%d",&choice);
		if (choice != 2){
			rewind(data);
			rewind(brg);
			rewind(pinjam);
		}

	}while(choice != 2);
	ManageMenu();
}
