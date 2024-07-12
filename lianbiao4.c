#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
unsigned char myarr[] = {
    0xcb,
    0x5a,
    0xff,
    0xff,
    0xff,
    0xff,
    0xbf,
    0xae,
    0x1c,
    0x24,
    0xde,
    0x03,
    0xdf,
    0x0b,
    0xdf,
    0x0b,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0xff,
    0x03,
    0xff,
    0x03,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x3f,
    0x14,
    0x5f,
    0x14,
    0x5f,
    0x1c,
    0x7f,
    0x1c,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
};

unsigned char myarr1[] = "kadgk";
unsigned char myarr2[] = {0x11, 0x22, 0x33, 0x77, 0x88, 0x99, 0xaa};

int open_size = 0;    // 开辟的总空间
int release_size = 0; // 释放的总空间

// 定义一个结构体
struct test
{
    int num;
    unsigned char *arr;
    struct test *next;
};

// 封装一个新malloc函数统计开辟的空间
void *my_malloc(size_t size, int *my_open_size)
{
    void *p = malloc(size);
    if (p == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    *my_open_size += size;
    return p;
}

// 封装一个新free函数统计释放的空间
void my_free(void *p, int my_release_size)
{
    free(p);
    release_size += my_release_size;
}

// 遍历链表
void printfLink(struct test *head)
{
    struct test *p;
    p = head;
    while (p != NULL)
    {
        printf("数组个数 = %4d ----", strlen(p->arr));
        for (int i = 0; i < p->num; i++)
        {
            if (p->arr[i] == '\0')
            {
                break;
            }
            printf("%02x ", p->arr[i]);
        }
        printf("\n");
        p = p->next;
    }
    printf("\n");
}

// 创建不被释放的头节点
struct test *creat_head_node()
{
    struct test *newnode = (struct test *)my_malloc(sizeof(struct test), &open_size);
    if (newnode == NULL)
    {
        printf("creat ListNode error\n");
        return NULL;
    }
    newnode->num = 2;
    newnode->arr = (unsigned char *)my_malloc(2 * sizeof(unsigned char), &open_size);
    newnode->next = NULL;
    newnode->arr[0] = 0xaa;
    newnode->arr[1] = '\0';
    if (newnode->arr == NULL)
    {
        printf("内存分配失败\n");
        free(newnode);
        return NULL;
    }
    int struct_size = sizeof(struct test) + 2 * sizeof(unsigned char);
    printf("创建头节点，开辟了%d个字节空间\n", struct_size);
    return newnode;
}

/*
 创建节点,开辟空间
 参数的num：为里面arr数组的元素个数
*/
struct test *creat_link_arr(int arr_num)
{
    struct test *newnode = (struct test *)my_malloc(sizeof(struct test), &open_size);
    if (newnode == NULL)
    {
        printf("BuySListNode error\n");
        return NULL;
    }
    newnode->num = arr_num;
    newnode->next = NULL;
    newnode->arr = (unsigned char *)my_malloc((arr_num + 1) * sizeof(unsigned char), &open_size);
    if (newnode->arr == NULL)
    {
        printf("内存分配失败\n");
        free(newnode);
        return NULL;
    }
    int struct_size = sizeof(struct test) + sizeof(unsigned char) * (arr_num + 1);
    printf("创建一个节点，开辟了%d字节空间, ", struct_size);
    return newnode;
}

// 释放内存---清空链表---保留头节点
void free_link_list(struct test *head)
{
    struct test *current = head->next; // 保留头节点
    head->next = NULL;                 // 必须要赋值为NULL不然遍历会出错
    struct test *temp;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        printf("arr的元素个数为 %d\n", strlen(temp->arr));
        int arr_num = strlen(temp->arr);
        int struct_size = sizeof(temp->num) + sizeof(temp->next) + sizeof(unsigned char) * strlen(temp->arr) + sizeof(temp->next);

        free(temp->arr);
        temp->arr = NULL;

        int arr_size = 1;
        int node_size = 1;

        if (NULL == temp->arr)
        {
            arr_size = 0;
        }

        free(temp);
        temp = NULL;
        if (NULL == temp)
        {
            node_size = 0;
        }
        printf("删除节点,原数据结构体占空间大小为 %d 个字节,数组元素个数为 %d ,占 %d 个字节空间,释放数值后剩余 %d 个字节空间,删除节点后剩余 %d 个字节空间\n",
               struct_size, arr_num, sizeof(unsigned char) * arr_num, arr_size, node_size);
    }
    temp = NULL;
}

