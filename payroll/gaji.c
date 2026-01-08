#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void gaji(struct gaji* g, struct karyawan* k) {
    while (1) {
        clear_screen();
        // Tampilkan informasi karyawan
        printf("=== Perhitungan Gaji Karyawan ===\n");
        printf("ID Karyawan     : %d\n", k->id);
        printf("Nama Karyawan   : %s\n", k->nama);
        printf("Jabatan         : %s\n", k->jabatan);
        printf("Status          : %s\n", k->status);
        printf("Gaji Pokok      : %d\n", k->gaji_pokok);
        printf("--------------------------------\n");
    
        // Input data gaji
        while (1) {
            printf("Masukkan Bulan (1-12)           : ");   
            scanf("%d", &g->bulan);
            if (g->bulan >= 1 && g->bulan <= 12) {
                break;
            }
        }
        printf("Masukkan Tahun                  : ");
        scanf("%d", &g->tahun);
        printf("Masukkan Hari Kerja             : ");
        scanf("%d", &g->hari_kerja);    
        printf("Masukkan Absen (Izin/Absen)     : ");
        scanf("%d", &g->absen);
        printf("Masukkan Tunjangan              : ");
        scanf("%d", &g->tunjangan);

        // Konfirmasi data
        printf("\nApakah data sudah benar? (y/n): ");
        char confirm;
        scanf(" %c", &confirm);
        if (confirm == 'n' || confirm == 'N') {
            continue; // ulangi input data
        }

        // Hitung potongan
        int potongan_per_hari = k->gaji_pokok / g->hari_kerja;
        g->potongan = g->absen * potongan_per_hari;

        // Hitung tunjangan
        if (strcmp(k->status, "Tetap") == 0) {
            g->tunjangan = k->gaji_pokok * 0.10;
        } else {
            g->tunjangan = 0;
        }

        // Hitung gaji bersih
        g->gaji_bersih = k->gaji_pokok + g->tunjangan - g->potongan;

        // Tampilkan hasil perhitungan
        printf("\n--- Rincian Gaji ---\n");
        printf("Gaji Pokok      : %d\n", k->gaji_pokok);
        printf("Tunjangan       : %d\n", g->tunjangan);
        printf("Potongan        : %d\n", g->potongan);
        printf("Gaji Bersih     : %d\n", g->gaji_bersih);
        printf("---------------------\n");

        fp_gaji = fopen("gaji.txt", "a");
        
        if (fp_gaji == NULL) {
            printf("Gagal membuka file gaji.txt untuk ditulis.\n");
            return;
        }

        fprintf(fp_gaji, "=============================\n");
        fprintf(fp_gaji, "ID Karyawan : %d\n", k->id);
        fprintf(fp_gaji, "Bulan       : %d\n", g->bulan);
        fprintf(fp_gaji, "Tahun       : %d\n", g->tahun);
        fprintf(fp_gaji, "Hari Kerja  : %d\n", g->hari_kerja);
        fprintf(fp_gaji, "Absen       : %d\n", g->absen);
        fprintf(fp_gaji, "Tunjangan   : %d\n", g->tunjangan);
        fprintf(fp_gaji, "Potongan    : %d\n", g->potongan);
        fprintf(fp_gaji, "Gaji Bersih : %d\n", g->gaji_bersih);
        fprintf(fp_gaji, "=============================\n\n");

        fclose(fp_gaji);

        printf("\nGaji telah dihitung dan disimpan ke file gaji.txt.\n");
        printf("Tekan Enter untuk kembali ke menu utama...");
        getchar(); getchar(); // wait for user input
        break;
    }
}