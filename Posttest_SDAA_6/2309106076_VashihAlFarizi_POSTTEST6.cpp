#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
    int idLaptop;
    string merkLaptop;
    string modelLaptop;
    long long hargaLaptop;
    Node* next;
};

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

// Menambahkan laptop ke Stack
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
    cout << "Masukkan harga laptop (tanpa menggunakan titik sebagai pemisah ribuan): ";
    cin >> inputHarga;
    nodeBaru->hargaLaptop = stoll(inputHarga);

    nodeBaru->next = *top;
    *top = nodeBaru;

    cout << "Laptop berhasil ditambahkan ke stack!\n";
}

// Hapus laptop dari Stack
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

// Tampilkan Stack
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

// Menambahkan laptop ke Queue
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
    cout << "Masukkan harga laptop (tanpa menggunakan titik sebagai pemisah ribuan): ";
    cin >> inputHarga;
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

// Hapus laptop dari Queue
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

// Tampilkan Queue
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

// Fungsi pencarian menggunakan metode Fibonacci
bool pencarianFibonacci(Node* head, string merk, string model) {
    vector<Node*> nodeList;
    Node* current = head;
    
    // Menyimpan node dalam vector
    while (current != nullptr) {
        nodeList.push_back(current);
        current = current->next;
    }

    int n = nodeList.size();
    int fibMm2 = 0;
    int fibMm1 = 1;
    int fibM = fibMm1 + fibMm2;

    // Mencari Fibonacci yang lebih besar dari atau sama dengan n
    while (fibM < n) {
        fibMm2 = fibMm1;
        fibMm1 = fibM;
        fibM = fibMm1 + fibMm2;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMm2, n - 1);

        if (nodeList[i]->merkLaptop < merk) {
            fibM = fibMm1;
            fibMm1 = fibMm2;
            fibMm2 = fibM - fibMm1;
            offset = i;
        } else if (nodeList[i]->merkLaptop > merk) {
            fibM = fibMm2;
            fibMm1 -= fibMm2;
            fibMm2 = fibM - fibMm1;
        } else {
            if (nodeList[i]->modelLaptop == model) {
                cout << "Laptop ditemukan dengan metode Fibonacci: ID: " << nodeList[i]->idLaptop
                     << ", Merk: " << nodeList[i]->merkLaptop
                     << ", Model: " << nodeList[i]->modelLaptop
                     << ", Harga: " << formatRibuan(nodeList[i]->hargaLaptop) << endl;
                return true;
            }
            return false;
        }
    }

    if (fibMm1 && offset + 1 < n && nodeList[offset + 1]->merkLaptop == merk &&
        nodeList[offset + 1]->modelLaptop == model) {
        cout << "Laptop ditemukan dengan metode Fibonacci: ID: " << nodeList[offset + 1]->idLaptop
             << ", Merk: " << nodeList[offset + 1]->merkLaptop
             << ", Model: " << nodeList[offset + 1]->modelLaptop
             << ", Harga: " << formatRibuan(nodeList[offset + 1]->hargaLaptop) << endl;
        return true;
    }

    return false;
}

// Fungsi pencarian menggunakan metode Jump Search
bool pencarianJump(Node* head, string merk, string model) {
    vector<Node*> nodeList;
    Node* current = head;

    // Menyimpan node dalam vector
    while (current != nullptr) {
        nodeList.push_back(current);
        current = current->next;
    }

    int n = nodeList.size();
    int step = sqrt(n);
    int prev = 0;

    while (nodeList[min(step, n) - 1]->merkLaptop < merk) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return false;
    }

    while (nodeList[prev]->merkLaptop < merk) {
        prev++;
        if (prev == min(step, n)) return false;
    }

    if (nodeList[prev]->merkLaptop == merk && nodeList[prev]->modelLaptop == model) {
        cout << "Laptop ditemukan dengan metode Jump Search: ID: " << nodeList[prev]->idLaptop
             << ", Merk: " << nodeList[prev]->merkLaptop
             << ", Model: " << nodeList[prev]->modelLaptop
             << ", Harga: " << formatRibuan(nodeList[prev]->hargaLaptop) << endl;
        return true;
    }

    return false;
}

