#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Task
{
    int id;
    char title[50];
    int Priority;
    char Dealine[20];
    int completed; // 0: chua hoan thanh, 1: da hoan thanh
} Task;

typedef struct linkedlist
{
    Task *data;
    struct linkedlist *next;
} linkedlist;

// Ham khoi tao mot node moi
linkedlist *createNode(Task *task)
{
    linkedlist *newNode = (linkedlist *)malloc(sizeof(linkedlist));
    newNode->data = task;
    newNode->next = NULL;
    return newNode;
}

// Sinh deadline ngau nhien
char *ranDealine()
{
    char *dealine = (char *)malloc(20);
    int d = rand() % 30 + 1;
    int h = rand() % 12 + 1;
    int y = rand() % 5 + 2024;
    sprintf(dealine, "%02d/%02d/%d", d, h, y);
    return dealine;
}

int empty(linkedlist *head)
{
    return head == NULL;
}

void menu()
{
    printf("\n------------------ TASK MANAGER ------------------\n");
    printf("1. Them nhiem vu\n");
    printf("2. Hien thi danh sach nhiem vu\n");
    printf("3. Xoa nhiem vu\n");
    printf("4. Cap nhat thong tin nhiem vu\n");
    printf("5. Danh dau nhiem vu hoan thanh\n");
    printf("6. Sap xep nhiem vu\n");
    printf("7. Tim kiem nhiem vu\n");
    printf("0. Thoat chuong trinh\n");
    printf("--------------------------------------------------\n");
    printf("Chon chuc nang: ");
}

void addTask(linkedlist **headRef, int *idCounter)
{
    Task *task = (Task *)malloc(sizeof(Task));
    task->id = (*idCounter)++;
    printf("Nhap ten nhiem vu: ");
    getchar();
    fgets(task->title, sizeof(task->title), stdin);
    task->title[strcspn(task->title, "\n")] = 0;
    printf("Nhap muc do uu tien: ");
    scanf("%d", &task->Priority);
    strcpy(task->Dealine, ranDealine());
    task->completed = 0;

    linkedlist *newNode = createNode(task);
    newNode->next = *headRef;
    *headRef = newNode;
    printf("Da them nhiem vu thanh cong.\n");
}

void OUTLIST(linkedlist *head)
{
    if (empty(head))
    {
        printf("Danh sach rong.\n");
        return;
    }
    linkedlist *temp = head;
    while (temp != NULL)
    {
        Task *t = temp->data;
        printf("ID: %d\nTen: %s\nUu tien: %d\nDeadline: %s\nTrang thai: %s\n\n",
               t->id, t->title, t->Priority, t->Dealine,
               t->completed ? "Da hoan thanh" : "Chua hoan thanh");
        temp = temp->next;
    }
}

void delTask(linkedlist **headRef, int id)
{
    linkedlist *temp = *headRef, *prev = NULL;
    while (temp != NULL && temp->data->id != id)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Khong tim thay nhiem vu.\n");
        return;
    }
    if (prev == NULL)
        *headRef = temp->next;
    else
        prev->next = temp->next;
    free(temp->data);
    free(temp);
    printf("Da xoa nhiem vu.\n");
}

void update(linkedlist *head, int id)
{
    linkedlist *temp = head;
    while (temp != NULL && temp->data->id != id)
        temp = temp->next;
    if (temp == NULL)
    {
        printf("Khong tim thay.\n");
        return;
    }
    printf("Ten nhiem vu moi: ");
    getchar();
    fgets(temp->data->title, 50, stdin);
    temp->data->title[strcspn(temp->data->title, "\n")] = 0;
    printf("Muc do uu tien (so): ");
    scanf("%d", &temp->data->Priority);
    printf("Deadline moi (dd/mm/yyyy): ");
    scanf("%s", temp->data->Dealine);
    printf("Da cap nhat.\n");
}

void markDone(linkedlist *head, int id)
{
    while (head != NULL)
    {
        if (head->data->id == id)
        {
            head->data->completed = 1;
            printf("Da danh dau hoan thanh.\n");
            return;
        }
        head = head->next;
    }
    printf("Khong tim thay nhiem vu.\n");
}

void findTask(linkedlist *head, const char *keyword)
{
    int found = 0;
    while (head != NULL)
    {
        if (strstr(head->data->title, keyword))
        {
            printf("ID: %d, Ten: %s, Uu tien: %d\n",
                   head->data->id, head->data->title, head->data->Priority);
            found = 1;
        }
        head = head->next;
    }
    if (!found)
        printf("Khong tim thay nhiem vu.\n");
}

void bublesort(linkedlist *head)
{
    if (head == NULL)
    {
        return;
    }
    int swap;
    linkedlist *top;
    linkedlist *maxvalue = NULL;

    do
    {
        swap = 0;
        top = head;
        while (top->next != maxvalue)
        {
            if (top->data->Priority > top->next->data->Priority)
            {
                Task *temp = top->data;
                top->data = top->next->data;
                top->next->data = temp;
                swap = 1;
            }
            top = top->next;
        }
        maxvalue = top;
    } while (swap);
}

void search(linkedlist *head, char *name)
{
    linkedlist *temp = head;
    while (temp != NULL)
    {
        if (strstr(temp->data->title, name) != NULL)
        {
            Task *t = temp->data;
            printf("ID: %d\nTen: %s\nUu tien: %d\nDeadline: %s\nTrang thai: %s\n\n",
                   t->id, t->title, t->Priority, t->Dealine,
                   t->completed ? "Da hoan thanh" : "Chua hoan thanh");
            temp = temp->next;
        }
    }
}

int main()
{
    linkedlist *head = NULL;
    int idCounter = 1;
    int choice, id;
    char keyword[50];

    srand(time(NULL));
    do
    {
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addTask(&head, &idCounter);
            break;
        case 2:
            OUTLIST(head);
            break;
        case 3:
            printf("Nhap ID can xoa: ");
            scanf("%d", &id);
            delTask(&head, id);
            break;
        case 4:
            printf("Nhap ID can cap nhat: ");
            scanf("%d", &id);
            update(head, id);
            break;
        case 5:
            printf("Nhap ID can danh dau hoan thanh: ");
            scanf("%d", &id);
            markDone(head, id);
            break;
        case 6:
            bublesort(head);
            break;
        case 7:
            printf("Nhap tu khoa tim kiem: ");
            getchar();
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = 0;
            search(head, keyword);
            break;
        case 0:
            printf("Tam biet!\n");
            break;
        default:
            printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);
    return 0;
}
