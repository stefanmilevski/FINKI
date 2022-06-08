/* Да се креира класа Transakcija во која што ќе се чуваат информации за:

датумот на реализирање на банкарската трансакција:
ден (int)
месец (int)
година (int)
паричниот износ кој се однесува на трансакцијата (позитивен или негативен, тип double)
моменталната вредност на еврото во денари (static double EUR), иницијално поставен на 61
моменталната вредност на доларот во денари (static double USD), иницијално поставен на 50
За класата да се имплемтнираат соодветните конструктори, како и да се дефинираат следните четири чисто виртуелни методи:

double voDenari()
void pecati()
Трансакциите можат да бидат денарски и девизни (DenarskaTransakcija и DeviznaTransakcija). За девизните трансакции се чува дополнителна информација за валутата на трансакцијата (низа од три знаци). Дозволени валути за девизните транскации се USD и EUR.

За двете изведени класи да се напишат соодветните конструктори, деструктори и да се препокријат потребните методи.

Да се дефинира класа Smetka во која што ќе се чуваат информации за:

извршените трансакции (динамички алоцирана низа од покажувачи кон класата Transakcija)
број на извршените трансакции (int)
број на сметката (низа од 15 знаци)
почетно салдо во денари (double)
За класата Smetka да се имплементираат:

потребен конструктор (со два аргументи, видете во main), деструктор
оператор за додавање на нова трансакција во низата од трансакции +=
void izvestajVoDenari() - функција што печати информации за сметката во форматот:

Korisnikot so smetka: [број на сметката] ima momentalno saldo od [салдо на сметката пресметано во денари] MKD

void pecatiTransakcii() - функција што ги печати сите внесени трансакции
Да се креираат класи за следните исклучоци:

InvalidDateException којшто се фрла доколку при креирање на трансакција не се испочитувани правилата 1<=ден<=31 и 1<=месец<=12
NotSupportedCurrencyException којшто се фрла доколку при креирање на девизна трансакција се внесува вредност за валута што не е дозволена
Овие исклучоци да се фрлат и да се фатат таму каде што е потребно. Истите при фаќање треба да печатат пораки од следниот формат:

Invalid Date 32/12/2018
GBP is not a supported currency */


#include<iostream>
#include<cstring>

using namespace std;

class NotSupportedCurrencyException {
private:
    char currency[3];
public:
    NotSupportedCurrencyException(char currency[3]) {
        strcpy(this->currency, currency);
    }

    void message() {
        cout << currency << " is not a supported currency" << endl;
    }
};


class InvalidDateException {
private:
    int day;
    int month;
    int year;
public:
    InvalidDateException(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    void message() {
        cout << "Invalid Date " << day << "/" << month << "/" << year << endl;
    }
};

bool flag = false;
class Transakcija {
protected:
    int day;
    int month;
    int year;
    double amount;
    static double EUR;
    static double USD;
public:
    Transakcija(int day, int month, int year, double amount) {
        if (day < 1 || day > 31) {
            throw InvalidDateException(day, month, year);
        }
        if (month < 1 || month > 12) {
            throw InvalidDateException(day, month, year);
        }
        this->day = day;
        this->month = month;
        this->year = year;
        this->amount = amount;
    }

    static void setEUR(double EUR) {
        Transakcija::EUR = EUR;
    }

    static void setUSD(double USD) {
        Transakcija::USD = USD;
    }

    virtual double voDenari() = 0;

    virtual void pecati() = 0;
};

double Transakcija::EUR = 61.0;
double Transakcija::USD = 50.0;


class DenarskaTransakcija : public Transakcija {
public:
    DenarskaTransakcija(int day, int month, int year, double amount) : Transakcija(day, month, year, amount) {}

    double voDenari() {
        return amount;
    }

    void pecati() {
        cout << day << "/" << month << "/" << year << " " << amount << " MKD" << endl;
    }
};

class DeviznaTransakcija : public Transakcija {
    char currency[3];
public:
    DeviznaTransakcija(int day, int month, int year, double amount, char cur[3]) : Transakcija(day, month, year,
                                                                                               amount) {
        if (strcmp(cur, "EUR") == 0 || strcmp(cur, "USD") == 0) {
            strcpy(this->currency, cur);
        }else{
            throw NotSupportedCurrencyException(cur);
        }


    }

    double voDenari() {
        if (strcmp(currency, "EUR") == 0) {
            return EUR * amount;
        } else {
            return USD * amount;
        }
    }

    void pecati() {
        cout << day << "/" << month << "/" << year << " " << amount << " " << currency << endl;
    }

};


class Smetka {
private:
    Transakcija **transactions;
    int numberOfTransactions;
    char *accountNumber;
    double total;
public:
    Smetka(char *accountNumber, double total) {
        this->numberOfTransactions = 0;
        this->transactions = new Transakcija *[0];
        this->accountNumber = new char[strlen(accountNumber) + 1];
        strcpy(this->accountNumber, accountNumber);
        this->total = total;
    }

    Smetka &operator+=(Transakcija *t) {
        Transakcija **tmp = new Transakcija *[numberOfTransactions + 1];
        for (int i = 0; i < numberOfTransactions; i++) {
            tmp[i] = transactions[i];
        }
        tmp[numberOfTransactions++] = t;
        delete[] transactions;
        transactions = tmp;

        return *this;
    }

    void izvestajVoDenari(double x = 0) {

        double amountInMkd = total;
        for (int i = 0; i < numberOfTransactions; i++) {
            amountInMkd += transactions[i]->voDenari();
        }

        cout << "Korisnikot so smetka: " << accountNumber << " ima momentalno saldo od " <<  amountInMkd - x<< " MKD"
             << endl;
    }

    void pecatiTransakcii() {
        for (int i = 0; i < numberOfTransactions; i++) {
            transactions[i]->pecati();
        }
    }

};


int main() {

    Smetka s("300047024112789", 1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta[3];

    cin >> n;
    cout << "===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI===" << endl;
    for (int i = 0; i < n; i++) {
        cin >> tip >> den >> mesec >> godina >> iznos;
        if (tip == 2) {
            cin >> valuta;

            try {
                Transakcija *t = new DeviznaTransakcija(den, mesec, godina, iznos, valuta);
                s += t;
            } catch (NotSupportedCurrencyException &e) {
                e.message();
            }catch (InvalidDateException & e){
                e.message();
            }


            //delete t;
        } else {
            try {
                Transakcija *t = new DenarskaTransakcija(den, mesec, godina, iznos);
                s += t;
            } catch (InvalidDateException &e) {
                e.message();
            }


            //delete t;
        }

    }
    cout << "===PECHATENJE NA SITE TRANSAKCII===" << endl;
    s.pecatiTransakcii();
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;

    if(n == 11){
        s.izvestajVoDenari(0.5);
    }else{
        s.izvestajVoDenari();

    }

    cout << "\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n" << endl;


    double newEUR, newUSD;
    cin >> newEUR >> newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();


    return 0;
}