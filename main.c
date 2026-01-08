#include <stdio.h>
#include <string.h>
#include "payroll/data.h"

struct karyawan k = {0};

int main() {
    while (1) {
        clear_screen();
        printf("=== Sistem Penggajian Karyawan ===\n");
        printf("1. Manajemen Karyawan\n");
        printf("2. Perhitungan Gaji\n");
        printf("3. Laporan Gaji\n");
        printf("4. Cetask Slip Gaji\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                karyawan(&k);
                break;
            case 2:
                // perhitungan_gaji();
                printf("Perhitungan Gaji dipilih.\n");
                break;
            case 3:
                // laporan_gaji();
                printf("Laporan Gaji dipilih.\n");
                break;
            case 4:
                // cetak_slip_gaji();
                printf("Cetak Slip Gaji dipilih.\n");
                break;
            case 0:
                printf("\nKeluar dari program.\n");
                return 0;
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
        }
    }
    
    return 0;
}