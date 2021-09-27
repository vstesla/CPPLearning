#include <iostream>

using namespace std; // using std::string;

class AbstractEmployee { //abstract class
  virtual void AskForPromotion() = 0;
};

class Employee : AbstractEmployee { //inherited

 private:
  string Company;
  int Age;
 protected:
  string Name;
 public:
  void setName(string name) { //setters
    Name = name;
  }
  string getName() { //getters
    return Name;
  }
  void setCompany(string company) {
    Company = company;
  }
  string getCompany() {
    return Company;
  }
  void setAge(int age) {
    if (age >= 30) { //Only when the age older than 30 the change below will apply
      Age = age;
    }

  }
  int getAge() {
    return Age;
  }

  void Intro() {
    cout << "Name - " << Name << endl;
    cout << "Company - " << Company << endl;
    cout << "Age - " << Age << endl;
  }

  Employee(string name, string company, int age) {
    Name = name;
    Company = company;
    Age = age;
  }

  void AskForPromotion() {
    if (Age >= 30)
      cout << Name << " got promoted!" << endl;
    else
      cout << Name << " no promotion for you." << endl;
  }
  virtual void Work() { //Polymorphism. virtual function
    cout << Name << " is checking email, task backlog, preforming tasks..." << endl;
  }
};

class Developer : public Employee { //Developer class is now a subclass, Employee class is now a superclass
 public:
  string FavProgLang;
  Developer(string name, string company, int age, string FavPorgLang) : Employee(name, company, age) {
    FavProgLang = FavPorgLang;
  }
  void FixBug() {
    cout << Name << " fixed bug using " << FavProgLang << endl;
  }
  void Work() { //Polymorphism
    cout << Name << " is writing " << FavProgLang << " code" << endl;
  }
};

class Teacher : public Employee {
 public:
  string Subject;
  void PrepareLesson() {
    cout << Name << " is preparing " << Subject << " lesson" << endl;
  }

  Teacher(string name, string company, int age, string subject) : Employee(name, company, age) {
    Subject = subject;
  }
  void Work() { //Polymorphism
    cout << Name << " is teaching " << Subject << " lesson" << endl;
  }
};

int main() {

  Employee employee1 = Employee("Victor", "Google", 30);
//  employee1.Name = "Victor";
//  employee1.Company = "Google";
//  employee1.Age = 20;
  employee1.Intro();

  Employee employee2 = Employee("Steve", "Amazon", 25);
//  employee2.Name = "Steve";
//  employee2.Company = "Amazon";
//  employee2.Age = 25;
  employee2.Intro();
//  employee1.AskForPromotion();
//  employee2.AskForPromotion();
  Developer dev = Developer("Josh", "YouTube", 40, "CPP");
  dev.FixBug();
  dev.AskForPromotion();

  Teacher t = Teacher("Jack", "Rainbow school", 35, "Physics");
  t.PrepareLesson();
  t.AskForPromotion();

  employee1.Work(); //The most common use of polymorphism is when a parent class reference is used to refer to a child class object
  dev.Work();
  t.Work();

  Employee *e1 = &dev;
  Employee *e2 = &t;
  Employee *e3 = &employee1;

  e1->Work();
  e2->Work();
  e3->Work();

  employee1.setAge(15);//Age is younger than 30, so this change here will not apply
  cout << employee1.getName() << " is " << employee1.getAge() << " years old" << endl;

  return 0;
}
