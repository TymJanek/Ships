/*
 * Do napisanego programu (gry w statki) dodać następujące funkcje:
 *   1. Możliwość dodawania jednomasztowców, trójmasztowców i czteromasztowców.
 *   2. Dodać informację o zatopieniu statku (Statek).
 *   3. Dodać informację o zatopieniu wszystkich statków – koniec gry (Plansza).
 *   4. Możliwość dotykania przez statki ścian planszy.
 *   5. Pozwolić na pionowy układ statków.
 *   6. Stworzyć drugą planszę.
 *   7. Zezwolić użytkownikowi na ustawienie statków (zadana liczba każdego rodzaju) dla dwóch plansz.
 *   8. Pozwolić na grę pomiędzy dwoma użytkownikami.
 *   9. Pozwolić na inny układ większych statków.
 */

#include <iostream>
using namespace std;

class Statek {
public:
    virtual void rysuj(int x, int y){}
    virtual void traf(int x, int y){};
    virtual bool czyZatopiony(){};
};

class Jednomasztowiec : public Statek {
private:
    int x, y, size = 1, hits = 0;
    char poklad[1];
public:
    Jednomasztowiec(int x, int y) : x(x), y(y) {
        poklad[0] = '_';
    }
    virtual void rysuj(int x, int y){
        cout << poklad[y - this->y];
    }
    virtual void traf(int x, int y){
        if(poklad[y - this -> y] == '_'){
            hits++;
        }
        poklad[y - this->y] = 'T';
    }
    virtual bool czyZatopiony(){
        if(hits < size){
            return false;
        }
        else{
            return true;
        }
    }
};

class Dwumasztowiec : public Statek {
private:
    int x, y, size = 2, hits = 0;
    char poklad[2];
public:
    Dwumasztowiec(int x, int y) : x(x), y(y) {
        poklad[0] = '_';
        poklad[1] = '_';
    }
    virtual void rysuj(int x, int y){
        cout << poklad[y - this->y];
    }
    virtual void traf(int x, int y){
        if(poklad[y - this -> y] == '_'){
            hits++;
        }
        poklad[y - this->y] = 'T';
    }
    virtual bool czyZatopiony(){
        if(hits < size){
            return false;
        }
        else{
            return true;
        }
    }
};

class Trojmasztowiec : public Statek {
private:
    int x, y, size = 3, hits = 0;
    char poklad[3];
public:
    Trojmasztowiec(int x, int y) : x(x), y(y) {
        poklad[0] = '_';
        poklad[1] = '_';
        poklad[2] = '_';
    }
    virtual void rysuj(int x, int y){
        cout << poklad[y - this->y];
    }
    virtual void traf(int x, int y){
        if(poklad[y - this -> y] == '_'){
            hits++;
        }
        poklad[y - this->y] = 'T';
    }
    virtual bool czyZatopiony(){
        if(hits < size){
            return false;
        }
        else{
            return true;
        }
    }
};

class Czteromasztowiec : public Statek {
private:
    int x, y, size = 4, hits = 0;
    char poklad[4];
public:
    Czteromasztowiec(int x, int y) : x(x), y(y) {
        poklad[0] = '_';
        poklad[1] = '_';
        poklad[2] = '_';
        poklad[3] = '_';
    }
    virtual void rysuj(int x, int y){
        cout << poklad[y - this->y];
    }
    virtual void traf(int x, int y){
        if(poklad[y - this -> y] == '_'){
            hits++;
        }
        poklad[y - this->y] = 'T';
    }
    virtual bool czyZatopiony(){
        if(hits < size){
            return false;
        }
        else{
            return true;
        }
    }
};


char getChar(int z){
    return z+'a';
}

int getInt(char z){
    return z-'a';
}

