/* За програмски јазик C.

Да се напише структура која ќе опишува отсечка во дводимензионален простор (две точки). Потоа да се напише функција која ќе проверува дали две отсечки се сечат.

*/

#include <stdio.h>
struct tocka
{
    double x;
    double y;
};
typedef struct tocka tocka;

struct otsecka
{
    tocka t1;
    tocka t2;
};
typedef struct otsecka otsecka;

int se_secat(otsecka o1, otsecka o2)
{
    int i=0;
    double slope1=(o1.t2.y - o1.t1.y)/(o1.t2.x - o1.t1.x);
    double slope2=(o2.t2.y - o2.t1.y)/(o2.t2.x - o2.t1.x);
    if (slope1 == slope2)
        return 0;
    else
    {
        if ((o1.t1.x >= o2.t1.x || o1.t1.x <= o2.t2.x) && (o1.t2.x >= o2.t1.x || o1.t2.x <= o2.t2.x))
        {
            if (o1.t1.y>=o2.t1.y)
            {
                if (o2.t2.y >= o1.t2.y)
                {
                    return 1;
                }
            }
            else return 0;
            if (o1.t1.y<= o2.t1.y)
            {
                if (o1.t2.y <= o2.t2.y)
                {
                    return 1;
                }
            }
            else return 0;
        }
        else if ((o2.t1.x >= o1.t1.x || o2.t1.x <= o1.t2.x) && (o2.t2.x >= o1.t1.x || o2.t2.x <= o1.t2.x))
        {
            if (o2.t1.y <= o1.t1.y)
            {
                if (o2.t2.y >= o1.t2.y)
                {
                    i=1;
                }
                else i=0;
            }
            else if (o2.t1.y >= o1.t1.y)
            {
                if (o2.t2.y<= o1.t2.y)
                {
                    i=1;
                }
                else i=0;
            }
        }
    }
    return i;
}


int main()
{
    float x1, y1, x2, y2;
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    tocka t1 = { x1, y1 };
    tocka t2 = { x2, y2 };
    otsecka o1 = { t1, t2 };
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    tocka t3 = { x1, y1 };
    tocka t4 = { x2, y2 };
    otsecka o2 = { t3, t4 };
    printf("%d\n", se_secat(o1, o2));
    return 0;
}
