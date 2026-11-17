#ifndef HUTANG_H
#define HUTANG_H

#include <stdio.h>

typedef struct {
    char nama[50];
    int jumlah;
    int tipe; // 1 = hutang, 2 = piutang
    int status; // 1 = lunas, 0 = belum
} catatanHutang;

void kelolaHutangPiutang(catatanHutang daftar[], int *jumlahCatatan);

void kelolaHutangPiutang(catatanHutang daftar[], int *jumlahCatatan){
    int pilihan;

    do{
        printf("\n+========================================+\n");
        printf("|          KELOLA HUTANG PIUTANG         |\n");
        printf("+========================================+\n");
        printf("|[1] Tambah Catatan Hutang/Piutang       |\n");
        printf("|[2] Lihat Daftar & Ringkasan Tanggungan |\n");
        printf("|[3] Tandai Lunas                        |\n");
        printf("|[0] Kembali ke Menu Utama               |\n");
        printf("+========================================+\n");
        printf("Pilihan Anda >> ");
        scanf("%d", &pilihan);

        if(pilihan == 1){
            if(*jumlahCatatan >= 10){
                printf("\n[!] Kapasitas Penyimpanan Penuh (Maksimal 10 Catatan).\n");
            }else{
                printf("\n-----TAMBAH CATATAN BARU-----\n");
                printf("Nama\t:");
                scanf(" %49[^\n]", daftar[*jumlahCatatan].nama);
                printf("Nominal\t:");
                scanf("%d", &daftar[*jumlahCatatan].jumlah);
                printf("Tipe (1 = Hutang, 2 = Piutang)\t:");
                scanf("%d", &daftar[*jumlahCatatan].tipe);
                daftar[*jumlahCatatan].status = 0;
                (*jumlahCatatan)++;

                printf("\n[OK] Berhasil Menambahkan Catatan\n");
            }
        }else if(pilihan == 2){
            if(*jumlahCatatan == 0){
                printf("\n[!] Belum Ada Catatan Hutang Piutang\n");
            }else{
                int totalHutang = 0;
                int totalPiutang = 0;

                printf("\n+============================================+\n");
                printf("|           DAFTAR HUTANG PIUTANG            |\n");
                printf("+============================================+\n");
                printf("+--+----------------+---------+-------+------+\n");
                printf("|No|Nama            |Jumlah   |Tipe   |Status|\n");
                printf("+--+----------------+---------+-------+------+\n");

                for(int i = 0; i < *jumlahCatatan; i++){
                    char *labelTipe = (daftar[i].tipe == 1) ? "Hutang" : "Piutang";
                    char *labelStatus = (daftar[i].status == 1) ? "Lunas" : "Belum";

                    printf("|%-2d|%-16s|%-9d|%-7s|%-6s|\n", i+1, daftar[i].nama, daftar[i].jumlah, labelTipe, labelStatus);

                    if(daftar[i].status == 0){
                        if(daftar[i].tipe == 1){
                            totalHutang += daftar[i].jumlah;
                        }else{
                        totalPiutang += daftar[i].jumlah;
                        }
                    }
                }
                printf("+--+----------------+---------+-------+------+\n");

                printf("\nRINGKASAN TANGGUNGAN (BELUM LUNAS)\n");
                printf("- Hutang Kamu ke Orang Lain\t: %d\n", totalHutang);
                printf("- Piutang Orang Lain ke Kamu\t: %d\n", totalPiutang);
                if(totalHutang > totalPiutang){
                    printf("Status: Hutang lebih besar, jangan lupa dibayar yawww\n");
                }else if(totalHutang < totalPiutang){
                    printf("Status: Piutang lebih besar, jangan lupa ditagih yawww\n");
                }else{
                    printf("Status: Hutang dan Piutang Seimbang\n");
                }
            }
        }else if(pilihan == 3){
            if(*jumlahCatatan == 0){
                printf("\n[!] Tidak Ada Catatan Hutang Piutang\n");
            }else{
                int nomor;
                printf("\nMasukkan Nomor Catatan yang Sudah Lunas (1 - %d): ", *jumlahCatatan);
                scanf("%d", &nomor);

                int idx = nomor - 1;
                if(idx >= 0 && idx < *jumlahCatatan){
                    if(daftar[idx].status == 1){
                        printf("\n[!] Catatan Tersebut Memang Sudah Lunas\n");
                    }else{
                        daftar[idx].status = 1;
                        char *tipe = (daftar[idx].tipe == 1) ? "Hutang ke" : "Piutang dari";
                        printf("\n[OK] %s \"%s\" Rp %d Sudah Lunas!\n", tipe, daftar[idx].nama, daftar[idx].jumlah);
                    }
                }else{
                    printf("\n[!] Nomor Catatan Tidak Valid!\n");
                }
            }
        }else if(pilihan != 0){
            printf("\n[!] Pilihan Tersebut Tidak Valid!\n");
        }
    }while(pilihan != 0);
}
#endif