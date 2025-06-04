#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> // Digunakan untuk gotoxy, GetAsyncKeyState, Sleep

#define MAX_BARANG 100
#define ENTER 13
#define UP_ARROW 72
#define DOWN_ARROW 80

// Fungsi untuk memindahkan kursor ke posisi (x,y)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct akun {
    char username[100];
    char password[100];
};

struct akun daftarakun[100];
int jumlahakun = 0;

void registerakun() {
    printf("\n\n\n\n\n\n\t\t\t\t\t\tREGISTER AKUN BARU\n");
    printf("\t\t\t\t\t\t-------------------\n");
    printf("\t\t\t\t\t\tUsername : ");
    scanf("%s", daftarakun[jumlahakun].username);
    printf("\t\t\t\t\t\tPassword : ");
    scanf("%s", daftarakun[jumlahakun].password);
    jumlahakun++;
    printf("\n\t\t\t\t\t\t\n");
    system("color a0");
    printf("\n\t\t\t\t\t        Akun berhasil dibuat!\n");
    printf("\t\t\t\t\t      ");
    system("pause");
    system("cls");
}

int loginakun() {
    char inputuser[100], inputpassword[100];
    system("color 0f");
    printf("\n\n\n\n\n\n\t\t\t\t\t\tLOGIN\n\n");
    printf("\t\t\t\t\t\tUsername : ");
    scanf("%s", inputuser);
    printf("\t\t\t\t\t\tPassword : ");
    scanf("%s", inputpassword);

    for (int i = 0; i < jumlahakun; i++) {
        if (strcmp(inputuser, daftarakun[i].username) == 0 && strcmp(inputpassword, daftarakun[i].password) == 0) {
            system("color a0");
            printf("\n\t\t\t\t\t\tLogin Berhasil!\n");
            printf("\t\t\t\t\tSelamat Datang di Supermarket Anjay\n");
            getchar();
            getchar();
            system("cls");
            return 1;
        }
    }
    system("color cf");
    printf("\n\t\t\t\t\tLogin Gagal, Username atau Password salah!\n");
    getchar();
    getchar();
    system("cls");
    return 0;
}

struct Barang {
    char nama[50];
    int jumlah;
    char hargaStr[20];
    float hargaVal;
};

struct ItemStruk {
    char nama[50];
    int jumlah;
    float hargaVal;
};

struct Barang keranjangBarang[MAX_BARANG];
struct ItemStruk keranjang[MAX_BARANG];
int jumlahKeranjangBarang = 0;
int jumlahKeranjang = 0;
int sudahLihatBarang = 0;

void printCenter(const char *text, int width) {
    int len = strlen(text);
    int spasi = (width - len) / 2;
    if (spasi < 0) spasi = 0;
    for (int i = 0; i < spasi; i++) putchar(' ');
    printf("%s", text);
    for (int i = 0; i < width - spasi - len; i++) putchar(' ');
}

void tampilkanBarang() {
    if (jumlahKeranjangBarang == 0) {
        printf("\nTidak ada barang dalam stok.\n");
        return;
    }

    int lebarNo = 5, lebarNama = 22, lebarStok = 8, lebarHarga = 12;

    printf("\n================ Daftar Barang ================\n");
    printf("----------------------------------------------------\n");
    printf("|"); printCenter("No", lebarNo);
    printf("|"); printCenter("Nama Barang", lebarNama);
    printf("|"); printCenter("Stok", lebarStok);
    printf("|"); printCenter("Harga", lebarHarga); printf("|\n");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < jumlahKeranjangBarang; i++) {
        char buffer[10];
        printf("|");
        snprintf(buffer, sizeof(buffer), "%d", i + 1);
        printCenter(buffer, lebarNo); printf("|");
        printCenter(keranjangBarang[i].nama, lebarNama); printf("|");
        snprintf(buffer, sizeof(buffer), "%d", keranjangBarang[i].jumlah);
        printCenter(buffer, lebarStok); printf("|");
        char hargaDisplay[25];
        snprintf(hargaDisplay, sizeof(hargaDisplay), "Rp%s", keranjangBarang[i].hargaStr);
        printCenter(hargaDisplay, lebarHarga); printf("|\n");
    }
    printf("----------------------------------------------------\n");
    sudahLihatBarang = 1;
    system("pause"); // Agar pengguna bisa melihat daftar barang sebelum melanjutkan
    system("cls");
}

