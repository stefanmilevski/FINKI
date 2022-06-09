/* Да се дефинира класа Film, во која ќе се чуваат информации за:

име низа од 100 знаци
режисер низа од 50 знаци
жанр низа од 50 знаци
година цел број
Сите променливи треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:

default конструктор и конструктор со аргументи
метод за печатење на информациите за филмот
Дополнително да се реализира надворешна функција:

void pecati_po_godina(Film *f, int n, int godina) која ќе прима аргумент низа од филмови, вкупниот број на филмови и година, а треба да ги отпечати само филмовите кои се направени во дадената година. */

#include <iostream>
#include <cstring>
using namespace std;

class Film
{
public:
    Film()
    {

    }
    Film(char * i, char * r,char * z,int g)
    {

        strcpy(ime,i);
        strcpy(reziser,r);
        strcpy(zanr,z);
        godina = g;
    }

    void printFilmInfo()
    {
        cout << "Ime: " << ime << endl;
        cout << "Reziser: " << reziser << endl;
        cout << "Zanr: " << zanr << endl;
        cout << "Godina: " << godina << endl;
    }

    int getGodina()
    {
        return godina;
    }




private:
    char ime[100];
    char reziser[50];
    char zanr[50];
    int godina;


};

void pecati_po_godina(Film *f, int n, int godina)
{
    for(int i = 0; i < n; i++)
    {
        if( f[i].getGodina() == godina)
        {
            f[i].printFilmInfo();
        }

    }
}


int main()
{
    int n;
    cin >> n;



    //da se inicijalizira niza od objekti od klasata Film
    Film films[n];
    for(int i = 0; i < n; ++i)
    {
        char ime[100];
        char reziser[50];
        char zanr[50];
        int godina;
        cin >> ime;
        cin >> reziser;
        cin >> zanr;
        cin >> godina;
        films[i] = Film(ime,reziser,zanr,godina);

    }
    int godina;
    cin >> godina;
    pecati_po_godina(films, n,godina);
    return 0;
}
