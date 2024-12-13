#include <stdio.h>
#include <limits.h>
#include <math.h>

void a() {
    FILE *f = fopen("13_2.txt", "r");
    char line[100];
    int numCaptured;
    char ch;
    long total = 0;
    while((ch = fgetc(f)) != EOF) {
        ungetc(ch, f);
        int ax, ay, bx, by, px, py;
        fscanf(f, "Button A: X+%d, Y+%d\n", &ax, &ay);
        fscanf(f, "Button B: X+%d, Y+%d\n", &bx, &by);
        fscanf(f, "Prize: X=%d, Y=%d\n\n", &px, &py);

        int cost = INT_MAX;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                // printf("checking %d, %d  ", i * ax + j * bx, i * ay + j * by);
                if (i * ax + j * bx == px && i * ay + j * by == py) {
                    if (cost > i * 3 + j * 1) cost = i * 3 + j * 1; 
                }
            }
        }
        if (cost != INT_MAX) {
            total += cost;
        }
        printf("cost %d. A: {%d, %d}. B {%d, %d}, P {%d, %d}\n", cost, ax, ay, bx, by, px, py);
    }


    //28138
    //39290 (2)
    printf("answer %ld\n", total);
}

void b() {
    FILE *f = fopen("13_2.txt", "r");
    char line[100];
    int numCaptured;
    char ch;
    long total = 0;
    while((ch = fgetc(f)) != EOF) {
        ungetc(ch, f);
        int ax, ay, bx, by;
        long px, py;
        fscanf(f, "Button A: X+%d, Y+%d\n", &ax, &ay);
        fscanf(f, "Button B: X+%d, Y+%d\n", &bx, &by);
        fscanf(f, "Prize: X=%ld, Y=%ld\n\n", &px, &py);
        // long extra = 10000000;
        long extra = 10000000000000;
        // long extra = 0;
        px += extra;
        py += extra;

        int cost = INT_MAX;
        int a1, b1;
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                // printf("checking %d, %d  ", i * ax + j * bx, i * ay + j * by);
                if (i * ax + j * bx == px && i * ay + j * by == py) {
                    if (cost > i * 3 + j * 1) {
                        cost = i * 3 + j * 1; 
                        a1 = i;
                        b1 = j;
                    }
                }
            }
        }
        int found1 = 0;
         if (cost != INT_MAX) {
            found1 = 1;
        }

// 26(x)a + 67(x')b = 10000000012748 (c)
// 66(y)a + 21(y')b = 10000000012176 (c')

// 26(ax)a + 67(bx)b = 10000000012748 (px)
// 66(ay)a + 21(by)b = 10000000012176 (py)
//          b = (ay*px - ax*py)/(bx*ay - ax*by)
// b = (66 * 10000000012748 - 10000000012176*26)/(67*66 - 26*21)
        double b = (ay*px - ax*py)/(double)(bx*ay - ax*by);
        double a = (px - bx * b)/(double)ax;

        double cost2 = 0;
        double inta, intb;
        modf(a, &inta);
        modf(b, &intb); 
        int found2 = 0;
        if (modf(a, &inta) == 0 && modf(b, &intb) == 0 && a >= 0 && b >= 0) {
        // if (a == inta && b == intb && a >= 0 && b >= 0) {
            cost2 = a * 3 + b;
            total += cost2;
            found2 = 1;
        }
        
        if (found1 != found2) {
            printf("cost %d. A: {%d, %d}. B {%d, %d}, P {%d, %d}\n", cost, ax, ay, bx, by, px, py);
            printf("result1. cost %d. press A %d and press B %d.\n", cost, a1, b1);
            printf("result2. cost %f. press A %f and press B %f. modf b %f\n", cost2, a, b, inta);
            printf("calc = %f * %d + %f * %d = %d\n", a, ax, b, bx, px);
            printf("calc = %f * %d + %f * %d = %d\n", a, ay, b, by, py);
            printf("woah ^^^\n\n\n\n"); 
        }
    }

    printf("answer %ld\n", total);
}

// 10 000 000 000 000
// 9223372036854775807

int main() {
    b();
}
