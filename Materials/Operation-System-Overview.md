# 🖥️ Ikhtisar Sistem Operasi (Operating System Overview)

![OS Concepts](https://img.shields.io/badge/Concept-Operating%20System-blue)
![Architecture](https://img.shields.io/badge/Architecture-System%20Design-orange)
![Reference](https://img.shields.io/badge/Source-William%20Stallings-green)

Dokumen ini berisi rangkuman teknis mengenai tujuan, evolusi, dan komponen utama dalam desain Sistem Operasi modern.  
Materi mencakup manajemen proses, memori, hingga arsitektur sistem mutakhir seperti **SMP** dan **Microkernel**.

---

## 📋 Daftar Isi
1. [Definisi & Tujuan Sistem Operasi](#1-definisi--tujuan-sistem-operasi)
2. [Struktur & Lapisan Sistem](#2-struktur--lapisan-sistem)
3. [Evolusi Sistem Operasi](#3-evolusi-sistem-operasi)
4. [Konsep Proses](#4-konsep-proses)
5. [Manajemen Memori & Virtual Memory](#5-manajemen-memori--virtual-memory)
6. [Keamanan & Penjadwalan](#6-keamanan--penjadwalan)
7. [Arsitektur Sistem Operasi Modern](#7-arsitektur-sistem-operasi-modern)

---

## 1. Definisi & Tujuan Sistem Operasi

Sistem Operasi (Operating System / OS) adalah program yang mengontrol eksekusi program aplikasi dan bertindak sebagai antarmuka antara pengguna, aplikasi, dan perangkat keras komputer.

### 🎯 Tujuan Utama Sistem Operasi
1. **Convenience (Kemudahan)**  
   Membuat komputer lebih mudah digunakan oleh pengguna.

2. **Efficiency (Efisiensi)**  
   Mengoptimalkan pemanfaatan sumber daya sistem komputer.

3. **Ability to Evolve (Kemampuan Berkembang)**  
   Memungkinkan pengembangan dan penambahan fungsi sistem tanpa mengganggu layanan yang sedang berjalan.

### 🧩 OS sebagai Manajer Sumber Daya
OS mengelola sumber daya utama seperti **CPU, memori, dan perangkat I/O**, serta mengatur kapan kontrol prosesor diberikan kepada program lain.

---

## 2. Struktur & Lapisan Sistem

Dalam hierarki sistem komputer, OS berada di antara perangkat keras dan program aplikasi.

### 📊 Visualisasi Lapisan Sistem
```text
[ End User ]
      ↓
[ Application Programs ]
      ↓
[ Utilities ]
      ↓
[ Operating System ]   ← Designer View
      ↓
[ Computer Hardware ]
```

### 🔧 Layanan yang Disediakan Sistem Operasi
- **Pembuatan Program**  
  Menyediakan tools seperti editor dan debugger.

- **Eksekusi Program**  
  Mengelola pemuatan instruksi dan data ke memori utama.

- **Akses Perangkat I/O**  
  Menyediakan antarmuka seragam untuk perangkat masukan/keluaran.

- **Manajemen File**  
  Mengatur format penyimpanan dan kontrol akses file.

- **Keamanan Akses Sistem**  
  Mencegah penggunaan sistem tanpa izin.

- **Deteksi & Penanganan Kesalahan**  
  Menangani error perangkat keras maupun perangkat lunak.

- **Accounting**  
  Mengumpulkan statistik penggunaan sumber daya sistem.

> **Inti Peran OS:**  
> Mengarahkan penggunaan prosesor dan sumber daya sistem secara efisien serta mengatur waktu eksekusi program pengguna.

---

## 3. Evolusi Sistem Operasi

Perkembangan sistem operasi didorong oleh peningkatan perangkat keras dan kebutuhan layanan komputasi.

### a. Serial Processing
- Tidak menggunakan sistem operasi.
- Program dijalankan langsung dari konsol.
- Masalah utama:
  - Penjadwalan manual
  - Waktu setup yang lama

### b. Simple Batch Systems
- Menggunakan **monitor program** untuk mengontrol urutan job.
- Job dikumpulkan dalam satu batch.
- Menggunakan **JCL (Job Control Language)**.
- Dukungan hardware:
  - Memory protection
  - Timer
  - Privileged instructions
  - Interrupts

### c. Multiprogramming
- Tujuan: memaksimalkan utilisasi CPU.
- Saat satu job menunggu I/O, CPU menjalankan job lain.
- Meningkatkan efisiensi dibanding uniprogramming.

### d. Time Sharing Systems
- Menggunakan multiprogramming untuk sistem interaktif.
- Waktu CPU dibagi ke banyak pengguna.
- Fokus pada **response time**, bukan hanya utilisasi CPU.

---

## 4. Konsep Proses

Proses adalah konsep inti dalam sistem operasi modern.

### 📌 Definisi Proses
- Program yang sedang dieksekusi
- Entitas yang dijadwalkan oleh prosesor
- Unit aktivitas dengan status dan sumber daya sendiri

### 🧱 Komponen Proses
- **Executable Program** – kode program
- **Associated Data** – data dan variabel
- **Execution Context** – informasi register, status, dan prioritas

> **Tantangan Desain Sistem:**  
> Sinkronisasi, mutual exclusion, non-determinisme, dan deadlock.

---

## 5. Manajemen Memori & Virtual Memory

Tugas utama OS dalam manajemen memori meliputi:
- Isolasi proses
- Alokasi otomatis
- Dukungan pemrograman modular
- Kontrol akses memori

### 🧠 Virtual Memory & Paging
- **Paging**: Memori dibagi menjadi halaman berukuran tetap.
- **Virtual Address**: Terdiri dari nomor halaman dan offset.
- Program tidak perlu dimuat seluruhnya ke RAM.
- Halaman dipanggil dari disk saat dibutuhkan.
- Translasi alamat dilakukan oleh **MMU (Memory Management Unit)**.

---

## 6. Keamanan & Penjadwalan

### 🔐 Keamanan Informasi
- **Availability** – sistem tetap tersedia
- **Confidentiality** – data tidak dibaca tanpa izin
- **Integrity** – data tidak dimodifikasi secara ilegal
- **Authenticity** – verifikasi identitas dan validitas data

### ⏱️ Penjadwalan (Scheduling)
- **Fairness** – akses sumber daya yang adil
- **Differential Responsiveness** – prioritas berdasarkan jenis pekerjaan
- **Efficiency** – throughput tinggi dan response time rendah

---

## 7. Arsitektur Sistem Operasi Modern

Sistem operasi modern bersifat modular dan fleksibel.

### ⚙️ Karakteristik Utama
1. **Microkernel Architecture**  
   Kernel hanya menangani fungsi esensial.

2. **Multithreading**  
   Proses dibagi menjadi thread yang berjalan secara concurrent.

3. **Symmetric Multiprocessing (SMP)**  
   Beberapa prosesor berbagi memori dan I/O secara setara.

4. **Distributed Operating Systems**  
   Memberikan ilusi satu sistem terpadu walau tersebar.

5. **Object-Oriented Design**  
   Memungkinkan ekstensi modular tanpa merusak integritas kernel.

---

*Disusun berdasarkan materi kuliah **Operating Systems: Internals and Design Principles (6th Edition)**  
oleh **William Stallings***