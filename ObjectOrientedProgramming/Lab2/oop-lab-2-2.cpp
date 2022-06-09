/* Да се дефинира класа Krug, во која се чуваат информации за:

радиус float
бројот π const float.
Во класата да се реализираат:

default конструктор и конструктор со аргументи
метод за пресметување плоштина
метод за пресметување периметар
метод кој кажува дали плоштината и периметарот на даден круг се еднакви */

#include <iostream>
#include <cmath>

using namespace std;

class Krug
{
public:
    Krug() {};
    Krug(float rad)
    {
        radius = rad * 1.0;

    };
    float getRad()
    {
        return radius;
    }


    float getP()
    {
        return p;
    }

    float plostina()
    {

        return p * (radius*radius);
    }

    float perimetar()
    {
        return  2 * p * radius;
    }

    bool ednakvi()
    {
        if(plostina() == perimetar())
        {
            return true;
        }
        return false;
    }


private:
    float radius;
    const float p = 3.14;
};

int main()
{
    float r;
    cin >> r;

    Krug k(r);


    //instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
    cout << k.perimetar() << endl;
    cout << k.plostina() << endl;
    cout << k.ednakvi() <<endl;

    //instanciraj objekt od klasata Krug cij radius ne e definiran
    Krug c();
    return 0;
}

