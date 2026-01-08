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

FILE *fp_karyawan; // file pointer untuk data karyawan
FILE *fp_gaji;     // file pointer untuk data gaji
FILE *fp_slip;    // file pointer untuk slip gaji
FILE *fp_laporan; // file pointer untuk laporan gaji

// fungsi untuk laporan
void laporan(struct karyawan* k,struct gaji* g);
void cetak_slip(struct karyawan* k,struct gaji* g);

// fungsi untuk mengelola data karyawan
void karyawan(struct karyawan* k);

// fungsi untuk menghitung gaji karyawan
void gaji(struct gaji* g, struct karyawan* k);

// fungsi untuk membersihkan layar
void clear_screen(void);

#endif