/* Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

OperativenSistem
Во класата OperativenSistem треба да се чуваат следниве податоци:

име на оперативниот систем (динамички алоцирана низа од знаци)
верзија (float)
тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
големина (во GB) (float)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктори со и без параметри
copy constructor
destructor
преоптоварување на операторот =
метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
Repozitorium
Во класата Repozitorium треба да се чуваат следниве податоци:

име на репозиториумот (низа од 20 знака)
динамички алоцирана низа од OperativenSistem
број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктор Repozitorium(const char *ime)
деструктор
метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот. */


#include <iostream>
#include <cstring>

using namespace std;

enum Tip {LINUX, UNIX, WINDOWS};

class OperativenSistem
{
private:
    char * ime;
    float verzija;
    Tip t;
    float golemina;

public:

    OperativenSistem()
    {
        this-> ime = new char[0];
        this->verzija = 1.0;
        this->golemina = 0;
    }

    OperativenSistem(char * ime,float verzija,Tip t,float golemina)
    {
        this-> ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->verzija = verzija;
        this->t = t;
        this->golemina = golemina;
    }

    OperativenSistem(const OperativenSistem & other)
    {
        this-> ime = new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->verzija = other.verzija;
        this->t = other.t;
        this->golemina = other.golemina;
    }

    OperativenSistem & operator = (const OperativenSistem & other)
    {
        if(this != &other)
        {
            delete [] ime;
            this-> ime = new char[strlen(other.ime)+1];
            strcpy(this->ime,other.ime);
            this->verzija = other.verzija;
            this->t = other.t;
            this->golemina = other.golemina;
        }
    }

    ~OperativenSistem()
    {
        delete [] ime;
    }

    bool ednakviSe(const OperativenSistem &os)
    {
        if(strcmp(this->ime,os.ime) == 0 && this->verzija == os.verzija && this->t == os.t && this->golemina == os.golemina)
        {
            return true;
        }
        return false;

    }

    int sporediVerzija(const OperativenSistem &os)
    {
        if(this->verzija == os.verzija)
        {
            return 0;
        }
        else if(this->verzija > os.verzija)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    bool istaFamilija(const OperativenSistem &sporedba)
    {
        if(strcmp(this->ime,sporedba.ime)==0 && this->t == sporedba.t)
        {
            return true;
        }
        return false;
    }

    void pecati()
    {
        cout << "Ime: " << this->ime << " Verzija: " << this->verzija << " Tip: " << this->t << " Golemina:" << this->golemina << "GB" << endl;
    }
};

class Repozitorium
{
private:
    char ime[20];
    OperativenSistem * nizaOs;
    int broj;

public:
    Repozitorium(const char * ime)
    {
        strcpy(this->ime,ime);
        this->nizaOs = new OperativenSistem[0];
        this->broj = 0;
    }

    void pecatiOperativniSistemi()
    {
        cout << "Repozitorium: " << this->ime << endl;
        for(int i = 0; i < this->broj; i ++)
        {
            this->nizaOs[i].pecati();
        }
    }



    void izbrishi(const OperativenSistem &operativenSistem)
    {
        int removeIndex = this->broj;
        for(int i = 0; i < this->broj; i++)
        {
            if(this->nizaOs[i].ednakviSe(operativenSistem))
            {
                removeIndex = i;
                break;
            }
        }

        if(removeIndex == this->broj)
        {
            return;
        }
        this->broj--;
        for(int i = removeIndex; i < this->broj; i++)
        {
            this->nizaOs[i]= this->nizaOs[i+1];
        }

    }



    void dodadi(const OperativenSistem &nov)
    {
        for(int i = 0; i < this->broj; i++){
            if(nizaOs[i].istaFamilija(nov) && nizaOs[i].sporediVerzija(nov)  == -1){
                nizaOs[i] = nov;
                return;
            }
        }

        OperativenSistem *tmp = new OperativenSistem[this->broj+1];
        for(int i = 0; i< this->broj; i++){
            tmp[i] = nizaOs[i];
        }
        tmp[this->broj++] = nov;
        delete [] nizaOs;
        nizaOs = tmp;
    }
};


int main()
{

    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++)
    {
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}





















