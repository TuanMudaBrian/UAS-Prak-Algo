#include <iostream>
#include <string>
using namespace std;

#define MAX_BUKU 50
#define MAX_ANGGOTA 50

// Input Data Buku
struct Buku {
    string judul;
    string penulis;
    int tahun;
    string kode;
    bool status;
};

// Input Data Anggota
struct Anggota {
    string nama;
    string tanggal;
    string kode_buku;
};

// Variabel global
Buku koleksi[MAX_BUKU];
Anggota anggota[MAX_ANGGOTA];
int jumlah_buku = 0;
int jumlah_anggota = 0;

// Fungsi untuk menambahkan buku ke koleksi perpustakaan
void tambah_buku() {
    if (jumlah_buku == MAX_BUKU) {
        cout << "Maaf, koleksi sudah penuh." << endl;
        return;
    }

    // Variabel Lokal
    Buku baru;

    // Meminta input dari pengguna
    cout << "Masukkan judul buku: ";
    getline(cin, baru.judul);
    cout << "Masukkan penulis buku: ";
    getline(cin, baru.penulis);
    cout << "Masukkan tahun terbit buku: ";
    cin >> baru.tahun;
    cout << "Masukkan kode buku: ";
    cin >> baru.kode;

    // Mengatur status buku menjadi tersedia
    baru.status = true;

    // Menambahkan buku ke koleksi perpustakaan
    koleksi[jumlah_buku] = baru;
    jumlah_buku++;

    // Memberitahu pengguna bahwa buku berhasil ditambahkan
    cout << "Buku berhasil ditambahkan ke koleksi." << endl;
}

// Fungsi untuk mencari buku berdasarkan kode buku
// Mengembalikan indeks buku di koleksi, atau -1 jika tidak ditemukan
int cari_buku(string kode) {
    // Melakukan pencarian linear pada koleksi
    for (int i = 0; i < jumlah_buku; i++) {
        if (koleksi[i].kode == kode) {
            // Mengembalikan indeks buku jika ditemukan
            return i;
        }
    }
    // Mengembalikan -1 jika tidak ditemukan
    return -1;
}

// Fungsi untuk meminjamkan buku ke anggota perpustakaan
void pinjam_buku() {
    if (jumlah_anggota == MAX_ANGGOTA) {
        cout << "Maaf, anggota sudah penuh." << endl;
        return;
    }

    // Membuat variabel lokal untuk menyimpan data anggota yang akan meminjam
    Anggota baru;

    // Meminta input dari pengguna
    cout << "Masukkan nama peminjam: ";
    getline(cin, baru.nama);
    cout << "Masukkan tanggal peminjaman (DD/MM/YYYY): ";
    getline(cin, baru.tanggal);

pinjam_ulang:

    cout << "Masukkan kode buku yang ingin dipinjam: ";
    cin >> baru.kode_buku;

    // Mencari indeks buku yang ingin dipinjam
    int indeks = cari_buku(baru.kode_buku);

    // Mengecek apakah buku ditemukan atau tidak
    if (indeks == -1) {
        cout << "Maaf, buku tidak ditemukan." << endl;
        goto pinjam_ulang;
    }

    // Mengecek apakah buku tersedia atau tidak
    if (koleksi[indeks].status == false) {
        cout << "Maaf, buku sedang dipinjam." << endl;
        goto pinjam_ulang;
    }

    // Mengubah status buku menjadi dipinjam
    koleksi[indeks].status = false;

    // Menambahkan anggota ke daftar anggota perpustakaan
    anggota[jumlah_anggota] = baru;
    jumlah_anggota++;

    // Memberitahu pengguna bahwa buku berhasil dipinjam
    cout << "Buku berhasil dipinjam." << endl;
}

// Fungsi untuk mengembalikan buku yang dipinjam
void kembalikan_buku() {
    string kode;
    // Meminta input dari pengguna
    cout << "Masukkan kode buku yang ingin dikembalikan: ";
    cin >> kode;
    int indeks = cari_buku(kode);

    // Mengecek apakah buku ditemukan atau tidak
    if (indeks == -1) {
        cout << "Maaf, buku tidak ditemukan." << endl;
        return;
    }

    // Mengecek apakah buku memang dipinjam atau tidak
    if (koleksi[indeks].status == true) {
        cout << "Maaf, buku tidak sedang dipinjam." << endl;
        return;
    }
    koleksi[indeks].status = true;

    // Mencari indeks anggota yang meminjam buku tersebut
    int i;
    for (i = 0; i < jumlah_anggota; i++) {
        if (anggota[i].kode_buku == kode) {
            break;
        }
    }

    // Menghapus data anggota yang mengembalikan buku dari daftar anggota perpustakaan
    for (int j = i; j < jumlah_anggota - 1; j++) {
        anggota[j] = anggota[j + 1];
    }
    jumlah_anggota--;

    // Memberitahu pengguna bahwa buku berhasil dikembalikan
    cout << "Buku berhasil dikembalikan." << endl;
}

// Fungsi untuk menampilkan informasi buku dan peminjaman
void tampil_info() {
    // Menampilkan informasi buku
    cout << "Informasi Buku:" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "No. \t\tJudul\tPenulis\t\tTahun\tKode\tStatus" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    // Menampilkan informasi buku dari akhir ke awal
    for (int i = 0; i < jumlah_buku; i++) {
        cout << i + 1 << ".\t\t" << koleksi[i].judul << "\t" << koleksi[i].penulis << "\t" << koleksi[i].tahun << "\t"
             << koleksi[i].kode << "\t";
        if (koleksi[i].status == true) {
            cout << "Tersedia" << endl;
        } else {
            cout << "Dipinjam" << endl;
        }
    }
    cout << endl;

    // Menampilkan informasi peminjaman
    cout << "Informasi Peminjaman:" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "No.\t Nama\t\tTanggal\t\tKode Buku" << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlah_anggota; i++) {
        cout << i + 1 << ".\t " << anggota[i].nama << "\t" << anggota[i].tanggal << "\t" << anggota[i].kode_buku << endl;
    }
    cout << endl;
}

int main() {
    int pilihan;
    // Menampilkan menu utama program secara berulang
    do {
        cout << "Program Manajemen Buku di Perpustakaan" << endl;
        cout << "--------------------------------------" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Pinjam Buku" << endl;
        cout << "3. Kembalikan Buku" << endl;
        cout << "4. Tampil Info" << endl;
        cout << "5. Keluar" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        // Membersihkan buffer input
        cin.ignore();

        // Memproses pilihan pengguna dengan memanggil fungsi yang sesuai
        switch (pilihan) {
        case 1:
            tambah_buku();
            break;
        case 2:
            pinjam_buku();
            break;
        case 3:
            kembalikan_buku();
            break;
        case 4:
            tampil_info();
            break;
        case 5:
            cout << "Terima kasih telah menggunakan program ini." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan masukkan angka 1-5." << endl;
            break;
        }
    } while (pilihan != 5);

    return 0;
}
