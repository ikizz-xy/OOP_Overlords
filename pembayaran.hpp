#pragma once
#include "tagihan.hpp"

struct Pembayaran { int idPenghuni, idTagihan; double jumlah; string bulan; };
vector<Pembayaran> daftarPembayaran;
inline void catatPembayaran() {
    while (true) {
        int idP = inInt("Input idPenghuni: ");
        int idT = inInt("Input idTagihan: ");
        double jumlah = inNum("Input jumlah bayar: ");
        TagihanPenghuni* tp = nullptr;
        for (auto& x : daftarTagihanPenghuni)
            if (x.idPenghuni == idP && x.idTagihan == idT)
                tp = &x;
        if (!tp) {
            cout << "Data tidak ditemukan\n";
            return;
        }
        if (jumlah <= 0 || jumlah > tp->sisa) {
            cout << "Jumlah bayar tidak valid\n";
            return;
        }
        tp->terbayar += jumlah;
        tp->sisa = tp->jumlahTagih - tp->terbayar;
        tp->status = (tp->sisa == 0) ? "Lunas" : "Belum Lunas";
        daftarPembayaran.push_back({
            idP, idT, jumlah, cariTagihan(idT)->bulan
        });
        cout << "Bukti pembayaran: penghuni " << idP
             << ", tagihan " << idT
             << ", bayar " << jumlah
             << "\nSisa tagihan: " << tp->sisa << "\n";
        return;
    }
}
inline void tampilkanLaporan() {
    string bulan = in("Input bulan laporan (Januari-Desember): ");
if (!bulanValid(bulan)) {
    cout << "Bulan tidak valid. Kembali ke menu pengelola.\n";
    return;
}

    string jenis[] = {"listrik", "air", "iuran", "internet"};
    double pengeluaran[4] = {0, 0, 0, 0};
    double pemasukan[4] = {0, 0, 0, 0};
    bool ada = false;
    // Menghitung total tagihan per jenis
    for (auto& t : daftarTagihan) {
        if (t.bulan == bulan) {
            ada = true;
            for (int i = 0; i < 4; i++) {
                if (t.jenis == jenis[i]) {
                    pengeluaran[i] += t.totalBiaya;
                }
            }
        }
    }

    // Menghitung pembayaran berdasarkan jenis tagihan
    for (auto& b : daftarPembayaran) {
        if (b.bulan == bulan) {
            ada = true;
            const Tagihan* t = cariTagihan(b.idTagihan);
            if (t != nullptr) {
                for (int i = 0; i < 4; i++) {
                    if (t->jenis == jenis[i]) {
                        pemasukan[i] += b.jumlah;
                    }
                }
            }
        }
    }

    if (!ada) {
        cout << "Belum ada data bulan ini\n";
        return;
    }

    double totalPengeluaran = 0;
    double totalPemasukan = 0;
    cout << "\n=== LAPORAN BULAN " << bulan << " ===\n";
    for (int i = 0; i < 4; i++) {
        cout << "\nJenis: " << jenis[i] << "\n";
        cout << "Pengeluaran: " << pengeluaran[i] << "\n";
        cout << "Pemasukan: " << pemasukan[i] << "\n";
        cout << "Selisih: "
             << pemasukan[i] - pengeluaran[i] << "\n";

        totalPengeluaran += pengeluaran[i];
        totalPemasukan += pemasukan[i];
    }

    cout << "\n=== TOTAL KESELURUHAN ===\n";
    cout << "Pemasukan: " << totalPemasukan << "\n";
    cout << "Pengeluaran: " << totalPengeluaran << "\n";
    cout << "Selisih: "
         << totalPemasukan - totalPengeluaran << "\n";
}