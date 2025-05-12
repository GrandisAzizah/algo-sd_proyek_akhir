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
int jml_input;

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
    cout << "10. Cari prodk berdasarkan stok." << endl;                                // binary search
    cout << "11. Edit nama produk di daftar barang" << endl;                           //
    cout << "12. Edit harga produk di daftar barang" << endl;                          //
    cout << "13. Edit stok produk di daftar barang" << endl;                           //
    cout << "14. Hapus produk dari daftar barang" << endl;                             //
    cout << "Pilih menu: ";
    cin >> menu;
}

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

void edit_daftar()
{
}

void hapus_barang()
{
}

void harga_asc()
{
}

void harga_desc()
{
}

void nama_produk_asc()
{
}

void nama_produk_desc()
{
}

void stok_asc()
{
}

void stok_desc()
{
}

void edit_nama_produk()
{
}

void edit_harga()
{
}

void edit_stok()
{
}

void cari_nama() {}

void cari_harga() {}

void cari_stok() {}

void lihat_daftar()
{
}

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
