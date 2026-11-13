#include <iostream>
#include <string>
#include <limits>
using namespace std;

// antrean mahasiswa mau meminjam buku (queue)
struct Antrian {
    string nim;
    string nama;
    Antrian* next;
};

// riwayat pengembalian buku (Stack)
struct Riwayat {
    string nim;
    int idBuku;
    string judul;
    Riwayat* next;
};

// data buku berdasarkan ID (BST)
struct Buku {
    int id;
    string judul;
    bool dipinjam;
    Buku* kiri;
    Buku* kanan;
};

Antrian* depan = nullptr;     // front queue
Antrian* belakang = nullptr;  // rear queue
Riwayat* atas = nullptr;      // top stack
Buku* root = nullptr;         // root BST

void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// baca angka, sisa baris dibuang supaya getline berikutnya aman
bool bacaInt(int& x) {
    if (!(cin >> x)) {
        bersihkanInput();
        return false;
    }
    bersihkanInput();
    return true;
}

// fungsi" queue
void enqueue(const string& nim, const string& nama) {
    Antrian* baru = new Antrian{nim, nama, nullptr};
    if (belakang == nullptr) {
        depan = belakang = baru;
    } else {
        belakang->next = baru;
        belakang = baru;
    }
}

void dequeue() {
    if (depan == nullptr) return;
    Antrian* temp = depan;
    depan = depan->next;
    if (depan == nullptr) belakang = nullptr;
    delete temp;
}

void tampilAntrian() {
    if (depan == nullptr) {
        cout << "Antrean kosong." << endl;
        return;
    }
    cout << endl << "Antrean peminjaman (depan ke belakang):" << endl;
    int no = 1;
    for (Antrian* p = depan; p != nullptr; p = p->next)
        cout << no++ << ". " << p->nim << " - " << p->nama << endl;
}

// fungsi" stack
void push(const string& nim, int idBuku, const string& judul) {
    atas = new Riwayat{nim, idBuku, judul, atas};
}

void tampilRiwayat() {
    if (atas == nullptr) {
        cout << "Riwayat pengembalian kosong." << endl;
        return;
    }
    cout << endl << "Riwayat pengembalian (terbaru ke terlama):" << endl;
    int no = 1;
    for (Riwayat* p = atas; p != nullptr; p = p->next)
        cout << no++ << ". NIM " << p->nim << " mengembalikan ["
             << p->idBuku << "] " << p->judul << endl;
}

// BST
Buku* insertBuku(Buku* node, int id, const string& judul, bool& berhasil) {
    if (node == nullptr) {
        berhasil = true;
        return new Buku{id, judul, false, nullptr, nullptr};
    }
    if (id < node->id) node->kiri = insertBuku(node->kiri, id, judul, berhasil);
    else if (id > node->id) node->kanan = insertBuku(node->kanan, id, judul, berhasil);
    else berhasil = false;   // ID duplikat
    return node;
}

Buku* cariBuku(int id) {
    Buku* p = root;
    while (p != nullptr && p->id != id) {
        if (id < p->id) p = p->kiri;
        else p = p->kanan;
    }
    return p;
}

void preOrder(Buku* node) { // root kiri kanan
    if (node == nullptr) return;
    cout << node->id << " ";
    preOrder(node->kiri);
    preOrder(node->kanan);
}

void inOrder(Buku* node) { // kiri root kanan
    if (node == nullptr) return;
    inOrder(node->kiri);
    cout << node->id << " ";
    inOrder(node->kanan);
}

void postOrder(Buku* node) { // Kiri kanan root
    if (node == nullptr) return;
    postOrder(node->kiri);
    postOrder(node->kanan);
    cout << node->id << " ";
}

void tampilBST() {
    if (root == nullptr) {
        cout << "BST kosong, belum ada buku." << endl;
        return;
    }
    cout << endl << "Pre-Order  : "; preOrder(root);
    cout << endl << "In-Order   : "; inOrder(root);
    cout << endl << "Post-Order : "; postOrder(root);
    cout << endl;
}

void hapusBST(Buku* node) {
    if (node == nullptr) return;
    hapusBST(node->kiri);
    hapusBST(node->kanan);
    delete node;
}

