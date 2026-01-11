#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void gaji(struct gaji* g, struct karyawan* k) {
    while (1) {
        clear_screen();
        if (!k->id) {
            printf("Belum ada data karyawan\n");
            getchar(); getchar();
            return;
        } else {
            // Tampilkan informasi karyawan
            printf("=== Perhitungan Gaji Karyawan ===\n");
            printf("ID Karyawan     : %d\n", k->id);
            printf("Nama Karyawan   : %s\n", k->nama);
            printf("Jabatan         : %s\n", k->jabatan);
            printf("Status          : %s\n", k->status);
            printf("Gaji Pokok      : %d\n", k->gaji_pokok);
            printf("--------------------------------\n");
        }
    
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
        if (g->hari_kerja <= 0) {
            printf("Hari kerja harus lebih dari 0.\n");
            continue; // ulangi input
        }
        printf("Masukkan Absen (Izin/Absen)     : ");
        scanf("%d", &g->absen);
        // Tunjangan dihitung berdasarkan status, tidak perlu input // Removed redundant tunjangan input as it's calculated based on status

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

        char nama_bulan[12][20] = {"Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"};

        fp_gaji = fopen("gaji.csv", "a");

        fseek(fp_gaji, 0, SEEK_END);
        long size = ftell(fp_gaji);
        if (size == 0) {
            fprintf(fp_gaji, "ID;Bulan;Tahun;Hari Kerja;Absen;Tunjangan;Potongan;Gaji Bersih\n");
        }
        
        if (fp_gaji == NULL) {
            printf("Gagal membuka file gaji.csv untuk ditulis.\n");
            return;
        }

        // tulis di file gaji.csv
        fprintf(fp_gaji, "%d;%s;%d;%d;%d;%d;%d;%d\n", 
            k->id,nama_bulan[g->bulan -1],g->tahun,g->hari_kerja,g->absen,g->tunjangan,g->potongan,g->gaji_bersih);

        fclose(fp_gaji);

        printf("\nGaji telah dihitung dan disimpan ke file gaji.csv.\n"); // Fixed message to match actual file extension
        printf("Tekan Enter untuk kembali ke menu utama...");
        getchar(); getchar(); // wait for user input
        break;
    }
}