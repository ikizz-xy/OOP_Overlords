#pragma once
#include "penghuni.hpp"
#include <iomanip>
struct Tagihan { int id; string jenis, bulan; double totalBiaya; };
struct TagihanPenghuni { int idPenghuni, idTagihan; double jumlahTagih, terbayar; string status; double sisa; };

vector<Tagihan> daftarTagihan;
vector<TagihanPenghuni> daftarTagihanPenghuni;
int idTagihan = 0;
inline const Tagihan* cariTagihan(int id) {
    for (auto& t : daftarTagihan) if (t.id == id) return &t;
    return nullptr;
}
inline bool bulanValid(const string& bulan) {
    string daftarBulan[] = {
        "Januari", "Februari", "Maret", "April",
        "Mei", "Juni", "Juli", "Agustus",
        "September", "Oktober", "November", "Desember"
    };
    for (auto& b : daftarBulan) { if (bulan == b) return true;
    }
    return false;
}
inline void lihatTagihan() {
    string id;
    while ((id = in("Input idPenghuni: ")).empty())
        cout << "ID penghuni tidak boleh kosong\n";
    int idP = atoi(id.c_str());
    bool ada = false;
    cout << left
     << setw(5) << "ID" << "|"
     << setw(12) << "Jenis" << "|"
     << setw(12) << "Bulan" << "|"
     << setw(12) << "Tagihan" << "|"
     << setw(12) << "Terbayar" << "|"
     << setw(15) << "Status" << "|"
     << "Sisa\n";
    for (auto& t : daftarTagihanPenghuni)
        if (t.idPenghuni == idP) { ada = true;
            const Tagihan* data = cariTagihan(t.idTagihan);
            cout << left
     << setw(5) << t.idTagihan << "|"
     << setw(12) << (data ? data->jenis : "-") << "|"
     << setw(12) << (data ? data->bulan : "-") << "|"
     << setw(12) << t.jumlahTagih << "|"
     << setw(12) << t.terbayar << "|"
     << setw(15) << t.status << "|"
     << t.sisa << "\n";
        }
    if (!ada) cout << "ID Penghuni belum ada\n";
}
inline void kelolaTagihan() {
    Tagihan t;
    t.jenis = in("Input jenis (listrik/air/iuran/internet): ");
    t.bulan = in("Input bulan (Januari-Desember): ");
    t.totalBiaya = inNum("Input totalBiaya: ");

    if (t.totalBiaya <= 0 || !bulanValid(t.bulan) ||
    (t.jenis != "listrik" && t.jenis != "air" &&
     t.jenis != "iuran" && t.jenis != "internet")) {
    cout << "Data tidak valid. Kembali ke menu pengelola.\n";
    return;
}
    for (auto& x : daftarTagihan) {
        if (x.jenis == t.jenis && x.bulan == t.bulan) {
            cout << "Tagihan " << t.jenis << " bulan "
                 << t.bulan << " sudah ada\n";
            return;
        }
    }
    t.id = ++idTagihan;
    daftarTagihan.push_back(t);
             cout << left
     << setw(5) << "ID" << "|"
     << setw(12) << "Jenis" << "|"
     << setw(15) << "Bulan" << "|"
     << "Total Biaya\n";

cout << string(43, '-') << "\n";
for (auto& x : daftarTagihan) {
    cout << left
         << setw(5) << x.id << "|"
         << setw(12) << x.jenis << "|"
         << setw(15) << x.bulan << "|"
         << x.totalBiaya << "\n";
}
}
inline void hitungPembagian() {
    int idT = inInt("Input idTagihan: ");
    const Tagihan* t = cariTagihan(idT);
    if (!t) { cout << "Tagihan tidak ditemukan (kembali ke menu)\n"; return; }
    if (daftarPenghuni.empty()) { cout << "Belum ada penghuni (kembali ke menu)\n"; return; }
    double biaya = t->totalBiaya / daftarPenghuni.size();
    cout << "Hasil pembagian per penghuni:\n";
    for (auto& p : daftarPenghuni) {
        bool ada = false; // hitung ulang tidak boleh menggandakan data
        for (auto& x : daftarTagihanPenghuni) if (x.idPenghuni == p.id && x.idTagihan == idT) ada = true;
        if (!ada) daftarTagihanPenghuni.push_back({p.id, idT, biaya, 0, "Belum Lunas", biaya});
        cout << p.nama << " (kamar " << p.noKamar << "): " << biaya << "\n";
    }
}
inline void tampilkanStatus() {
    if (daftarTagihanPenghuni.empty()) { cout << "Belum ada tagihan\n"; return; }
    cout << left
     << setw(20) << "Nama" << "|"
     << setw(8) << "Kamar" << "|"
     << setw(12) << "Jenis" << "|"
     << setw(13) << "Tagihan" << "|"
     << setw(13) << "Terbayar" << "|"
     << setw(13) << "Sisa" << "|"
     << "Status\n";
    for (auto& tp : daftarTagihanPenghuni) {
        tp.sisa = tp.jumlahTagih - tp.terbayar;
        tp.status = (tp.sisa <= 0) ? "Lunas" : "Belum Lunas";
        const Penghuni* p = cariPenghuni(tp.idPenghuni);
        const Tagihan* t = cariTagihan(tp.idTagihan);
if (!p || !t) continue;
cout << left
     << setw(20) << p->nama << "|"
     << setw(8) << p->noKamar << "|"
     << setw(12) << t->jenis << "|"
     << setw(13) << tp.jumlahTagih << "|"
     << setw(13) << tp.terbayar << "|"
     << setw(13) << tp.sisa << "|"
     << tp.status << "\n";
    }
}
