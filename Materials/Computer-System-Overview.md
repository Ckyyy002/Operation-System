# 💻 Dasar Sistem Operasi & Arsitektur Komputer

![Computer Science](https://img.shields.io/badge/Topic-Operating%20Systems-blue) ![Architecture](https://img.shields.io/badge/Topic-Computer%20Architecture-orange) ![Learning](https://img.shields.io/badge/Status-Educational%20Material-green)

Dokumen ini berisi rangkuman mendalam mengenai fundamental sistem operasi, komponen utama komputer, manajemen memori, hingga teknik Input/Output (I/O). Materi ini dirancang untuk memahami bagaimana perangkat keras dan perangkat lunak bekerja sama dalam sebuah sistem komputer.

## 📋 Daftar Isi
- [1. Apa itu Sistem Operasi?](#1-apa-itu-sistem-operasi-operating-system)
- [2. Komponen Utama Komputer](#2-isi-dasar-sebuah-komputer-top-level-view)
- [3. Register: Memori Tercepat](#3-register-catatan-kecil-yang-sangat-penting)
- [4. Siklus Instruksi (Instruction Cycle)](#4-cara-komputer-menjalankan-program)
- [5. Konsep Interupsi](#5-interupsi-saat-komputer-disela)
- [6. Multiprogramming & Multitasking](#6-multitasking--multiprogramming)
- [7. Hirarki & Cache Memori](#7-hirarki-memori-memory-hierarchy--cache)
- [8. Teknik Komunikasi I/O](#8-cara-komputer-berkomunikasi-dengan-perangkat-io)

---

## 1. Apa itu Sistem Operasi? (Operating System)

Sistem Operasi (OS) adalah perangkat lunak sistem yang bertugas mengelola perangkat keras dan sumber daya perangkat lunak, serta menyediakan layanan umum untuk program komputer.

### 🍽️ Analogi Restoran
Untuk memahaminya dengan mudah, bayangkan komputer sebagai sebuah restoran:
| Komponen Komputer | Analogi Restoran | Keterangan |
| :--- | :--- | :--- |
| **Hardware** (CPU, RAM, HDD) | **Dapur & Alat Masak** | Sumber daya mentah untuk memproses pesanan. |
| **Pengguna** (User) | **Pelanggan** | Pihak yang memberikan perintah/pesanan. |
| **Sistem Operasi** (OS) | **Kepala Dapur (Manager)** | Mengatur alur kerja, memastikan efisiensi, dan melayani pelanggan. |

### Tugas Utama OS:
1.  **Resource Manager:** Menggunakan sumber daya (processor, memori, I/O) seefisien mungkin.
2.  **Service Provider:** Memberikan layanan ke pengguna (GUI, akses file, eksekusi aplikasi).
3.  **Hardware Control:** Mengatur driver untuk perangkat tambahan (keyboard, mouse, disk drive).

> **Inti:** Tanpa OS, hardware hanyalah besi yang tidak bisa berinteraksi dengan pengguna secara normal.

---

## 2. Isi Dasar Sebuah Komputer (Top Level View)

Secara garis besar, arsitektur komputer terdiri dari empat komponen utama:

### a. Processor (CPU) - Otak Komputer
Tempat pemrosesan seluruh instruksi. Di dalamnya terdapat unit penyimpanan super cepat bernama **Register**:
* **MAR (Memory Address Register):** Menunjuk *alamat* data di memori yang akan diakses.
* **MBR (Memory Buffer Register):** Menyimpan *isi data* yang sedang dibaca atau akan ditulis.
* **I/O Registers:** Buffer khusus untuk komunikasi dengan perangkat input/output.

### b. Main Memory (RAM) - Meja Kerja
* Tempat data/program ditaruh saat sedang dieksekusi.
* **Volatile:** Data hilang jika listrik mati.
* Disebut juga sebagai *Primary Memory*.

### c. I/O Modules - Pintu Masuk & Keluar
Jembatan antara CPU dengan dunia luar.
* *Storage:* Hard Disk, SSD, Flashdisk.
* *Human Interface:* Keyboard, Mouse, Monitor.
* *Communication:* Network Interface Card (Internet).

### d. System Bus - Jalan Raya
Jalur komunikasi utama tempat data berpindah antar komponen (CPU ↔ RAM ↔ I/O).

---

## 3. Register: Catatan Kecil yang Sangat Penting

Register adalah memori di dalam CPU dengan kecepatan akses paling tinggi.

### a. User-Visible Registers
Register yang dapat diakses dan dimanipulasi oleh programmer (via bahasa Assembly/Machine code) untuk efisiensi agar tidak perlu sering mengakses RAM.
* **Data Register:** Menyimpan angka/variabel.
* **Address Register:** Menyimpan alamat memori/pointer.
* **Stack Pointer:** Menunjuk posisi tumpukan data (LIFO) saat ini.

### b. Control & Status Registers
Register internal yang dipakai CPU dan OS untuk mengontrol eksekusi program.
* **Program Counter (PC):** Menunjuk alamat instruksi *berikutnya* yang akan diambil.
* **Instruction Register (IR):** Menyimpan instruksi yang *sedang* dikerjakan.
* **Program Status Word (PSW):** Menyimpan *flag* kondisi (misal: Zero flag, Overflow flag, Supervisor mode).

---

## 4. Cara Komputer Menjalankan Program

Komputer bekerja dengan siklus sederhana yang terus berulang tanpa henti. Proses ini dikenal sebagai **Instruction Cycle**.

1.  **Fetch (Ambil):** Processor mengambil instruksi/perintah dari memori berdasarkan alamat yang ditunjuk.
2.  **Execute (Jalankan):** Processor menerjemahkan perintah tersebut dan melaksanakannya.
3.  **Repeat:** Processor pindah ke instruksi berikutnya.

> **Analogi:** Bayangkan sedang membaca resep masakan.
> 1. Baca satu langkah (Fetch).
> 2. Lakukan langkah tersebut (Execute).
> 3. Lanjut baca langkah berikutnya.

---

## 5. Interupsi: Saat Komputer "Disela"

Terkadang, komputer harus berhenti sejenak dari pekerjaan utamanya karena ada perangkat lain yang membutuhkan perhatian (misalnya printer selesai mencetak atau ada data masuk dari internet). Mekanisme ini disebut **Interrupt**.

Karena perangkat I/O (Input/Output) bekerja jauh lebih lambat daripada Processor, interrupt digunakan agar Processor tidak perlu menunggu (idle).

**Apa yang terjadi saat Interrupt?**
> Sinyal masuk: *"Eh, berhenti sebentar. Ada hal penting yang harus ditangani."*

1.  Komputer **menyimpan** pekerjaan sementara (save context).
2.  Komputer **menangani** permintaan tersebut (Interrupt Service Routine).
3.  Komputer **kembali** ke pekerjaan semula.

---

## 6. Multitasking & Multiprogramming

Komputer modern tampak bisa melakukan banyak hal sekaligus: mengetik dokumen, mendengar lagu, dan mengunduh file.

Padahal, secara fisik (pada single core), processor hanya mengerjakan **satu hal dalam satu waktu**.

* **Ilusi Kebersamaan:** Processor bergantian mengerjakan tugas-tugas tersebut dengan kecepatan yang sangat tinggi.
* **Peran OS:** Sistem Operasi menentukan prioritas mana yang jalan duluan.

Konsep ini disebut **Multiprogramming**, tujuannya agar processor tidak pernah menganggur.

---

## 7. Hirarki Memori (Memory Hierarchy) & Cache

Memori dalam komputer disusun bertingkat berdasarkan prinsip:
* Semakin **cepat** → Semakin **mahal** → Kapasitas semakin **kecil**.
* Semakin **besar** → Semakin **lambat** → Harga semakin **murah**.

[attachment_0](attachment)

**Urutan Hirarki:**
1.  **Register** (Paling Cepat, ada di dalam Processor)
2.  **Cache** (Sangat Cepat)
3.  **RAM / Main Memory** (Cepat)
4.  **Hard Disk / Storage** (Lambat, Kapasitas Besar)

### Masalah & Solusi (Cache)
Masalah utama komputer adalah **Processor jauh lebih cepat daripada RAM**. Jika Processor harus selalu mengambil data langsung ke RAM, ia akan sering menunggu.

**Solusinya: Cache Memory**
* Memori kecil tapi super cepat yang menjadi perantara.
* Menyimpan data yang paling sering atau baru saja dipakai.
* **Prinsip Locality:** Jika sebuah data dipakai sekarang, kemungkinan besar data itu (atau temannya yang berdekatan) akan dipakai lagi sebentar lagi.

> **Tujuan:** Membuat komputer terasa lebih cepat tanpa harus membeli memori super cepat (mahal) dalam jumlah besar.

---

## 8. Cara Komputer Berkomunikasi dengan Perangkat (I/O)

Bagaimana processor bertukar data dengan keyboard, disk, atau layar? Ada 3 metode utama:

### a. Programmed I/O (Tidak Efisien)
* Processor "menunggu" sampai alat siap.
* Processor terus mengecek status alat berulang-ulang (polling).
* *Analogi:* Anda menunggu air mendidih sambil terus menatap panci tanpa melakukan hal lain.

### b. Interrupt-Driven I/O (Cukup Efisien)
* Processor memberi perintah, lalu lanjut bekerja mengerjakan hal lain.
* Jika alat sudah siap, alat akan mengirim sinyal (interupsi) ke processor.
* Processor berhenti sebentar untuk mentransfer data.

### c. Direct Memory Access / DMA (Sangat Efisien)
* Teknik paling canggih untuk transfer data besar.
* Processor menyuruh modul DMA: *"Tolong pindahkan data ini dari Disk ke RAM."*
* Data pindah secara langsung **tanpa** melibatkan processor.
* Processor hanya diberi tahu saat **semua** data selesai dipindah.

---

*Materi dirangkum untuk pembelajaran Sistem Operasi.*

