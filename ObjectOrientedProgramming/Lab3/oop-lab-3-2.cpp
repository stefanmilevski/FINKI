/* Да се дефинира класа Potpisuvac во која се чуваат информации за:

име (низа од максимум 20 знаци)
презиме (низа од максимум 20 знаци)
ЕМБГ (низа од максимум 14 знаци)
За класата да се дефинира copy конструктор, default конструктор и конструктор со аргументи.

Да се дефинира класа Dogovor, во која се чуваат информации за:

број на договор (int),
категорија на договор (низа од 50 знаци),
поле од 3 потпишувачи на договорот (објекти од класата Potpisuvac)
Во класата да се додаде метод кој ќе проверува дали постојат два исти потпишувачи (имаат ист ЕМБГ).

For example: */

#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac
{
private:
    char ime[20];
    char prezime[20];
    char embg[14];
public:
    Potpisuvac()
    {
        strcpy(ime,"default");
        strcpy(prezime,"default");
        strcpy(embg,"default");
    };
    Potpisuvac(char * i, char * p, char * e)
    {
        strcpy(ime,i);
        strcpy(prezime,p);
        strcpy(embg,e);
    }
    Potpisuvac(const Potpisuvac& p)
    {
        strcpy(ime,p.ime);
        strcpy(prezime,p.prezime);
        strcpy(embg,p.embg);
    }

    char * getEmbg()
    {
        return this->embg;
    }
};
class Dogovor
{
private:
    int broj;
    char kategorija[50];
    Potpisuvac * p;

public:
    Dogovor();
    Dogovor(int b,char * k,Potpisuvac* pot)
    {
        broj = b;
        strcpy(kategorija,k);
        p = pot;
    }


    bool proverka()
    {
        int flag = 0;
        for(int i = 0; i < 3; i++)
        {
            for(int k=i +1; k< 3; k++)
            {
                if(strcmp(this->p[i].getEmbg(), this->p[k].getEmbg() ) == 0)
                {
                    flag = 1;
                }
            }
        }
        if(flag == 1)
        {
            return true;
        }
        else
        {
            return false;
        }


    }
};


//ne smee da se menuva main funkcijata
int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> embg >> ime >> prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        if(d.proverka() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}
