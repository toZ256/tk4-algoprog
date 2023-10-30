#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_HISTORY 100

// Struct untuk menyimpan data buku
typedef struct {
    char kode[10];
    char nama[100];
    char jenis[50];
    int harga;
} Buku;

// Struct untuk menyimpan data pembelian
typedef struct {
    char kodeUnik[20];  // Kode pembelian unik
    char kodeBuku[10]; // Kode buku yang dibeli
    int jumlah;
    int total;
} Pembelian;

// Fungsi-fungsi yang akan digunakan
void loadBooks(Buku books[], int *count);
void saveBooks(Buku books[], int count);
void loadHistory(Pembelian history[], int *count);
void saveHistory(Pembelian history[], int count);
void inputBuku(Buku books[], int *count);
void inputPembelian(Buku books[], int bookCount, Pembelian history[], int *historyCount);
void viewHistory(Buku books[], Pembelian history[], int historyCount, int bookCount);
void viewBooks(Buku books[], int bookCount);
void deleteHistory(Buku books[], Pembelian history[], int *historyCount, int *bookCount);
void deleteBook(Buku books[], int *bookCount, Pembelian history[], int historyCount);

int main() {
    Buku books[MAX_BOOKS];
    Pembelian history[MAX_HISTORY];
    int bookCount = 0;
    int historyCount = 0;
    int choice;

    // Memuat data buku dan riwayat pembelian dari file
    loadBooks(books, &bookCount);
    loadHistory(history, &historyCount);

    do {
        printf("\nMenu:\n");
        printf("1. Input data\n");
        printf("2. View History\n");
        printf("3. View Data\n");
        printf("4. Delete History\n");
        printf("5. Delete Buku\n");
        printf("6. Pembelian\n");
        printf("7. Exit\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);

        // Error checking input
        int extra = getchar();
        if (extra != '\n' && extra != EOF) {
            printf("\033[1;31m\n\nInput invalid, masukkan angka 1-7!!\033[0m\n\n");
            while (getchar() != '\n');
            continue;
        } else {
            switch (choice) {
                case 1:
                    inputBuku(books, &bookCount);
                    saveBooks(books, bookCount);
                    break;
                case 2:
                    viewHistory(books, history, historyCount, bookCount);
                    break;
                case 3:
                    viewBooks(books, bookCount);
                    break;
                case 4:
                    deleteHistory(books, history, &historyCount, &bookCount);
                    break;
                case 5:
                    deleteBook(books, &bookCount, history, historyCount);
                    break;
                case 6:
                    inputPembelian(books, bookCount, history, &historyCount);
                    saveHistory(history, historyCount);
                    break;
                case 7:
                    printf("\033[1;31m\n\nData berhasil disimpan. Program selesai.\033[0m\n\n");
                    break;
                default:
                    printf("\033[1;31m\n\nInput invalid, masukkan angka 1-7!!\033[0m\n\n");
                    break;
            }
        }
    } while (choice != 7);

    // Simpan data buku dan riwayat pembelian sebelum program berakhir
    saveBooks(books, bookCount);
    saveHistory(history, historyCount);

    return 0;
}

// Fungsi untuk membaca file databuku.txt
void loadBooks(Buku books[], int *count) {
    FILE *file = fopen("databuku.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        exit(1);
    }

    *count = 0;
    char line[256]; // Menyimpan setiap baris dari file
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Kode Buku: ", 11) == 0) {
            sscanf(line, "Kode Buku: %9s", books[*count].kode);
            fgets(line, sizeof(line), file); // Baca baris berikutnya (Nama)
            sscanf(line, "Nama: %99[^\n]", books[*count].nama);
            fgets(line, sizeof(line), file); // Baca baris berikutnya (Jenis)
            sscanf(line, "Jenis: %49[^\n]", books[*count].jenis);
            fgets(line, sizeof(line), file); // Baca baris berikutnya (Harga)
            sscanf(line, "Harga: %d", &books[*count].harga);
            (*count)++;
        }
    }

    fclose(file);
}

