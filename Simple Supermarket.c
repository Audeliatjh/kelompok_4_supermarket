#include <stdio.h>
#include <string.h>

struct barang{
    char namabarang[100];
    int stok;
    float harga;
    int jumlahbeli;
};

struct akun{
    char username[100];
    char password[100];
};

struct akun daftarakun[100];
struct barang daftarbarang[100];
int jumlahakun=0;
int jumlahbarang=0;

void registerakun() {
    printf("\nREGISTER AKUN BARU\n");
    printf("Username : ");
    scanf("%s", daftarakun[jumlahakun].username);
    printf("Password : ");
    scanf("%s", daftarakun[jumlahakun].password);
    jumlahakun++;
    printf("Akun berhasil dibuat!\n");
}

int loginakun() {
    char inputuser[100], inputpassword[100];
    
    printf("\nLOGIN\n");
    printf("Username : ");
    scanf("%s", inputuser);
    printf("Password : ");
    scanf("%s", inputpassword);
    
    for(int i=0;i<jumlahakun;i++) {
        if(strcmp(inputuser, daftarakun[i].username) == 0 && strcmp(inputpassword, daftarakun[i].password) == 0) {
            printf("Login Berhasil!\n");
            printf("Selamat Datang di Supermarket Anjay\n");
            return 1;
        }
    }
    printf("Login Gagal, Username atau Password salah!\n");
    return 0;
}

void menuuu() {
    printf("\nMENU SUPERMARKET ANJAY\n");
    for(int i=0;i<jumlahbarang;i++) {
        printf("%d. %s | Stok : %d | Harga : %.2f\n", i+1, daftarbarang[i].namabarang, daftarbarang[i].stok, daftarbarang[i].harga);
    }
}

void tambahbarang() {
    printf("\nTAMBAH BARANG\n");
    printf("Nama Barang : ");
    scanf("%s", daftarbarang[jumlahbarang].namabarang);
    printf("Masukan Jumlah Stok : ");
    scanf("%d", &daftarbarang[jumlahbarang].stok);
    printf("Masukan Harga : ");
    scanf("%f", &daftarbarang[jumlahbarang].harga);
    daftarbarang[jumlahbarang].jumlahbeli=0;
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
    if(index >= 0 && index < jumlahbarang && jumlah <= daftarbarang[index].stok) {
        daftarbarang[index].jumlahbeli += jumlah;
        daftarbarang[index].stok -= jumlah;
        printf("Barang ditambahkan ke keranjang.\n");
    } else {
        printf("Jumlah baranf tidak valid atau stok kurang.\n");
    }
}

void keranjang() {
    float total = 0;
    printf("KERANJANG\n");
    for(int i=0;i<jumlahbarang;i++) {
        if (daftarbarang[i].jumlahbeli > 0) {
            float subtotal = daftarbarang[i].jumlahbeli * daftarbarang[i].harga;
            printf("%s x%d = %.2f/n", daftarbarang[i].namabarang, daftarbarang[i].jumlahbeli, subtotal);
            total += subtotal;
        }
    }
    printf("Total Harga : Rp %.2f\n");
}

int main() {
    int logged = 0;
    int menu;
    
    printf("SELAMAT DATANG DI SUPERMARKET ANJAY\n");
    registerakun();
    while (!logged) {
        logged = loginakun();
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
                printf("Developer");
                break;
            default:
                printf("Menu tidak valid!");
        }
    }while (menu !=5);
    
    
    
    return 0;
}
