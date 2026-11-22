#include <stdio.h>
#include <stdlib.h>  // library untuk fungsi rand() dan srand()
#include <time.h>   // library untuk fungsi time() agar angka random berbeda setiap kali program dijalankan

void rekomendasimakanan(float saldosaatini){
    char menuHemat[5][30] = {
        
        "Nasi Goreng",
        "Mie Goreng",
        "Ayam Geprek",
        "Bakso",
        "Sate"
    };

    printf("====================================\n");
    printf("|  REKOMENDASI SURVIVAL ANAK KOST|  \n");
    printf("====================================\n");

    printf("saldo saat ini: Rp %.2f\n", saldosaatini);

    printf("Berikut adalah rekomendasi makanan hemat untuk anak kost:\n");
    if(saldosaatini > 500000){
        printf("Cafe atau restoran mewah\n");
        printf("Sushi/Ramen\n");
        printf("status:orkay nie boss!\n");
    }
    else if(saldosaatini >=30000 && saldosaatini <= 100000){
        printf("Nasi Goreng\n");
        printf("Nasi padang\n");
        printf("Ayam Geprek/ Gemas\n");
        printf("Bakso\n");
    }
    else {
        printf("Mie Instan\n");
        printf("Telur Rebus\n");
        printf("warteg/angkringan\n");
        printf("status: mode survival on\n\n");
    }

    int randomIndex = rand() % 5; // Menghasilkan indeks acak antara 0 hingga 4
    printf(" GACHA MENU HARI INI: \n");
    printf(" ===============================\n");
    printf(" |Menu Acak : %-22s  |\n", menuHemat[randomIndex]);
    printf(" ===============================\n");
    printf("Selamat menikmati menu rekomendasi hari ini!\n");

    
}
int main(){
        srand(time(0)); // Inisialisasi seed untuk fungsi rand()

        float saldo = 800000;

        rekomendasimakanan(saldo);
        return 0;
    }