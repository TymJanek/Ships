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

class Ship {
public:
    virtual void draw(int x, int y){}
    virtual void hit(int x, int y){}
    virtual bool isSunken(){};
};

class OneMasted : public Ship {
private:
    int x, y, size = 1, hits = 0;
    char deck[1];
public:
    OneMasted(int x, int y) : x(x), y(y) {
        deck[0] = '_';
    }
    virtual void draw(int x, int y){
        cout << deck[y - this->y];
    }
    virtual void hit(int x, int y){
        if(deck[y - this -> y == '_']){
            hits++;
        }
        deck[y - this -> y] = 'T';
    }
    virtual bool isSunken(){
        if(hits < size){
            return false;
        }
        else{
            return true;
        }
    }
};


class TwoMasted : public Ship {
private:
    int x, y, size = 2, hits = 0;
    char deck[2];
public:
    TwoMasted(int x, int y) : x(x), y(y) {
        deck[0] = '_';
        deck[1] = '_';
    }
    virtual void draw(int x, int y){
        cout << deck[y - this->y];
    }
    virtual void hit(int x, int y){
        if(deck[y - this -> y == '_']){
            hits++;
        }
        deck[y - this -> y] = 'T';
    }
    virtual bool isSunken(){
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


class Board {
private:
    int height, width;
    int numberOfShips;
    Ship * ships[10];
    int ** maps; //0 - wolne pole, -1 - pudło, x - numer statku.
public:
    Board(int height, int width);
    ~Board();
    int giveHeight();
    int giveWidth();
    bool emptySpace(int x, int y);
    void addShip(int x, int y, int w);
    void addOneMastedShip(int x, int y, int z);
    int giveNumberOfShips();
    void shoot(int w, int k);
    void draw();
};

Board::Board(int height, int width){
    this->height = height;
    this->width = width;
    numberOfShips = 0;

    maps = new int*[height];
    for(int i=0; i < width; i++)
        maps[i] = new int[width];

    for(int i=0; i < height; i++)
        for(int j=0; j < width; j++)
            maps[i][j]=-1;

    addShip(2, 2, 1); //3 c
    addShip(3, 3, 2); //4 d Kolizja
    addShip(6, 3, 2); //7 d
    addShip(4, 1, 2); //5 b

}

Board::~Board(){
    for(int i=0; i < giveHeight(); i++)
        delete [] maps[i];
    delete [] maps;
    for(int i=0; i < numberOfShips; i++)
        delete ships[i];
}

int Board::giveHeight(){
    return height;
}

int Board::giveWidth(){
    return width;
}

bool Board::emptySpace(int x, int y){
    if(x < giveHeight() && x > 0 && y < giveWidth() && y > 0){
        bool result = true;
        for(int i=x-1; i<x+2; i++)
            for(int j=y-1; j<y+2; j++)
                if(maps[i][j] != -1)
                    result=false;
        return result;
    }
    return false;
}

void Board::addShip(int x, int y, int w){
    bool empty=true;
    for(int i=0; i<w; i++)
        if(!emptySpace(x, y + 1))
            empty=false;
    if(empty){
        for(int i=0; i<w; i++)
            maps[x][y + i] = numberOfShips;
        if(w == 1){
            Ship *st = new OneMasted(x, y);
            ships[numberOfShips++] = st;
        }
        else if(w == 2){
            Ship *st = new TwoMasted(x, y);
            ships[numberOfShips++] = st;
        }

    }
    else
        cout << endl << "Incorrect ship position" << endl << endl;
}


void Board::shoot(int w, int k){
    if(maps[w][k] >= 0)
        ships[maps[w][k]]->hit(w, k);

    if(ships[maps[w][k]] -> isSunken()){
        cout << "Ship sunken" << endl;
        //numberOfShips--;
    }
    else
        maps[w][k]=-2;
}

void Board::draw(){
    cout << ' ';
    for(int j=0; j < giveWidth(); j++)
        cout << ' ' << getChar(j);
    cout << endl;
    for(int i=0; i < giveHeight(); i++){
        cout << i+1;
        for(int j=0; j < giveWidth(); j++)
            switch(maps[i][j]) {
                case -2: cout << ' ' << 'X'; break;
                case -1: cout << ' ' << '_'; break;
                default: cout << ' ';
                    ships[maps[i][j]]->draw(i, j);
            }
        cout << endl;
    }
    cout << "____________________" << endl << endl;
}

int main() {
    Board pl(8, 8);
    pl.draw();

    int l;
    char z;

    for(int i=0; i<20; i++){
        cout << "Shoot (row - number, column - sign): ";
        cin >> l >> z;

        pl.shoot(l - 1, getInt(z));
        pl.draw();
    }



    return 0;
}
