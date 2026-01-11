#ifndef PAYROLL_DATA_H
#define PAYROLL_DATA_H

// data karyawan
struct karyawan {
    int no;
    int id;            // PK
    char nama[50];
    char jabatan[30];
    char status[10];   // Tetap / Kontrak
    int gaji_pokok;
};

// data gaji karyawan
struct gaji {
    int id_karyawan;   // FK
    int tahun;
    int bulan;

    int hari_kerja;
    int absen;

    int tunjangan;
    int potongan;
    int gaji_bersih;
};

#define MAX 200
// untuk variable slip gaji
struct slip_gaji {
    int id[MAX];
    char bulan[MAX][20];
    int tahun[MAX];
    int hari_kerja[MAX];
    int absen[MAX];
    int tunjangan[MAX];
    int potongan[MAX];
    int gaji_bersih[MAX];
    char nama[MAX][50];
    char jabatan[MAX][30];
    char status[MAX][10];
    int gaji_pokok[MAX];
};

FILE *fp_karyawan; // file pointer untuk data karyawan
FILE *fp_gaji;     // file pointer untuk data gaji
FILE *fp_slip;    // file pointer untuk slip gaji
FILE *fp_laporan; // file pointer untuk laporan gaji

// fungsi untuk laporan
void laporan(struct slip_gaji* s);
void cetak_slip(struct slip_gaji* s);

// fungsi untuk mengelola data karyawan
void karyawan(struct karyawan* k);

// fungsi untuk menghitung gaji karyawan
void gaji(struct gaji* g, struct karyawan* k);

// fungsi untuk membersihkan layar
void clear_screen(void);

#endif
