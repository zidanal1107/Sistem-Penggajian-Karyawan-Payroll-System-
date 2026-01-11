#include <stdio.h>
#include <string.h>
#include "data.h"

void laporan(struct slip_gaji* s) {
    int total_gaji = 0;
    fp_gaji = fopen("gaji.csv", "r");
    if (!fp_gaji) {
        printf("\nTidak dapat membuka file gaji.csv\n");
        getchar(); getchar();
        return;
    }

    char line[200];
    int jml_id = 0;
    total_gaji = 0;

    /* skip header */
    fgets(line, sizeof(line), fp_gaji);

    while (fgets(line, sizeof(line), fp_gaji)) {

        if (sscanf(line,
            "%d;%19[^;];%d;%d;%d;%d;%d;%d",
            &s->id[jml_id],
            s->bulan[jml_id],
            &s->tahun[jml_id],
            &s->hari_kerja[jml_id],
            &s->absen[jml_id],
            &s->tunjangan[jml_id],
            &s->potongan[jml_id],
            &s->gaji_bersih[jml_id]) == 8)
        {
            total_gaji += s->gaji_bersih[jml_id];
            jml_id++;
        }
    }

    fclose(fp_gaji);
    clear_screen();

    int i, j;
    int sudah[MAX] = {0};

    printf("--------- Laporan Gaji ---------\n");

    for (i = 0; i < jml_id; i++) {
        if (sudah[i]) continue;

        int total = s->gaji_bersih[i];
        int jumlah = 1;

        for (j = i + 1; j < jml_id; j++) {
            if (strcmp(s->bulan[i], s->bulan[j]) == 0) {
                total += s->gaji_bersih[j];
                jumlah++;
                sudah[j] = 1;
            }
        }

        printf("Bulan                   : %s\n", s->bulan[i]);
        printf("Jumlah Karyawan         : %d\n", jumlah);
        printf("Rekap Pengeluaran Gaji  : %d\n", total);
        printf("--------------------------------\n");
    }

    fp_laporan = fopen("laporan.csv", "a");

    fseek(fp_laporan, 0, SEEK_END); // Fixed fseek to use fp_laporan // Fixed fseek to use correct file pointer
    long size = ftell(fp_laporan);
    if (size == 0) {
        fprintf(fp_laporan, "Bulan;Jumlah;total\n"); // Fixed fprintf to use fp_laporan // Fixed fprintf to use correct file pointer
    }

    for (i = 0; i < jml_id; i++) {
        if (sudah[i]) continue;

        int total = s->gaji_bersih[i];
        int jumlah = 1;

        for (j = i + 1; j < jml_id; j++) {
            if (strcmp(s->bulan[i], s->bulan[j]) == 0) {
                total += s->gaji_bersih[j];
                jumlah++;
                sudah[j] = 1;
            }
        }

        fprintf(fp_laporan ,"%s;%d;%d\n", s->bulan[i], jumlah,total);
    }
    fclose(fp_laporan);

    printf("Tekan enter untuk kembali ke menu...");
    getchar(); getchar();
}

