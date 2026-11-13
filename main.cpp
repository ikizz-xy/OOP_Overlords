#include "pembayaran.hpp"
using namespace std;
void menuPengelola() {
    while (true) {
        cout << "\n--- Menu Pengelola ---\n1. Kelola Tagihan\n2. Kelola Penghuni\n3. Hitung Pembagian\n"
                "4. Catat Pembayaran\n5. Tampilkan Status\n6. Tampilkan Laporan\n7. Kembali ke Menu Utama\n";
        string c = in("Pilih: ");
        if (c == "1") kelolaTagihan();
        else if (c == "2") kelolaPenghuni();
        else if (c == "3") hitungPembagian();
        else if (c == "4") catatPembayaran();
        else if (c == "5") tampilkanStatus();
        else if (c == "6") tampilkanLaporan();
        else if (c == "7") break; // Keluar dari loop pengelola, kembali ke menu utama
        else { 
            cout << "Input Tidak Valid\n"; 
            continue; 
        }
    }
}
void menuPenghuni() {
    while (true) {
        cout << "\n--- Menu Penghuni ---\n1. Lihat Tagihan\n2. Kembali ke Menu Utama\n";
        string c = in("Pilih: ");
        if (c == "1") { 
            lihatTagihan(); 
        } else if (c == "2") { 
            break; // Keluar dari loop penghuni, kembali ke menu utama
        } else { 
            cout << "Input Tidak Valid\n"; 
        }
    }
}
int main() {
    while (true) {
        cout << "\n=== MENU UTAMA ===\n"
             << "1. Pengelola\n"
             << "2. Penghuni\n"
             << "3. Keluar \n";
        string c = in("Pilih Role: ");
        if (c == "1") {
            menuPengelola(); // Masuk ke menu pengelola untuk input data penghuni/tagihan
        } else if (c == "2") {
            menuPenghuni(); // Masuk ke menu penghuni, bisa cek data di sini
        } else if (c == "3") {
            cout << "Selesai\n";
            break; // Keluar total dari program
        } else {
            cout << "Input tidak valid!\n";
        }
    }
    return 0;
}