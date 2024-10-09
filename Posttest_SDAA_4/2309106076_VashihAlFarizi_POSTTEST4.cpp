#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Struct untuk menyimpan data laptop
struct Node {
    int idLaptop;
    string merkLaptop;
    string modelLaptop;
    long long hargaLaptop;
    Node* next;
};

// Fungsi untuk menghapus titik dari string
string hapusTitik(string input) {
    input.erase(remove(input.begin(), input.end(), '.'), input.end());
    return input;
}

// Fungsi untuk memformat angka ke dalam format ribuan
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

// Fungsi untuk menambahkan laptop ke Stack (push ke atas)
void pushStack(Node** top, int& jumlahLaptop) {
    Node* nodeBaru = new Node();
    nodeBaru->idLaptop = ++jumlahLaptop;

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

    nodeBaru->next = *top;
    *top = nodeBaru;

    cout << "Laptop berhasil ditambahkan ke stack!\n";
}

// Fungsi untuk menghapus laptop dari Stack (pop dari atas)
void popStack(Node** top, int& jumlahLaptop) {
    if (*top == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }

    Node* temp = *top;
    *top = (*top)->next;
    delete temp;
    jumlahLaptop--;

    cout << "Laptop berhasil dihapus dari stack!\n";
}

// Fungsi untuk menampilkan semua laptop di Stack
void displayStack(Node* top) {
    if (top == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }

    Node* temp = top;
    while (temp != nullptr) {
        cout << "ID: " << temp->idLaptop
             << ", Merk: " << temp->merkLaptop
             << ", Model: " << temp->modelLaptop
             << ", Harga: " << formatRibuan(temp->hargaLaptop) << endl;
        temp = temp->next;
    }
}

// Fungsi untuk enqueue laptop ke Queue (menambah ke belakang)
void enqueue(Node** front, Node** rear, int& jumlahLaptop) {
    Node* nodeBaru = new Node();
    nodeBaru->idLaptop = ++jumlahLaptop;
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

    if (*rear == nullptr) {
        *front = nodeBaru;
        *rear = nodeBaru;
    } else {
        (*rear)->next = nodeBaru;
        *rear = nodeBaru;
    }

    cout << "Laptop berhasil ditambahkan ke queue!\n";
}

// Fungsi untuk dequeue laptop dari Queue (menghapus dari depan)
void dequeue(Node** front, Node** rear, int& jumlahLaptop) {
    if (*front == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }

    Node* temp = *front;
    *front = (*front)->next;

    if (*front == nullptr) {
        *rear = nullptr;
    }

    delete temp;
    jumlahLaptop--;

    cout << "Laptop berhasil dihapus dari queue!\n";
}

// Fungsi untuk menampilkan semua laptop di Queue
void displayQueue(Node* front) {
    if (front == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }

    Node* temp = front;
    while (temp != nullptr) {
        cout << "ID: " << temp->idLaptop
             << ", Merk: " << temp->merkLaptop
             << ", Model: " << temp->modelLaptop
             << ", Harga: " << formatRibuan(temp->hargaLaptop) << endl;
        temp = temp->next;
    }
}

// Fungsi untuk menampilkan menu utama
void menuUtama() {
    int pilihanStrukturData;
    int pilihanOperasi;
    Node* stackTop = nullptr;        // Stack
    Node *queueFront = nullptr, *queueRear = nullptr; // Queue
    int jumlahLaptopStack = 0; // Variabel untuk menghitung jumlah laptop di Stack
    int jumlahLaptopQueue = 0;  // Variabel untuk menghitung jumlah laptop di Queue

    do {
        cout << "Pilih struktur data yang ingin digunakan:\n";
        cout << "1. Stack\n";
        cout << "2. Queue\n";
        cout << "3. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihanStrukturData;

        if (pilihanStrukturData == 1) {
            // Menu untuk Stack
            do {
                cout << "\nMenu Stack\n";
                cout << "1. Tambah Laptop\n";
                cout << "2. Tampilkan Laptop\n";
                cout << "3. Hapus Laptop\n";
                cout << "4. Keluar\n";
                cout << "Masukkan pilihan: ";
                cin >> pilihanOperasi;

                switch (pilihanOperasi) {
                    case 1:
                        pushStack(&stackTop, jumlahLaptopStack);
                        break;
                    case 2:
                        displayStack(stackTop);
                        break;
                    case 3:
                        popStack(&stackTop, jumlahLaptopStack);
                        break;
                    case 4:
                        cout << "Keluar dari menu Stack.\n";
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
            } while (pilihanOperasi != 4);
        } else if (pilihanStrukturData == 2) {
            // Menu untuk Queue
            do {
                cout << "\nMenu Queue\n";
                cout << "1. Tambah Laptop \n";
                cout << "2. Tampilkan Laptop \n";
                cout << "3. Hapus Laptop \n";
                cout << "4. Keluar\n";
                cout << "Masukkan pilihan: ";
                cin >> pilihanOperasi;

                switch (pilihanOperasi) {
                    case 1:
                        enqueue(&queueFront, &queueRear, jumlahLaptopQueue);
                        break;
                    case 2:
                        displayQueue(queueFront);
                        break;
                    case 3:
                        dequeue(&queueFront, &queueRear, jumlahLaptopQueue);
                        break;
                    case 4:
                        cout << "Keluar dari menu Queue.\n";
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
            } while (pilihanOperasi != 4);
        } else if (pilihanStrukturData == 3) {
            cout << "Keluar dari program.\n";
            break; // Keluar dari program
        } else {
            cout << "Pilihan struktur data tidak valid.\n";
        }
    } while (true);
}

int main() {
    menuUtama();
    return 0;
}