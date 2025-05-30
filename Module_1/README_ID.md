[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Ph837wyE)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025241138 | William Hans Chandra |
| 5025241145 | Lyonel Oliver Dwiputra |
| 5025241147 | Lucky Himawan Prasetya |
| 5025241161 | Muh. Aqil Alqadri Syahid |


# Praktikum Modul 1 _(Module 1 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - New Jeans Global Teratas _(Top Global New Jeans)_](/task-1/)

- [Task 2 - Liburan Bersama Rudi _(Holiday with Rudi)_](/task-2/)

- [Task 3 - Ignatius Si Cloud Engineer _(Ignatius The Cloud Engineer)_](/task-3/)

- [Task 4 - Proxy Terbaik di New Eridu _(Best Proxy in New Eridu)_](/task-4/)

### Laporan Resmi Praktikum Modul 1 _(Module 1 Lab Work Report)_

#### Task 1

##### a. Code:
```sh
#!/bin/bash

cd ~/Downloads

unzip newjeans_analysis.zip
cd newjeans_analysis

awk -F, '$2 ~ /[2]/ && $2 !~ /_/ {print $2}' DataStreamer.csv | sort | uniq -c | awk '{print $2} {total += $1} END {print "Total:", total}'
```

##### Hasil:
![WhatsApp Image 2025-03-26 at 15 25 14_f305bdb4](https://github.com/user-attachments/assets/ef17c31b-4aad-496c-a3af-3da369081535)
![WhatsApp Image 2025-03-26 at 15 25 56_2454d65b](https://github.com/user-attachments/assets/17dc55d0-a96a-4f53-9796-0b0b54a072f4)
![WhatsApp Image 2025-03-26 at 15 26 20_5849084f](https://github.com/user-attachments/assets/308ad222-1305-4c60-9809-2237c4628fbc)
![WhatsApp Image 2025-03-26 at 15 26 38_eb65a6a9](https://github.com/user-attachments/assets/c41b57e0-021d-4458-9ebf-7c1e7b2c90e5)
![WhatsApp Image 2025-03-26 at 15 27 16_7adfdc27](https://github.com/user-attachments/assets/6b784979-d050-4c81-9d50-3b5f02cde3d6)

##### Cara Pengerjaan:
File diekstrak kemudian di akses agar bisa digunakan. Kemudian menggunakan perintah awk untuk memproses/mencari data dengan kondisi-kondisi
yang ada di soal, $2 ~ /[2]/ → memeriksa apakah kolom kedua mengandung angka 2 di dalamnya
$2 !~ /_/ → memastikan bahwa kolom kedua tidak mengandung karakter _ (underscore)
lalu di sort berdasarkan abjad ASCII dan dihitung yang uniq alias tidak double/sama, lalu ditampilkan dengan variabel Total

##### b. Code:
```sh
#!/bin/bash

cd ~/Downloads

unzip newjeans_analysis.zip
cd newjeans_analysis

most_streamed=$(awk -F, '$2 ~ /[0-9]/ {print $3}' DataStreamer.csv | sort | uniq -c | sort -nr | head -n 1)

jumlah=$(echo "$most_streamed" | awk '{print $1}')

echo $most_streamed

if [ "$jumlah" -lt 24 ] 
then
  echo "Maaf, Minji, total streamingnya tidak sesuai harapan :("
else
  echo "Keren, Minji! Kamu hebat <3!"
fi
```

##### Hasil:
![WhatsApp Image 2025-03-26 at 15 27 51_4ae3d61d](https://github.com/user-attachments/assets/29c3e7e0-31ba-4bed-b9e4-e55de6342f23)

##### Cara Pengerjaan:
Kurang lebih sama seperti soal a, variabel most_streamed untuk mencari lagu terpopuler dengan kondisi-kondisi sesuai soal seperti user mengandung angka,
kemudian di sort lalu uniqnya di count, dan di urutkan lagi secara descending (terbesar diatas) dan mengambil nilai yang paling atas saja.
Lalu variabel jumlah digunakan untuk menghitung berapa yang mendengar lagu tersebut. Terakhir ada percabangan dengan kondisi jika kurang dari 24 akan ngeprint
pesan yang tertera, jika sebaliknya maka ngeprint pesan di baris selanjutnya.

##### c. Code:
```sh
#!/bin/bash

cd ~/Downloads

unzip newjeans_analysis.zip
cd newjeans_analysis

most_streamed=$(awk -F, '$2 ~ /[0-9]/{print $3}' DataStreamer.csv | sort | uniq -c | sort -nr | head -n 1 | awk '{$1=$1};1')

jumlah=$(echo "$most_streamed" | awk '{print $1}')

nama_lagu=$(echo "$most_streamed" | awk '{$1=""; print $0}' | sed 's/^ //')

album_info=$(sed -n "/,$nama_lagu,/p" AlbumDetails.csv | awk -F, '{print $1, $3}')

echo "$nama_lagu $jumlah"
echo "$album_info"
```

##### Hasil:
![WhatsApp Image 2025-03-26 at 15 28 16_135d031a](https://github.com/user-attachments/assets/6360bafc-b251-40f6-aec2-fdf54bb7e07f)

##### Cara Pengerjaan:
Soal ini sama dengan soal sebelumnya, namun dengan tambahan untuk mencari album dari si lagu tersebut. Disini ada tambahan variabel nama_lagu
yang digunakan untuk mengambil nama lagu yang ada divariabel most_streamed, {$1=""; print $0} digunakan untuk menghapus jumlah streaming dan 
menampilkan nama lagunya saja. Lalu ada variabel album_info untuk menampilkan nama album dari lagu yang dimaksud dan tahun rilisnya.

##### d. Code:
```sh
#!/bin/bash

cd ~/Downloads

unzip newjeans_analysis.zip
cd newjeans_analysis

awk -F, '
NR > 1 {
    gsub(/^ +| +$/, "", $7)
        sub(/\r$/, "", $7)
        total_durasi[$7] += $4
        user_per_device[$7 "-" $2] = 1
}

END {
    for (key in user_per_device) {
        split(key, arr, "-")
        dev = arr[1]
        unique_user[dev]++
    }
    user_terbanyak = -1
    durasi_tertinggi = -1
    rasio_loyal = -1

    printf "%-15s %-10s %-10s\n", "Device", "User", "Total Durasi (detik)"
        for (dev in total_durasi) {
            ratio = total_durasi[dev] / unique_user[dev]
            printf "%-15s %-10d %-10d\n", dev, unique_user[dev], total_durasi[dev]
            if (unique_user[dev] > user_terbanyak) {
                user_terbanyak = unique_user[dev]
                popular_device = dev
            }
            if (total_durasi[dev] > durasi_tertinggi) {
                durasi_tertinggi = total_durasi[dev]
                longest_device = dev
            }
            if (ratio > rasio_loyal) {
                rasio_loyal = ratio
                loyal_device = dev
            }
        }

    printf "\nDevice paling populer : " popular_device " (" user_terbanyak " user)\n"
    printf "Device menang durasi  : " longest_device " (" durasi_tertinggi " detik)\n"
    printf "Device Terloyal       : " loyal_device " (%.2f detik/user)\n", rasio_loyal
}' DataStreamer.csv
```

##### Hasil:
![WhatsApp Image 2025-03-26 at 15 28 41_34da4c15](https://github.com/user-attachments/assets/b9abddee-ae5e-4772-8c23-890d275e63b7)

##### Cara Pengerjaan:
Soal meminta agar menghitung device yang paling populer, durasi terbanyak, dan device terloyal. Fungsi gsub dan sub digunakan untuk merapikan saja kedepannya.
total_durasi[$7] += $4 menjumlahkan durasi streaming berdasarkan tiap device (kolom ke-7). user_per_device[$7 "-" $2] = 1 menyimpan kombinasi unik dari device (kolom ke-7) dan username (kolom ke-2) untuk menghitung jumlah pengguna unik per perangkat. Perulangan pertama melakukan iterasi pada setiap entri dalam user_per_device lalu hasilnya kita menambahkan jumlah user unik untuk jenis perangkat tersebut. Kemudian inisialisasi 3 variabel yang akan dicari.
Untuk looping kedua, digunakan untuk menentukan device terpopuler, terlama, dan terloyal. 
printf "%-15s %-10s %-10s\n", "Device", "User", "Total Durasi (detik)" digunakan untuk mencetak format output yang rapi.
Terakhir untuk tiga percabangan (digunakan untuk mencari tiap-tiap device yang punya user terbanyak, durasi tertinggi, dan terloyal:
Lalu tinggal ditampilkan diakhir outputnya yang "ter" dari tiap-tiap kategori, namun akan ditampilkan juga informasi tentang masing-masing device.

##### Kendala:
Sempat salah mengira bahwasanya output yang ditampilkan hanya yang "ter" dari tiap kategori. Namun, ternyata juga harus menampilkan informasi dari masing-masing
device dan sudah saya ubah di masa revisi.

#### Task 2

##### a. Cara Pengerjaan
Request per IP: Ambil IP ($1), hitung berapa kali muncul, urutkan dari yang terbanyak.

Status Code: Ambil status HTTP ($9), hitung jumlahnya, urutkan dari yang paling sering.

Hasil: Dua daftar (IP & status code) + frekuensinya, terurut descending.

##### Code:
```sh
#!/bin/bash


echo "Total Request yang Dibuat oleh Setiap IP:"
awk '{print $1}' access.log | sort | uniq -c | sort -nr

echo -e "\nJumlah dari Setiap Status Code:"
awk '{print $9}' access.log | sort | uniq -c | sort -nr
```

##### Hasil:
![image](https://github.com/user-attachments/assets/26885c07-490a-4858-9888-8ff8fb775a84)

##### b. Cara Pengerjaan
Input: Minta tanggal dan IP (format 192.168.1.X).

Cari Pengguna: Ambil angka terakhir IP (X), cocokkan dengan tanggal di file peminjaman_computer.csv untuk dapat nama pengguna.

Buat Backup Log: Jika pengguna ditemukan, buat file log dengan format:

[timestamp]: method - endpoint - status_code

(data diambil dari access.log yang sesuai dengan IP dan tanggal).

Output: Jika ada: "Pengguna saat itu adalah [nama]" + file log backup.

Jika tidak: "Data tidak ada".

##### Code:
```sh
#!/bin/bash


read -p "Masukkan tanggal (format: MM/DD/YYYY): " tanggal
read -p "Masukkan IP Address (format: 192.168.1.X): " ip


computer=$(echo $ip | awk -F. '{print $4}')

penggunacomputer=$(awk -v tanggal="$tanggal" -v computer="$computer" -F, '
$1 == tanggal && $2 == computer {print $3}
' peminjaman_computer.csv)

if [ -n "$penggunacomputer" ]; then
    echo "Pengguna saat itu adalah $penggunacomputer"
    
    mkdir -p ./backup
    
    timenow=$(date +"%H%M%S")
    convertdate=$(date -d "$tanggal" +"%m%d%Y")
    namafile="./backup/${penggunacomputer}_${convertdate}_${timenow}.log"
    
    tanggallog=$(date -d "$tanggal" +"%d/%b/%Y")
    
    grep "^$ip" access.log | grep "$tanggallog" | while read -r baris; do
        method=$(echo "$baris" | awk -F'"' '{print $2}' | awk '{print $1}')
        endpoint=$(echo "$baris" | awk -F'"' '{print $2}' | awk '{print $2}')
        statuscode=$(echo "$baris" | awk '{print $9}')
        
        timestamp=$(echo "$baris" | awk -F'[' '{print $2}' | awk -F']' '{print $1}')
        
        echo "[$timestamp]: $method - $endpoint - $statuscode" >> "$namafile"
    done
    
    echo "Log Aktivitas $penggunacomputer"
else
    echo "Data yang kamu cari tidak ada"
fi
```

##### Hasil:
![image](https://github.com/user-attachments/assets/2be8f1fd-0ec8-4877-8e70-af01c4b34e68)

![image](https://github.com/user-attachments/assets/b2648623-55e3-4ffb-aade-bacfad6354d7)

##### c. Cara Pengerjaan:
Ambil Error 500: Filter log (access.log) untuk status code 500, lalu ekstrak IP dan tanggal.

Konversi format tanggal (contoh: [01/Jan/2023:15:30:45] → 01/01/2023).

Hitung Error per User: Cocokkan tanggal dan IP dengan data peminjaman_computer.csv untuk dapatkan nama pengguna (Andi/Budi/Caca).

Hitung berapa kali setiap user menyebabkan error 500.

Tentukan Pemenang: Bandingkan jumlah error Andi, Budi, dan Caca.

Tampilkan user dengan error 500 terbanyak.

Output:"Pengguna dengan Status Code 500 terbanyak adalah [nama] dengan jumlah [X]."

##### Code:
```sh
#!/bin/bash


tempcount=$(mktemp)
tempdateip=$(mktemp)

grep " 500 " "access.log" | awk '
BEGIN {
    convertmonth["Jan"] = "01";
    convertmonth["Feb"] = "02";
    convertmonth["Mar"] = "03";
    convertmonth["Apr"] = "04";
    convertmonth["May"] = "05";
    convertmonth["Jun"] = "06";
    convertmonth["Jul"] = "07";
    convertmonth["Aug"] = "08";
    convertmonth["Sep"] = "09";
    convertmonth["Oct"] = "10";
    convertmonth["Nov"] = "11";
    convertmonth["Dec"] = "12";
}
{
    ip = $1;
    pdate = $4;
    gsub(/[\[\]]/, "", pdate);
    split(pdate, pdates, ":");
    stringdate = pdates[1];

    split(stringdate, arraydate, "/");
    day = arraydate[1];
    month = convertmonth[arraydate[2]];
    year = arraydate[3];

    mmddyyyy = month "/" day "/" year;

    split(ip, ipparts, ".");
    computer = ipparts[4];

    print mmddyyyy "," computer;
}' | sort > "$tempdateip"

jumlahandi=0
jumlahbudi=0
jumlahcaca=0

declare -A arrayuser

while IFS=, read -r date compy name; do
    if [ "$date" = "Tanggal" ]; then
        continue
    fi
    
    key="${date},${compy}"
    arrayuser["$key"]="$name"
done < "peminjaman_computer.csv"

while IFS=, read -r date compy; do
    key="${date},${compy}"
    user="${arrayuser[$key]}"
    
    if [ -n "$user" ]; then
        case "$user" in
            "Andi")
                jumlahandi=$((jumlahandi + 1))
                ;;
            "Budi")
                jumlahbudi=$((jumlahbudi + 1))
                ;;
            "Caca")
                jumlahcaca=$((jumlahcaca + 1))
                ;;
        esac
    fi
done < "$tempdateip"

rm "$tempdateip" "$tempcount"

if [ "$jumlahandi" -ge "$jumlahbudi" ] && [ "$jumlahandi" -ge "$jumlahcaca" ]; then
    winner="Andi"
    jumlah="$jumlahandi"
elif [ "$jumlahbudi" -ge "$jumlahandi" ] && [ "$jumlahbudi" -ge "$jumlahcaca" ]; then
    winner="Budi"
    jumlah="$jumlahbudi"
else
    winner="Caca"
    jumlah="$jumlahcaca"
fi

echo "Pengguna dengan Status Code 500 terbanyak adalah $winner dengan jumlah $jumlah."
```

##### Hasil:
![image](https://github.com/user-attachments/assets/0f84d6da-929b-4edd-825a-cbcacff64f45)



#### Task 3

##### a. 

#### register.sh:

#### Cara pengerjaan:

Meminta input username dan password

Kalau berhasil register,data pengguna disimpan di /home/$user/cloud_storage/users.txt kalau pengguna berhasil login dengan format username,password

Mencatat log di cloud_log.txt (sukses/gagal) dengan fungsi isilog

Menolak username yang sudah ada dengan cara mengecek username yang sudah ada di users.txt

Mengecek apakah ada user yang sedang login, kalau ada, tidak boleh ada register baru sampai user logout

Kriteria Password:

Minimal 8 karakter

Mengandung setidaknya satu huruf kapital, satu angka, dan satu karakter spesial (misalnya: @, #, $, dll.)

Password tidak boleh sama dengan username

Tidak boleh mengandung kata "cloud" atau "storage"

#### Kode:
```sh
#!/bin/bash
read -p "Username: " username
read -p "Password: " password
user=$(whoami)
mkdir -p "/home/$user/cloud_storage/"
touch "/home/$user/cloud_storage/users.txt" "/home/$user/cloud_storage/cloud_log.txt"

isilog(){
echo "$(date '+%y/%m/%d %H:%M:%S') REGISTER: $1" >> "/home/$user/cloud_storage/cloud_log.txt"
}

if awk -v u="$username" -F, 'tolower($1) == tolower(u)' "/home/$user/cloud_storage/users.txt" | grep -q .; then
echo "ERROR User already exists"
isilog "ERROR User already exists"
exit 1
fi

if grep -q "LOGIN: INFO User .* logged in" "/home/$user/cloud_storage/cloud_log.txt"; then
last_login=$(grep "LOGIN: INFO User .* logged in" "/home/$user/cloud_storage/cloud_log.txt" | tail -n 1)
last_logout=$(grep "LOGOUT: INFO User .* logged out" "/home/$user/cloud_storage/cloud_log.txt" | tail -n 1)

if [[ -z "$last_logout" || "$last_login" > "$last_logout" ]]; then
echo "ERROR Cannot register while a user is logged in"
isilog "ERROR Cannot register while a user is logged in"
exit 1
fi
fi

if tail -n 1 "/home/$user/cloud_storage/cloud_log.txt" | grep -q "LOGIN:INFO User .* logged in"; then
echo "ERROR Cannot register while a user is logged in"
isilog "ERROR Cannot register while a user is logged in"
exit 1
fi

if [[ ${#password} -lt 8 ]]; then
echo "ERROR Password must be at least 8 characters"
isilog "ERROR Password must be at least 8 characters"
exit 1
fi

if [[ ! "$password" =~ [A-Z] ]]; then
echo "ERROR Password must contain an uppercase letter"
isilog "ERROR Password must contain an uppercase letter"
exit 1
fi

if [[ ! "$password" =~ [0-9] ]]; then
echo "ERROR Password must contain a number"
isilog "ERROR Password must contain a number"
exit 1
fi

if [[ ! "$password" =~ [^a-zA-Z0-9] ]]; then
echo "ERROR Password must contain a special character"
isilog "ERROR Password must contain a special character"
exit 1
fi

if [[ "$password" == "$username" ]]; then
echo "ERROR Password cannot be the same as username"
isilog "ERROR Password cannot be the same as username"
exit 1
fi

if [[ "$password" =~ cloud || "$password" =~ storage ]]; then
isilog "ERROR Password cannot contain 'cloud' or 'storage'"
echo "ERROR Password cannot contain 'cloud' or 'storage'"
exit 1
fi

echo "$username,$password" >> "/home/$user/cloud_storage/users.txt"
isilog "INFO User registered successfully"
echo "Registered"
```




login.sh:

Memproses login dan logout pengguna

Memeriksa apakah ada pengguna yang login dengan cara membandingkan waktu login terakhir di cloud_log.txt dengan waktu logout terakhir di cloud_log.txt

Cek apakah username ada di users.txt, kalau ada, cek apakah password yang diinput sama dengan password di users.txt

Mencatat log di cloud_log.txt dengan fungsi log

Jika login berhasil, sistem menjalankan crontab

Kode:
```sh
#!/bin/bash

log() {
echo "$(date '+%y/%m/%d %H:%M:%S') $1"
echo "$(date '+%y/%m/%d %H:%M:%S') $1" >> "/home/$user/cloud_storage/cloud_log.txt"
}
user=$(whoami)
login() {
read -p "Enter username: " username
read -p "Enter password: " password

pwlama=$(awk -F',' -v user="$username" '$1 == user {print $2}' "/home/$user/cloud_storage/users.txt")

if [[ -n "$pwlama" ]]; then
if [[ "$pwlama" == "$password" ]]; then

if grep -q "LOGIN: INFO User .* logged in" "/home/$user/cloud_storage/cloud_log.txt"; then

login1=$(grep "LOGIN: INFO User .* logged in" "/home/$user/cloud_storage/cloud_log.txt" | tail -n 1)
logout1=$(grep "LOGOUT: INFO User .* logged out" "/home/$user/cloud_storage/cloud_log.txt" | tail -n 1)

if [[ -z "$logout1" || "$login1" > "$logout1" ]]; then
log "LOGIN: ERROR Another user is currently logged in"
exit 1
fi
fi

crontab -l > "/home/$user/cloud_storage/crontabs"
crontab "/home/$user/cloud_storage/crontabs"

log "LOGIN: INFO User $username logged in"

else
log "LOGIN: ERROR Failed login attempt on user $username"
fi
else
log "LOGIN: ERROR User $username not found"
fi
}

logout() {
read -p "Enter username to logout: " username
if grep -q "LOGIN: INFO User $username" "/home/$user/cloud_storage/cloud_log.txt"; then
log "LOGOUT: INFO User $username logged out"
else
log "LOGOUT: ERROR User $username is not logged in"
fi
}

while true; do
echo "1. Login"
echo "2. Logout"
echo "3. Exit"
read -p "Choose an option: " option
case $option in
1) login ;;
2) logout ;;
3) break ;;
*) echo "ERROR Invalid option" ;;
esac
done
```
##### Hasil:
![WhatsApp Image 2025-03-26 at 18 25 12](https://github.com/user-attachments/assets/f3e2b0f1-7f2b-446e-b123-994bb9fa4ec7)

![WhatsApp Image 2025-03-26 at 18 27 37](https://github.com/user-attachments/assets/5795d557-13a5-46f0-9f01-48ea3ea65415)

![WhatsApp Image 2025-03-26 at 19 32 59](https://github.com/user-attachments/assets/51c4fe23-18e5-4395-8009-5ecf7e0d21ec)


##### b.
automation.sh:

Memeriksa apakah ada pengguna yang login dengan cara membandingkan waktu login terakhir di cloud_log.txt dengan waktu logout terakhir di cloud_log.txt

Jika ada pengguna aktif, biarkan crontab menyala

Jika pengguna logout, hentikan crontab

Kode:
```sh
#!/bin/bash

if grep -q "LOGIN: INFO User .* logged in" "/home/$USER/cloud_storage/cloud_log.txt"; then
login1=$(grep "LOGIN: INFO User .* logged in" "/home/$USER/cloud_storage/cloud_log.txt" | tail -n 1)
logout1=$(grep "LOGOUT: INFO User .* logged out" "/home/$USER/cloud_storage/cloud_log.txt" | tail -n 1)
if [[ -z "$logout1" || "$login1" > "$logout1" ]]; then
:
else
crontab -r
fi
else
crontab -r
fi

```

#### download.sh:

Membuat direktori penyimpanan jika belum ada

Mengunduh gambar alam secara acak dari 15 pilihan

Menyimpan gambar di /home/$user/cloud_storage/downloads/{USERNAME}/ dengan format nama:
HH-MM_DD-MM-YYYY.{ext} (contoh: 14-20_12-03-2025.jpg)

Berjalan otomatis setiap 10 menit menggunakan crontab

#### Kode:
```sh
#!/bin/bash

images=(
"https://media.istockphoto.com/id/471926619/id/foto/danau-moraine-saat-matahari-terbit-taman-nasional-banff-kanada.jpg?s=612x612&w=0&k=20&c=gTd7AEpKl3mHR_TCiyPSoG8JIiHEKg9NnhhHzNMAA1s="
"https://media.istockphoto.com/id/1161610609/id/foto/matahari-terbit-yang-indah-di-atas-laut.jpg?s=612x612&w=0&k=20&c=c5_d6b67GuSGP3w7LNJhALvOLgDVEVF5WH83oi5Ep5M="
"https://media.istockphoto.com/id/483724081/id/foto/yosemite-valley-landscape-and-river-california.jpg?s=612x612&w=0&k=20&c=tkTsD-xo5kKZexa-qoLwLFgilFRR5xpafDP367yHtRI="
"https://media.istockphoto.com/id/495508534/id/foto/pemandangan-udara-di-hutan-pinus-yang-luas-saat-matahari-terbit.jpg?s=612x612&w=0&k=20&c=BjvKAzVfWnEQ6JOwAgsqNPKwJ4gEax5E4L1IzPWJLo8="
"https://media.istockphoto.com/id/483076291/id/foto/hari-di-laut.jpg?s=612x612&w=0&k=20&c=63SIYJBuLRUe1Kn_Y44K8_spboWdaJjD95bgvDPrJ_Y="
"https://media.istockphoto.com/id/1168009842/id/foto/latar-belakang-udara-hutan-musim-gugur-campuran-berwarna-warni-dibuat-langsung-dari-atas.jpg?s=612x612&w=0&k=20&c=eUabVYYbgklXHNIC8R7URF2v3Sq7QauXvqUjrXImBPw="
"https://media.istockphoto.com/id/1696167872/id/foto/pemandangan-udara-hutan-saat-matahari-terbenam-dengan-latar-belakang-pegunungan-di-dolomites.jpg?s=612x612&w=0&k=20&c=iXJCimSdu1suE6RtA6Jf_6MysbIu_JubVdTpnxLvh98="
"https://media.istockphoto.com/id/1255610084/id/foto/ladang-lavender-tanpa-akhir-di-provence-prancis.jpg?s=612x612&w=0&k=20&c=3TKJAz6l-2mLuiUsAP5RR3XaGih6vdVmB1UKDXYORZM="
"https://media.istockphoto.com/id/1900503626/id/foto/matahari-terbenam-di-lupin-liar-dekat-mt-cook-selandia-baru.jpg?s=612x612&w=0&k=20&c=qxldBCpPDa5cJNCNjYhzfDdoEd5D2dG48z80jBFrCxo="
"https://media.istockphoto.com/id/935746242/id/foto/mata-atlantica-hutan-atlantik-di-brasil.jpg?s=612x612&w=0&k=20&c=xeqZsDGq3X7Rkke9JisTuMkF7Kc7tn1Woc1x9O18evI="
"https://media.istockphoto.com/id/526705622/id/foto/pegunungan-karst-dan-sungai-li-di-wilayah-guilin-guangxi-cina.jpg?s=612x612&w=0&k=20&c=tgDFeHrXxvuVMgsV77xFyAI9ZT5YSlKJnOqYjW95WEQ="
"https://media.istockphoto.com/id/1176527951/id/foto/matahari-terbit-lengkung-mesa.jpg?s=612x612&w=0&k=20&c=jUJp6fYJ2yBBTbfrTZXLp2UPWLmbktoXswKTO0ciO0Q="
"https://media.istockphoto.com/id/170464921/id/foto/matahari-terbit-yang-indah-di-pegunungan-pagi-berkabut.jpg?s=612x612&w=0&k=20&c=-ZKR7CfVIyRKNVkJGpzu-bmreJfuziP66K06yKgEv3M="
"https://media.istockphoto.com/id/108327817/id/foto/danau-plansee-tirol-austria.jpg?s=612x612&w=0&k=20&c=uV5bE60fIBLdMp89e3UBxnbL8bHLRH6EB9t4du-BhJ0="
)

LOGIN_USER=$(grep "LOGIN: INFO User" "/home/$USER/cloud_storage/cloud_log.txt" | tail -1 | awk -F'User ' '{print $2}' | awk '{print $1}')
DOWNLOAD_DIR="/home/$USER/cloud_storage/downloads/$LOGIN_USER"
mkdir -p "$DOWNLOAD_DIR"

filename="$DOWNLOAD_DIR/$(date '+%s-%H-%M_%d-%m-%Y').jpg" 
random_image="${images[$RANDOM % ${#images[@]}]}"
wget -q -O "$filename" "$random_image"
```


#### crontab:

Menjalankan automation.sh setiap 2 menit

Menjalankan donwload.sh setiap 10 menit

Menjalankan archive.sh setiap 2 jam

#### Kode:
```sh
*/2 * * * * /home/$USER/cloud_storage/automation.sh
*/10 * * * * /home/$USER/cloud_storage/download.sh 
0 */2 * * * /home/$USER/cloud_storage/archive.sh
```
##### Hasil:
![WhatsApp Image 2025-03-27 at 12 23 33](https://github.com/user-attachments/assets/1bcec934-a29a-466c-ae33-10f6a2219a80)

##### c.
archive.sh:

Dijalankan otomatis setiap 2 jam dengan crontab

Mengarsipkan semua gambar di folder /home/$user/cloud_storage/downloads/{USERNAME}/ ke ZIP di:
/home/$user/cloud_storage/archives/{USERNAME}/archive_HH-DD-MM-YYYY.zip

Menghapus semua file di folder  /home/$user/cloud_storage/downloads/{USERNAME} setelah di-zip

Kode:
```sh
#!/bin/bash
LOGIN_USER=$(grep "LOGIN: INFO User" "/home/$USER/cloud_storage/cloud_log.txt" | tail -1 | awk -F'User ' '{print $2}' | awk '{print $1}')
download_dir="/home/$USER/cloud_storage/downloads/$LOGIN_USER"
archive_dir="/home/$USER/cloud_storage/archives/$LOGIN_USER"
mkdir -p "$archive_dir"
if [ -n "$(ls -A "$download_dir" 2>/dev/null)" ]; then
timestamp=$(date '+%Y%m%d_%H%M%S')
archive_file="$archive_dir/archive_$timestamp.zip"
zip -j "$archive_file" "$download_dir"/*
rm -f "$download_dir"/*
fi
``` 

##### Hasil:
![WhatsApp Image 2025-03-27 at 12 23 31](https://github.com/user-attachments/assets/9e67a09f-f719-43e9-86c7-3cc888eaf8f5)


#### Task 4

#### minute5_log.sh

#### Cara Pengerjaan

- Membuat file script yang berjalan tiap 5 menit untuk membuat file log yang bernama metrics_{YmdHms}.log
- File log berisi total penggunaan RAM pada saat script itu dijalankan.
- File log tersebut dimasukkan ke dalam folder metrics dan hanya dapat diakses oleh admin

#### Kode
```sh
#!/bin/bash

file_name="metrics_$(date +%Y%m%d%H%M%S).log"	
touch "$file_name"
echo "mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" >> "$file_name"
free -m | awk 'NR==2 {printf "%s,%s,%s,%s,%s,%s,", $2,$3,$4,$5,$6,$7} NR==3 {printf "%s,%s,%s,", $2,$3,$4}' >> "$file_name"
echo -n "$(pwd)," >> "$file_name"
du -sh $(pwd) | awk '{print $1}' >> "$file_name"
chmod 200 "$file_name"
mv "$file_name" "/home/$USER/metrics"
```

#### Hasil

![min5](https://github.com/user-attachments/assets/1a184cc6-9d7c-4707-bf05-5165cf777da1)

#### agg_5min_to_hour.sh

#### Cara Pengerjaan

- Membuat file script yang berjalan setiap 1 jam untuk membuat file log yang bernama metrics_agg_{YmdH}.log.
- File log berisi nilai minimum, maksimum, dan rata-rata penggunaan RAM.
- Nilai minimim, maksimum, dan rata-rata penggunaan ram diambil dari file metrics yang telah dibuat dalam satu jam sebelum script ini dijalankan
- File log tersebut dimasukkan ke dalam folder metrics dan hanya dapat diakses oleh admin.

#### Kode
```sh
#!/bin/bash

file_name="metrics_agg_$(date +%Y%m%d%H).log"
touch "$file_name"

declare -a min max sum count
first_file=true

min_size=999999999
max_size=0
sum_size_mb=0
count_size=0

for file in $(find "$(pwd)/metrics/" -name "metrics_*" -mmin -60); do
    if [[ $file == metrics_agg_* ]]; then
        continue
    fi
    line=$(awk 'NR==2' "$file")
    if [[ -n "$line" ]]; then
        IFS=, read value1 value2 value3 value4 value5 value6 value7 value8 value9 value10 value11 <<< "$line"
        values=($value1 $value2 $value3 $value4 $value5 $value6 $value7 $value8 $value9)
        if [[ "$first_file" == true ]]; then
            for i in {0..8}; do
                min[$i]=${values[$i]}
                max[$i]=${values[$i]}
                sum[$i]=${values[$i]}
            done
            first_file=false
        else
            for i in {0..8}; do
                if [[ ${values[$i]} -lt ${min[$i]} ]]; then
                    min[$i]=${values[$i]}
                fi
                if [[ ${values[$i]} -gt ${max[$i]} ]]; then
                    max[$i]=${values[$i]}
                fi
                sum[$i]=$((${sum[$i]} + ${values[$i]}))
            done
        fi

        numeric_part=$(echo "$value11" | grep -o '[0-9]\+')
        unit=$(echo "$value11" | grep -o '[KMG]')

        if [[ -n "$numeric_part" && -n "$unit" ]]; then
            if [[ "$unit" == "K" ]]; then
                size_mb=$(echo "scale=1; $numeric_part / 1024" | bc)
            elif [[ "$unit" == "G" ]]; then
                size_mb=$(echo "scale=1; $numeric_part * 1024" | bc)
            else
                size_mb=$numeric_part
            fi

            if [[ "$numeric_part" -lt "$min_size" ]]; then
                min_size=$numeric_part
                min_unit=$unit
            fi
            if [[ "$numeric_part" -gt "$max_size" ]]; then
                max_size=$numeric_part
                max_unit=$unit
            fi

            sum_size_mb=$(echo "scale=1; $sum_size_mb + $size_mb" | bc)
            count_size=$((count_size + 1))
        fi
    fi
done

average_size_mb=$(echo "scale=1; $sum_size_mb / $count_size" | bc)
average_size_mb=$(LC_NUMERIC=C printf "%0.1f" "$average_size_mb")

echo "type,mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" >> "$file_name"

echo -n "minimum," >> "$file_name"
for ((i=0; i<9; i++)); do
   printf "%d," "${min[$i]}" >> "$file_name"
done
echo -n "$(pwd)/metrics," >> "$file_name"
echo -n "$min_size" >> "$file_name"
echo -n "$min_unit" >> "$file_name"
echo >> "$file_name"

echo -n "maximum," >> "$file_name"
for ((i=0; i<9; i++)); do
   printf "%d," "${max[$i]}" >> "$file_name"
done
echo -n "$(pwd)/metrics," >> "$file_name"
echo -n "$max_size" >> "$file_name"
echo -n "$max_unit" >> "$file_name"
echo >> "$file_name"

echo -n "average," >> "$file_name"
for ((i=0; i<9; i++)); do
   average=$(echo "scale=1; ${sum[$i]} / $count_size" | bc)
   average=$(LC_NUMERIC=C printf "%0.1f" "$average")
   if [[ $(echo "$average" | grep -E "\.0+$") ]]; then
       printf "%d," "${average%.*}" >> "$file_name"
   else
       LC_NUMERIC=C printf "%0.1f," "$average" >> "$file_name"
   fi
done
echo -n "$(pwd)/metrics," >> "$file_name"
echo -n "$average_size_mb" >> "$file_name"
echo -n "M" >> "$file_name"
echo >> "$file_name"

chmod 200 "$file_name"
mv "$file_name" "/home/$USER/metrics"

```

#### Hasil

![agg](https://github.com/user-attachments/assets/57bc1d6f-3a99-48f8-8dc1-6c48856f37e8)

#### Kendala Pengerjaan

- Pada output rata-rata, angka yang memiliki nilai desimal di belakang kome sama dengan nol harus dioutputkan sebagai bilangan bulat yang terkadang menyebabkan kesulitan dan harus menggunakan perintah seperti berikut
```sh
  if [[ $(echo "$average" | grep -E "\.0+$") ]]; then
       printf "%d," "${average%.*}" >> "$file_name"
   else
       LC_NUMERIC=C printf "%0.1f," "$average" >> "$file_name"
   fi
```

#### uptime_monitor.sh

#### Cara Pengerjaan

- Membuat file script yang berjalan setiap 1 jam untuk membuat file log yang bernama uptime_{YmdH}.log
- File log berisi total uptime dan load average server.
- File log tersebut dimasukkan ke dalam folder metrics dan hanya dapat diakses oleh admin

#### Kode
```sh
#!/bin/bash

file_name="uptime_$(date +%Y%m%d%H).log"
touch "$file_name"
echo "uptime,load_avg_1min,load_avg_5min,load_avg_15min" >> "$file_name"
uptime | awk '{printf "%s %s %s", $1,$2,$3}' >> "$file_name"
cat /proc/loadavg | awk '{printf "%s,%s,%s\n", $1,$2,$3}' >> "$file_name"
chmod 200 "$file_name"
mv "$file_name" "/home/$USER/metrics"
```

#### Hasil

![uptime](https://github.com/user-attachments/assets/e7829c62-6d9b-4cc7-b652-0d71253cc863)

#### cleanup_log.sh

#### Cara Pengerjaan

- Membuat file script yang berjalan setiap jam 00.00 untuk menghapus file log agregasi yang lebih lama dari 12 jam pertama

#### Kode
```sh
#!/bin/bash

find "$(pwd)/metrics" -name "metrics_agg_*.log" -mmin +720 -print -delete
```

#### Hasil

![clean](https://github.com/user-attachments/assets/8a62bd8e-35e5-49fe-bb14-c631b136e511)

#### crontab

#### Cara Pengerjaan

- minute5_log.sh dijalankan setiap 5 menit
- agg_min5_to_hour.sh dijalankan setiap jam
- uptime_log.sh dijalankan setiap jam
- cleanup_log.sh dijalankan setiap jam 00.00

#### Kode
```sh
*/5 * * * * /bin/bash /home/$USER/minute5_log.sh
0 * * * * /bin/bash /home/$USER/agg_5min_to_hour.sh
0 * * * * /bin/bash /home/$USER/uptime_log.sh
0 0 * * * /bin/bash /home/$USER/cleanup_log.sh 
```
