#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

struct barang {
    char namabarang[100];
    int stok;
    float harga;
    int jumlahbeli;
};

struct akun {
    char username[100];
    char password[100];
};

struct akun daftarakun[100];
struct barang daftarbarang[100];
int jumlahakun = 0;
int jumlahbarang = 0;

void loading() {
    printf("Loading");
    for (int i = 0; i < 3; i++) {
        printf("%c%c", 219, 219);
        Sleep(900);
    }
    Beep(670, 200);
    system("cls");
}

void color() {
    system("color 1F");
}

void stokawal() {
    char *namabarang[] = {"Indomie Goreng", "Nugget Ayam", "Bumbu Racik", "Saos Tomat", "Saos Sambal"};
    int stok[] = {20, 50, 30, 40, 35};
    float harga[] = {2500, 40000, 2000, 15000, 15000};

    for (int i = 0; i < 5; i++) {
        strcpy(daftarbarang[jumlahbarang].namabarang, namabarang[i]);
        daftarbarang[jumlahbarang].stok = stok[i];
        daftarbarang[jumlahbarang].harga = harga[i];
        daftarbarang[jumlahbarang].jumlahbeli = 0;
        jumlahbarang++;
    }
}

void registerakun() {
    printf("=======================\n");
    printf("| REGISTER AKUN BARU  |\n");
    printf("=======================\n");
    printf("Username : ");
    scanf("%s", daftarakun[jumlahakun].username);
    printf("Password : ");
    scanf("%s", daftarakun[jumlahakun].password);
    jumlahakun++;
    printf("======================\n");
    printf("Akun berhasil dibuat!\n");
    Sleep(1000);
    system("cls");
}

int loginakun() {
    char inputuser[100], inputpassword[100];
    printf("=======================\n");
    printf("|       LOGIN         |\n");
    printf("=======================\n");
    printf("Username : ");
    scanf("%s", inputuser);
    printf("Password : ");
    scanf("%s", inputpassword);

    for (int i = 0; i < jumlahakun; i++) {
        if (strcmp(inputuser, daftarakun[i].username) == 0 && strcmp(inputpassword, daftarakun[i].password) == 0) {
            printf("====================\n");
            printf("Login Berhasil!\n");
            printf("Selamat Datang di Supermarket Anjay\n");
            return 1;
        }
    }
    printf("Login Gagal, Username atau Password salah!\n");
    return 0;
}

void menuuu() {
    printf("===============================================\n");
    printf("|*           MENU SUPERMARKET ANJAY          *|\n");
    printf("===============================================\n");
    printf("| No | Nama Barang         | Stok | Harga     |\n");

    for (int i = 0; i < jumlahbarang; i++) {
        printf("| %-3d| %-20s| %-5d| %-10.2f|\n", i + 1, daftarbarang[i].namabarang, daftarbarang[i].stok, daftarbarang[i].harga);
    }
    printf("===============================================\n");
}

void tambahbarang() {
    printf("\nTAMBAH BARANG\n");
    printf("Nama Barang : ");
    getchar(); // membersihkan newline
    fgets(daftarbarang[jumlahbarang].namabarang, sizeof(daftarbarang[jumlahbarang].namabarang), stdin);
    daftarbarang[jumlahbarang].namabarang[strcspn(daftarbarang[jumlahbarang].namabarang, "\n")] = '\0';
    printf("Masukan Jumlah Stok : ");
    scanf("%d", &daftarbarang[jumlahbarang].stok);
    printf("Masukan Harga : ");
    scanf("%f", &daftarbarang[jumlahbarang].harga);
    daftarbarang[jumlahbarang].jumlahbeli = 0;
    jumlahbarang++;
    printf("Barang berhasil ditambahkan!\n");
}

void kasir() {
    int index, jumlah;
    menuuu();
    printf("\nMasukan Nomor Barang : ");
    scanf("%d", &index);
    printf("Masukan Jumlah : ");
    scanf("%d", &jumlah);

    index -= 1;
    if (index >= 0 && index < jumlahbarang && jumlah <= daftarbarang[index].stok) {
        daftarbarang[index].jumlahbeli += jumlah;
        daftarbarang[index].stok -= jumlah;
        printf("Barang ditambahkan ke keranjang.\n");
    } else {
        printf("Jumlah barang tidak valid atau stok kurang.\n");
    }
}

void keranjang() {
    float total = 0;
    printf("\nKERANJANG BELANJA:\n");
    for (int i = 0; i < jumlahbarang; i++) {
        if (daftarbarang[i].jumlahbeli > 0) {
            float subtotal = daftarbarang[i].jumlahbeli * daftarbarang[i].harga;
            printf("%s x%d = Rp %.2f\n", daftarbarang[i].namabarang, daftarbarang[i].jumlahbeli, subtotal);
            total += subtotal;
        }
    }
    printf("Total Harga : Rp %.2f\n", total);
}

int main() {
    int logged = 0;
    int menu;
    color();
    loading();
    printf("SELAMAT DATANG DI SUPERMARKET ANJAY\n");
    registerakun();
    stokawal();

    while (!logged) {
        logged = loginakun();
        Sleep(1000);
        system("cls");
    }

    do {
        printf("\nMenu Utama\n");
        printf("1. Tampilkan Barang\n");
        printf("2. Tambah Barang\n");
        printf("3. Kasir\n");
        printf("4. Keranjang\n");
        printf("5. Exit\n");
        printf("Masukan Menu(angka) : ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                menuuu();
                break;
            case 2:
                tambahbarang();
                break;
            case 3:
                kasir();
                break;
            case 4:
                keranjang();
                break;
            case 5:
                printf("Terima kasih sudah berbelanja!\n");
                break;
            default:
                printf("Menu tidak valid!\n");
        }
    } while (menu != 5);

    return 0;
}
