//
//  board.cpp
//  Housie Player
//
//  Created by Divyansh Agarwal on 30/04/20.
//  Copyright © 2020 Divyansh Agarwal. All rights reserved.
//

#include "game.cpp"

class Grid {
public:
    Grid() {
        for (int i = 0; i < 100; i++) {
            if (i != 0) {
                numbers.push_back(i);
            }
            num[i] = i+1;
            num_marked[i-1] = false;
        }
        num_marked[99] = true;
    }
    
    void check_number(int n) {
        num_marked[n-1] = true;
        for (int i = 0; i < numbers.size(); i++) {
            if (numbers[i] == n) {
                numbers.erase(numbers.begin()+i);
                break;
            }
        }
    }
    
    void print_grid() {
        
        cout << "Printing current board..." << endl << endl;
        cout << bg_white << yellow << "|----|----|----|----|----|----|----|----|----|----|";
        cout << def << bg_def << endl;
        for (int i = 0; i < 10; i++) {
            cout << bg_white;
            for (int j = 0; j < 10; j++) {
                if (j == 0) {
                    cout << yellow << "| " << def;
                }
                if (num[i*10+j] == 100) {
                    cout << yellow << "   | " << def;
                }
                else {
                    if (num_marked[i*10+j]) {
                        cout << red;
                        if (num[i*10+j] < 10) {
                            cout << " ";
                        }
                        cout << num[i*10+j] << def << yellow << " | " << def;
                    }
                    else {
                        if (num[i*10+j] < 10) {
                            cout << " ";
                        }
                        cout << green << num[i*10+j] << yellow << " | " << def;
                    }
                }
            }
        cout << bg_def << endl << bg_white << yellow << "|----|----|----|----|----|----|----|----|----|----|" << def << bg_def << endl;
        }
        cout <<  bg_white << "                                                    " << bg_def << endl << endl;
    }
    
    vector <int> numbers;
    
    bool is_complete() {
        if ((int)numbers.size() == 0) {
            return true;
        }
        return false;
    }
    
private:
    int num[100];
    bool num_marked[100];
    
};

int call_out_number(vector <Ticket> &tickets, Grid &grid) {
    srand((int)time(NULL));
    int size = (int)grid.numbers.size();
    int n = grid.numbers[rand()%size];
    grid.check_number(n);
    for (int i = 0; i < tickets.size(); i++) {
        tickets[i].check_number(n);
    }
    return n;
}

int valid_ticket_number(int n, vector <Ticket> &tickets) {
    for (int i = 0; i < (int)tickets.size(); i++) {
        if (tickets[i].ticket_num == n) {
            return i;
        }
    }
    return -1;
}

bool do_menu(vector <Ticket> &tickets, vector <Prize> &prizes, vector <bool> &prizes_won, Grid &grid) {
    int input = print_menu();
    if (input == 2) {
        grid.print_grid();
        return false;
    }
    
    if (input == 3) {
        cout << "Please enter Ticket No." << endl;
        cout << yellow << "Enter -> " << def;
        int ticket_num;
        cin >> ticket_num;
        while (!cin.good() || (valid_ticket_number(ticket_num, tickets) == -1)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl;
            cout << red << "This is not a valid Ticket No. Please enter input again." << def << endl;
            cout << yellow << "Enter -> " << def;
            cin >> ticket_num;
        }
        cout << endl;
        tickets[valid_ticket_number(ticket_num, tickets)].print_ticket();
        cout << endl;
        return false;
    }
    
    if (input == 6) {
        cout << red << "Are you sure you want to end game? All changes will be lost." << endl;
        cout << "Please enter "  << yellow << 1 << red << " to confirm. Press any other number to resume game" << def << endl;
        cout << yellow << "Enter -> " << def;
        int endgame;
        cin >> endgame;
        while (!cin.good()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl;
            cout << red << "You can only enter a number. Please enter input again." << def << endl;
            cout << yellow << "Enter -> " << def;
            cin >> endgame;
        }
        cout << endl << endl;
        return (endgame == 1);
    }
    
    if (input == 5) {
        print_prizes_left(prizes);
        return false;
    }
    
    if (input == 4) {
        print_prizes(prizes);
        cout << "Pease enter prize number." << endl;
        cout << yellow << "Enter -> " << def;
        int prize;
        cin >> prize;
        while (!cin.good() && prize > 0 && prize < 13) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl;
            cout << red << "You can only enter a number number between 1 and 12." << def << endl;
            cout << yellow << "Enter -> " << def;
            cin >> prize;
        }
        cout << endl << endl;
        
        
        cout << "Please enter first winner's ticket number." << endl;
        cout << yellow << "Enter -> " << def;
        int winner1;
        cin >> winner1;
        while (!cin.good() || winner1 < 1 || winner1 > (int)tickets.size()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl;
            cout << red << "You can only enter a number number between 1 and " << (int)tickets.size() << def << endl;
            cout << yellow << "Enter -> " << def;
            cin >> winner1;
        }
        cout << endl << endl;
        
        cout << "Please enter second winner's ticket number. Enter 0 if no 2nd winner." << endl;
        cout << yellow << "Enter -> " << def;
        int winner2;
        cin >> winner2;
        while (!cin.good() || winner2 < 0 || winner2 > (int)tickets.size()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl;
            cout << red << "You can only enter a number number between 0 and " << (int)tickets.size() << def << endl;
            cout << yellow << "Enter -> " << def;
            cin >> winner2;
        }
        
        cout << endl << endl;
        add_winnings(prize, winner1, winner2, tickets, prizes);
        return false;
    }
    
    cout << "Calling out the next number..." << endl;
    cout << green << "The next number is " << yellow;
    cout << call_out_number(tickets, grid) << def << endl << endl;
    return false;
}

bool update_prizes_won(vector <Ticket> &tickets, vector <Prize> &prizes, vector <bool> &prizes_won, Grid &grid);

void print_results(vector <Ticket> &tickets) {
    for (int i = 0; i < (int)tickets.size(); i++) {
        cout << yellow << tickets[i].holder << def << " has won " << yellow << tickets[i].money_won << def << endl;
    }
    cout << endl;
}

