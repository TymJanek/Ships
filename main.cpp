#include <iostream>
using namespace std;

class Ship {
public:
    virtual void draw(int x, int y){}
    virtual void hit(int x, int y){};
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
        if(deck[y - this -> y] == '_'){
            hits++;
        }
        deck[y - this->y] = 'T';
    }
    virtual bool isSunken(){
        return hits == size;
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
        if(deck[y - this -> y] == '_'){
            hits++;
        }
        deck[y - this->y] = 'T';
    }
    virtual bool isSunken(){
        return hits == size;
    }
};

class ThreeMasted : public Ship {
private:
    int x, y, size = 3, hits = 0;
    char deck[3];
public:
    ThreeMasted(int x, int y) : x(x), y(y) {
        deck[0] = '_';
        deck[1] = '_';
        deck[2] = '_';
    }
    virtual void draw(int x, int y){
        cout << deck[y - this->y];
    }
    virtual void hit(int x, int y){
        if(deck[y - this -> y] == '_'){
            hits++;
        }
        deck[y - this->y] = 'T';
    }
    virtual bool isSunken(){
        return hits == size;
    }
};

class FourMasted : public Ship {
private:
    int x, y, size = 4, hits = 0;
    char deck[4];
public:
    FourMasted(int x, int y) : x(x), y(y) {
        deck[0] = '_';
        deck[1] = '_';
        deck[2] = '_';
        deck[3] = '_';
    }
    virtual void draw(int x, int y){
        cout << deck[y - this->y];
    }
    virtual void hit(int x, int y){
        if(deck[y - this -> y] == '_'){
            hits++;
        }
        deck[y - this->y] = 'T';
    }
    virtual bool isSunken(){
        return hits == size;
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
    int ** map; //0 - empty, -1 - miss, x - ship number.
public:
    Board(int height, int width);
    ~Board();
    int getHeight();
    int getWidth();
    bool emptyField(int x, int y);
    void addShip(int x, int y, int w);
    int getNumberOfShips();
    void shoot(int w, int k);
    void draw();
};

Board::Board(int height, int width){
    this->height = height;
    this->width = width;
    numberOfShips = 0;

    map = new int*[height];
    for(int i=0; i < width; i++)
        map[i] = new int[width];

    for(int i=0; i < height; i++)
        for(int j=0; j < width; j++)
            map[i][j]=-1;


    addShip(1, 0, 1);   // 2a
    addShip(2, 2, 2);   // 3c & 3d
    addShip(6, 2, 3);   // 7c & 7d & 7e
    addShip(4, 4, 4);   // 5e & 5f & 5g & 5h

}

Board::~Board(){
    for(int i=0; i < getHeight(); i++)
        delete [] map[i];
    delete [] map;
    for(int i=0; i < numberOfShips; i++)
        delete ships[i];
}

int Board::getHeight(){
    return height;
}

int Board::getWidth(){
    return width;
}

int Board::getNumberOfShips() {
    return numberOfShips;
}

bool Board::emptyField(int x, int y){
    if(x < getHeight() && x > 0 && y < getWidth() && y > 0){
        bool result = true;
        for(int i=x-1; i<x+2; i++)
            for(int j=y-1; j<y+2; j++)
                if(map[i][j] != -1)
                    result=false;
        return result;
    }
    return false;
}

void Board::addShip(int x, int y, int w){
    bool isEmpty=true;
    for(int i=0; i<w; i++)
        if(!emptyField(x, y + 1))
            isEmpty=false;
    if(isEmpty){
        for(int i=0; i<w; i++)
            map[x][y + i] = numberOfShips;
        if(w == 1){
            Ship *st = new OneMasted(x, y);
            ships[numberOfShips++] = st;
        }
        else if(w == 2){
            Ship *st = new TwoMasted(x, y);
            ships[numberOfShips++] = st;
        }
        else if(w == 3){
            Ship *st = new ThreeMasted(x, y);
            ships[numberOfShips++] = st;
        }
        else if(w == 4){
            Ship *st = new FourMasted(x, y);
            ships[numberOfShips++] = st;
        }

    }
    else
        cout << endl << "Incorrect ship position" << endl << endl;
}

void Board::shoot(int w, int k){
    if(map[w][k] >= 0) {
        ships[map[w][k]]->hit(w, k);

        if(ships[map[w][k]]->isSunken()) {
            cout<<"Ship sunken!"<<endl;
            numberOfShips--;
        }
    }
    else
        map[w][k]=-2;
}

void Board::draw(){
    cout << ' ';
    for(int j=0; j < getWidth(); j++)
        cout << ' ' << getChar(j);
    cout << endl;
    for(int i=0; i < getHeight(); i++){
        cout << i+1;
        for(int j=0; j < getWidth(); j++)
            switch(map[i][j]) {
                case -2: cout << ' ' << 'X'; break;
                case -1: cout << ' ' << '_'; break;
                default: cout << ' ';
                    ships[map[i][j]]->draw(i, j);
            }
        cout << endl;
    }
    cout << "____________________" << endl << endl;
}

int main() {
    Board pl(8, 8);
    pl.draw();

    int l = 0;
    char z = ' ';


    while(pl.getNumberOfShips() > 0){
        cout << "Shoot (row - number, column - character): ";
        cin >> l >> z;

        pl.shoot(l - 1, getInt(z));
        pl.draw();

    }
    cout << "All ships are sunken. Game over." << endl;



    return 0;
}