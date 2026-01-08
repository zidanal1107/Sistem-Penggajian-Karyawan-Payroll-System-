#include <stdio.h>
#include <string.h>
#include "data.h"

void laporan(struct karyawan* k,struct gaji* g) {
    int total_gaji;
    int jumlah_karyawan;
    int pengeluaran_gaji;
    clear_screen();
    printf("========= Laporan Gaji =========\n");
    printf("Total Gaji di Bulan     : %d\n", total_gaji);
    printf("Jumlah Karyawan         : %d\n", jumlah_karyawan);
    printf("Rekap Pengeluaran Gaji  : %d\n", pengeluaran_gaji);
    printf("================================\n");
}

void cetak_slip(struct karyawan* k,struct gaji* g) {

}