void hapusSemua() {
    while (depan != nullptr) dequeue();
    while (atas != nullptr) {
        Riwayat* temp = atas;
        atas = atas->next;
        delete temp;
    }
    hapusBST(root);
    root = nullptr;
}

int main() {
    int pilihan;

    do {
        cout <<  "\n===== SISTEM ANTREAN & PENGELOLAAN BUKU PERPUSTAKAAN =====" << endl;
        cout << "1. Tambah mahasiswa ke antrean" << endl;
        cout << "2. Proses peminjaman" << endl;
        cout << "3. Tampilkan antrean" << endl;
        cout << "4. Kembalikan buku" << endl;
        cout << "5. Tampilkan riwayat pengembalian" << endl;
        cout << "6. Tambah buku" << endl;
        cout << "7. Cari buku berdasarkan ID" << endl;
        cout << "8. Tampilkan BST" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        if (!bacaInt(pilihan)) pilihan = -1;

        if (pilihan == 1) {
            string nim, nama;
            cout << "NIM  : ";
            getline(cin, nim);
            cout << "Nama : ";
            getline(cin, nama);
            enqueue(nim, nama);
            cout << nama << " masuk antrean." << endl;
        } else if (pilihan == 2) {
            if (depan == nullptr) {
                cout << "Antrean kosong." << endl;
                continue;
            }
            cout << "Mahasiswa terdepan: " << depan->nim << " - " << depan->nama << endl;
            cout << "ID buku yang dipinjam: ";
            int id;
            if (!bacaInt(id)) {
                cout << "ID tidak valid." << endl;
                continue;
            }
            Buku* b = cariBuku(id);
            if (b == nullptr) {
                cout << "Buku dengan ID " << id << " tidak ditemukan." << endl;
            } else if (b->dipinjam) {
                cout << "Buku \"" << b->judul << "\" sedang dipinjam." << endl;
            } else {
                b->dipinjam = true;
                cout << depan->nama << " berhasil meminjam \"" << b->judul << "\"." << endl;
                dequeue();     // keluar dari antrean setelah dilayani
            }
        } else if (pilihan == 3) {
            tampilAntrian();
        } else if (pilihan == 4) {
            string nim;
            int id;
            cout << "NIM pengembali : ";
            getline(cin, nim);
            cout << "ID buku        : ";
            if (!bacaInt(id)) {
                cout << "ID tidak valid." << endl;
                continue;
            }
            Buku* b = cariBuku(id);
            if (b == nullptr) {
                cout << "Buku dengan ID " << id << " tidak ditemukan." << endl;
            } else if (!b->dipinjam) {
                cout << "Buku \"" << b->judul << "\" tidak sedang dipinjam." << endl;
            } else {
                b->dipinjam = false;
                push(nim, id, b->judul);
                cout << "Buku \"" << b->judul << "\" berhasil dikembalikan." << endl;
            }
        } else if (pilihan == 5) {
            tampilRiwayat();
        } else if (pilihan == 6) {
            int id;
            string judul;
            cout << "ID buku    : ";
            if (!bacaInt(id)) {
                cout << "ID tidak valid." << endl;
                continue;
            }
            cout << "Judul buku : ";
            getline(cin, judul);
            bool berhasil = false;
            root = insertBuku(root, id, judul, berhasil);
            if (berhasil) cout << "Buku berhasil ditambahkan." << endl;
            else cout << "ID buku sudah ada!" << endl;
        } else if (pilihan == 7) {
            int id;
            cout << "ID buku yang dicari: ";
            if (!bacaInt(id)) {
                cout << "ID tidak valid." << endl;
                continue;
            }
            Buku* b = cariBuku(id);
            if (b == nullptr) cout << "Buku tidak ditemukan." << endl;
            else cout << "Ditemukan: [" << b->id << "] " << b->judul
                      << (b->dipinjam ? " (sedang dipinjam)" : " (tersedia)") << endl;
        } else if (pilihan == 8) {
            tampilBST();
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);

    hapusSemua();
    cout << "Program selesai." << endl;
    return 0;
}