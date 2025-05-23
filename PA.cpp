#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct node
{
    string nama;
    int harga;
    int stok;
    node *next;
    node *prev;
};

node *head = nullptr;
node *tail = nullptr;
node *nodeArr[100];
int x = 0;

int menu;      // variabel untuk memilih menu di beranda dan fungsi lihat_daftar
char pilihan;  // variabel pilihan untuk operasi do-while apakah ingin melanjutkan program atau tidak
int jml_input; // jmulah input di menu input_baru

void beranda()
{
    // HEADER
    cout << setfill('=') << setw(50) << "" << endl;
    cout << setfill(' ') << setw(20) << "" << "TOKO PIGURA" << endl;
    cout << setfill('=') << setw(50) << "" << endl;

    // PILIHAN MENU MANAJEMEN TOKO
    cout << "Menu:" << endl;
    cout << "1. Input Baru" << endl;                                                   // file
    cout << "2. Tampilkan daftar barang berdasarkan nama secara ascending." << endl;   // bubble sort
    cout << "3. Tampilkan daftar barang berdasarkan nama secara descending." << endl;  // quick sort
    cout << "4. Tampilkan daftar barang berdasarkan harga secara ascending." << endl;  // quick sort
    cout << "5. Tampilkan daftar barang berdasarkan harga secara descending." << endl; // bubble sort
    cout << "6. Tampilkan daftar barang berdasarkan stok secara ascending." << endl;   // bubble sort
    cout << "7. Tampilkan daftar barang berdasarkan stok secara descending." << endl;  // quick sort
    cout << "8. Cari produk berdasarkan nama." << endl;                                // sequence/linear search
    cout << "9. Cari produk berdasarkan harga." << endl;                               // binary search
    cout << "10. Cari produk berdasarkan stok." << endl;                                // binary search
    cout << "11. Edit nama produk di daftar barang" << endl;                           //
    cout << "12. Edit harga produk di daftar barang" << endl;                          //
    cout << "13. Edit stok produk di daftar barang" << endl;                           //
    cout << "14. Hapus produk dari daftar barang" << endl;                             //
    cout << "Pilih menu: ";
    cin >> menu;
}

// untuk normalisasi input
string to_lowercase(string str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 'a' - 'A';
        }
    }
    return str;
}

// convert linked list ke array sebelum pake binary search buat pencarian
void convertListToArray(node *head, node *nodeArr[], int &x)
{
    x = 0;
    node *current = head;

    while (current != nullptr)
    {
        nodeArr[x++] = current;
        current = current->next;
    }
}

