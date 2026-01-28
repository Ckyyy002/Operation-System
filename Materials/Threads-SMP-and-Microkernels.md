# Threads, SMP, dan Microkernel (Sistem Operasi)

## 1. Konsep Dasar: Proses vs Thread

Di bab sebelumnya, kita menganggap Proses itu satu kesatuan. Ternyata, **Proses** itu punya dua karakteristik yang bisa dipisah:

1. **Resource Ownership (Kepemilikan Sumber Daya):** Ini adalah "Modal"-nya. Memori, file yang dibuka, dan hak akses.
2. **Scheduling/Execution (Eksekusi):** Ini adalah "Aktivitas"-nya. Jalur eksekusi instruksi, status prosesor, dan stack.

**Analogy Time:**

> Bayangkan sebuah **Bengkel Mobil (Proses)**.
> * **Resource Ownership:** Adalah gedung bengkel, peralatan, kunci inggris, dan mobil yang sedang diperbaiki.
> * **Thread:** Adalah **Mekanik** yang bekerja di sana.
> * **Single-threaded:** Bengkel hanya punya 1 mekanik. Dia mengerjakan semua sendirian.
> * **Multi-threaded:** Bengkel punya 5 mekanik. Mereka berbagi gedung dan alat yang sama (Resource), tapi masing-masing mengerjakan bagian mobil yang berbeda (buka ban, ganti oli, cek mesin) secara bersamaan. Jauh lebih efisien, kan?
> 
> 

## 2. Multithreading

Multithreading adalah kemampuan OS untuk mendukung banyak jalur eksekusi (threads) dalam satu proses yang sama.

### Keuntungan Multithreading

Kenapa kita butuh banyak "mekanik" dalam satu bengkel?

1. **Responsiveness:** Jika satu thread macet (misal: mekanik A menunggu sparepart), mekanik B tetap bisa bekerja. Aplikasi tidak akan *freeze*.
2. **Resource Sharing:** Semua thread dalam satu proses bisa berbagi memori dan data tanpa perlu proses kirim-kiriman data yang ribet antar-proses.
3. **Economy:** Membuat thread baru jauh lebih "murah" dan cepat daripada membuat proses baru (karena tidak perlu alokasi memori baru).
4. **Utilization of MP Architectures:** Jika komputer Anda punya banyak core CPU (Multiprocessor), setiap thread bisa jalan di core yang berbeda secara paralel.

### User-Level Thread (ULT) vs Kernel-Level Thread (KLT)

* **User-Level Thread (ULT):** "Mekanik magang" yang diatur oleh aplikasi sendiri, OS tidak tahu menahu. Cepat, tapi kalau satu macet, OS bisa menganggap seluruh proses macet.
* **Kernel-Level Thread (KLT):** "Mekanik resmi" yang terdaftar di OS. OS yang mengatur jadwal kerjanya. Lebih stabil, tapi manajemennya sedikit lebih lambat.

## 3. Symmetric Multiprocessing (SMP)

Ini adalah arsitektur komputer modern.

* **Single Processor:** Satu otak mengerjakan semuanya.
* **SMP:** Komputer punya banyak "otak" (Processor/Core) yang setara. Mereka berbagi memori utama dan I/O yang sama.

**Manfaat SMP:**

* **Performance:** Lebih banyak otak = kerja lebih cepat.
* **Availability:** Jika satu prosesor rusak, sistem masih bisa jalan dengan prosesor sisanya.
* **Incremental Growth:** Bisa upgrade performa dengan menambah prosesor.

## 4. Microkernels

Desain OS zaman dulu (Monolithic) itu seperti "Raksasa" di mana semua fungsi (file system, driver, memori) ada di satu kernel besar.
**Microkernel** adalah pendekatan modern: "Buat kernel sekecil mungkin".

* **Filosofi:** Pindahkan sebanyak mungkin fungsi OS ke luar kernel (ke user space). Kernel hanya mengurus yang paling krusial: komunikasi (IPC), memori dasar, dan penjadwalan.
* **Kelebihan:** Lebih aman (crash di driver tidak mematikan sistem), fleksibel, dan mudah dimodifikasi.

## 5. Studi Kasus Sistem Operasi

### A. Windows (Manajemen Thread)

Windows menggunakan pendekatan **Kernel-Level Threads**. Setiap thread di Windows punya:

* **Thread ID:** Identitas unik.
* **Register Context:** Posisi terakhir CPU.
* **User & Kernel Stack:** Tumpukan data kerja.
* **Priority:** Tingkat kepentingan thread (0-31).

### B. Solaris (Sistem UNIX Modern)

Solaris punya pendekatan unik dengan konsep **LWP (Lightweight Process)**.

* **LWP:** Adalah jembatan antara User Thread dan Kernel Thread. Anggap LWP sebagai "kursi kerja" yang disediakan kernel untuk thread pengguna.

Struktur Data LWP:

* LWP Identifier (ID).
* Priority (Prioritas LWP).
* Signal Mask (Pengaturan sinyal).
* Saved values of user-level registers (Menyimpan status CPU).
* Kernel Stack (Memori kerja kernel).
* Resource usage data (Catatan penggunaan sumber daya).
* Pointer to corresponding kernel thread & process (Penunjuk ke thread dan proses induknya).

Diagram Status Thread Solaris:
Siklus hidup thread di Solaris lebih kompleks, meliputi status:

* **IDL:** Thread baru dibuat.
* **RUN:** Siap jalan (antre).
* **ONPROC:** Sedang jalan di prosesor.
* **SLEEP:** Tidur menunggu event (Blocked).
* **STOPPED:** Dihentikan sementara.
* **ZOMBIE:** Thread selesai tapi belum dibersihkan.

### C. Linux (Tasks)

Linux tidak membedakan secara ketat antara Proses dan Thread. Linux menyebut keduanya sebagai **Task**.

* Proses/Thread baru dibuat dengan perintah `clone()`.
* Struktur data utamanya adalah `task_struct`.

**Isi `task_struct` meliputi:**

* **State:** Status task (Running, Interruptible, dll).
* **Scheduling Information:** Prioritas dan jatah waktu.
* **Identifiers:** PID user dan grup.
* **Interprocess Communication:** Bendera untuk komunikasi.
* **Links:** Link ke task orang tua (*parent*) atau saudara (*sibling*).

---
