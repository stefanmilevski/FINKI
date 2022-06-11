/* Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

името (низа од 50 знаци),
електронска адреса (низа од 50 знаци),
вид на купувач (стандардни, лојални или вип),
основен попуст (цел број изразен во проценти),
дополнителен попуст (цел број изразен во проценти) и
број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата. Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

За оваа класа да се имплементира оператор << за печатење на купувач во формат:

[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени) */


#include <iostream>
#include <cstring>

using namespace std;
#define MAX  100


class UserExistsException {
public:

    void message() {
        cout << "The user already exists in the list!" << endl;
    }
};


enum typeC {
    standard, loyal, vip
};

class Customer {
protected:
    char name[50];
    char email[50];
    typeC type;
    static int baseDiscount;
    static int additionalDiscount;
    int numberOfProductsBought;

public:
    Customer() {
        strcpy(this->name, "name");
        strcpy(this->email, "email");
        this->type = standard;
        this->numberOfProductsBought = 0;
    }


    Customer(char name[50], char email[50], typeC type = standard, int numberOfProductsBought = 0) {
        strcpy(this->name, name);
        strcpy(this->email, email);
        this->type = type;
        this->numberOfProductsBought = numberOfProductsBought;
    }

    Customer(Customer &other) {
        strcpy(this->name, other.name);
        strcpy(this->email, other.email);
        this->type = other.type;
        this->numberOfProductsBought = other.numberOfProductsBought;
    }

    Customer &operator=(Customer &other) {
        if (this != &other) {
            strcpy(this->name, other.name);
            strcpy(this->email, other.email);
            this->type = other.type;
            this->numberOfProductsBought = other.numberOfProductsBought;
        }
        return *this;
    }

    const char *getName() const;

    const char *getEmail() const;

    static void setDiscount1(int discount) {
        Customer::baseDiscount = discount;
    }

    friend ostream &operator<<(ostream &out, Customer &c) {
        out << c.name << endl;
        out << c.email << endl;
        out << c.numberOfProductsBought << endl;
        if (c.type == 1) {
            out << "loyal ";
            out << baseDiscount << endl;
        } else if (c.type == 2) {
            out << "vip ";
            out << baseDiscount + additionalDiscount << endl;
        } else {
            out << "standard 0" << endl;
        }
        return out;
    }

    typeC getType() const;

    void setType(typeC type);

    int getNumberOfProductsBought() const;

    void setNumberOfProductsBought(int numberOfProductsBought);

};

int Customer::baseDiscount = 10;
int Customer::additionalDiscount = 20;

typeC Customer::getType() const {
    return type;
}

void Customer::setType(typeC type) {
    Customer::type = type;
}

int Customer::getNumberOfProductsBought() const {
    return numberOfProductsBought;
}

void Customer::setNumberOfProductsBought(int numberOfProductsBought) {
    Customer::numberOfProductsBought = numberOfProductsBought;
}

const char *Customer::getName() const {
    return name;
}

const char *Customer::getEmail() const {
    return email;
}

class FINKI_bookstore {
private:
    Customer *customers;
public:
    Customer *getCustomers() const {
        return customers;
    }

    void setCustomers(Customer *customers, int number) {
        FINKI_bookstore::customers = customers;
        FINKI_bookstore::numberOfCustomers = number;
    }

private:
    int numberOfCustomers;

public:
    FINKI_bookstore() {
        this->numberOfCustomers = 0;
        this->customers = new Customer[numberOfCustomers];

    }

    FINKI_bookstore &operator+=(Customer &c) {
        for (int i = 0; i < numberOfCustomers; i++) {
            if (strcmp(customers[i].getEmail(), c.getEmail()) == 0) {
                throw UserExistsException();
            }
        }


        Customer *tmp = new Customer[numberOfCustomers + 1];
        for (int i = 0; i < numberOfCustomers; i++) {
            tmp[i] = customers[i];
        }

        tmp[numberOfCustomers++] = c;
        customers = tmp;
        return *this;
    }


    friend ostream &operator<<(ostream &out, FINKI_bookstore &fb) {
        for (int i = 0; i < fb.numberOfCustomers; i++) {
            out << fb.customers[i];
        }
        return out;
    }

    void update() {
        for (int i = 0; i < numberOfCustomers; i++) {
            if (customers[i].getNumberOfProductsBought() > 10 && customers[i].getType() == 1) {
                customers[i].setType(vip);
            }

            if (customers[i].getNumberOfProductsBought() > 5 && customers[i].getType() == 0) {
                customers[i].setType(loyal);
            }
        }
    }

};


int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc += c;

        }catch (UserExistsException & e){
            e.message();
        }
        cout << fc;


    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        Customer c1;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            c1 = c;
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        try{
            fc += c1;
        }catch (UserExistsException & e){
            e.message();
        }


        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
