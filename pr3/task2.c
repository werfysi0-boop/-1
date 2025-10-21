#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* create_list() {
    return NULL;
}

Node* add_node(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    
    if (head == NULL) {
        newNode->next = NULL;
        newNode->prev = NULL;
        return newNode;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
        newNode->next = NULL;
        return head;
    }
}

Node* delete_from_end(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->prev->next = NULL;
    free(current);
    return head;
}

void print_list(Node* head) {
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

void print_list_reverse(Node* head) {
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    while (current != NULL) {
        printf("%d", current->data);
        if (current->prev != NULL) {
            printf(" -> ");
        }
        current = current->prev;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* head = create_list();
    
    head = add_node(head, 10);
    head = add_node(head, 20);
    head = add_node(head, 30);
    head = add_node(head, 40);
    head = add_node(head, 50);

    printf("Исходный список:\n");
    print_list(head);
    
    printf("Список в обратном порядке:\n");
    print_list_reverse(head);

    head = delete_from_end(head);
    printf("\nПосле удаления из конца:\n");
    print_list(head);

    head = delete_from_end(head);
    printf("После еще одного удаления из конца:\n");
    print_list(head);

    free_list(head);

    return 0;
}
