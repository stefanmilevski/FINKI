/* Да се дефинира класа Ekipa за коjа се чуваат следниве информации:

името на екипата (низа од наjмногу 15 знаци)
броj на порази
броj на победи
За оваа класа да се дефинира метод pecati() коjа ги печати податоците за екипаta. Од оваа класа да се изведe новa класa, FudbalskaEkipa.

За фудбалската екипа дополнително се чуваат информации за:

вкупниот броj на црвени картони
вкупниот броj жолти картони
броjот на нерешени натпревари
За фудбалската екипа да се преоптовари методот pecati(), така што покрај останатите информации, ќе се испечатат и бројот на нерешени резултати и вкупен број на поени
во формат: Име на екипа, броj на победи, броj на порази, броj на нерешени натпревари и вкупен броj на поени (за победа фудбалската екипа добива 3 поени, додека за нерешен резултата, 1 поен); */


#include <iostream>
#include <cstring>

using namespace std;
class Ekipa{
protected:
    char name[15];
    int loses;
    int wins;
public:
    Ekipa(char name[] = "",int wins =0,int loses = 0 ){
        strcpy(this->name,name);
        this->loses= loses;
        this->wins = wins;

    }

    void pecati(){
        cout << "Ime: " << name << " Pobedi: " << wins << " Porazi: " << loses << endl;
    }
};

class FudbalskaEkipa : public Ekipa{
private:
    int yellowCards;
    int redCards;
    int draws;
public:
    FudbalskaEkipa(char name[] = "",int wins =0,int loses = 0,int redCards= 0,int yellowCards = 0,int draws = 0 ) : Ekipa(name,wins,loses){
        this->redCards = redCards;
        this->yellowCards = yellowCards;
        this->draws = draws;
    }

    int points(){
        int total = 0;
        total += wins * 3;
        total += draws;
        return total;

    }

    void pecati(){
        cout << "Ime: " << name << " Pobedi: " << wins << " Porazi: " << loses <<  " Nereseni: " << draws << " Poeni: " << points() << endl; ;
    }

};



int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}