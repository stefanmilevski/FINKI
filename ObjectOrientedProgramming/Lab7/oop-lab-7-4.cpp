/* Да се дефинира класа Vozilo која ќе содржи информација за неговата маса (децимален број), ширина и висина (цели броеви).

Од оваа класа да се изведе класата Автомобил во која како дополнителна информација се чува информацијата за бројот на врати (цел број).

Од класата возило да се изведе и класата Автобус во која се чуваат информации и за бројот на патници кои може да ги пренесува.

Од класата возило да се изведе класата Камион во која се чуваат информации и за максималната маса која може да се товари на него (децимална вредност).

За сите класи да се креираат погодни контруктори, како и set и get функции.

Да се дефинира класа ParkingPlac за која се чува динамичко алоцирано поле од покажувачи кон Vozilo, како и бројот на елементи во полето. Во оваа класа да се дефинираат:

конструктор
деструктор
операторот += за додавање на ново возило (аргументот е покажувач кон Vozilo)
функција float presmetajVkupnaMasa() со која се пресметува вкупната маса на сите возила во паркинг плацот
функција int brojVozilaPoshirokiOd(int l) со која се пресметува бројот на возила кои се пошироки од дадената вредност
функција void pecati() со која се печати: Brojot na avtomobili e X, brojot na avtobusi e Y i brojot na kamioni e Z.
функција int pogolemaNosivostOd(Vozilo& v) во која се враќа бројот на сите камиони кои имаат носивост поголема од масата на возилото предадено како аргумент.
Да се дефинира виртуелна функција int vratiDnevnaCena() во класата Vozilo и истата да се преоптовари во сите изведени класи. За секој автомобил со помалку од 5 врати дневната цена е 100, а инаку е 130 денари. За секој камион цената се пресметува со формулата: (masa+nosivost)*0.02. За секој автобус цената е 5 денари по лице кое може да се пренесува.

Во класата ParkingPlac да се додаде следната функција: - функција int vratiDnevnaZarabotka() со која се враќа дневната заработка од сите возила на паркингот. */

#include<iostream>
using namespace std;

class Vozilo{
protected:
    double mass;
    int height;
    int width;
public:
    Vozilo(double mass = 0,int width =0,int height =0 ){
        this->mass = mass;
        this->height = height;
        this->width = width;
    }

    double getMass(){
        return this->mass;
    }

    int getWidth(){
        return this->width;
    }

    virtual int vratiDnevnaCena() = 0;

};

class Avtomobil : public Vozilo{
    int numberOfDoors;
public:
    Avtomobil(double mass = 0,int width =0,int height =0  ,int numberOfDoors = 0) : Vozilo(mass,width,height){
        this->numberOfDoors = numberOfDoors;
    }

    int vratiDnevnaCena(){
        if(numberOfDoors < 5){
            return 100;
        }
        return 130;
    }
};

class Avtobus : public Vozilo{
    int numberOfPassengers;
public:
    Avtobus(double mass = 0,int width =0,int height =0 ,int numberOfPassengers = 0) : Vozilo(mass,width,height){
        this->numberOfPassengers = numberOfPassengers;
    }
    int vratiDnevnaCena(){
        return 5 * numberOfPassengers;
    }
};

class Kamion : public Vozilo{
    double maxWeightToCarry;
public:
    Kamion(double mass = 0,int width =0,int height =0  ,double maxWeightToCarry = 0) : Vozilo(mass,width,height){
        this->maxWeightToCarry = maxWeightToCarry;
    }

    double getMaxWeightToCarry(){
        return maxWeightToCarry;
    }

    int vratiDnevnaCena(){
        return (getMass()+maxWeightToCarry)*0.02;
    }
};

class ParkingPlac{
    int numberOfVehicles;
    Vozilo ** vehicles;
public:
    ParkingPlac(int number = 0){
        this->numberOfVehicles  = number;
        this->vehicles = new Vozilo*[number];
    }

    ParkingPlac & operator += (Vozilo * v){
        Vozilo ** tmp = new Vozilo*[numberOfVehicles+1];
        for(int i = 0;i< numberOfVehicles;i++){
            tmp[i] = vehicles[i];
        }
        tmp[numberOfVehicles++] = v;
        delete [] vehicles;
        vehicles = tmp;
        return * this;
    }

    float presmetajVkupnaMasa(){
        float totalMasa = 0;
        for(int i = 0;i< numberOfVehicles;i++){
            totalMasa += vehicles[i]->getMass();
        }
        return totalMasa;
    }


    int brojVozilaPoshirokiOd(int input){
        int counter = 0;
        for(int i = 0;i< numberOfVehicles;i++){

            if (vehicles[i]->getWidth() > input)++counter;
        }
        return counter;
    }

    int countAvtomobili(){
        int counter = 0;
        for(int i = 0;i< numberOfVehicles;i++){
            Avtomobil * ptr = dynamic_cast<Avtomobil*>(vehicles[i]);
            if(ptr != 0){
                counter++;
            }
        }
        return counter;

    }

    int countAvtobusi(){
        int counter = 0;
        for(int i = 0;i< numberOfVehicles;i++){
            Avtobus * ptr = dynamic_cast<Avtobus*>(vehicles[i]);
            if(ptr != 0){
                counter++;
            }
        }
        return counter;

    }

    void pecati(){
        cout << "Brojot na avtomobili e " << countAvtomobili() << ", brojot na avtobusi e " << countAvtobusi() << " i brojot na kamioni e " << numberOfVehicles - countAvtobusi() - countAvtomobili() << "." << endl;
    }

    int vratiDnevnaZarabotka(){
        int total = 0;
        for(int i = 0;i < numberOfVehicles;i++){
            total += vehicles[i]->vratiDnevnaCena();
        }
        return total;

    }

    int pogolemaNosivostOd(Vozilo& v){

        int counter = 0;
        for(int i = 0;i< numberOfVehicles;i++){

            Kamion * ptr = dynamic_cast<Kamion*>(vehicles[i]);
            if(ptr!= 0 && ptr->getMaxWeightToCarry() > v.getMass()){
                counter++;
            }

        }
        return counter;

    }



};



int main(){
ParkingPlac p;

int n;
cin>>n;
int shirina,visina, broj;
float masa,nosivost;
for (int i=0;i<n;i++){
    int type;
    cin>>type;
    if(type==1){
        cin>>masa>>shirina>>visina>>broj;
        Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
        p+=a;
    }
    if(type==2){
        cin>>masa>>shirina>>visina>>broj;
        p+=new Avtobus(masa,shirina,visina,broj);
    }
    if(type==3){
        cin>>masa>>shirina>>visina>>nosivost;
        p+=new Kamion(masa,shirina,visina,nosivost);
    }
}

p.pecati();

cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
Avtomobil a(1200,4,3,5);
cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
