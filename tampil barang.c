#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BARANG 100

// Struktur data barang
typedef struct {
    char nama[50];
    int jumlah;
    char hargaStr[20]; // Simpan harga sebagai string
    float hargaVal;    // Versi numerik jika dibutuhkan
} Barang;

// Data global
Barang inventaris[MAX_BARANG];
int jumlahBarang = 0;
int sudahLihatBarang = 0; // Flag apakah daftar sudah dilihat

// Cetak teks rata tengah
void printCenter(const char *text, int width) {
    int len = strlen(text);
    int spasi = (width - len) / 2;
    if (spasi < 0) spasi = 0;

    for (int i = 0; i < spasi; i++) putchar(' ');
    printf("%s", text);
    for (int i = 0; i < width - spasi - len; i++) putchar(' ');
}

// Tampilkan daftar barang
void tampilkanBarang() {
    if (jumlahBarang == 0) {
        printf("\nTidak ada barang dalam inventaris.\n");
        return;
    }

    int lebarNo = 5;
    int lebarNama = 22;
    int lebarStok = 8;
    int lebarHarga = 12;

    printf("\n================ Daftar Barang ================\n");
    printf("----------------------------------------------------\n");

    printf("|"); printCenter("No", lebarNo);
    printf("|"); printCenter("Nama Barang", lebarNama);
    printf("|"); printCenter("Stok", lebarStok);
    printf("|"); printCenter("Harga", lebarHarga); printf("|\n");

    printf("----------------------------------------------------\n");

    for (int i = 0; i < jumlahBarang; i++) {
        char buffer[10];

        printf("|");
        snprintf(buffer, sizeof(buffer), "%d", i + 1);
        printCenter(buffer, lebarNo); printf("|");

        printCenter(inventaris[i].nama, lebarNama); printf("|");

        snprintf(buffer, sizeof(buffer), "%d", inventaris[i].jumlah);
        printCenter(buffer, lebarStok); printf("|");

        char hargaDisplay[25];
        snprintf(hargaDisplay, sizeof(hargaDisplay), "Rp%s", inventaris[i].hargaStr);
        printCenter(hargaDisplay, lebarHarga); printf("|\n");
    }

    printf("----------------------------------------------------\n");

    // Tandai bahwa daftar sudah dilihat
    sudahLihatBarang = 1;
}

// Tambah barang ke inventaris
void tambahBarang() {
    if (!sudahLihatBarang) {
        printf("\n⚠  Anda harus melihat daftar barang terlebih dahulu sebelum menambahkan barang baru.\n");
        return;
    }

    if (jumlahBarang >= MAX_BARANG) {
        printf("Inventaris penuh.\n");
        return;
    }

    Barang *b = &inventaris[jumlahBarang];

    printf("Masukkan nama barang: ");
    getchar();
    fgets(b->nama, sizeof(b->nama), stdin);
    b->nama[strcspn(b->nama, "\n")] = '\0';

    printf("Masukkan jumlah stok: ");
    scanf("%d", &b->jumlah);

    printf("Masukkan harga barang: ");
    scanf("%s", b->hargaStr);
    b->hargaVal = atof(b->hargaStr);

    jumlahBarang++;
    printf("Barang berhasil ditambahkan.\n");
}

// Tambahkan beberapa barang awal
void inisialisasiBarangAwal() {
    strcpy(inventaris[0].nama, "Beras 5kg");
    inventaris[0].jumlah = 20;
    strcpy(inventaris[0].hargaStr, "60000");
    inventaris[0].hargaVal = 60000;

    strcpy(inventaris[1].nama, "Minyak Goreng 2L");
    inventaris[1].jumlah = 15;
    strcpy(inventaris[1].hargaStr, "35000");
    inventaris[1].hargaVal = 35000;

    jumlahBarang = 2;
}

int main() {
    int pilihan;

    inisialisasiBarangAwal();

    do {
        printf("\n=== Sistem Inventaris Supermarket ===\n");
        printf("1. Tampilkan Daftar Barang\n");
        printf("2. Tambah Barang (aktif setelah lihat daftar)\n");
        printf("3. Keluar\n");
        printf("Pilih opsi (1-3): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanBarang();
                break;
            case 2:
                tambahBarang();
                break;
            case 3:
                printf("Program selesai. Terima kasih.\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (pilihan != 3);

    return 0;
}