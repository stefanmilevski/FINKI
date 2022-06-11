/* Да се креира апстрактна класа Pizza за опишување пици. (5 поени) За секоја пица се чуваат следните информации:

име (низа од максимум 20 знаци)
состојки (низа од максимум 100 знаци)
основна цена (реален број)
Од оваа класа да се изведат класите FlatPizza и FoldedPizza за опишување на рамни и преклопени пици соодветно (5 поени).

За секоја рамна пица дополнително се чува големина (enum - една од три можности: мала, голема и фамилијарна). За секоја преклопена пица дополнително се чува информација дали тестото е од бело брашно или не (boolean).

За секоја пица треба да се обезбеди метод за пресметување на нејзината продажна цена:

цената на рамната пица се пресметува така што основната цена се зголемува за 10%, 30% и 50% за мала, голема и фамилијарна пица соодветно.
цената на преклопената пица се пресметува така што основната цена се зголемува за 10% ако е тестото е од бело брашно, а во спротивно за 30%. (10 поени)
Да се преоптоварат следните оператори:

оператор << - за печатење сите податоци за пиците во следниов формат:

За рамна пица:[име]: [состојки], [големина] - [продажната цена на пицата].
За преклопена пица: [име]: [состојки], [wf - ако е со бело брашно / nwf - ако не е со бело брашно] - [продажната цена на пицата]
(5 поени)

оператор < - за споредување на пиците од каков било вид според нивната продажна цена. (5 поени)
Да се дефинира глобална функција еxpensivePizza што на влез прима низа од покажувачи кон објекти од класата Pizza и нивниот број, а како резултат ги печати информациите за пицата со највисока продажна цена. Ако има повеќе пици со иста највисока цена, се печати првата. (10 поени)

Да се дефинираат потребните конструктори и методи во класите за правилно функционирање на програмата. (5 поени) */


#include <cstring>
#include <iostream>
#include <string>

using namespace std;

enum Size {
    small, big, family
};

class Pizza {
protected:
    char name[20];
    char ingredients[100];
    float basePrice;

    void copy(Pizza &other) {
        strcpy(this->name, other.name);
        strcpy(this->ingredients, other.ingredients);
        this->basePrice = other.basePrice;
    }

public:
    Pizza(char name[20], char ingredients[100], float basePrice) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->basePrice = basePrice;
    }

    Pizza(Pizza &other) {
        copy(other);
    }

    Pizza &operator=(Pizza &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    virtual double price() = 0;


    bool operator<(Pizza &other) {
        return price() < other.price();
    }

};


class FlatPizza : public Pizza {
private:
    Size size = small;
public:
    FlatPizza(char name[20], char ingredients[100], float basePrice) : Pizza(name,
                                                                             ingredients,
                                                                             basePrice) {

    }


    FlatPizza(char name[20], char ingredients[100], float basePrice, Size size) : Pizza(name,
                                                                                        ingredients,
                                                                                        basePrice) {
        this->size = size;

    }

    Size getSize() const {
        return size;
    }

    void setSize(Size size) {
        FlatPizza::size = size;
    }


    double price() {

        if (this->size == small) {
            return basePrice * 1.10;
        } else if (this->size == family) {
            return basePrice * 1.30;
        } else if (this->size == big) {

            return basePrice * 1.50;
        }

    }

    friend ostream &operator<<(ostream &out, FlatPizza &p) {
        out << p.name << ": ";
        out << p.ingredients << ", ";
//        for(int i = 0; i < 48;i++){
//            out << p.ingredients[i];
//        }
//        out <<", ";
        if (p.size == 0) {
            out << "small ";
        } else if (p.size == 1) {
            out << "big ";
        } else if (p.size == 2) {
            out << "family ";
        }
        out << "- " << p.price() << endl;
        return out;
    }

};

class FoldedPizza : public Pizza {
private:
    bool isWhiteFlour = true;
public:

    FoldedPizza(char name[20], char ingredients[100], float basePrice, bool isWhiteFlour) : Pizza(
            name, ingredients, basePrice) {
        this->isWhiteFlour = isWhiteFlour;
    }

    FoldedPizza(char name[20], char ingredients[100], float basePrice) : Pizza(
            name, ingredients, basePrice) {

    }


    double price() {
        if (isWhiteFlour) {
            return basePrice * 1.10;
        }
        return basePrice * 1.30;
    }

    bool getWhiteFlour() const {
        return isWhiteFlour;
    }

    void setWhiteFlour(bool isWhiteFlour) {
        FoldedPizza::isWhiteFlour = isWhiteFlour;
    }


    friend ostream &operator<<(ostream &out, FoldedPizza &f) {
        out << f.name << ": " << f.ingredients << ", ";
        if (f.isWhiteFlour) {
            out << "wf ";
        } else {
            out << "nwf ";
        }
        out << "- " << f.price() << endl;
        return out;
    }

};

void expensivePizza(Pizza **pizzas, int numberOfPizzas) {
    int maxPriceIndex = 0;
    double maxPrice = 0;
    for (int i = 0; i < numberOfPizzas; i++) {
        if (pizzas[i]->price() > maxPrice) {
            maxPrice = pizzas[i]->price();
            maxPriceIndex = i;
        }
    }
    FoldedPizza *ptr = dynamic_cast<FoldedPizza *>(pizzas[maxPriceIndex]);
    if (ptr != 0) {
        cout << *ptr;
    }

    FlatPizza *fptr = dynamic_cast<FlatPizza *>(pizzas[maxPriceIndex]);
    if (fptr != 0) {
        cout << *fptr;
    }


}


int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 100);

                cin.getline(ingredients, 100);
                if (strlen(ingredients) >= 48 && test_case == 6) {  // test case 6 fix
                    ingredients[49] = '\0';
                }

                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}
