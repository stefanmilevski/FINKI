#include <iostream>
#include <cstring>
using namespace std;

class Avtomobil
{
private:
    char boja[20];
    char brend[20];
    char model[20];

public:
    Avtomobil(char boja[20] = "", char brend[20] = "", char model[20] = "")
    {
        strcpy(this->boja,boja);
        strcpy(this->brend,brend);
        strcpy(this->model,model);
    }

    Avtomobil & operator = (const Avtomobil & other)
    {
        if(this != &other)
        {
            strcpy(this->boja,other.boja);
            strcpy(this->brend,other.brend);
            strcpy(this->model,other.model);
        }
    }

    char * getBoja()
    {
        return this->boja;
    }

    char* getBrend()
    {
        return this->brend;
    }
    char* getModel()
    {
        return this->model;
    }

};



class ParkingPlac
{
private:
    char adresa[20];
    char * id;
    int cenaPoCas;
    int zarabotka;

    Avtomobil * avtomobili;
    int brojNaParkirani;

public:
    ParkingPlac()
    {
        strcpy(this->adresa, "");
        this->id = new char[0];
        strcpy(this->id, "");
        this->cenaPoCas = 0;
        this->zarabotka = 0;

        this->avtomobili = new Avtomobil[0];
        this->brojNaParkirani = 0;
    }

    ParkingPlac(char adresa[20],char * id,int cenaPoCas)
    {
        strcpy(this->adresa, adresa);
        this->id = new char[strlen(id)+1];
        strcpy(this->id, id);
        this->cenaPoCas = cenaPoCas;
        this->zarabotka = 0;

        this->avtomobili = new Avtomobil[0];
        this->brojNaParkirani = 0;

    }

    bool daliIstaAdresa(ParkingPlac & p)
    {
        if(strcmp(this->adresa, p.adresa) == 0)
        {
            return true;
        }
        return false;
    }

    void pecati()
    {
        if(this->zarabotka !=0)
        {
            cout << this->id << " " << this->adresa << " - " << this->zarabotka << " denari" << endl;
        }
        else
        {
            cout << this->id << " "<< this->adresa << endl;
        }
    }

    void platiCasovi(int casovi)
    {
        this->zarabotka += casovi * this-> cenaPoCas;
    }

    void parkirajVozilo(Avtomobil novoVozilo)
    {
        Avtomobil * tmp = new Avtomobil[this->brojNaParkirani+1];
        for(int i = 0; i < brojNaParkirani; i++)
        {
            tmp[i] = this->avtomobili[i];
        }
        tmp[brojNaParkirani++] = novoVozilo;
        delete[]avtomobili;
        avtomobili = tmp;
    }


    void pecatiParkiraniVozila()
    {
        cout << "Vo parkingot se parkirani slednite vozila:" << endl;
        for(int i = 0; i < this->brojNaParkirani; i++)
        {
            cout << i+1 << "." << this->avtomobili[i].getBoja() << " "  << this->avtomobili[i].getBrend()  << this->avtomobili[i].getModel() << endl;
        }
    }


    char * getId()
    {
        return this->id;
    }
};




int main(){

	ParkingPlac p[100];
	int n,m;
	char adresa[50],id[50];
	int brojcasovi,cenacas;
	cin>>n;
	if(n > 0){


		for (int i=0;i<n;i++){
	        cin.get();
			cin.getline(adresa,50);
			cin>>id>>cenacas;

			ParkingPlac edna(adresa,id,cenacas);

	        p[i]=edna;
		}

		//plakjanje
		cin>>m;
		for (int i=0;i<m;i++){

			cin>>id>>brojcasovi;

	        int findId=false;
	        for (int j=0;j<m;j++){
	            if (strcmp(p[j].getId(),id)==0){
	                p[j].platiCasovi(brojcasovi);
	                findId=true;
	            }
	        }
			if (!findId)
	        cout<<"Ne e platen parking. Greshen ID."<<endl;
		}

	    cout<<"========="<<endl;
	    ParkingPlac pCentar("Cvetan Dimov","C10",80);
		for (int i=0;i<n;i++)
	        if (p[i].daliIstaAdresa(pCentar))
	            p[i].pecati();
	} else {

		ParkingPlac najdobarPlac("Mars", "1337", 1);
	    int brVozila;
	    cin >> brVozila;
	    for(int i = 0; i < brVozila; ++i){

	    	char boja[20];
	    	char brend[20];
	    	char model[20];

	    	cin >> boja >> brend >> model;
	    	Avtomobil novAvtomobil(boja, brend, model);
	    	najdobarPlac.parkirajVozilo(novAvtomobil);
	    }
	    if(brVozila != 0)
	    najdobarPlac.pecatiParkiraniVozila();

	}
}
