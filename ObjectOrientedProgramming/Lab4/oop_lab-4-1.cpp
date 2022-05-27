/* Да се имплементира класа List во којашто ќе се чуваат информации за:

броеви што се дел од листата (динамички алоцирана низа од цели броеви)
бројот на броеви што се дел од листата
За класата да се дефинираат следните методи:

конструктор (со аргументи), copy-конструктор, деструктор, оператор =
void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
int sum() метод што ја враќа сумата на елементите во листата
double average() метод што ќе го враќа просекот на броевите во листата
Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

низа од листи (динамички алоцирана низа од објекти од класата List)
број на елементи во низата од листи (цел број)
број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
За класата потребно е да ги дефинирате следните методи:

конструктор (default), copy-конструктор, деструктор, оператор =
void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
доколку контејнерот е празен се печати само порака The list is empty.
void addNewList(List l) метод со којшто се додава листа во контејнерот
Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
int sum() метод што ја враќа сумата на сите елементи во сите листи
double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот */


#include <iostream>
#include <cstring>

using namespace std;

class List
{
private:
    int * numbers;
    int sizeOfList;

    void copyMethod(const List & other)
    {
        this->sizeOfList = other.sizeOfList;
        this->numbers = new int[other.sizeOfList];
        this->numbers = other.numbers;
    }


public:
    List(int  * numbers,int sizeOfList = 0)
    {
        this->sizeOfList = sizeOfList;
        this->numbers = new int[sizeOfList];
        for(int i = 0; i < sizeOfList; i++)
        {
            this->numbers[i] = numbers[i];
        }
    }



    List(int sizeOfList = 0)
    {
        this->sizeOfList = sizeOfList;
        this->numbers = new int[sizeOfList];
    }



    List(const List & other)
    {
        copyMethod(other);
    }

    List & operator = (const List & other)
    {
        if(this != &other)
        {
            copyMethod(other);
        }
        return *this;
    }



    int * getNumbers()
    {
        return this->numbers;
    }

    int getSize()
    {
        return this->sizeOfList;
    }

    int sum()
    {
        int sum = 0;
        for(int i = 0; i < sizeOfList; i++)
        {
            sum += numbers[i];
        }
        return sum;
    }

    double average()
    {
        int sum = this->sum();
        return (1.0 * sum) / sizeOfList;
    }


    void pecati()
    {
        cout << sizeOfList << ": ";
        for(int p = 0; p< sizeOfList; p++)
        {
            cout << numbers[p] << " ";
        }
        cout << "sum: " << sum() << " average: " << average();
    }


};


class ListContainer
{
private:
    List * lists;
    int numberOfElements;
    int triesToAddList = 0;

public:
    ListContainer(int numberOfElements = 0)
    {
        this->numberOfElements = numberOfElements;
        this->lists = new List[numberOfElements];
        this->triesToAddList = 0;
    }

    ListContainer(const ListContainer & other)
    {
        this->numberOfElements = other.numberOfElements;
        delete [] lists;
        this->lists = new List[numberOfElements];
        this->lists = other.lists;

        this->triesToAddList = other.triesToAddList;
    }

    ListContainer & operator = (ListContainer & other)
    {
        if(this != &other)
        {
            this->numberOfElements = other.numberOfElements;
            delete [] lists;
            this->lists = new List[numberOfElements];
            this->lists = other.lists;
            this->triesToAddList = other.triesToAddList;

        }
        return *this;
    }


    void print()
    {
        if(numberOfElements == 0)
        {
            cout <<"The list is empty" << endl;
        }
        else
        {
            for(int i = 0; i < numberOfElements; i++)
            {

                cout << "List number: "  << i+1 << " List info: ";
                lists[i].pecati();
                cout << endl;

            }
            cout << "Sum: " << sum() << " Average: " << average() << endl;
            cout << "Successful attempts: " << this->numberOfElements << " Failed attempts: " <<    triesToAddList<< endl;




        }


    }

    bool checkIfSumAlreadyExists(List l)
    {
        int sum = l.sum();
        bool flag = false;
        for(int i = 0; i < numberOfElements; i++)
        {
            if(sum == lists[i].sum())
            {
                flag = true;
            }
        }
        return flag;
    }

    void addNewList(List l)
    {


        if(!checkIfSumAlreadyExists(l))
        {

            List * tmp = new List[this->numberOfElements+1];
            for(int i = 0; i < this->numberOfElements; i++)
            {
                tmp[i] = this->lists[i];
            }
            tmp[this->numberOfElements++] = l;

            delete [] lists;
            this->lists = tmp;
        }
        else
        {

            this->triesToAddList++;

        }



    }

    int sum()
    {
        int total = 0;
        for(int i = 0; i < numberOfElements; i++)
        {
            total += lists[i].sum();
        }
        return total;
    }

    double average()
    {
        double total = 0;
        int countOfEntries = 0;
        for(int i = 0; i < numberOfElements; i++)
        {
            total += lists[i].sum();
            countOfEntries += lists[i].getSize();
        }
        return total / countOfEntries;
    }



};

int main()
{

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0; i<N; i++)
    {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0; j<n; j++)
        {
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1)
    {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else
    {
        lc.print();
    }
}
