/*
 * ============================================================
 *  PROGRAM SURVIVAL ANAK KOST
 * ============================================================
 *  Deskripsi : Program modular Bahasa C untuk membantu
 *              kehidupan sehari-hari anak kost, mencakup
 *              pengelolaan keuangan, to-do list, dan
 *              rekomendasi survival.
 *
 *  Konsep C  : Fungsi (Pass-by-Value & Pass-by-Reference),
 *              Array 1D, Array 2D String, Looping (for,
 *              do-while, while), Percabangan (if-else,
 *              switch-case), Pointer, Tipe Data (int, float,
 *              char array/string).
 *
 *  Compiler  : GCC / MinGW (C99/C11)
 *              Compile: gcc -o survival survival_anak_kost.c
 * ============================================================
 */

#include <stdio.h>   // scanf, printf, fgets, getchar
#include <stdlib.h>  // rand(), srand(), system()
#include <string.h>  // strlen(), strcspn()
#include <time.h>    // time() untuk seed random

/* ============================================================
 *  KONSTANTA GLOBAL
 * ============================================================ */
#define MAX_TUGAS       5    // Kapasitas maksimal to-do list
#define MAX_LEN_TUGAS   100  // Panjang maksimal string tugas
#define MAX_LEN_NAMA    50   // Panjang maksimal nama
#define MAX_LEN_NIM     20   // Panjang maksimal NIM
#define HARI            7    // Jumlah hari dalam seminggu

/* ============================================================
 *  DEKLARASI PROTOTIPE FUNGSI (FUNCTION PROTOTYPES)
 * ============================================================ */

// Fungsi utilitas
void tampilkanBanner(void);
void tampilkanMenuUtama(void);
void bersihkanBuffer(void);

// Fungsi inisialisasi data diri  -- Pass-by-Reference (Pointer)
void inputDataDiri(char *nama, char *nim, float *saldo);

// Fitur 1: Kelola Keuangan      -- Array 1D + Pointer
void kelolaKeuangan(float pengeluaran[], float *saldoUtama);

// Fitur 2: To-Do List            -- Array 2D String + Pointer
void toDoList(char listTugas[][MAX_LEN_TUGAS], int statusTugas[], int *jumlahTugas);
void lihatDaftarTugas(char listTugas[][MAX_LEN_TUGAS], int statusTugas[], int jumlahTugas);
void tambahUbahTugas(char listTugas[][MAX_LEN_TUGAS], int statusTugas[], int *jumlahTugas);
void tandaiSelesai(int *status);  // Pass-by-Reference (Pointer) untuk update status

// Fitur 3: Rekomendasi Survival  -- Pass-by-Value
void sarankanSurvival(float saldoSaatIni);
void rekomendasiTempatMakan(float saldo);     // Percabangan if-else
void gachaMenuMakan(void);                    // Array 2D String lokal + rand()

// Fitur 4: Keluar
void tampilkanPenutup(char *nama);

/* ============================================================
 *  FUNGSI MAIN
 * ============================================================
 *  Konsep: do-while loop, switch-case, variabel lokal utama
 * ============================================================ */
int main(void)
{
    /* --- Variabel utama di main() --- */
    char nama[MAX_LEN_NAMA];                          // Array Char 1D : Nama penghuni
    char nim[MAX_LEN_NIM];                             // Array Char 1D : NIM
    float saldo = 0.0f;                                // Saldo/uang saku (akan diisi via pointer)

    float pengeluaran[HARI] = {0};                     // Array 1D float : pengeluaran 7 hari
    char listTugas[MAX_TUGAS][MAX_LEN_TUGAS] = {""};  // Array 2D String : daftar tugas
    int statusTugas[MAX_TUGAS] = {0};                  // Array 1D int   : status tugas (0/1)
    int jumlahTugas = 0;                               // Counter tugas yang terisi

    int pilihan;                                       // Pilihan menu utama

    /* --- Seed random number generator --- */
    srand((unsigned int)time(NULL));

    /* --- Tampilkan banner & input data diri --- */
    tampilkanBanner();

    // Memanggil fungsi dengan POINTER agar data terisi langsung di main()
    // Konsep: Pass-by-Reference menggunakan Pointer
    inputDataDiri(nama, nim, &saldo);

    /* --- Menu Utama: do-while loop --- */
    // Konsep: Perulangan do-while memastikan menu ditampilkan minimal 1 kali
    do {
        tampilkanMenuUtama();
        printf("  Pilihan Anda >> ");
        scanf("%d", &pilihan);
        bersihkanBuffer(); // Membersihkan buffer '\n' setelah scanf

        // Konsep: switch-case untuk percabangan menu
        switch (pilihan)
        {
            case 1:
                /* Fitur 1: Kelola Keuangan Mingguan */
                // Pass Array 1D (pengeluaran) dan Pointer ke saldo
                kelolaKeuangan(pengeluaran, &saldo);
                break;

            case 2:
                /* Fitur 2: To-Do List Harian / Mingguan */
                // Pass Array 2D String (listTugas), Array status, dan pointer jumlahTugas
                toDoList(listTugas, statusTugas, &jumlahTugas);
                break;

            case 3:
                /* Fitur 3: Rekomendasi Survival */
                // Pass-by-Value: hanya mengirim salinan nilai saldo
                sarankanSurvival(saldo);
                break;

            case 4:
                /* Fitur 4: Keluar dari program */
                tampilkanPenutup(nama);
                break;

            default:
                printf("\n  [!] Pilihan tidak valid! Silakan masukkan angka 1-4.\n");
                break;
        }

    } while (pilihan != 4);
    // Loop berhenti ketika user memilih 4 (Keluar)

    return 0;
}

