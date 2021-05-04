#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



struct text {
    char *b;
    int size;
};

int main(void) {

    char *array  = (char *)malloc(sizeof(char) * 8);
    array[0] = 'h';
    array[1] = 'e';
    array[6] = 'g';
    array[7] = 'o';
    int start = 2;
    int length = 0;
    while(array[start++] == '\0')
        length++;
    
    printf("%d\n", length);

    return 0;
}
