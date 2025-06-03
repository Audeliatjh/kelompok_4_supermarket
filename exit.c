#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void selesai(){
    int i;
    char tengs[]="\n\n\n\n\n\n\n\t\t\t\tTerimakasih telah berbelanja di Simple Supermarket^^\n\n\n\t\t\t\t\t(klik ENTER untuk melihat developer)";

    system("color 0a");

    for(i=0; tengs[i]!='\0'; i++){
        printf("%c", tengs[i]);
        Sleep(30);
    }
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

    system("color 8f");
    developerDelay(lines, 7, 30, 7);
    getchar();
}

int main(){
    selesai();
    system("cls");
    developer();
    system("cls");
    return 0;
}
