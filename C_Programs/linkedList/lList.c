#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

Node *createNode(int val){
    Node *node = malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

void insert_head(Node **head, int data) { 
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = *head;
    *head = node;

}

void insert_tail(Node **head, int data){
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    
    Node *tmp = *head;
    if(tmp == NULL){
        *head = node;
        return;
    }

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = node;
    
}

int search(Node *head, int data) { 
    
    while(head != NULL){
        if((*head).data == data){
            return 1;
        }
        head = (*head).next;
    }
    return 0; 

}

int list_length(Node *head){
    int count = 0;

    while(head != NULL){
        head = head->next;
        count++;
    }
    return count;
}

Node *reverse_list(Node *head){

    Node *prev = NULL;
    Node *curr = head;

    while(curr){
        Node *nxt = curr->next;
        curr->next = prev;

        prev = curr;
        curr = nxt;
    }

    return prev;

}

void print_list(Node *head) { 
    Node *tmp = head;

    while (tmp != NULL){
        printf("%d -> ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");

}

int delete_node(Node **head, int data) { 
    Node *curr = *head;
    Node *nxt = curr->next;

    if(curr->data == data){
        free((*head));
        (*head) = nxt;
        return 1;
    }

    while (nxt != NULL){
        if(nxt->data = data){
        (*head)->next = nxt->next;
            free(nxt);
            return 1;
        }
        curr = curr->next;
        nxt = nxt->next;
    }
    
    return 0; 
}

void free_list(Node *head){
    
    while (head != NULL){
        Node *nxt = head->next;

        free(head);
        head = nxt;
    }
}

int main(int argc, char const *argv[])
{
    Node *head = NULL;

    /*for (int i = 1; i <= 5; i++) insert_tail(&head, i);
        delete_node(&head, 3);
        print_list(head);
        free_list(head);*/
    
    for (int i = 1; i <= 5; i++) insert_tail(&head, i);
        delete_node(&head, 3);
        printf("%d\n", list_length(head));
        free_list(head);

    return 0;
}
