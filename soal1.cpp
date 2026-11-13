#include <iostream>
#include <string>
#include <limits>
using namespace std;

// data mahasiswa (single linked list)
struct Mahasiswa {
    string nama;
    string nim;
    double nilai;
    Mahasiswa* next;
};

// nilai (dynamic array) 
struct arrNilai {
    double* data;
    int size;
    int capacity;
};

// variabel global
Mahasiswa* head = nullptr;
arrNilai arr = {nullptr, 0, 0};

void initArray(int cap = 2) {
    arr.data = new double[cap];
    arr.size = 0;
    arr.capacity = cap;
}

void pushBack(double value) {
    if (arr.size == arr.capacity) {  // kalau penuh, ukuran array x 2          
        int newCap = arr.capacity * 2;
        double* temp = new double[newCap];
        for (int i = 0; i < arr.size; i++) temp[i] = arr.data[i];
        delete[] arr.data;
        arr.data = temp;
        arr.capacity = newCap;
    }
    arr.data[arr.size++] = value;
}

// hapus array, buat lagi yg baru
void resetArray() {
    delete[] arr.data;
    initArray();
    for (Mahasiswa* p = head; p != nullptr; p = p->next) pushBack(p->nilai);
}

// utk cek apakh nim sudah ada atau belum
bool cekNim(const string& nim) {
    for (Mahasiswa* p = head; p != nullptr; p = p->next)
        if (p->nim == nim) return true;
    return false;
}

void tambahMahasiswa(const string& nim, const string& nama, double nilai) {
    Mahasiswa* baru = new Mahasiswa{nama, nim, nilai, nullptr};
    if (head == nullptr) {
        head = baru;
    } else {
        Mahasiswa* p = head;
        while (p->next != nullptr) p = p->next;   
        p->next = baru;
    }
    pushBack(nilai);                              
}

bool hapusMahasiswa(const string& nim) {
    Mahasiswa* prev = nullptr;
    Mahasiswa* cur = head;
    while (cur != nullptr && cur->nim != nim) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == nullptr) return false;
    if (prev == nullptr) head = cur->next;
    else prev->next = cur->next;
    delete cur;
    resetArray();
    return true;
}

void tampilMahasiswa() {
    if (head == nullptr) {
        cout << "Belum ada data mahasiswa." << endl;
        return;
    }
    cout << endl << "No  NIM            Nama                     Nilai" << endl;
    cout << "----------------------------------------------------" << endl;
    int no = 1;
    for (Mahasiswa* p = head; p != nullptr; p = p->next) {
        cout << no++ << "   " << p->nim;
        for (int i = p->nim.length(); i < 15; i++) cout << ' ';
        cout << p->nama;
        for (int i = p->nama.length(); i < 25; i++) cout << ' ';
        cout << p->nilai << endl;
    }
}

// insertion sort pada dynamic array (ascending)
void insertionSortArray() {
    for (int i = 1; i < arr.size; i++) {
        double key = arr.data[i];
        int j = i - 1;
        while (j >= 0 && arr.data[j] > key) {
            arr.data[j + 1] = arr.data[j];
            j--;
        }
        arr.data[j + 1] = key;
    }
}

// insertion sort pada linked list (ascending)
void insertionSortList() {
    Mahasiswa* sorted = nullptr;
    Mahasiswa* cur = head;
    while (cur != nullptr) {
        Mahasiswa* next = cur->next;
        if (sorted == nullptr || cur->nilai < sorted->nilai) {
            cur->next = sorted;
            sorted = cur;
        } else {
            Mahasiswa* t = sorted;
            while (t->next != nullptr && t->next->nilai <= cur->nilai) t = t->next;
            cur->next = t->next;
            t->next = cur;
        }
        cur = next;
    }
    head = sorted;
}

// tampilkan isi array
void tampilArray() {
    if (arr.size == 0) {
        cout << "Array nilai masih kosong." << endl;
        return;
    }
    cout << "Nilai : [ ";
    for (int i = 0; i < arr.size; i++) {
        cout << arr.data[i];
        if (i < arr.size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

// supaya input tidak terikut /n
void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// utk hapus semua linked list dari data mahasiswa
void hapusSemua() {
    while (head != nullptr) {
        Mahasiswa* temp = head;
        head = head->next;
        delete temp;
    }
    delete[] arr.data;
    arr.data = nullptr;
}

int main() {
    system("cls");
    initArray();
    int pilihan;

    do {
        cout << "\n===== SISTEM PENGELOLAAN NILAI MAHASISWA =====" << endl;
        cout << "1. Tambah mahasiswa" << endl;
        cout << "2. Tampilkan data mahasiswa" << endl;
        cout << "3. Hapus mahasiswa (berdasarkan NIM)" << endl;
        cout << "4. Urutkan nilai (Insertion Sort - Dynamic Array)" << endl;
        cout << "5. Urutkan data mahasiswa berdasarkan nilai (Insertion Sort - Linked List)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";

        if (!(cin >> pilihan)) {
            bersihkanInput();
            pilihan = -1;
        }

        if (pilihan == 1) {
            string nim, nama;
            double nilai;
            bersihkanInput();
            cout << "NIM   : ";
            getline(cin, nim);
            if (cekNim(nim)) {
                cout << "NIM sudah terdaftar!" << endl;
                continue;
            }
            cout << "Nama  : ";
            getline(cin, nama);
            cout << "Nilai : ";
            if (!(cin >> nilai) || nilai < 0 || nilai > 100) {
                bersihkanInput();
                cout << "Nilai tidak valid (harus 0-100)." << endl;
                continue;
            }
            tambahMahasiswa(nim, nama, nilai);
            cout << "Data berhasil ditambahkan." << endl;
        } else if (pilihan == 2) {
            tampilMahasiswa();
        } else if (pilihan == 3) {
            string nim;
            cout << "Masukkan NIM yang dihapus: ";
            bersihkanInput();
            getline(cin, nim);
            if (hapusMahasiswa(nim)) cout << "Data berhasil dihapus." << endl;
            else cout << "NIM tidak ditemukan." << endl;
        } else if (pilihan == 4) {
            insertionSortArray();
            tampilArray();
        } else if (pilihan == 5) {
            insertionSortList();
            cout << "Data mahasiswa ascending.";
            tampilMahasiswa();
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);

    hapusSemua();
    cout << "Program selesai." << endl;
    return 0;
}