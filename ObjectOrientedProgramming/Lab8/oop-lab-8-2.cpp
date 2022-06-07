/* Во една игротека има 2 типа играчки: топки и коцки. Коцките и топките се опишани со параметри како што се:

боја (char *)
густина (int).
Дополнително за топките се знае и радиусот (int), додека за коцките целосните димензии (висина, ширина и длабочина – int).

За секоја од класите треба да се дефинираат методи getMasa() и getVolumen(). Масата на играчката се пресметува како производ од волуменот и густината на играчката. За PI користете ја вредноста 3.14.

Во функцијата main да се декларира променлива kupche што претставува динамички алоцирана низа кон Igrachka. Во зависност од првиот влезен параметар се внесуваат објекти од класите Topka или Kocka (1 - се внесува топка, 2 - се внесува коцка).

Од тастатура да се внесат податоци за коцката на Петра Kocka petra. Во главната функција во да се отпечатат:

Да се отпечати DA ако вкупната маса на сите играчки е поголема од масата на играчката на Петра, а NE во спротивно.
Разликата по апсолутна вредност на волуменот на играчката со максимален волумен во купчето и волуменот на коцката на Петра. Форматот е:

Razlikata e: {razlika}
Задачата да се реши со тоа што класите Kocka и Topka ќе наследуваат од класите Forma и Igrachka.

Дополнителни барања:

Во класата Igrachka да се додаде уште една чисто виртуелна функција float getPlostina(). Истата да се имплементира во класите Kocka и Topka
Во главната функција, дополнително да се испечати и: Разликата по апсолутна вредност на плоштината на играчката со минимална плоштина во купчето и плоштината на коцката на Петра во истиот формат како и второто барање погоре. */


#include <iostream>
#include <cstring>

using namespace std;

class Igrachka {
public:
    virtual float getVolumen() = 0;

    virtual float getMasa() = 0;

    virtual float getPlostina() = 0;

};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    Forma(char boja[100] = "", int gustina = 0) {
        strcpy(this->boja, boja);
        this->gustina = gustina;
    }
    // да се имплементираат потребните методи

};

class Kocka : public Igrachka, public Forma {
    int height;
    int width;
    int depth;

public:


    Kocka(char boja[100] = "", int gustina = 0, int height = 0, int width = 0, int depth = 0) : Forma(boja, gustina) {
        this->height = height;
        this->width = width;
        this->depth = depth;
    }

    int getHeight() {
        return this->height;
    }

    float getVolumen() {
        return height * width * depth;
    }

    float getMasa() {
        return getVolumen() * gustina;
    }

    float getPlostina() {
        return 2*(width*height + depth*width + height*depth);
    }

};

class Topka : public Igrachka, public Forma {
    int radius;

public:
    Topka(char boja[100] = "", int gustina = 0, int radius = 0) : Forma(boja, gustina) {
        this->radius = radius;
    }


    float getVolumen() {
        return 4 / 3.0 * 3.14 * radius * radius * radius;
    }

    float getMasa() {
        return getVolumen() * gustina;
    }

    float getPlostina() {
        return 4 * 3.14 * radius * radius;
    }

};


int main() {

    Igrachka **kupche = new Igrachka *;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {

        int type;
        cin >> type;

        if (type == 1) {
            char boja[100];
            int gustina;
            int radius;
            cin >> boja >> gustina >> radius;
            kupche[i] = new Topka(boja, gustina, radius);
        } else if (type == 2) {
            char boja[100];
            int gustina;
            int height;
            int width;
            int depth;
            cin >> boja>> gustina>>  height >> width >> depth;
            kupche[i] = new Kocka(boja, gustina, height, width, depth);

        }

    }

    char petraBoja[100];
    int petraGustina;
    int petraHeight;
    int petraWidth;
    int petraDepth;
    cin >> petraBoja;
    cin >> petraGustina;
    cin >> petraHeight;
    cin >> petraWidth;
    cin >> petraDepth;
    Kocka petra(petraBoja, petraGustina, petraHeight, petraWidth, petraDepth);
    float totalMass = 0;
    float maxVolume = 0;
    float minPlostina = 999999999;
    for (int j = 0; j < n; j++) {
        totalMass += kupche[j]->getMasa();
        if (kupche[j]->getVolumen() > maxVolume) {
            maxVolume = kupche[j]->getVolumen();
        }

        if (kupche[j]->getPlostina() < minPlostina) {
            minPlostina = kupche[j]->getPlostina();

        }
    }


    if (petra.getMasa() < totalMass) {
        cout << "DA" << endl;
    } else {
        cout << "NE" << endl;
    }

    cout << "Razlikata e: " << maxVolume - petra.getVolumen() << endl;
    cout << "Razlikata e: " <<  petra.getPlostina() - minPlostina << endl;


    return 0;
}