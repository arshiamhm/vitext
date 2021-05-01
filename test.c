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

    struct text *t;
    t = (struct text *) malloc(sizeof(struct text));

    t->b = (char *)malloc(sizeof(char) * 10);
    strcpy(t->b, "byr");
    t->b[3] = 'n';
    t->size = 34;

    int c;
    while ((c = *t->b++) != '\0')
        ;
    

    printf("%s , %d\n", t->b, t->size);


    return 0;
}
