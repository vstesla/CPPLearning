#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const int N=5;

void menu(){

    int choose, n, time[N], prio[N], Count;//Count记录待运行进程数
    string name[N];
    int temp[N];//设置temp数组暂存优先级
    char state[N];
    int arr[N] = { 0 };//用数组模拟指针

    while (1){
        cout << "----------------------------" << endl;
        cout << "1.初始化" << endl<< "2.查看进程列表" << endl<< "3.执行" << endl<< "0.退出" << endl;
        cout << "----------------------------" << endl;

        //操作选择
        cin >> choose;
        switch(choose){
            case 1: cout << "----------------------------" << endl;
                cout << "输入进程数：" << endl;
                cin >> n;
                Count = n;//初始待运行进程数为进程数
                for (int i = 0; i < n; i++){
                    cout << "输入进程名、时间、优先数："  << endl;
                    cin >> name[i] >> time[i] >> prio[i];
                    state[i] = 'R';
                    arr[i] = i;//指针初始化
                    cout << endl;
                }
                cout << "----------------------------" << endl;
                break;

            case 2: cout << "----------------------------" << endl;
                if(n==0)
                    cout << "列表为空！" << endl;
                else{
                    cout << "此时进程列表为：（进程 优先级 时间 状态）" << endl;

                    for (int i = 0; i < n; i++)
                        cout << name[i] << " " << prio[i] << " " << time[i] << " " << state[i] << endl;
                }

                cout << "----------------------------" << endl;
                break;

            case 3: while(1){
                    if (Count>0){
                        cout << "----------------------------" << endl;
                        int count = n;
                        //将当前优先级赋值给temp数组
                        for (int i = 0; i < n; i++){
                            temp[i] = prio[i];
                        }
                        while (count != 0){//比较优先级，改变指针数组给队列排序

                            int tmp = 0;
                            for (int i = 0; i < n; i++){
                                if (temp[i] > temp[tmp])
                                    tmp = i;
                            }
                            temp[tmp] = 0;//将加入指针的中间数组改为0
                            arr[n - count] = tmp;
                            count--;
                        }
                        //对排序后优先级最高的进程执行一次操作，即优先级和时间同时--
                        cout << "此时执行进程为：" << name[arr[0]] << endl;

                        prio[arr[0]] -= 1;
                        time[arr[0]] -= 1;

                        cout << "之后执行进程为：";
                        //如果有进程执行完成，更新状态
                        if (time[arr[0]] == 0){
                            state[arr[0]] = 'E';
                            prio[arr[0]] = -100;//把优先级更新为一个足够小的值
                            Count--;
                        }
                        //比较修改后的前两个进程优先级高低，取高的执行
                        if (prio[arr[0]] <= prio[arr[1]]){
                            cout << name[arr[1]] << endl;
                        }
                        else{
                            cout << name[arr[0]] << endl;
                        }
                    }else{
                        cout << "没有可执行的进程" << endl;
                        cout << "----------------------------" << endl;
                        break;
                    }
                }

            case 4:break;

            default:cout << "----------------------------" << endl;
                cout << "命令无效重新输入" << endl;
                cout << "----------------------------" << endl;
                break;
        }
    }
}

int main(){
    menu();
    return 0;
}
/*测试数据
a 5 1
b 4 3
c 6 2
d 1 4
e 2 5
*/