#include <iostream>
#include <fstream>
using namespace std;

//   LINKEDLIST PASIEN

struct pasien{
    string nama;
    int umur;
    string keluhanPasien;
    string statusMedis;
    pasien* next;
    pasien* prev;
};

pasien* head = nullptr;

//   STACK PASIEN PENANGANAN

struct pasienPenangan{
    string nama;
    int umur;
    string keluhanPasien;
    string statusMedis;
    string dokter;
    pasienPenangan* next;
};

pasienPenangan* headP = nullptr;
pasien* berhasil = nullptr;

int totPasienAktif = 0;
int totPasienDitangani = 0;
int totPasienBerhasil = 0;

int main();

void listAllPasien(){
    cout << "\n============================\n";
    cout << "   MENAMPILKAN DATA PASIEN   \n";
    cout << "============================\n";

    pasien* p = head;
    int num = 1;

    if (!p) {
        cout << "Tidak ada pasien yang terdaftar." << endl;
        return;
    }

    while (p) {
        cout << num << ") " << p->nama << " - Umur: " << p->umur 
             << " - Keluhan: " << p->keluhanPasien 
             << " - Status medis: " << p->statusMedis << endl;
        cout << "Total Pasien: " << totPasienAktif << endl;
        num++;
        p = p->next;
    }
}

//  PUSH PASIEN KE STACK PENANGANAN

void pushPasien(pasien* p) {
    pasienPenangan* newPasien = new pasienPenangan();

    newPasien->nama = p->nama;
    newPasien->umur = p->umur;
    newPasien->keluhanPasien = p->keluhanPasien;
    newPasien->statusMedis = "Dalam penanganan";

    if(p == head) {
        head = head->next;
        if(head) {
            head->prev = nullptr;
        }
    } else {
        pasien* temp = head;
        while(temp && temp->next != p) {
            temp = temp->next;
        }
        if(temp) {
            temp->next = p->next;
            if(p->next) {
                p->next->prev = temp;
            }
        }
    }

    newPasien->next = headP;
    headP = newPasien;
    totPasienDitangani++;
}

//  ENQUEUE PASIEN

void enqueuePasien(){
    pasien* p = new pasien();
    
    cin.ignore();
    cout << "Masukkan nama pasien: ";
    getline(cin, p->nama);
    cout << "Masukkan umur pasien: ";
    cin >> p->umur;
    cin.ignore();
    cout << "Keluhan pasien: ";
    getline(cin, p->keluhanPasien);
    p->statusMedis = "Dalam antrean";

    if (!head) {
        head = p;
    } else {
        pasien* ph = head;
        while (ph->next != NULL) {
            ph = ph->next;
        }
        ph->next = p;
        p->prev = ph;
        
    }

    cout << "Pasien berhasil didata!" << endl;
    totPasienAktif++;
}

//   QUEUE PASIEN

void queuePasien(){
    pasien* p = head;
    if (p == NULL) {
        cout << "Tidak ada pasien yang terdaftar." << endl;
        return;
    }

    int num = 1;

    cout << "Daftar Pasien:" << endl;
    while (p != NULL) {
        cout << num << ". " << "- Nama: " << p->nama << ", Umur: " << p->umur << ", Diagnosa: "<< p->keluhanPasien << ", Status medis: " << p->statusMedis << endl;
        p = p->next;
    }
    cout << "Total Pasien: " << totPasienAktif << endl;
}

//  DEQUEUE PASIEN

void dequeuePasien(){
    if (!head) {
        cout << "Tidak ada pasien yang terdaftar." << endl;
        return;
    }

    pasien* p = head;

    head = head->next;
    if (head) {
        head->prev = nullptr;
    }

    pushPasien(p);

    totPasienAktif--;

    cout << "Pasien bernama " << p->nama << " dipindahkan ke ruang kamar." << endl;
    cout << "Sisa pasien dalam antrean: " << totPasienAktif << endl;
}

void cariPasien(){
    string nama;
    cout << "Masukkan nama pasien yang dicari: ";
    cin >> nama;

    pasien* p = head;
    while (p) {
        cout << "Pasien ditemukan!" << endl;
        cout << "- Nama: " << p->nama
             << ", Umur: " << p->umur 
             << ", Diagnosa: " << p->keluhanPasien << endl;
        p = p->next;
    }
    cout << "Pasien tidak ditemukan!" << endl;
}