// 1. Input Baru
void input_baru()
{
    FILE *file = fopen("databarang.txt", "a");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    cout << setfill('-') << setw(20) << "" << endl;
    cout << "Input Produk" << endl;
    cout << "Jumlah Input: ";
    cin >> jml_input;
    cin.ignore();

    for (int i = 0; i < jml_input; i++)
    {
        node *newNode = new node;
        cout << endl;
        // input dari user
        cout << "Input ke-" << i + 1 << endl;
        cout << "Nama Produk: ";
        getline(cin, newNode->nama);
        cout << "Harga Produk: ";
        cin >> newNode->harga;
        cout << "Stok Produk: ";
        cin >> newNode->stok;
        cin.ignore();

        // simpan input ke file
        fprintf(file, "Nama Produk: %s\n", newNode->nama.c_str());
        fprintf(file, "Harga Produk: %d\n", newNode->harga);
        fprintf(file, "Stok Produk: %d\n\n", newNode->stok);
        cout << endl;

        // newNode disisipkan dari belakang
        newNode->next = nullptr;
        newNode->prev = tail;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "Input Berhasil!" << endl;
    fclose(file);
}

// 2. Tampilkan daftar barang berdasarkan nama secara ascending.
void nama_produk_asc()
{
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    // membaca isi file ke dalam linked list
    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip line kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(file);

    // bubble sort berdasarkan nama secara ascending
    bool swapped;
    node *current;

    do
    {
        swapped = false;
        current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (current->nama > current->next->nama)
            {
                swap(current->nama, current->next->nama);
                swap(current->harga, current->next->harga);
                swap(current->stok, current->next->stok);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    // tampilkan hasil
    node *temp = head;
    cout << "\n DAFTAR BARANG BERDASARKAN NAMA \n";
    while (temp != nullptr)
    {
        cout << "Nama Produk: " << temp->nama
             << "\tHarga Produk: " << temp->harga
             << "\tStok Produk: " << temp->stok << endl;
        temp = temp->next;
    }
}

// partition untuk quicksort
int partition(node *nodeArr[], int low, int high)
{
    node *pivot = nodeArr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (nodeArr[j]->nama > pivot->nama)
        {
            i++;
            swap(nodeArr[i], nodeArr[j]);
        }
    }

    swap(nodeArr[i + 1], nodeArr[high]);
    return i + 1;
}

// quicksort
void quicksort(node *nodeArr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(nodeArr, low, high);
        quicksort(nodeArr, low, pivotIndex - 1);
        quicksort(nodeArr, pivotIndex + 1, high);
    }
}

// 3. Tampilkan daftar barang berdasarkan nama secara descending. 45
node *nama_produk_desc(node *head)
{
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return nullptr;
    }

    // menyimpan isi file sementara untuk parsing
    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    cout << endl;
    // head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip line kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(file);

    convertListToArray(head, nodeArr, x);
    quicksort(nodeArr, 0, x - 1);

    head = nodeArr[0];
    head->prev = nullptr;

    for (int i = 0; i < x - 1; i++)
    {
        nodeArr[i]->next = nodeArr[i + 1];
        nodeArr[i + 1]->prev = nodeArr[i];
    }

    nodeArr[x - 1]->next = nullptr;
    tail = nodeArr[x - 1];

    // tampilkan hasil
    node *temp = head;
    cout << "Daftar barang stok desc: " << endl;
    while (temp != nullptr)
    {
        cout << "Nama Produk: " << temp->nama << "\tHarga Produk: " << temp->harga << "\tStok Produk: " << temp->stok;
        temp = temp->next;
        cout << endl;
    }

    return head;
}

// 4. Tampilkan daftar barang berdasarkan harga secara ascending. 45 quicksort
node *harga_asc(node *head)
{
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return nullptr;
    }

    // menyimpan isi file sementara untuk parsing
    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    cout << endl;
    head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip line kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(file);

    convertListToArray(head, nodeArr, x);
    quicksort(nodeArr, 0, x - 1);

    head = nodeArr[0];
    head->prev = nullptr;

    for (int i = 0; i < x - 1; i++)
    {
        nodeArr[i]->next = nodeArr[i + 1];
        nodeArr[i + 1]->prev = nodeArr[i];
    }

    nodeArr[x - 1]->next = nullptr;
    tail = nodeArr[x - 1];

    // tampilkan hasil
    node *temp = head;
    cout << "Daftar barang stok desc: " << endl;
    while (temp != nullptr)
    {
        cout << "Nama Produk: " << temp->nama << "\tHarga Produk: " << temp->harga << "\tStok Produk: " << temp->stok;
        temp = temp->next;
        cout << endl;
    }

    return head;
}

