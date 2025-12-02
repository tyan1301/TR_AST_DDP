#include <stdio.h>
#include <string.h>

struct Barang {
    char nama[30];
    int harga;
};

int main() {
    struct Barang daftar[] = {
        {"Potato", 10000},
        {"sunsilk", 18000},
        {"Rexona", 23000},
        {"Khaf", 42000},
        {"Kecap Bangau", 19000},
        {"Sosis", 24000},
        {"Makarizo", 24000},
        {"Wipol", 18000},
        {"Indomie Kuah", 3500},
        {"Qtela", 9300},
        {"Bimoli", 27000},
        {"SilverQuin", 30000},
        {"Cocacola", 9500},
        {"Oreo", 11000},
        {"Roti Tawar", 13000}
    };

    int jumlah_barang = sizeof(daftar) / sizeof(daftar[0]);

    int kode, qty;
    char lanjut;
    char beli_nama[20][30];
    int beli_qty[20];
    int beli_total[20];
    int count = 0;

    printf("============== GROSIR ECERAN =============\n");
    printf("| No | NAMA BARANG        | HARGA BARANG |\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < jumlah_barang; i++) {
        printf("| %-2d | %-17s | Rp %-7d |\n",
               i+1, daftar[i].nama, daftar[i].harga);
    }

    printf("===========================================\n\n");

    do {
        printf("Masukkan nomor barang: ");
        scanf("%d", &kode);

        if (kode < 1 || kode > jumlah_barang) {
            printf("Nomor Barang Tidak Valid!!!\n");
            continue;
        }

        printf("Jumlah Barang : ");
        scanf("%d", &qty);

        strcpy(beli_nama[count], daftar[kode-1].nama);
        beli_qty[count] = qty;
        beli_total[count] = daftar[kode-1].harga * qty;

        printf("Anda membeli %d %s\n", qty, daftar[kode-1].nama);

        printf("Ingin membeli barang lagi? (y/n): ");
        scanf(" %c", &lanjut);

        count++;

    } while (lanjut == 'y' || lanjut == 'Y');

    printf("\n================= STRUK BELANJA =================\n");
    int total = 0;

    for (int i = 0; i < count; i++) {
        printf("%-15s | %-2d | Rp %d\n",
               beli_nama[i], beli_qty[i], beli_total[i]);
        total += beli_total[i];
    }

    printf("-----------------------------------------------\n");
    printf("Total Harga               : Rp %.2f\n", (float)total);

    int uang;
ulang_bayar:
    printf("Masukkan Uang Pembeli     : Rp ");
    scanf("%d", &uang);

    if (uang < total) {
        printf("Uang pembeli kurang! Mohon masukkan lagi.\n");
        goto ulang_bayar;
    }

    printf("-----------------------------------------------\n");
    printf("Masukkan uang pembeli     : Rp %d\n", uang);
    printf("Kembalian                 : Rp %d\n", uang - total);
    printf("-----------------------------------------------\n");
    printf("\n>>>> Next >>>>\n");

    return 0;
}