// Fungsi untuk menyimpan data buku
void saveBooks(Buku books[], int count) {
    FILE *file = fopen("databuku.txt", "w");
    if (file == NULL) {
        printf("File tidak bisa dibuka.");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "Kode Buku: %s\n", books[i].kode);
        fprintf(file, "Nama: %s\n", books[i].nama);
        fprintf(file, "Jenis: %s\n", books[i].jenis);
        fprintf(file, "Harga: %d\n\n", books[i].harga);
    }

    fclose(file);
}

// Fungsi untuk membaca file datapembelian.txt
void loadHistory(Pembelian history[], int *count) {
    FILE *file = fopen("datapembelian.txt", "r");
    if (file == NULL) {
        printf("File tidak bisa dibuka.");
        exit(1);
    }

    *count = 0;
    char line[256]; // Menyimpan setiap baris dari file
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Kode Pembelian: ", 16) == 0) {
            sscanf(line, "Kode Pembelian: %19s", history[*count].kodeUnik);
            fgets(line, sizeof(line), file); // Baca baris berikutnya (Kode Buku)
            sscanf(line, "Kode Buku: %9s", history[*count].kodeBuku);
            fgets(line, sizeof(line), file); // Baca baris berikutnya (Jumlah)
            sscanf(line, "Jumlah: %d", &history[*count].jumlah);
            fgets(line, sizeof(line), file); // Baca baris berikutnya (Total)
            sscanf(line, "Total: %d", &history[*count].total);
            (*count)++;
        }
    }

    fclose(file);
}

// Fungsi untuk menyimpan data pembelian
void saveHistory(Pembelian history[], int count) {
    FILE *file = fopen("datapembelian.txt", "w");
    if (file == NULL) {
        printf("File tidak dapat dibuka.");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "Kode Pembelian: %s\n", history[i].kodeUnik);
        fprintf(file, "Kode Buku: %s\n", history[i].kodeBuku);
        fprintf(file, "Jumlah: %d\n", history[i].jumlah);
        fprintf(file, "Total: %d\n\n", history[i].total);
    }

    fclose(file);
}

// Fungsi untuk menginput data buku
void inputBuku(Buku books[], int *count) {
    printf("\nMasukkan kode buku: ");
    scanf("%9s", books[*count].kode);
    // Membersihkan input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Masukkan nama buku: ");
    fgets(books[*count].nama, sizeof(books[*count].nama), stdin);
    books[*count].nama[strcspn(books[*count].nama, "\n")] = '\0';

    printf("Masukkan jenis buku: ");
    fgets(books[*count].jenis, sizeof(books[*count].jenis), stdin);
    books[*count].jenis[strcspn(books[*count].jenis, "\n")] = '\0';

    printf("Masukkan harga buku: ");
    scanf("%d", &books[*count].harga);

    (*count)++;

    printf("\e[0;32m\n\nBuku berhasil ditambahkan!\033[0m\n");
}

// Fungsi untuk menginput transaksi pembelian buku
void inputPembelian(Buku books[], int bookCount, Pembelian history[], int *historyCount) {
    char kodeBuku[10];
    int jumlah;
    int total = 0;

    // Mendapatkan waktu saat ini
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char kodePembelian[20]; // Kode pembelian akan berisi timestamp unik

    sprintf(kodePembelian, "%d-%02d-%02d-%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    // Menampilkan daftar buku yang tersedia
    printf("\nDaftar Buku yang Tersedia:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d. Kode Buku: %s, Nama: %s, Harga: %d\n", i + 1, books[i].kode, books[i].nama, books[i].harga);
    }

    // Meminta pengguna memasukkan kode buku
    printf("Masukkan kode buku yang ingin dibeli: ");
    scanf("%9s", kodeBuku);

    // Meminta pengguna memasukkan jumlah pembelian
    printf("Masukkan jumlah pembelian: ");
    scanf("%d", &jumlah);

    // Mencari buku yang sesuai dengan kode
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(kodeBuku, books[i].kode) == 0) {
            total = books[i].harga * jumlah;

            // Menyimpan data pembelian dengan kode pembelian yang unik
            strcpy(history[*historyCount].kodeUnik, kodePembelian);
            strcpy(history[*historyCount].kodeBuku, kodeBuku);
            history[*historyCount].jumlah = jumlah;
            history[*historyCount].total = total;
            (*historyCount)++;
            printf("\e[0;32m\n\nPembelian berhasil ditambahkan!\033[0m\n");
            return;
        }
    }

    // Jika kode buku tidak valid
    printf("\nKode buku tidak valid!\n");
}