void tambahBarang() {
    if (!sudahLihatBarang) {
        printf("\n⚠  Harus lihat daftar barang dulu sebelum tambah barang.\n");
        system("pause");
        system("cls");
        return;
    }
    if (jumlahKeranjangBarang >= MAX_BARANG) {
        printf("Stok penuh.\n");
        system("pause");
        system("cls");
        return;
    }
    struct Barang *b = &keranjangBarang[jumlahKeranjangBarang];

    printf("Masukkan nama barang: ");
    getchar(); // Membersihkan buffer input
    fgets(b->nama, sizeof(b->nama), stdin);
    b->nama[strcspn(b->nama, "\n")] = '\0';

    printf("Masukkan jumlah stok: ");
    scanf("%d", &b->jumlah);

    printf("Masukkan harga barang: ");
    scanf("%s", b->hargaStr);
    b->hargaVal = atof(b->hargaStr);

    jumlahKeranjangBarang++;
    printf("Barang berhasil ditambahkan.\n");
    system("pause");
    system("cls");
}

// kalkulasiHarga()
void kalkulasiHarga() {
    system("cls");
    tampilkanBarang();

    int nomorBarang, jumlahBeli;
    printf("\nMasukkan nomor barang yang ingin dibeli: ");
    scanf("%d", &nomorBarang);

    if(nomorBarang < 1 || nomorBarang > jumlahKeranjangBarang) {
        printf("Nomor barang tidak valid!\n");
        //system("pause");
        return;
    }

    int index = nomorBarang - 1; // Penyesuaian indeks array

    printf("Masukkan jumlah yang ingin dibeli: ");
    scanf("%d", &jumlahBeli);

    if(jumlahBeli <= 0) {
        printf("Jumlah tidak boleh kurang dari 1!\n");
        system("pause");
        return;
    }

    if(jumlahBeli > keranjangBarang[index].jumlah) {
        printf("Stok tidak mencukupi!\n");
        system("pause");
        return;
    }

    // Tambahkan ke keranjang belanja
    strcpy(keranjang[jumlahKeranjang].nama, keranjangBarang[index].nama);
    keranjang[jumlahKeranjang].hargaVal = keranjangBarang[index].hargaVal;
    keranjang[jumlahKeranjang].jumlah = jumlahBeli;
    jumlahKeranjang++;

    // Kurangi stok barang
    keranjangBarang[index].jumlah -= jumlahBeli;

    printf("Barang berhasil ditambahkan ke keranjang!\n");
    system("pause");
}

void tampilkanStruk() {
    system("cls");
    float subtotal = 0, totalDiskon = 0, totalPajak = 0, totalAkhir = 0;
    int uangDibayar, kembalian;

    printf("======= Struk Belanja =======\n");
    for(int i = 0; i < jumlahKeranjang; i++) {
        float hargaTotal = keranjang[i].hargaVal * keranjang[i].jumlah;
        float diskon = 0;

        // Diskon: 10% kalau beli >= 5
        if(keranjang[i].jumlah >= 5) {
            diskon = 0.10 * hargaTotal;
        }

        float hargaSetelahDiskon = hargaTotal - diskon;
        float pajak = 0.02 * hargaSetelahDiskon;
        float total = hargaSetelahDiskon + pajak;

        // Cetak struk per barang
        printf("%s x%d @%.0f = %.0f\n", keranjang[i].nama, keranjang[i].jumlah, keranjang[i].hargaVal, hargaTotal);
        printf("  Diskon: %.0f\n", diskon);
        printf("  Pajak : %.0f\n", pajak);
        printf("  Total : %.0f\n\n", total);

        // Akumulasi
        subtotal += hargaTotal;
        totalDiskon += diskon;
        totalPajak += pajak;
        totalAkhir += total;
    }

    printf("==============================\n");
    printf("Subtotal      : %.0f\n", subtotal);
    printf("Total Diskon  : %.0f\n", totalDiskon);
    printf("Total Pajak   : %.0f\n", totalPajak);
    printf("Total Akhir   : %.0f\n", totalAkhir);
    printf("==============================\n\n");

    do
    {
        printf("Uang Anda: Rp.");
        scanf("%d", &uangDibayar);

        // Kalau uang kurang dari total harga, minta input ulang
        if (uangDibayar < totalAkhir)
        {
            printf("Uang Anda kurang!\n");
        }
    }
    while (uangDibayar < totalAkhir); // Looping ini terus berjalan kalau uang yang dibayar kurang dari total harga

    kembalian = uangDibayar - totalAkhir;
    printf("Kembalian : Rp. %d\n", kembalian);
    printf("==============================\n");

    system("pause");
}

void inisialisasiBarangAwal() {
    strcpy(keranjangBarang[0].nama, "Beras 5kg");
    keranjangBarang[0].jumlah = 20;
    strcpy(keranjangBarang[0].hargaStr, "60000");
    keranjangBarang[0].hargaVal = 60000;

    strcpy(keranjangBarang[1].nama, "Minyak Goreng 2L");
    keranjangBarang[1].jumlah = 15;
    strcpy(keranjangBarang[1].hargaStr, "35000");
    keranjangBarang[1].hargaVal = 35000;

    jumlahKeranjangBarang = 2;
}

