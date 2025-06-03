#include "shell.h"    // Deklarasi untuk shell() dan parseCommand()
#include "kernel.h"   // Untuk printString(), readString(), clearScreen()
#include "std_lib.h"  // Untuk strcpy(), clear(), strncpy(), atoi(), itoa(), mul(), mod()
#include "std_type.h" // Untuk bool, true, false, byte

// Variabel global untuk menyimpan state shell
static char current_username[32] = "user"; // Username default, kapasitas 31 karakter + null terminator
static char current_company_suffix[16] = ""; // Suffix untuk Grand Company (misalnya "@Storm")
byte current_text_color = 0x07; // Default: putih pada hitam (didefinisikan di sini)

// State untuk generator angka acak
static unsigned int rand_seed = 1;

// Fungsi sederhana untuk menghasilkan angka acak (LCG: Linear Congruential Generator)
static void seed_random(unsigned int seed) {
    rand_seed = seed;
}

static int get_random() {
    // Gunakan konstanta lebih kecil dan panggil mul serta mod
    rand_seed = mod(mul(rand_seed, 1103) + 1234, 32767); // Batasi ke range positif kecil
    return mod(rand_seed, 3); // Kembali ke range 0-2
}

// Fungsi untuk parsing input pengguna menjadi perintah dan argumen
void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    int i = 0, j = 0, k = 0;
    int arg_idx = 0;

    // Bersihkan buffer untuk mencegah data sisa
    clear((byte*)cmd, 64);
    clear((byte*)arg[0], 64);
    clear((byte*)arg[1], 64);

    // Lewati semua spasi dan karakter kontrol di awal input
    while (buf[i] != '\0' && (buf[i] == ' ' || buf[i] == '\r' || buf[i] == '\n')) i++;

    // Ekstrak nama perintah (bagian sebelum spasi pertama atau akhir string)
    while (buf[i] != '\0' && buf[i] != ' ' && buf[i] != '\r' && buf[i] != '\n') {
        if (j < 63) cmd[j++] = buf[i]; // Hindari buffer overflow
        i++;
    }
    cmd[j] = '\0'; // Null-terminate perintah

    // Lewati semua spasi dan karakter kontrol setelah perintah
    while (buf[i] != '\0' && (buf[i] == ' ' || buf[i] == '\r' || buf[i] == '\n')) i++;

    // Ekstrak argumen (maksimal 2 argumen)
    while (buf[i] != '\0' && arg_idx < 2) {
        k = 0;
        while (buf[i] != '\0' && buf[i] != ' ' && buf[i] != '\r' && buf[i] != '\n') {
            if (k < 63) arg[arg_idx][k++] = buf[i]; // Hindari buffer overflow
            i++;
        }
        arg[arg_idx][k] = '\0'; // Null-terminate argumen
        arg_idx++;
        while (buf[i] != '\0' && (buf[i] == ' ' || buf[i] == '\r' || buf[i] == '\n')) i++;
    }
}

