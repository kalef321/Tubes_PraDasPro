#include <stdio.h>
#include "hutang.h"

int main() {
    char nama[100], nim[20], jurusan[50];
    int UangSaku, opsi;

    catatanHutang daftar[10];
    int jumlahCatatan = 0;

    printf("+========================================+\n");
    printf("|       PROGRAM SURVIVE ANAK KOST        |\n");
    printf("+========================================+\n");

    printf("Nama                 : ");
    scanf(" %[^\n]", nama);
    printf("NIM                  : ");
    scanf("%s", nim);
    printf("Jurusan              : ");
    scanf(" %[^\n]", jurusan);
    printf("Uang Saku per-Minggu : ");
    scanf("%d", &UangSaku);

    do {
        printf("\n+==========================================+\n");
        printf("|              DATA ANAK KOST                |\n");
        printf("+============================================+\n");
        printf("| Nama     : %-29s |\n", nama);
        printf("| NIM      : %-29s |\n", nim);
        printf("| Jurusan  : %-29s |\n", jurusan);
        printf("| Uang Saku: Rp %-26d |\n", UangSaku);
        
        if (UangSaku >= 300000) {
            printf("| Status   : [CURIGA ANAK MANDIRI]           |\n");
        } else if (UangSaku >= 100000) {
            printf("| Status   : [MASIH SANGGUP SAYA MASIH SANGGUP]             |\n");
        } else {
            printf("| Status   : [LAMBUNG AMAN BOSS]          |\n");
        }
        printf("+==========================================+\n");

        printf("\n+==========================================+\n");
        printf("|           MENU UTAMA ANAK KOST           |\n");
        printf("+==========================================+\n");
        printf("| [1] Kelola Hutang Piutang                |\n");
        printf("| [0] Keluar                               |\n");
        printf("+==========================================+\n");
        printf("Pilihan Anda >> ");
        scanf("%d", &opsi);

        switch (opsi) {
            case 1:
                kelolaHutangPiutang(daftar, &jumlahCatatan);
                break;
            case 0:
                printf("\n[!] Terima Kasih Telah Menggunakan Program Ini.\n");
                break;
            default:
                printf("\n[!] Pilihan Tidak Valid. Silakan Coba Lagi.\n");
                break;
        }

    } while (opsi != 0);

    return 0;
}