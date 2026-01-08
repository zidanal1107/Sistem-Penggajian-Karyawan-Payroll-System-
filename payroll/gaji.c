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
            printf("Masukkan Bulan (1-12)   : ");   
            scanf("%d", &g->bulan);
            if (g->bulan >= 1 && g->bulan <= 12) {
                break;
            }
        }
        printf("Masukkan Tahun          : ");
        scanf("%d", &g->tahun);
        printf("Masukkan Hari Kerja     : ");
        scanf("%d", &g->hari_kerja);
        printf("Masukkan Absen          : ");
        scanf("%d", &g->absen);
        printf("Masukkan Tunjangan      : ");
        scanf("%d", &g->tunjangan);
        printf("Masukkan Potongan       : ");
        scanf("%d", &g->potongan);

        // Konfirmasi data
        printf("\nApakah data sudah benar? (y/n): ");
        char confirm;
        scanf(" %c", &confirm);
        if (confirm == 'n' || confirm == 'N') {
            continue; // ulangi input data
        }

        // Hitung potongan
        int potongan_per_hari = k->gaji_pokok / 22;
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
        printf("Tekan Enter untuk kembali ke menu utama...");
        getchar(); getchar(); // wait for user input
        break;
    }
}