// Fungsi untuk melihat riwayat pembelian
void viewHistory(Buku books[], Pembelian history[], int historyCount, int bookCount) {
    printf("\nData Pembelian:\n");
    for (int i = 0; i < historyCount; i++) {
        for (int j = 0; j < bookCount; j++) {
            if (strcmp(history[i].kodeBuku, books[j].kode) == 0) {
                printf("Kode pembelian: %s, Kode Buku: %s, Nama: %s, Jumlah: %d, Total: %d\n", history[i].kodeUnik, books[j].kode, books[j].nama, history[i].jumlah, history[i].total);
                break;
            }
        }
    }
}

// Fungsi untuk melihat data buku
void viewBooks(Buku books[], int bookCount) {
    printf("\nData Buku:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Kode Buku: %s\n", books[i].kode);
        printf("Nama: %s\n", books[i].nama);
        printf("Jenis: %s\n", books[i].jenis);
        printf("Harga: %d\n\n", books[i].harga);
    }
}

// Fungsi untuk menghapus history pembelian berdasarkan kode pembelian
void deleteHistory(Buku books[], Pembelian history[], int *historyCount, int *bookCount) {
    char kodePembelian[20];
    printf("List History Pembelian:\n");
    viewHistory(books, history, *historyCount, *bookCount);

    printf("Masukkan kode pembelian yang ingin dihapus: ");
    scanf("%19s", kodePembelian);

    for (int i = 0; i < *historyCount; i++) {
        if (strcmp(kodePembelian, history[i].kodeUnik) == 0) {
            // Memindahkan semua history pembelian setelah yang akan dihapus
            for (int j = i; j < *historyCount - 1; j++) {
                history[j] = history[j + 1];
            }
            (*historyCount)--;
            printf("\033[1;31m\n\nData berhasil dihapus.\033[0m\n\n");
            return;
        }
    }
    printf("\033[1;31m\n\nKode pembelian tidak ditemukan.\033[0m\n\n");
}

// Fungsi untuk menghapus data buku berdasarkan kode buku
void deleteBook(Buku books[], int *bookCount, Pembelian history[], int historyCount) {
    char kodeBuku[10];
    printf("\nList Data Buku:\n");
    viewBooks(books, *bookCount);

    printf("Masukkan kode buku yang ingin dihapus: ");
    scanf("%9s", kodeBuku);

    // Mengecek apakah buku yang akan dihapus sedang ada dalam riwayat pembelian
    for (int i = 0; i < historyCount; i++) {
        if (strcmp(kodeBuku, history[i].kodeBuku) == 0) {
            printf("\033[1;31m\n\nBuku ini telah dibeli, tidak dapat dihapus.\033[0m\n\n");
            return;
        }

        for (int i = 0; i < *bookCount; i++) {
            if (strcmp(kodeBuku, books[i].kode) == 0) {
                // Memindahkan semua buku setelah buku yang akan dihapus
                for (int j = i; j < *bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
                (*bookCount)--;
                printf("\033[1;31m\n\nData berhasil dihapus.\033[0m\n\n");
                return;
            }
        }
        printf("\033[1;31m\n\nKode buku tidak ditemukan.\033[0m\n\n");
    }
}
