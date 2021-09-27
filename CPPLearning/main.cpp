#include <iostream>
#include <cmath>
#include <bitset>

#define maxsize 100
#define overflow -2
#define error -1
#define ok 0

using namespace std;

class Chef{ //SuperClass
public:
    void makeChicken(){
        cout << "The chef makes chicken" << endl;
    }
    void makeSalad(){
        cout << "The chef makes salad" << endl;
    }
    void makeOtherdish(){
        cout << "The chef makes Pork" << endl;
    }
};

class ChineseChef: public Chef{ //SubClass
public:
    void makeYuxiangrousi(){
        cout << "The Chinese chef makes yuxiangrousi" << endl;
    }
    void makeOtherdish(){
        cout << "The chef makes BBQ ribs" << endl;
    }
};

class Movie{
private:
    string actor;
public:
    string title;
    string director;
    string rating;

    Movie(string aTitle, string aDirector, string aRating, string aActor){
        title = aTitle;
        director = aDirector;
        rating = aRating;
        setActor(aActor);


    }
    void setActor(string aActor){
        if(aActor == "Steve" || aActor == "Johnson"){
            actor = aActor;
        }
        else actor = "Unknown actor";

    }

    string getActor(){
        return actor;
    }
};

class Book {
public:
    string title;
    string author;
    int pages;

    Book(string aTitle, string aAuthor, int aPages){
        title = aTitle;
        author = aAuthor;
        pages = aPages;

    }

};

typedef struct {
    int *base;
    int *top;
    int stacksize;
} SqStack;

int InitStack(SqStack &S) {

    S.base = new int[maxsize];
    if (!S.base)exit(overflow);
    S.top = S.base;
    S.stacksize = maxsize;
    return ok;
}

int Pop(SqStack &S, int &e) {
    if (S.top == S.base) return error;
    e = *--S.top;
    return ok;
}

bool StackEmpty(SqStack S) {
    if (S.top == S.base) return true;
    else return false;


}

int Push(SqStack &S, int e) {
    if (S.top - S.base == S.stacksize) return error;
    *S.top++ = e;
    return ok;
}

double calculator(double num1, double num2, char op, double result) {
    int cycle;

    do {
        cout << "Please enter the number1 you want to calculate:";
        cin >> num1;
        cout << "Then the second number:";
        cin >> num2;
        cout << "Choose a operate you want to execute(+,-,*,/,^,srt=~,transcode=t):";
        cin >> op;

        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                } else {
                    cout << "ERROR. You can not let the dividend equals to 0." << endl;
                    break;
                }
                break;
            case '^':
                result = pow(num1, num2);
                break;
            case '~':
                if (num1 >= 0) {
                    if (num2 != 0) {
                        result = pow(num1, 1 / num2);
                    } else {
                        cout << "The order of the root can not be 0." << endl;
                        break;
                    }
                } else {
                    cout << "The number inside the root can not be negative." << endl;
                    break;
                }
                break;
            case 't':
                cout << "The binary code of " << num1 << " is:" << bitset<8>(num1) << endl;
                cout << "The octonary code of " << num1 << " is:" << oct << num1 << endl;
                cout << "The hexadecimal code of " << num1 << " is:" << hex << num1 << endl;
                cout << "The binary code of " << num2 << " is:" << bitset<8>(num2) << endl;
                cout << "The octonary code of " << num2 << " is:" << oct << num2 << endl;
                cout << "The hexadecimal code of " << num2 << " is:" << hex << num2 << endl;

            default:
                cout << "Invalid operator" << endl;

        }

        cout << "The answer is:" << result << endl;
        result = NULL;
        cout << "Do you have another pill of numbers need to calculate(1/0):";
        cin >> cycle;
    } while (cycle == 1);

    return result;
}

double cube(double num) {
    cout << "Enter a num you want to cube:";
    cin >> num;
    double result = pow(num, 3);
    cout << "The answer is:" << result << endl;
    return result;
}

void StuInfo(string stuname, int age, bool gender, int classnum) {

    string displaygen;
    cout << "Tell us your name:";
    getline(cin, stuname);
    cout << endl;
    cout << "And your age:";
    cin >> age;
    cout << endl;
    cout << "And your gender(Type in 0 or 1):";
    cin >> gender;
    if (gender == false)
        displaygen = "boy";
    else displaygen = "girl";
    cout << endl;
    cout << "And your classnum:";
    cin >> classnum;
    cout << endl;
    cout << "OK. Hi, " << stuname << ". You are " << age << " years old. You are a " << displaygen << " from class "
         << classnum << endl;


}

int stoneTolb(int sts) {
    return 14 * sts;
}

int weightConvert(int stone) {
    cout << "Enter the weight in stone: ";
    cin >> stone;
    int pounds = stoneTolb(stone);
    cout << stone << " stone = ";
    cout << pounds << " pounds." << endl;
    return pounds;
}

int housearea(double area) {

    cout << "Enter the area of the floor, in square meters, of your home: ";
    cin >> area;
    double side;
    side = sqrt(area);
    cout << "That's the equivalent of a square which is " << side
         << " meters to the side." << endl;

    return side;

}

int main() {

    Chef chef;
    chef.makeChicken();
    chef.makeOtherdish();
    ChineseChef CNchef;
    CNchef.makeYuxiangrousi();
    CNchef.makeOtherdish();

    Movie avengers("The Avengers", "Joss Whedon", "PG-13", "Steve");
    cout << avengers.rating << endl;
    avengers.setActor("Johnson");
    cout << avengers.getActor() << endl;



    Book book1("Lord of the rings", "Tolkein", 500);
    cout << book1.title << endl;

    int age1 = 19;
    int *pAge1 = &age1;
    double gpa = 2.7;
    double *pGpa = &gpa;
    string name1 = "Victor";
    string *pName = &name1;

    cout << *pAge1 << ";" << pGpa << ";" << pName << endl;

    int N, e, a, loop;
    do {
        SqStack S;
        InitStack(S);
        printf("请问你要转换成什么进制的：");
        cin >> a; //a表示的是你想要转换的进制
        printf("请输入你想要转换的数：");
        cin >> N; //N为你输入的十进制的数字
        while (N) {
            Push(S, N % a);
            N = N / a;

        }
        printf("转换后的数字为\n");

        while (!StackEmpty(S)) {
            Pop(S, e);
            cout << e;
        }
        cout << endl;
        cout << "Do you have another pill of numbers need to calculate(1/0):";
        cin >> loop;
    } while (loop == 1);

    //Transcode
    double num1;
    double num2;
    char op;
    double result;
    cout << "Get trouble in calculation? Let me help!" << endl;
    calculator(num1, num2, op, result);
//calculator
    double num;
    cube(num);
    //cube a number
    string stuname;
    int age;
    bool gender;
    int classnum;
    StuInfo(stuname, age, gender, classnum);
    //display students info
    int luckyNums[25];
    luckyNums[0] = 1;
    cout << luckyNums[0] << endl;
    string name;
    cout << "Enter your name:";
    getline(cin, name);
    cout << "Hi," << name << endl;

    string phrase = "My name is VST";
    phrase[0] = 'H';
    phrase[1] = 'i';
    phrase[2] = 's';
    cout << phrase.find("VST", 0) << endl;
    cout << phrase.substr(3, 11) << endl;
    cout << 6 * 6 << endl;
    cout << fmax(20, 22) << endl;
    int appleNum;
    double area;
    int stone;
    cout << "How many apples do you have?" << endl;
    cin >> appleNum;
    cout << "I have " << appleNum << " apples." << endl;
    housearea(area);
    weightConvert(stone);
    return 0;
}
