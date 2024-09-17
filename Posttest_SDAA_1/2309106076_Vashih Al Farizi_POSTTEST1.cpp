#include <iostream>
using namespace std;

// Fungsi rekursif untuk menghitung nilai di Segitiga Pascal
int hitungSegitigaPascal(int baris, int kolom) {
    if (kolom == 0 || kolom == baris) {
        return 1;
    }
    return hitungSegitigaPascal(baris - 1, kolom - 1) + hitungSegitigaPascal(baris - 1, kolom);
}

// Fungsi untuk menampilkan Segitiga Pascal berbentuk segitiga siku-siku
void tampilkanSegitigaPascal(int tingkat) {
    for (int baris = 0; baris < tingkat; baris++) {
        for (int kolom = 0; kolom <= baris; kolom++) {
            cout << hitungSegitigaPascal(baris, kolom) << " ";
        }
        cout << endl;
    }
}

int main() {
    int tingkatSegitiga = 3;
    cout << "Segitiga Pascal Siku-siku:\n";
    tampilkanSegitigaPascal(tingkatSegitiga);
    
    return 0;
}
