#include <stdio.h>
#include <stdlib.h>

#define RED     "\x1b[41m"   // Background merah
#define WHITE   "\x1b[47m"   // Background putih
#define RESET   "\x1b[0m"    // Reset warna

void gambarBendera(int tinggi) {
    int i, j;
    int lebar = tinggi * 4; // proporsional

    // Bagian merah
    for (i = 0; i < tinggi; i++) {
        printf("|| ");
        for (j = 0; j < lebar; j++)
            printf(RED " " RESET);
        printf("\n");
    }

    // Bagian putih
    for (i = 0; i < tinggi; i++) {
        printf("|| ");
        for (j = 0; j < lebar; j++)
            printf(WHITE " " RESET);
        printf("\n");
    }

    // Tiang bawah
    for (i = 0; i < tinggi; i++) {
        printf("||\n");
    }
}

int main() {
menu:
    system("cls || clear");

    printf("=====================================\n");
    printf("=               Bendera             =\n");
    printf("=====================================\n\n");

    int tinggi;
    printf("Masukkan tinggi bendera: ");
    scanf("%d", &tinggi);

    printf("\n");

    gambarBendera(tinggi);

    int pilihan;
    printf("\n");
    printf("1. Ulang\n");
    printf("2. Exit\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);

    if (pilihan == 1)
        goto menu;

    printf("Keluar...\n");
    return 0;
}
