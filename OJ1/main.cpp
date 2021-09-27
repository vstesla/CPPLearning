#include <stdio.h>
#include <stdbool.h>
#define Maximize 30
#define JobNum 6
#define null -1

typedef struct
{
    int base;
    int length;
}Area;
typedef struct
{
    Area arr[Maximize];
    int length;
}Free_List;
static Area Job[6];

void init_list ( Free_List* L )
{
    L->length = 1;
    L->arr[0].base = 0;
    L->arr[0].length = 512;
}

int search_free_area ( int need, Free_List* L )
{
    for ( int i = 0; i < L->length; i++ )
        if ( need <= L->arr[i].length )
            return i;
}

void alloc ( Free_List* L, int num, int job_num )
{
    if ( Job[job_num].length < L->arr[num].length ) {
        Job[job_num].base = L->arr[num].base;
        L->arr[num].base = Job[job_num].base + Job[job_num].length + 1;
        L->arr[num].length = L->arr[num].length - Job[job_num].length;
    }else {
        L->arr[num] = { null, null };
    }
}

int main()
{
    int job_num, need_mem;
    char loop_code;
    Free_List L;
    init_list(&L);
    while ( true ) {
        printf("请输入申请资源的作业: ");
        scanf("%d", &job_num);
        printf("请输入申请资源的大小: ");
        scanf("%d", &Job[job_num].length);
        int num = search_free_area( Job[job_num].length, &L );
        alloc( &L, num, job_num );
        printf("是否继续分配，是请按y，否则按其他键退出: ");
        scanf("%c", &loop_code);
        if ( loop_code != 'y' )
            break;
    }
}