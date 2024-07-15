#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// 定义一个结构体
struct test
{
    int data;
    struct test *next;
};

// 遍历数组
void printfLink(struct test *head)
{
    struct test *pointer;
    pointer = head;
    while (pointer != NULL)
    {
        printf("%d ", pointer->data);
        pointer = pointer->next;
    }
    printf("\n");
}

// 统计链表节点个数
int getLinkNodeNum(struct test *head)
{
    int cnt = 0;
    struct test *pointer = head;
    while (pointer != NULL)
    {
        pointer = pointer->next;
        cnt++;
    }
    return cnt;
}

// 根据头结点和data查找是否有data这个数据
int searchLinkNodeData(struct test *head, int data)
{
    struct test *pointer = head;
    while (pointer != NULL)
    {
        if (pointer->data == data)
        {
            return 1;
        }
        pointer = pointer->next;
    }
    return 0;
}

// 动态创建节点
struct test *createListNode(int x)
{
    struct test *newnode = (struct test *)malloc(sizeof(struct test));
    if (newnode == NULL)
    {
        printf("BuySListNode error\n");
        exit(-1);
    }
    else
    {
        newnode->data = x;
        newnode->next = NULL;
    }
    return newnode;
}

// 动态创建节点-返回头节点法----头插法
struct test *insert_fromHead(struct test *head, int data)
{
    struct test *new;
    new = (struct test *)malloc(sizeof(struct test));
    new->data = data;
    new->next = head;
    head = new;
    return head;
}

// 动态双指针创建节点---头插法
void insertFromHead1(struct test **head, int x)
{
    // assert(pphead);
    struct test *newnode = createListNode(x);
    struct test *p = *head;
    if (*head == NULL)
    {
        *head = newnode;
    }
    else
    {
        newnode->next = *head;
        *head = newnode;
    }
}

// 动态创建节点-返回头节点法----尾插法
struct test *insertFromBehind(struct test *head, int data)
{
    struct test *new;
    new = (struct test *)malloc(sizeof(struct test));
    new->data = data;
    new->next = NULL;
    struct test *pointer = head;
    // 无链表
    if (head == NULL)
    {
        head = new;
        return head;
    }
    // 链表只有一个节点
    if (pointer->next == NULL)
    {
        pointer->next = new;
        return head;
    }
    while (pointer->next != NULL)
    {
        pointer = pointer->next;
    }
    pointer->next = new;

    return head;
}

// 动态双指针创建节点---尾插法
void insertFromBehind1(struct test **head, int data)
{
    struct test *newnode = createListNode(data);
    // 如果没有头节点，就当头节点
    if (*head == NULL)
    {
        *head = newnode;
    }
    else
    {
        struct test *p = *head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = newnode;
    }
}

// 指定位置前插
void insertFromFront(struct test **head, struct test *pos, int x)
{
    // 创建一个新节点
    struct test *newnode = createListNode(x);
    //
    if ((*head) == pos)
    {
        newnode->next = *head;
        *head = newnode;
    }
    else
    {
        struct test *tempNode = *head;
        while (tempNode->next != pos)
        {
            tempNode = tempNode->next;
        }
        newnode->next = pos;
        tempNode->next = newnode;
    }
}

// 指定位置后插
void insertFromBehindNode(struct test **head, struct test *pos, int x)
{
    // 创建一个新节点
    struct test *newnode = createListNode(x);
    struct test *tempNode = *head;
    while (tempNode != NULL)
    {
        if (tempNode == pos)
        {
            newnode->next = tempNode->next;
            tempNode->next = newnode;
        }
        tempNode = tempNode->next;
    }
}

// 删除链表头
void deleteLinkfront(struct test **head)
{
    struct test *p = (*head)->next;
    free(*head);
    *head = p;
}

// 删除链表尾
void deleteLinkBehind(struct test **head)
{
    // 链表为空
    if (*head == NULL)
    {
        return;
    }
    // 链表只有一个节点
    if ((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        // 尾部节点
        struct test *tail = *head;
        // 尾部前一个节点
        struct test *prevTail = NULL;

        while (tail->next != NULL)
        {
            prevTail = tail;
            tail = tail->next;
        }
        // 释放尾节点
        free(tail);
        tail = NULL;
        // 把尾节点的前一个节点的next指向空
        prevTail->next = NULL;
    }
}

// 删除指定节点
void deletePosNode(struct test **head, struct test *pos)
{
    if ((*head) == pos)
    {
        deleteLinkfront(head);
    }
    else
    {
        struct test *prevHead = *head;
        while (prevHead->next != pos)
        {
            prevHead = prevHead->next;
        }
        prevHead->next = pos->next;
        free(pos);
    }
}

// 删除链表
void deleteLink(struct test **head)
{
    // 无链表
    if (*head == NULL)
    {
        return;
    }
    struct test *prevHead = *head;
    while (*head != NULL)
    {
        // 头节点前一个节点
        prevHead = *head;
        // 头节点移向后一个
        *head = (*head)->next;
        // 释放头节点的前一个节点
        free(prevHead);
    }
    printf("清空完成！\n");
}

// 查找链表的节点
struct test *linkFind(struct test *head, int data)
{
    struct test *p = head;
    while (p != NULL)
    {
        if (p->data == data)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void test()
{
    struct test *head = NULL;
    struct test *find = NULL;

    head = createListNode(100);
    insertFromHead1(&head, 101);
    insertFromHead1(&head, 102);
    insertFromBehind1(&head, 103);
    insertFromBehind1(&head, 104);
    insertFromBehind1(&head, 105);
    head = insertFromHead(head, 2000);
    head = insertFromBehind(head, 1000);
    head = insertFromBehind(head, 1001);
    head = insertFromBehind(head, 1002);
    head = insertFromBehind(head, 1003);
    printfLink(head);
    deleteLinkfront(&head);
    printfLink(head);
    deleteLinkBehind(&head);
    printfLink(head);
    // deleteLink(&head);
    // printfLink(head);
    find = linkFind(head, 1001);
    deletePosNode(&head, find);
    // insertFromBehindNode(&head, find, 111);
    // insertFromFront(&head, find, 111);
    printfLink(head);
}

int main()
{
    test();
    return 0;
}