/*
 给节点赋值
 *head： 头节点
 num：   结构体里面对应数组的个数
*/
void insert_from_tail1(struct test *head, int num, unsigned char arr[])
{
    struct test *p = head;
    struct test *newnode = creat_link_arr(num);
    memcpy(newnode->arr, arr, num);
    newnode->arr[num] = '\0'; // 在数组末尾加一个结束的标志==='\0'
    printf("开辟的数组元素个数为%d,写入的元素个数为：%d\n", num, strlen(newnode->arr));
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newnode;
}

// 读取节点内容
void read_node_oldest(struct test *head)
{
    struct test *p;
    struct test *temp;
    p = head->next;
    while (p != NULL)
    {
        // printf("arr的元素个数为 %4d\n", strlen(p->arr));
        int reality_arr_num = strlen(p->arr);
        int apply_arr_num = p->num;
        int struct_size = sizeof(struct test) + sizeof(unsigned char) * (p->num + 1);

        printf("读取的数据为：\n");
        for (int i = 0; i < p->num; i++)
        {
            printf("%02x ", p->arr[i]);
        }

        temp = p;
        head->next = p->next;

        my_free(temp->arr, sizeof(unsigned char) * (p->num + 1));
        temp->arr = NULL;
        int arr_size = 1;
        int node_size = 1;

        if (NULL == temp->arr)
        {
            arr_size = 0;
        }
        my_free(temp, sizeof(struct test));
        temp = NULL;
        printf("\n");
        p = head->next;
        if (NULL == temp)
        {
            node_size = 0;
        }
        printf("删除节点,原数据结构体占空间大小为 %d 个字节,申请的数组元素个数为 %d ,占 %d 个字节空间,读取的元素个数为：%d,释放数值后剩余 %d 个字节空间,删除节点后剩余 %d 个字节空间\n",
               struct_size, apply_arr_num, sizeof(unsigned char) * apply_arr_num, reality_arr_num, arr_size, node_size);
        printf("\n");
    }
}

// 删除链表尾部
void delete_link_list_form_behind(struct test *head)
{
    if (head->next == NULL)
    {
        return;
    }
    else
    {
        // 尾部节点
        struct test *tail = head;
        // 尾部前一个节点
        struct test *prev_tail = NULL;
        while (tail->next != NULL)
        {
            prev_tail = tail;
            tail = tail->next;
        }

        printf("arr的元素个数为 %d\n", strlen(tail->arr));
        int arr_num = strlen(tail->arr);
        int struct_size = sizeof(tail->num) + sizeof(tail->next) + sizeof(unsigned char) * strlen(tail->arr) + sizeof(tail->next);

        // 释放尾节点的数据空间
        free(tail->arr);
        tail->arr = NULL;
        int arr_size = 1;
        int node_size = 1;

        if (NULL == tail->arr)
        {
            arr_size = 0;
        }

        // 释放尾节点
        free(tail);
        tail = NULL;
        // 把尾节点的next指向空
        prev_tail->next = NULL;
        if (NULL == tail)
        {
            node_size = 0;
        }
        printf("删除节点,原数据结构体占空间大小为 %d 个字节,数组元素个数为 %d ,占 %d 个字节空间,释放数值后剩余 %d 个字节空间,删除节点后剩余 %d 个字节空间\n",
               struct_size, arr_num, sizeof(unsigned char) * arr_num, arr_size, node_size);
    }
}

// 统计链表节点个数
int get_link_list_node_num(struct test *head)
{
    int cnt = 0;
    struct test *p = head;
    while (p != NULL)
    {
        p = p->next;
        cnt++;
    }
    return cnt;
}

int main()
{
    struct test *head = creat_head_node();

    int myarr2_num = sizeof(myarr2) / sizeof(myarr2[0]);
    insert_from_tail1(head, myarr2_num, myarr2);
    insert_from_tail1(head, 10, myarr1);
    insert_from_tail1(head, 20, myarr);
    insert_from_tail1(head, 30, myarr);
    insert_from_tail1(head, 40, myarr);
    insert_from_tail1(head, 100, myarr);
    printfLink(head);

    // delete_link_list_form_behind(head);
    // printfLink(head);

    // int num = get_link_list_node_num(head);
    // printf("链表的节点个数为 = %d\n", num);

    // free_link_list(head);
    read_node_oldest(head);
    printfLink(head);
    printf("总共开辟的空间大小为：%d\n", open_size);
    printf("总共释放的空间大小为：%d\n", release_size);
    printf("剩余开辟-释放的空间大小为：%d\n", open_size - release_size);
    return 0;
}