/* Да се развие класа Nediviznina за коjа се чуваат следниве информации:

адреса (динамички алоцирана низа од знаци)
квадратура (цел боj)
цена за квадрат (цел боj)
За оваа класа да се имплементираат соодветните конструктори и следните методи:

cena() коj ќе jа враќа цената на недвижнината (квадратура * цена-за-квадрат)
pecati() коj ќе ги испечати сите информации за истата
danokNaImot() коj го ваќа данокот што се плаќа за недвижнината, а истиот се пресметува како 5% од цената на недвижнината.
Од оваа класа да се изведе класа Vila за коjа дополнително се чува данок на луксуз (цел боj, пр. 10%). За оваа класа да се преоптоварат методите:

pecati()
danokNaImot() со тоа што пресметаниот данок се зголемува процентуално за данокот на луксуз.
И за двете класи треба да се преоптовари operator >>. */

#include <iostream>
#include <cstring>
using namespace std;

class Nedviznina{
protected:
    char * adresa;
    int kvadratura;
    int cenaPoKvadrat;
public:
    Nedviznina(char * adresa = "",int kvadratura = 0, int cenaPoKvadra = 0){
        this->adresa = new char[strlen(adresa)+1];
        strcpy(this->adresa,adresa);
        this->kvadratura = kvadratura;
        this->cenaPoKvadrat = cenaPoKvadra;
    }

    Nedviznina  (Nedviznina & other){
        this->adresa = new char[strlen(other.adresa)+1];
        strcpy(this->adresa,other.adresa);
        this->kvadratura = other.kvadratura;
        this->cenaPoKvadrat = other.cenaPoKvadrat;
    }

    ~Nedviznina(){
        delete [] adresa;
    }
    int cena(){
        return this->kvadratura * cenaPoKvadrat;
    }

    char * getAdresa(){
        return this->adresa;
    }

    void pecati(){
        cout << adresa << ", " << "Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaPoKvadrat << endl;
    }

    double danokNaImot(){
        return cena() * 0.05;
    };

    friend istream & operator >> (istream & in,Nedviznina & n){
        in >> n.adresa >> n.kvadratura >> n.cenaPoKvadrat;

    }

};

class Vila : public Nedviznina{
private:
    int danokNaLuksuz;
public:
    Vila(char * adresa = "",int kvadratura = 0, int cenaPoKvadra = 0,int danokNaLuksuz = 0) : Nedviznina(adresa,kvadratura,cenaPoKvadra){
        this->danokNaLuksuz = danokNaLuksuz;
    }

    double danokNaImot(){
        return Nedviznina::danokNaImot()+ Nedviznina::cena() * (danokNaLuksuz / (100.0));
    };


    friend istream & operator >> (istream & in,Vila & n){
        in >> n.adresa >> n.kvadratura >> n.cenaPoKvadrat >> n.danokNaLuksuz;

    }

    void pecati(){
        cout << adresa << ", " << "Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaPoKvadrat << ", Danok na luksuz: " << danokNaLuksuz << endl;
    }



};


int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}