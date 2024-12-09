#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 30000


void a() {
    FILE *f = fopen("09.txt", "r");
    int line[LEN];
    // fgets(line, LEN, f);
    int c;
    int len = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') continue;
        line[len++] = c - '0';
    }

    int fileI = len % 2 ? len - 1 : len - 2;
    int spaceI = 1;

    int r, l;
    int i = line[0];
    long checksum = 0;
    // for (int j = 0; j < i; j++) 
    //     checksum += j * 0;
    while (spaceI < fileI) {
        int s = line[spaceI];
        int f = line[fileI];
        if (s > f) {
            line[spaceI] -= line[fileI];
            for (int j = i; j < i + line[fileI]; j++) {
                checksum += (fileI / 2) * j;
            }
            i += line[fileI];
            fileI -= 2;
        } else {
            line[fileI] -= line[spaceI];
            for (int j = i; j < i + line[spaceI]; j++) {
                checksum += (fileI / 2) * j;
            }
            i += line[spaceI];
            for (int j = i; j < i + line[spaceI+1]; j++) {
                checksum += ((spaceI+1) / 2) * j;
            }
            i += line[spaceI+1];
            spaceI += 2;
        }
    }

    printf("answer %ld\n", checksum);
}

void b() {
    FILE *f = fopen("09.txt", "r");
    int line[LEN];
    int pos[LEN];
    pos[0] = 0;
    int c;
    int len = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') continue;
        line[len++] = c - '0';
        pos[len] = pos[len-1] + (c - '0');
    }

    long checksum = 0;
    for (int fileI = len % 2 ? len - 1 : len - 2; fileI > 0; fileI -= 2) {
        int found = 0;
        for (int spaceI = 1; spaceI < fileI; spaceI +=2) {
            // free space found
            if (line[spaceI] >= line[fileI]) {
                line[spaceI] -= line[fileI];
                for (int j = pos[spaceI]; j < pos[spaceI] + line[fileI]; j++) {
                    checksum += (fileI / 2) * j;
                }
                pos[spaceI] += line[fileI];
                found = 1;
                break;
            }
        }
        if (!found) {
            for (int j = pos[fileI]; j < pos[fileI] + line[fileI]; j++) {
                checksum += (fileI / 2) * j;
            }
        }
    }
    // 6286182965311
    printf("answer %ld\n", checksum);
}

int main() {
    b();
}