// Fungsi pencarian menggunakan metode Boyer-Moore
bool pencarianBoyerMoore(Node* head, string merk, string model) {
    Node* current = head;
    while (current != nullptr) {
        if (current->merkLaptop == merk && current->modelLaptop == model) {
            cout << "Laptop ditemukan dengan metode Boyer-Moore: ID: " << current->idLaptop
                 << ", Merk: " << current->merkLaptop
                 << ", Model: " << current->modelLaptop
                 << ", Harga: " << formatRibuan(current->hargaLaptop) << endl;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Sub-menu Pencarian untuk Stack
void menuPencarianStack(Node* head) {
    if (head == nullptr) {
        cout << "Stack kosong, tidak ada laptop untuk dicari.\n";
        return;
    }

    string merk, model;
    cout << "Masukkan merk laptop yang ingin dicari: ";
    cin >> merk;
    cout << "Masukkan model laptop yang ingin dicari: ";
    cin >> model;

    int pilihanPencarian;
    do {
        cout << "Pilih metode pencarian:\n";
        cout << "1. Fibonacci Search\n";
        cout << "2. Jump Search\n";
        cout << "3. Boyer-Moore Search\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilihan Anda: ";
        cin >> pilihanPencarian;

        switch (pilihanPencarian) {
            case 1:
                if (!pencarianFibonacci(head, merk, model)) {
                    cout << "Laptop tidak ditemukan dengan metode Fibonacci.\n";
                }
                break;
            case 2:
                if (!pencarianJump(head, merk, model)) {
                    cout << "Laptop tidak ditemukan dengan metode Jump Search.\n";
                }
                break;
            case 3:
                if (!pencarianBoyerMoore(head, merk, model)) {
                    cout << "Laptop tidak ditemukan dengan metode Boyer-Moore.\n";
                }
                break;
            case 4:
                cout << "Kembali ke menu utama.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihanPencarian != 4);
}

// Sub-menu Pencarian untuk Queue
void menuPencarianQueue(Node* front) {
    if (front == nullptr) {
        cout << "Queue kosong, tidak ada laptop untuk dicari.\n";
        return;
    }

    string merk, model;
    cout << "Masukkan merk laptop yang ingin dicari: ";
    cin >> merk;
    cout << "Masukkan model laptop yang ingin dicari: ";
    cin >> model;

    int pilihanPencarian;
    do {
        cout << "Pilih metode pencarian:\n";
        cout << "1. Fibonacci Search\n";
        cout << "2. Jump Search\n";
        cout << "3. Boyer-Moore Search\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilihan Anda: ";
        cin >> pilihanPencarian;

        switch (pilihanPencarian) {
            case 1:
                if (!pencarianFibonacci(front, merk, model)) {
                    cout << "Laptop tidak ditemukan dengan metode Fibonacci.\n";
                }
                break;
            case 2:
                if (!pencarianJump(front, merk, model)) {
                    cout << "Laptop tidak ditemukan dengan metode Jump Search.\n";
                }
                break;
            case 3:
                if (!pencarianBoyerMoore(front, merk, model)) {
                    cout << "Laptop tidak ditemukan dengan metode Boyer-Moore.\n";
                }
                break;
            case 4:
                cout << "Kembali ke menu utama.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihanPencarian != 4);
}

// Menu utama program
void menuUtama() {
    Node* stackTop = nullptr;
    Node* queueFront = nullptr;
    Node* queueRear = nullptr;
    int jumlahLaptopStack = 0;
    int jumlahLaptopQueue = 0;

    int pilihanStrukturData;

    do {
        cout << "Pilih struktur data:\n";
        cout << "1. Stack\n";
        cout << "2. Queue\n";
        cout << "3. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihanStrukturData;

        if (pilihanStrukturData == 1) {
            int pilihanOperasi;
            do {
                cout << "Operasi pada Stack:\n";
                cout << "1. Tambah laptop ke Stack\n";
                cout << "2. Hapus laptop dari Stack\n";
                cout << "3. Tampilkan Stack\n";
                cout << "4. Cari laptop\n";
                cout << "5. Kembali ke menu utama\n";
                cout << "Pilihan Anda: ";
                cin >> pilihanOperasi;

                switch (pilihanOperasi) {
                    case 1:
                        pushStack(&stackTop, jumlahLaptopStack);
                        break;
                    case 2:
                        popStack(&stackTop, jumlahLaptopStack);
                        break;
                    case 3:
                        displayStack(stackTop);
                        break;
                    case 4:
                        menuPencarianStack(stackTop);
                        break;
                    case 5:
                        cout << "Kembali ke menu utama.\n";
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
            } while (pilihanOperasi != 5);
        } else if (pilihanStrukturData == 2) {
            int pilihanOperasi;
            do {
                cout << "Operasi pada Queue:\n";
                cout << "1. Tambah laptop ke Queue\n";
                cout << "2. Hapus laptop dari Queue\n";
                cout << "3. Tampilkan Queue\n";
                cout << "4. Cari laptop\n";
                cout << "5. Kembali ke menu utama\n";
                cout << "Pilihan Anda: ";
                cin >> pilihanOperasi;

                switch (pilihanOperasi) {
                    case 1:
                        enqueue(&queueFront, &queueRear, jumlahLaptopQueue);
                        break;
                    case 2:
                        dequeue(&queueFront, &queueRear, jumlahLaptopQueue);
                        break;
                    case 3:
                        displayQueue(queueFront);
                        break;
                    case 4:
                        menuPencarianQueue(queueFront);
                        break;
                    case 5:
                        cout << "Kembali ke menu utama.\n";
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
            } while (pilihanOperasi != 5);
        } else if (pilihanStrukturData == 3) {
            cout << "Keluar dari program.\n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihanStrukturData != 3);
}

int main() {
    menuUtama();
    return 0;
}