void cetak_slip(struct slip_gaji* s) {
    int i, pilih;
    char line[200];
    int jml_id = 0;

    fp_karyawan = fopen("karyawan.csv", "r"); // Changed to open karyawan.csv // Changed file from karyawan.txt to karyawan.csv
    if (!fp_karyawan) {
        printf("\nTidak dapat membuka file karyawan.csv"); // Updated error message // Updated error message to match file
        getchar(); getchar();
        return;
    }

    /* === BACA DATA KARYAWAN === */
    fgets(line, sizeof(line), fp_karyawan); // skip header
    while (fgets(line, sizeof(line), fp_karyawan)) {
        if (sscanf(line, "%d;%d;%49[^;];%29[^;];%9[^;];%d",
            &s->id[jml_id], // no field, but we don't need it
            &s->id[jml_id],
            s->nama[jml_id],
            s->jabatan[jml_id],
            s->status[jml_id],
            &s->gaji_pokok[jml_id]) == 6) {
            jml_id++;
        }
    }
    fclose(fp_karyawan);

    if (jml_id == 0) {
        printf("Data karyawan kosong.\n");
        getchar(); getchar();
        return;
    }

    /* === PILIH KARYAWAN === */
    while (1) {
        clear_screen();
        printf("=== Cetak Slip Gaji ===\n");
        for (i = 0; i < jml_id; i++) {
            printf("%d. %s (ID: %d)\n", i + 1, s->nama[i], s->id[i]);
        }

        printf("Pilih nomor karyawan: ");
        if (scanf("%d", &pilih) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (pilih <= 0 || pilih > jml_id) {
            printf("Pilihan tidak ada.\n");
            getchar(); getchar();
        } else {
            break;
        }
    }

    int idx = pilih - 1; // Declare idx here // Declare idx before using in gaji reading

    // Read gaji.csv to populate gaji fields for the selected karyawan
    fp_gaji = fopen("gaji.csv", "r");
    if (!fp_gaji) {
        printf("Gagal membuka gaji.csv\n");
        getchar(); getchar();
        return;
    }
    fgets(line, sizeof(line), fp_gaji); // skip header
    int found = 0;
    while (fgets(line, sizeof(line), fp_gaji)) {
        int temp_id, temp_tahun, temp_hari_kerja, temp_absen, temp_tunjangan, temp_potongan, temp_gaji_bersih;
        char temp_bulan[20];
        if (sscanf(line, "%d;%19[^;];%d;%d;%d;%d;%d;%d",
            &temp_id, temp_bulan, &temp_tahun, &temp_hari_kerja, &temp_absen,
            &temp_tunjangan, &temp_potongan, &temp_gaji_bersih) == 8) {
            if (temp_id == s->id[idx]) {
                // Take the last entry (overwrite previous)
                strcpy(s->bulan[idx], temp_bulan);
                s->tahun[idx] = temp_tahun;
                s->hari_kerja[idx] = temp_hari_kerja;
                s->absen[idx] = temp_absen;
                s->tunjangan[idx] = temp_tunjangan;
                s->potongan[idx] = temp_potongan;
                s->gaji_bersih[idx] = temp_gaji_bersih;
                found = 1;
            }
        }
    }
    fclose(fp_gaji);
    if (!found) {
        printf("Data gaji untuk karyawan ini tidak ditemukan.\n");
        getchar(); getchar();
        return;
    }

    fp_slip = fopen("slip_gaji.txt", "w");
    if (!fp_slip) {
        printf("Gagal membuka slip_gaji.txt\n");
        getchar(); getchar();
        return;
    }

    fprintf(fp_slip, "=============================\n");
    fprintf(fp_slip, "SLIP GAJI KARYAWAN\n");
    fprintf(fp_slip, "-----------------------------\n");
    fprintf(fp_slip, "Nama          : %s\n", s->nama[idx]);
    fprintf(fp_slip, "ID            : %d\n", s->id[idx]);
    fprintf(fp_slip, "Jabatan       : %s\n", s->jabatan[idx]);
    fprintf(fp_slip, "Status        : %s\n", s->status[idx]);
    fprintf(fp_slip, "Bulan         : %s\n", s->bulan[idx]); // Added bulan to slip // Added bulan field to slip gaji
    fprintf(fp_slip, "Tahun         : %d\n", s->tahun[idx]); // Added tahun to slip // Added tahun field to slip gaji
    fprintf(fp_slip, "Gaji Pokok    : %d\n", s->gaji_pokok[idx]);
    fprintf(fp_slip, "Tunjangan     : %d\n", s->tunjangan[idx]);
    fprintf(fp_slip, "Potongan      : %d\n", s->potongan[idx]);
    fprintf(fp_slip, "-----------------------------\n");
    fprintf(fp_slip, "Gaji Bersih   : %d\n", s->gaji_bersih[idx]);
    fprintf(fp_slip, "=============================\n\n");

    fclose(fp_slip);

    printf("\nSlip gaji berhasil dicetak.\n");
    printf("Tekan enter untuk kembali...");
    getchar(); getchar();
}
