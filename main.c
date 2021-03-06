#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include "editor.h"


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
    /* Ed.buf = buffer_new(3); */ 
    Ed.line = line_new();
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
                line_prev();
                mvgapto(Ed.line->buf, Ed.cx);
            break;
        case KEY_DOWN:
            if(Ed.cy != Ed.screenrow - 1) {
                if(Ed.line->next != NULL) {
                    Ed.cy++;
                    line_next();                
                    mvgapto(Ed.line->buf, Ed.cx);
            } 
        }
            break;
        case KEY_RIGHT:
            if (Linebuf->postsize != 0)
                if(Ed.cx != Ed.screencol - 1 ) {
                    Ed.cx++;
                    buffer_forward(Linebuf);
                }
                break;
        case KEY_LEFT:
            if(Ed.cx != 0) { 
                Ed.cx--;
                buffer_backward(Linebuf);
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
    if(Ed.cx == 0) return;
    Ed.cx--;
    move(Ed.cy, Ed.cx);
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
            if (isempty(Linebuf) && Ed.line->prev != NULL) {
                deleteln();
                line_delete(Ed.line);
            } else 
                handle_delete(Linebuf);
            break;
        case KEY_ENTER:
        case 10:
            if (Linebuf->postsize == 0) {
                line_add(Ed.line);
                Ed.cx = 0;
                handle_cursor(KEY_DOWN);
                move(Ed.cy, Ed.cx);
                insertln();
            }
            break;
        default:
            handle_insert(Linebuf, ch);
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
        keypress(stdscr); 
    }

    refresh();
    endwin();

    return 0;
}
