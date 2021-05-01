#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include "editor.h"


struct editorconfig { int cx, cy;
    int screenrow;
    int screencol;
    buffer *buf;
    int numrows;
} Ed;

/* struct tempbuf { */
/*     char *b; */
/*     int len; */
/* }; */
/* #define TEMPBUF_INIT {NULL, 0} */

/* void tempbuf_append(struct tempbuf *tb, const char *s, int len) { */
/*     char *new = realloc(tb->b, tb->len + len); */

/*     if (new == NULL) return; */

/*     memcpy(&new[tb->len], s, len); */
/*     tb->b = new; */
/*     tb->len += len; */
/* } */

/* void tempbuf_free(struct tempbuf *tb) { */
/*     free(tb->b); */
/*     free(tb); */
/* } */

void initEditor() {
    Ed.cx = 0;
    Ed.cy = 0;
    Ed.numrows = 1; 
    Ed.buf = buffer_new(3); 
    getmaxyx(stdscr, Ed.screenrow, Ed.screencol);
}


/* void drawRows() { */
/*     int y; */
/*     for (y = 0; y < Ed.screenrow; y++) { */
/*         if (y >= Ed.numrows) { */
/*             /1* tempbuf_append(tb, "\n~", 2); *1/ */
/*             printw("\n~"); */
/*         } */
/*         /1* else { *1/ */
/*         /1*     tempbuf_append(tb, Ed.buf->text, ); *1/ */
/*         /1* } *1/ */
/*     } */
/* } */

/* void refresh_screen() { */
/*     struct tempbuf *tb = (struct tempbuf *)malloc(sizeof(struct tempbuf)); */
/*     tb->b = NULL; */
/*     tb->len = 0; */


/*     /1* printw("%s", tb->b); *1/ */
/*     tempbuf_free(tb); */
/* } */

/* void file_open() { */
/*     char *line = "this line is intresting"; */
/*     size_t length = 23; */

/*     Ed.buf = buffer_new(length); */
/*     memcpy(Ed.buf->text, line, length); */
/*     Ed.buf->text[length] = '\0'; */ 
/*     Ed.numrows = 1; */ 

/* } */

void handle_cursor(int c) {
    switch(c) {
        case KEY_UP:
            if(Ed.cy != 0) 
                Ed.cy--;
            break;
        case KEY_DOWN:
            if(Ed.cy != Ed.screenrow - 1)
                Ed.cy++;
            break;
        case KEY_RIGHT:
            if (Ed.buf->postsize != 0)
                if(Ed.cx != Ed.screencol - 1 ) {
                    Ed.cx++;
                    buffer_forward(Ed.buf);
                }
                break;
        case KEY_LEFT:
            if(Ed.cx != 0) { 
                Ed.cx--;
                buffer_backward(Ed.buf);
            }
            break;
    }
}

void handle_insert(buffer *b, char ch) {
    Ed.cx++;
    insch(ch);
    insert_char(b, ch);
}   

void handle_delete(buffer *b) {
    Ed.cx--;
    move(0, Ed.cx);
    delch();
    delete_char(b);
}

void keypress(WINDOW *win) {
    int ch = getch();

    switch(ch) {
        case KEY_UP:
        case KEY_DOWN:
        case KEY_RIGHT:
        case KEY_LEFT:
            handle_cursor(ch);
            break;
        case KEY_BACKSPACE:
        case 127:
        case '\b':
            if(Ed.cx != 0) 
                handle_delete(Ed.buf);
            break;
        default:
            handle_insert(Ed.buf, ch);
            break;
    }

    wmove(win, Ed.cy, Ed.cx);
}


int main(){

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    move(0, 0);
    refresh();
    initEditor(); 
    /* file_open(); */
    /* drawRows(); */
    while (1){
        /* refresh_screen(); */
        keypress(stdscr); 
    }

    refresh();
    endwin();

    return 0;
}