/* ============================================================
 *  IMPLEMENTASI FUNGSI-FUNGSI
 * ============================================================ */

/* ----------------------------------------------------------
 *  tampilkanBanner()
 *  Konsep: Fungsi void tanpa parameter, mencetak teks ASCII
 * ---------------------------------------------------------- */
void tampilkanBanner(void)
{
    printf("\n");
    printf("  +=========================================================+\n");
    printf("  |                                                         |\n");
    printf("  |    ____  _   _ ______     _____ __     __ _____         |\n");
    printf("  |   / ___|| | | |  _ \\ \\   / /_ _|\\ \\   / /| ____|  |\n");
    printf("  |   \\___ \\| | | | |_) \\ \\ / / | |  \\ \\ / / |  _|    |\n");
    printf("  |    ___) | |_| |  _ < \\ V /  | |   \\ V /  | |___      |\n");
    printf("  |   |____/ \\___/|_| \\_\\ \\_/  |___|   \\_/   |_____|  |\n");
    printf("  |                                                         |\n");
    printf("  |        P R O G R A M   S U R V I V A L                 |\n");
    printf("  |            A N A K   K O S T                            |\n");
    printf("  |                                                         |\n");
    printf("  |   \"Bertahan hidup itu seni, apalagi di kost!\"           |\n");
    printf("  |                                                         |\n");
    printf("  +=========================================================+\n");
    printf("\n");
}

/* ----------------------------------------------------------
 *  tampilkanMenuUtama()
 *  Konsep: Fungsi void, mencetak pilihan menu
 * ---------------------------------------------------------- */
void tampilkanMenuUtama(void)
{
    printf("\n");
    printf("  +--------------------------------------+\n");
    printf("  |         M E N U   U T A M A          |\n");
    printf("  +--------------------------------------+\n");
    printf("  |  [1] Kelola Keuangan Mingguan        |\n");
    printf("  |  [2] To-Do List Harian / Mingguan    |\n");
    printf("  |  [3] Rekomendasi Survival Anak Kost  |\n");
    printf("  |  [4] Keluar dari Program             |\n");
    printf("  +--------------------------------------+\n");
}

/* ----------------------------------------------------------
 *  bersihkanBuffer()
 *  Konsep: Membersihkan sisa karakter di input buffer
 *          agar fgets / scanf berikutnya tidak ter-skip.
 *          Menggunakan while loop dan getchar().
 * ---------------------------------------------------------- */