void swapPasien(pasien* a, pasien* b) {
    string tempNama = a->nama;
    int tempUmur = a->umur;
    string tempKeluhan = a->keluhanPasien;
    string tempStatus = a->statusMedis;

    a->nama = b->nama;
    a->umur = b->umur;
    a->keluhanPasien = b->keluhanPasien; 
    a->statusMedis = b->statusMedis;

    b->nama = tempNama;
    b->umur = tempUmur;
    b->keluhanPasien = tempKeluhan;
    b->statusMedis = tempStatus;
}

int partition(pasien arr[], int low, int high) {
    int pivot = arr[high].umur;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].umur > pivot) { // Sort descending (dari tertua)
            i++;
            swapPasien(&arr[i], &arr[j]);
        }
    }
    swapPasien(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(pasien arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sortUmurPasien() {
    if (!head || !head->next) {
        cout << "Tidak ada pasien yang cukup untuk diurutkan" << endl;
        return;
    }

    // linked list to array
    pasien* arr = new pasien[totPasienAktif];
    pasien* current = head;
    int i = 0;
    
    while (current != NULL) {
        arr[i] = *current;
        current = current->next;
        i++;
    }

    quickSort(arr, 0, totPasienAktif - 1);

    cout << "\nDaftar Pasien (Lansia - anak):" << endl;
    for (int i = 0; i < totPasienAktif; i++) {
        cout << "- Nama: " << arr[i].nama 
             << ", Umur: " << arr[i].umur 
             << ", Diagnosa: " << arr[i].keluhanPasien 
             << ", Status medis: " << arr[i].statusMedis << endl;
    }

    char pilihan;
    cout << "\nTangani pasien teratas? ";    
    cin >> pilihan;

    if (pilihan == 'y' || pilihan == 'Y'){
        pasien* p = head;
        pasien* prev = nullptr;

        while (p){
            if (p->nama == arr[0].nama && p->umur == arr[0].umur){

                pushPasien(p);

                if(prev == nullptr){
                    head = p->next;
                    if(head){
                        head->prev = nullptr;
                    }
                } else {
                    prev->next = p->next;
                    if(p->next){
                        p->next->prev = prev;
                    }
                }
                delete p;
                totPasienAktif--;

                cout << "Pasien " << arr[0].nama << " masuk ke ruangan. " << endl;
                p->statusMedis = "Dalam penanganan";
                cout << "Status pasien : " << p->statusMedis << endl;
                break;
            }
            prev = p;
            p = p->next;
        }
    }

    delete[] arr;
}

void tanganiPasien(){
    cout << "Pilihan penanganan pasien : " << endl;
    cout << "1. Prioritas umur" << endl;
    cout << "2. Tangani langsung (FIFO)" << endl;

    int pilih;
    cout << "Pilih menu: ";
    cin >> pilih;

    switch(pilih){
        case 1:
            sortUmurPasien();
            break;
        case 2:
            dequeuePasien();
            return;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
}

//          FARMASI HASH TABLE
//          FARMASI HASH TABLE

const int TABLE_SIZE = 100;
struct Obat {
    string namaPasien;
    string namaObat;
    Obat* next;
};

Obat* hashTable[TABLE_SIZE] = {nullptr};

int hashFunc(string key) {
    int hash = 0;
    for (char c : key) hash += c;
    return hash % TABLE_SIZE;
}

void tambahObat(string namaPasien, string namaObat) {
    int index = hashFunc(namaPasien);
    Obat* baru = new Obat{namaPasien, namaObat, nullptr};
    if (!hashTable[index]) {
        hashTable[index] = baru;
    } else {
        Obat* temp = hashTable[index];
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
}

void cariObat(string namaPasien) {
    int index = hashFunc(namaPasien);
    Obat* temp = hashTable[index];
    while (temp) {
        if (temp->namaPasien == namaPasien) {
            cout << "Obat untuk " << namaPasien << ": " << temp->namaObat << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Obat untuk pasien tidak ditemukan." << endl;
}

void farmasi(){
    cout << "\n============================\n";
    cout << "         MENU FARMASI        \n";
    cout << "============================\n";

    while (true) {
        cout << "1. Tambah Obat" << endl;
        cout << "2. Cari Obat" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;

        int pilihan;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                pasien* ph = berhasil;

                string namaPasien, namaObat;
                cin.ignore();
                cout << "Masukkan nama pasien: ";
                getline(cin, namaPasien);

                cout << "Keluhan pasien: " << ph->keluhanPasien << endl;

                cin.ignore();
                cout << "Masukkan nama obat: ";
                getline(cin, namaObat);

                if (namaPasien == ph->nama){
                    tambahObat(namaPasien, namaObat);
                    cout << "Obat berhasil diserahkan kepada " << ph->nama << endl;
                }else{
                    cout << "Pasien belum terdata." << endl;
                }

                break;
            }
            case 2: {
                pasien* ph = berhasil;

                string namaPasien;

                cin.ignore();
                cout << "Masukkan nama pasien yang ingin dicari obatnya: ";
                getline(cin, namaPasien);
                
                if (namaPasien == ph->nama){

                    cariObat(namaPasien);
                    cout << "Obat berhasil ditambahkan" << endl;

                }else{

                    cout << "Pasien belum terdata." << endl;

                }
                break;
            }
            case 3:
                return; 
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }
}

//      TREE TREE TREE
//      TREE TREE TREE

struct TreeNode {
    string nama;
    string keluhanPasien;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* root = nullptr;

TreeNode* insertTree(TreeNode* node, string nama, string penyakit) {
    if (!node) {
        node = new TreeNode{nama, penyakit, nullptr, nullptr};
    } else if (nama < node->nama) {
        node->left = insertTree(node->left, nama, penyakit);
    } else {
        node->right = insertTree(node->right, nama, penyakit);
    }
    return node;
}

void tampilkanTree(TreeNode* node) {
    if (!node) return;
    tampilkanTree(node->left);
    cout << "Nama: " << node->nama << " - Penyakit: " << node->keluhanPasien << endl;
    tampilkanTree(node->right);
}

//    GRAPH GRAPH GRAPH
//    GRAPH GRAPH GRAPH
// Rujukan antar rumah sakit

const int MAX_RS = 5;
string rumahSakit[MAX_RS] = {"RS Dr. Rudjianto", "RS Dr. Soetomo", "RS Dr. Soegiri", "RS_C", "RS_D"};
bool rujukan[MAX_RS][MAX_RS] = {false};

void inisialisasiRujukan() {
    rujukan[0][1] = rujukan[1][0] = true;
    rujukan[0][2] = rujukan[2][0] = true;
    rujukan[1][3] = rujukan[3][1] = true;
    rujukan[2][4] = rujukan[4][2] = true;
}

void tampilkanRujukan(string dari) {
    int idx = -1;
    for (int i = 0; i < MAX_RS; i++) {
        if (rumahSakit[i] == dari) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "Rumah sakit tidak ditemukan." << endl;
        return;
    }

    cout << "Rujukan dari " << dari << ": ";
    for (int j = 0; j < MAX_RS; j++) {
        if (rujukan[idx][j]) {
            cout << rumahSakit[j] << ", ";
        }
    }
    cout << endl;
}

void ubahStatusMedis(){
    cout << "\n============================\n";
    cout << "   Ubah status medis pasien  \n";
    cout << "============================\n";

    pasienPenangan* p = headP;
    pasienPenangan* prev = nullptr;

    if (p == NULL) {
        cout << "Tidak ada pasien yang terdaftar." << endl;
        return;
    }

    string nama;
    cout << "Masukkan nama pasien: ";
    cin >> nama;

    if(nama == p->nama){
        cout << "Status medis pasien saat ini: " << p->statusMedis << endl;
        cout << "Masukkan status medis baru: ";
        cin >> p->statusMedis;

        if (p->statusMedis == "Selesai" || p->statusMedis == "selesai") {
            pasien* newBerhasil = new pasien();
            newBerhasil->nama = p->nama;
            newBerhasil->umur = p->umur;
            newBerhasil->keluhanPasien = p->keluhanPasien;
            newBerhasil->statusMedis = "Selesai";
            newBerhasil->next = nullptr;
            newBerhasil->prev = nullptr;

            if (!berhasil) {
                berhasil = newBerhasil;
            } else {
                newBerhasil->next = berhasil;
                berhasil->prev = newBerhasil;
                berhasil = newBerhasil;
            }

            if (prev == nullptr) {
                headP = p->next;
            } else {
                prev->next = p->next;
            }
                
            delete p;
            totPasienDitangani--;
            totPasienBerhasil++;
            cout << "Pasien berhasil ditangani dan dipindahkan ke riwayat berhasil." << endl;
            root = insertTree(root, newBerhasil->nama, newBerhasil->keluhanPasien);
            return;

        } else if (p->statusMedis == "Gagal") {
            cout << "Pasien gagal ditangani." << endl;
            cout << "Pasien gagal ditangani. Menampilkan rumah sakit rujukan..." << endl;
            tampilkanRujukan("RS_Induk");
            
        }
        cout << "Status medis pasien berhasil diubah!" << endl;
    } else {
        cout << "Pasien tidak ditemukan!" << endl;
    }
}

void historyMedis(){
    cout << "\n============================\n";
    cout << "    Riwayat medis pasien    \n";
    cout << "============================\n";

    pasien* pb = berhasil;
    int num;

    while(pb){
        cout << num << ") " << pb->nama << " Umur: " << pb->umur << " - Keluhan: " << pb->keluhanPasien << " - Status medis: " << pb->statusMedis << endl;
        num++;
        pb = pb->next;
    }

}

void statistikAngka(){
    cout << "\n============================\n";
    cout << "   Statistik angka   \n";
    cout << "=====================\n";

    cout << "Total Pasien: " << totPasienAktif << endl;
    cout << "Total Pasien dalam penanganan: " << totPasienDitangani << endl;
    cout << "Total Pasien berhasil ditangani: " << totPasienBerhasil << endl;
}

void statistik(){
    cout << "\n============================\n";
    cout << "   Statistik pasien rawat   \n";
    cout << "============================\n";

    cout << "1. Statistik Angka" << endl;
    cout << "2. Statistik Data (stack)" << endl;

    int pilih;
    cout << "Pilih menu: ";
    cin >> pilih;

    switch(pilih){
        case 1:
            statistikAngka();
            break;
        case 2:
            historyMedis();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
}

void menuUtama(){
    while(true){
        cout << "\n==========\n";
        cout << "   MENU   \n";
        cout << "==========\n";

        cout << "\nSelamat datang di menu!" << endl;
        cout << "1. Input Pasien" << endl;
        cout << "2. List Pasien" << endl;
        cout << "3. Cari Pasien" << endl;
        cout << "4. Kembali ke Menu Utama" << endl;

        int pilih;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch(pilih){
            case 1:
                enqueuePasien();
                break;
            case 2:
                listAllPasien();
                break;
            case 3:
                cariPasien();
                return;
            case 4:
                main();
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    }
}

void menuDokter(){
    while(true){
        cout << "\n================\n";
        cout << "   MENU DOKTER  \n";
        cout << "================\n";

        cout << "1. Lihat Pasien" << endl;
        cout << "2. Tangani Pasien" << endl;
        cout << "3. Ubah Status Medis" << endl;
        cout << "4. Kembali ke Menu Utama" << endl;

        int pilih;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch(pilih){
            case 1:
                queuePasien();
                break;
            case 2:
                tanganiPasien();
                break;
            case 3:
                ubahStatusMedis();
                break;
            case 4:
                main();
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
            }
    }
    
}

void loginDokter(){
    cout << "\n================\n";
    cout << "   MENU DOKTER  \n";
    cout << "================\n";

    cout << "Masukkan ID Dokter: ";
    string ID;
    cin >> ID;
    
    ifstream myfile("dokter.txt");
    if (!myfile) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    string line, nama, id;
    bool ketemu = false;

    while (getline(myfile, line)) {
        if (line.find("Nama Dokter : ") != string::npos) {
            nama = line.substr(13); // Mengambil nama setelah "Nama Dokter : "
            getline(myfile, line); // Membaca baris ID
            if (line.find("ID : ") != string::npos) {
                id = line.substr(5); // Mengambil ID setelah "ID : "
                if (id == ID) {
                    ketemu = true;
                    cout << "Selamat datang, Dr." << nama << endl;
                    menuDokter();
                    break;
                }
            }
        }
    }

    if (!ketemu) {
        cout << "ID Dokter tidak ditemukan!" << endl;
    }
    myfile.close();
}

int main() {
    while(true){
        cout << "\n===============================\n";
        cout << "   RUMAH SAKIT Dr. Rudjianto   \n";
        cout << "===============================\n";

        cout << "\nSelamat datang di sistem informasi rumah sakit!" << endl;
        cout << "1. Menu Utama" << endl;
        cout << "2. Menu Dokter" << endl;
        cout << "3. Menu Farmasi" << endl;
        cout << "4. Statistik" << endl;
        cout << "5. Riwayat pasien" << endl;

        int pilih;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch(pilih){
            case 1:
                menuUtama();
                break;
            case 2:
                loginDokter();
                break;
            case 3:
                farmasi();
                break;
            case 4:
                statistik();
                break;
            case 5:
                cout << "Riwayat pasien (urut nama):" << endl;
                tampilkanTree(root);
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    }
    
    return 0;
}