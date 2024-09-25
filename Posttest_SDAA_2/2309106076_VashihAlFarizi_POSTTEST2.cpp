#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Struct untuk menyimpan data laptop
struct Laptop {
    int idLaptop;
    string merkLaptop;
    string modelLaptop;
    long long hargaLaptop;
};

// Array untuk menyimpan data laptop
Laptop daftarLaptop[100]; 
int jumlahLaptop = 0;

string hapusTitik(string input) {
    input.erase(remove(input.begin(), input.end(), '.'), input.end());
    return input;
}

string formatRibuan(long long angka) {
    stringstream ss;
    string hasil = to_string(angka);
    int n = hasil.length() - 3;
    
    while (n > 0) {
        hasil.insert(n, ".");
        n -= 3;
    }
    
    return hasil;
}

// Fungsi untuk menambahkan laptop baru
void tambahLaptop(int* jumlahLaptopPtr, Laptop daftarLaptop[]) {
    Laptop laptopBaru;
    laptopBaru.idLaptop = *jumlahLaptopPtr + 1;

    string inputMerkModel;
    cout << "Masukkan merk dan model laptop (pisahkan dengan spasi): ";
    cin.ignore();
    getline(cin, inputMerkModel);
    size_t posisiSpasi = inputMerkModel.find(' ');
    laptopBaru.merkLaptop = inputMerkModel.substr(0, posisiSpasi);
    laptopBaru.modelLaptop = inputMerkModel.substr(posisiSpasi + 1);

    string inputHarga;
    cout << "Masukkan harga laptop (gunakan titik sebagai pemisah ribuan): ";
    cin >> inputHarga;
    inputHarga = hapusTitik(inputHarga);
    laptopBaru.hargaLaptop = stoll(inputHarga);

    daftarLaptop[*jumlahLaptopPtr] = laptopBaru;
    (*jumlahLaptopPtr)++;
    cout << "Laptop berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan daftar laptop
void tampilkanLaptop(int jumlahLaptop, Laptop daftarLaptop[]) {
    if (jumlahLaptop == 0) {
        cout << "Tidak ada data laptop.\n";
    } else {
        for (int i = 0; i < jumlahLaptop; i++) {
            cout << "ID: " << daftarLaptop[i].idLaptop
                 << ", Merk: " << daftarLaptop[i].merkLaptop
                 << ", Model: " << daftarLaptop[i].modelLaptop
                 << ", Harga: " << formatRibuan(daftarLaptop[i].hargaLaptop) << endl;
        }
    }
}

// Fungsi untuk mengupdate data laptop berdasarkan ID
void updateLaptop(int jumlahLaptop) {
    int idLaptop;
    cout << "Masukkan ID laptop yang akan diupdate: ";
    cin >> idLaptop;
    cin.ignore();

    bool ditemukan = false;
    for (int i = 0; i < jumlahLaptop; i++) {
        if (daftarLaptop[i].idLaptop == idLaptop) {
            ditemukan = true;

            string inputMerkModel;
            cout << "Masukkan merk dan model laptop baru (pisahkan dengan spasi): ";
            getline(cin, inputMerkModel);

            size_t posisiSpasi = inputMerkModel.find(' ');
            daftarLaptop[i].merkLaptop = inputMerkModel.substr(0, posisiSpasi);
            daftarLaptop[i].modelLaptop = inputMerkModel.substr(posisiSpasi + 1);

            string inputHarga;
            cout << "Masukkan harga laptop baru (gunakan titik sebagai pemisah ribuan): ";
            cin >> inputHarga;
            inputHarga = hapusTitik(inputHarga);
            daftarLaptop[i].hargaLaptop = stoll(inputHarga);

            cout << "Laptop berhasil diupdate!\n";
            break;
        }
    }

    if (!ditemukan) {
        cout << "Laptop dengan ID tersebut tidak ditemukan.\n";
    }
}

// Fungsi untuk menghapus data laptop berdasarkan ID
void hapusLaptop(int* jumlahLaptopPtr) {
    int idLaptop;
    cout << "Masukkan ID laptop yang akan dihapus: ";
    cin >> idLaptop;

    bool ditemukan = false;
    for (int i = 0; i < *jumlahLaptopPtr; i++) {
        if (daftarLaptop[i].idLaptop == idLaptop) {
            ditemukan = true;
            for (int j = i; j < *jumlahLaptopPtr - 1; j++) {
                daftarLaptop[j] = daftarLaptop[j + 1];
            }
            (*jumlahLaptopPtr)--;
            cout << "Laptop berhasil dihapus!\n";
            break;
        }
    }

    if (!ditemukan) {
        cout << "Laptop dengan ID tersebut tidak ditemukan.\n";
    }
}

// Fungsi untuk menu
int main() {
    int pilihan;
    int* jumlahLaptopPtr = &jumlahLaptop;

    do {
        cout << "\nManajemen Penjualan Laptop\n";
        cout << "1. Tambah Laptop\n";
        cout << "2. Tampilkan Laptop\n";
        cout << "3. Update Laptop\n";
        cout << "4. Hapus Laptop\n";
        cout << "5. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahLaptop(jumlahLaptopPtr, daftarLaptop);
                break;
            case 2:
                tampilkanLaptop(jumlahLaptop, daftarLaptop);
                break;
            case 3:
                updateLaptop(jumlahLaptop);
                break;
            case 4:
                hapusLaptop(jumlahLaptopPtr);
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 5);

    return 0;
}