/* Да се креира генеричка класа Array за работа со низи. Класата треба во себе да ги вклучи:

покажувач кон елементи од соодветниот тип
број на елементи во рамките на низата
Елементите во рамките на објектот треба динамички да се алоцираат. Класата треба да ги поддржува следниве методи:

void Erase() - ги брише сите елементи од низата
Т operator[](int i) - за пристап до соодветниот елемент во низата (вклучувајќи и проверка дали индексот е во границите)
int GetLength() - го враќа бројот на елементите во низата
Да се преоптовари operator<< (ostream) за работа со класата (да се претпостави дека елементите од низата го имаат преоптоварено операторот <<).

Надвор од класата да се напишат следниве функции:

void BubbleSort(Array<T> t&)  - ги сорира елементите користејќи го BubbleSort алгоритмот (да се претпостави дека операторот > e преоптоварен за елементите од класата).

Т Sum(Array<T> &) - ги сумира елементите (да се претпостави дека операторот += e преоптоварен за елементите од класата).

Т Average(Array<T>&) - користејќи ја функцијата за сума пресметува просечна вредност на елементите ( операторот / е преоптоварен за елементите)

bool Equal (Array<T>&, Array<M>&) - проверува дали низите се еднакви (се претпоставува дека операторот == е преоптоварен за соодветните класи)

bool Equal (Array <T>&, Array<double>& ) - која ќе изврши пацијална специјализација и ќе смета дека:
 - два елементи се исти ако и само ако се разликуваат за помалку од 0.1
 - разликата од просечната вредност на низите мора да е помала од 0.5. */


#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

class InvalidIndexException {
public:
    void message() {
        cout << "Index out of bounds." << endl;
    }
};


template<typename T>
class Array {
private:
    T *ArrayElements;
    int numberOfElements;
public:

    Array(int numberOfElements = 0) {
        this->numberOfElements = numberOfElements;
        this->ArrayElements = new T[numberOfElements];
    }

    T *getArrayElements() {
        return this->ArrayElements;
    }

    T &operator[](int index) {
        if (index < 0 || index > numberOfElements) {
            throw InvalidIndexException();
        }
        return ArrayElements[index];
    }

    void add(T number) {
        this->ArrayElements[numberOfElements] = number;
    }

    void Erase() {
        this->numberOfElements = 0;
        delete[] ArrayElements;
    }

    int GetLength() {
        return this->numberOfElements;
    }

    friend ostream &operator<<(ostream &out, Array &q) {
        for (int i = 0; i < q.GetLength(); i++) {
            out << "Array[" << i << "] = " << q.ArrayElements[i];
            if (i < q.GetLength() - 1) {
                out << ", ";
            }
        }
        out << endl;

    }

    friend void operator>>(istream &in, Array &q) {
        for (int i = 0; i < q.GetLength(); i++) {
            in >> q.ArrayElements[i];
        }
    }


    Array operator=(Array &a) {
        this->numberOfElements = a.numberOfElements;
        this->ArrayElements = new T[a.numberOfElements];
        for (int i = 0; i < a.GetLength(); i++) {
            ArrayElements[i] = a.ArrayElements[i];
        }

        return *this;
    };
};

template<typename T, typename M>
bool Equal(Array<T> &a1, Array<M> &a2) {
    if (a1.GetLength() == a2.GetLength()) {
        for (int i = 0; i < a1.GetLength(); i++) {
            if (a1.getArrayElements()[i] != a2.getArrayElements()[i]) {
                return false;
            }
        }
        return true;

    } else {
        return false;
    }

}


template<typename T>
T Sum(Array<T> &a) {
    T sum = 0;
    for (int i = 0; i < a.GetLength(); i++) {
        sum += a.getArrayElements()[i];
    }
    return sum;
}

template<typename T>
T Average(Array<T> &a) {
    return Sum(a) / a.GetLength();
}

template<typename T>
void BubbleSort(Array<T> &t) {
    int i, j;
    for (i = 0; i < t.GetLength() - 1; i++) {

        for (j = 0; j < t.GetLength() - i - 1; j++) {

            if (t.getArrayElements()[j] > t.getArrayElements()[j + 1]) {

                T tmp = t.getArrayElements()[j];
                t.getArrayElements()[j] = t.getArrayElements()[j + 1];
                t.getArrayElements()[j + 1] = tmp;
            }
        }

    }

}

template<typename T>
bool Equal(Array<T> &a1, Array<double> &a2) {
    if (a1.GetLength() == a2.GetLength()) {
        for (int i = 0; i < a1.GetLength(); i++) {
            if (abs(a1.getArrayElements()[i] - a2.getArrayElements()[i]) > 0.1 ||
                abs(Average(a1) - Average(a2)) > 0.5) {
                return false;
            }
        }
        return true;

    } else {
        return false;
    }

}


int main() {

    int n;
    double r;

    cin >> r;
    cin >> n;

    Array<int> anArray(n);
    Array<double> adArray(n);
    Array<int> intArray2(n);

    for (int nCount = 0; nCount < n; nCount++) {
        cin >> anArray[nCount];
        adArray[nCount] = anArray[nCount] + r;
    }

    BubbleSort(anArray);

    intArray2 = anArray;

    cout << "The arrays: " << endl;
    cout << anArray;
    cout << "and " << endl;
    cout << intArray2;
    cout << ((Equal(anArray, intArray2)) ? " ARE" : " ARE NOT") << " same!" << endl;
    cout << "The Average of the array adArray is: " << Average(adArray) << endl;

    cout << "The arrays: " << endl;
    cout << anArray;
    cout << "and " << endl;
    cout << adArray;
    cout << ((Equal(anArray, adArray)) ? " ARE" : " ARE NOT") << " same!";


    return 0;
}
