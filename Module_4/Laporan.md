|    NRP     |      Name      |
| :--------: | :------------: |
| 5025241138 | William Hans Chandra |
| 5025241145 | Lyonel Oliver Dwiputra |
| 5025241147 | Lucky Himawan Prasetya |
| 5025241161 | Muh. Aqil Alqadri Syahid |

</div>

- [Task 4 - Proxy Terbaik di New Eridu _(Best Proxy in New Eridu)_](/task-4/)

### Laporan Resmi Praktikum Modul 4 _(Module 4 Lab Work Report)_

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
