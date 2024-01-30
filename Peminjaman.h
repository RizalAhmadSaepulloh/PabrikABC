#ifndef header_h
#define header_h


// DEKLARASI TIPE BENTUKAN
typedef struct
{
	// DATA ADMIN MELIPUTI
	int kode; // Kaga tau ini gunanya apaan. Padahal ada username.
	char nama[25];
	char username[25];
	char password[25];
} admin_identity;

typedef struct
{
	// Setiap Karyawan Memiliki Data Berikut:
	int ID; //
	char Nama[25];
	char NomorHP[25]; // Integer Memiliki Batas Nilai.
	char Alamat[40];
	int Denda;
} data_karyawan;

typedef struct
{
	// Setiap Barang punya ID, Nama, dll.
	int ID;		   //
	char Nama[25]; // Nama Barang
	int Rak;	   // Masih Belum Ngerti ini Digunakan untuk Apa.
	int Qty;
	char Status[15];
	int Durasi; // Batas Waktu Meminjam. Kena Denda Jika Melewati.
} inventaris;	// Data Barang

typedef struct
{
	// Kalo Karyawan Mau Pinjem Barang, User Akan Menambah Data Pinjam.
	int IDPinjam;	  // ID Pinjam
	int IDPeminjam;	  // ID Karyawan
	int IDBrg;		  // ID Barang Yang Dipinjam
	char Nama[25];	  // Nama Karyawan yang Meminjam. Bukan Nama Barang yang Dipinjam.
	char NamaBrg[25]; // Nama Brg
	int Qty;
	int TGLpinjam; // Tanggal integer Karena Dipakai untuk Menghitung Denda per Hari.
	int TGLkembali;
} data_pinjam;

// DEKLARASI VARIABEL GLOBAL
admin_identity admin[50]; // Jumlah Akun Admin Bisa Dipakai
inventaris barang[50];
data_pinjam dipinjam[50];
data_karyawan employees[50];

int akun;	  // Menghitung Jumlah Akun Admin.
int i;		  // Counter Loop

// DEKLARASI FUNCTION DAN PROCEDURE
void Registration();
void Login();
void ManageMenu();
void CRUDKaryawan();
void CRUDBarang();
void CRUDPeminjaman();
void Pengembalian();

void lihat_karyawan();
void tambah_karyawan();
void hapus_karyawan();
void ganti_karyawan();
void search_karyawan();

void lihat_barang();
void tambah_barang();
void ganti_barang();
void search_barang();
void hapus_barang();

void ganti_peminjam();
void tambah_peminjam();
void lihat_peminjam();
void search_peminjam();

#endif