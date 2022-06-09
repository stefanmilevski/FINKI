/* Сите елементи кои ги превезуваат камионите имаат одредена маса. Имплементирајте апстрактна класа ImaMasa од која што ќе наследуваат сите класи кои имаат маса. Во оваа класа треба да се дефинираат методите:

double vratiMasa() враќа маса изразена во kg
void pecati() печати информации за соодветниот објект
Нека еден камион превезува пијалоци и тоа: пакет сокови и пакет вина. Да се дефинираат класите PaketSok и PaketVino кои ги имплементираат методите од апстрактната класа ImaMasa. При тоа да се земе предвид дека класите PaketSok и PaketVino се изведени од класата PaketPijalok. Притоа да се земат дадените податоци:

Класа PaketPijalok:

членови:
volumenEden double
kolicina int
методи:
double vratiMasa()
void pecati()
int getKolicina()
Класа PaketSok:

членови:
volumenEden double
kolicina int
daliGaziran bool
методи:
double vratiMasa()
void pecati()
Класа PaketVino:

членови:
volumenEden double
kolicina int
procentAlkohol double
методи:
double vratiMasa()
double getProcentAlkohol()
void pecati()
Еден пијалок има маса пресметана како производ на волуменот и густината (0.8kg/dm3) и масата на амбалажата (0.2kg). Овие податоци за густината и за масата на амбалажата да се стават како статички податоци за класата PaketPijalok. Масата на пакетот е производ на масата на еден пијалок и количината на пијалоци која ја има во пакетот. Соковите кои не се газирани имаат дополнителна маса од 0.1kg по пијалок. За вината, масата се добива како производ од масата на пакетот пресметан по правилата за секој пијалок помножен со коефициентот: (0.9+procentAlkohol).

Покрај овие класи, да се имплементира класата Kamion. За еден камион се чуваат информации за:

регистрацијата char*
возачот char*
елементите кои ги превезува камионот (низа од покажувачи од ImaMasa)
Во класата Kamion покрај методите set и get дефинирајте ги и следните методи:

Kamion(char* ) конструктор со кој се генерира празен камион (без товар) и само возач
void registriraj(char*) се додава регистрацијата на камионот
void dodadiElement(ImaMasa) се додава нов елемент во камионот
double vratiVkupnaMasa() се враќа вкупната маса на товарот кој го пренесува камионот
void pecati() се печатат сите елементи во камионот заедно со регистрацијата и името на возачот
Kamion pretovar(char* , char* ) се врши претовар во нов камион, но во новиот покрај тоа што се менуваат регистрацијата и името на возачот (аргументи), се отстранува пакетот со најголема маса.
Со помош на правилата за справување со исклучоци да се модифицира програмата така што ќе се запазат следните правила: - Регистрацијата има 8 карактери, така што првите два и последните два мора да бидат букви. Да се определи каде ќе се фрли соодветниот исклучок. Онаму каде што ќе се фати исклучокот, ќе се отпечати "Pogresno vnesena registracija!". */

#include<iostream>
#include<cstring>

using namespace std;

class InvalidLicensePlateExecption {
public:
    void message() {
        cout << "Pogresno vnesena registracija" << endl;
    }
};

class ImaMasa {
public:
    virtual double vratiMasa() = 0;

    virtual void pecati() = 0;
};

class PaketPijalok {
protected:
    double volumenEden;
    int kolicina;
    static double gustina;
    static double masaNaAmbalaza;
public:
    PaketPijalok(double volumenEden = 0, int kolicina = 0) {
        this->volumenEden = volumenEden;
        this->kolicina = kolicina;
    }

    double vratiMasa() {
    };

    void pecati() {};

    double getVolumenEden() {
        return this->volumenEden;
    }

    int getKolicina() {
        return this->kolicina;
    }
};

double PaketPijalok::gustina = 0.8;
double PaketPijalok::masaNaAmbalaza = 0.2;


class PaketSok : public ImaMasa, public PaketPijalok {
    bool daliGaziran;
public:
    PaketSok(double volumenEden = 0, int kolicina = 0, bool daliGaziran = false) : PaketPijalok(volumenEden, kolicina) {
        this->daliGaziran = daliGaziran;
    }

    double vratiMasa() {
        if (daliGaziran) {
            return (((volumenEden * gustina) + masaNaAmbalaza + 0.1) * (double) kolicina) + 3;
        } else {
            return ((volumenEden * gustina) + masaNaAmbalaza) * (double) kolicina;
        }


    };

    void pecati() {
        cout << "Paket sok" << endl;
        cout << "kolicina " << kolicina << ", so po " << volumenEden * 1.0 * gustina << " l(dm3)" << endl;
    };


};


class PaketVino : public ImaMasa, public PaketPijalok {
    double procentAlkohol;
public:
    PaketVino(double volumenEden = 0, int kolicina = 0, double procentAlkohol = 0) : PaketPijalok(volumenEden,
                                                                                                  kolicina) {
        this->procentAlkohol = procentAlkohol;
    }

