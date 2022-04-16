#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


#define SIZE 52

int runda;

int wygrane_a, wygrane_b;

struct Cards
{
    char kolor[5];
    int wartosc;
}deck[SIZE], hand_1[SIZE * 2], hand_2[SIZE * 2];

void tworzenie_talii(struct Cards tab[], int MIN, int wielkosc)
{

    int wartosc = 14, z = 0;
    char b[] = "karo", c[] = "kier", d[] = "trefl", zmienna[5] = "pik";
    for (int i = 0; i < wielkosc; i++, wartosc--) {
        tab[i].wartosc = wartosc;
        for (int j = 0; j < 5; j++) {
            tab[i].kolor[j] = zmienna[j];
        }
        if (wartosc == MIN) {
            if (z == 0) { for (int j = 0; j < 5; j++) zmienna[j] = b[j]; }
            if (z == 1) { for (int j = 0; j < 5; j++) zmienna[j] = c[j]; }
            if (z == 2) { for (int j = 0; j < 5; j++) zmienna[j] = d[j]; }
            wartosc = 15;
            z++;
        }
        if (z == 4)
            break;
    }
}

int sprawdz_losowana_liczbe(int liczba[], int i) {
    for (int j = 0; j < i; j++)
        if (liczba[i] == liczba[j]) return 1;
    return 0;
}

void losowanie_liczby(int liczba_losowa[], int wielkosc)
{
    srand(time(NULL));
    for (int i = 0; i < wielkosc; i++) {
        liczba_losowa[i] = rand() % wielkosc;
        if (sprawdz_losowana_liczbe(liczba_losowa, i)) i--;
    }

}

void tasowanie_talii(struct Cards tab[], int liczba_losowa[], int wielkosc) {
    struct Cards przetasowana_talia[SIZE];
    for (int i = 0; i < wielkosc; i++)
        przetasowana_talia[i] = tab[liczba_losowa[i]];
    for (int i = 0; i < wielkosc; i++)
        tab[i] = przetasowana_talia[i];
}

void rozdawanie_kart(struct Cards tab_1[], struct Cards tab_2[], struct Cards karty[]) {
    char napis[] = "0";
    for (int i = 0, j = 1; i < SIZE / 2; i++, j += 2) {
        tab_1[i] = karty[j - 1];
        tab_2[i] = karty[j];
    }

}

void przesuniecie(struct Cards tab_1[], struct Cards tab_2[], int x)
{
    for (int k = 0; k < x + 1; k++) {
        for (int i = 0; i < SIZE; i++) {
            tab_1[i] = tab_1[i + 1];
            tab_2[i] = tab_2[i + 1];
        }
    }
}

void bitwa(struct Cards tab_1[], struct Cards tab_2[]) {

    for (int i = 0; i < SIZE; i++) {
        if (tab_1[i].wartosc == 0) {
            tab_1[i] = tab_1[0];
            tab_1[i + 1] = tab_2[0];
            break;
        }
    }
    przesuniecie(tab_1, tab_2, 0);
}

void wojna(struct Cards tab_1[], struct Cards tab_2[], int x, bool wariant) {

    runda += 3;

    if (wariant == false) {     //WARIANT B
        if (tab_2[x - 1].wartosc == 0) {
            tab_2[x - 1] = tab_1[x - 1];
            tab_2[x] = tab_1[x];
            for (int i = x - 1; i < SIZE; i++)
                tab_1[i] = tab_1[i + 2];

        }
        if (tab_1[x - 1].wartosc == 0) {
            tab_1[x - 1] = tab_2[x - 1];
            tab_1[x] = tab_2[x];
            for (int i = x - 1; i < SIZE; i++)
                tab_2[i] = tab_2[i + 2];

        }
        if (tab_2[x].wartosc == 0) {
            tab_2[x] = tab_2[x - 1];
            tab_2[x - 1] = tab_1[x - 1];
            for (int i = x - 1; i < SIZE; i++)
                tab_1[i] = tab_1[i + 1];

        }
        if (tab_1[x].wartosc == 0) {
            tab_1[x] = tab_1[x - 1];
            tab_1[x - 1] = tab_2[x - 1];
            for (int i = x - 1; i < SIZE; i++)
                tab_2[i] = tab_2[i + 1];

        }
    }



    std::cout << "WOJNA" << std::endl;
    std::cout << "  " << tab_1[x - 2].wartosc << "  " << tab_1[x - 2].kolor << " || " << tab_2[x - 2].wartosc << "  " << tab_2[x - 2].kolor << "    #" << runda - 2 << std::endl;
    std::cout << "  " << tab_1[x - 1].wartosc << " ? " << tab_1[x - 1].kolor << " || " << tab_2[x - 1].wartosc << " ? " << tab_2[x - 1].kolor << "    #" << runda - 1 << std::endl;
    std::cout << "  " << tab_1[x].wartosc << "  " << tab_1[x].kolor << " || " << tab_2[x].wartosc << "  " << tab_2[x].kolor << "    #" << runda << std::endl;



    if (wariant == true) { //WARIANT A

        if (tab_2[x - 1].wartosc == 0 || tab_2[x].wartosc == 0) {
            std::cout << "Graczowi drugiemu skonczyly sie karty!" << std::endl;
            tab_2[0].wartosc = 0;
            return;
        }
        if (tab_1[x - 1].wartosc == 0 || tab_1[x].wartosc == 0) {
            std::cout << "Graczowi pierwszemu skonczyly sie karty!" << std::endl;
            tab_1[0].wartosc = 0;
            return;
        }
    }


    if (tab_1[x].wartosc > tab_2[x].wartosc) {
        for (int i = 0; i < SIZE; i++) {
            if (tab_1[i].wartosc == 0) {
                for (int j = 0; j <= x; j++) {
                    tab_1[i + j] = tab_1[j];
                    tab_1[i + j + x + 1] = tab_2[j];
                }
                break;
            }
        }
        przesuniecie(tab_1, tab_2, x);
        return;
    }


    if (tab_1[x].wartosc < tab_2[x].wartosc) {
        for (int i = 0; i < SIZE; i++) {
            if (tab_2[i].wartosc == 0) {
                for (int j = 0; j <= x; j++) {
                    tab_2[i + j] = tab_2[j];
                    tab_2[i + j + x + 1] = tab_1[j];
                }
                break;
            }
        }
        przesuniecie(tab_2, tab_1, x);
        return;
    }


    if (tab_1[x].wartosc == tab_2[x].wartosc) {
        runda--;
        wojna(tab_1, tab_2, x + 2, wariant);
    }
}



