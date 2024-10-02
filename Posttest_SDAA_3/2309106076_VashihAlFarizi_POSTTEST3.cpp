#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// struct untuk menyimpan data laptop
struct Node {
    int idLaptop;
    string merkLaptop;
    string modelLaptop;
    long long hargaLaptop;
    Node* next;
};

Node* head = nullptr;

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
void tambahLaptop(int& jumlahLaptop) {
    Node* nodeBaru = new Node();
    nodeBaru->idLaptop = jumlahLaptop + 1;
    nodeBaru->next = nullptr;

    string inputMerkModel;
    cout << "Masukkan merk dan model laptop (pisahkan dengan spasi): ";
    cin.ignore();
    getline(cin, inputMerkModel);
    size_t posisiSpasi = inputMerkModel.find(' ');
    nodeBaru->merkLaptop = inputMerkModel.substr(0, posisiSpasi);
    nodeBaru->modelLaptop = inputMerkModel.substr(posisiSpasi + 1);

    string inputHarga;
    cout << "Masukkan harga laptop (gunakan titik sebagai pemisah ribuan): ";
    cin >> inputHarga;
    inputHarga = hapusTitik(inputHarga);
    nodeBaru->hargaLaptop = stoll(inputHarga);

    if (head == nullptr) {
        head = nodeBaru;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }

    jumlahLaptop++;
    cout << "Laptop berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan semua laptop
void tampilkanLaptop(int jumlahLaptop) {
    if (jumlahLaptop == 0) {
        cout << "Tidak ada data laptop.\n";
    } else {
        Node* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->idLaptop
                 << ", Merk: " << temp->merkLaptop
                 << ", Model: " << temp->modelLaptop
                 << ", Harga: " << formatRibuan(temp->hargaLaptop) << endl;
            temp = temp->next;
        }
    }
}

// Fungsi untuk mengupdate data laptop berdasarkan ID
void updateLaptop(int jumlahLaptop) {
    int idLaptop;
    cout << "Masukkan ID laptop yang akan diupdate: ";
    cin >> idLaptop;
    cin.ignore();

    Node* temp = head;
    while (temp != nullptr) {
        if (temp->idLaptop == idLaptop) {
            string inputMerkModel;
            cout << "Masukkan merk dan model laptop baru (pisahkan dengan spasi): ";
            getline(cin, inputMerkModel);

            size_t posisiSpasi = inputMerkModel.find(' ');
            temp->merkLaptop = inputMerkModel.substr(0, posisiSpasi);
            temp->modelLaptop = inputMerkModel.substr(posisiSpasi + 1);

            string inputHarga;
            cout << "Masukkan harga laptop baru (gunakan titik sebagai pemisah ribuan): ";
            cin >> inputHarga;
            inputHarga = hapusTitik(inputHarga);
            temp->hargaLaptop = stoll(inputHarga);

            cout << "Laptop berhasil diupdate!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Laptop dengan ID tersebut tidak ditemukan.\n";
}

// Fungsi untuk menghapus data laptop berdasarkan ID
void hapusLaptop(int& jumlahLaptop) {
    int idLaptop;
    cout << "Masukkan ID laptop yang akan dihapus: ";
    cin >> idLaptop;

    if (head == nullptr) {
        cout << "Linked List kosong.\n";
        return;
    }

    if (head->idLaptop == idLaptop) {
        Node* temp = head;
        head = head->next;
        delete temp;
        jumlahLaptop--;
        cout << "Laptop berhasil dihapus!\n";
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr && temp->next->idLaptop != idLaptop) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Laptop dengan ID tersebut tidak ditemukan.\n";
    } else {
        Node* nodeHapus = temp->next;
        temp->next = nodeHapus->next;
        delete nodeHapus;
        jumlahLaptop--;
        cout << "Laptop berhasil dihapus!\n";
    }
}

// Fungsi untuk menu
int main() {
    int pilihan;
    int jumlahLaptop = 0;

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
                tambahLaptop(jumlahLaptop);
                break;
            case 2:
                tampilkanLaptop(jumlahLaptop);
                break;
            case 3:
                updateLaptop(jumlahLaptop);
                break;
            case 4:
                hapusLaptop(jumlahLaptop);
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