#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

const int TABLE_SIZE = 20;

enum State { EMPTY, OCCUPIED, DELETED };

struct Slot {
    long long nim;
    string nama;
    State state;
    Slot() : nim(0), nama(""), state(EMPTY) {}
};

class HashTable {
private:
    Slot table[TABLE_SIZE];

    int hash1(long long key) const { return (int)(key % 20); }
    int hash2(long long key) const { return (int)(19 - (key % 19)); }
    
    // double hashing: (h1 + i * h2) % TABLE_SIZE
    int probe(long long key, int i) const {
        return (hash1(key) + i * hash2(key)) % TABLE_SIZE;
    }

public:
    // mengembalikan index slot jika ditemukan, jika tidak maka -1
    int findIndex(long long nim) const {
        for (int i = 0; i < TABLE_SIZE; i++) {
            int idx = probe(nim, i);
            if (table[idx].state == EMPTY) return -1;
            if (table[idx].state == OCCUPIED && table[idx].nim == nim) return idx;
        }
        return -1;
    }

    bool insert(long long nim, const string &nama) {
        if (findIndex(nim) != -1) {
            cout << "[GAGAL] NIM " << nim << " sudah ada." << endl;
            return false;
        }
        int collision = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            int idx = probe(nim, i);
            if (table[idx].state != OCCUPIED) {  // EMPTY atau DELETED
                table[idx].nim = nim;
                table[idx].nama = nama;
                table[idx].state = OCCUPIED;
                cout << "[OK] " << nim << " (" << nama << ") masuk ke index " << idx;
                if (collision > 0) cout << "  <-- collision " << collision << "x";
                cout << endl;
                return true;
            }
            collision++;
            cout << "     collision di index " << idx << " (milik NIM "
                 << table[idx].nim << "), coba probe berikutnya..." << endl;
        }
        cout << "[GAGAL] Tabel penuh / tidak ada slot yang terjangkau untuk NIM " << nim << "." << endl;
        return false;
    }

    void search(long long nim) const {
        int idx = findIndex(nim);
        if (idx == -1)
            cout << "[TIDAK DITEMUKAN] NIM " << nim << endl;
        else
            cout << "[DITEMUKAN] NIM " << nim << " -> " << table[idx].nama << " (index " << idx << ")" << endl;
    }

    void remove(long long nim) {
        int idx = findIndex(nim);
        if (idx == -1) {
            cout << "[GAGAL] NIM " << nim << " tidak ditemukan." << endl;
            return;
        }
        // Tandai DELETED biar probing ga rusak
        table[idx].state = DELETED;
        cout << "[OK] NIM " << nim << " (" << table[idx].nama << ") dihapus dari index " << idx << endl;
    }

    void display() const {
        cout << endl << "Idx | Status   | NIM        | Nama" << endl;
        cout << "-----------------------------------------------" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << setw(3) << i << " | ";
            if (table[i].state == OCCUPIED){
                cout << left << setw(8) << "ISI" << " | " << setw(10) << table[i].nim
                     << " | " << table[i].nama << right << endl;
            }
            else if (table[i].state == DELETED){
                cout << left << setw(8) << "DIHAPUS" << " | " << setw(10) << "-"
                     << " | -" << right << endl;
            }
            else{
                cout << left << setw(8) << "KOSONG" << " | " << setw(10) << "-"
                     << " | -" << right << endl;
            }
        }
        cout << endl;
    }
};

void ujiProgram(HashTable &ht) {
    struct Data { long long nim; const char *nama; };
    // NIM 2311001, 2311021, 2311041 sama-sama menghasilkan Hash1 = 1 (collision)
    Data data[] = {
        {2311001, "Andi Pratama"},   {2311021, "Budi Santoso"},
        {2311041, "Citra Dewi"},     {2311002, "Dewi Lestari"},
        {2311003, "Eko Prasetyo"},   {2311004, "Fitri Handayani"},
        {2311005, "Gilang Ramadhan"},{2311006, "Hana Putri"},
        {2311007, "Indra Wijaya"},   {2311008, "Joko Susilo"},
        {2311009, "Kartika Sari"},   {2311010, "Lukman Hakim"},
        {2311061, "Maya Anggraini"}, {2311081, "Nanda Saputra"},
        {2311011, "Oki Setiawan"},   {2311012, "Putri Amelia"}
    };

    cout << endl << "===== 1. INSERT 16 DATA (termasuk collision) =====" << endl;
    for (auto &d : data) ht.insert(d.nim, d.nama);

    cout << endl << "===== 2. DISPLAY =====";
    ht.display();

    cout << "===== 3. SEARCH =====" << endl;
    ht.search(2311041);  // data hasil collision
    ht.search(9999999);  // tidak ada

    cout << endl << "===== 4. REMOVE =====" << endl;
    ht.remove(2311021);  // hapus data di tengah rantai collision
    ht.remove(9999999);  // tidak ada

    cout << endl << "===== 5. SEARCH SETELAH REMOVE =====" << endl;
    ht.search(2311021);  // sudah terhapus
    ht.search(2311041);  // tetap ditemukan (krn tombstone)

    cout << endl << "===== 6. INSERT ULANG (memakai slot DELETED) =====" << endl;
    ht.insert(2311101, "Qori Rahman");

    cout << endl << "===== 7. DISPLAY AKHIR =====";
    ht.display();
}

int main() {
    HashTable ht;
    int pilihan;
    do {
        cout << "\n=== SISTEM DATA MAHASISWA (HASH TABLE) ===" << endl
             << "1. Insert" << endl 
             << "2. Search" << endl 
             << "3. Remove" << endl 
             << "4. Display" << endl
             << "5. Pengujian otomatis (16 data)" << endl 
             << "0. Keluar" << endl 
             << "Pilih: ";
        if (!(cin >> pilihan)) break;

        long long nim;
        string nama;
        switch (pilihan) {
            case 1:
                cout << "NIM  : "; cin >> nim;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nama : ";
                getline(cin, nama);
                ht.insert(nim, nama);
                break;
            case 2:
                cout << "NIM yang dicari: ";
                cin >> nim;
                ht.search(nim);
                break;
            case 3:
                cout << "NIM yang dihapus: "; 
                cin >> nim;
                ht.remove(nim);
                break;
            case 4: ht.display(); break;
            case 5: ujiProgram(ht); break;
            case 0: cout << "Dah siap, gas turu!" << endl; break;
            default: cout << "Menu tidak valid." << endl;
        }
        cout << endl;
    } while (pilihan != 0);
    return 0;
}