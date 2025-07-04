#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#define MAX_BARANG 100
#define ENTER 13
#define UP_ARROW 72
#define DOWN_ARROW 80

struct akun{
    char username[100];
    char password[100];
};

struct akun daftarakun[100];
int jumlahakun=0;

void hapusenter(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void gotoxy(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void loading(){
    int width, height;
    getConsoleSize(&width, &height);

    const char *text = "Loading";
    int x = (width - strlen(text) - 6) / 2; // 6 karakter tambahan untuk efek ▓▓▓
    int y = height / 2;

    gotoxy(x, y);
    printf("%s", text);

    for (int i = 0; i < 3; i++) {
        printf("%c%c", 219, 219); // efek kotak
        Sleep(900);
    }
    Beep(670, 200);
    system("cls");
}


void inputPassword(char *password) {
    int pos = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) {
            break;
        } else if (ch == 8 && pos > 0) {
            pos--;
            printf("\b \b");
        } else if (ch != 8 && pos < 99) {
            password[pos++] = ch;
            printf("*");
        }
    }
    password[pos] = '\0';
    printf("\n");
}

void registerakun(){
    system("cls");
    int width, height;
    getConsoleSize(&width, &height);

    const char *lines[] = {
        "=======================",
        "|  REGISTER AKUN BARU |",
        "=======================",
    };

    int linesCount = sizeof(lines)/sizeof(lines[0]);
    int startY = (height - linesCount - 4) / 2; // -4 untuk jarak input dan pesan
    int kotakX = (width - strlen(lines[0])) / 2; // posisi awal kiri dari kotak

    // Tampilkan header kotak
    for (int i = 0; i < linesCount; i++) {
        gotoxy(kotakX, startY + i);
        printf("%s\n", lines[i]);
    }

    // Input username (sejajar dengan '=' pertama)
    gotoxy(kotakX, startY + 3);
    printf("Username : ");
    fgets(daftarakun[jumlahakun].username, sizeof(daftarakun[jumlahakun].username), stdin);
    hapusenter(daftarakun[jumlahakun].username);

    gotoxy(kotakX, startY + 4);
    printf("Password : ");
    inputPassword(daftarakun[jumlahakun].password);

    jumlahakun++;
    system("color a0");

    // Cetak garis bawah dan pesan berhasil
    gotoxy(kotakX, startY + 5);
    printf("=======================\n");

    const char *msg = "Akun berhasil dibuat!";
    gotoxy((width - strlen(msg)) / 2, startY + 6);
    printf("%s\n", msg);

    gotoxy(0, height - 1); // pindahkan cursor ke bawah agar pause tidak nutup
    system("pause");
    system("cls");
}

int loginakun() {
    system("cls");
    int width, height;
    getConsoleSize(&width, &height);

    const char *lines[] = {
        "=======================",
        "|        LOGIN        |",
        "======================="
    };

    int linesCount = sizeof(lines) / sizeof(lines[0]);
    int startY = (height - linesCount - 4) / 2; // -4 untuk input dan pesan
    int kotakX = (width - strlen(lines[0])) / 2; // posisi awal kiri dari kotak

    char inputuser[100], inputpassword[100];
    system("color 0f");

    // Tampilkan header kotak
    for (int i = 0; i < linesCount; i++) {
        gotoxy(kotakX, startY + i);
        printf("%s\n", lines[i]);
    }

    // Input username
    gotoxy(kotakX, startY + 3);
    printf("Username : ");
    fgets(inputuser, sizeof(inputuser), stdin);
    hapusenter(inputuser);

    // Input password
    gotoxy(kotakX, startY + 4);
    printf("Password : ");
    inputPassword(inputpassword);

    // Cek kredensial
    for (int i = 0; i < jumlahakun; i++) {
        if (strcmp(inputuser, daftarakun[i].username) == 0 &&
            strcmp(inputpassword, daftarakun[i].password) == 0) {
            system("color a0");

            gotoxy(kotakX, startY + 5);
            printf("=======================\n");
            const char *msg = "Login Berhasil!";
            gotoxy((width - strlen(msg)) / 2, startY + 6);
            printf("%s\n", msg);

            gotoxy(0, height - 1);
            getchar();
            system("cls");
            return 1;
        }
    }

    // Jika gagal login
    system("color cf");
    gotoxy(kotakX, startY + 5);
    printf("=======================\n");

    const char *msg = "Login Gagal, Username atau Password salah!";
    gotoxy((width - strlen(msg)) / 2, startY + 6);
    printf("%s\n", msg);

    const char *msg2 = "Masukkan Username atau Password yang benar!";
    gotoxy((width - strlen(msg2)) / 2, startY + 7);
    printf("%s\n", msg2);

    gotoxy(0, height - 1);
    getchar();
    system("cls");
    return 0;
}

