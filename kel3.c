#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// ====================================================================
//                       FUNGSI DASAR (WARNA & CURSOR)
// ====================================================================
void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                           (bgColor << 4) | textColor);
}

void setCursorPosition(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ====================================================================
//                       LOADING AWAL (PERSEN + BAR)
// ====================================================================
void loadingAnimation() {
    int barWidth = 40;
    int percent = 0;

    setColor(15, 1);
    system("cls");

    setCursorPosition(28, 5);
    printf("      SELAMAT DATANG DI TUGAS RANCANG");

    while (percent <= 100) {
        setCursorPosition(36, 7);
        printf("Loading : %3d%%", percent);

        setCursorPosition(28, 8);
        printf("============================================");

        setCursorPosition(28, 9);
        printf("||");

        int filled = (percent * barWidth) / 100;

        for (int i = 0; i < barWidth; i++) {
            if (i < filled) {
                setColor(15, 15);
                printf("%c", 219);
                setColor(15, 1);
            } else {
                printf(" ");
            }
        }

        printf("||");

        setCursorPosition(28, 10);
        printf("============================================");

        Sleep(45);
        percent++;
    }

    Beep(1000, 200);
    setCursorPosition(33, 12);
    printf("Tekan ENTER untuk melanjutkan...");
    getchar();
}

// ====================================================================
//                 LOADING KETIK SETELAH LOGIN BERHASIL
// ====================================================================
void loadingKetik() {
    system("cls");
    setColor(15, 1);

    int centerX = 40;   // posisi tengah horizontal (ubah jika layar berbeda)
    int centerY = 10;   // posisi tengah vertical
    char text[] = "Loading....";

    // Tampilkan Loading.... secara mengetik
    setCursorPosition(centerX, centerY);
    for (int i = 0; i < strlen(text); i++) {
        printf("%c", text[i]);
        Sleep(180);
    }

    // Teks NEXT setelah loading selesai
    Sleep(300);
    setCursorPosition(centerX - 2, centerY + 4);
    printf(">>>> NEXT >>>>");

    getch();
}


// ====================================================================
//                        DATA LOGIN USER
// ====================================================================
typedef struct {
    char user[20];
    char pass[20];
} Akun;

Akun akunList[] = {
    {"admin", "admin123"},
    {"fajar", "ganteng"},
    {"123456", "password"}
};

int totalAkun = 3;

// ====================================================================
//                         CEK LOGIN
// ====================================================================
int cekLogin(char user[], char pass[]) {
    for (int i = 0; i < totalAkun; i++) {
        if (strcmp(user, akunList[i].user) == 0 &&
            strcmp(pass, akunList[i].pass) == 0) {
            return 1;
        }
    }
    return 0;
}

// ====================================================================
//                      TAMPILAN LOGIN
// ====================================================================
void tampilLogin() {
LOGIN_AGAIN:
    system("cls");
    setColor(15, 1);
    Beep(1000, 200);
    int x = 28, y = 6;

    setCursorPosition(x, y);
    printf("++============================================++");
    setCursorPosition(x, y + 1);
    printf("||        Username :                          ||");
    setCursorPosition(x, y + 2);
    printf("||        Password :                          ||");
    setCursorPosition(x, y + 3);
    printf("++============================================++");

    char username[30], password[30];
    int index = 0;
    char ch;

    // INPUT USERNAME
    setCursorPosition(x + 22, y + 1);
    scanf("%s", username);

    // INPUT PASSWORD (masked)
    setCursorPosition(x + 22, y + 2);
    index = 0;

    while (1) {
        ch = getch();

        if (ch == 13) { // ENTER
            password[index] = '\0';
            break;
        }

        if (ch == 8 && index > 0) { // BACKSPACE
            index--;
            printf("\b \b");
            continue;
        }

        password[index++] = ch;
        printf("*");
    }

    // CLEAR LAYAR HASIL LOGIN
    system("cls");
    setColor(15, 1);

    setCursorPosition(x, y);
    printf("++============================================++");

    setCursorPosition(x, y + 1);
    printf("||   Username: %-30s||", username);

    char passMask[30];
    for (int i = 0; i < strlen(password); i++) passMask[i] = '*';
    passMask[strlen(password)] = '\0';

    setCursorPosition(x, y + 2);
    printf("||   Password: %-30s||", passMask);

    setCursorPosition(x, y + 3);
    printf("++============================================++");

    // VALIDASI LOGIN
    if (cekLogin(username, password)) {
        setCursorPosition(x + 12, y + 5);
        printf("[ Login Berhasil ]");
        getch();

        loadingKetik();  // <-- LOADING KETIK JIKA LOGIN BENAR
        return;
    }

    // LOGIN GAGAL
    setCursorPosition(x + 14, y + 5);
    printf("[ Login Gagal ]");

    setCursorPosition(x + 8, y + 7);
    printf("Username / Password Salah");

    setCursorPosition(x + 12, y + 9);
    printf(">>>> Coba Lagi >>>>");

    getch();
    goto LOGIN_AGAIN;
}



// ====================================================================
//                       MENU BENDERA                                //
// ====================================================================
#define RED_BG_COLOR    4  //warna background merah
#define WHITE_BG_COLOR  7  //warna background putih

void clearScreen(void) { //fungsi membersihkan layar
    system("cls || clear");
}

void printJudulBendera(int tinggi) { //fungsi print judul
    setColor(15, 1); //warna teks putih, background biru
    printf("========================================================\n"); 
    printf("=                        Bendera                       =\n");
    printf("========================================================\n\n");
    if (tinggi >= 0) { //input tinggi
        setColor(15, 1);
        printf("Masukkan tinggi bendera: %d\n\n", tinggi);
    }
}

void sleep_ms(int ms) { //fungsi delay 
    Sleep(ms);
}

void gambarBendera(int tinggi) { //fungsi gambar bendera
    int i, j;
    int lebar = tinggi * 4; //lebar 4 x tinggi
    setColor(15, 1);

    for (i = 0; i < tinggi; i++) { //bagian merah
        setColor(15, 1); //warna teks putih, background biru
        printf("|| "); //gambar tiang bendera
        setColor(15, RED_BG_COLOR); //warna background merah
        for (j = 0; j < lebar; j++) printf(" "); //menggambar bagian merah
        setColor(15, 1); //kembali ke warna teks putih, background biru
        printf("\n");
    }

    for (i = 0; i < tinggi; i++) { //bagian putih
        setColor(15, 1); //warna teks putih, background biru
        printf("|| "); //gambar tiang bendera
        setColor(0, WHITE_BG_COLOR); //warna background putih
        for (j = 0; j < lebar; j++) printf(" "); //menggambar bagian putih
        setColor(15, 1); //kembali ke warna teks putih, background biru
        printf("\n");
    }

    for (i = 0; i < tinggi; i++) { //bagian tiang bawah
        setColor(15, 1); //warna teks putih, background biru
        printf("||\n");
    }
}

void animasiBendera(int tinggi, int delay_ms) { //fungsi animasi bendera
    int i, j;
    int lebar = tinggi * 4; // lebar dibuat 4 x dari tinggi
    int totalRows = tinggi * 3; // total baris tiang dan bendera
    int flagRows = tinggi * 2; // total baris bendera
    setColor(15, 1);

    for (i = 0; i < totalRows; i++) { // Animasi tiang bendera: tampilkan tiang baris demi baris
        clearScreen();
        printJudulBendera(tinggi); 
        for (int r = 0; r <= i; r++) { // perulangan untuk setiap baris hingga i
            if (r < flagRows) { // bagian bendera: kosongkan
                printf("|| ");
                setColor(15, 1);
                for (j = 0; j < lebar; j++) printf(" "); //menggambar bagian kosong
                printf("\n");
            } else {
                printf("||\n");
            }
        }
        for (int r = i + 1; r < totalRows; r++) putchar('\n'); // sisakan baris kosong untuk animasi
        sleep_ms(delay_ms); // delay
    }

    for (i = 0; i < flagRows; i++) { // Animasi bendera: tampilkan warna baris demi baris
        clearScreen();
        printJudulBendera(tinggi);
        for (int r = 0; r < totalRows; r++) { // perulangan untuk setiap baris
            if (r < flagRows) { // baris-baris bendera, tampilkan warna bila sudah waktunya
                printf("|| ");
                if (r <= i) {
                    if (r < tinggi) {
                            setColor(15, RED_BG_COLOR); //warna background merah
                            for (j = 0; j < lebar; j++) printf(" ");
                            setColor(15, 1);
                    } else {
                            setColor(0, WHITE_BG_COLOR); //warna background putih
                            for (j = 0; j < lebar; j++) printf(" ");
                            setColor(15, 1);
                    }
                } else {
                    setColor(15, 1); //warna teks putih, background biru
                    for (j = 0; j < lebar; j++) printf(" "); //menggambar bagian kosong
                }
                printf("\n");
            } else {
                printf("||\n"); // bagian tiang bawah
            }
        }
        sleep_ms(delay_ms);
    }
    clearScreen(); 
    printJudulBendera(tinggi);
    gambarBendera(tinggi);
}

void menuBendera() { //fungsi menu bendera
menu:
    clearScreen();
    printJudulBendera(-1);
    setColor(15, 1);

    int tinggi;
    while (1) { //input tinggi dengan validasi
        printf("Masukkan tinggi bendera: "); 
        if (scanf("%d", &tinggi) != 1) { //cek input apakah angka
            printf("Input tidak valid! Harap masukkan angka.\n");
            while (getchar() != '\n'); // bersihkan buffer input
            continue; // ulang input
        }
        break;
    }

    animasiBendera(tinggi, 100); //jalankan animasi bendera

    int pilihan;
    while (1) {
        printf("\n1. Ulang\n2. Exit\nPilihan: "); //menu ulang atau exit
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n"); //cek input valid (harus angka)
            while (getchar() != '\n'); // bersihkan buffer input
            continue; // ulang input
        }
        if (pilihan == 1) goto menu; // ulang menu
        else if (pilihan == 2) break;      // keluar dari menu
        else printf("Pilihan hanya 1 atau 2!\n"); //cek pilihan hanya 1 atau 2
    }
}

