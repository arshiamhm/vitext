#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define Linebuf Ed.line->buf

typedef struct gap_buffer {
	char *text; //a pointer to the start of our text;
	size_t size; //size of the buffer;
	size_t postsize; //size of the split buffer after the curser;
	size_t presize; //size of the split buffer before the curser;
} buffer;

typedef struct Line {
	buffer *buf;
	struct Line *next;
	struct Line *prev;
} Line; 

struct editorconfig {
	int cx, cy;
	int screenrow;
	int screencol;
	Line *line;
	int numrows;
} Ed;

void handle_cursor(int);
//Gap utility functions
size_t gap_length(buffer *b);
size_t post_start(buffer *b);
size_t gap_start(buffer *b);

//Gap manipulation functions
buffer* buffer_new(size_t size);
void buffer_expand(buffer *b);
void buffer_forward(buffer* b);
void buffer_backward(buffer* b);
void mvgapto(buffer *b, int cx);
bool isempty(buffer *b);
void insert_char(buffer* b, char c);
void delete_char(buffer *b);


//Line manipulation functions
Line* line_new(void);
void line_add(Line *);
void line_prev();
void line_next();
void line_delete(Line *);
void line_split(Line *);