struct Barang {
    char nama[50];
    int jumlah;
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

// Fungsi untuk mengecek apakah string hanya berisi spasi atau kosong
int is_string_empty_or_whitespace(const char *str) {
    if (str == NULL || *str == '\0') {
        return 1; // String kosong
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return 0; // Menemukan karakter selain spasi
        }
    }
    return 1; // Hanya berisi spasi
}

void sortBarangAbjad() {
    struct Barang temp;
    for (int i = 0; i < jumlahKeranjangBarang - 1; i++) {
        for (int j = i + 1; j < jumlahKeranjangBarang; j++) {
            if (strcasecmp(keranjangBarang[i].nama, keranjangBarang[j].nama) > 0) {
                // Tukar posisi
                temp = keranjangBarang[i];
                keranjangBarang[i] = keranjangBarang[j];
                keranjangBarang[j] = temp;
            }
        }
    }
}

void tampilkanBarang(){
    if (jumlahKeranjangBarang == 0) {
        printf("\nTidak ada barang dalam stok.\n");
        return;
    }

    sortBarangAbjad();

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
        snprintf(hargaDisplay, sizeof(hargaDisplay), "Rp%.0f", keranjangBarang[i].hargaVal);
        printCenter(hargaDisplay, lebarHarga); printf("|\n");
    }
    printf("----------------------------------------------------\n");
    sudahLihatBarang = 1;
}

