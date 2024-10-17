#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

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

// Fungsi untuk membersihkan layar
void clearScreen() {
    system(CLEAR);
}

// Prototipe fungsi enqueue dan dequeue
void enqueue(Node** front, Node** rear, int& jumlahLaptop);
void dequeue(Node** front, Node** rear, int& jumlahLaptop);

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
    cout << "Masukkan pilihan: ";
    cin.ignore(); 
    cin.get(); 
    clearScreen();
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

// Fungsi untuk mengubah LinkedList menjadi array untuk pengurutan
int linkedListToArray(Node* head, long long* arr) {
    int length = 0;
    while (head != nullptr) {
        arr[length++] = head->hargaLaptop;
        head = head->next;
    }
    return length;
}

// Fungsi untuk mengubah array menjadi LinkedList setelah pengurutan
void arrayToLinkedList(Node* head, long long* arr, int length) {
    for (int i = 0; i < length; i++) {
        head->hargaLaptop = arr[i];
        head = head->next;
    }
}

// Fungsi Merge Sort (Ascending)
void merge(long long* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    long long* L = new long long[n1];
    long long* R = new long long[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
    delete[] L;
    delete[] R;
}

void mergeSort(long long* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Fungsi Quick Sort (Descending)
void quickSort(long long* arr, int low, int high) {
    if (low < high) {
        long long pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] > pivot) { // Descending
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Fungsi untuk sorting secara ascending menggunakan Merge Sort
void sortAscending(Node* head) {
    long long arr[100];
    int length = linkedListToArray(head, arr);
    mergeSort(arr, 0, length - 1);
    arrayToLinkedList(head, arr, length);
}

// Fungsi untuk sorting secara descending menggunakan Quick Sort
void sortDescending(Node* head) {
    long long arr[100];
    int length = linkedListToArray(head, arr);
    quickSort(arr, 0, length - 1);
    arrayToLinkedList(head, arr, length);
}

// Fungsi untuk menampilkan stack dengan sorting (pilih ascending/descending)
void displayStack(Node* top) {
    if (top == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }

    int pilihan;
    cout << "Tampilkan laptop dengan urutan:\n";
    cout << "1. Ascending (Harga rendah ke tinggi)\n";
    cout << "2. Descending (Harga tinggi ke rendah)\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;

    // Sorting sebelum ditampilkan
    if (pilihan == 1) {
        sortAscending(top);
    } else if (pilihan == 2) {
        sortDescending(top);
    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    clearScreen(); // Bersihkan layar sebelum menampilkan

    Node* temp = top;
    while (temp != nullptr) {
        cout << "ID: " << temp->idLaptop
             << ", Merk: " << temp->merkLaptop
             << ", Model: " << temp->modelLaptop
             << ", Harga: " << formatRibuan(temp->hargaLaptop) << endl;
        temp = temp->next;
    }
    
    // Meminta pengguna untuk menekan sembarang untuk keluar
    cout << "Ketik sembarang untuk keluar: ";
    cin.ignore();
    cin.get();
    clearScreen();
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
        *front = nodeBaru; // Jika antrian kosong
        *rear = nodeBaru;  // Front dan rear menunjuk ke simpul baru
    } else {
        (*rear)->next = nodeBaru; // Menetapkan simpul baru sebagai simpul berikutnya dari rear
        *rear = nodeBaru; // Memperbarui rear ke simpul baru
    }

    cout << "Laptop berhasil ditambahkan ke queue!\n";
}

// Fungsi untuk dequeue laptop dari Queue (menghapus dari depan)
void dequeue(Node** front, Node** rear, int& jumlahLaptop) {
    if (*front == nullptr) { // Memeriksa apakah Queue kosong
        cout << "Queue kosong.\n";
        return;
    }

    Node* temp = *front; // Menyimpan simpul depan
    *front = (*front)->next; // Memperbarui front ke simpul berikutnya

    if (*front == nullptr) {
        *rear = nullptr; // Jika Queue menjadi kosong, rear juga harus diatur menjadi null
    }

    delete temp; // Menghapus simpul yang telah dikeluarkan
    jumlahLaptop--; // Mengurangi jumlah laptop
    cout << "Laptop berhasil dihapus dari queue!\n";
}

// Fungsi untuk menampilkan queue (tambahkan sorting jika perlu)
void displayQueue(Node* front) {
    if (front == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }

    int pilihan;
    cout << "Tampilkan laptop dengan urutan:\n";
    cout << "1. Ascending (Harga rendah ke tinggi)\n";
    cout << "2. Descending (Harga tinggi ke rendah)\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;

    // Sorting sebelum ditampilkan
    if (pilihan == 1) {
        sortAscending(front);
    } else if (pilihan == 2) {
        sortDescending(front);
    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    clearScreen(); // Bersihkan layar sebelum menampilkan

    Node* temp = front;
    while (temp != nullptr) {
        cout << "ID: " << temp->idLaptop
             << ", Merk: " << temp->merkLaptop
             << ", Model: " << temp->modelLaptop
             << ", Harga: " << formatRibuan(temp->hargaLaptop) << endl;
        temp = temp->next;
    }
    
    // Meminta pengguna untuk menekan sembarang untuk keluar
    cout << "Ketik sembarang untuk keluar: ";
    cin.ignore(); 
    cin.get(); 
    clearScreen(); 
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
        clearScreen(); // Bersihkan layar sebelum menampilkan menu
        cout << "Pilih struktur data yang ingin digunakan:\n";
        cout << "1. Stack\n";
        cout << "2. Queue\n";
        cout << "3. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihanStrukturData;

        if (pilihanStrukturData == 1) {
            // Menu untuk Stack
            do {
                cout << "Menu Stack\n";
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
                cout << "Menu Queue\n";
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
