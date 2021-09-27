#include<iostream>
#include <iomanip>
using namespace std;
#define INF 2147483647
class Visit;
//进程请求类
class Request
{
public:
    Request(int num)
    {
        number = num;
        finish = false;
    }
    void reset();//复位，重新标记finish为未访问
    void achieve();//标记该请求已经完成
    friend void FCFS(Request** request, Visit** visit, int num, int begin);
    friend void SSTF(Request** request, Visit** visit, int num, int begin);
    friend void SCAN(Request** request, Visit** visit, int num, int begin, bool direction);
    friend void show_visit(Visit** visit, int num, int begin);
private:
    int number;//磁道号
    bool finish;//是否完成访问
};
void Request::reset()
{
    finish = false;
}
void Request::achieve()
{
    finish = true;
}

//磁盘访问类
//记录访问顺序和移动距离
class Visit
{
public:
    Visit()
    {
        number = -1;
        distance = -1;
    }
    void reset();//复位。记录清空
    friend void FCFS(Request** request, Visit** visit, int num, int begin);
    friend void SSTF(Request** request, Visit** visit, int num, int begin);
    friend void SCAN(Request** request, Visit** visit, int num, int begin, bool direction);
    friend void show_visit(Visit** visit, int num, int begin);
private:
    int number;//被访问的磁道号
    int distance;//移动距离
};
void Visit::reset()
{
    number = -1;
    distance = -1;
}

//FCFS算法
void FCFS(Request** request, Visit** visit, int num, int begin)
{
    for (int i = 0; i < num; i++)
    {
        //加入已访问队列
        visit[i]->number = request[i]->number;
        visit[i]->distance = abs(begin - request[i]->number);
        //跟新磁头位置，并标记已访问
        begin= request[i]->number;
        request[i]->finish = true;
    }
}

//SSTF算法
void SSTF(Request** request, Visit** visit, int num, int begin)
{
    Request *point;
    for (int i = 0; i < num; i++)
    {
        //先指向无穷大
        point = new Request(INF);
        for (int j = 0; j < num; j++)
        {
            //若当前请求距离更短且未被访问过，则指向当前请求
            if ((abs(point->number - begin) > abs(request[j]->number - begin)) && request[j]->finish == false)
            {
                point = request[j];
            }
        }
        //加入已访问队列
        visit[i]->number = point->number;
        visit[i]->distance = abs(begin - point->number);
        //跟新磁头位置，并标记已访问
        begin = point->number;
        point->finish = true;
    }
    return;
}

//SCAN算法
void SCAN(Request** request, Visit** visit, int num, int begin, bool direction)
{
    //求得边界
    int max = -INF, min = INF;
    for (int i = 0; i<num; i++)
    {
        if (max < request[i]->number)
        {
            max = request[i]->number;
        }
        if (min > request[i]->number)
        {
            min = request[i]->number;
        }
    }
    Request *point;
    for (int i = 0; i < num; i++)
    {
        //先指向无穷大
        point = new Request(INF);
        for (int j = 0; j < num; j++)
        {
            //若和当前访问方向相反则忽略
            if ((direction == false && request[j]->number < begin) || (direction == true && request[j]->number > begin))
            {
                continue;
            }
            //若当前请求距离更短且未被访问过，则指向当前请求
            if ((abs(point->number - begin) > abs(request[j]->number - begin)) && request[j]->finish == false)
            {
                point = request[j];
            }
        }
        //加入已访问队列
        visit[i]->number = point->number;
        visit[i]->distance = abs(begin - point->number);
        //跟新磁头位置，并标记已访问
        begin = point->number;
        point->finish = true;
        //若到头，则掉头
        if (direction == false && point->number == max)
        {
            direction = true;
        }
        if (direction == true && point->number == min)
        {
            direction = false;
        }
    }
    return;
}

void show_option()
{
    cout << "\n****************************" << endl;
    cout << "******    算法选择    ******" << endl;
    cout << "****** 1、FCFS算法    ******" << endl;
    cout << "****** 2、SSTF算法    ******" << endl;
    cout << "****** 3、SCAN算法    ******" << endl;
    cout << "****** 4、退出        ******" << endl;
    cout << "****************************\n" << endl;
}

void show_visit(Visit** visit, int num, int begin)
{
    cout << "—————————————" << endl;
    cout << "     从" << begin << "号磁道开始" << endl;
    cout << "  ———————————  " << endl;
    cout << "被访问磁道号\t移动距离" << endl;
    for (int i = 0; i < num; i++)
    {
        cout << "    " << visit[i]->number << "\t\t  " << visit[i]->distance << endl;
    }


    float ans = 0;
    for (int i = 0; i < num; i++)
    {
        ans += visit[i]->distance;
    }
    //保留两位小数点后两位
    cout << "  ———————————  " << endl;
    cout << "   平均寻道长度：" << fixed << setprecision(2) << ans/num << endl;
    cout << "—————————————" << endl;
}

//Request和Visit复位
void reset(Request** request, Visit** visit, int num)
{
    for (int i = 0; i < num; i++)
    {
        request[i]->reset();
        visit[i]->reset();
    }
    return;
}

int main()
{
    int num, temp, begin;
    Request* request[100];
    Visit* visit[100];
    cout << "请输入请求总数：";
    cin >> num;
    cout << "请输入请求序列：";
    for (int i = 0; i < num; i++)
    {
        cin >> temp;
        request[i] = new Request(temp);
        visit[i] = new Visit();
    }
    cout << "请输入开始磁道号：";
    cin >> begin;

    int flag;
    while (true)
    {
        show_option();
        cout << "请选择功能：";
        cin >> flag;
        if (flag == 1)
        {
            //FCFS算法
            reset(request, visit, num);
            FCFS(request, visit, num, begin);
            show_visit(visit, num, begin);
        }
        else if (flag == 2)
        {
            //SSTF算法
            reset(request, visit, num);
            SSTF(request, visit, num, begin);
            show_visit(visit, num, begin);
        }
        else if (flag == 3)
        {
            //SCAN算法
            bool direction;
            cout << "请输入移动方向（0.由里向外 1.由外向里）：";
            cin >> direction;
            reset(request, visit, num);
            SCAN(request, visit, num, begin, direction);
            show_visit(visit, num, begin);
        }
        else if (flag == 4)
        {
            //退出
            cout << "成功退出！" << endl;
            break;
        }
    }
    return 0;
}