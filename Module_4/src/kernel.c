#include "std_lib.h"
#include "kernel.h"

void executeCommand(char* command);
void handlePipeCommands(char* command);
int grepPattern(char* text, char* pattern);
void wordCount(char* text);
void printString(char* str);
void readString(char* buf);
void clearScreen();
void printChar(char c);
void printNumber(int num);

int main() {
    char buf[128];
    int i;

    clearScreen();
    printString("LilHabOS - C12\n\r");

    while (1) {
        printString("$> ");
        readString(buf);
        printString("\r");

        if (strlen(buf) > 0) {
            if (strstr(buf, "|") != 0) {
                handlePipeCommands(buf);
            } else {
                executeCommand(buf);
            }
        }
    }
}

void handlePipeCommands(char* command) {
    char cmd1[64];
    char cmd2[64];
    char pipeBuffer[128];
    int i = 0;
    int j;

    for (i = 0; i < 128; i++) {
        pipeBuffer[i] = 0;
    }
    i = 0;

    while (command[i] != '|' && command[i] != '\0') {
        cmd1[i] = command[i];
        i++;
    }
    cmd1[i] = '\0';

    if (command[i] == '|') {
        i++;
        while (command[i] == ' ') {
            i++;
        }

        j = 0;
        while (command[i] != '\0') {
            cmd2[j++] = command[i++];
        }
        cmd2[j] = '\0';
    } 
    else {
        cmd2[0] = '\0';
    }

    if (strstr(cmd1, "echo") != 0) {
        char* echoArg = strstr(cmd1, "echo");
        if (echoArg != 0) {
            echoArg += 4;
            while (*echoArg == ' ') {
                echoArg++;
            }
            strcpy(echoArg, pipeBuffer);
        }
    }

    if (strstr(cmd2, "grep") != 0) {
        char* grepArg = strstr(cmd2, "grep");
        if (grepArg != 0) {
            grepArg += 4;
            while (*grepArg == ' ') grepArg++;
            if (grepPattern(pipeBuffer, grepArg)) {
                printString(grepArg);
                printString("\n\r");
            } 
            else {
                printString("NULL\n\r");
            }
        }
    }
    else if (strstr(cmd2, "wc") != 0) {
        wordCount(pipeBuffer);
    }
}

void wordCount(char* text) {
    int lines = 1;
    int words = 0;
    int chars = 0;
    int inWord = 0;
    int i;

    if (strlen(text) == 0) {
        printString("0 0 0\n\r");
        return;
    }

    for (i = 0; text[i] != '\0'; i++) {
        chars++;
        
        if (text[i] == '\n') {
            lines++;
        }
        
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
            if (inWord) {
                words++;
                inWord = 0;
            }
        } 
        else {
            inWord = 1;
        }
    }
    
    if (inWord) {
        words++;
    }
    
    printNumber(lines);
    printString(" ");
    printNumber(words);
    printString(" ");
    printNumber(chars);
    printString("\n\r");
}

void printNumber(int num) {
    char buffer[16];
    itoa(num, buffer);
    printString(buffer);
}

int grepPattern(char* text, char* pattern) {
    return strstr(text, pattern) != 0;
}

void executeCommand(char* command) {
    char cmd_name[32];
    char args[96];
    int i = 0;
    int j;

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
    } 
    else {
        args[0] = '\0';
    }

    if (strcmp(cmd_name, "echo")) {
        printString(args);
        printString("\n\r");
    }
}

void printString(char* str) {
    while (*str != '\0') {
        printChar(*str);
        str++;
    }
}

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

void clearScreen() {
    interrupt(0x10, 0x0600, 0x0700, 0, 0x184F);
    interrupt(0x10, 0x0200, 0, 0, 0);
}

void printChar(char c) {
    interrupt(0x10, 0x0E00 | c, 0, 0, 0);
}
