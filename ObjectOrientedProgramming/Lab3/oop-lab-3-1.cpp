/* Во оваа задача треба да се внесат и испечатат податоци за автомобили.

За еден автомобил (објект од класата Car) се чуваат следниве податоци:

сопственик (објект од класата Person)
датум на купување (објект од класата Date)
цена (float price), предодредена вредност 0
За класата Car потребно е да се напише метод за печатење print() и метод за добивање на цената getPrice().

Класата Date содржи три цели броеви (int year, month, day) кои претставуваат датум. За неа треба да се напише метод за печатење print(), предодреден (default) конструктор, конструктор со параметри и конструктор за копирање.

Класата Person содржи име и презиме (низи од максимум 20 знаци, со предодредени вредности not specified), предодреден конструктор, конструктор со параметри и метод за печатење print().

Методот за печатење кај класата Person изгледа вака: [name] [lastName].

Методот за печатење кај класата Date изгледа вака: [year].[month].[day].

Методот за печатење кај класата Car изгледа вака:

owner.print()

date.print()

Price: [price]

Покрај тоа, потребно е да се напише метод cheaperThan(Car* cars, int numCars, float price) кој ќе ги испечати сите објекти Car од низата cars со големина numCars чија цена е помала од price. */


#include<iostream>
#include<cstring>
using namespace std;
class Date
{
private:
    int year;
    int month;
    int day;
public:
    Date()
    {
        this->year = 0;
        this->month = 0;
        this->day =0;
    };
    Date(int y, int m, int d)
    {
        this->year = y;
        this->month = m;
        this->day =d;
    }
    Date(const Date& a)
    {
        this->year = a.year;
        this->month = a.month;
        this->day =a.day;
    };

    void print()
    {
        cout << year << "." << month << "." << day << endl;
    }

};

class Person
{
private:
    char name[20];
    char lastName[20];
public:
    Person()
    {
        strcpy(this->name,"not specified");
        strcpy(this->lastName,"not specified");
    };
    Person(char * n, char * l)
    {
        strcpy(this->name,n);
        strcpy(this->lastName,l);
    }

    void print()
    {
        cout << name << " " << lastName << endl;
    }



};

class Car
{
private:
    Person owner;
    Date dateOfPurchase;
    float cena = 0;
public:
    Car()
    {
        this->owner = Person();
        this->dateOfPurchase = Date();
        this->cena = 0;
    };
    Car(Person o,Date d,float c)
    {
        this->owner = o;
        this->dateOfPurchase = d;
        this->cena = c;
    }
    float getPrice()
    {
        return cena;
    }

    void print()
    {
        this->owner.print();
        this->dateOfPurchase.print();
        cout << "Price: " << cena;
    }


};

void cheaperThan(Car* cars, int numCars, float price)
{
    for(int i = 0; i < numCars; i++)
    {
        if(cars[i].getPrice() < price)
        {
            cars[i].print();
        }
    }

}




int main()
{
    char name[20];
    char lastName[20];
    int year;
    int month;
    int day;
    float price;

    int testCase;
    cin >> testCase;

    if (testCase == 1)
    {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(year, month, day);

        cin >> price;
        Car car(lik, date,  price);

        car.print();
    }
    else if (testCase == 2)
    {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(Date(year, month, day));

        cin >> price;
        Car car(lik, date,  price);
        car.print();
    }
    else
    {
        int numCars;
        cin >> numCars;

        Car cars[10];
        for (int i = 0; i < numCars; i++)
        {
            cin >> name;
            cin >> lastName;
            Person lik(name, lastName);

            cin >> year;
            cin >> month;
            cin >> day;
            Date date(year, month, day);

            cin >> price;
            cars[i] = Car(lik, date,  price);
        }
        float priceLimit;
        cin >> priceLimit;
        cheaperThan(cars, numCars, priceLimit);
    }


    return 0;
}
