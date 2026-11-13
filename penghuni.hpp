#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
using namespace std;
inline string in(const string& prompt) {
    string s;
    cout << prompt;
    if (!getline(cin, s)) exit(0);
    return s;
}
inline int inInt(const string& p) { return atoi(in(p).c_str()); }
inline double inNum(const string& p) { return atof(in(p).c_str()); }
struct Penghuni { int id; string nama; int noKamar; };
struct Kamar { int noKamar; bool terisi; };
inline vector<Penghuni> daftarPenghuni;
inline vector<Kamar> daftarKamar;
inline int idPenghuni = 0;
inline const Penghuni* cariPenghuni(int id) {
    for (auto& p : daftarPenghuni)
        if (p.id == id) return &p;
    return nullptr;
}
inline void kelolaPenghuni() { Penghuni p;
    p.nama = in("Input nama penghuni: ");
    p.noKamar = inInt("Input no kamar: ");

    if (p.nama.empty() || p.noKamar <= 0) {
        cout << "Input tidak valid\n";
        return;
    }
    for (auto& k : daftarKamar)
        if (k.noKamar == p.noKamar && k.terisi) {
            cout << "No kamar sudah terisi\n";
            return;
        }
    bool ada = false;
    for (auto& k : daftarKamar)
        if (k.noKamar == p.noKamar) { k.terisi = true; ada = true;
            break;
        }
    if (!ada) daftarKamar.push_back({p.noKamar, true});
    p.id = ++idPenghuni;
    daftarPenghuni.push_back(p);
    cout << left
     << setw(5) << "ID" << "|"
     << setw(20) << "Nama" << "|"
     << "No Kamar\n";
cout << string(33, '-') << "\n";
for (auto& x : daftarPenghuni) {
    cout << left
         << setw(5) << x.id << "|"
         << setw(20) << x.nama << "|"
         << x.noKamar << "\n";
}
}