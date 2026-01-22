# Deskripsi dan Kontrol Proses (Sistem Operasi)

## 1. Pengantar: Apa itu Proses?

Seringkali mahasiswa bingung membedakan antara **Program** dan **Proses**. Mari kita luruskan dengan analogi sederhana:
* **Program** itu seperti **Buku Resep Masakan**. Ia diam, pasif, dan hanya sekumpulan instruksi yang tertulis di hard disk.
* **Proses** itu adalah **Kegiatan Memasak** itu sendiri. Ia aktif, dinamis, dan sedang dieksekusi oleh koki (Processor).

Secara teknis, proses adalah sebuah entitas yang bisa ditugaskan ke dan dieksekusi oleh prosesor.

### Elemen Pembentuk Proses
Agar sebuah proses bisa berjalan, ia membutuhkan beberapa elemen kunci:
1.  **Program Code:** Instruksi masakan itu sendiri (bisa dibagi dengan proses lain).
2.  **Set of Data:** Bahan-bahan masakan (variabel, data kerja).
3.  **Attributes (Process Control Block):** Catatan status koki. Ini mencakup ID proses, prioritas, dan status saat ini.

### Trace dan Dispatcher
Bagaimana CPU bekerja? Bayangkan CPU menelusuri daftar instruksi satu per satu. Jejak langkah eksekusi instruksi ini disebut **Trace**.

Namun, CPU tidak hanya mengerjakan satu proses sampai selesai (karena akan sangat lama). Ada sebuah program kecil bernama **Dispatcher** yang bertugas sebagai "Manajer Lalu Lintas". Dispatcher inilah yang memindahkan CPU dari satu proses ke proses lainnya.

> **Contoh Trace:** Bayangkan CPU mengerjakan Proses A (Alamat 5000-5005), lalu tiba-tiba "Timeout". Dispatcher (Alamat 100-105) mengambil alih, lalu mengoper tugas ke Proses B (Alamat 8000). Inilah yang membuat komputer terasa bisa melakukan *multitasking*.

---

## 2. Siklus Hidup Proses (State Process)

Proses itu tidak selalu "bekerja". Ia memiliki siklus hidup atau status (*state*).

### A. Model 2 Status (Sederhana)
Model paling dasar hanya membagi dunia menjadi dua:
* **Running:** Sedang dimasak (dieksekusi CPU).
* **Not Running:** Sedang antre atau menunggu.

### B. Model 5 Status (Lebih Realistis)
Model 2 status tidak cukup karena antrean bisa panjang. Kita memecahnya menjadi 5 bagian:
1.  **New:** Proses baru saja dibuat (bahan baru disiapkan).
2.  **Ready:** Proses siap dieksekusi, tinggal menunggu giliran CPU (menunggu kompor kosong).
3.  **Running:** Proses sedang dieksekusi.
4.  **Blocked/Waiting:** Proses tidak bisa jalan bukan karena tidak ada CPU, tapi karena menunggu hal lain (misalnya menunggu data dari disk, atau menunggu input keyboard pengguna).
5.  **Exit:** Proses selesai atau dihentikan.

### C. Suspended Processes (Proses yang "Digantung")
Kadang memori utama (RAM) penuh. Prosesor bekerja jauh lebih cepat daripada I/O, sehingga banyak proses yang diam menunggu I/O. Daripada memenuhi RAM dengan proses yang sedang diam (*Blocked*), OS memindahkannya ke **Disk** (Swap). Status ini disebut **Suspend**.

**Mengapa Proses di-Suspend?**
Berikut adalah alasan utamanya berdasarkan Tabel 3.3:

| Alasan | Penjelasan |
| :--- | :--- |
| **Swapping** | OS butuh RAM kosong untuk proses lain yang lebih siap jalan. |
| **Alasan OS Lain** | OS mencurigai proses bermasalah (misal: untuk debugging). |
| **Permintaan User** | Pengguna ingin menunda eksekusi (misal: debugging program). |
| **Timing** | Proses dijalankan secara berkala (misal: monitoring sistem) dan sedang menunggu waktu berikutnya. |
| **Permintaan Parent** | Proses induk (*parent*) ingin memodifikasi atau mengoordinasikan anak (*child*)-nya. |

---

## 3. Struktur Data Sistem Operasi

Sistem Operasi itu pada dasarnya adalah manajer administrasi yang sangat rapi. Ia mencatat segala sesuatu dalam tabel-tabel kontrol:

1.  **Memory Tables:** Mencatat alokasi RAM dan memori sekunder (virtual memory) untuk setiap proses, serta atribut proteksinya.
2.  **I/O Tables:** Mencatat status perangkat I/O (tersedia/sibuk) dan tujuan transfer datanya.
3.  **File Tables:** Mencatat keberadaan file, lokasi di disk, dan statusnya.
4.  **Process Tables:** Mengelola seluruh data proses melalui *Process Control Block*.

### Process Control Block (PCB)
Ini adalah bagian terpenting! Anggaplah PCB ini sebagai **KTP atau Rekam Medis** dari sebuah proses. Jika PCB rusak, proses akan hancur.

PCB berisi tiga kategori informasi utama:

1.  **Process Identification:** ID unik (angka) untuk proses tersebut, proses induknya, dan user yang menjalankannya.
2.  **Processor State Information:** Isi dari register CPU saat itu. Termasuk *Program Counter* (alamat instruksi selanjutnya) dan *Status Word* (seperti register EFLAGS pada Pentium yang mencatat flag error, interrupt, dll).
3.  **Process Control Information:** Informasi untuk OS mengelola proses, seperti prioritas penjadwalan, status (waiting/ready), pointer ke memori, dan sumber daya yang dimiliki.

