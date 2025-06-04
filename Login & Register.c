#include <stdio.h>
#include <string.h>

struct akun{
    char username[100];
    char password[100];
};

struct akun daftarakun[100];
int jumlahakun=0;

void hapusenter(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void registerakun() {
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
    printf("\n=======================\n");
    printf("Akun berhasil dibuat!\n");
}

int loginakun() {
    char inputuser[100], inputpassword[100];
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
            printf("==================\n");
            printf("Login Berhasil!\n");
            return 1;
        }
    }
    printf("Login Gagal, Username atau Password salah!\n");
    printf("Masukan Username atau Password yang benar!\n");

    return 0;
}

int main() {
    int logged = 0;
    registerakun();

    while (!logged) {
        logged = loginakun();
    }
    return 0;
}
