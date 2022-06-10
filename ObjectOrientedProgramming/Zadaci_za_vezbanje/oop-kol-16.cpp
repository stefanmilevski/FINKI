/* Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени) */


#include <iostream>
#include <cstring>

using namespace std;

class Transport {
protected:
    char *destination;
    int basePrice;
    int distance;

    void copy(Transport &other) {
        this->destination = new char[strlen(other.destination) + 1];
        strcpy(this->destination, other.destination);
        this->basePrice = other.basePrice;
        this->distance = other.distance;
    }

public:
    Transport(char *destination, int basePrice, int distance) {
        this->destination = new char[strlen(destination) + 1];
        strcpy(this->destination, destination);
        this->basePrice = basePrice;
        this->distance = distance;
    }

    Transport(Transport &other) {
        copy(other);
    }

    bool operator<(Transport &other) {
        return this->distance < other.distance;
    }

    char *getDestination() const {
        return destination;
    }

    void setDestination(char *destination) {
        Transport::destination = destination;
    }

    int getBasePrice() const {
        return basePrice;
    }

    void setBasePrice(int basePrice) {
        Transport::basePrice = basePrice;
    }

    int getDistance() const {
        return distance;
    }

    void setDistance(int distance) {
        Transport::distance = distance;
    }

    virtual double cenaTransport() = 0;

    void print() {
        cout << destination << " " << distance << " " << cenaTransport() << endl;
    }

};

class AvtomobilTransport : public Transport {
    bool paidDriver;
public:
    AvtomobilTransport(char *destination, int basePrice, int distance, bool paidDriver) : Transport(destination,
                                                                                                    basePrice,
                                                                                                    distance) {
        this->paidDriver = paidDriver;
    }

    double cenaTransport() {
        if (paidDriver) {
            return this->basePrice * 1.20;
        }
        return this->basePrice;
    }

    bool isPaidDriver() const {
        return paidDriver;
    }

    void setPaidDriver(bool paidDriver) {
        AvtomobilTransport::paidDriver = paidDriver;
    }


};

class KombeTransport : public Transport {
    int numberOfPassengers;
public:
    KombeTransport(char *destination, int basePrice, int distance, int numberOfPassengers) : Transport(destination,
                                                                                                       basePrice,
                                                                                                       distance) {
        this->numberOfPassengers = numberOfPassengers;
    }

    double cenaTransport() {
        return basePrice - (numberOfPassengers * 200);
    }

    int getNumberOfPassengers() const {
        return numberOfPassengers;
    }

    void setNumberOfPassengers(int numberOfPassengers) {
        KombeTransport::numberOfPassengers = numberOfPassengers;
    }


};


void pecatiPoloshiPonudi(Transport **ponudi, int brojNaPonudi, Transport &ponuda) {
    for (int i = 0; i < brojNaPonudi; i++) {
        for (int j = i + 1; j < brojNaPonudi; j++) {
            if (ponudi[i]->cenaTransport() > ponudi[j]->cenaTransport()) {
                Transport *temp = ponudi[i];
                ponudi[i] = ponudi[j];
                ponudi[j] = temp;
            }
        }

    }

    for (int i = 0; i < brojNaPonudi; i++) {
        if (ponudi[i]->cenaTransport() > ponuda.cenaTransport()) {
            ponudi[i]->print();
        }
    }
}

int main() {

    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {

        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }


    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++) delete ponudi[i];
    delete[] ponudi;
    return 0;
}
