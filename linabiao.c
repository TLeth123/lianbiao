#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// 从指定的节点后面添加新节点
int insertFromNodeBehind(struct test *head, int data, struct test *new)
{
    struct test *pointer = head;
    while (pointer != NULL)
    {
        if (pointer->data == data)
        {
            new->next = pointer->next;
            pointer->next = new;
            return 1;
        }
        pointer = pointer->next;
    }
    return 0;
}

// 从指定的节点前面添加新节点
struct test *insertFromNodeFront(struct test *head, int data, struct test *new)
{
    struct test *pointer = head;
    // 情况一：要从头节点前插入数据
    if (pointer->data == data)
    {
        new->next = pointer;
        return new;
    }
    // 情况二，不在头节点的前面增加新的节点
    while (pointer != NULL)
    {
        if (pointer->next->data == data)
        {
            new->next = pointer->next;
            pointer->next = new;
            return head;
        }
        pointer = pointer->next;
    }
    return head;
}

// 删除节点
struct test *deleteNode(struct test *head, int data)
{
    struct test *pointer = head;
    // 情况一：删除头节点
    if (pointer->data == data)
    {
        head = pointer->next;
        // free(pointer);
        return head;
    }

    // 情况二，删除非头节点
    while (pointer != NULL)
    {
        if (pointer->next->data == data)
        {
            pointer->next = pointer->next->next;
            return head;
        }
        pointer = pointer->next;
    }
    return head;
}

int main()
{

    struct test *head = NULL;
    struct test t1 = {1, NULL};
    struct test t2 = {2, NULL};
    struct test t3 = {3, NULL};
    struct test t4 = {4, NULL};
    struct test t5 = {5, NULL};
    struct test t6 = {6, NULL};

    struct test new = {100, NULL};
    struct test new2 = {102, NULL};
    struct test new3 = {103, NULL};
    t1.next = &t2;
    t2.next = &t3;
    t3.next = &t4;
    t4.next = &t5;
    t5.next = &t6;

    head = &t1;
    printf("%d %d %d\n", t1.data, t1.next->data, t1.next->next->data);
    printfLink(head);
    printf("链表节点个数为：%d\n", getLinkNodeNum(&t1));

    insertFromNodeBehind(head, 4, &new);
    printfLink(head);

    head = insertFromNodeFront(head, 1, &new2);
    printfLink(head);

    head = insertFromNodeFront(head, 5, &new3);
    printfLink(head);

    head = deleteNode(head, 102);
    printfLink(head);

    head = deleteNode(head, 100);
    printfLink(head);

    // int a = searchLinkNodeData(&t1, 2);
    // if (a != 0)
    // {
    //     printf("找到数据");
    // }
    // else
    // {
    //     printf("未到数据");
    // }
    return 0;
}
