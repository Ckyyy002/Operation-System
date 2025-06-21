#### Task 4

#### a. Implementasikan fungsi `printString`, `readString`, dan `clearScreen` di `kernel.c` yang akan menampilkan dan membaca string di layar.

  - `printString`: Menampilkan string yang diakhiri null menggunakan `int 10h` dengan `AH=0x0E`.
  - `readString`: Membaca karakter dari keyboard menggunakan `int 16h` dengan `AH=0x00` sampai Enter ditekan. Termasuk penanganan Backspace dasar.
  - `clearScreen`: Membersihkan layar dan mengatur kursor ke pojok kiri atas `(0, 0)` menggunakan `int 10h` dengan `AH=0x06` dan `AH=0x02`. Buffer video untuk warna karakter akan diubah menjadi putih.

#### Cara Pengerjaan

1. Fungsi printString(char* str)

    - Menggunakan loop while untuk iterasi tiap karakter string
    - Memanggil printChar untuk setiap karakter hingga menemukan null terminator (\0)
    - Menggunakan interrupt 0x10 dengan AH=0x0E (teletype output) melalui printChar

2. Fungsi readString(char* buf)

    - Menggunakan interrupt 0x16 dengan AH=0x00 (keyboard read)
    - Menangani 3 jenis karakter: Enter (\r atau \n) dan Backspace (\b):
    - Mengurangi index buffer
    - Menghapus karakter di layar dengan backspace + spasi + backspace
    - Karakter biasa (ASCII 32-126): Disimpan di buffer dan ditampilkan
    - Batasan buffer maksimal 127 karakter (128 termasuk null terminator)

3. Fungsi clearScreen()

    - Menggunakan dua interrupt 0x10:
    - AH=0x06 (scroll up):
    - AL=0x00 (clear seluruh layar)
    - Atribut 0x07 (warna teks putih di latar hitam)
    - Area layar 0x184F (25x80)
    - AH=0x02 (set cursor position): Pindah ke posisi (0,0) (pojok kiri atas)

#### Kode

printString():
```c
void printChar(char c) {
    interrupt(0x10, 0x0E00 | c, 0, 0, 0);
}

void printString(char* str) {
    while (*str != '\0') {
        printChar(*str);
        str++;
    }
}
```

readString():
```c
void readString(char* buf) {
    int index = 0;
    while (1) {
        int result = interrupt(0x16, 0, 0, 0, 0);
        char ch = result & 0xFF;
        
        if (ch == '\r' || ch == '\n') {
            buf[index] = '\0';
            printChar('\n');
            printChar('\r');
            return;
        } 
        else if (ch == '\b') {
            if (index > 0) {
                index--;
                printChar('\b');
                printChar(' ');
                printChar('\b');
            }
        } 
        else if (ch >= 32 && ch <= 126) {
            if (index < 127) {
                buf[index] = ch;
                index++;
                printChar(ch);
            }
        }
    }
}
```

clearScreen():
```c
void clearScreen() {
    interrupt(0x10, 0x0600, 0x0700, 0, 0x184F);
    interrupt(0x10, 0x0200, 0, 0, 0);
}

```

#### b. Lengkapi implementasi fungsi-fungsi di [`std_lib.h`](./include/std_lib.h) dalam [`std_lib.c`](./src/std_lib.c).

  Fungsi-fungsi di atas dapat digunakan untuk menyederhanakan implementasi fungsi `printString`, `readString`, `clearScreen`, dan fungsi-fungsi lebih lanjut yang dijelaskan pada tugas berikutnya.

#### Cara Pengerjaan

1. Fungsi Matematika Dasar
    a. div(int a, int b)
       Implementasi pembagian integer melalui pengurangan berulang
    b. mod(int a, int b)
        Menghitung sisa pembagian dengan metode pengurangan
2. Fungsi Manipulasi Memori
   a. memcpy(byte* src, byte* dst, unsigned int size)
        Menyalin blok memori byte-per-byte
        Tidak menangani overlapping memory (bukan memmove)
        Parameter size menentukan jumlah byte yang disalin
    b. clear(byte* buf, unsigned int size)
        Mengisi buffer dengan nilai 0 (zero-out)
        Berguna untuk inisialisasi memori
