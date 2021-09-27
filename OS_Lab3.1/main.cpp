#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;
const int MAX=512;
char c;
int counts,num;//统计块数,申请资源个数

typedef struct Job{
    char name;
    int start;
    int length;
    char status;//是否分配的标志
}Job;

Job OS[MAX];

void init();//初始化
void insert(int m, int st, int en);//插入数据
void remove(int m);//删除
void merge(int m, int st, int en);//合并
void show();//输出当前存储器分配情况
void put();//录入数据
bool apply();//申请资源
bool free();//释放资源


void init(){

    counts = 1;
    OS[0].name = 'S';//未分配空间命名为S
    OS[0].start = 0;//起始位置0
    OS[0].length = MAX;
    OS[0].status = 'U';//未分配记U，分配记D
}


void insert(int m, int st, int en){

    counts++;//每次申请令分区数量加1
    for (int i = counts; i > m ; i--)//插入数据
        OS[i] = OS[i - 1];
    OS[m].start = st;//记录起始位置
    OS[m].length = en;//记录长度
}


void remove(int m){

    for (int i = m; i < counts - 1; i++)//数据整体向前移覆盖掉m实现删除
        OS[i] = OS[i + 1];
    counts--;//分区数量--
}


void merge(int m, int st, int en){

    if((OS[m - 1].status == 'D' || m == 0) && (OS[m + 1].status == 'D' || m == counts)){//m前后都已分配则不合并
        OS[m].name = 'S';
        OS[m].status = 'U';
    }else if(OS[m - 1].status == 'U'){//与前一个合并
        OS[m - 1].length = OS[m - 1].length + en;//通过改变前面空间长度实现合并
        remove(m);//删除已合并的m
    }else if(OS[m + 1].status == 'U'){//与后一个合并
        OS[m].length = OS[m].length + OS[m + 1].length;
        OS[m].name = 'S';//修改m状态
        OS[m].status = 'U';
        remove(m + 1);//删除后一个空间
    }
}


void show(){

    cout<<"名称\t标识\t起址\t长度\t状态"<<endl;
    for(int i = 0; i < counts; i++){
        if(OS[i].status == 'U') cout<<"S\t";
        else cout<<OS[i].name<<"\t";
        cout<<i<<"\t"<<OS[i].start<<"\t"<<OS[i].length<<"\t"<<OS[i].status<<endl;
    }
}


void put(){

    cout<<"输入申请或者释放的进程名称及空间大小："<<endl;
    cin>>c;
    cin>>num;
}


bool apply(){

    int i = 0;
    int flag = 0;//标记是否申请成功
    while(!flag && i < counts){
        if(OS[i].length >= num && OS[i].status == 'U'){
            if(OS[i].length == num){//刚好等于num时
                OS[i].name = c;
                OS[i].status = 'D';
            }
            else{//分成两部分，未分配的和分配的
                insert(i + 1, OS[i].start + num, OS[i].length - num);//用减法实现插入空闲的分区
                OS[i + 1].status = 'U'; //标记为未分配
                OS[i + 1].name = 'S';
                OS[i].name = c;
                OS[i].length = num;
                OS[i].status = 'D';//标志分配
            }
            flag = 1;//成功
        }
        i++;
    }

    if(flag){
        cout<<"申请成功"<<endl;
        return true;
    }else{
        cout<<"没有足够大空间"<<endl;
        return false;
    }
}


bool free(){

    int i = 0;
    int flag = 0;//标记是否释放成功
    while (!flag && i < counts){
        if (OS[i].name == c){//寻找作业
            if (OS[i].length == num)	merge(i, OS[i].start, OS[i].length);
            else{
                if (OS[i].length > num){//不全部释放，将作业拆成已分配和未分配

                    insert(i + 1, OS[i].start + num, OS[i].length - num);
                    OS[i+1].name = c;
                    OS[i+1].status = 'D';
                    OS[i].length = num;
                    OS[i].status = 'U';
                    //检查是不是能进行合并
                    if (OS[i-1].status == 'U')	merge(i, OS[i].start, OS[i].length);
                }else{
                    cout<<"正使用的数量小于释放的数量"<<endl;
                    return 0;
                }
            }
            flag = 1;//成功
        }
        i++;//没找到作业就++
    }

    if (flag){
        cout<<"释放成功"<<endl;
        return true;
    }else{
        cout<<"未找到匹配的进程名称"<<endl;
        return false;
    }
}

int main(void){

    int code;
    init();
    while (1){
        cout<<"————————————————————————————————————————"<<endl;
        cout<<"选择操作："<<"  1.查看  "<<"  2.申请  "<< "	3.释放  "<<"  0.退出  "<<endl;

        cin>>code;
        switch(code){
            case 1: show();break;

            case 2: put();
                apply();
                show();
                break;

            case 3: put();
                free();
                show();
                break;

            case 0:
                break;

            default: cout << "指令错误重新输入！" << endl;
        }
        cout<<"————————————————————————————————————————"<<endl;
        if(code == 0)
            break;
    }

}