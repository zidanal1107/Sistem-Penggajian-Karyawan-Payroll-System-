#include <stdio.h>
#include <string.h>
#include "data.h"

void laporan(struct slip_gaji* s) {
    int total_gaji = 0;
    fp_gaji = fopen("gaji.txt", "r");
    if (!fp_gaji) {
        printf("\nTidak dapat membuka file gaji.txt\n");
        getchar(); getchar();
        return;
    }
    char line[200];
    int jml_id = 0;
    while (fgets(line, sizeof(line), fp_gaji)) {

        if (sscanf(line, "ID Karyawan : %d", &s->id[jml_id]) == 1) {

            fgets(line, sizeof(line), fp_gaji);
            sscanf(line, "Bulan       : %19[^\n]", s->bulan[jml_id]);

            fgets(line, sizeof(line), fp_gaji);
            sscanf(line, "Tahun       : %d", &s->tahun[jml_id]);

            fgets(line, sizeof(line), fp_gaji);
            sscanf(line, "Hari Kerja  : %d", &s->hari_kerja[jml_id]);

            fgets(line, sizeof(line), fp_gaji);
            sscanf(line, "Absen       : %d", &s->absen[jml_id]);

            fgets(line, sizeof(line), fp_gaji);
            sscanf(line, "Tunjangan   : %d", &s->tunjangan[jml_id]);

            fgets(line, sizeof(line), fp_gaji);
            sscanf(line, "Potongan    : %d", &s->potongan[jml_id]);

            fgets(line, sizeof(line), fp_gaji);
            sscanf(line, "Gaji Bersih : %d", &s->gaji_bersih[jml_id]);

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

    printf("Tekan enter untuk kembali ke menu...");
    getchar(); getchar();
}

void cetak_slip(struct slip_gaji* s) {
    int i, pilih;
    char line[200];
    int jml_id = 0;

    fp_karyawan = fopen("karyawan.txt", "r");
    if (!fp_karyawan) {
        printf("\nTidak dapat membuka file karyawan.");
        getchar(); getchar();
        return;
    }

    /* === BACA DATA KARYAWAN === */
    while (fgets(line, sizeof(line), fp_karyawan)) {

        if (sscanf(line, "ID        : %d", &s->id[jml_id]) == 1) {

            fgets(line, sizeof(line), fp_karyawan);
            sscanf(line, "Nama      : %49[^\n]", s->nama[jml_id]);

            fgets(line, sizeof(line), fp_karyawan);
            sscanf(line, "Jabatan   : %29[^\n]", s->jabatan[jml_id]);

            fgets(line, sizeof(line), fp_karyawan);
            sscanf(line, "Status    : %9[^\n]", s->status[jml_id]);

            fgets(line, sizeof(line), fp_karyawan);
            sscanf(line, "Gaji Pokok: %d", &s->gaji_pokok[jml_id]);

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

    fp_slip = fopen("slip_gaji.txt", "w");
    if (!fp_slip) {
        printf("Gagal membuka slip_gaji.txt\n");
        getchar(); getchar();
        return;
    }

    int idx = pilih - 1;

    fprintf(fp_slip, "=============================\n");
    fprintf(fp_slip, "SLIP GAJI KARYAWAN\n");
    fprintf(fp_slip, "-----------------------------\n");
    fprintf(fp_slip, "Nama          : %s\n", s->nama[idx]);
    fprintf(fp_slip, "ID            : %d\n", s->id[idx]);
    fprintf(fp_slip, "Jabatan       : %s\n", s->jabatan[idx]);
    fprintf(fp_slip, "Status        : %s\n", s->status[idx]);
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
