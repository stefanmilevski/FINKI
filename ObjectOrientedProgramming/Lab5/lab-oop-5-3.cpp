/* Да се напише класа за матрица. Во класата се чуваат елементите од матрицата од тип float (матрица со максимална димензија [10]x[10]) и големината на матрицата (број на редици и колони). За оваа класа да се преоптоварат следните оператори:

оператор + за собирање матрица со број
оператор - за одземање на матрици
оператор * за множење на матрици
операторот >> за внесување на елементите на матрицата
операторот << за печатење на елементите на матрицата
Во главната функција да се креираат објекти A, B и C со подразбирливиот конструктор на класата Matrica. Од стандарден влез да се прочитаат нивните вредности. Да се отпечати вредноста на изразот A-(B*C)+2 на стандарден излез.

Да се претпостави дека секогаш матриците ќе бидат квадратни со ист број на редици и колони. */

#include <iostream>
#include <cstring>

using namespace std;

class Matrica
{
private:
    float matrica[10][10];
    int rows;
    int columns;

public:
    Matrica(int rows = 0,int colums = 0)
    {
        this->rows = rows;
        this->columns = columns;
    }



    Matrica & operator + (int number)
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                matrica[i][j] += number;
            }
        }
        return *this;
    }

    Matrica operator = (const Matrica & m)
    {
        Matrica tmp;
        tmp.columns = m.columns;
        tmp.rows = m.rows;
        for(int i = 0; i < tmp.rows; i++)
        {
            for(int j = 0; j < tmp.columns; j++)
            {
                tmp.matrica[i][j] = m.matrica[i][j];
            }
        }
        return tmp;
    }



    Matrica operator - (const Matrica & m)
    {
        Matrica tmp;
        tmp.columns = m.columns;
        tmp.rows = m.rows;
        for(int i = 0; i < tmp.rows; i++)
        {
            for(int j = 0; j < tmp.columns; j++)
            {
                tmp.matrica[i][j] = matrica[i][j] - m.matrica[i][j];
            }
        }
        return tmp;
    }

    Matrica operator * (const Matrica & m)
    {
        Matrica tmp;
        tmp.columns = m.columns;
        tmp.rows = m.rows;

        int sum;
        for(int i=0; i<tmp.rows; i++)
        {
            for(int j=0; j<tmp.columns; j++)
            {
                sum=0;
                for(int k=0; k<tmp.columns; k++)
                    sum = sum + (matrica[i][k] * m.matrica[k][j]);
                tmp.matrica[i][j] = sum;
            }
        }
        return tmp;
    }

    friend ostream & operator << (ostream & out,const Matrica & m)
    {
        for(int i = 0; i < m.rows; i++)
        {
            for(int j = 0; j < m.columns; j++)
            {
                out << m.matrica[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }

    friend istream & operator >> (istream & in,Matrica & m)
    {
        in >> m.rows >> m.columns;
        for(int i = 0; i < m.rows; i++)
        {
            for(int j = 0; j < m.columns; j++)
            {
                in >> m.matrica[i][j];
            }

        }
        return in;
    }

};

int main()
{
    Matrica A,B,C;
    cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D+2;
    cout << "A" << endl;
    cout<<A << endl;
    cout << "B" << endl;
    cout<<B << endl;
    cout << "C" << endl;
    cout<<C << endl;
    cout << "D" << endl;
    cout<<D << endl;
    cout << "R" << endl;
    cout<<R;
}
