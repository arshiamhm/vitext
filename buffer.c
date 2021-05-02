#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"


buffer* buffer_new(size_t size) {
    buffer *b = NULL;
    b = (buffer *)malloc(sizeof(buffer));
    if (b != NULL) {
        b->text = malloc(sizeof(char) * (size + 1));
        b->size = size;
        b->postsize = 0;
        b->presize = 0;
        return b;
    }
    return NULL;
}

size_t post_start(buffer *b) {
    return b->size - b->postsize;     
}

size_t gap_start(buffer *b) { 
    return b->presize;
}

size_t gap_length(buffer *b) {
    /* size_t pst = post_start(b); */
    return post_start(b) - b->presize;  
}

/* bool is_right(buffer *b) { */
/*     return b->presize + gap_length(b) >= b->size; */
/* } */

void buffer_expand(buffer *b) {
    
    //allocate space double the size of the current buffer
    //copy pre section to the new buffer
    //get the post start index
    //copy the post section
    //deallocate the previous buffer
    size_t newsize = b->size * 2;
    size_t poststart = post_start(b);
    char *newbuf = (char *)malloc(sizeof(char) * newsize);
    if (newbuf == NULL) return ;
    if (!memcpy(newbuf, b->text, b->presize * sizeof(char)) || !memcpy(&newbuf[newsize - b->postsize], &newbuf[poststart], b->postsize * sizeof(char))) {
        
        perror("failed to expand the gap buffer");
        return;
    }

    free(b->text);
    b->text = newbuf;
    b->size = newsize;
}


void buffer_forward(buffer* b) {
    if (b->postsize == 0) {
        return;
    }
    b->text[b->presize] = b->text[post_start(b)];
    b->presize++;
    b->postsize--;
}

void buffer_backward(buffer *b) {
    if (b->presize == 0) {
        return;
    }
    b->text[post_start(b) - 1] = b->text[b->presize - 1];
    b->presize--;
    b->postsize++;
}

void insert_char(buffer *b, char c) {
    size_t gaplen;
    if ((gaplen = gap_length(b)) == 1) 
        buffer_expand(b);
    b->text[gap_start(b)] = c;
    b->presize++;
}

void delete_char(buffer *b) {
    if (b->presize > 0)
        b->presize--;
}

static Line* line_alloc() {
    return (Line *)malloc(sizeof(Line));
}

Line* line_new(void) {
    Line* head;
    head = line_alloc();
    
    if (head != NULL) {
        head->buf = buffer_new(5);
        head->prev = head->next = NULL;
        return head;
    }
    
    return NULL;
}

void line_add(Line *lnode) {
    Line *new_node;
    if ((new_node = line_alloc()) == NULL) return;

    new_node->buf = buffer_new(5);
    if(lnode->next != NULL) {
        Line *temp = lnode->next;
        temp->prev = new_node;
        lnode->next = new_node;
        new_node->prev = lnode;
        new_node->next = temp;
    } else {
        lnode->next = new_node;
        new_node->prev = lnode;
        new_node->next = NULL;
    }

    Ed.line = new_node;
}

void line_next(Line *lnode) {
    if (lnode->next != NULL) {
        Ed.line = lnode->next;
    }
    return;
}

void line_prev(Line *lnode) {
    if (lnode->prev != NULL) {
        Ed.line = lnode->prev;
    }
}