3. Fungsi String
    a. strlen(char* str)
        Menghitung panjang string hingga null terminator
        Tidak termasuk '\0' dalam perhitungan
    b. strcmp(char* str1, char* str2) 
        Return value:
        - 0 jika string sama
        - <0 jika str1 < str2 (lexicographical)
        - 0 jika str1 > str2
    c. strcpy(char* src, char* dst)
        Menyalin string termasuk null terminator
        Tidak menangani buffer overflow (harus dipastikan dst cukup besar)
    d. strstr(char* str, char* find) 
        Mencari substring dalam string
        Mengembalikan pointer ke kemunculan pertama atau NULL
        Implementasi naive string matching (O(n*m))
   e. itoa(int num, char* str) (Tambahan)
        Konversi integer ke string ASCII
        Menangani:
        - Angka negatif (menambahkan '-')
        - Pembalikan digit setelah konversi
        - Kasus khusus untuk angka 0

#### Kode
```c
#include "std_type.h"
#include "std_lib.h"
#include "kernel.h"

int div(int a, int b) {
    int result = 0;
    while (a >= b) {
        a -= b;
        result++;
    }
    return result;
}

int mod(int a, int b) {
    while (a >= b) {
        a -= b;
    }
    return a;
}

void memcpy(byte* src, byte* dst, unsigned int size) {
    unsigned int i;
    for (i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}

void clear(byte* buf, unsigned int size) {
    unsigned int i;
    for (i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

unsigned int strlen(char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

bool strcmp(char* str1, char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (*str1 == *str2);
}

void strcpy(char* src, char* dst) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

char* strstr(char* str, char* find) {
    if (!*find) return str;
    for (; *str; str++) {
        char *h = str, *n = find;
        while (*h && *n && (*h == *n)) {
            h++;
            n++;
        }
        if (!*n) return str;
    }
    return 0;
}

void itoa(int num, char* str) {
    int i;
    int isNegative;
    int start;
    int end;
    char temp;

    i = 0;
    isNegative = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    start = 0;
    end = i - 1;
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

```

#### c. Implementasikan perintah `echo`

  Perintah ini mengambil argumen yang diberikan (karakter keyboard) untuk perintah `echo` dan mencetaknya ke shell.

#### Cara Pengerjaan

- Memisahkan nama command (echo) dan argumennya menggunakan spasi sebagai delimiter
- Mengecek jika command adalah "echo" dengan strcmp. Jika ada argumen, akan dicetak menggunakan printString
- Selalu menambahkan newline (\n\r) di akhir output

#### Kode
```c
void executeCommand(char* command) {
    char cmd_name[32];
    char args[96];
    int i;
    int j;

    i = 0;
    while (command[i] != ' ' && command[i] != '\0') {
        cmd_name[i] = command[i];
        i++;
    }
    cmd_name[i] = '\0';

    if (command[i] == ' ') {
        i++;
        j = 0;
        while (command[i] != '\0') {
            args[j++] = command[i++];
        }
        args[j] = '\0';
    } else {
        args[0] = '\0';
    }

    if (strcmp(cmd_name, "echo") == 0) {\
        if (strlen(args) > 0) {
            printString(args);
        }
        printString("\n\r");
    }
}
```

#### d. Implementasikan perintah `grep`

  Perintah ini mencari baris yang cocok dengan pola dalam inputnya dan mencetak baris yang cocok. `grep` hanya akan mengambil satu argumen menggunakan piping (`|`) dari perintah `echo`. Output harus berupa bagian dari argumen yang di-pipe yang diteruskan ke `grep`. Jika argumen tidak cocok, mengembalikan `NULL`

  Contoh penggunaan:

  ```bash
  $> echo <argument> | grep <argument>

#### Cara Pengerjaan

- grepPattern(): Mengecek apakah pattern ada dalam text menggunakan strstr
- handleGrepCommand(): Menangani output sesuai hasil pencarian
- Output dari echo disimpan di pipeBuffer
- grep membaca dari pipeBuffer dan mencari pattern
- Jika pattern ditemukan, cetak teks asli. Jika tidak ditemukan maka cetak "NULL"

#### Kode
```c
int grepPattern(char* text, char* pattern) {
    if (text == 0 || pattern == 0) return 0;
    
    char* found = strstr(text, pattern);
    return (found != 0);
}

