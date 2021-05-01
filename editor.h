#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct gap_buffer {
		char *text; //a pointer to the start of our text;
		size_t size; //size of the buffer;
		size_t postsize; //size of the split buffer after the curser;
		size_t presize; //size of the split buffer before the curser;
} buffer;

//gap utility functions
size_t gap_length(buffer *b);
size_t post_start(buffer *b);
size_t gap_start(buffer *b);
/* size_t pre_end(buffer *b); */

//gap manipulation functions
buffer* buffer_new(size_t size);
void buffer_expand(buffer *b);
void buffer_forward(buffer* b);
void buffer_backward(buffer* b);


void insert_char(buffer* b, char c);
void delete_char(buffer *b);
/* void buffer_delete(buffer* b); */


