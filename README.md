# 📚 Tugas Struktur Data — C++

##  Identitas
- **Nama** : Geofrey Melvern
- **NIM** : 251401059
- **Lab** : 3
- **Mata Kuliah** : Lab Struktur Data

##  Deskripsi Program

### 1. Sistem Pengelolaan Nilai Mahasiswa (`soal1/nilai_mahasiswa.cpp`)
Mengelola data mahasiswa (NIM, Nama, Nilai) menggunakan:
- **Single Linked List** untuk menyimpan data mahasiswa
- **Dynamic Array** (resize ×2 saat penuh) untuk kumpulan nilai
- **Insertion Sort** ascending pada array dan linked list
- **Linear Search** berdasarkan NIM & **Binary Search** nilai setelah diurutkan

### 2. Sistem Antrean & Pengelolaan Buku Perpustakaan (`soal2/perpustakaan.cpp`)
Simulasi peminjaman dan pengembalian buku menggunakan:
- **Queue** (FIFO) untuk antrean peminjam
- **Stack** (LIFO) untuk riwayat pengembalian
- **Binary Search Tree** untuk data buku + pencarian ID
- Traversal **Pre-Order, In-Order, Post-Order**

### 3. Sistem Pencarian Rute Kampus (`soal3/rute_kampus.cpp`)
Pencarian rute antar 6 lokasi (A–F) menggunakan:
- **Graph** dengan representasi **Adjacency Matrix** (berbobot, tidak berarah)
- **BFS** dan **DFS** untuk penelusuran graf
- **Dijkstra** untuk rute terpendek + total jarak
- Vertex awal & tujuan dipilih oleh pengguna

### 4. Sistem Data Mahasiswa — Hash Table (`soal4/hash_table.cpp`)
Menyimpan data mahasiswa (NIM = key, Nama = value) menggunakan:
- **Hash Table** ukuran 20 dengan **Double Hashing**
  - `Hash1(key) = key % 20`
  - `Hash2(key) = 19 - (key % 19)`
  - Probe: `(h1 + i × h2) % 20`
- Fitur Insert, Search, Remove (tombstone/DELETED), Display
- Pengujian otomatis 16 data: collision, penghapusan di tengah rantai, insert ulang ke slot DELETED

##  Struktur Folder
```
.
├── README.md
├── soal1.cpp
├── soal2.cpp
├── soal3.cpp
└── soal4.cpp
```

##  Cara Menjalankan
Butuh compiler C++ (g++ / MinGW). Compile & jalankan tiap program:

```bash
# Soal 1
g++ soal1/nilai_mahasiswa.cpp -o nilai && ./nilai

# Soal 2
g++ soal2/perpustakaan.cpp -o perpustakaan && ./perpustakaan

# Soal 3
g++ soal3/rute_kampus.cpp -o rute && ./rute

# Soal 4
g++ soal4/hash_table.cpp -o hash && ./hash
```
> Windows: ganti `./nilai` menjadi `nilai.exe`, dst. Bisa juga langsung Run di VS Code / Dev-C++.

##  Video Penjelasan
https://www.youtube.com/watch?v=R7PzQnSX2pM
