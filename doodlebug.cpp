#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;


class indicies {
    public:
        indicies();
        indicies(int a, int b);
        int getX();
        int getY();
        void setX(int a);
        void setY(int b);
    private:
        int x;
        int y;
};

indicies::indicies() {
    this->x = 0;
    this->y = 0;
}

indicies::indicies(int a, int b) {
    this->x = a;
    this->y = b;
}

int indicies::getX() {
    return x;
}

int indicies::getY() {
    return y;
}

void indicies::setX(int a) {
    x = a;
}

void indicies::setY(int b) {
    y = b;
}


class Organism {
    public:
        Organism();
        Organism(int x, int y, char role);
        int getPosX();
        int getPosY();
        char getChar();
        void setPosX(int i);
        void setPosY(int j);
        void setChar(char nu);
        void incAge();
        void setAge(int g);
        int getAge();
        void reset();
        void incHunger();
        void resetHunger();
        int getHunger();
        virtual void move();
        virtual void breed();

    private:
        char type;
        int posX;
        int posY;
        int age;
        int hunger;
};

Organism::Organism() {
    this->type = '-';
    this->posX = 0;
    this->posY = 0;
    this->age = 0;
    this->hunger = 0;
}

Organism::Organism(int x, int y, char role) {
    this->type = role;
    this->posX = x;
    this->posY = y;
    this->age = 0;
    this->hunger = 0;
}

int Organism::getPosX() {
    return posX;
}

int Organism::getPosY() {
    return posY;
}

char Organism::getChar() {
    return type;
}

void Organism::setPosX(int i) {
    posX = i;
}

void Organism::setPosY(int j) {
    posY = j;
}

void Organism::setChar(char nu) {
    type = nu;
}

void Organism::incAge() {
    age++;
}

void Organism::setAge(int g) {
    age = g;
}

int Organism::getAge() {
    return age;
}

void Organism::incHunger() {
    hunger++;
}

void Organism::resetHunger() {
    hunger = 0;
}

int Organism::getHunger() {
    return hunger;
}

void Organism::reset() {
    type = '-';
    age = 0;
}

void Organism::move() {
    // unused base function
}

void Organism::breed() {
    // unused base function
}

class ant: public Organism {
    public:
        ant();
        ant(int x, int y, int age);
        void move(Organism set[20][20], indicies &adex);
        void breed(Organism set[20][20], vector<indicies> &antindex, int &antnum);

    private:
        int x;
        int y;
        int age;
        char symbol;
};

ant::ant() {
    this->x = 0;
    this->y = 0;
    this->age = 0;
    this->symbol = 'o';
}

ant::ant(int x, int y, int age) {
    this->x = x;
    this->y = y;
    this->age = age;
    this->symbol = 'o';
}

void ant::move(Organism set[20][20], indicies &adex) {
    int direction_arr[] = {0, 1, 2, 3};
    std::vector<int> directions(direction_arr, direction_arr + sizeof(direction_arr) / sizeof(direction_arr[0]));
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));

    for (int random : directions) {

        bool dirfound = false;
        switch (random) {
            case 0:
                if (y - 1 >= 0 && set[x][y - 1].getChar() == '-') {
                    adex.setY(y - 1);
                    set[x][y - 1].setChar('o');
                    set[x][y - 1].setAge(set[x][y].getAge());
                    set[x][y].reset();
                    dirfound = true;
                    y--;
                }
                break;

            case 1:
                if (x + 1 < 20 && set[x + 1][y].getChar() == '-') {
                    adex.setX(x + 1);
                    set[x + 1][y].setChar('o');
                    set[x + 1][y].setAge(set[x][y].getAge());
                    set[x][y].reset();
                    dirfound = true;
                    x++;
                }
                break;

            case 2:
                if (x - 1 >= 0 && set[x - 1][y].getChar() == '-') {
                    adex.setX(x - 1);
                    set[x - 1][y].setChar('o');
                    set[x - 1][y].setAge(set[x][y].getAge());
                    set[x][y].reset();
                    dirfound = true;
                    x--;
                }
                break;

            case 3:
                if (y + 1 < 20 && set[x][y + 1].getChar() == '-') {
                    adex.setY(y + 1);
                    set[x][y + 1].setChar('o');
                    set[x][y + 1].setAge(set[x][y].getAge());
                    set[x][y].reset();
                    dirfound = true;
                    y++;
                }
                break;
        }
        if (dirfound) {
            break;
        }
    }
}

