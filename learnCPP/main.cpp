#include <iostream> //输入十进制正整数输出八进制，十六进制，二进制数,输入布尔值输出true or false
using namespace std;

void BinaryRecursion(int n){
    int x;
    x = n % 2;
    n = n >> 1;
    if(0 != n){
        BinaryRecursion(n);
    }
    cout << x;
}

int main() {
    cout << "请输入一个十进制正整数：" << endl;
    int x;
    cin >> x;
    cout << oct << x << endl;
    cout << hex << x << endl;
    BinaryRecursion(x);
    cout << endl;
    cout << "请输入一个布尔值：" << endl;
    bool a = false;
    cin >> a;
    cout << boolalpha << a << endl;
    return 0;
}