void rozgrywka(struct Cards tab_1[], struct Cards tab_2[], bool wariant) {
    while (1) {
        while (1) {
            if (tab_1[0].wartosc > tab_2[0].wartosc) {
                runda++;
                std::cout << tab_1[0].wartosc << "  " << tab_1[0].kolor << " || " << tab_2[0].wartosc << "  " << tab_2[0].kolor << "    #" << runda << std::endl;
                bitwa(tab_1, tab_2);
                break;
            }
            if (tab_1[0].wartosc < tab_2[0].wartosc) {
                runda++;
                std::cout << tab_1[0].wartosc << "  " << tab_1[0].kolor << " || " << tab_2[0].wartosc << "  " << tab_2[0].kolor << "    #" << runda << std::endl;
                bitwa(tab_2, tab_1);
                break;
            }
            if (tab_1[0].wartosc == tab_2[0].wartosc) {
                wojna(tab_1, tab_2, 2, wariant);
                break;
            }
        }
        if (tab_2[0].wartosc == 0) {
            printf("WYGRYWA GRACZ 1 \n");
            wygrane_a++;
            break;
        }
        if (tab_1[0].wartosc == 0) {
            printf("WYGRYWA GRACZ 2 \n");
            wygrane_b++;
            break;
        }
    }
}

void wariant_talii(struct Cards tab[], int wielkosc, int MIN) {
    tworzenie_talii(tab, MIN, wielkosc);
    int *liczba = new int[wielkosc];
    losowanie_liczby(liczba, wielkosc);
    tasowanie_talii(tab, liczba, wielkosc);
}

int main()
{

    char wybor;
    wybor = 'c';
    std::cout << "wybierz wielkosc talii:" << std::endl;
    std::cout << "Talia 20 kart <10,AS> - \"A\"" << std::endl;
    std::cout << "Talia 24 kart <9,AS> - \"B\"" << std::endl;
    std::cout << "Talia 28 kart <8,AS> - \"C\"" << std::endl;
    std::cout << "Talia 32 kart <7,AS> - \"D\"" << std::endl;
    std::cout << "Talia 36 kart <6,AS> - \"E\"" << std::endl;
    std::cout << "Talia 40 kart <5,AS> - \"F\"" << std::endl;
    std::cout << "Talia 44 kart <4,AS> - \"G\"" << std::endl;
    std::cout << "Talia 48 kart <3,AS> - \"H\"" << std::endl;
    std::cout << "Talia 52 kart <2,AS> - \"I\"" << std::endl;
    std::cout << "WYBOR: ";
    std::cin >> wybor;
    switch (wybor) {
    case'A': case'a':
        wariant_talii(deck, 20, 10);
        break;
    case'B': case'b':
        wariant_talii(deck, 24, 9);
        break;
    case'C': case'c':
        wariant_talii(deck, 28, 8);
        break;
    case'D': case'd':
        wariant_talii(deck, 32, 7);
        break;
    case'E': case'e':
        wariant_talii(deck, 36, 6);
        break;
    case'F': case'f':
        wariant_talii(deck, 40, 5);
        break;
    case'G': case'g':
        wariant_talii(deck, 44, 4);
        break;
    case'H': case'h':
        wariant_talii(deck, 48, 3);
        break;
    case'I': case'i':
        wariant_talii(deck, 52, 2);
        break;
    default: break;
    }

    rozdawanie_kart(hand_1, hand_2, deck);


    std::cout << "Wariant wojny A - \"A\"" << std::endl;
    std::cout << "Wariant wojny B - \"B\"" << std::endl;
    std::cout << "Wybor: ";
    std::cin >> wybor;

    switch (wybor) {
    case'A': case'a':
        rozgrywka(hand_1, hand_2, true);
        break;
    case'B': case'b':
        rozgrywka(hand_1, hand_2, false);
        break;
    default: break;
    }



    return 0;
}