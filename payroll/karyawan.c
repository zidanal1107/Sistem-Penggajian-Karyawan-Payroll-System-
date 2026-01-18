#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int get_no_terakhir() {
    fp_karyawan = fopen("karyawan.csv", "r");
    char line[256];
    int no = 0;

    if (fp_karyawan == NULL) return 1;

    // Lewati header
    fgets(line, sizeof(line), fp_karyawan);

    while (fgets(line, sizeof(line), fp_karyawan)) {
        sscanf(line, "%d;", &no);
    }

    fclose(fp_karyawan);
    return no + 1;
}


void karyawan(struct karyawan* k) {
    static int no_counter = 1; // Static counter for auto-incrementing 'no' field // Added static counter for 'no' field
    while (1) {
        clear_screen();
        // input data karyawan
        printf("======= Manajemen Karyawan =======\n");

        k->no = no_counter++; // Auto-increment 'no' field // Set 'no' to auto-incrementing counter

        printf("Masukkan ID Karyawan                    : ");
        scanf("%d", &k->id);

        printf("Masukkan Nama Karyawan                  : ");
        scanf(" %[^\n]", k->nama);
    
        printf("Masukkan Jabatan Karyawan               : ");
        scanf(" %[^\n]", k->jabatan);
        
        while (1) {
            printf("Masukkan Status Karyawan (Tetap/Kontrak): ");
            scanf(" %[^\n]", k->status);
            if (strcmp(k->status, "Tetap") != 0 && strcmp(k->status, "Kontrak") != 0) {
                printf("Status tidak valid. Harus 'Tetap' atau 'Kontrak'.\n");
                continue;
            } else {
                break;
            }
        }
        
        printf("Masukkan Gaji Pokok Karyawan            : ");
        scanf("%d", &k->gaji_pokok);
    
        // konfirmasi data
        printf("\n--- Rincian Karyawan ---\n");
        printf("ID          : %d\n", k->id);
        printf("Nama        : %s\n", k->nama);
        printf("Jabatan     : %s\n", k->jabatan);
        printf("Status      : %s\n", k->status);
        printf("Gaji Pokok  : %d\n", k->gaji_pokok);
        
        printf("\nApakah data sudah benar? (y/n): ");
        char confirm;
        scanf(" %c", &confirm);
        if (confirm == 'y' || confirm == 'Y') {
            /* AUTO INCREMENT NO */
            k->no = get_no_terakhir();

            fp_karyawan = fopen("karyawan.csv", "a");

            if (fp_karyawan == NULL) {
                printf("Gagal membuka file karyawan.csv untuk ditulis.\n");
                return;
            }

            fseek(fp_karyawan, 0, SEEK_END);
            long size = ftell(fp_karyawan);

            if (size == 0) {
                fprintf(fp_karyawan, "No;ID;Nama;Jabatan;Status;Gaji Pokok\n");
            }

            /* TULIS DATA */
            fprintf(fp_karyawan, "%d;%d;%s;%s;%s;%d\n",
                    k->no,
                    k->id,
                    k->nama,
                    k->jabatan,
                    k->status,
                    k->gaji_pokok);

            fclose(fp_karyawan);

            printf("\nData karyawan berhasil disimpan di karyawan.csv\n");
            printf("Tekan enter untuk lanjut...\n");
            getchar(); getchar(); // wait for user input
            break;
        }
    }
}