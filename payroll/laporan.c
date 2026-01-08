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

    printf("========= Laporan Gaji =========\n");

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
    }

    printf("================================\n");

    printf("Tekan enter untuk kembali ke menu...");
    getchar(); getchar();
}

void cetak_slip(struct karyawan* k,struct gaji* g,struct slip_gaji* s) {

}