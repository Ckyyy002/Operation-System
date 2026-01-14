# 🖥️ Ikhtisar Sistem Operasi (Operating System Overview)

![OS Concepts](https://img.shields.io/badge/Concept-Operating%20System-blue) ![Architecture](https://img.shields.io/badge/Architecture-System%20Design-orange) ![Reference](https://img.shields.io/badge/Source-William%20Stallings-green)

Dokumen ini berisi rangkuman teknis mengenai tujuan, evolusi, dan komponen utama dalam desain Sistem Operasi modern. Materi ini mencakup manajemen proses, memori, hingga arsitektur sistem mutakhir seperti SMP dan Microkernel.

## 📋 Daftar Isi
- [1. Definisi & Tujuan Sistem Operasi](#1-definisi--tujuan-sistem-operasi)
- [2. Struktur & Lapisan Sistem](#2-struktur--lapisan-sistem-layers-and-views)
- [3. Evolusi Sistem Operasi](#3-evolusi-sistem-operasi)
- [4. Konsep Proses (Process)](#4-konsep-proses-process)
- [5. Manajemen Memori & Virtual Memory](#5-manajemen-memori--virtual-memory)
- [6. Keamanan & Penjadwalan](#6-keamanan--penjadwalan-resource-management)
- [7. Arsitektur Sistem Operasi Modern](#7-arsitektur-sistem-operasi-modern)

---

## 1. Definisi & Tujuan Sistem Operasi

[span_0](start_span)Sistem Operasi (OS) adalah program yang mengontrol eksekusi program aplikasi dan bertindak sebagai antarmuka (interface) antara aplikasi dan perangkat keras komputer[span_0](end_span).

### Tiga Tujuan Utama OS:
1.  **[span_1](start_span)Convenience (Kemudahan):** Membuat komputer lebih mudah digunakan[span_1](end_span).
2.  **[span_2](start_span)Efficiency (Efisiensi):** Memungkinkan sumber daya sistem komputer digunakan dengan cara yang efisien[span_2](end_span).
3.  **[span_3](start_span)Ability to Evolve (Kemampuan Berkembang):** Memungkinkan pengembangan, pengujian, dan pengenalan fungsi sistem baru tanpa mengganggu layanan yang ada[span_3](end_span).

### Peran OS sebagai Manajer Sumber Daya
[span_4](start_span)OS berfungsi sama seperti perangkat lunak biasa (program yang dieksekusi), namun tugas utamanya adalah mengelola sumber daya (CPU, Memori, I/O) dan menyerahkan kontrol prosesor ke program lain saat diperlukan[span_4](end_span).

---

## 2. Struktur & Lapisan Sistem (Layers and Views)

Dalam hierarki sistem komputer, OS berada di antara perangkat keras (hardware) dan program aplikasi/utilitas.

**Visualisasi Lapisan:**
```text
[ End User ]
      ⬇
[ Application Programs ]
      ⬇
[ Utilities ]
      ⬇
[ Operating System ]  <-- (Designer View)
      ⬇
[ Computer Hardware ]
```

### Layanan yang Disediakan OS
Sistem operasi menyediakan layanan bagi programmer, pengguna, dan efisiensi sistem itu sendiri:
* **[span_0](start_span)Pembuatan Program:** Menyediakan alat seperti editor dan debugger untuk membantu programmer[span_0](end_span).
* **[span_1](start_span)Eksekusi Program:** Menangani langkah-langkah pemuatan instruksi dan data ke memori utama[span_1](end_span).
* **[span_2](start_span)Akses Perangkat I/O:** Menyediakan antarmuka seragam agar programmer tidak perlu memikirkan detail teknis setiap perangkat I/O[span_2](end_span).
* **[span_3](start_span)Akses Terkontrol ke File:** Memahami format penyimpanan pada media (disk/tape) dan menyediakan mekanisme perlindungan akses[span_3](end_span).
* **[span_4](start_span)Akses Sistem:** Mengontrol akses ke sistem publik atau bersama untuk mencegah penggunaan tanpa izin[span_4](end_span).
* **[span_5](start_span)Deteksi & Respons Kesalahan:** Menangani error perangkat keras (misal: memori rusak) dan perangkat lunak (misal: overflow, akses memori terlarang)[span_5](end_span).
* **[span_6](start_span)Accounting:** Mengumpulkan statistik penggunaan sumber daya untuk memantau kinerja atau keperluan penagihan (billing)[span_6](end_span).

### Peran OS sebagai Manajer Sumber Daya
[span_7](start_span)OS berfungsi sama seperti perangkat lunak komputer biasa, yaitu berupa program yang dieksekusi[span_7](end_span). [span_8](start_span)Namun, OS secara periodik melepaskan kontrol prosesor untuk menjalankan aplikasi lain[span_8](end_span).

> **[span_9](start_span)Inti:** OS mengarahkan prosesor dalam penggunaan sumber daya sistem lainnya dan mengatur waktu eksekusi program pengguna[span_9](end_span).

---

## 3. Evolusi Sistem Operasi

[span_10](start_span)Perkembangan OS didorong oleh peningkatan perangkat keras dan kebutuhan akan layanan baru[span_10](end_span).

### a. Serial Processing (Era Awal)
* **[span_11](start_span)Tanpa Sistem Operasi:** Mesin dijalankan langsung dari konsol dengan lampu indikator dan sakelar[span_11](end_span).
* **Masalah Utama:**
    * *[span_12](start_span)Penjadwalan:* Pengguna harus mendaftar jam pakai mesin[span_12](end_span).
    * *[span_13](start_span)Waktu Setup:* Waktu terbuang banyak untuk memuat compiler, program sumber, dan menyimpan hasil[span_13](end_span).

### b. Simple Batch Systems
* [span_14](start_span)Menggunakan **Monitor**, yaitu perangkat lunak sederhana yang mengontrol urutan kejadian[span_14](end_span).
* [span_15](start_span)Pekerjaan (jobs) dikumpulkan dalam satu "batch" dan kontrol dikembalikan ke monitor saat program selesai[span_15](end_span).
* **[span_16](start_span)JCL (Job Control Language):** Bahasa khusus untuk memberi instruksi ke monitor (misal: `$JOB`, `$LOAD`, `$RUN`)[span_16](end_span).
* **Fitur Hardware Pendukung:**
    * *[span_17](start_span)Memory Protection:* Melindungi area memori Monitor agar tidak terhapus oleh program user[span_17](end_span).
    * *[span_18](start_span)Timer:* Mencegah satu pekerjaan memonopoli sistem selamanya[span_18](end_span).
    * *[span_19](start_span)Privileged Instructions:* Instruksi tertentu hanya boleh dijalankan oleh Monitor[span_19](end_span).
    * *[span_20](start_span)Interrupts:* Memungkinkan processor menangani I/O dengan lebih fleksibel[span_20](end_span).

### c. Multiprogramming (Multi-tasking)
[span_21](start_span)Tujuannya adalah memaksimalkan penggunaan prosesor[span_21](end_span).
* **[span_22](start_span)Uniprogramming:** Prosesor harus menunggu (idle) saat program melakukan operasi I/O[span_22](end_span).
* **[span_23](start_span)Multiprogramming:** Saat satu pekerjaan menunggu I/O, prosesor beralih ke pekerjaan lain yang siap[span_23](end_span).
* *[span_24](start_span)Hasil:* Utilisasi CPU meningkat drastis dibandingkan uniprogramming[span_24](end_span).

### d. Time Sharing Systems
* [span_25](start_span)Menggunakan multiprogramming untuk menangani banyak pekerjaan interaktif sekaligus[span_25](end_span).
* [span_26](start_span)Waktu prosesor dibagi-bagi (shared) di antara banyak pengguna yang mengakses sistem secara simultan[span_26](end_span).
* **Perbandingan Objektif:**
    * *[span_27](start_span)Batch Multiprogramming:* Memaksimalkan penggunaan prosesor[span_27](end_span).
    * *[span_28](start_span)Time Sharing:* Meminimalkan waktu respon (response time)[span_28](end_span).

---

## 4. Konsep Proses (Process)

Proses adalah konsep sentral dalam sistem operasi modern.

### Definisi Proses:
1.  [span_29](start_span)Sebuah program yang sedang dieksekusi[span_29](end_span).
2.  [span_30](start_span)Entitas yang dapat ditugaskan ke dan dieksekusi oleh prosesor[span_30](end_span).
3.  [span_31](start_span)Unit aktivitas yang memiliki status saat ini dan set sumber daya sistem yang terkait[span_31](end_span).

### Komponen Proses:
* **[span_32](start_span)Executable Program:** Kode program itu sendiri[span_32](end_span).
* **[span_33](start_span)Associated Data:** Data/variabel yang dibutuhkan program[span_33](end_span).
* **[span_34](start_span)Execution Context:** Semua informasi yang dibutuhkan OS untuk mengelola proses (seperti isi register prosesor dan prioritas)[span_34](end_span).

> **[span_35](start_span)Tantangan Desain Software Sistem:** Kesulitan utama meliputi sinkronisasi yang tidak tepat, gagalnya mutual exclusion (akses data bersamaan), operasi program non-deterministik, dan deadlock[span_35](end_span).

---

## 5. Manajemen Memori & Virtual Memory

[span_36](start_span)Tugas utama OS dalam memori meliputi isolasi proses, alokasi otomatis, dukungan pemrograman modular, dan kontrol akses[span_36](end_span).

### Virtual Memory & Paging
* **[span_37](start_span)Paging:** Memungkinkan proses dipecah menjadi blok-blok berukuran tetap yang disebut *pages*[span_37](end_span).
* **[span_38](start_span)Virtual Address:** Alamat logis yang terdiri dari nomor halaman dan offset, bukan alamat fisik[span_38](end_span).
* **Konsep Virtual Memory:**
    * [span_39](start_span)Program tidak perlu dimuat seluruhnya ke memori utama (RAM) untuk berjalan[span_39](end_span).
    * [span_40](start_span)Halaman program disimpan di disk (secondary memory) dan dipanggil ke RAM saat dibutuhkan[span_40](end_span).
    * [span_41](start_span)Menggunakan **MMU (Memory Management Unit)** untuk menerjemahkan alamat virtual ke alamat fisik (Real Address)[span_41](end_span).

---

## 6. Keamanan & Penjadwalan (Resource Management)

### Keamanan Informasi (Protection & Security)
OS harus menjamin keamanan dalam beberapa aspek:
* **[span_42](start_span)Availability:** Melindungi sistem dari gangguan/interupsi[span_42](end_span).
* **[span_43](start_span)Confidentiality:** Mencegah pembacaan data tanpa izin[span_43](end_span).
* **[span_44](start_span)Data Integrity:** Mencegah modifikasi data tanpa izin[span_44](end_span).
* **[span_45](start_span)Authenticity:** Verifikasi identitas pengguna dan validitas pesan/data[span_45](end_span).

### Penjadwalan (Scheduling)
Kebijakan alokasi sumber daya harus mempertimbangkan:
* **[span_46](start_span)Fairness (Keadilan):** Memberikan akses yang setara ke sumber daya[span_46](end_span).
* **[span_47](start_span)Differential Responsiveness:** Membedakan layanan berdasarkan kelas pekerjaan (misal: real-time vs background)[span_47](end_span).
* **[span_48](start_span)Efficiency:** Memaksimalkan throughput, meminimalkan waktu respon, dan mengakomodasi pengguna sebanyak mungkin[span_48](end_span).

---

## 7. Arsitektur Sistem Operasi Modern

Sistem operasi modern telah berevolusi dari struktur monolitik menjadi desain yang lebih modular.

### Karakteristik Utama:
1.  **Microkernel Architecture:**
    * [span_49](start_span)Menugaskan hanya fungsi-fungsi paling esensial ke dalam kernel[span_49](end_span).
    * Fungsi lain berjalan di luar kernel untuk meningkatkan stabilitas dan fleksibilitas.
2.  **Multithreading:**
    * [span_50](start_span)Proses dibagi menjadi thread-thread yang dapat berjalan secara *concurrent* (bersamaan)[span_50](end_span).
    * **[span_51](start_span)Thread:** Unit kerja yang dapat didispatch (dikirim) yang berjalan secara berurutan dan dapat diinterupsi[span_51](end_span).
3.  **Symmetric Multiprocessing (SMP):**
    * [span_52](start_span)Terdapat beberapa prosesor yang berbagi memori utama dan fasilitas I/O yang sama[span_52](end_span).
    * [span_53](start_span)Semua prosesor dapat melakukan fungsi yang sama[span_53](end_span).
    * *[span_54](start_span)Perbedaan:* Multiprogramming melakukan *interleaving* (selang-seling) pada satu prosesor, sedangkan Multiprocessing bisa melakukan *overlapping* fisik pada dua prosesor atau lebih[span_54](end_span).
4.  **Distributed Operating Systems:**
    * [span_55](start_span)Memberikan ilusi satu ruang memori utama tunggal dan satu ruang penyimpanan sekunder meskipun tersebar di banyak mesin[span_55](end_span).
5.  **Object-Oriented Design:**
    * [span_56](start_span)Memungkinkan penambahan ekstensi modular ke kernel kecil[span_56](end_span).
    * [span_57](start_span)Memudahkan kustomisasi OS tanpa mengganggu integritas sistem[span_57](end_span).

---
*[span_58](start_span)Dibuat berdasarkan materi kuliah Operating Systems: Internals and Design Principles, 6/E oleh William Stallings[span_58](end_span).*
