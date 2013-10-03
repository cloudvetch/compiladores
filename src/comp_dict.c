#include <comp_dict.h>
#include <stdlib.h>
#include <stdio.h>

static inline void __comp_dict_init(comp_dict_t *dict) {
    dict->prev = dict;
    dict->next = dict;
}

inline int comp_dict_is_empty(comp_dict_t *dict) {
    return dict == dict->next;
}

comp_dict_t *new_comp_dict() {
    comp_dict_t *dict;
    dict = malloc(sizeof(comp_dict_t));
    __comp_dict_init(dict);
    return dict;
}

void comp_dict_delete(comp_dict_t *dict) {
    if (!comp_dict_is_empty) {
        comp_dict_t *temp;
        temp = dict->next;
        do {
            temp = temp->next;    
            free(temp->prev);
            temp->prev = NULL;
        } while(temp != dict);
    }
    free(dict);
    dict = NULL;
}

void comp_dict_append(comp_dict_t *dict, comp_dict_t *new_node) {
    comp_dict_t *node_to_append;
    /* to append the same dict any times we need a new one, but
       when active this, we cant find the dict by reference, just by item value */
    //node_to_append = new_comp_dict();
    //node_to_append->item = new_node->item;
    

    node_to_append = new_node;
    
    dict->prev->next = node_to_append;
    node_to_append->prev = dict->prev;
    node_to_append->next = dict;
    dict->prev = node_to_append;
}

void comp_dict_insert(comp_dict_t *dict, comp_dict_t *new_node) {
    comp_dict_t *node_to_insert;
    /* same as append */
    //node_to_insert = new_comp_dict();
    //node_to_insert->item = new_node->item;

    node_to_insert = new_node;

    dict->next->prev = node_to_insert;
    node_to_insert->prev = dict;
    node_to_insert->next = dict->next;
    dict->next = node_to_insert;
}

void comp_dict_remove(comp_dict_t *dict, comp_dict_t *node_to_remove) {
    comp_dict_t *temp;
    temp = dict->next;
    while(temp != dict) {
        if (temp == node_to_remove) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            break;
        }
        temp = temp->next;
    }
}

void comp_dict_concat(comp_dict_t *dict1, comp_dict_t *dict2) {
    dict1->prev->next = dict2;
    dict2->prev->next = dict1;
    comp_dict_t *temp_dict1_prev;
    temp_dict1_prev = dict1->prev;
    dict1->prev = dict2->prev;
    dict2->prev = temp_dict1_prev;
}

void comp_dict_set(comp_dict_t *dict, comp_dict_item_t *item) {
    dict->item = item;
}

comp_dict_t* comp_dict_find(comp_dict_t *dict, char *key) {
    comp_dict_t *it = dict;
    while(it != dict->prev) {
        if (strcmp(it->item->key,key)) {
            return it;
        }
        it = it->next;
    }
    return NULL; //not found
}


void comp_dict_print(comp_dict_t *dict) {
    comp_dict_t *temp;
    temp = dict;
    int i=0;
    do {
        printf("%s -> %X\n",comp_dict_item_key_get(temp->item),comp_dict_item_value_get(temp->item));
        temp = temp->next;    
    } while(temp != dict);
    printf("\n");
}


static inline void __comp_dict_item_init(comp_dict_item_t *dict_item) {
    dict_item->key = NULL;
    dict_item->value = NULL;
}

comp_dict_item_t *new_comp_dict_item() {
    comp_dict_item_t *dict_item;
    dict_item = malloc(sizeof(comp_dict_item_t));
    __comp_dict_item_init(dict_item);
    return dict_item;
    
}
void comp_dict_item_delete(comp_dict_item_t *dict_item) {
    free(dict_item->key);
    dict_item->key = NULL;
    free(dict_item->value);
    dict_item->value = NULL;
    free(dict_item);
    dict_item = NULL;
}

char *comp_dict_item_key_get(comp_dict_item_t *dict_item) {
    return dict_item->key;
}

void *comp_dict_item_value_get(comp_dict_item_t *dict_item) {
    return dict_item->value;
}

int comp_dict_item_set(comp_dict_item_t *dict_item, char key[], char value[]) {
    int ret = 0;
    int key_s,value_s;
    key_s = sizeof(key);
    value_s = sizeof(value);
    if ( (key_s <= DICT_ITEM_MAX_KEY_SIZE) && (value_s <= DICT_ITEM_MAX_VALUE_SIZE) ) {
        free(dict_item->key);
        dict_item->key = malloc(key_s);
        dict_item->key = key;
        free(dict_item->value);
        dict_item->value = malloc(value_s);
        dict_item->value = value;
        ret = 1;
    }
    return ret;
}

void comp_dict_item_print(comp_dict_item_t *dict_item) {
    printf("%s -> %s\n",dict_item->key,dict_item->value);
}
