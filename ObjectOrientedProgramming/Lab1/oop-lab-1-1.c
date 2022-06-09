/* За програмски јазик C.

Да се напише програма во која од стандарден влез се вчитува N (бројот на производи), а потоа се вчитуваат податоците за N производи (име, цена, количина). Програмата треба на стандарден излез да ја отпечати листата на купени производи и вкупната сума која треба да се плати во следниот облик (пример):

1. Flips    10.00 x 3 = 30.00
2. CocaCola 75.00 x 2 = 150.00
3. ChokoBanana  5.00 x 10 = 50.00
Total: 230.00 */

#include <stdio.h>

struct proizvod
{
    char ime[50] ;
    float cena;
    float kolicina;

};




typedef struct proizvod proizvod;

int main()
{
    int n;
    scanf("%d",&n );
    proizvod proizvod;

    float total = 0.0;
    for(int i= 1; i<= n; i++)
    {
        printf("%d. ", i);
        scanf("%s %f %f ", &proizvod.ime, &proizvod.cena, &proizvod.kolicina);
        printf("%s\t%.2f x %.1f = %.2f\n",proizvod.ime, proizvod.cena,proizvod.kolicina, proizvod.cena*proizvod.kolicina);
        total += proizvod.cena*proizvod.kolicina;


    }


    printf("Total: %.2f \n", total);




    return 0;
}
