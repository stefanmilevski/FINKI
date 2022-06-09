/* Во оваа задача е потребно да уредите даден дом со маси. Креирајте класа Masa со следниве атрибути:

должина (целобројна вредност)
ширина (целобројна вредност)
конструктор со и без параметри и метода pecati().

Креирајте класа Soba која содржи:

маса (објект од класата Маса)
должина на собата (целобројна вредност)
ширина на собата (целобројна вредност)
конструктор со и без параметри и метода pecati() во која се повикува и pecati() за објектот Masa.

Креирајте класа Kukja со атрибути:

соба (објект од класата Soba)
адреса (низа од 50 знаци), и соодветни методи.
конструктор со и без параметри, деструктор и метода pecati() во која се повикува и pecati() за објектот Soba. */

#include <iostream>
#include <cstring>

using namespace std;

class Masa{
private:
    int dolzina;
    int sirina;

public:
    Masa(int d = 0,int s = 0){
        dolzina = d;
        sirina = s;
    }

    void pecati(){
        cout << "Masa: " << dolzina << " " << sirina << " ";
    }

};

class Soba{
private:
    Masa masa;
    int dolzina;
    int sirina;

public:
    Soba(){
        this->dolzina =0;
        this->sirina = 0;
    };
    Soba( int d, int s,Masa m){
        this->masa = m;
        this->dolzina =d;
        this->sirina = s;
    }

    Masa getMasa(){
        return masa;
    }

    void pecati(){
        cout << "Soba: " << dolzina << " " << sirina << " ";
    }
};

class Kukja{
private:
    Soba soba;
    char adresa[50];

public:
    Kukja();
    Kukja(Soba s, char * a){
        this->soba =s;
        strcpy(this->adresa,a);
    }

    void pecati(){
        cout << "Adresa: " << adresa << " ";
        this->soba.pecati();
        this->soba.getMasa().pecati();
        cout << endl;
    }
};



//ne smee da se menuva main funkcijata!
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
    	Masa m(masaSirina,masaDolzina);
    	int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
    	Soba s(sobaSirina,sobaDolzina,m);
    	char adresa[30];
        cin>>adresa;
    	Kukja k(s,adresa);
    	k.pecati();
	}

    return 0;
}
