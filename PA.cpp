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

int menu;     // variabel untuk memilih menu di beranda dan fungsi lihat_daftar
char pilihan; // variabel pilihan untuk operasi do-while apakah ingin melanjutkan program atau tidak
int jml_input; // jmulah input di menu input_baru

void beranda()
{
    // HEADER
    cout << setfill('=') << setw(50) << "" << endl;
    cout << setfill(' ') << setw(20) << "" << "TOKO PIGURA" << endl;
    cout << setfill('=') << setw(50) << "" << endl;

    // PILIHAN MENU MANAJEMEN TOKO
    cout << "Menu:" << endl;
    cout << "1. Input Baru" << endl; // file
    cout << "2. Tampilkan daftar barang berdasarkan nama secara ascending." << endl;   // bubble sort
    cout << "3. Tampilkan daftar barang berdasarkan nama secara descending." << endl;  // quick sort
    cout << "4. Tampilkan daftar barang berdasarkan harga secara ascending." << endl;  // quick sort
    cout << "5. Tampilkan daftar barang berdasarkan harga secara descending." << endl; // bubble sort
    cout << "6. Tampilkan daftar barang berdasarkan stok secara ascending." << endl;   // bubble sort
    cout << "7. Tampilkan daftar barang berdasarkan stok secara descending." << endl;  // quick sort
    cout << "8. Cari produk berdasarkan nama." << endl; // sequence/linear search
    cout << "9. Cari produk berdasarkan harga." << endl; // binary search
    cout << "10. Cari prodk berdasarkan stok." << endl; // binary search
    cout << "11. Edit nama produk di daftar barang" << endl; //
    cout << "12. Edit harga produk di daftar barang" << endl; //
    cout << "13. Edit stok produk di daftar barang" << endl;  //
    cout << "14. Hapus produk dari daftar barang" << endl;  //
    cout << "Pilih menu: ";
    cin >> menu;
}

// untuk normalisasi input jadi case insensitive
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
        fprintf(file, "nama produk: %s\n", newNode->nama.c_str());
        fprintf(file, "harga produk: %d\n", newNode->harga);
        fprintf(file, "stok produk: %d\n\n", newNode->stok);
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
}

// 3. Tampilkan daftar barang berdasarkan nama secara descending.
void nama_produk_desc()
{
    // menampilkan daftar barang berdasarkan nama secara desc
    FILE *file = fopen("databarang.txt", "a");

    // cek apakah file bisa dibuka atau NULL
    if (file == NULL)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }
    fclose(file);
}

// 4. Tampilkan daftar barang berdasarkan harga secara ascending.
void harga_asc(){}

// 5. Tampilkan daftar barang berdasarkan harga secara descending.
void harga_desc(){}

// 6. Tampilkan daftar barang berdasarkan stok secara ascending.
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
void stok_desc(){}

// 8. Cari produk berdasarkan nama
void cari_nama() {
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

// 10. Cari produk berdasarkan stok
void cari_stok() {}

// 11. Edit nama produk di daftar barang
void edit_nama_produk(){}

// 12. Edit harga produk di daftar barang
void edit_harga(){}

// 13. Edit stok produk di daftar barang
void edit_stok(){}

// 14. Hapus produk dari daftar barang
void hapus_barang(){}

// lihat daftar
void lihat_daftar(){}

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
            nama_produk_desc();
            break;
        case 4:
            harga_asc();
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
