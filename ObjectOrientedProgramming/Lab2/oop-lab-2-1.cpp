/* Да се дефинира класа Agol, во која се чуваат информации за:

степени, минути и секунди (int)
Во класата да се реализираат:

конструктор по потреба
методи за поставување на вредности на атрибутите на класата (set методи)
метод за пресметување на вредноста на аголот во секунди
Да се дефинира и метод за проверување на тоа дали внесениот агол е валиден, односно дали се внесени соодветни вредности за атрибутите (во границите кои ги дозволуваат).

For example: */

#include <iostream>
using namespace std;

class Agol
{
public:
    Agol(int degs,int mins,int secs)
    {
        degs = degs;
        mins = mins;
        secs = secs;
    }

    int get_stepeni()
    {
        return degs;
    }

    void set_stepeni(int d)
    {
        degs = d;
    }


    int get_minuti()
    {
        return mins;
    }

    void set_minuti(int m)
    {
        mins = m;
    }

    int getSekundi()
    {
        return secs;
    }

    void set_sekundi(int s)
    {
        secs = s;
    }

    int to_sekundi()
    {
        int res;
        res = (degs * 3600) + (mins * 60) + secs;
        return res;
    }


private:
    int degs;
    int mins;
    int secs;
};


bool changeOfSeconds(Agol a, int sec)
{
    return a.getSekundi()!=sec;
}


bool proveri(int degs,int mins,int secs)
{
    if(degs > 360)
    {
        cout << "Nevalidni vrednosti za agol";
        return false;
    }


    if(mins > 59 || mins < 0)
    {
        cout << "Nevalidni vrednosti za agol";
        return false;
    }

    if(secs > 59 || secs < 0)
    {
        cout << "Nevalidni vrednosti za agol";
        return false;
    }

    return true;
}


int main()
{

    //da se instancira objekt od klasata Agol
    int deg, min, sec;
    cin >> deg >> min >> sec;
    Agol a1(deg,min,sec);
    if (proveri(deg, min, sec))
    {

        a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
            cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    }

    return 0;
}
