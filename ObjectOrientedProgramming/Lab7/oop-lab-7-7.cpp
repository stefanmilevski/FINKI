/* Да се имплементира апстрактна класа Secret со два чисто виртуелни методи:

double simpleEntropy() - се пресеметува како бројот на уникатни (цифри/букви) поделен со бројот на вкупно знаци. (2 поени)
int total()- го враќа вкупниот број на цифри/букви. (1 поени)
Од оваа класа да се имплементираат две изведени класи DigitSecret (цифри 0-9) и CharSecret (букви a-z) во кои се чува низа од максимум 100 цифри односно 100 мали букви од a до z (1 поени).

Да се имплементира соодветен конструктор, како и следните оператори:

оператори== и != за споредување на два објекти од каков било тип (DigitSecret,CharSecret) според елементите што ги содржат (1 поени)
оператор << за печатење на стандарден излез во формат: (1 поени)
[cifri/bukvi] Simple entropy: [entropy] Total: [total]

Да се имплементираaт методите:

void process(Secret **secrets, int n) - што прима низа од покажувачи од класата Secret и нивниот број и треба да го отпечати елементот со најголема вредност за simpleEntropy. (3 поени)
void printAll(Secret **secrets, int n) - што прима исти аргументи како претходниот и треба да ги испечати сите елементи во низата secrets. (1 поен) */


#include<cstring>
#include<iostream>

using namespace std;

class Secret {
public:
    virtual double simpleEntropy() const = 0;

    virtual int total() const = 0;

    virtual void print() = 0;
};

bool operator==(Secret &s1, Secret &s2) {
    if (s1.total() == s2.total()) {
        return true;
    }
    return false;
}

bool operator!=(Secret &s1, Secret &s2) {
    if (s1.total() == s2.total()) {
        return false;
    }
    return true;
}


class DigitSecret : public Secret {
private:
    int numbers[100];
    int count;

public:
    DigitSecret(int *numbers = {}, int count = 0) {
        this->count = count;
        for (int i = 0; i < count; i++) {
            this->numbers[i] = numbers[i];
        }
    }


    double simpleEntropy() const {
        double unique = 0.0;
        int counter = 0;

        for (int i = 0; i < count; i++) {
            counter = 0;
            for (int j = 0; j < count; j++) {
                if ((i != j) && (numbers[i] == numbers[j]))
                    counter++;
            }
            if (counter == 0)
                unique += 1.0;
        }

        return unique / total();
    }

    int total() const {
        return count;
    }

    friend ostream &operator<<(ostream &out, DigitSecret &d) {
        for (int i = 0; i < d.count; i++) {
            out << d.numbers[i];
        }
        out << " Simple entropy: " << d.simpleEntropy() << " Total: " << d.total();
    }

    void print() {
        for (int i = 0; i < count; i++) {
            cout << numbers[i];
        }
        cout << " Simple entropy: " << simpleEntropy() << " Total: " << total() << endl;
    }

};

class CharSecret : public Secret {
private:
    char chars[100];

public:
    CharSecret(char *chars) {
        strcpy(this->chars, chars);
    }

    double simpleEntropy() const {
        double unique = 0.0;
        int counter = 0;

        for (int i = 0; i < total(); i++) {
            counter = 0;
            for (int j = 0; j < total(); j++) {
                if ((i != j) && (chars[i] == chars[j]))
                    counter++;
            }
            if (counter == 0)
                unique += 1.0;
        }

        return unique / total();
    }

    int total() const {
        return strlen(chars);
    }

    friend ostream &operator<<(ostream &out, CharSecret &d) {
        out << d.chars;
        out << " Simple entropy: " << d.simpleEntropy() << " Total: " << d.total() << endl;
    }

    void print() {
        cout << chars;
        cout << " Simple entropy: " << simpleEntropy() << " Total: " << total() << endl;
    }


};

void process(Secret **secrets, int n) {

    double maxSimpleEntropy = -888;
    int index = -888;
    for (int i = 0; i < n; i++) {
        if (secrets[i]->simpleEntropy() > maxSimpleEntropy) {
            maxSimpleEntropy = secrets[i]->simpleEntropy();
            index = i;
        }
    }

    CharSecret *charSecretPtr = dynamic_cast<CharSecret *>(secrets[index]);
    if (charSecretPtr != 0) {
        cout << *charSecretPtr;
    }

    DigitSecret *digitSecretPtr = dynamic_cast<DigitSecret *>(secrets[index]);
    if (digitSecretPtr != 0) {
        cout << *digitSecretPtr;
    }

}

void printAll(Secret **secrets, int n) {
    for (int i = 0; i < n; i++) {
        secrets[i]->print();
    }
}


int main() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << "Constructors" << endl;
        int numbers[] = {1, 2, 3, 4, 5};
        DigitSecret ds(numbers, 5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if (n == 1) {
        cout << "operator <<" << endl;
        int numbers[] = {1, 2, 3, 4, 5};
        DigitSecret ds(numbers, 5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    } else if (n == 2) {
        cout << "== and !=" << endl;
        int numbers[] = {1, 2, 3, 4, 5};
        DigitSecret ds(numbers, 5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if (n == 3) {
        cout << "Secret processor" << endl;
        int numbers1[] = {1, 2, 3, 4, 5, 6, 4, 3, 2, 1, 1, 2, 3, 4, 5};
        DigitSecret ds1(numbers1, 15);
        int numbers2[] = {1, 2, 3, 4, 5, 0, 0, 0, 5, 5, 4, 4, 3, 3, 2};
        DigitSecret ds2(numbers2, 15);
        int numbers3[] = {1, 0, 9, 4, 3, 8, 4, 0, 9, 3, 1, 4, 3, 2, 1, 4, 4, 3, 7, 2};
        DigitSecret ds3(numbers3, 20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret **s = new Secret *[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s, 6);
        delete[] s;
    } else if (n == 4) {
        cout << "Print all secrets" << endl;
        int numbers1[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5};
        DigitSecret ds1(numbers1, 15);
        int numbers2[] = {1, 2, 3, 4, 5, 0, 0, 0, 5, 5, 4, 4, 3, 3, 2};
        DigitSecret ds2(numbers2, 15);
        int numbers3[] = {1, 0, 9, 4, 3, 8, 4, 0, 9, 3, 1, 4, 3, 2, 1, 4, 4, 3, 7, 2};
        DigitSecret ds3(numbers3, 20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret **s = new Secret *[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s, 6);
        delete[] s;
    }

    return 0;
}