### Mode Eksekusi
Prosesor biasanya mendukung setidaknya dua mode operasi untuk keamanan:
* **User Mode (Less-privileged):** Mode biasa untuk program pengguna. Aksesnya terbatas agar tidak merusak sistem.
* **System/Kernel Mode (More-privileged):** Mode "Dewa". Kernel OS berjalan di sini dan punya akses penuh ke memori dan instruksi khusus.

---

## 4. Bagaimana OS Mengontrol Proses?

OS mengontrol proses dengan cara menghentikan satu proses dan memulai proses lain (**Process Switching**).

### Kapan Pergantian Proses Terjadi?
Pergantian bisa terjadi kapan saja OS mengambil alih kendali. Pemicunya ada tiga:
1.  **Interrupt:** Kejadian eksternal (contoh: Timer habis, I/O selesai). Sifatnya *asynchronous*.
2.  **Trap:** Error saat eksekusi (contoh: membagi dengan nol, akses memori ilegal). Sifatnya terkait instruksi saat ini.
3.  **Supervisor Call (System Call):** Proses meminta layanan OS secara eksplisit (contoh: minta buka file).

### Langkah-langkah Process Switching
Ketika OS memutuskan mengganti proses, inilah langkah "ribet" yang harus dilakukan:
1.  **Save Context:** Simpan posisi terakhir proses lama (Program counter, register) ke dalam PCB-nya.
2.  **Update PCB Lama:** Ubah statusnya (misal dari Running ke Ready atau Blocked).
3.  **Move PCB:** Pindahkan PCB ke antrean yang sesuai.
4.  **Select New Process:** Pilih proses baru (Jadwal).
5.  **Update PCB Baru:** Ubah status proses baru menjadi Running.
6.  **Update Memory Mgmt:** Siapkan struktur memori untuk proses baru.
7.  **Restore Context:** Muat data register dari PCB proses baru ke CPU.

### Di Mana Posisi OS Dieksekusi?
Apakah OS itu proses juga? Jawabannya bisa bervariasi:
1.  **Non-process Kernel:** Kernel berjalan di luar proses manapun (konsep lama). OS punya memori dan stack sendiri.
2.  **Execution Within User Process:** OS adalah sekumpulan rutin yang dipanggil *di dalam* konteks proses pengguna (umum di UNIX). Ini efisien karena tidak perlu ganti proses total, hanya ganti mode (User ke Kernel).
3.  **Process-based OS:** OS diimplementasikan sebagai kumpulan proses sistem. Sangat modular.

---

## 5. Keamanan Sistem (Security)

OS bertanggung jawab menjaga "benteng" sistem dari akses tidak sah.

### Ancaman (Threats)
* **Intruders (Penyusup):**
    * *Masquerader:* Orang luar yang menyamar jadi user sah.
    * *Misfeasor:* Orang dalam (user sah) yang menyalahgunakan wewenang.
    * *Clandestine:* User yang menggunakan kontrol sistem untuk menghindari audit.
* **Malicious Software (Malware):** Perangkat lunak jahat.

### Penanggulangan (Countermeasures)
1.  **Intrusion Detection System (IDS):** Sensor dan penganalisa untuk mendeteksi perilaku aneh (seperti satpam CCTV).
2.  **Authentication:** Memastikan user adalah orang yang benar. Menggunakan 4 faktor: Sesuatu yang Anda *tahu* (password), *punya* (token), *adalah* (sidik jari), atau *lakukan* (tanda tangan/suara).
3.  **Access Control:** Kebijakan siapa boleh buka file apa. Ada database otorisasi.
4.  **Firewalls:** Komputer khusus yang memfilter lalu lintas jaringan antara komputer internal dan dunia luar (internet).

---

## 6. Studi Kasus: Manajemen Proses di UNIX SVR4

UNIX menggunakan model di mana sebagian besar OS berjalan dalam konteks proses pengguna (User Process).

### Diagram Status Proses UNIX
UNIX memiliki status yang lebih kompleks dari model standar 5-state. Beberapa status uniknya antara lain:
* **User Running vs Kernel Running:** Membedakan apakah proses sedang jalan di mode user atau mode kernel (karena system call).
* **Zombie:** Proses sudah selesai (Exit), tapi "arwahnya" (catatannya) masih ada di tabel proses menunggu diambil oleh proses induknya (*Parent*).
* **Preempted:** Proses sedang jalan di mode kernel, tapi dipaksa berhenti (preempt) untuk memberikan CPU ke proses lain yang lebih prioritas.

### Pembuatan Proses: `fork()`
Di UNIX, proses baru dibuat dengan perintah sistem `fork()`.
Ketika `fork()` dipanggil, OS melakukan hal berikut:
1.  Alokasi slot di tabel proses untuk anak (*child*).
2.  Berikan ID unik ke *child*.
3.  **Copy Image:** Salin seluruh isi "otak" (image) dari proses induk ke anak. Kecuali memori yang dibagi (*shared memory*).

Uniknya, setelah `fork()`:
* Proses Induk (*Parent*) menerima kembalian berupa **PID Anak**.
* Proses Anak (*Child*) menerima kembalian **angka 0**.
Ini cara program tahu apakah dia sedang jadi induk atau jadi anak.
