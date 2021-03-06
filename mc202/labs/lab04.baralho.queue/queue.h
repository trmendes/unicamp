#ifndef __QUEUE_H__
#define __QUEUE_H__

#define ERR_QUEUE_NULL  -1
#define ERR_QUEUE_EMPTY -2
#define SUCCESS          0

typedef struct node_s {
    int             id;
    struct node_s * next;
    struct node_s * prev;
} node_t;

typedef struct queue_s {
    int     len;
    node_t * head;
    node_t * tail;
} queue_t;

queue_t * qe_create    ();
int       qe_destroy   (queue_t *q);
int       qe_insert    (queue_t *q, node_t * data);
node_t *  qe_get       (queue_t *q);
int       qe_len       (queue_t *q);
void      qe_print     (queue_t *q);

#endif
