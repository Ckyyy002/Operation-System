[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Eu-CByJh)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025241138 | William Hans Chandra |
| 5025241145 | Lyonel Oliver Dwiputra |
| 5025241147 | Lucky Himawan Prasetya |
| 5025241161 | Muh. Aqil Alqadri Syahid |

# Praktikum Modul 3 _(Module 3 Lab Work)_

### Laporan Resmi Praktikum Modul 3 _(Module 3 Lab Work Report)_

Di suatu pagi hari yang cerah, Budiman salah satu mahasiswa Informatika ditugaskan oleh dosennya untuk membuat suatu sistem operasi sederhana. Akan tetapi karena Budiman memiliki keterbatasan, Ia meminta tolong kepadamu untuk membantunya dalam mengerjakan tugasnya. Bantulah Budiman untuk membuat sistem operasi sederhana!

_One sunny morning, Budiman, an Informatics student, was assigned by his lecturer to create a simple operating system. However, due to Budiman's limitations, he asks for your help to assist him in completing his assignment. Help Budiman create a simple operating system!_

### Soal 1

> Sebelum membuat sistem operasi, Budiman diberitahu dosennya bahwa Ia harus melakukan beberapa tahap terlebih dahulu. Tahap-tahapan yang dimaksud adalah untuk **mempersiapkan seluruh prasyarat** dan **melakukan instalasi-instalasi** sebelum membuat sistem operasi. Lakukan seluruh tahapan prasyarat hingga [perintah ini](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/blob/master/Modul3/README-ID.md#:~:text=sudo%20apt%20install%20%2Dy%20busybox%2Dstatic) pada modul!

> _Before creating the OS, Budiman was informed by his lecturer that he must complete several steps first. The steps include **preparing all prerequisites** and **installing** before creating the OS. Complete all the prerequisite steps up to [this command](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/blob/master/Modul3/README-ID.md#:~:text=sudo%20apt%20install%20%2Dy%20busybox%2Dstatic) in the module!_

**Answer:**

  1. Siapkan virtual machine (seperti VMWare Player) dengan mengaktifkan nested virtualization
  2. Install Linux Ubuntu 22.04 dengan minimal 4GB memory dan 4 vCPU pada virtual machine

- **Code:**

  ```bash
  sudo apt -y update
  sudo apt -y install qemu-system build-essential bison flex libelf-dev libssl-dev bc grub-common grub-pc libncurses-dev libssl-dev mtools grub-pc-bin xorriso tmux
  
  mkdir -p osboot
  cd osboot
  
  wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.1.tar.xz
  tar -xvf linux-6.1.1.tar.xz
  cd linux-6.1.1
  
  make tinyconfig
  make menuconfig
  
  make -j$(nproc)

  cp arch/x86/boot/bzImage ..
  ```

- **Explanation:**

1. Lakukan instalasi tools seperti qemu pada terminal
2. Membuat direktori baru `osboot` untuk membuat sistem operasi baru yang akan dibuat
3. Pindah ke dalam direktori `osboot`
4. Unduh kode sumber kernel Linux versi 6.1.1 dan ekstrak ke dalam direktori `linux-6.1.1`
5. Pindah ke dalam direktori `linux-6.1.1`
6. `make tinyconfig` akan membuat konfigurasi minimal dari kernel Linux.
7. Konfigurasi lainnya akan diubah menggunakan `make menuconfig` dan simpan hasil ke dalam `.config`
8. Kompilasi kernel menggunakan seluruh inti CPU yang tersedia pada sistem.
9. Setelah kompilasi selesai, kita akan mendapatkan file `bzImage` di dalam direktori `arch/x86/boot/`

- **Screenshot:**

  `put your answer here`

- **Configuration**

  ```
  64-Bit Kernel
  General Setup > Configure standard kernel features > Enable support for printk
  General Setup > Configure standard kernel features > Enable futex support
  General Setup > Configure standard kernel features > Multiple users, groups and capabilites support
  General Setup > Initial RAM filesystem and RAM disk (initramfs/initrd) support
  General Setup > Control Group Support
  Enable the block layer > Legacy autoloading support
  Enable the block layer > Partition type > Advanced Partition Selection
  Device Drivers > Character devices > Enable TTY
  Device Drivers > Character devices > Virtio console
  Device Drivers > Character devices > /dev/mem virtual device support
  Device Drivers > Network device support > Virtio Network Driver
  Device Drivers > Serial Ata / Paralel ATA
  Device Drivers > Block Devices > Virtio block driver
  Device Drivers > Block Devices > loopback device support
  Device Drivers > Block Devices > RAM block device support
  Device Drivers > Virtio drivers
  Device Drivers > Virtualization Drivers
  Device Drivers > Generic  Driver Options > Maintain a devtmpfs at filesystems
  Device Drivers > Generic Driver Options > Automount devtmpfs at /dev
  Executable file formats > Kernel Support for ELF binaries
  Executable file formats > Kernel Support scripts starting with #!
  File Systems > FUSE support
  File Systems > The extended 3 filesystem
  File Systems > The extended 4 filesystem
  File Systems > Second extended fs support
  File Systems > Virtio Filesystem
  File Systems > Kernel automounter support
  File Systems > Pseudo File Systems > /proc file system support
  File Systems > Pseudo File Systems > sysctl support
  File Systems > Pseudo File Systems > sysfs file system support
  Networking Support > Networking options > Unix domain sockets
  Networking Support > Networking options > TCP/IP Networking
  ```

### Soal 2

> Setelah seluruh prasyarat siap, Budiman siap untuk membuat sistem operasinya. Dosen meminta untuk sistem operasi Budiman harus memiliki directory **bin, dev, proc, sys, tmp,** dan **sisop**. Lagi-lagi Budiman meminta bantuanmu. Bantulah Ia dalam membuat directory tersebut!

> _Once all prerequisites are ready, Budiman is ready to create his OS. The lecturer asks that the OS should contain the directories **bin, dev, proc, sys, tmp,** and **sisop**. Help Budiman create these directories!_

**Answer:**

- **Code:**

  ```bash
  sudo bash
  
  mkdir -p myramdisk/{bin,dev,proc,sys,etc,root,tmp,sisop,home/Budiman,home/guest,home/praktikan1,home/praktikan2}

  cp -a /dev/null myramdisk/dev
  cp -a /dev/tty* myramdisk/dev
  cp -a /dev/zero myramdisk/dev
  cp -a /dev/console myramdisk/dev

  cp /usr/bin/busybox myramdisk/bin
  cd myramdisk/bin
  ./busybox --install .

  cd ..
  touch init

  chmod +x init
  find . | cpio -oHnewc | gzip > ../myramdisk.gz
  ```

  `init`:
  ```bash
  #!/bin/sh
   /bin/mount -t proc none /proc
   /bin/mount -t sysfs none /sys

   while true
   do
       /bin/getty -L tty1 115200 vt100
       sleep 1
   done
  ```

- **Explanation:**

1. Masuk ke dalam mode superuser
2. Membuat folder bernama myramdisk dan beberapa sub-direktori yang diperlukan sistem file root
3. Salin dari sistem host ke dalam direktori `dev` di `myramdisk`
4. Salin file `BusyBox` ke dalam direktori `bin` di `myramdisk`
5. Buat file `init` di alam direktori `myramdisk`
6. Memberikan akses executable ke file `init`
7. Membuat file `myramdisk.gz` untuk booting sistem operasi yang akan dibuat

- **Screenshot:**

  `put your answer here`
  

### Soal 3

> Budiman lupa, Ia harus membuat sistem operasi ini dengan sistem **Multi User** sesuai permintaan Dosennya. Ia meminta kembali kepadamu untuk membantunya membuat beberapa user beserta directory tiap usernya dibawah directory `home`. Buat pula password tiap user-usernya dan aplikasikan dalam sistem operasi tersebut!

> _Budiman forgot that he needs to create a **Multi User** system as requested by the lecturer. He asks your help again to create several users and their corresponding home directories under the `home` directory. Also set each user's password and apply them in the OS!_

**Format:** `user:pass`

```
root:Iniroot
Budiman:PassBudi
guest:guest
praktikan1:praktikan1
praktikan2:praktikan2
```

**Answer:**

- **Code:**

  ```bash
  sudo bash

  cd myramdisk/etc

  openssl passwd -1 Iniroot
  openssl passwd -1 PassBudi
  openssl passwd -1 guest
  openssl passwd -1 praktikan1
  openssl passwd -1 praktikan2
  
  touch passwd group
  ```

  `passwd`:
  ```bash
  root:$1$G/Q2ESqP$0bWAnagAHaUuEWlhwvQYl/:0:0:root:/root:/bin/sh 
  Budiman:$1$S4THyjtH$gTB8Ei2Z3JfXVWnoC4.FQ0:1001:100:Budiman:/home/Budiman:/bin/sh 
  guest:$1$NARO6Ily$f/40p/3e2F.zuN4R0gTX40:1002:100:guest:/home/guest:/bin/sh 
  praktikan1:$1$jACzsxt6$WoiURg3Fq1wPYO38FA8Nr0:1003:100:praktikan1:/home/praktikan1:/bin/sh
  praktikan2:$1$ckT.unjX$tJiHF0Jxg0q3UchSWCuFI0:1004:100:praktikan2:/home/praktikan2:/bin/sh 
  ```

  `group`:
  ```bash
  root:x:0
  bin:x:1:root
  sys:x:2:root
  tty:x:5:root,Budiman,guest,praktikan1,praktikan2
  disk:x:6:root
  wheel:x:10:root,Budiman,guest,praktikan1,praktikan2
  users:x:100:Budiman,guest,praktikan1,praktikan2
  ```

- **Explanation:**

1. Masuk ke dalam mode superuser
2. Pindah ke direktori `myramdisk/etc`
3. Gunakan `openssl passwd` untuk membuat password yang dienkripsi dengan format `openssl passwd -1 <password>`
4. Pada file `passwd`, tulis format "<namauser>:<passwordyangdienkripsi>:<UID>:<GID>:<namauser>:<direktoriuser>:/bin/sh" untuk setiap user (root wajib UID 0 dan GID 0)
5. Pada file `group`, tambahkan multi user pada bagian `tty`, `wheel`, dan `users`

- **Screenshot:**

  `put your answer here`

### Soal 4

> Dosen meminta Budiman membuat sistem operasi ini memilki **superuser** layaknya sistem operasi pada umumnya. User root yang sudah kamu buat sebelumnya akan digunakan sebagai superuser dalam sistem operasi milik Budiman. Superuser yang dimaksud adalah user dengan otoritas penuh yang dapat mengakses seluruhnya. Akan tetapi user lain tidak boleh memiliki otoritas yang sama. Dengan begitu user-user selain root tidak boleh mengakses `./root`. Buatlah sehingga tiap user selain superuser tidak dapat mengakses `./root`!

> _The lecturer requests that the OS must have a **superuser** just like other operating systems. The root user created earlier will serve as the superuser in Budiman's OS. The superuser should have full authority to access everything. However, other users should not have the same authority. Therefore, users other than root should not be able to access `./root`. Implement this so that non-superuser accounts cannot access `./root`!_

**Answer:**

- **Code:**

  ```
  cd osboot/myramdisk
  chown root:root root
  chmod 700 root
  ```

- **Explanation:**

1. Masuk ke direktori osboot/myramdisk
2. Gunakan command 'chown' untuk mengatur kepemilikan/akses ke direktori tertentu
3. chown root:root root -> mengubah kepemilikan direktori root hanya bisa diakses oleh root
4. chmod 700 root -> memberikan hak (rwx) hanya ke pemilik direktori 
 
- **Screenshot:**

  `put your answer here`

### Soal 5

> Setiap user rencananya akan digunakan oleh satu orang tertentu. **Privasi dan otoritas tiap user** merupakan hal penting. Oleh karena itu, Budiman ingin membuat setiap user hanya bisa mengakses dirinya sendiri dan tidak bisa mengakses user lain. Buatlah sehingga sistem operasi Budiman dalam melakukan hal tersebut!

> _Each user is intended for an individual. **Privacy and authority** for each user are important. Therefore, Budiman wants to ensure that each user can only access their own files and not those of others. Implement this in Budiman's OS!_

**Answer:**

- **Code:**

  ```
  cd osboot/myramdisk/home
  chown -R 1001:100 Budiman
  chmod 700 Budiman
  chown -R 1002:100 guest
  chmod 700 guest
  chown -R 1003:100 praktikan1
  chmod 700 praktikan1
  chown -R 1004:100 praktikan2
  chmod 700 praktikan2
  ```

- **Explanation:**

  '''
  Masuk ke direktori osboot/myramdisk/home, kemudian ubah kepemilikan/akses setiap direktori    sesuai dengan namanya masing-masing. chown -R artinya mengganti kepemilikan secara rekursif (file-file didalam kepemilikannya juga berubah dan bukan cuman direktori nya saja yang berubah). 1001, 1002, 1003, 1004 merupakan PID unik untuk setiap user yang ada pada file passwd di direktori etc. Lalu chmod 700 "user" untuk memberikan hak (rwx) kepada pemilik direktori only.
  '''

- **Screenshot:**

  ` `

### Soal 6

> Dosen Budiman menginginkan sistem operasi yang **stylish**. Budiman memiliki ide untuk membuat sistem operasinya menjadi stylish. Ia meminta kamu untuk menambahkan tampilan sebuah banner yang ditampilkan setelah suatu user login ke dalam sistem operasi Budiman. Banner yang diinginkan Budiman adalah tulisan `"Welcome to OS'25"` dalam bentuk **ASCII Art**. Buatkanlah banner tersebut supaya Budiman senang! (Hint: gunakan text to ASCII Art Generator)

> _Budiman wants a **stylish** operating system. Budiman has an idea to make his OS stylish. He asks you to add a banner that appears after a user logs in. The banner should say `"Welcome to OS'25"` in **ASCII Art**. Use a text to ASCII Art generator to make Budiman happy!_ (Hint: use a text to ASCII Art generator)

**Answer:**

- **Code:**

  ```
  cd osboot/myramdisk/etc
  nano motd
```
 __      __   _                    _          ___  ___ _ ___ ___ 
 \ \    / /__| |__ ___ _ __  ___  | |_ ___   / _ \/ __( )_  ) __|
  \ \/\/ / -_) / _/ _ \ '  \/ -_) |  _/ _ \ | (_) \__ \/ / /|__ \
   \_/\_/\___|_\__\___/_|_|_\___|  \__\___/  \___/|___/ /___|___/

  ```

- **Explanation:**

  ```
  cd osboot/myramdisk/etc untuk pindah ke direktori osboot/myramdisk/etc kemudian nano motd membuat motd yang diisi dengan welcome banner dengan tulisan `"Welcome to OS'25"` dalam bentuk ASCII Art
  ```

- **Screenshot:**

  `put your answer here`

### Soal 7

> Melihat perkembangan sistem operasi milik Budiman, Dosen kagum dengan adanya banner yang telah kamu buat sebelumnya. Kemudian Dosen juga menginginkan sistem operasi Budiman untuk dapat menampilkan **kata sambutan** dengan menyebut nama user yang login. Sambutan yang dimaksud berupa kalimat `"Helloo %USER"` dengan `%USER` merupakan nama user yang sedang menggunakan sistem operasi. Kalimat sambutan ini ditampilkan setelah user login dan setelah banner. Budiman kembali lagi meminta bantuanmu dalam menambahkan fitur ini.

> _Seeing the progress of Budiman's OS, the lecturer is impressed with the banner you created. The lecturer also wants the OS to display a **greeting message** that includes the name of the user who logs in. The greeting should say `"Helloo %USER"` where `%USER` is the name of the user currently using the OS. This greeting should be displayed after user login and after the banner. Budiman asks for your help again to add this feature._

**Answer:**

- **Code:**

  ```
   cd osboot/myramdisk/etc
   nano profile
  
   echo "Helloo $USER"

  ```

- **Explanation:**

  ```
  masuk direktori osboot/myramdisk/etc, kemudian buat dan isi profile dengan echo "Helloo $USER"
  ```

- **Screenshot:**

  `put your answer here`

### Soal 8

> Dosen Budiman sudah tua sekali, sehingga beliau memiliki kesulitan untuk melihat tampilan terminal default. Budiman menginisiatif untuk membuat tampilan sistem operasi menjadi seperti terminal milikmu. Modifikasilah sistem operasi Budiman menjadi menggunakan tampilan terminal kalian.

> _Budiman's lecturer is quite old and has difficulty seeing the default terminal display. Budiman takes the initiative to make the OS look like your terminal. Modify Budiman's OS to use your terminal appearance!_

**Answer:**

- **Code:**

```
cd osboot/myramdisk/etc
nano profile

