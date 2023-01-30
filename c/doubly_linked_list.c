/**
 * 双向链表的实现 查找是O(N) 插入在头尾都是O(1) 这里尾部可以是O(1)因为可以保持一个size + tail 这样尾部操作就和头部一样
 * 中间是O(N) remove同理 update同理
*/

#include <stdio.h>
#include <stdlib.h>
#include <err.h>

typedef struct node {
    int data;
    struct node * prev;
    struct node * next;
} node;

// 创建一个双向链表
node* init_list() {
    node* head = (node*)malloc(sizeof(node));
    head->data = 0;
    head->prev = NULL;
    head->next = NULL;
    return head;
}

// free所有的nodes 
void free_list(node* head) {
    node* temp = head;
    while(temp != NULL) {
        head = head->next;
        free(temp);
        temp = head;
    }
}

// insert a node into the list at index, return the head of the new list
node* insert_node(node* head, int data, int index) {
    if(index == 0) { // insert at the front
        node* new_node = (node*) malloc(sizeof(node));
        new_node->data = data;
        new_node->prev = NULL;
        new_node->next = head;
        head->prev = new_node;
        return new_node;
    }
    node* iterator = head;
    int i = 0;
    while(iterator != NULL) {
        if(i == index) { // insert in the middle
            node* new_node = (node*) malloc(sizeof(node));
            new_node->data = data;
            new_node->prev = iterator->prev;
            iterator->prev->next = new_node;
            new_node->next = iterator;
            iterator->prev = new_node;
            return new_node;
        }
        if(iterator->next == NULL && i + 1 == index) { // insert at the end
            node* new_node = (node*) malloc(sizeof(node));
            new_node->data = data;
            new_node->prev = iterator;
            new_node->next = NULL;
            iterator->next = new_node;
            return new_node;
        }
        i++;
        iterator = iterator->next;
    }
    // index > size - 1, we will raise an error 我们不应该在这里再插入队尾了 指针已经不见了
    err(1, 0);
}

node* remove_node(node* head, int index) {
    if(index == 0) { // remove at the front
        node* new_head = head->next;
        if(new_head != NULL) new_head->prev = NULL;
        free(head);
        return new_head;
    }
    node* iterator = head;
    int i = 0;
    while(iterator != NULL) {
        if(i == index) { // remove in the middle
            iterator->prev->next = iterator->next;
            if(iterator->next != NULL) { // remove at the last i->next->prev will be null pointer
                iterator->next->prev = iterator->prev;
            }
            free(iterator);
            return head;
        }
        i++;
        iterator = iterator->next;
    }
    err(1,0); // index not in the list
}

// search list for target value, the first one wil be searched out
node* search_list(node* head, int target) {
    node* iterator = head;
    while(iterator != NULL) {
        if(iterator->data == target) return iterator;
        iterator = iterator->next;
    }
    return NULL; // return NULL is 
}

// update value of a node
void update_list(node* head, int index, int new_value) {
    node* iterator = head;
    int i = 0;
    while(iterator != NULL) {
        if(i == index) {
            iterator->data = new_value;
            return;
        };
        i++;
        iterator = iterator->next;
    }
    err(1, 0); 
}

// 打印list中所有node的data
void print_list(node* head) {
    node* iterator = head;
    while(iterator != NULL) {
        if(iterator->next == NULL) { // last node
            fprintf(stdout, "node: %d.", iterator->data);
        }else{
            fprintf(stdout, "node: %d <->", iterator->data);
        }
        iterator = iterator->next;
    }
}

int main() {
    node* head = NULL;
    head = init_list();
    free_list(head);
}