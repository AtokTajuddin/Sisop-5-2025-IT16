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

![1, 2, 3](assets/5.2.png)

## Soal 2

2. Praktikan diminta membuat fitur percakapan dua arah yang sederhana, seperti chatbot. Shell akan mengenali dua kata kunci:
   - Jika user mengetik yo, maka shell harus membalas dengan gurt
   - Jika user mengetik gurt, maka shell membalas yo
   Ini adalah mekanisme toggle antara dua kata.


## Soal 3

untuk no 3 praktikan diminta untuk membuat sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
    - user <username>: Mengubah nama shell prompt.
    - user: Mengembalikan ke "user".
    
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


![maelstrom / 4](assets/5.3.png)
![twinadder / 4](assets/5.4.png)
![immortalflames / 4](assets/5.5.png)

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
      
## Soal 7

Pada bagian terakhir ini, praktikan diminta untuk melengkapi atau membuat file Makefile yang bertugas meng-compile seluruh komponen dari sistem operasi EorzeOS secara otomatis menggunakan perintah make.
dimana Makefile adalah file konfigurasi yang digunakan oleh tool make untuk mengotomatisasi proses kompilasi program. Di sini, praktikan diminta membuat sistem build yang menyusun seluruh bagian sistem   operasi ke dalam satu file image (floppy.img).
Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.




   