#!/bin/sh

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RESET='\033[0m'

printf "\nHelloo ${GREEN}%s${RESET}\n\n" "$(whoami)"

export PS1="${GREEN}\u@\h${RESET}:${BLUE}\w${RESET}\$ "

alias ls='ls --color=auto'
export LS_COLORS='di=34:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=37;41:sg=30;43:tw=30;42:ow=34;42'

  ```

- **Explanation:**

  ```
masuk direktori osboot/myramdisk/etc, kemudian mengubah isi profile dengan
  ```

#!/bin/sh

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RESET='\033[0m'
```
Ini variabel yang menyimpan kode warna ANSI untuk terminal.
GREEN = warna hijau,
BLUE = warna biru,
RESET = reset warna ke default.
Digunakan untuk memberi warna pada teks yang ditampilkan di terminal.


```
printf "\nHelloo ${GREEN}%s${RESET}\n\n" "$(whoami)"
```
Ini mencetak pesan ke terminal: Helloo [nama user].
${GREEN} membuat nama user berwarna hijau.
$(whoami) menjalankan perintah whoami yang outputnya nama user yang sedang login.
printf bisa format warna dan format string.


```
export PS1="${GREEN}\u@\h${RESET}:${BLUE}\w${RESET}\$ "
```
PS1 adalah prompt string 1. Teks yang muncul sebagai prompt terminal
Variabel ini mengatur warna prompt:
${GREEN}\u@\h${RESET}, username dan hostname berwarna hijau,
:${BLUE}\w${RESET} → tanda ":" dan path direktori kerja saat ini berwarna biru,
\$ → karakter $ (untuk user biasa) atau # (untuk root) tanpa warna.


