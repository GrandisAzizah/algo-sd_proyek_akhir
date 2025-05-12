#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int menu;     // variabel untuk memilih menu di beranda dan fungsi lihat_daftar
char pilihan; // variabel pilihan untuk operasi do-while apakah ingin melanjutkan program atau tidak

void beranda()
{
    // HEADER jj
    cout << setfill('=') << setw(50) << "" << endl;
    cout << setfill(' ') << setw(20) << "" << "TOKO PIGURA" << endl;
    cout << setfill('=') << setw(50) << "" << endl
         << endl;

    // PILIHAN MENU MANAJEMEN TOKO
    cout << "Menu:" << endl;
    cout << "1. Input Baru" << endl;
    cout << "2. Tampilkan daftar barang berdasarkan nama secara ascending" << endl;
    cout << "3. Tampilkan daftar barang berdasarkan nama secara descending" << endl;
    cout << "4. Tampilkan daftar barang berdasarkan harga secara ascending" << endl;
    cout << "5. Tampilkan daftar barang berdasarkan harga secara descending" << endl;
    cout << "6. Tampilkan daftar barang berdasarkan stok secara ascending" << endl;
    cout << "7. Tampilkan daftar barang berdasarkan stok secara descending" << endl;
    cout << "8. Edit nama produk di daftar barang" << endl;
    cout << "9. Edit harga produk di daftar barang" << endl;
    cout << "10. Edit stok produk di daftar barang" << endl;
    cout << "11. Hapus produk dari daftar barang" << endl;
    cout << "Pilih menu: ";
    cin >> menu;
}

void input_baru()
{
    int jml_input;
    cout << setfill('-') << setw(20) << "" << endl;
    cout << "Input Produk" << endl;
    cout << "Jumlah Input: ";
    cin >> jml_input;

    for (int i = 0; i < jml_input; i++)
    {
        cout << "Nama Produk: ";
        cout << "Harga Produk: ";
        cout << "Stok Produk: ";
    }
    cout << endl;
    cout << "Input Berhasil!" << endl;
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
            edit_nama_produk();
            break;
        case 9:
            edit_harga();
            break;
        case 10:
            edit_stok();
            break;
        case 11:
            hapus_barang();
            break;
        default:
            cout << "Pilihan tidak tersedia. Pastikan Anda memilih menu 1 sd 4.";
            break;
        }
        cout << "Apakah Anda ingin melanjutkan program? (y/n) -> ";
        cin >> pilihan;
    } while (pilihan == 'Y' || pilihan == 'y');
}
