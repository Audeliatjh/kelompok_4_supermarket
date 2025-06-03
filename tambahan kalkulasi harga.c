#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BARANG 100
//blabkabassggubzxvvbzbkjzxvb
typedef struct {
    char nama[50];
    int jumlah;
    char hargaStr[20];
    float hargaVal;
} Barang;

Barang inventaris[MAX_BARANG];
int jumlahBarang = 0;

void printCenter(const char *text, int width) {
    int len = strlen(text);
    int spasi = (width - len) / 2;
    if (spasi < 0) spasi = 0;
    for (int i = 0; i < spasi; i++) putchar(' ');
    printf("%s", text);
    for (int i = 0; i < width - spasi - len; i++) putchar(' ');
}

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
}

void tambahBarang() {
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

void kalkulasiHarga() {
    if (jumlahBarang == 0) {
        printf("\nTidak ada barang dalam inventaris untuk dikalkulasi.\n");
        return;
    }

    int nomorBarang, jumlahBeli;
    float totalHarga;

    printf("\n============ KALKULASI HARGA PEMBELIAN ============\n");

    printf("\nDaftar Barang:\n");
    for (int i = 0; i < jumlahBarang; i++) {
        printf("%d. %s - Rp%s (Stok: %d)\n",
               i + 1, inventaris[i].nama, inventaris[i].hargaStr, inventaris[i].jumlah);
    }

    printf("\nPilih nomor barang (1-%d): ", jumlahBarang);
    scanf("%d", &nomorBarang);

    if (nomorBarang < 1 || nomorBarang > jumlahBarang) {
        printf("Nomor barang tidak valid!\n");
        return;
    }

    nomorBarang--;

    printf("Masukkan jumlah yang ingin dibeli: ");
    scanf("%d", &jumlahBeli);

    if (jumlahBeli > inventaris[nomorBarang].jumlah) {
        printf("Stok tidak mencukupi! Stok tersedia: %d\n", inventaris[nomorBarang].jumlah);
        return;
    }

    totalHarga = inventaris[nomorBarang].hargaVal * jumlahBeli;

    printf("\n=============== HASIL KALKULASI ===============\n");
    printf("Barang dipilih    : %s\n", inventaris[nomorBarang].nama);
    printf("Harga per unit    : Rp%.2f\n", inventaris[nomorBarang].hargaVal);
    printf("Jumlah pembelian  : %d\n", jumlahBeli);
    printf("================================================\n");
    printf("TOTAL HARGA       : Rp%.2f\n", totalHarga);
    printf("================================================\n");

    char konfirmasi;
    printf("\nApakah ingin mengurangi stok barang? (y/n): ");
    scanf(" %c", &konfirmasi);

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        inventaris[nomorBarang].jumlah -= jumlahBeli;
        printf("Stok barang '%s' berhasil diupdate. Sisa stok: %d\n",
               inventaris[nomorBarang].nama, inventaris[nomorBarang].jumlah);
    }
}

int main() {
    int pilihan;
    do {
        printf("\n=== Sistem Inventaris Supermarket ===\n");
        printf("1. Tampilkan Daftar Barang\n");
        printf("2. Tambah Barang\n");
        printf("3. Kalkulasi Harga Pembelian\n");
        printf("4. Keluar\n");
        printf("Pilih opsi (1-4): ");
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
                printf("Program selesai. Terima kasih.\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (pilihan != 4);
    return 0;
}
