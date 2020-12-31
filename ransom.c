#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct linked_list_node linked_list_node;
typedef struct linked_list linked_list;

struct linked_list_node {
    char *data;
    int key;
    linked_list_node *next;
};

struct linked_list {
    linked_list_node *head;
    linked_list_node *tail;
};


char* readline();
char** split_string(char*);
linked_list_node *create_new_node (char *node_data, int key);
void insert_node_list (linked_list *list, linked_list_node *new_node);
void change_duplicate(linked_list *list);
void free_linked_list (linked_list_node *node);
int cmp_lists(linked_list *list_note, linked_list *list_magazine);


// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {

    /*allocate the magazine and note lists, free if needed*/
    linked_list *list_magazine=(linked_list*)(malloc(sizeof(linked_list)));
    if (list_magazine==NULL) {
        free(list_magazine);
        return;
    }

    linked_list *list_note=(linked_list*)(malloc(sizeof(linked_list)));
    if (list_note==NULL) {
        free(list_magazine);
        free(list_note);
        return;
    }

    /*initializing the head and tail of both lists*/
    list_magazine->head=NULL;
    list_magazine->tail=NULL;
    list_note->head=NULL;
    list_note->tail=NULL;

    /*creating the nodes of the lists*/
    linked_list_node *new_node;
    for (int i=0; i<magazine_count; i++) {
        new_node = create_new_node (magazine[i], 1);
        if (new_node==0){
            free_linked_list(list_magazine->head);
            free(list_magazine);
            free(list_note);
            return;
        }
        insert_node_list (list_magazine, new_node);
    }
    for (int i=0; i<note_count; i++) {
        new_node = create_new_node (note[i], 1);
        if (new_node==0){
            free_linked_list(list_note->head);
            free_linked_list(list_magazine->head);
            free(list_magazine);
            free(list_note);
            return;
        }
            
        insert_node_list (list_note, new_node);
    }

    /*minimizing the lists - delete duplicated values*/
    change_duplicate(list_magazine);
    change_duplicate(list_note);
    

    /*check if all the words needed are founded*/
    if (cmp_lists(list_note, list_magazine)) {
        printf("Yes");
    }
    else {
        printf("No");
    }

    free_linked_list(list_note->head);
    free_linked_list(list_magazine->head);
    free(list_magazine);
    free(list_note);
}


linked_list_node *create_new_node (char *node_data, int key) {
    linked_list_node *node=(linked_list_node*)malloc(sizeof(linked_list_node));
    if (node==NULL) {
        free(node);
        return 0;
    }
    node->data=node_data;
    node->key=key;
    node->next=NULL;
    return node;
}

void insert_node_list (linked_list *list, linked_list_node *new_node) {
    if (!(list->head)) {
        list->head=new_node;
    } else {
        list->tail->next=new_node;
    }
    list->tail=new_node;
}

void change_duplicate (linked_list *list) {
    linked_list_node *rv = list->head;
    linked_list_node *rv2;
    linked_list_node *tmp;
    while (rv != NULL) {
        rv2=rv;
        while (rv2->next != NULL) {
            /*if two strings are equal in one list,
            delete one node and change key*/
            if (strcmp(rv->data,rv2->next->data)==0) {
                rv->key = rv->key + 1;
                tmp = rv2->next;
                rv2->next = tmp->next;
                free(tmp);
            } 
            else {
                rv2 = rv2->next;
            }
        }
        rv = rv->next;
    }
}
 

void free_linked_list (linked_list_node *node) {
    while (node) {
        linked_list_node *temp = node;
        node = node->next;
        free(temp);
    }
}

int cmp_lists(linked_list *list_note, linked_list *list_magazine) {
    int word_was_found;
    linked_list_node *magazine_node;
    linked_list_node *note_node = list_note->head;
    while (note_node != NULL) {
        word_was_found=0;
        magazine_node=list_magazine->head;

        /*we didn't find the word yet*/
        while (magazine_node != NULL && (!word_was_found)) {
            if (strcmp(note_node->data,magazine_node->data)==0) {
                if (note_node->key > magazine_node->key) {
                    return 0;
                }
                word_was_found=1;
            }
        magazine_node=magazine_node->next;
        }
        if (!word_was_found) {
            return 0;
        }
        note_node=note_node->next;
    }
    return 1;
}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}