void ant::breed(Organism set[20][20], vector<indicies> &antindex, int &antnum) {
    if (age % 3 == 0) {
        int direction_arr[] = {0, 1, 2, 3};
        std::vector<int> directions(direction_arr, direction_arr + sizeof(direction_arr) / sizeof(direction_arr[0]));
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));

        for (int random : directions) {
            bool bfound = false;
            switch(random) {
                case 0:
                    if (y - 1 >= 0 && set[x][y - 1].getChar() == '-') {
                        set[x][y - 1].setChar('o');
                        antindex.push_back(indicies(x, y - 1));
                        antnum++;
                        bfound = true;
                    }
                    break;

                case 1:
                    if (x + 1 < 20 && set[x + 1][y].getChar() == '-') {
                        set[x + 1][y].setChar('o');
                        antindex.push_back(indicies(x + 1, y));
                        antnum++;
                        bfound = true;
                    }
                    break;

                case 2:
                    if (x - 1 >= 0 && set[x - 1][y].getChar() == '-') {
                        set[x - 1][y].setChar('o');
                        antindex.push_back(indicies(x - 1, y));
                        antnum++;
                        bfound = true;
                    }
                    break;

                case 3:
                    if (y + 1 < 20 && set[x][y + 1].getChar() == '-') {
                        set[x][y + 1].setChar('o');
                        antindex.push_back(indicies(x, y + 1));
                        antnum++;
                        bfound = true;
                    }
                    break;
            }
            if (bfound) {
                break;
            }
        }
    }
}

class doodlebug: public Organism {
    public:
        doodlebug();
        doodlebug(int x, int y, int age);
        void move(Organism set[20][20], indicies &dbugindex, vector<indicies> &antindex, int &antnum);
        void breed(Organism set[20][20], vector<indicies> &doodledex, int &doodlecount);
        void starve(Organism set[20][20], indicies &dbugindex, vector<indicies> &doodledex, int &doodlecount);

    private:
        int x;
        int y;
        int age;
        char symbol;
        bool hunger;
};

doodlebug::doodlebug() {
    this->x = 0;
    this->y = 0;
    this->age = 0;
    this->symbol = 'X';
}

doodlebug::doodlebug(int x, int y, int age) {
    this->x = x;
    this->y = y;
    this->age = age;
    this->symbol = 'X';
}

int getIndex(vector <indicies> vec, indicies xedni) {
    int i;
    for (i = 0; i < vec.size(); i++) {
        if (vec[i].getX() == xedni.getX() && vec[i].getY() == xedni.getY()) {
            return i;
        }
    }
    return -1;
}

void doodlebug::move(Organism set[20][20], indicies &dbugindex, vector<indicies> &antindex, int &antnum) {
    for (int random = 0; random < 4; random++) {
        bool found = false;
        int temp;
        switch(random) {
            case 0:
                if (y - 1 >= 0 && (set[x][y - 1].getChar() == '-' || set[x][y - 1].getChar() == 'o')) {
                    if (set[x][y - 1].getChar() == 'o') {
                        temp = getIndex(antindex, indicies(x, y - 1)); 
                        if (temp == -1) break; // added if statement to handle exceptions
						antindex.erase(antindex.begin() + temp);
                        set[x][y].resetHunger();
						antnum--;
					}

                    dbugindex.setY(y - 1);
                    set[x][y - 1].setChar('X');
                    set[x][y - 1].setAge(set[x][y].getAge());
                    set[x][y].reset();
                    y--;
                    found = true;
                }
                break;
            
            case 1:
                if (x + 1 < 20 && (set[x + 1][y].getChar() == '-' || set[x + 1][y].getChar() == 'o')) {
                    if (set[x + 1][y].getChar() == 'o') {
                        temp = getIndex(antindex, indicies(x, y + 1));
                        if (temp == -1) break; // added if statement to handle exceptions
						antindex.erase(antindex.begin() + temp);
                        set[x][y].resetHunger();
						antnum--;
                    }
                    dbugindex.setX(x + 1);
                    set[x + 1][y].setChar('X');
                    set[x + 1][y].setAge(set[x][y].getAge());
                    set[x][y].resetHunger();
                    set[x][y].reset();
                    x++;
					found = true;
                }
                break;
            
            case 2: 
                if (x - 1 >= 0 && (set[x - 1][y].getChar() == '-' || set[x - 1][y].getChar() == 'o')) {
					
                    if (set[x - 1][y].getChar() == 'o') {
                        temp = getIndex(antindex, indicies(x - 1, y));
                        if (temp == -1) break;
						antindex.erase(antindex.begin() + temp);
                        set[x][y].resetHunger();
						antnum--;
					}
					dbugindex.setX(x - 1);
                    set[x - 1][y].setChar('X');
                    set[x - 1][y].setAge(set[x][y].getAge());
                    set[x][y].reset();
                    x--;
					found = true;
				}
				break;

            case 3: 
                if (y + 1 < 20 && (set[x][y + 1].getChar() == '-' || set[x][y + 1].getChar() == 'o')) {
                    if (set[x][y + 1].getChar() == 'o') {
                        temp = getIndex(antindex, indicies(x + 1, y));
                        if (temp == -1) break;
						antindex.erase(antindex.begin() + temp);
						antnum--;
					}
					dbugindex.setY(y + 1);
                    set[x][y + 1].setChar('X');
                    set[x][y + 1].setAge(set[x][y].getAge());
                    set[x][y].reset();
                    y++;
					found = true;
				}
				break;

            }
        if (found) {
                break;
            }
    }
}

