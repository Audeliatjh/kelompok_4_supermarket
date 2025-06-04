#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_BARANG 100

struct akun{
    char username[100];
    char password[100];
};

struct akun daftarakun[100];
int jumlahakun=0;

void hapusenter(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void registerakun(){
    printf("=======================");
    printf("\n|  REGISTER AKUN BARU |\n");
    printf("=======================\n");
    printf("Username : ");
    fgets(daftarakun[jumlahakun].username, sizeof(daftarakun[jumlahakun].username), stdin);
    hapusenter(daftarakun[jumlahakun].username);
    printf("Password : ");
    fgets(daftarakun[jumlahakun].password, sizeof(daftarakun[jumlahakun].password), stdin);
    hapusenter(daftarakun[jumlahakun].password);
    jumlahakun++;
    system("color a0");
    printf("\n=======================\n");
    printf("Akun berhasil dibuat!\n");
    system("pause");
    system("cls");
}

int loginakun() {
    char inputuser[100], inputpassword[100];
    system("color 0f");
    printf("=======================");
    printf("\n|       LOGIN         |\n");
    printf("=======================\n");
    printf("Username : ");
    fgets(inputuser, sizeof(inputuser), stdin);
    hapusenter(inputuser);
    printf("Password : ");
    fgets(inputpassword, sizeof(inputpassword), stdin);
    hapusenter(inputpassword);

    for(int i=0;i<jumlahakun;i++) {
        if(strcmp(inputuser, daftarakun[i].username) == 0 && strcmp(inputpassword, daftarakun[i].password) == 0) {
            system("color a0");
            printf("==================\n");
            printf("Login Berhasil!\n");
            getchar();
            getchar();
            system("cls");
            return 1;
        }
    }
    system("color cf");
    printf("Login Gagal, Username atau Password salah!\n");
    printf("Masukan Username atau Password yang benar!\n");

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

void tampilkanBarang(){
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

    getchar();
    getchar();
    system("cls");
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

    getchar();
    getchar();
    system("cls");
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

    getchar();
    getchar();
    system("cls");
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

    getchar();
    getchar();
    system("cls");
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

void selesai(){
    int i;
    char tengs[]="\n\n\n\n\n\n\n\t\t\t\tTerimakasih telah berbelanja di Simple Supermarket^^\n\n\n\t\t\t\t\t(klik ENTER untuk melihat developer)";

    system("color 0a");

    for(i=0; tengs[i]!='\0'; i++){
        printf("%c", tengs[i]);
        Sleep(30);
    }
    getchar();
    getchar();
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

void developer(){
    // Array 2 dimensi untuk menyimpan semua baris teks
    char lines[7][100] = {
        "\n\n\n\n\n\n\n\t\t\t\t\t====== Developer Simple Supermarket ======\n\n\n",
        "\t\t\t\t\tSamuel Richad Christianto      - 672024156\n",
        "\t\t\t\t\tSheila Agustina Wismarani      - 672024158\n",
        "\t\t\t\t\tAudelia Tjhoernandes           - 672024162\n",
        "\t\t\t\t\tNadya Nur Aini Lailatun Nikmah - 672024172\n",
        "\t\t\t\t\tBagus Kurniawan                - 672024218\n",
        "\t\t\t\t\tEdwin Kristianus Papa          - 672024238\n"
    };

    system("color 8b");
    developerDelay(lines, 7, 30, 7);
    getchar();
}

int main() {
    int pilihan;
    int logged=0;
    registerakun();
    while (!logged) {
        logged = loginakun();
    }
    inisialisasiBarangAwal();

    do {
        system("color 0f");
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
                system("cls");
                selesai();
                getchar();
                system("cls");
                developer();
                system("cls");
                break;
            default:
                printf("Pilihan tidak valid, coba lagi.\n");
                break;
        }
    } while (pilihan != 5);

    return 0;
}
