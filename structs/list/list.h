#include <stddef.h>

struct list {
    int val;
    struct list *next;
};

struct list *create_list(int value);
int length(struct list *ls);
int add_to_end(struct list *ls, int value);
int add_in_start(struct list **ls, int value);
int add_after_index(struct list *ls, int index, int value);
int find_by_index(struct list *ls, int index);
int remove_by_index(struct list **ls, int index);
void destroy(struct list *ls);