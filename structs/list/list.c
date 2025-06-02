#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct list *create_list(int value) {
    struct list *ls = (struct list *)malloc(sizeof(struct list));
    if (!ls) return NULL;
    ls->val = value;
    ls->next = NULL;
    return ls;
}

int length(struct list *ls) {
    int i = 0;
    while (ls != NULL) {
        ls = ls->next;
        i++;
    }
    return i;
}

int add_to_end(struct list *ls, int value) {
    if (!ls) return 1;
    while (ls->next != NULL)
        ls = ls->next;

    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    if (!new_node) return 1;

    new_node->val = value;
    new_node->next = NULL;
    ls->next = new_node;
    return 0;
}

int add_in_start(struct list **ls, int value) {
    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    if (!new_node) return 1;

    new_node->val = value;
    new_node->next = *ls;
    *ls = new_node;
    return 0;
}

int add_after_index(struct list *ls, int index, int value) {
    int i = 0;
    while (ls != NULL && i < index) {
        ls = ls->next;
        i++;
    }

    if (!ls) return 1;

    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    if (!new_node) return 1;

    new_node->val = value;
    new_node->next = ls->next;
    ls->next = new_node;
    return 0;
}

int find_by_index(struct list *head, int index) {
    if (head == NULL || index < 0)
        return -1;

    struct list *cur = head;
    for (int i = 0; i < index && cur != NULL; ++i) {
        cur = cur->next;
    }

    if (cur == NULL)
        return -1;

    return cur->val;
}

int remove_by_index(struct list **ls, int index) {
    if (!*ls || index < 0) return 1;

    struct list *temp = *ls;

    if (index == 0) {
        *ls = temp->next;
        free(temp);
        return 0;
    }

    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    if (!temp || !temp->next) return 1;

    struct list *to_delete = temp->next;
    temp->next = to_delete->next;
    free(to_delete);
    return 0;
}

void destroy(struct list *ls) {
    while (ls != NULL) {
        struct list *next = ls->next;
        free(ls);
        ls = next;
    }
}
