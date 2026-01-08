#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void karyawan(struct karyawan* k) {
    while (1) {
        clear_screen();
        // input data karyawan
        printf("======= Manajemen Karyawan =======\n");
    
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
            fp_karyawan = fopen("karyawan.txt", "a");
            if (fp_karyawan == NULL) {
                printf("Gagal membuka file karyawan.txt untuk ditulis.\n");
                return;
            }

            // tulis di file karyawan.txt
            fprintf(fp_karyawan, "ID        : %d\n", k->id);
            fprintf(fp_karyawan, "Nama      : %s\n", k->nama);
            fprintf(fp_karyawan, "Jabatan   : %s\n", k->jabatan);
            fprintf(fp_karyawan, "Status    : %s\n", k->status);
            fprintf(fp_karyawan, "Gaji Pokok: %d\n\n", k->gaji_pokok);

            fclose(fp_karyawan);

            printf("\nData karyawan berhasil disimpan di karyawan.txt\n");
            printf("Tekan enter untuk lanjut...\n");
            getchar(); getchar(); // wait for user input
            break;
        }
    }
}