```
alias ls='ls --color=auto'
```
Membuat alias untuk perintah ls agar otomatis menggunakan opsi --color=auto.
Jadi saat mengetik ls, hasil listing file dan folder akan berwarna sesuai tipe file


```
export LS_COLORS='di=34:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=37;41:sg=30;43:tw=30;42:ow=34;42'
```
LS_COLORS adalah variabel environment yang mengatur warna spesifik untuk tipe file saat ls --color dijalankan.



- **Screenshot:**

  `put your answer here`

### Soal 9

> Ketika mencoba sistem operasi buatanmu, Budiman tidak bisa mengubah text file menggunakan text editor. Budiman pun menyadari bahwa dalam sistem operasi yang kamu buat tidak memiliki text editor. Budimanpun menyuruhmu untuk menambahkan **binary** yang telah disiapkan sebelumnya ke dalam sistem operasinya. Buatlah sehingga sistem operasi Budiman memiliki **binary text editor** yang telah disiapkan!

> _When trying your OS, Budiman cannot edit text files using a text editor. He realizes that the OS you created does not have a text editor. Budiman asks you to add the prepared **binary** into his OS. Make sure Budiman's OS has the prepared **text editor binary**!_

**Answer:**

- **Code:**

```
cd home
git clone https://github.com/morisab/budiman-text-editor.git
cd osboot
g++ -static ../budiman-text-editor/main.cpp -o myramdisk/bin/budiman

```

- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

### Soal 10

> Setelah seluruh fitur yang diminta Dosen dipenuhi dalam sistem operasi Budiman, sudah waktunya Budiman mengumpulkan tugasnya ini ke Dosen. Akan tetapi, Dosen Budiman tidak mau menerima pengumpulan selain dalam bentuk **.iso**. Untuk terakhir kalinya, Budiman meminta tolong kepadamu untuk mengubah seluruh konfigurasi sistem operasi yang telah kamu buat menjadi sebuah **file .iso**.

> After all the features requested by the lecturer have been implemented in Budiman's OS, it's time for Budiman to submit his assignment. However, Budiman's lecturer only accepts submissions in the form of **.iso** files. For the last time, Budiman asks for your help to convert the entire configuration of the OS you created into a **.iso file**.

**Answer:**

- **Code:**

```
cd osboot
mkdir -p mylinuxiso/boot/grub
cp bzImage mylinuxiso/boot
cp myramdisk.gz mylinuxiso/boot
nano mylinuxiso/boot/grub grub.cfg
```

Lalu isi file dengan
```
set timeout=5
set default=0

menuentry "MyLinux" {
  linux /boot/bzImage
  initrd /boot/myramdisk.gz
}
```

Lanjutkan dengan menjalankan command ini di direktori osboot
```
grub-mkrescue -o mylinux.iso mylinuxiso
```


- **Explanation:**

  `put your answer here`

- **Screenshot:**

  `put your answer here`

---

Pada akhirnya sistem operasi Budiman yang telah kamu buat dengan susah payah dikumpulkan ke Dosen mengatasnamakan Budiman. Kamu tidak diberikan credit apapun. Budiman pun tidak memberikan kata terimakasih kepadamu. Kamupun kecewa tetapi setidaknya kamu telah belajar untuk menjadi pembuat sistem operasi sederhana yang andal. Selamat!

_At last, the OS you painstakingly created was submitted to the lecturer under Budiman's name. You received no credit. Budiman didn't even thank you. You feel disappointed, but at least you've learned to become a reliable creator of simple operating systems. Congratulations!_