void tambahBarang() {
    if (!sudahLihatBarang) {
        printf("\n⚠ Harus lihat daftar barang dulu sebelum tambah barang.\n");
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

    // Loop untuk memastikan input nama barang tidak kosong atau hanya spasi
    while (1) {
        printf("Masukkan nama barang: ");
        fflush(stdin);
        fgets(b->nama, sizeof(b->nama), stdin);
        hapusenter(b->nama); // Hapus karakter newline

        if (is_string_empty_or_whitespace(b->nama)) {
            printf("Nama barang tidak boleh kosong atau hanya berisi spasi. Silakan masukkan lagi.\n");
        } else {
            break; // Input valid, keluar dari loop
        }
    }

    int validInput = 0;
    while (!validInput) {
        printf("Masukkan jumlah stok: ");
        if (scanf("%d", &b->jumlah) == 1) {
            if (b->jumlah < 0) {
                printf("Jumlah stok tidak boleh negatif. Silakan masukkan lagi.\n");
            } else {
                validInput = 1;
            }
        } else {
            printf("Input tidak valid! Harap masukkan angka untuk jumlah stok.\n");
            while (getchar() != '\n'); // Bersihkan buffer
        }
    }

    validInput = 0;
    while (!validInput) {
        printf("Masukkan harga barang: ");
        if (scanf("%f", &b->hargaVal) == 1) {
            if (b->hargaVal < 0) {
                printf("Harga barang tidak boleh negatif. Silakan masukkan lagi.\n");
            } else {
                validInput = 1;
            }
        } else {
            printf("Input tidak valid! Harap masukkan angka untuk harga barang.\n");
            while (getchar() != '\n');
        }
    }

    jumlahKeranjangBarang++;
    printf("Barang berhasil ditambahkan.\n");
    system("pause");
    system("cls");
}

void kalkulasiHarga(){

    tampilkanBarang();

    int nomorBarang, jumlahBeli,validInput;
    printf("\nMasukkan nomor barang yang ingin dibeli: ");
    validInput = scanf("%d", &nomorBarang);
    if(validInput != 1) {
        printf("Input tidak valid! Harap masukkan angka.\n");
        getch();
        // Bersihkan buffer agar tidak loop terus karena karakter masih tertinggal
        while(getchar() != '\n');
        return;
    }

    if(nomorBarang < 1 || nomorBarang > jumlahKeranjangBarang) {
        printf("Nomor barang tidak valid!\n");
        getch();
        return;
    }

    int index = nomorBarang - 1; // Penyesuaian indeks array

    printf("Masukkan jumlah yang ingin dibeli: ");
    scanf("%d", &jumlahBeli);

    if(jumlahBeli <= 0) {
        printf("Jumlah tidak boleh kurang dari 1!\n");
        getch();
        return;
    }

    if(jumlahBeli > keranjangBarang[index].jumlah) {
        printf("Stok tidak mencukupi!\n");
        getch();
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
    system("cls");
}

void bayar() {
    system("cls");
    float subtotal = 0, totalDiskon = 0, totalPajak = 0, totalAkhir = 0;
    int uangDibayar, kembalian;

    printf("======== Struk Belanja ========\n");
    for (int i = 0; i < jumlahKeranjang; i++) {
        float hargaTotal = keranjang[i].hargaVal * keranjang[i].jumlah;
        float diskon = 0;
        if(keranjang[i].jumlah>=5){
            diskon = 0.10*hargaTotal;
        }
        float hargaSetelahDiskon = hargaTotal - diskon;
        float pajak = 0.02 * hargaSetelahDiskon;
        float total = hargaSetelahDiskon + pajak;

        subtotal += hargaTotal;
        totalDiskon += diskon;
        totalPajak += pajak;
        totalAkhir += total;

        printf("%s x%d @%.0f = %.0f\n", keranjang[i].nama, keranjang[i].jumlah, keranjang[i].hargaVal, hargaTotal);
        printf("  Diskon: %.0f\n", diskon);
        printf("  Pajak : %.0f\n", pajak);
        printf("  Total : %.0f\n\n", total);
    }
    printf("==============================\n");
    printf("Subtotal      : %.0f\n", subtotal);
    printf("Total Diskon  : %.0f\n", totalDiskon);
    printf("Total Pajak   : %.0f\n", totalPajak);
    printf("Total Akhir   : %.0f\n", totalAkhir);
    printf("==============================\n\n");

    // Validasi input uang
    int validInput;
    do {
        printf("Uang Anda: Rp.");
        validInput = scanf("%d", &uangDibayar);

        if (validInput != 1) {
            printf("Input tidak valid! Harap masukkan angka.\n");
            getch();
            while (getchar() != '\n');
            return;
        }

        if (uangDibayar < totalAkhir) {
            printf("Uang Anda kurang!\n");
        }
    } while (uangDibayar < totalAkhir || validInput != 1);

    kembalian = uangDibayar - totalAkhir;

    FILE *fptr = fopen("struk.txt", "w");
    if (fptr == NULL) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    fprintf(fptr, "======= Struk Belanja =======\n");
    for (int i = 0; i < jumlahKeranjang; i++) {
        float hargaTotal = keranjang[i].hargaVal * keranjang[i].jumlah;
        float diskon = 0;
        if (keranjang[i].jumlah >= 5){
            diskon = 0.10 * hargaTotal;
        }
        float hargaSetelahDiskon = hargaTotal - diskon;
        float pajak = 0.02 * hargaSetelahDiskon;
        float total = hargaSetelahDiskon + pajak;

        fprintf(fptr, "%s x%d @%.0f = %.0f\n", keranjang[i].nama, keranjang[i].jumlah, keranjang[i].hargaVal, hargaTotal);
        fprintf(fptr, "  Diskon: %.0f\n", diskon);
        fprintf(fptr, "  Pajak : %.0f\n", pajak);
        fprintf(fptr, "  Total : %.0f\n\n", total);
    }

    fprintf(fptr, "==============================\n");
    fprintf(fptr, "Subtotal      : %.0f\n", subtotal);
    fprintf(fptr, "Total Diskon  : %.0f\n", totalDiskon);
    fprintf(fptr, "Total Pajak   : %.0f\n", totalPajak);
    fprintf(fptr, "Total Akhir   : %.0f\n", totalAkhir);
    fprintf(fptr, "Uang Dibayar  : Rp. %d\n", uangDibayar);
    fprintf(fptr, "Kembalian     : Rp. %d\n", kembalian);
    fprintf(fptr, "==============================\n");

    fclose(fptr);

    printf("Kembalian : Rp. %d\n", kembalian);
    printf("==============================\n");
    printf("\nLihat struk belanja di menu Tampilkan Struk\n");
    system("pause");
}

void tampilkanStruk(){
    FILE *fptr;
    char ch;
    system("cls");

    fptr = fopen("struk.txt", "r");
    if(fptr == NULL){
        printf("Gagal menampilkan struk! Mungkin belum ada pembayaran yang dilakukan.\n");
        system("pause");
        return;
    }

    while((ch = fgetc(fptr)) !=EOF){
        printf("%c", ch);
    }
    fclose(fptr);
    system("pause");
}

void inisialisasiBarangAwal() {
    strcpy(keranjangBarang[0].nama, "Beras 5kg");
    keranjangBarang[0].jumlah = 20;
    keranjangBarang[0].hargaVal = 60000;

    strcpy(keranjangBarang[1].nama, "Minyak Goreng 2L");
    keranjangBarang[1].jumlah = 15;
    keranjangBarang[1].hargaVal = 35000;

    strcpy(keranjangBarang[2].nama, "Gula Pasir 1kg");
    keranjangBarang[2].jumlah = 25;
    keranjangBarang[2].hargaVal = 15000;

    strcpy(keranjangBarang[3].nama, "Telur Ayam 1kg");
    keranjangBarang[3].jumlah = 10;
    keranjangBarang[3].hargaVal = 28000;

    strcpy(keranjangBarang[4].nama, "Kopi Instan");
    keranjangBarang[4].jumlah = 30;
    keranjangBarang[4].hargaVal = 12000;

    jumlahKeranjangBarang = 5;
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
    system("cls");
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
    getchar();
    system("cls");
}

void tampilkanMenu(int pilihan, char menu[][30], int jumlah) {
    system("cls");
    printf("\n====== MENU UTAMA ======\n");
    for (int i = 0; i < jumlah; i++) {
        if (i == pilihan) {
            printf("  --> %s\n", menu[i]);
        } else {
            printf("      %s\n", menu[i]);
        }
    }
}

int main() {
    int pilihan=0; //pilihan menu yang sedang aktif
    int logged=0;
    char key;
    int keluar=0;

    registerakun();
    loading();
    while (!logged) {
        logged = loginakun();
    }
    loading();
    inisialisasiBarangAwal();

      char menu[6][30] = {
        "Lihat Barang",
        "Tambah Barang",
        "Kalkulasi Harga",
        "Bayar",
        "Tampilkan Struk",
        "Keluar"
    };

    do {
        system("color 0f");
        tampilkanMenu(pilihan, menu, 6);
        key = _getch();

        if (key == 72 && pilihan > 0) pilihan--;        // panah atas
        else if (key == 80 && pilihan < 5) pilihan++;  // panah bawah
        else if (key == 13) {                          // Enter
            system("cls");
            switch (pilihan) {
                case 0:
                    tampilkanBarang();
                    getch();
                    break;
                case 1:
                    tambahBarang();
                    break;
                case 2:
                    kalkulasiHarga();
                    break;
                case 3:
                    bayar();
                    break;
                case 4:
                    tampilkanStruk();
                    break;
                case 5:
                    selesai();
                    developer();
                    keluar=1;
            }
        }
    } while(!keluar);
    return 0;
}
