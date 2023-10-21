#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_HISTORY 100

typedef struct {
    char kode[10];
    char nama[100];
    char jenis[50];
    int harga;
} Buku;

typedef struct {
    char kode[10];
    int jumlah;
    int total;
} Pembelian;

void loadBooks(Buku books[], int *count) {
    FILE *file = fopen("databuku.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open file.");
        exit(1);
    }

    *count = 0;
    while (fscanf(file, "Kode Buku: %9s", books[*count].kode) == 1) {
        fscanf(file, "Nama: %[^\n]s", books[*count].nama);
        fscanf(file, "Jenis: %[^\n]s", books[*count].jenis);
        fscanf(file, "Harga: %d", &books[*count].harga);
        (*count)++;
    }

    fclose(file);
}

void saveBooks(Buku books[], int count) {
    FILE *file = fopen("databuku.txt", "w");
    if (file == NULL) {
        printf("File tidak bisa dibuka.");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d.\nKode Buku: %s\n", i+1, books[i].kode);
        fprintf(file, "Nama: %s\n", books[i].nama);
        fprintf(file, "Jenis: %s\n", books[i].jenis);
        fprintf(file, "Harga: %d\n\n", books[i].harga);
    }

    fclose(file);
}

void loadHistory(Pembelian history[], int *count) {
    FILE *file = fopen("datapembelian.txt", "r");
    if (file == NULL) {
        printf("File tidak bisa dibuka.");
        exit(1);
    }

    *count = 0;
    while (fscanf(file, "Kode Buku: %9s", history[*count].kode) == 1) {
        fscanf(file, "Jumlah: %d", &history[*count].jumlah);
        fscanf(file, "Total: %d", &history[*count].total);
        (*count)++;
    }

    fclose(file);
}

void saveHistory(Pembelian history[], int count) {
    FILE *file = fopen("datapembelian.txt", "w");
    if (file == NULL) {
        printf("Error: Cannot open file.");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "Kode Buku: %s\n", history[i].kode);
        fprintf(file, "Jumlah: %d\n", history[i].jumlah);
        fprintf(file, "Total: %d\n\n", history[i].total);
    }

    fclose(file);
}

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
}

void viewHistory(Pembelian history[], int count) {
    printf("History Pembelian:\n");
    for (int i = 0; i < count; i++) {
        printf("Kode Buku: %s, Jumlah: %d, Total: %d\n", history[i].kode, history[i].jumlah, history[i].total);
    }
}

void viewBooks(Buku books[], int count) {
    printf("\nData Buku:\n");
    for (int i = 0; i < count; i++) {
        printf("%d.\nKode Buku: %s\n", i+1, books[i].kode);
        printf("Nama: %s\n", books[i].nama);
        printf("Jenis: %s\n", books[i].jenis);
        printf("Harga: %d\n\n", books[i].harga);
    }
}

void deleteHistory(Pembelian history[], int *count) {
    printf("List History Pembelian:\n");
    for (int i = 0; i < *count; i++) {
        printf("Kode Buku: %s, Jumlah: %d, Total: %d\n", history[i].kode, history[i].jumlah, history[i].total);
    }

    int index;
    printf("Masukkan index data yang ingin dihapus: ");
    scanf("%d", &index);

    if (index >= 1 && index <= *count) {
        for (int i = index - 1; i < *count - 1; i++) {
            history[i] = history[i + 1];
        }
        (*count)--;
        printf("Data berhasil dihapus.\n");
    } else {
        printf("Index tidak valid.\n");
    }
}

void deleteBook(Buku books[], int *count) {
    printf("\nList Data Buku:\n");
    for (int i = 0; i < *count; i++) {
        printf("%d.\nKode Buku: %s\n", i+1, books[i].kode);
        printf("Nama: %s\n", books[i].nama);
        printf("Jenis: %s\n", books[i].jenis);
        printf("Harga: %d\n\n", books[i].harga);
    }

    int index;
    printf("Masukkan index data yang ingin dihapus: ");
    scanf("%d", &index);

    if (index >= 1 && index <= *count) {
        for (int i = index - 1; i < *count - 1; i++) {
            books[i] = books[i + 1];
        }
        (*count)--;
        printf("Data berhasil dihapus.\n");
    } else {
        while (getchar() != '\n'); // Membersihkan input buffer
        printf("\033[1;31m\n\nIndex tidak valid.\033[0m\n");
    }
}

void viewPembelian(Buku books[], int bookCount, Pembelian history[], int historyCount) {
    printf("Data Pembelian:\n");
    for (int i = 0; i < historyCount; i++) {
        for (int j = 0; j < bookCount; j++) {
            if (strcmp(history[i].kode, books[j].kode) == 0) {
                                printf("Kode Buku: %s, Nama: %s, Jumlah: %d, Total: %d\n", books[j].kode, books[j].nama, history[i].jumlah, history[i].total);
                break;
            }
        }
    }
}

int main() {
    Buku books[MAX_BOOKS];
    Pembelian history[MAX_HISTORY];
    int bookCount = 0;
    int historyCount = 0;
    int choice;

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

        int extra = getchar();
        if (extra != '\n' && extra != EOF) {
            printf("\033[1;31m\n\nInput invalid, masukkan angka 1-7!!\033[0m\n\n");
            while (getchar() != '\n'); // Membersihkan input buffer
            continue;
        } else {
            switch (choice) {
                case 1:
                    inputBuku(books, &bookCount);
                    break;
                case 2:
                    viewHistory(history, historyCount);
                    break;
                case 3:
                    viewBooks(books, bookCount);
                    break;
                case 4:
                    deleteHistory(history, &historyCount);
                    break;
                case 5:
                    deleteBook(books, &bookCount);
                    break;
                case 6:
                    viewPembelian(books, bookCount, history, historyCount);
                    break;
                case 7:
                    saveBooks(books, bookCount);
                    saveHistory(history, historyCount);
                    printf("Data berhasil disimpan. Program selesai.\n");
                    break;
                default:
                    printf("\033[1;31m\n\nInput invalid, masukkan angka 1-7!!\033[0m\n\n");
                    break;
            }
        }
    } while (choice != 7);

    return 0;
}

