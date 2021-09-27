#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Maximize 30
#define JobNum 6
#define null -1

typedef struct
{
    int start;
    int length;
}Area;                                                                  //作业/空闲区基址及长度
typedef struct
{
    Area arr[Maximize];
    int length;
}Free_List;                                                             //空闲分区表结构
static Area Job[JobNum] = { null, null };

void init_list ( Free_List* );                                          //初始化空闲分区队列
int search_free_area ( int, Free_List* );                               //查找合适的空闲分区号
void alloc ( Free_List*, int, int );                                    //分配空闲分区
int search_insert_area ( int, Free_List* );                             //寻找被释放空间的插入区域
void release ( Free_List*, int, int );                                  //将释放的空间插入空闲分区表
void Print_List ( Free_List* );                                         //打印空闲分区表

void init_list ( Free_List* L )
{
    L->length = 1;
    L->arr[0].start = 0;
    L->arr[0].length = 512;
}

int search_free_area ( int need, Free_List* L )
{
    for ( int i = 0; i < L->length; i++ )
        if ( need <= L->arr[i].length )
            return i;
    printf("分配失败，退出\n");
    exit(EXIT_FAILURE);
}

void alloc ( Free_List* L, int order, int job_order )
{
    if ( Job[job_order].length < L->arr[order].length ) {
        Job[job_order].start = L->arr[order].start;
        L->arr[order].start = Job[job_order].start + Job[job_order].length + 1;
        L->arr[order].length = L->arr[order].length - Job[job_order].length;
    }else {
        L->arr[order] = (Area){ null, null };
        L->length--;
    }
}

int search_insert_area ( int start, Free_List* L )
{
    for ( int i = 0; i < L->length; i++ )
        if ( ( start < L->arr[i].start ) || ( i == L->length - 1 ) )
            return i;
}

void release ( Free_List* L, int order, int job_order )
{
    if ( Job[job_order].start == L->arr[order - 1].start + L->arr[order - 1].length + 1 )
        L->arr[order - 1].length += Job[job_order].length;
    else if ( Job[job_order].start == Job[job_order].start + Job[job_order].length + 1 ) {
        L->arr[order].length += Job[job_order].length;
        L->arr[order].start = Job[job_order].start;
    }else if ( ( Job[job_order].start == L->arr[order - 1].start + L->arr[order - 1].length + 1 ) && ( Job[job_order].start == Job[job_order].start + Job[job_order].length + 1 ) ) {
        L->arr[order - 1].length += Job[job_order].length + L->arr[order].length;
        for ( int i = order; i < L->length; i++ )
            L->arr[i] = L->arr[i + 1];
    }else {
        L->length++;
        for ( int i = L->length - 1; i > order; i-- )
            L->arr[i] = L->arr[i - 1];
        L->arr[order].start = Job[job_order].start;
        L->arr[order].length = Job[job_order].length;
    }
    Job[job_order] = (Area){ null, null };
}

void Print_List ( Free_List* L )
{
    printf("|   序号   |    起址    |   长度   |   状态   |\n");
    printf("+-----------+-----------+-----------+-----------+\n");
    for ( int i = 0; i < L->length; i++ )
        printf("|   %d   |   %d   |   %d   |   未分配   |\n", i + 1, L->arr[i].start, L->arr[i].length);
}

int main()
{
    int job_order;
    char loop_code, oper_code;
    Free_List L;
    init_list(&L);
    while ( true ) {
        printf("请输入申请/释放资源的作业: ");
        scanf("%d", &job_order);
        job_order--;
        printf("请输入申请/释放资源的大小: ");
        scanf("%d", &Job[job_order].length);
        printf("申请or释放，申请按1，释放按2: ");
        scanf("%c", &oper_code);
        if (oper_code == '\n')
            oper_code = getchar();
        if ( oper_code == '1' ) {
            int num = search_free_area( Job[job_order].length, &L );
            alloc( &L, num, job_order );
        }else if ( oper_code == '2' ) {
            int num = search_insert_area( Job[job_order].start, &L );
            release( &L, num, job_order );
        }else
            exit(EXIT_FAILURE);
        Print_List(&L);
        printf("是否继续分配/释放，是请按y，否则按其他键退出: ");
        scanf("%c", &loop_code);
        if ( loop_code == '\n' )
            loop_code = getchar();
        if ( loop_code != 'y' )
            break;
    }

    return 0;
}
