#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cctype>
#include <string>
using namespace std;

const int N = 6;
const int INF = numeric_limits<int>::max();
const char VERTEX[N] = {'A', 'B', 'C', 'D', 'E', 'F'};

// Adjacency Matrix (0 = tidak ada sisi), graf tidak berarah
int matrix_[N][N] = {};

struct Edge { char a, b; int w; };


void tampilkanMatrix() {
    cout << endl << "Adjacency matrix:" << endl << "    ";
    for (int i = 0; i < N; i++) cout << setw(3) << VERTEX[i];
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(3) << VERTEX[i] << " ";
        for (int j = 0; j < N; j++) cout << setw(3) << matrix_[i][j];
        cout << endl;
    }
}

void bfs(int start) {
    bool visited[N] = {false};
    queue<int> q;
    q.push(start);
    visited[start] = true;
    cout << "BFS : ";
    bool pertama = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << (pertama ? "" : " -> ") << VERTEX[u];
        pertama = false;
        for (int v = 0; v < N; v++) {
            if (matrix_[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

void dfsRek(int u, bool visited[], bool &pertama) {
    visited[u] = true;
    cout << (pertama ? "" : " -> ") << VERTEX[u];
    pertama = false;
    for (int v = 0; v < N; v++)
        if (matrix_[u][v] != 0 && !visited[v]) dfsRek(v, visited, pertama);
}

void dfs(int start) {
    bool visited[N] = {false};
    bool pertama = true;
    cout << "DFS : ";
    dfsRek(start, visited, pertama);
    cout << endl;
}

void dijkstra(int s, int t) {
    int dist[N];
    int prev[N];
    for (int i = 0; i < N; i++) { dist[i] = INF; prev[i] = -1; }
    dist[s] = 0;

    // min-heap berisi pasangan (jarak, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        pair<int, int> top = pq.top(); pq.pop();
        int d = top.first, u = top.second;
        if (d > dist[u]) continue;
        for (int v = 0; v < N; v++) {
            if (matrix_[u][v] == 0) continue;
            int nd = d + matrix_[u][v];
            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                pq.push({nd, v});
            }
        }
    }

    if (dist[t] == INF) {
        cout << "Tidak ada rute yang menghubungkan kedua vertex." << endl;
        return;
    }
    vector<int> rute;
    for (int cur = t; cur != -1; cur = prev[cur]) rute.push_back(cur);
    reverse(rute.begin(), rute.end());

    cout << "Rute terpendek : ";
    for (size_t i = 0; i < rute.size(); i++)
        cout << (i ? " -> " : "") << VERTEX[rute[i]];
    cout << endl << "Total jarak    : " << dist[t] << endl;
}

// Meminta vertex dari pengguna, mengembalikan indeks 0..N-1
int inputVertex(const string &pesan, bool adaDefault) {
    while (true) {
        cout << pesan;
        string s;
        getline(cin, s);
        if (s.empty() && adaDefault) return 0;  // default A
        if (s.size() == 1) {
            char c = toupper((unsigned char)s[0]);
            if (c >= 'A' && c < 'A' + N) return c - 'A';
        }
        cout << "Vertex tidak valid. Pilih salah satu dari A-F." << endl;
    }
}

int main() {
    // masukin graf sesuai petunjuk soal
    Edge edges[] = {
        {'A', 'B', 4}, {'A', 'C', 2}, {'B', 'C', 1}, {'B', 'D', 5},
        {'B', 'E', 3}, {'C', 'D', 8}, {'C', 'E', 6}, {'D', 'E', 2},
        {'D', 'F', 4}, {'E', 'F', 3}
    };
    for (const Edge &e : edges) {
        int i = e.a - 'A', j = e.b - 'A';
        matrix_[i][j] = matrix_[j][i] = e.w;
    }


    tampilkanMatrix();

    string pilihan;
    while (true) {
        cout << "\n=== SISTEM PENCARIAN RUTE KAMPUS ===" << endl
             << "1. Telusuri graf" << endl
             << "2. Cari rute terpendek" << endl
             << "3. Tampilkan adjacency matrix" << endl
             << "0. Keluar" << endl
             << "Pilih menu: ";
        getline(cin, pilihan);

        if (pilihan == "1") {
            int awal = inputVertex("Vertex awal (default A): ", true);
            bfs(awal);
            dfs(awal);
        } else if (pilihan == "2") {
            int awal = inputVertex("Vertex awal (default A): ", true);
            int tujuan = inputVertex("Vertex tujuan: ", false);
            dijkstra(awal, tujuan);
        } else if (pilihan == "3") {
            tampilkanMatrix();
        } else if (pilihan == "0") {
            cout << "Terima kasih!" << endl;
            break;
        } else {
            cout << "Menu tidak valid." << endl;
        }
    }
    return 0;
}