// ====================================================================
//                       TAMPIL CREATOR                                
// ====================================================================

void typeEffect(const char *text, int delay) { //efek mengetik
    while (*text) { // selama belum akhir string
        printf("%c", *text); // cetak karakter saat ini
        fflush(stdout); // pastikan karakter langsung tampil
        usleep(delay); // delay mikrodetik
        text++; // pindah ke karakter berikutnya
    }
}

void tampilCreator() {
    system("cls || clear"); // Bersihkan layar
    printf("==================================================\n");
    printf("=                     CREATOR                    =\n");
    printf("==================================================\n\n");

    // Animasi mengetik
    typeEffect("Nama : Wahyu Andrean\n", 45000); // delay 45ms per karakter
    typeEffect("NIM  : 672025049\n\n", 45000);

    typeEffect("Nama : M. Fajar Putra\n", 45000);
    typeEffect("NIM  : 672025053\n\n", 45000);

    typeEffect("Nama : Christian Loveindi\n", 45000);
    typeEffect("NIM  : 672025042\n\n", 45000);

    typeEffect("Nama : Damar Maharyanu Prihanto\n", 45000);
    typeEffect("NIM  : 672025051\n\n", 45000);


    printf("\n>>>> Next >>>>\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);   // bersihkan buffer
    printf("Press Enter to continue...");
    getchar(); // tunggu Enter
}

void menuBelanja() {
    struct Barang {
        char nama[30];
        int harga;
    };

    struct Barang daftar[] = {
        {"Potato", 10000},
        {"Sunsilk", 18000},
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

    system("cls || clear");
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
    printf("Uang Pembeli              : Rp %d\n", uang);
    printf("Kembalian                 : Rp %d\n", uang - total);
    printf("-----------------------------------------------\n");
    printf("\n>>>> Next >>>>\n");
    int c; while ((c = getchar()) != '\n' && c != EOF); // bersihkan buffer
    getchar(); // tunggu Enter
}

void menuBGK() {
    int user, komputer;
    char ulang;
    char *nama[4] = {"", "batu", "gunting", "kertas"};

    srand(time(NULL));

    do {
        system("cls || clear"); // Windows: cls, Linux/Mac: clear

        printf("=======================================================\n");
        printf("||               Permainan Batu Gunting Kertas       ||\n");
        printf("=======================================================\n");
        printf("||                                                   ||\n");
        printf("||                   1. Batu                         ||\n");
        printf("||                   2. Gunting                      ||\n");
        printf("||                   3. Kertas                       ||\n");
        printf("||                                                   ||\n");
        printf("=======================================================\n");

        // INPUT USER
        printf("||   Masukkan pilihan : ");
        scanf("%d", &user);
        printf("||%50s||\n", "");   // menutup kanan dengan rapi
        printf("=======================================================\n\n");

        if (user < 1 || user > 3) {
            printf("Pilihan tidak valid!\n");
            ulang = 'u';
            continue;
        }

        komputer = (rand() % 3) + 1;
        printf("    Komputer memilih %s\n", nama[komputer]);

        // Tentukan hasil
        if (user == komputer) {
            printf("    Hasil : Seri\n");
        } else if ((user == 1 && komputer == 2) ||
                   (user == 2 && komputer == 3) ||
                   (user == 3 && komputer == 1)) {
            printf("    Hasil : Pemenangnya Kamu\n");
        } else {
            printf("    Hasil : Pemenangnya Komputer\n");
        }

        printf("\n");
        printf("U (Ulang)\n");
        printf("X (Exit)\n");
        printf("Masukkan pilihan : ");
        scanf(" %c", &ulang);

        ulang = tolower(ulang);

    } while (ulang == 'u');

    printf("\nTekan Enter untuk kembali ke menu...");
    int c; while ((c = getchar()) != '\n' && c != EOF); // bersihkan buffer
    getchar();
}



void menuUtama() {
    int pilihan;

    while (1) {
        clearScreen();
        setColor(15, 1);
        Beep(1000, 200);

        int x = 20;   // POSISI KE TENGAH
        int y = 3;

        // ================== HEADER ====================
        setCursorPosition(x, y++);
        printf("++====================================================++");
        setCursorPosition(x, y++);
        printf("||                     KELOMPOK 4                     ||");
        setCursorPosition(x, y++);
        printf("++====================================================++");

        // ================== MENU =======================
        setCursorPosition(x, y++);
        printf("||                                                    ||");
        setCursorPosition(x, y++);
        printf("||                    [  Menu : ]                     ||");
        setCursorPosition(x, y++);
        printf("||                                                    ||");

        setCursorPosition(x, y++);
        printf("||        1. Toko Kelontong                           ||");
        setCursorPosition(x, y++);
        printf("||        2. Batu Gunting Kertas                      ||");
        setCursorPosition(x, y++);
        printf("||        3. Bendera                                  ||");
        setCursorPosition(x, y++);
        printf("||        4. Author                                   ||");
        setCursorPosition(x, y++);
        printf("||        5. Exit                                     ||");

        setCursorPosition(x, y++);
        printf("||                                                    ||");

        // ================== GARIS PEMBATAS =============
        setCursorPosition(x, y++);
        printf("++====================================================++");

        // ================== INPUT DALAM KOTAK ==========
        setCursorPosition(x, y);
        printf("  Pilihan:  ");
        setCursorPosition(x + 10, y); 
        scanf("%d", &pilihan);

        // ================== LOGIKA MENU =================
        switch (pilihan) {
            case 1:
                Beep(1000, 200);
                menuBelanja();
                break;
            case 2:
                Beep(1000, 200);
                menuBGK();
                break;
            case 3:
                Beep(1000, 200);
                menuBendera();
                break;
            case 4:
                Beep(1000, 200);
                tampilCreator();
                break;
            case 5:
                setCursorPosition(x + 10, y + 2);
                printf("Keluar...\n");
                Sleep(1000);
                return;

            default:
                setCursorPosition(x + 10, y + 2);
                printf("Pilihan hanya 1-5!\n");
                Sleep(1000);
        }
    }
}



// ====================================================================
//                           MAIN PROGRAM
// ====================================================================
int main() {
    loadingAnimation();
    tampilLogin();
    menuUtama();
    return 0;
}
