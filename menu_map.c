//
// Created by Liran on 4/13/2026.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// --- Task 2 Functions ---
char* map(char *array, int array_length, char (*f) (char)){
    char* mapped_array = (char*)(malloc(array_length * sizeof(char)));
    if (mapped_array == NULL) {
        return NULL;
    }
    for (int i = 0; i < array_length; i++) {
        mapped_array[i] = f(array[i]);
    }
    return mapped_array;
}

char my_get(char c) {
    return fgetc(stdin);
}

char cxprt(char c) {
    if (c >= 0x20 && c <= 0x7E) {
        printf("%c ", c);
    } else {
        printf(". ");
    }
    printf("%x\n", c);
    return c;
}

char encrypt(char c) {
    if (c == 0x7F) {
        return 0x20;
    } else if (c >= 0x20 && c <= 0x7F) {
        return c + 1;
    }
    return c;
}

char decrypt(char c) {
    if (c == 0x20) {
        return 0x7F;
    } else if (c >= 0x20 && c <= 0x7F) {
        return c - 1;
    }
    return c;
}

char dprt(char c) {
    printf("%d\n", c);
    return c;
}

// --- Task 3: OOP Simulation ---
struct fun_desc {
    char *name;
    char index;
    char (*fun)(char);
};

int main(int argc, char **argv) {
    // 1. הגדרת carray כמצביע למערך מאותחל ריק (מניעת גישה לזבל בזיכרון)
    char *carray = (char *)calloc(5, sizeof(char));
    if (!carray) return 1;

    // 2. אתחול "טבלת הניתוב" (vtable) של הפונקציות
    struct fun_desc menu[] = {
        {"Get string", '0', my_get},
        {"Print hex", '1', cxprt},
        {"Encrypt", '2', encrypt},
        {"Decrypt", '3', decrypt},
        {"Print dec", '4', dprt},
        {NULL, 0, NULL} // איבר סיום (Null Terminator)
    };

    // חישוב גודל המערך האפקטיבי (ללא ה-Null Terminator)
    int bounds = 0;
    while (menu[bounds].name != NULL) {
        bounds++;
    }

    char input[256];

    // 3. לולאת התפריט האינסופית
    while (1) {
        printf("Select operation from the following menu:\n");
        for (int i = 0; i < bounds; i++) {
            printf("%c) %s\n", menu[i].index, menu[i].name);
        }
        printf("Option: ");

        // 4. טיפול בקלט וזיהוי EOF (Ctrl+D)
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nDone.\n");
            break;
        }

        // חילוץ האינדקס מהקלט (הפיכת התו הראשון למספר שלם)
        int choice = input[0] - '0';

        // 5. ניתוב דינמי ללא שימוש ב-if/switch לבחירת הפונקציה
        if (choice >= 0 && choice < bounds) {
            printf("Within bounds\n");
            char *new_carray = map(carray, 5, menu[choice].fun);

            // שחרור הזיכרון הישן כדי למנוע Memory Leak, ועדכון המצביע
            free(carray);
            carray = new_carray;
        } else {
            printf("Not within bounds\n");
        }
    }

    free(carray); // ניקוי סופי עם יציאת התוכנית
    return 0;
}