/* Да се дефинира апстрактна класа Employee којашто ќе содржи име на вработениот, години и работно искуство во години (integer). Да се дефинираат чисти виртуелни функции plata() и bonus() (double).

Од класата Employee да се изведе класа SalaryEmployee која покрај основните информации содржи и информација за основната плата. Бонусот на овие работници се пресметува како процент од основната плата, а процентот е бројот на години со работно искуство. На пример ако работеле 10 години, бонусот е 10 проценти од основната плата. Вкупната плата се пресметува како основната плата плус бонусот.

Од класата Employee исто така да се изведе класа HourlyEmployee која покрај основните информации содржи информација и за вкупниот број на часови кои ги одработил работникот и платата по час. Вкупната плата се пресметува како бројот на часови помножен со платата по час плус бонусот, додека бонусот се пресметува на следниот начин: За секој час над 320-тиот се добива 50 проценти од платата по час.

Од класата Employee на крај се изведува класата Freelancer која покрај основните информации содржи и број на проекти на кои работел вработениет и низа со суми кои ги добил за тие проекти (double). По направени 5 проекти, за секој нареден вработените добиваат бонус од 1000 денари. Вкупната плата на овој тип на вработени изнесува вкупната сума добиена од сите проекти плус бонусот.

Да се преоптовари операторот == кој ќе прима два објекти од класата Employee и ќе ги споредува според тоа дали имаат ист број на години.

Да се дефинира класа Company која ќе содржи информации за името на компанијата, бројот на вработени, и динамична низа од покажувачи од класата Employee или Employee **. За потребите на оваа класа треба да се дефинира конструктор кој прима само еден аргумент - името на компанијата, да се преоптовари операторот += и да се дефинираат следните методи:

double vkupnaPlata() - метод којшто ја враќа вкупната плата на сите вработени во компанијата
double filtriranaPlata(Employee * emp) - метод којшто ја враќа платата само на работниците кои се еднакви со дадениот вработен (според оператор ==)
void pecatiRabotnici() - метод којшто печати по колку вработени има од секој тип на работници во компанијата, а форматот на печатење можете да го видите од тест примерите
Hint: За потребите на последниот метод можете да искористите статички членови и статички функции во секоја од класата, dynamic_cast, виртуелна функција која ќе ја преоптоварите во секоја од класите или нешто друго по ваша желба. */


#include <iostream>
#include <cstring>
using namespace std;

class Employee{
protected:
    char name[50];
    int age;
    int experience;

public:
    virtual double plata() = 0;
    virtual double bonus() = 0;

    int getAge(){
        return age;
    }
    bool operator == (const Employee & e){
        if(this->age == e.age){
            return true;
        }
        return false;
    }
};


class SalaryEmployee : public Employee{
protected:
    double baseSalary;
public:
    SalaryEmployee(char name[50],int age,int experience,double baseSalary){
        strcpy(this->name,name);
        this->age = age;
        this->experience = experience;
        this->baseSalary = baseSalary;
    }


    double plata(){
        return baseSalary + bonus();
    }

    double bonus(){
        return baseSalary * experience / 100.0;
    }



};


class HourlyEmployee : public Employee{
protected:
    int hoursWorked;
    double hourlySalary;
public:
    HourlyEmployee(char name[50],int age,int experience,int hoursWorked,double hourlySalary){
        strcpy(this->name,name);
        this->age = age;
        this->experience = experience;
        this->hoursWorked = hoursWorked;
        this->hourlySalary = hourlySalary;
    }

    double plata(){
        return hourlySalary * hoursWorked + bonus();
    }

    double bonus(){
        if(hoursWorked > 320) {
           return  (hoursWorked - 320) * (hourlySalary * 0.5);
        }
        return 0;
    }
};


class Freelancer : public Employee{
protected:
    int numberOfProjects;
    double * projects;
public:
    Freelancer(char name[50],int age,int experience,int numberOfProjects,double * projects){
        strcpy(this->name,name);
        this->age = age;
        this->experience = experience;
        this->projects = new double[numberOfProjects];
        this->numberOfProjects= numberOfProjects;
        for(int i = 0; i < numberOfProjects; i++){
            this->projects[i] = projects[i];
        }
    }

    double plata(){
        double total = 0;
        for(int i= 0; i < numberOfProjects; i++){
            total += projects[i];
        }
        return total + bonus();
    }

    double bonus(){
        if(numberOfProjects > 5) {
            return  (numberOfProjects - 5) * 1000;
        }
        return 0;
    }
};

class Company{
    char name[50];
    int numberOfEmployees;
    Employee ** employees;

public:
    Company(char name[50]){
        strcpy(this->name,name);
        this->numberOfEmployees = 0;
        this->employees = new Employee* [numberOfEmployees];

    }

    Company & operator += (Employee * e){
        Employee ** tmp = new Employee *[numberOfEmployees+1];
        for(int i = 0;i < numberOfEmployees; i++){
            tmp [i] = employees [i];
        }
        tmp[numberOfEmployees++] = e;
        delete [] employees;
        employees = tmp;
        return *this;
    }

    double vkupnaPlata(){
        double sum = 0;
        for(int i = 0; i < numberOfEmployees;i++){
            sum += employees[i]->plata();
        }
        return  sum;
    }

    double filtriranaPlata(Employee * emp){
        double sum = 0;
        for(int i = 0; i < numberOfEmployees;i++){
            if(employees[i]->getAge() == emp->getAge())
            sum += employees[i]->plata();
        }
        return  sum;
    }

    int SalaryEmployee (Employee **employees, int n) {
        int counter = 0;
        for (int i=0;i<n;i++) {
            class SalaryEmployee * casted = dynamic_cast<class SalaryEmployee *>(employees[i]);
            if (casted!=0) {
                ++counter;
            }
        }
        return counter;
    }

    int HourlyEmployee  (Employee **employees, int n) {
        int counter = 0;
        for (int i=0;i<n;i++) {
            class HourlyEmployee  * casted = dynamic_cast<class HourlyEmployee  *>(employees[i]);
            if (casted!=0) {
                ++counter;
            }
        }
        return counter;
    }

    int Freelancer (Employee **employees, int n) {
        int counter = 0;
        for (int i=0;i<n;i++) {
            class Freelancer  * casted = dynamic_cast<class Freelancer  *>(employees[i]);
            if (casted!=0) {
                ++counter;
            }
        }
        return counter;
    }

    void pecatiRabotnici(){
        cout << "Vo kompanijata " << name << " rabotat:" << endl;
        cout << "Salary employees: " << SalaryEmployee(employees,numberOfEmployees) << endl;
        cout << "Hourly employees: " << HourlyEmployee(employees,numberOfEmployees) << endl;
        cout << "Freelancers: " << Freelancer(employees,numberOfEmployees) << endl;
    }


};

int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1) {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        }

        else if (type == 2) {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        }

        else {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i=0; i < numProjects; ++i) {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}