// Fungsi utama shell
void shell() {
    char input_buffer[128]; // Buffer untuk input pengguna
    char command[64];       // Buffer untuk menyimpan perintah
    char arguments[2][64];  // Buffer untuk menyimpan argumen
    bool command_found;     // Flag untuk menandai apakah perintah dikenali
    int counter = 0;        // Counter untuk seed acak
    char result_str[16];    // Buffer untuk hasil kalkulator

    // Inisialisasi shell dengan pesan selamat datang
    clearScreen();
    printString("Anda terbangun di dunia Eorzea pada pukul 03:34 pagi...\r\n");
    printString("Selamat datang di EorzeOS, sistem operasi untuk mendampingi petualangan Anda!\r\n");
    printString("Anda yang dimasak atau anda termasak ? haha\r\n");

    // Loop utama shell
    while (true) {
        command_found = false;
        counter++; // Tambah counter untuk seed acak
        seed_random(counter); // Atur seed acak

        // Tampilkan prompt dinamis
        printString(current_username);
        if (current_company_suffix[0] != '\0') {
            printString("@");
            printString(current_company_suffix);
        }
        printString("> ");

        // Baca input pengguna
        readString(input_buffer);

        // Parse input menjadi perintah dan argumen
        parseCommand(input_buffer, command, arguments);

        // Jika input kosong, lanjutkan ke iterasi berikutnya
        if (command[0] == '\0') {
            continue;
        }

        // Penanganan perintah
        // Perintah "yo" -> mencetak "gurt"
        if (compareStrings(command, "yo")) {
            printString("gurt\r\n");
            command_found = true;
        }
        // Perintah "gurt" -> mencetak "yo"
        else if (compareStrings(command, "gurt")) {
            printString("yo\r\n");
            command_found = true;
        }
        // Perintah "user <nama>"
        else if (compareStrings(command, "user")) {
            if (arguments[0][0] != '\0') { // Jika ada argumen (misal "user Atok")
                if (compareStrings(arguments[0], "default")) {
                    strncpy(current_username, "user", 32); // Reset ke default
                    printString("Username changed to user\r\n");
                } else {
                    strncpy(current_username, arguments[0], 32); // Salin dengan aman
                    printString("Username changed to ");
                    printString(current_username); // Tampilkan nama baru
                    printString("\r\n");
                }
            } else {
                printString("Invalid command: use 'user <name>' or 'user default'\r\n");
            }
            command_found = true;
        }
        // Perintah "grandcompany <nama>"
        else if (compareStrings(command, "grandcompany")) {
            if (arguments[0][0] != '\0') {
                if (compareStrings(arguments[0], "maelstrom")) {
                    current_text_color = 0x0C; // Merah
                    clearScreen(); // Bersihkan layar dengan warna baru
                    strncpy(current_company_suffix, "Storm", 16);
                    printString("Bergabung dengan Maelstrom!\r\n");
                } else if (compareStrings(arguments[0], "twinadder")) {
                    current_text_color = 0x0E; // Kuning
                    clearScreen(); // Bersihkan layar dengan warna baru
                    strncpy(current_company_suffix, "Serpent", 16);
                    printString("Bergabung dengan Twin Adder!\r\n");
                } else if (compareStrings(arguments[0], "immortalflames")) {
                    current_text_color = 0x0B; // Biru
                    clearScreen(); // Bersihkan layar dengan warna baru
                    strncpy(current_company_suffix, "Flame", 16);
                    printString("Bergabung dengan Immortal Flames!\r\n");
                } else {
                    printString("Invalid Grand Company: use 'maelstrom', 'twinadder', or 'immortalflames'\r\n");
                }
            } else {
                printString("Invalid command: use 'grandcompany <name>'\r\n");
            }
            command_found = true;
        }
        // Perintah "clear"
        else if (compareStrings(command, "clear")) {
            current_text_color = 0x07; // Kembali ke putih
            clearScreen(); // Bersihkan layar dengan warna default
            current_company_suffix[0] = '\0'; // Hapus suffix Grand Company
            command_found = true;
        }
        // Perintah kalkulator: "add <x> <y>"
        else if (compareStrings(command, "add")) {
            if (arguments[0][0] != '\0' && arguments[1][0] != '\0') {
                int x, y, result;
                atoi(arguments[0], &x);
                atoi(arguments[1], &y);
                result = x + y;
                itoa(result, result_str);
                printString(result_str);
                printString("\r\n");
            } else {
                printString("Invalid command: use 'add <x> <y>'\r\n");
            }
            command_found = true;
        }
        // Perintah kalkulator: "sub <x> <y>"
        else if (compareStrings(command, "sub")) {
            if (arguments[0][0] != '\0' && arguments[1][0] != '\0') {
                int x, y, result;
                atoi(arguments[0], &x);
                atoi(arguments[1], &y);
                result = x - y;
                itoa(result, result_str);
                printString(result_str);
                printString("\r\n");
            } else {
                printString("Invalid command: use 'sub <x> <y>'\r\n");
            }
            command_found = true;
        }
        // Perintah kalkulator: "mul <x> <y>"
        else if (compareStrings(command, "mul")) {
            if (arguments[0][0] != '\0' && arguments[1][0] != '\0') {
                int x, y, result;
                atoi(arguments[0], &x);
                atoi(arguments[1], &y);
                result = mul(x, y); // Gunakan mul alih-alih *
                itoa(result, result_str);
                printString(result_str);
                printString("\r\n");
            } else {
                printString("Invalid command: use 'mul <x> <y>'\r\n");
            }
            command_found = true;
        }
        // Perintah kalkulator: "div <x> <y>"
        else if (compareStrings(command, "div")) {
            if (arguments[0][0] != '\0' && arguments[1][0] != '\0') {
                int x, y, result;
                atoi(arguments[0], &x);
                atoi(arguments[1], &y);
                if (y != 0) {
                    result = div(x, y);
                    itoa(result, result_str);
                    printString(result_str);
                    printString("\r\n");
                } else {
                    printString("Error: Division by zero\r\n");
                }
            } else {
                printString("Invalid command: use 'div <x> <y>'\r\n");
            }
            command_found = true;
        }
        // Perintah "yogurt"
        else if (compareStrings(command, "yogurt")) {
            int random_value = get_random(); // Pilih antara 0, 1, atau 2
            if (random_value == 0) {
                printString("yo\r\n");
            } else if (random_value == 1) {
                printString("ts unami gng </3\r\n");
            } else {
                printString("sygau\r\n");
            }
            command_found = true;
        }

        // Perilaku "The Echo": ulang input jika perintah tidak dikenali
        if (!command_found) {
            printString(input_buffer);
            printString("\r\n");
        }
    }
}