void doodlebug::breed(Organism set[20][20], vector<indicies> &doodledex, int &doodlecount) {
    if (age % 8 == 0) {
        for (int random = 0; random < 4; random++) {
            bool bfound = false;
            switch(random) {
                case 0:
                    if (y - 1 >= 0 && set[x][y - 1].getChar() == '-') {
                        set[x][y - 1].setChar('o');
                        doodledex.push_back(indicies(x, y - 1));
                        doodlecount++;
                        bfound = true;
                    }
                    break;

                case 1:
                    if (x + 1 < 20 && set[x + 1][y].getChar() == '-') {
                        set[x + 1][y].setChar('o');
                        doodledex.push_back(indicies(x + 1, y));
                        doodlecount++;
                        bfound = true;
                    }
                    break;

                case 2:
                    if (x - 1 >= 0 && set[x - 1][y].getChar() == '-') {
                        set[x - 1][y].setChar('o');
                        doodledex.push_back(indicies(x - 1, y));
                        doodlecount++;
                        bfound = true;
                    }
                    break;

                case 3:
                    if (y + 1 < 20 && set[x][y + 1].getChar() == '-') {
                        set[x][y + 1].setChar('o');
                        doodledex.push_back(indicies(x, y + 1));
                        doodlecount++;
                        bfound = true;
                    }
                    break;
            }
            if (bfound) {
                break;
            }
        }
    }
}

void doodlebug::starve(Organism set[20][20], indicies &dbugindex, vector<indicies> &doodledex, int &doodlecount) {
    
    if (age % 3 == 0 && set[x][y].getHunger() >= 3) {
		int x = dbugindex.getX();
		int y = dbugindex.getY();
        int temp = getIndex(doodledex, indicies(x, y));
		doodledex.erase(doodledex.begin() + temp);
		set[x][y].reset();
		doodlecount--;
	}

}

void timestep(Organism set[20][20], vector<indicies> &adicies, vector<indicies> &ddicies, int &antpop, int &doodpop) {
    // timestep code

    //move doodlebugs
    for (int i = 0; i < ddicies.size(); i++) {
        indicies &d = ddicies[i];
        int x = d.getX();
        int y = d.getY();
        set[x][y].incAge();
        set[x][y].incHunger();
        doodlebug temp(x, y, set[x][y].getAge());
        temp.move(set, d, adicies, antpop);
        temp.breed(set, ddicies, doodpop);
    }

    // ants move & breed
    for (int i = 0; i < adicies.size(); i++) {
        indicies &a = adicies[i];
        int x = a.getX();
        int y = a.getY();
        set[x][y].incAge();
        ant an = ant(x, y, set[x][y].getAge());
        an.move(set, a);
        an.breed(set, adicies, antpop);
    }

    //Doodlebug starve
    for (indicies &d : ddicies) {
        int x = d.getX();
        int y = d.getY();
        doodlebug temp(x, y, set[x][y].getAge());
        temp.starve(set, d, ddicies, doodpop);
    }
}

int main() {
    // Ant is o, doodlebug is X, neither is -
    srand(time(0)%100);
    vector <indicies> an;
    vector <indicies> dood;
    int antcount = 0;
    int dbugcount = 0;
    int tstep = 0;
    string test;
    
    Organism board[20][20];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            int random = rand() % 3;
            switch(random) {
                case 0:
                    if (antcount < 100) {
                        board[i][j] = Organism(i, j, 'o');
                        an.push_back(indicies(i, j));
                        antcount++;
                    }
                    else {
                        board[i][j] = Organism(i, j, '-');
                    }
                    break;
                case 1:
                    if (dbugcount < 5) {
                        board[i][j] = Organism(i, j, 'X');
                        dood.push_back(indicies(i, j));
                        dbugcount++;
                    }
                    else {
                        board[i][j] = Organism(i, j, '-');
                    }
                    break;
                case 2:
                    board[i][j] = Organism(i, j, '-');
                    break;
            }
        }
    }

    cout << endl;
    
    do {
        cout << "timestep #" << tstep << endl;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                cout << board[i][j].getChar() << " ";
            }
            cout << endl;
        }
        cout << "Press Enter to initiate time step" << endl;
        test = fgetc(stdin); // Always hit enter
        tstep++;
        // timestep goes here
        timestep(board, an, dood, antcount, dbugcount);
    } while (test == "\n");


    return 0;
}