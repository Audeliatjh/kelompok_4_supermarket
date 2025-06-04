#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BARANG 100

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
}

void tambahBarang() {
    if (!sudahLihatBarang) {
        printf("\n⚠  Harus lihat daftar barang dulu sebelum tambah barang.\n");
        return;
    }
    if (jumlahKeranjangBarang >= MAX_BARANG) {
        printf("Stok penuh.\n");
        return;
    }
    struct Barang *b = &keranjangBarang[jumlahKeranjangBarang];

    printf("Masukkan nama barang: ");
    getchar();
    fgets(b->nama, sizeof(b->nama), stdin);
    b->nama[strcspn(b->nama, "\n")] = '\0';

    printf("Masukkan jumlah stok: ");
    scanf("%d", &b->jumlah);

    printf("Masukkan harga barang: ");
    scanf("%s", b->hargaStr);
    b->hargaVal = atof(b->hargaStr);

    jumlahKeranjangBarang++;
    printf("Barang berhasil ditambahkan.\n");
}

void kalkulasiHarga() {
    if (jumlahKeranjangBarang == 0) {
        printf("\nTidak ada barang dalam stok untuk dibeli.\n");
        return;
    }
    int nomorBarang, jumlahBeli;
    float diskon, pajak;
    float subtotal, totalDiskon, totalPajak, totalAkhir;

    printf("\n============ KALKULASI HARGA PEMBELIAN ============\n");
    printf("\nDaftar Barang:\n");
    for (int i = 0; i < jumlahKeranjangBarang; i++) {
        printf("%d. %s - Rp%.2f (Stok: %d)\n",
               i + 1, keranjangBarang[i].nama, keranjangBarang[i].hargaVal, keranjangBarang[i].jumlah);
    }
    printf("\nPilih nomor barang (1-%d): ", jumlahKeranjangBarang);
    scanf("%d", &nomorBarang);

    if (nomorBarang < 1 || nomorBarang > jumlahKeranjangBarang) {
        printf("Nomor barang tidak valid!\n");
        return;
    }
    nomorBarang--;

    printf("Masukkan jumlah yang ingin dibeli: ");
    scanf("%d", &jumlahBeli);

    if (jumlahBeli > keranjangBarang[nomorBarang].jumlah) {
        printf("Stok tidak mencukupi! Stok tersedia: %d\n", keranjangBarang[nomorBarang].jumlah);
        return;
    }

    printf("Masukkan diskon (%%): ");
    scanf("%f", &diskon);
    printf("Masukkan pajak (%%): ");
    scanf("%f", &pajak);

    subtotal = keranjangBarang[nomorBarang].hargaVal * jumlahBeli;
    totalDiskon = subtotal * (diskon / 100);
    totalPajak = (subtotal - totalDiskon) * (pajak / 100);
    totalAkhir = subtotal - totalDiskon + totalPajak;

    printf("\n=============== HASIL KALKULASI ===============\n");
    printf("Barang dipilih    : %s\n", keranjangBarang[nomorBarang].nama);
    printf("Harga per unit    : Rp%.2f\n", keranjangBarang[nomorBarang].hargaVal);
    printf("Jumlah pembelian  : %d\n", jumlahBeli);
    printf("------------------------------------------------\n");
    printf("Subtotal          : Rp%.2f\n", subtotal);
    printf("Diskon (%.1f%%)     : Rp%.2f\n", diskon, totalDiskon);
    printf("Setelah diskon    : Rp%.2f\n", subtotal - totalDiskon);
    printf("Pajak (%.1f%%)      : Rp%.2f\n", pajak, totalPajak);
    printf("================================================\n");
    printf("TOTAL AKHIR       : Rp%.2f\n", totalAkhir);
    printf("================================================\n");

    keranjangBarang[nomorBarang].jumlah -= jumlahBeli;

    strcpy(keranjang[jumlahKeranjang].nama, keranjangBarang[nomorBarang].nama);
    keranjang[jumlahKeranjang].jumlah = jumlahBeli;
    keranjang[jumlahKeranjang].hargaVal = keranjangBarang[nomorBarang].hargaVal;
    jumlahKeranjang++;

    printf("Barang berhasil ditambahkan ke keranjang belanja.\n");
}

void tampilkanStruk() {
    if (jumlahKeranjang == 0) {
        printf("\nKeranjang belanja kosong.\n");
        return;
    }
    float total = 0.0;
    printf("\n=========== STRUK BELANJA ===========\n");
    printf("%-20s %-10s %-15s %-15s\n", "Nama Barang", "Jumlah", "Harga/Unit", "Subtotal");
    for (int i = 0; i < jumlahKeranjang; i++) {
        float subtotal = keranjang[i].hargaVal * keranjang[i].jumlah;
        total += subtotal;
        printf("%-20s %-10d Rp%-14.2f Rp%-14.2f\n",
               keranjang[i].nama,
               keranjang[i].jumlah,
               keranjang[i].hargaVal,
               subtotal);
    }
    printf("=====================================\n");
    printf("TOTAL HARGA KESELURUHAN : Rp%.2f\n", total);
    printf("=====================================\n");
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

int main() {
    int pilihan;
    inisialisasiBarangAwal();

    do {
        printf("\n====== MENU ======\n");
        printf("1. Tampilkan Daftar Barang\n");
        printf("2. Tambah Barang\n");
        printf("3. Kalkulasi Harga\n");
        printf("4. Total dan Tampilan Harga Keseluruhan\n");
        printf("5. Exit\n");
        printf("Pilih menu (1-5): ");
        scanf("%d", &pilihan);

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
                printf("Terima kasih sudah menggunakan program.\n");
                break;
            default:
                printf("Pilihan tidak valid, coba lagi.\n");
                 break;
        }
    } while (pilihan != 5);

    return 0;
}