void handleGrepCommand(char* text, char* pattern) {
    if (grepPattern(text, pattern)) {
        printString(text);
        printString("\n\r");
    } else {
        printString("NULL\n\r");
    }
}

void handlePipeCommands(char* command) {
    char cmd1[64];
    char cmd2[64];
    char pipeBuffer[128];

    for(int i = 0; i < 128; i++) {
        pipebuffer[i] = 0;
    }

    if (strstr(cmd2, "grep") != 0) {
        char* grepArg = cmd2 + 4;
        while (*grepArg == ' ') grepArg++;
        handleGrepCommand(pipeBuffer, grepArg);
    }
}
```

#### e. Implementasikan perintah `wc`

  Perintah ini menghitung baris, kata, dan karakter dalam inputnya. `wc` tidak memerlukan argumen karena mendapat input dari pipe (`|`) dari perintah sebelumnya. Output harus berupa hitungan akhir dari argumen yang di-pipe yang diteruskan ke `wc`. Jika argumen tidak cocok, mengembalikan `NULL` atau `0`

  Contoh penggunaan:

  ```bash
  $> echo <argument> | wc
  $> echo <argument> | grep <argument> | wc

#### Cara Pengerjaan

- wordCount(): Menghitung lines, words, dan chars dalam satu pass
- Lines: Diitung setiap newline (\n), minimal 1 jika ada teks
- Words: Diitung berdasarkan spasi/tab/newline
- Chars: Semua karakter termasuk spasi dan newline
- Input kosong → Output "0 0 0"
- Tanpa newline → Tetap dihitung 1 line
- Multiple spaces → Tetap dihitung sebagai 1 word boundary
- Mengikuti format Unix wc: lines words chars

#### Kode
```c
void wordCount(char* text) {
    int lines = 0;
    int words = 0;
    int chars = 0;
    int inWord = 0;
    int i = 0;

    if (text == 0 || strlen(text) == 0) {
        printString("0 0 0\n\r");
        return;
    }

    while (text[i] != '\0') {
        chars++;
        
        if (text[i] == '\n') {
            lines++;
        }
        
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
            if (inWord) {
                words++;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
        i++;
    }
    
    if (inWord) {
        words++;
    }
    
    if (lines == 0 && chars > 0) {
        lines = 1;
    }
    
    printNumber(lines);
    printString(" ");
    printNumber(words);
    printString(" ");
    printNumber(chars);
    printString("\n\r");
}
```

#### f. Buat otomatisasi untuk mengompilasi dengan melengkapi file [`makefile`](./makefile).

  Untuk mengompilasi program, perintah `make build` akan digunakan. Semua hasil program yang dikompilasi akan disimpan di direktori [`bin/`](./bin). Untuk menjalankan program, perintah `make run` akan digunakan.

#### Cara Pengerjaan

- prepare: Membuat direktori bin
- bootloader: Mengompilasi bootloader (NASM binary)
- kernel_asm: Mengompilasi bagian assembly kernel
- stdlib: Mengompilasi library standar
- kernel_c: Mengompilasi kernel C
- link: Melakukan linking dan membuat floppy image
- build: Melakukan semua tahap kompilasi (prepare → bootloader → kernel → link)
- run: Menjalankan kernel di Bochs emulator

#### Kode
```sh
prepare:
	mkdir -p bin

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin
	nasm -f as86 src/kernel.asm -o bin/kernel-asm.o

stdlib:
	bcc -ansi -c -Iinclude src/std_lib.c -o bin/std_lib.o

kernel:
	bcc -ansi -c -Iinclude src/kernel.c -o bin/kernel.o

link:
	ld86 -o bin/kernel.bin -d bin/kernel.o bin/std_lib.o bin/kernel-asm.o /usr/lib/bcc/libc.a
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 count=15 conv=notrunc

build: prepare bootloader stdlib kernel link

run:
	bochs -f bochsrc.txt
```

#### Hasil