void bersihkanBuffer(void)
{
    int c;
    // While loop: baca karakter satu per satu sampai '\n' atau EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ----------------------------------------------------------
 *  inputDataDiri()
 *  Konsep: Pass-by-Reference menggunakan POINTER
 *          - Parameter `nama` dan `nim` sudah berupa pointer
 *            (nama array = alamat elemen pertama).
 *          - Parameter `saldo` menggunakan pointer `float *`
 *            agar nilai di main() langsung berubah.
 * ---------------------------------------------------------- */
void inputDataDiri(char *nama, char *nim, float *saldo)
{
    printf("  ======================================\n");
    printf("       INPUT DATA DIRI PENGHUNI\n");
    printf("  ======================================\n\n");

    // Input nama menggunakan fgets (aman untuk string dengan spasi)
    printf("  Nama Penghuni   : ");
    fgets(nama, MAX_LEN_NAMA, stdin);
    // Hapus karakter newline '\n' di akhir string hasil fgets
    nama[strcspn(nama, "\n")] = '\0';

    // Input NIM
    printf("  NIM             : ");
    fgets(nim, MAX_LEN_NIM, stdin);
    nim[strcspn(nim, "\n")] = '\0';

    // Input uang saku -- menggunakan pointer (*saldo) untuk mengubah nilai di main()
    printf("  Uang Saku (Rp)  : ");
    scanf("%f", saldo);
    // `saldo` sudah berupa pointer, jadi scanf langsung menulis ke alamat asli
    bersihkanBuffer();

    printf("\n  --------------------------------------\n");
    printf("  Data berhasil disimpan!\n");
    printf("  Halo, %s (NIM: %s)\n", nama, nim);
    printf("  Uang saku awal minggu ini: Rp %.2f\n", *saldo);
    printf("  --------------------------------------\n");
}

/* ===========================================================
 *  FITUR 1: KELOLA KEUANGAN MINGGUAN
 * ===========================================================
 *  Konsep:
 *  - Array 1D `float pengeluaran[7]` untuk 7 hari
 *  - For loop untuk input dan kalkulasi
 *  - Pointer `float *saldoUtama` untuk update saldo (Pass-by-Ref)
 *  - Percabangan if-else untuk cek status keuangan
 * =========================================================== */
void kelolaKeuangan(float pengeluaran[], float *saldoUtama)
{
    // Array 1D String untuk nama-nama hari
    const char *namaHari[] = {
        "Senin", "Selasa", "Rabu", "Kamis",
        "Jumat", "Sabtu", "Minggu"
    };

    float totalPengeluaran = 0.0f;
    int i; // variabel loop

    printf("\n  +======================================+\n");
    printf("  |    KELOLA KEUANGAN MINGGUAN          |\n");
    printf("  +======================================+\n\n");
    printf("  Saldo saat ini: Rp %.2f\n\n", *saldoUtama);

    printf("  Masukkan pengeluaran untuk setiap hari:\n");
    printf("  --------------------------------------\n");

    // For loop: input pengeluaran 7 hari ke dalam Array 1D
    for (i = 0; i < HARI; i++)
    {
        printf("  Hari ke-%d (%s)\t: Rp ", i + 1, namaHari[i]);
        scanf("%f", &pengeluaran[i]);
        bersihkanBuffer();
    }

    // For loop: hitung total pengeluaran dari array
    for (i = 0; i < HARI; i++)
    {
        totalPengeluaran += pengeluaran[i];
    }

    // Pointer: update saldo utama secara langsung (Pass-by-Reference)
    *saldoUtama -= totalPengeluaran;

    /* --- Tampilkan Ringkasan --- */
    printf("\n  ======================================\n");
    printf("       RINGKASAN KEUANGAN MINGGUAN\n");
    printf("  ======================================\n\n");

    // For loop: cetak riwayat pengeluaran harian
    printf("  +--------+-----------------------+\n");
    printf("  |  Hari  |   Pengeluaran (Rp)    |\n");
    printf("  +--------+-----------------------+\n");
    for (i = 0; i < HARI; i++)
    {
        printf("  | %-6s |   %15.2f     |\n", namaHari[i], pengeluaran[i]);
    }
    printf("  +--------+-----------------------+\n\n");

    printf("  Total Pengeluaran  : Rp %.2f\n", totalPengeluaran);
    printf("  Sisa Saldo Utama   : Rp %.2f\n\n", *saldoUtama);

    // Percabangan if-else: evaluasi status keuangan
    if (*saldoUtama < 50000.0f)
    {
        printf("  +==================================================+\n");
        printf("  |  [WARNING] Status: Siaga 1 Tanggal Tua!          |\n");
        printf("  |  Hemat pengeluaran! Makan Indomie aja dulu...    |\n");
        printf("  +==================================================+\n");
    }
    else
    {
        printf("  +--------------------------------------------------+\n");
        printf("  |  [OK] Status Keuangan Aman. Tetap bijak ya!      |\n");
        printf("  +--------------------------------------------------+\n");
    }
}

/* ===========================================================
 *  FITUR 2: TO-DO LIST HARIAN / MINGGUAN
 * ===========================================================
 *  Konsep:
 *  - Array 2D String `char listTugas[5][100]` untuk daftar tugas
 *  - Array 1D `int statusTugas[5]` untuk status (0/1)
 *  - Sub-menu dengan do-while + switch-case
 *  - Pointer untuk update jumlah tugas & status
 * =========================================================== */
void toDoList(char listTugas[][MAX_LEN_TUGAS], int statusTugas[], int *jumlahTugas)
{
    int subPilihan;

    // Do-while loop untuk sub-menu to-do list
    do {
        printf("\n  +======================================+\n");
        printf("  |      TO-DO LIST ANAK KOST            |\n");
        printf("  +======================================+\n");
        printf("  |  [1] Lihat Daftar Tugas              |\n");
        printf("  |  [2] Tambah / Ubah Tugas             |\n");
        printf("  |  [3] Tandai Tugas Selesai            |\n");
        printf("  |  [0] Kembali ke Menu Utama           |\n");
        printf("  +======================================+\n");
        printf("  Pilihan >> ");
        scanf("%d", &subPilihan);
        bersihkanBuffer();

        switch (subPilihan)
        {
            case 1:
                // Lihat daftar tugas -- Pass-by-Value untuk jumlahTugas (dereferenced)
                lihatDaftarTugas(listTugas, statusTugas, *jumlahTugas);
                break;

            case 2:
                // Tambah/Ubah tugas -- Pass-by-Reference pointer jumlahTugas
                tambahUbahTugas(listTugas, statusTugas, jumlahTugas);
                break;

            case 3:
            {
                // Tandai tugas selesai -- Pointer ke elemen statusTugas
                int idx;
                if (*jumlahTugas == 0)
                {
                    printf("\n  [!] Belum ada tugas. Tambahkan dulu!\n");
                    break;
                }

                // Tampilkan daftar tugas agar user bisa memilih
                lihatDaftarTugas(listTugas, statusTugas, *jumlahTugas);

                printf("\n  Pilih nomor tugas yang selesai (1-%d): ", *jumlahTugas);
                scanf("%d", &idx);
                bersihkanBuffer();

                // Validasi input
                if (idx < 1 || idx > *jumlahTugas)
                {
                    printf("  [!] Nomor tugas tidak valid!\n");
                }
                else if (statusTugas[idx - 1] == 1)
                {
                    printf("  [!] Tugas \"%s\" sudah ditandai selesai.\n",
                           listTugas[idx - 1]);
                }
                else
                {
                    // Memanggil fungsi dengan POINTER ke elemen array
                    // Konsep: Pass-by-Reference -- mengirim alamat
                    //         elemen statusTugas[idx-1]
                    tandaiSelesai(&statusTugas[idx - 1]);
                    printf("  [V] Tugas \"%s\" berhasil ditandai selesai!\n",
                           listTugas[idx - 1]);
                }
                break;
            }

            case 0:
                printf("\n  Kembali ke Menu Utama...\n");
                break;

            default:
                printf("\n  [!] Pilihan tidak valid!\n");
                break;
        }

    } while (subPilihan != 0);
}

/* ----------------------------------------------------------
 *  lihatDaftarTugas()
 *  Konsep: For loop + Percabangan if-else
 *          Mencetak indikator [ ] atau [X]
 *          Parameter jumlahTugas di-pass secara Pass-by-Value
 * ---------------------------------------------------------- */
void lihatDaftarTugas(char listTugas[][MAX_LEN_TUGAS], int statusTugas[], int jumlahTugas)
{
    int i;

    printf("\n  --------------------------------------\n");
    printf("           DAFTAR TUGAS KAMU\n");
    printf("  --------------------------------------\n");

    if (jumlahTugas == 0)
    {
        printf("  (Belum ada tugas. Yuk tambahkan!)\n");
        return;
    }

    // For loop: iterasi semua tugas yang sudah diinput
    for (i = 0; i < jumlahTugas; i++)
    {
        // Percabangan if-else: tampilkan indikator status
        if (statusTugas[i] == 1)
        {
            printf("  %d. [X] %s\n", i + 1, listTugas[i]);
        }
        else
        {
            printf("  %d. [ ] %s\n", i + 1, listTugas[i]);
        }
    }
    printf("  --------------------------------------\n");
}

/* ----------------------------------------------------------
 *  tambahUbahTugas()
 *  Konsep: Array 2D String -- menulis ke baris tertentu
 *          Pointer untuk update jumlahTugas
 * ---------------------------------------------------------- */
void tambahUbahTugas(char listTugas[][MAX_LEN_TUGAS], int statusTugas[], int *jumlahTugas)
{
    int pilihan;
    int idx;

    printf("\n  [1] Tambah Tugas Baru\n");
    printf("  [2] Ubah Tugas yang Ada\n");
    printf("  Pilihan >> ");
    scanf("%d", &pilihan);
    bersihkanBuffer();

    if (pilihan == 1)
    {
        // Tambah tugas baru
        if (*jumlahTugas >= MAX_TUGAS)
        {
            printf("  [!] Daftar tugas penuh! (Maks %d tugas)\n", MAX_TUGAS);
            return;
        }

        printf("  Masukkan tugas baru: ");
        // fgets: membaca string lengkap termasuk spasi ke Array 2D
        fgets(listTugas[*jumlahTugas], MAX_LEN_TUGAS, stdin);
        listTugas[*jumlahTugas][strcspn(listTugas[*jumlahTugas], "\n")] = '\0';

        statusTugas[*jumlahTugas] = 0; // Status awal: Belum Selesai

        // Pointer: menambah jumlah tugas melalui dereferensi pointer
        (*jumlahTugas)++;

        printf("  [+] Tugas berhasil ditambahkan! (Total: %d tugas)\n", *jumlahTugas);
    }
    else if (pilihan == 2)
    {
        // Ubah tugas yang ada
        if (*jumlahTugas == 0)
        {
            printf("  [!] Belum ada tugas untuk diubah.\n");
            return;
        }

        lihatDaftarTugas(listTugas, statusTugas, *jumlahTugas);

        printf("  Pilih nomor tugas yang ingin diubah (1-%d): ", *jumlahTugas);
        scanf("%d", &idx);
        bersihkanBuffer();

        if (idx < 1 || idx > *jumlahTugas)
        {
            printf("  [!] Nomor tugas tidak valid!\n");
            return;
        }

        printf("  Masukkan teks tugas baru: ");
        // Menulis ke baris tertentu di Array 2D String
        fgets(listTugas[idx - 1], MAX_LEN_TUGAS, stdin);
        listTugas[idx - 1][strcspn(listTugas[idx - 1], "\n")] = '\0';

        statusTugas[idx - 1] = 0; // Reset status ke Belum Selesai

        printf("  [~] Tugas nomor %d berhasil diubah!\n", idx);
    }
    else
    {
        printf("  [!] Pilihan tidak valid!\n");
    }
}

/* ----------------------------------------------------------
 *  tandaiSelesai()
 *  Konsep: Pass-by-Reference menggunakan POINTER
 *          Mengubah nilai 0 menjadi 1 melalui dereferensi
 *          pointer `*status = 1;`
 * ---------------------------------------------------------- */
void tandaiSelesai(int *status)
{
    // Memakai Pointer untuk update status tugas
    // Dereferensi pointer: mengubah nilai pada alamat yang ditunjuk
    *status = 1;
}

/* ===========================================================
 *  FITUR 3: REKOMENDASI SURVIVAL ANAK KOST
 * ===========================================================
 *  Konsep: Pass-by-Value -- saldo dikirim sebagai salinan
 *          Sub-menu, Percabangan if-else, Array 2D String,
 *          rand() untuk gacha menu acak
 * =========================================================== */
void sarankanSurvival(float saldoSaatIni)
{
    // Parameter saldoSaatIni merupakan SALINAN (Pass-by-Value)
    // Perubahan di sini TIDAK mempengaruhi variabel asli di main()

    int subPilihan;

    do {
        printf("\n  +======================================+\n");
        printf("  |   REKOMENDASI SURVIVAL ANAK KOST     |\n");
        printf("  +======================================+\n");
        printf("  |  [1] Rekomendasi Tempat Makan        |\n");
        printf("  |  [2] Gacha Menu Makan Acak           |\n");
        printf("  |  [0] Kembali ke Menu Utama           |\n");
        printf("  +======================================+\n");
        printf("  Pilihan >> ");
        scanf("%d", &subPilihan);
        bersihkanBuffer();

        switch (subPilihan)
        {
            case 1:
                // Pass-by-Value: mengirim salinan saldo
                rekomendasiTempatMakan(saldoSaatIni);
                break;

            case 2:
                gachaMenuMakan();
                break;

            case 0:
                printf("\n  Kembali ke Menu Utama...\n");
                break;

            default:
                printf("\n  [!] Pilihan tidak valid!\n");
                break;
        }

    } while (subPilihan != 0);
}

/* ----------------------------------------------------------
 *  rekomendasiTempatMakan()
 *  Konsep: Percabangan if - else if - else
 *          Pass-by-Value (float saldo = salinan)
 * ---------------------------------------------------------- */
void rekomendasiTempatMakan(float saldo)
{
    printf("\n  --------------------------------------\n");
    printf("     REKOMENDASI TEMPAT MAKAN\n");
    printf("  --------------------------------------\n");
    printf("  Saldo kamu saat ini: Rp %.2f\n\n", saldo);

    // Percabangan if - else if - else berdasarkan sisa saldo
    if (saldo >= 100000.0f)
    {
        printf("  [$$] Saldo cukup buat jajan mewah!\n");
        printf("  Rekomendasi:\n");
        printf("    * Kafe hits dekat kampus\n");
        printf("    * Restoran All You Can Eat\n");
        printf("    * Sushi / Korean BBQ\n");
        printf("  Nikmati hidup, tapi tetap bijak! :)\n");
    }
    else if (saldo >= 30000.0f)
    {
        printf("  [$] Saldo menengah -- masih oke lah!\n");
        printf("  Rekomendasi:\n");
        printf("    * Ayam Penyet SS / Geprek Bensu\n");
        printf("    * Rumah Makan Padang\n");
        printf("    * Bakso Urat + Es Teh Manis\n");
        printf("  Hemat sedikit ya, bos!\n");
    }
    else
    {
        printf("  [!] Saldo kritis! Mode hemat diaktifkan.\n");
        printf("  Rekomendasi:\n");
        printf("    * Warteg (Nasi + Orek Tempe + Telur)\n");
        printf("    * Indomie di Warmindo (tambah telor)\n");
        printf("    * Nasi + Lauk Kemarin (kalo masih ada)\n");
        printf("  Semangat!! Tanggal gajian tinggal bentar!\n");
    }

    printf("  --------------------------------------\n");
}

/* ----------------------------------------------------------
 *  gachaMenuMakan()
 *  Konsep: Array 2D String lokal (5 menu makanan hemat)
 *          rand() % 5 untuk memilih secara acak
 * ---------------------------------------------------------- */
void gachaMenuMakan(void)
{
    // Array 2D String lokal: 5 daftar makanan hemat anak kost
    char menuHemat[5][30] = {
        "Indomie Dok-Dok",
        "Nasi Omelet Tahu",
        "Warteg Nasi Orek",
        "Ayam Geprek",
        "Nasi Goreng Margarin"
    };

    // Menggunakan rand() % 5 untuk mendapatkan indeks acak 0-4
    int indeksAcak = rand() % 5;

    printf("\n  --------------------------------------\n");
    printf("       GACHA MENU MAKAN HARI INI\n");
    printf("  --------------------------------------\n\n");
    printf("  *memutar roda keberuntungan...*\n\n");
    printf("  +------------------------------+\n");
    printf("  |  Menu Hari Ini:              |\n");
    printf("  |                              |\n");
    printf("  |  >>> %-24s|\n", menuHemat[indeksAcak]);
    printf("  |                              |\n");
    printf("  +------------------------------+\n\n");
    printf("  Selamat makan! Apapun menunya,\n");
    printf("  yang penting kenyang :D\n");
    printf("  --------------------------------------\n");
}

/* ----------------------------------------------------------
 *  tampilkanPenutup()
 *  Konsep: Pointer ke string (char *nama)
 *          Mencetak pesan motivasi penutup
 * ---------------------------------------------------------- */
void tampilkanPenutup(char *nama)
{
    printf("\n");
    printf("  +==================================================+\n");
    printf("  |                                                  |\n");
    printf("  |   Terima kasih sudah menggunakan program ini!    |\n");
    printf("  |                                                  |\n");
    printf("  |   Pesan untuk %-33s|\n", nama);
    printf("  |                                                  |\n");
    printf("  |   \"Hidup di kost itu bukan soal bertahan,       |\n");
    printf("  |    tapi soal bertumbuh. Kelola uangmu,          |\n");
    printf("  |    selesaikan tugasmu, dan jangan lupa makan!\"  |\n");
    printf("  |                                                  |\n");
    printf("  |      ~ Semangat Survive, Anak Kost! ~            |\n");
    printf("  |                                                  |\n");
    printf("  +==================================================+\n");
    printf("\n");
}