// 5. Tampilkan daftar barang berdasarkan harga secara descending.
void harga_desc() 
{
FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }
    // menyimpan isi file sementara untuk parsing
    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    cout << endl;

    head = tail = nullptr;
    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip line kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }

    fclose(file);
    bool swapped;
    node *current;

    do
    {
        swapped = false;
        current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (current->harga < current->next->harga)
            {
                swap(current->nama, current->next->nama);
                swap(current->harga, current->next->harga);
                swap(current->stok, current->next->stok);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    // tampilkan hasil
    node *bantu = head;
    cout << "\n DAFTAR BARANG BERDASARKAN HARGA \n";
    while (bantu != nullptr)
    {
        cout << "Nama Produk: " << bantu->nama
             << "\tHarga Produk: " << bantu->harga
             << "\tStok Produk: " << bantu->stok << endl;
        bantu = bantu->next;
    }
}

// 6. Tampilkan daftar barang berdasarkan stok secara ascending. 45
void stok_asc()
{
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    // menyimpan isi file sementara untuk parsing
    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    cout << endl;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip line kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(file);

    // bubble sort stok asc
    bool swapped;

    do
    {
        swapped = false;
        node *current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (current->stok > current->next->stok)
            {
                swap(current->nama, current->next->nama);
                swap(current->harga, current->next->harga);
                swap(current->stok, current->next->stok);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    // tampilkan hasil
    node *temp = head;
    cout << "Daftar barang stok asc: " << endl;
    while (temp != nullptr)
    {
        cout << "Nama Produk: " << temp->nama << "\tHarga Produk: " << temp->harga << "\tStok Produk: " << temp->stok;
        temp = temp->next;
        cout << endl;
    }
}

// 7. Tampilkan daftar barang berdasarkan stok secara descending.
void stok_desc() {}

// 8. Cari produk berdasarkan nama 45
void cari_nama()
{
    string cari;
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    cin.ignore();
    cout << "Masukkan produk yang ingin dicari: ";
    getline(cin, cari);

    // menyimpan isi file sementara untuk parsing
    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    cout << endl;
    head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip line kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(file);

    bool found = false;
    node *current = head;

    while (current != nullptr)
    {
        if (to_lowercase(current->nama) == to_lowercase(cari))
        {
            cout << "Nama Produk: " << current->nama << "\tHarga Produk: " << current->harga << "\tStok Produk: " << current->stok;
            cout << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "Data tidak ditemukan." << endl;
    }
}

// 9. Cari produk berdasarkan harga
void cari_harga() {}

// convert linked list ke array sebelum pake binary search buat pencarian
void converstListToArray(node *head, node *nodeArr[], int &x)
{
    x = 0;
    node *current = head;

    while (current != nullptr)
    {
        nodeArr[x++] = current;
        current = current->next;
    }
}

// 10. Cari produk berdasarkan stok 45
void cari_stok()
{
    int cari, i;
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    cout << "Masukkan stok produk yang ingin dicari: ";
    cin >> cari;

    // menyimpan isi file sementara untuk parsing
    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    cout << endl;
    head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip line kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(file);

    // bubble sort buat urutin data
    bool swapped;
    do
    {
        swapped = false;
        node *current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (current->stok > current->next->stok)
            {
                swap(current->nama, current->next->nama);
                swap(current->harga, current->next->harga);
                swap(current->stok, current->next->stok);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    // convert linked list ke array sebelum ke binary search
    converstListToArray(head, nodeArr, x);

    int awal = 0, akhir = x - 1, mid;
    bool found = false;

    while ((!found) && (awal <= akhir))
    {
        mid = (awal + akhir) / 2;
        if (cari == nodeArr[mid]->stok)
        {
            found = true;
        }
        else if (cari < nodeArr[mid]->stok)
        {
            akhir = mid - 1;
        }
        else
        {
            awal = mid + 1;
        }
    }

    if (found)
    {
        cout << "Nama Produk: " << nodeArr[mid]->nama
             << "\tHarga Produk: " << nodeArr[mid]->harga
             << "\tStok Produk: " << nodeArr[mid]->stok;
        cout << endl;
    }
    else
    {
        cout << "Produk tidak ditemukan." << endl;
    }
}

// 11. Edit nama produk di daftar barang
void edit_nama_produk() 
{
     string target, namabaru;
    bool found = false;
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    cout << endl;

    head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            fgets(buff, sizeof(buff), file); // skip kosong

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = newNode->prev = nullptr;

            if (head == nullptr)
                head = tail = newNode;
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
fclose(file);
    // minta nama produk yang akan diedit
    cin.ignore();
    cout << "Masukkan nama produk yang ingin diedit: ";
    getline(cin, target);

    node *bantu = head;
    while (bantu != nullptr)
    {
        if (bantu->nama == target)
        {
            found = true;
            cout << "Nama produk yang baru: ";
            getline(cin, namabaru);
            bantu->nama = namabaru;
            cout << "Nama produk berhasil diubah." << endl;
            break;
        }
        bantu = bantu->next;
    }
    if (!found)
    {
        cout << "Produk tidak ditemukan." << endl;
    }
    
   // tulis ulang file nya
    file = fopen("databarang.txt", "w");
    node *temp = head;
    while (temp != nullptr)
    {
        fprintf(file, "Nama Produk: %s\n", temp->nama.c_str()); //pakai c_str untuk convert string ke char* kalau mau dihapus bisa diganti offstream
        fprintf(file, "Harga Produk: %d\n", temp->harga); // kalau pakai cout data tidak tersimpan dan malah hilang
        fprintf(file, "Stok Produk: %d\n\n", temp->stok);
        temp = temp->next;
    }
    fclose(file);

}

// 12. Edit harga produk di daftar barang 45
void edit_harga()
{
   string cari;
    int hargaBaru;
    bool found = false;
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    // menyimpan isi file sementara untuk parsing
    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    cout << endl;
    head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip line kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(file);

    node *current = head;

    cin.ignore();
    cout << "Masukkan nama produk yang ingin diedit harganya: ";
    getline(cin, cari);

    while (current != nullptr)
    {
        if (current->nama == cari)
        {
            cout << "Harga saat ini: " << current->harga << endl;
            cout << "Masukkan harga terbaru: ";
            cin >> hargaBaru;
            current->harga = hargaBaru;
            cout << "Harga berhasil diubah" << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "Data tidak ditemukan." << endl;
    }

    // tulis kembali file nya
    file = fopen("databarang.txt", "w");
    node *temp = head;

    while (temp != nullptr)
    {
        fprintf(file, "Nama Produk: %s\n", temp->nama.c_str());
        fprintf(file, "Harga Produk: %d\n", temp->harga);
        fprintf(file, "Stok Produk: %d\n\n", temp->stok);
        temp = temp->next;
    }
    fclose(file);
}

// 13. Edit stok produk di daftar barang
void edit_stok() 
{
    string target;
   int stokbaru;
   bool found = false;
    FILE *file = fopen("databarang.txt", "r");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    char buff[255];
    char tempNama[255];
    int tempHarga = 0, tempStok = 0;
    

    head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            fgets(buff, sizeof(buff), file); // skip kosong

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = newNode->prev = nullptr;

            if (head == nullptr)
                head = tail = newNode;
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
fclose(file);
    // minta nama stok yang akan diedit
    cin.ignore();
    cout << "Masukkan nama barang yang ingin diedit stoknya : ";
    getline(cin, target);

    node *bantu = head;
    while (bantu != nullptr)
    {
        if (bantu->nama == target)
        {
            cout << "Stok terkini: " << bantu->stok << endl;
            found = true;
            cout << "Masukkan stok terbaru: ";
            cin >> stokbaru;
            bantu->stok = stokbaru;
            cout << "Stok berhasil diubah." << endl;
            break;
        }
        bantu = bantu->next;
    }
    
    if (!found)
    {
        cout << "Produk tidak ditemukan." << endl;
    }
    
   // tulis ulang file nya
    file = fopen("databarang.txt", "w");
    node *temp = head;
    while (temp != nullptr)
    {
        fprintf(file, "Nama Produk: %s\n", temp->nama.c_str()); //pakai c_str untuk convert string ke char* kalau mau dihapus bisa diganti offstream
        fprintf(file, "Harga Produk: %d\n", temp->harga);
        fprintf(file, "Stok Produk: %d\n\n", temp->stok);
        temp = temp->next;
    }
    fclose(file);
 
}

// 14. Hapus produk dari daftar barang
void hapus_barang() 
{
     string target;
    bool found = false;

    FILE *file = fopen("databarang.txt", "r");
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    // baca semua data dari file ke linked list
    char buff[255], tempNama[255];
    int tempHarga, tempStok;
    head = tail = nullptr;

    while (fgets(buff, sizeof(buff), file))
    {
        if (sscanf(buff, "Nama Produk: %[^\n]", tempNama) == 1)
        {
            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Harga Produk: %d", &tempHarga);

            fgets(buff, sizeof(buff), file);
            sscanf(buff, "Stok Produk: %d", &tempStok);

            // skip baris kosong
            fgets(buff, sizeof(buff), file);

            node *newNode = new node;
            newNode->nama = tempNama;
            newNode->harga = tempHarga;
            newNode->stok = tempStok;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    fclose(file);

    // input nama produk yang ingin dihapus
    cin.ignore();
    cout << "Masukkan nama produk yang ingin dihapus: ";
    getline(cin, target);

    // cari dan hapus node yang cocok
    node *bantu = head;
    while (bantu != nullptr)
    {
        if (bantu->nama == target)
        {
            found = true;
            if (bantu == head && bantu == tail) // hanya satu node
            {
                head = tail = nullptr;
            }
            else if (bantu == head) // pakai else tidak bisa jadi bisanya if/else i
            {
                head = head->next;
                head->prev = nullptr;
            }
            else if (bantu == tail)
            {
                tail = tail->prev;
                tail->next = nullptr;
            }
            else
            {
                bantu->prev->next = bantu->next;
                bantu->next->prev = bantu->prev;
            }
            delete bantu;
            cout << "Produk berhasil dihapus.\n";
            break;
        }
        bantu = bantu->next;
    }

    if (!found)
    {
        cout << "Produk tidak ditemukan.\n";
        return;
    }

    // tulis ulang file
    file = fopen("databarang.txt", "w");
    node *temp = head;
    while (temp != nullptr)
    {
        fprintf(file, "Nama Produk: %s\n", temp->nama.c_str()); // pakai c_str untuk convert string ke char* kalau mau dihapus bisa diganti offstream pas fprint di awal
        fprintf(file, "Harga Produk: %d\n", temp->harga); // kalau pakai cout data hanya tampil tapi tidak tersimpan
        fprintf(file, "Stok Produk: %d\n\n", temp->stok);
        temp = temp->next;
    }
    fclose(file);
}

// lihat daftar
void lihat_daftar() {}

int main()
{
    do
    {
        system("CLS");
        beranda();

        switch (menu)
        {
        case 1:
            input_baru();
            break;
        case 2:
            nama_produk_asc();
            break;
        case 3:
            head = nama_produk_desc(head);
            break;
        case 4:
            harga_asc(head);
            break;
        case 5:
            harga_desc();
            break;
        case 6:
            stok_asc();
            break;
        case 7:
            stok_desc();
            break;
        case 8:
            cari_nama();
            break;
        case 9:
            cari_harga();
            break;
        case 10:
            cari_stok();
            break;
        case 11:
            edit_nama_produk();
            break;
        case 12:
            edit_harga();
            break;
        case 13:
            edit_stok();
            break;
        case 14:
            hapus_barang();
            break;
        default:
            cout << "Pilihan tidak tersedia. Pastikan Anda memilih menu 1-4.";
            break;
        }
        cout << "Apakah Anda ingin melanjutkan program? (y/n) -> ";
        cin >> pilihan;
    } while (pilihan == 'Y' || pilihan == 'y');
}
