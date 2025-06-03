// kernel.c
// Fungsi-fungsi inti kernel

#include "std_type.h" // Untuk tipe data dasar seperti byte, bool
#include "kernel.h"   // Untuk deklarasi fungsi kernel seperti printString, clearScreen, dan fungsi assembly
#include "shell.h"    // Untuk deklarasi fungsi shell()

// Deklarasi extern untuk variabel global yang ada di shell.c
extern byte current_text_color;

// Fungsi utama C kernel.
int main() {
    // Coba tampilkan pesan debug untuk memastikan eksekusi dimulai
    printString("Starting kernel... ");
    clearScreen();
    printString("Kernel Mini OS Sederhana Telah Dimuat!\r\n");
    printString("Menggunakan fungsi dari kernel.h dan kernel.asm.\r\n");
    printString("Selamat datang.\r\n\r\n");

    printString("Menjalankan shell...\r\n");
    shell();

    printString("\r\nShell telah keluar (seharusnya tidak terjadi untuk shell interaktif sederhana).\r\n");
    printString("Sistem akan halt.\r\n");
    
    while (true) {
        // Loop tak terbatas
    }

    return 0; 
}

// Implementasi fungsi printString yang dideklarasikan di kernel.h
// Fungsi ini akan mencetak string ke layar menggunakan BIOS interrupt.
void printString(char* str) {
    while (*str) {
        // Menggunakan BIOS teletype output (int 0x10, ah=0x0E)
        // AX: ah=0x0E (fungsi teletype), al=karakter
        // BX: bh=0x00 (nomor halaman), bl=atribut warna (dinamis)
        interrupt(0x10, (0x0E00 | (unsigned int)*str), (0x0000 | current_text_color), 0, 0);
        str++;
    }
}

// Implementasi fungsi readString yang dideklarasikan di kernel.h
// Fungsi ini akan membaca string dari keyboard menggunakan BIOS interrupt.
void readString(char* buf) {
    int i = 0;
    char c;
    unsigned int ax_val;

    while (i < 127) { // Batasi panjang input, sisakan ruang untuk null terminator
        // Menggunakan BIOS int 0x16, ah=0x00 untuk membaca karakter
        // Mengembalikan: AH = scan code, AL = ASCII char
        ax_val = interrupt(0x16, 0x0, 0, 0, 0);
        c = (char)(ax_val & 0xFF); // Ambil ASCII char dari AL

        if (c == '\r') { // Tombol Enter
            buf[i] = '\0'; // Akhiri string
            printString("\r\n"); // Pindah baris
            return;
        } else if (c == 0x08) { // Tombol Backspace
            if (i > 0) {
                i--;
                // Hapus karakter dari layar: mundurkan kursor, cetak spasi, mundurkan kursor lagi
                printString("\b \b");
            }
        } else if (c >= ' ' && c <= '~') { // Karakter yang dapat dicetak
            if (i < 127) { // Pastikan tidak melebihi buffer -1 untuk null terminator
                buf[i++] = c;
                // Echo karakter ke layar
                interrupt(0x10, (0x0E00 | (unsigned int)c), (0x0000 | current_text_color), 0, 0);
            }
        }
        // Karakter lain (misalnya tombol fungsi, panah) diabaikan dalam implementasi sederhana ini
    }
    // Jika buffer penuh sebelum Enter
    buf[i] = '\0';
    printString("\r\n");
}

// Implementasi fungsi clearScreen yang dideklarasikan di kernel.h
// Fungsi ini akan membersihkan layar menggunakan BIOS interrupt.
void clearScreen() {
    // Gunakan current_text_color untuk atribut warna
    interrupt(0x10, 0x0600, (current_text_color << 8), 0x0000, 0x184F);
}
