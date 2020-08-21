//
//  prizes.cpp
//  Housie Player
//
//  Created by Divyansh Agarwal on 25/04/20.
//  Copyright © 2020 Divyansh Agarwal. All rights reserved.
//

#include <iostream>
#include <vector>
#include <ostream>


// for color
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW   = 33,
        FG_BLUE     = 34,
        FG_BLACK    = 30,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49,
        BG_WHITE    = 47,
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

Color::Modifier red(Color::FG_RED);
Color::Modifier def(Color::FG_DEFAULT);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier black(Color::FG_BLACK);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier bg_white(Color::BG_WHITE);
Color::Modifier bg_def(Color::BG_DEFAULT);

// the prize class starts here
using namespace std;

class Prize {
public:
    Prize() {
        value = 0;
        complete = false;
        winner = "default";
    }
    
    Prize(string name_in) {
        name = name_in;
        value = 0;
        complete = false;
        winner = "default";
    }
    
    void set_value(int val) {
        value = val;
    }
    
    string name;
    string winner;
    bool complete;
    int value;
    
};

vector<Prize> set_prize_names() {
    vector <Prize> prizes(12);
    prizes[0] = Prize("First Line");
    prizes[1] = Prize("Second Line");
    prizes[2] = Prize("Third Line");
    prizes[3] = Prize("Fourth Line");
    prizes[4] = Prize("Fifth Line");
    
    prizes[5] = Prize("First House");
    prizes[6] = Prize("Second House");
    prizes[7] = Prize("Third House");
    
    prizes[8] = Prize("4 Corners");
    prizes[9] = Prize("Early 5");
    prizes[10] = Prize("Big X");
    prizes[11] = Prize("Half-Century");
    
    return prizes;
}

vector <Prize> input_prize_values(vector <Prize> &prizes) {
    int sum = 0;
    cout  << endl << "First, enter the prize for " << yellow << "Each Line" << def << ": ";
    int value;
    cin >> value;
    while (!cin.good() || value < 50 || value > 1000 || value %50 != 0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << endl;
        cout << red << "The prize has to be between 50 and 1000." << endl;
        cout << "It has to be a multiple of 50. Please try again." << def << endl;
        cout << "Enter -> ";
        cin >> value;
    }
    for (int i = 0; i < 5; i++) {
        prizes[i].set_value(value);
        sum += value;
    }
    for (int i = 5; i < 12; i++) {
        cout << "Enter the value of prize - " << yellow << prizes[i].name << def << ": ";
        int val;
        cin >> val;
        while (!cin.good() || val < 50 || val > 1000) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl;
            cout << red << "The prize has to be between 50 and 1000. Please enter again." << def << endl;
            cout << "Enter -> ";
            cin >> val;
        }
        prizes[i].set_value(val);
        sum += val;
    }
    cout << green << endl << "All prizes and values have been set." << endl << def;
    cout << "The total prize money adds up to " << yellow << sum << def << "." << endl;
    return prizes;
}

void print_prizes(vector <Prize> &prizes) {
    cout << green << "There are 12 prizes. They are as follows:" << def << endl << endl;
    for (int i = 0; i < 12; i++) {
        cout << "Prize " << i+1 << ": " << yellow << prizes[i].name << def << endl;
    }
    cout << endl;
}

void print_prizes_left(vector <Prize> &prizes) {
    cout << green << "The prizes remaining are:" << def << endl << endl;
    for (int i = 0; i < 12; i++) {
        if (!prizes[i].complete) {
        cout << "Prize " << i+1 << ": " << yellow << prizes[i].name << def << endl;
        }
    }
    cout << endl;
}