    double vratiMasa() {
        return ((volumenEden * gustina) + masaNaAmbalaza) * (0.9 + procentAlkohol) * (double) kolicina;
    };

    void pecati() {
        cout << "Paket vino" << endl;
        cout << "kolicina " << kolicina << ", " << procentAlkohol * 100 << "% alkohol od po "
             << volumenEden * 1.0 * gustina << " l(dm3)"
             << endl;
    };

};


class Kamion {
    char *registracija;
    char *vozac;
    ImaMasa **elementi;
    int brojNaElementi;
public:
    Kamion(char *reg = "", char *vozac = "") {
        if (strlen(reg) != 8) {
            throw InvalidLicensePlateExecption();
        } else if (!isalpha(reg[0]) || !isalpha(reg[1]) || !isalpha(reg[6]) || !isalpha(reg[7])) {
            throw InvalidLicensePlateExecption();
        }


        this->vozac = new char[strlen(vozac) + 1];
        strcpy(this->vozac, vozac);
        this->elementi = new ImaMasa *[0];
        this->registracija = new char[strlen(reg) + 1];
        strcpy(this->registracija, reg);
        this->brojNaElementi = 0;
    }


    Kamion(const Kamion &other) {

        if (strlen(other.registracija) != 8) {
            throw InvalidLicensePlateExecption();
        } else if (!isalpha(other.registracija[0]) || !isalpha(other.registracija[1]) ||
                   !isalpha(other.registracija[6]) || !isalpha(other.registracija[7])) {
            throw InvalidLicensePlateExecption();
        }

        this->vozac = new char[strlen(other.vozac) + 1];
        strcpy(this->vozac, other.vozac);
        this->elementi = new ImaMasa *[other.brojNaElementi];
        this->registracija = new char[strlen(other.registracija) + 1];
        strcpy(this->registracija, other.registracija);
        this->brojNaElementi = other.brojNaElementi;

    }

    void registriraj(char *reg) {
        if (strlen(reg) != 8) {
            throw InvalidLicensePlateExecption();
        } else if (!isalpha(reg[0]) || !isalpha(reg[1]) || !isalpha(reg[6]) || isalpha(reg[7])) {
            throw InvalidLicensePlateExecption();
        }


        delete[] registracija;
        this->registracija = new char[strlen(reg) + 1];
        strcpy(this->registracija, reg);
    }

    void dodadiElement(ImaMasa *e) {
        ImaMasa **tmp = new ImaMasa *[brojNaElementi + 1];
        for (int i = 0; i < brojNaElementi; i++) {
            tmp[i] = elementi[i];
        }
        tmp[brojNaElementi++] = e;
        delete[] elementi;
        elementi = tmp;
    }

    double vratiVkupnaMasa() {
        double total = 0;
        for (int i = 0; i < brojNaElementi; i++) {
            total += elementi[i]->vratiMasa();
        }

        return total;
    }


    Kamion pretovar(char *reg = "", char *vozac = "") {
        Kamion newK = Kamion(reg, vozac);
        int maxWeight = 0;
        int index = 0;
        for (int i = 0; i < brojNaElementi; i++) {
            if (elementi[i]->vratiMasa() > maxWeight) {
                maxWeight = elementi[i]->vratiMasa();
                index = i;

            }
        }

        for (int i = 0; i < brojNaElementi; i++) {
            if (i != index) {
                newK.dodadiElement(elementi[i]);
            }
        }
        return newK;


    }


    void pecati() {
        cout << "Kamion so registracija " << registracija << " i vozac " << vozac << " prenesuva:" << endl;
        for (int i = 0; i < brojNaElementi; i++) {
            elementi[i]->pecati();
        }

    }

};


int main() {
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;

    cin >> reg;
    cin >> ime;
    try {
        Kamion A(reg, ime);
        ImaMasa **d = new ImaMasa *[5];
        cin >> vol >> kol;
        cin >> g;
        d[0] = new PaketSok(vol, kol, g);


        cin >> vol >> kol;
        cin >> proc;
        d[1] = new PaketVino(vol, kol, proc);

        cin >> vol >> kol;
        cin >> proc;
        d[2] = new PaketVino(vol, kol, proc);

        cin >> vol >> kol;
        cin >> g;
        d[3] = new PaketSok(vol, kol, g);

        cin >> vol >> kol;
        cin >> proc;
        d[4] = new PaketVino(vol, kol, proc);


        A.dodadiElement(d[0]);
        A.dodadiElement(d[1]);
        A.dodadiElement(d[2]);
        A.dodadiElement(d[3]);
        A.dodadiElement(d[4]);
        A.pecati();
        cout << "Vkupna masa: " << A.vratiVkupnaMasa() << endl;
        cin >> reg;
        cin >> ime;
        Kamion B = A.pretovar(reg, ime);
        B.pecati();
        cout << "Vkupna masa: " << B.vratiVkupnaMasa() << endl;
    } catch (InvalidLicensePlateExecption &e) {
        e.message();
    }


}