class Plansza {
private:
    int wys, szer;
    int lStatkow;
    Statek * statki[10];
    int ** mapa; //0 - wolne pole, -1 - pudło, x - numer statku.
public:
    Plansza(int wys, int szer);
    ~Plansza();
    int dajWys();
    int dajSzer();
    bool pustePole(int x, int y);
    void dodajStatek(int x, int y, int w);
    int dajLStatkow();
    void strzel(int w, int k);
    void rysuj();
};

Plansza::Plansza(int wys, int szer){
    this->wys = wys;
    this->szer = szer;
    lStatkow = 0;

    mapa = new int*[wys];
    for(int i=0; i<szer; i++)
        mapa[i] = new int[szer];

    for(int i=0; i<wys; i++)
        for(int j=0; j<szer; j++)
            mapa[i][j]=-1;



    dodajStatek(1, 0, 1);   // 2a
    dodajStatek(2, 2, 2);   // 3c & 3d
    dodajStatek(6, 2, 3);     // 7c & 7d & 7d
    dodajStatek(4, 4, 4);   // 5e & 5f & 5g & 5h

}

Plansza::~Plansza(){
    for(int i=0; i<dajWys(); i++)
        delete [] mapa[i];
    delete [] mapa;
    for(int i=0; i<lStatkow; i++)
        delete statki[i];
}

int Plansza::dajWys(){
    return wys;
}

int Plansza::dajSzer(){
    return szer;
}

int Plansza::dajLStatkow() {
    return lStatkow;
}

bool Plansza::pustePole(int x, int y){
    if(x<dajWys() && x>0 && y<dajSzer() && y>0){
        bool wynik = true;
        for(int i=x-1; i<x+2; i++)
            for(int j=y-1; j<y+2; j++)
                if(mapa[i][j]!=-1)
                    wynik=false;
        return wynik;
    }
    return false;
}

void Plansza::dodajStatek(int x, int y, int w){
    bool wolne=true;
    for(int i=0; i<w; i++)
        if(!pustePole(x,y+1))
            wolne=false;
    if(wolne){
        for(int i=0; i<w; i++)
            mapa[x][y+i] = lStatkow;
        if(w == 1){
            Statek *st = new Jednomasztowiec(x, y);
            statki[lStatkow++] = st;
        }
        else if(w == 2){
            Statek *st = new Dwumasztowiec(x, y);
            statki[lStatkow++] = st;
        }
        else if(w == 3){
            Statek *st = new Trojmasztowiec(x, y);
            statki[lStatkow++] = st;
        }
        else if(w == 4){
            Statek *st = new Czteromasztowiec(x, y);
            statki[lStatkow++] = st;
        }

    }
    else
        cout << endl << "Błędna pozycja statku" << endl << endl;
}

void Plansza::strzel(int w, int k){
    if(mapa[w][k]>=0) {
        statki[mapa[w][k]]->traf(w,k);

        if(statki[mapa[w][k]]->czyZatopiony()) {
            cout<<"Statek zatopiony!"<<endl;
            lStatkow--;
        }
    }
    else
        mapa[w][k]=-2;
}

void Plansza::rysuj(){
    cout << ' ';
    for(int j=0; j<dajSzer(); j++)
        cout << ' ' << getChar(j);
    cout << endl;
    for(int i=0; i<dajWys(); i++){
        cout << i+1;
        for(int j=0; j<dajSzer(); j++)
            switch(mapa[i][j]) {
                case -2: cout << ' ' << 'X'; break;
                case -1: cout << ' ' << '_'; break;
                default: cout << ' '; statki[mapa[i][j]]->rysuj(i, j);
            }
        cout << endl;
    }
    cout << "____________________" << endl << endl;
}

int main() {
    Plansza pl(8, 8);
    pl.rysuj();

    int l = 0;
    char z = ' ';


    while(pl.dajLStatkow() > 0){
        cout << "Strzel (wiersz - liczba, kolumna - znak): ";
        cin >> l >> z;

        pl.strzel(l-1, getInt(z));
        pl.rysuj();

    }
    cout << "Wszystkie statki zatopione. Gra skończona." << endl;



    return 0;
}