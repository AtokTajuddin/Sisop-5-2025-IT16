# Sisop-5-2025-IT16

## Kelompok

# LAPORAN PRAKTIKUM MODUL-5 #
## Praktikum Sistem Operasi Kelompok IT16 ##

| Nama | NRP       |
|-------|-----------|
| Ahmad Syauqi Reza | 5027241085   |
| Mochammad Atha Tajuddin   | 5027241093  |
| Tiara Fatimah Azzahra   | 5027241090  |
---

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal 1](#soal-1)
- [Soal 2](#soal-2)
- [Soal 3](#soal-3)
- [Soal 4](#soal-4)
- [Soal 5](#soal-5)
- [Soal 6](#soal-6)
- [Soal 7](#soal-7)


## Soal 1

Jika input bukan command valid, shell akan mencetak ulang string input. 

![1](assets/1.png)

## Soal 2

2. Praktikan diminta membuat fitur percakapan dua arah yang sederhana, seperti chatbot. Shell akan mengenali dua kata kunci:
   - Jika user mengetik yo, maka shell harus membalas dengan gurt
   - Jika user mengetik gurt, maka shell membalas yo
   Ini adalah mekanisme toggle antara dua kata.

![2](assets/2.png)

## Soal 3

untuk no 3 praktikan diminta untuk membuat sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
    - user <username>: Mengubah nama shell prompt.
    - user: Mengembalikan ke "user".

![3](assets/3.png)

## Soal 4

Pada bagian ini praktikan ditugaskan untuk mengimplementasikan fitur perintah grandcompany dalam shell EorzeOS dengan tujuan membuat command handler dalam shell.c agar ketika user mengetik
   - grandcompany maelstrom
   - grandcompany twinadder
   - grandcompany immortalflames

   maka shell akan: 
   - Clear layar terminal.
   - Mengubah warna teks berikutnya.
   - Mengubah prompt nama shell menjadi sesuai nama Grand Company:
     @Storm untuk Maelstrom
     @Serpent untuk Twin Adder
     @Flame untuk Immortal Flames

   Jika user mengetik:
   - grandcompany (tanpa argumen) atau
   - grandcompany <random> (bukan 3 nama valid)
   Maka shell harus mencetak error message.


![maelstrom / 4](assets/5.4.1.png)
![twinadder / 4](assets/5.4.2.png)
![immortalflames / 4](assets/5.4.3.png)

## Soal 5

Pada bagian ini, praktikan diminta untuk mengimplementasikan fitur kalkulator sederhana di dalam shell buatan sendiri (EorzeOS), yang bisa digunakan untuk melakukan operasi aritmatika dasar melalui command      input. Praktikan harus membuat shell mengenali 4 jenis perintah berikut:
   | Perintah      | Fungsi                      |
   | ------------- | --------------------------- |
   | `add <x> <y>` | Menjumlahkan dua bilangan   |
   | `sub <x> <y>` | Mengurangkan `x` dengan `y` |
   | `mul <x> <y>` | Mengalikan dua bilangan     |
   | `div <x> <y>` | Membagi `x` dengan `y`      |
   
   Shell akan menerima input dalam bentuk string seperti "add 4 2" lalu:
   - Parse input tersebut
   - Ambil nilai x dan y (harus dikonversi dari string ke integer)
   - Lakukan operasi sesuai command
   - Hasilnya akan ditampilkan
     
![5](assets/5.png)

## Soal 6

Pada bagian ini, praktikan diminta untuk mengimplementasikan command spesial yogurt yang akan menghasilkan respon acak dari karakter bernama gurt di dalam shell EorzeOS. Tujuannya adalah agar saat pengguna      mengetikkan yogurt, maka karakter bernama gurt akan membalas dengan salah satu dari tiga kemungkinan respon yang dipilih secara acak.
   
   1. Mendeteksi perintah khusus bernama yogurt saat user mengetiknya di terminal shell buatan sendiri.
   2. Membuat sistem pemilihan secara acak dari tiga respon yang sudah ditentukan, yaitu:
     ```
     gurt> yo
     gurt> ts unami gng </3
     gurt> sygau
     ```
   3. Menampilkan salah satu dari tiga respon tersebut, dan hasilnya bisa berbeda setiap kali user mengetikkan yogurt — karena dipilih secara acak.
   4. Menunjukkan interaksi antara pengguna (user>) dan karakter virtual gurt> dalam sistem operasi tersebut, mirip seperti easter egg atau fitur rahasia yang menyenangkan.

![6](assets/6.png)

## Soal 7

Pada bagian terakhir ini, praktikan diminta untuk melengkapi atau membuat file Makefile yang bertugas meng-compile seluruh komponen dari sistem operasi EorzeOS secara otomatis menggunakan perintah make.
dimana Makefile adalah file konfigurasi yang digunakan oleh tool make untuk mengotomatisasi proses kompilasi program. Di sini, praktikan diminta membuat sistem build yang menyusun seluruh bagian sistem   operasi ke dalam satu file image (floppy.img).
Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.


```Makefile
.PHONY: prepare bootloader stdlib shell kernel link build

build: prepare bootloader stdlib shell kernel link

prepare:
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin

stdlib:
	bcc -ansi -c -o bin/std_lib.o src/std_lib.c -Iinclude

shell:
	bcc -ansi -c -o bin/shell.o src/shell.c -Iinclude

kernel:
	bcc -ansi -c -o bin/kernel.o src/kernel.c -Iinclude
	nasm -f as86 src/kernel.asm -o bin/kernel_asm.o

link:
	ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel_asm.o bin/std_lib.o bin/shell.o
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 conv=notrunc
```


prepare: Membuat file kosong bin/floppy.img seukuran disket 1.44 MB.
bootloader, kernel, stdlib, shell: Meng-compile semua kode sumber (.c dan .asm) menjadi file-file objek perantara (.o dan .bin) menggunakan compiler bcc dan nasm.
link:
Menggabungkan semua file objek (.o) menjadi satu file kernel utuh bernama kernel.bin.
Menyalin bootloader.bin ke awal dari floppy.img.
Menyalin kernel.bin ke floppy.img tepat setelah bootloader.
Hasil akhirnya adalah sebuah file bin/floppy.img yang siap dijalankan sebagai sistem operasi di emulator seperti QEMU.












