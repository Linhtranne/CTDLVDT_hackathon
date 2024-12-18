#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head != NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertAtTail(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPosition(Node** head, int position, int data) {
    if (position < 1) {
        printf("Vui long nhap vi tri hop le\n");
        return;
    }
    Node* newNode = createNode(data);
    if (position == 1) {
        insertAtHead(head, data);
        return;
    }
    Node* temp = *head;
    for (int i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        insertAtTail(head, data);
        return;
    }

    newNode->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteHead(Node** head) {
    if (*head == NULL) return;
    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

void deleteTail(Node** head) {
    if (*head == NULL) return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}

void deleteByValue(Node** head, int value) {
    if (*head == NULL) return;
    Node* temp = *head;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay phan tu co gia tri %d\n", value);
        return;
    }
    if (temp->prev == NULL) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
    printf("Da xoa phan tu co gia tri %d.\n", value);
}


void printListForward(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void printListBack(Node* head) {
    if (head == NULL) return;
    while (head->next != NULL) {
        head = head->next;
    }
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->prev;
    }
    printf("NULL\n");
}

void freeList(Node** head) {
    while (*head != NULL) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;
    int choice, value, position;

    do {
        printf("\nMenu:\n");
        printf("1. Them vao dau danh sach\n");
        printf("2. Them vao cuoi danh sach\n");
        printf("3. Them vao vi tri bat ky\n");
        printf("4. Xoa dau danh sach\n");
        printf("5. Xoa cuoi danh sach\n");
        printf("6. Xoa phan tu theo gia tri\n");
        printf("7. In danh sach theo thu tu xuoi\n");
        printf("8. In danh sach theo thu tu nguoc\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap gia tri can them: ");
                scanf("%d", &value);
                insertAtHead(&head, value);
                break;
            case 2:
                printf("Nhap gia tri can them: ");
                scanf("%d", &value);
                insertAtTail(&head, value);
                break;
            case 3:
                printf("Nhap vi tri can them: ");
                scanf("%d", &position);
                printf("Nhap gia tri can them: ");
                scanf("%d", &value);
                insertAtPosition(&head, position, value);
                break;
            case 4:
                deleteHead(&head);
                printf("Da xoa dau danh sach.\n");
                break;
            case 5:
                deleteTail(&head);
                printf("Da xoa cuoi danh sach.\n");
                break;
            case 6:
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &value);
                deleteByValue(&head, value);
                break;
            case 7:
                printf("Danh sach theo thu tu xuoi: ");
                printListForward(head);
                break;
            case 8:
                printf("Danh sach theo thu tu nguoc: ");
                printListBack(head);
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 9);

    freeList(&head);
    return 0;
}
