#ifndef PAYROLL_DATA_H
#define PAYROLL_DATA_H

// data karyawan
struct karyawan {
    int id;            // PK
    char nama[50];
    char jabatan[30];
    char status[10];   // Tetap / Kontrak
    int gaji_pokok;
};

// data gaji karyawan
struct gaji {
    int id_karyawan;   // FK
    int bulan;
    int tahun;

    int hari_kerja;
    int absen;

    int tunjangan;
    int potongan;
    int gaji_bersih;
};

// fungsi untuk mengelola data karyawan
void karyawan(struct karyawan* k);

// fungsi untuk membersihkan layar
void clear_screen(void);

#endif