void selesai() {
    int i;
    char tengs[] = "\n\n\n\n\n\n\n\t\t\t\tTerimakasih telah berbelanja di Simple Supermarket^^\n\n\n\t\t\t\t\t(klik ENTER untuk melihat developer)";

    system("color 0a");

    for (i = 0; tengs[i] != '\0'; i++) {
        printf("%c", tengs[i]);
        Sleep(30);
    }
    getchar(); // Menangkap sisa newline
}

void developerDelay(char text[][100], int baris, int judulDelay, int namaDelay) {
    // Tampilkan judul
    for (int i = 0; text[0][i] != '\0'; i++) {
        printf("%c", text[0][i]);
        Sleep(judulDelay);
    }

    // Tampilkan baris-baris berikutnya
    for (int j = 1; j < baris; j++) {
        for (int i = 0; text[j][i] != '\0'; i++) {
            printf("%c", text[j][i]);
            Sleep(namaDelay);
        }
    }
}

void developer() {
    // Array 2 dimensi untuk menyimpan semua baris teks
    char lines[7][100] = {
        "\n\n\n\n\n\n\n\t\t\t\t\t====== Developer Simple Supermarket ======\n\n\n",
        "\t\t\t\t\tSamuel Richad Christianto     - 672024156\n",
        "\t\t\t\t\tSheila Agustina Wismarani     - 672024158\n",
        "\t\t\t\t\tAudelia Tjhoernandes          - 672024162\n",
        "\t\t\t\t\tNadya Nur Aini Lailatun Nikmah - 672024172\n",
        "\t\t\t\t\tBagus Kurniawan               - 672024218\n",
        "\t\t\t\t\tEdwin Kristianus Papa         - 672024238\n"
    };

    system("color 8b");
    developerDelay(lines, 7, 30, 7);
    getchar(); // Menangkap sisa newline
}

int main() {
    int pilihan = 0; // Pilihan menu yang sedang aktif
    int logged = 0;
    int key;

    registerakun();
    while (!logged) {
        logged = loginakun();
    }
    inisialisasiBarangAwal();

    // Menu interaktif
    char *menu[] = {
        "Tampilkan Daftar Barang",
        "Tambah Barang",
        "Kalkulasi Harga",
        "Total dan Tampilan Harga Keseluruhan",
        "Exit"
    };
    int jumlahMenu = sizeof(menu) / sizeof(menu[0]);
    int pilihanMenuSaatIni = 0; // Indeks menu yang sedang disorot

    while (1) {
        system("cls"); // Bersihkan layar setiap kali menu ditampilkan
        system("color 0f");
        printf("\n====== MENU ======\n");
        for (int i = 0; i < jumlahMenu; i++) {
            if (i == pilihanMenuSaatIni) {
                printf("  -> %s\n", menu[i]); // Sorot menu yang aktif
            } else {
                printf("     %s\n", menu[i]);
            }
        }

        key = 0; // Reset key
        // Tunggu input dari keyboard
        while (key == 0) {
            if (GetAsyncKeyState(VK_UP) & 0x8000) { // Panah atas
                key = UP_ARROW;
            } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Panah bawah
                key = DOWN_ARROW;
            } else if (GetAsyncKeyState(VK_RETURN) & 0x8000) { // Enter
                key = ENTER;
            }
            Sleep(100); // Penundaan kecil untuk menghindari deteksi berulang
        }

        // Buang sisa input jika ada (misal: jika _kbhit() tidak digunakan)
        // while (_kbhit()) _getch(); // Ini opsional, tergantung bagaimana input dibaca

        if (key == UP_ARROW) {
            pilihanMenuSaatIni--;
            if (pilihanMenuSaatIni < 0) {
                pilihanMenuSaatIni = jumlahMenu - 1; // Kembali ke bawah jika melewati batas atas
            }
        } else if (key == DOWN_ARROW) {
            pilihanMenuSaatIni++;
            if (pilihanMenuSaatIni >= jumlahMenu) {
                pilihanMenuSaatIni = 0; // Kembali ke atas jika melewati batas bawah
            }
        } else if (key == ENTER) {
            pilihan = pilihanMenuSaatIni + 1; // Ubah indeks menjadi pilihan (1-based)
            switch (pilihan) {
                case 1:
                    tampilkanBarang();
                    break;
                case 2:
                    tambahBarang();
                    break;
                case 3:
                    kalkulasiHarga();
                    break;
                case 4:
                    tampilkanStruk();
                    break;
                case 5:
                    system("cls");
                    selesai();
                    getchar(); // Menangkap enter dari selesai()
                    system("cls");
                    developer();
                    system("cls");
                    return 0; // Keluar dari program
                default:
                    printf("Pilihan tidak valid, coba lagi.\n");
                    break;
            }
        }
    }

    return 0;
}
