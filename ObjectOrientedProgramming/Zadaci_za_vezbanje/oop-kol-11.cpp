/* Потребно е да се моделира продажба на карти за прикажување на претстави во некој културен центар. За таа цел, да се направи класа DELO. За класата се чуваат следните атрибути:

Име на делото (низа од 50 знаци)
Година кога е напишано (цел број)
Земја на потекло (низа од 50 знаци)
За класата да се направат потребниот конструктор, get и set методи. За класата DELO да се преоптовари операторот == кој ќе споредува дали две дела се исти (две дела се исти ако имаат исто име) (5 поени).

Да се дефинира класа PRЕTSTAVA. За класата се чуваат информации за:

Делото кое се прикажува (објект од класата DELO)
Број на продадени карти (цел број)
Дата на прикажување (низа од 15 знаци)
За класата да се дефинира потребниот конструктор, set и get методите Дополнително, за класата PRETSTAVA да се напише метода cena која треба да ја врати цената на една карта. (5 поени) Цената зависи од староста на делото и од земјата на потекло и се пресметува по следната формула: Цена = N + М, каде М = 50ден. ако делото е напишано во 20 или 21 век, М = 75ден. ако делото е напишано во 19 век и М = 100ден. ако делото е напишано пред 19 век. N = 100ден ако делото е од Италија, N = 150ден ако делото е од Русија. Делата од останатите земји имаат N = 80ден.

Претставите можат да бидат опера и балет. За балетите се чува дополнителен атрибут за цената на балетот која се додава на оригиналната цена на картата и таа вредност е иста за сите балетски претстави. На почеток изнесува 150 денари, со можност да се променува ако така одлучи менаџментот на културниот центар. (10 поени)

Да се дефинира надворешна функција prihod која како аргумент прима низа од покажувачи кон претстави кои се прикажале во еден месец и големина на низата, а како резултат треба да го пресмета и врати вкупниот приход на културниот центар. (10 поени)

Да се дефинира надворешна функција brojPretstaviNaDelo која како аргумент прима низа од покажувачи кон претстави кои се прикажале во еден месец, големина на низата и едно дело. Оваа функција пресметува на колку од дадените претстави е прикажано даденото дело. (5 поени)

(Напомена: Во низата од претстави која се проследува како аргумент во функциите prihod и brojPretstaviNaDelo може да имаме повеќе претстави за едно исто дело)

Целосна функционалност на задачата  */

#include<iostream>
#include<string.h>
#include<cstring>

using namespace std;

int parseYear(char *yearString) {
    int length = strlen(yearString);
    int yearInt = 0;
    int multiplier = 1;

    for (int i = length - 1; i > length - 5; i--) {
        yearInt += (yearString[i] - '0') * multiplier;
        multiplier *= 10;
    }
    return yearInt;

}

class Delo {
    char name[50];
    int year;
    char country[50];
public:
    Delo() {
        strcpy(this->name, "name");
        this->year = 2000;
        strcpy(this->country, "country");
    }

    Delo(char *name, int year, char *country) {
        strcpy(this->name, name);
        this->year = year;
        strcpy(this->country, country);
    }

    const char *getIme() const {
        return name;
    }

    int getYear() const {
        return year;
    }

    void setYear(int year) {
        Delo::year = year;
    }

    const char *getCountry() const {
        return country;
    }

    bool operator==(Delo &d) {
        return (strcmp(name, d.getIme()) == 0);
    }
};

class Pretstava {
protected:
    Delo delo;
    int numberOfTickets;
    char date[15];
public:
    Pretstava(Delo &d, int numberOfTickets, char *date) {
        this->delo = d;
        this->numberOfTickets = numberOfTickets;
        strcpy(this->date, date);
    }


    Delo getDelo() const {
        return delo;
    }

    void setDelo(const Delo &delo) {
        Pretstava::delo = delo;
    }

    int getNumberOfTickets() const {
        return numberOfTickets;
    }

    void setNumberOfTickets(int numberOfTickets) {
        Pretstava::numberOfTickets = numberOfTickets;
    }

    const char *getDate() const {
        return date;
    }

    virtual int cena() {
        int cena1;

        if (strcmp(delo.getCountry(), "Italija") == 0) {
            cena1 = 100;
        } else if (strcmp(delo.getCountry(), "Rusija") == 0) {
            cena1 = 150;
        } else {
            cena1 = 80;
        }

        if (delo.getYear() <= 1800) {
            cena1 += 100;
        } else if ((delo.getYear()) > 1800 && delo.getYear() <= 1900) {
            cena1 += 75;
        } else if (delo.getYear() <= 2100 && delo.getYear() >= 1900) {
            cena1 += 50;
        }

        return cena1;

    }
};

class Balet : public Pretstava {
    static int extraPrice;
public:
    Balet(Delo &d, int numberOfTickets, char *date) : Pretstava(d, numberOfTickets, date) {
    }

    static void setCenaBalet(int n) {
        Balet::extraPrice = n;
    }

    int cena() {
        return Pretstava::cena() + (extraPrice);
    }
};

int Balet::extraPrice = 150;

class Opera : public Pretstava {
public:
    Opera(Delo &d, int numberOfTickets, char *date) : Pretstava(d, numberOfTickets, date) {}
};


//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0) return new Balet(d, brojProdadeni, data);
    else return new Opera(d, brojProdadeni, data);
}

int prihod(Pretstava **pretstavi, int number) {
    int total = 0;
    for (int i = 0; i < number; i++) {
        total += pretstavi[i]->cena() * pretstavi[i]->getNumberOfTickets();
    }
    return total;
}

int brojPretstaviNaDelo(Pretstava **pretstavi, int number, Delo d) {
    int count = 0;
    for (int i = 0; i < number; i++) {
        if (pretstavi[i]->getDelo() == d) {
            count++;
        }
    }
    return count;
}


int main() {

    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getIme() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getIme() << endl;
        }
            break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
            break;

        case 3:
            //Testiranje na operator ==
        {
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();

            if (f1 == f2) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;
            if (f1 == f3) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;

        }
            break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();

            }
            cout << prihod(pole, n);
        }
            break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
            break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }

            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
        }
            break;

    };


    return 0;
}
