//
//  game.cpp
//  Housie Player
//
//  Created by Divyansh Agarwal on 29/04/20.
//  Copyright © 2020 Divyansh Agarwal. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "ticket.cpp"

using namespace std;

void print_intial_header() {
    cout << endl << endl;
    cout << "----------------------------------------" << endl;
    cout << "      Welcome to Divyansh's Housie!     " << endl;
    cout << "----------------------------------------" << endl << endl << def;
}

int print_start_game() {
    cout << green << "Are you ready to start the game?" << def << endl << endl;
    cout << yellow << "(1)" << def << " Yes" << endl;
    cout << yellow << "(2)" << def << " No" << endl;
    int input;
    cout << yellow << "Enter -> " << def;
    cin >> input;
    while (!cin.good() || (input != 1 && input != 2)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << endl;
        cout << red << "You can only enter 1 or 2. Please enter input again." << def << endl;
        cout << yellow << "Enter -> " << def;
        cin >> input;
    }
    cout << endl;
    return input;
}

void print_ending() {
    cout << green << "Thank you for playing Divyansh's Housie!" << endl;
    cout << "You can give me feedback at +91 9007757799!" << def << endl << endl;
}

bool check_name(string name, vector <Ticket> &v) {
    for (int i = 0; i < v.size(); i++) {
        if (name == v[i].holder) {
            return false;
        }
    }
    return true;
}

vector <Prize> input_prizes() {
    vector <Prize> v;
    v = set_prize_names();
    print_prizes(v);
    cout << green << "Please enter the prize money for each of these prizes." << def << endl;
    v = input_prize_values(v);
    return v;
}

vector <Ticket> input_participants(vector <Prize> &prizes) {
    vector <Ticket> v;
    cout << green << endl << "Please enter the number of players." << endl << def;
    int num_players;
    cout << yellow << "Enter -> " << def;
    cin >> num_players;
    while (!cin.good() || num_players < 0 || num_players > 30) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << endl;
        cout << red << "You can only enter a number between 1 and 30. Please enter input again." << def << endl;
        cout << yellow << "Enter -> " << def;
        cin >> num_players;
    }
    cout << endl << endl;
    for (int i = 0; i < num_players; i++) {
        cout << "Please enter the name of " << yellow << "Player " << i+1 << def << ": ";
        string name;
        cin >> name;
        while (!cin.good() || (!check_name(name, v))) {
            cin.clear();
            cin.ignore();
            cout << endl << red << "Please enter a valid name. Try again." << def << endl;
            cout << "Please enter the name of " << yellow << "Player " << i+1 << def << ": ";
            cin >> name;
        }
        v.push_back(Ticket(name, i+1));
    }
    cout << green << endl << "All names have been entered successfully." << def << endl << endl;
    for (int i = 0; i < (int)v.size(); i++) {
        v[i].print_ticket();
        cout << endl << endl << endl;
    }
    
    cout << yellow << num_players << green << " tickets have been randomly generated." << endl;
    cout << "Please send these tickets to the respective players." << endl << endl << def;
    return v;
}

int print_menu() {
    cout << yellow << "(1)" << def << " Call out next number" << endl;
    cout << yellow << "(2)" << def << " Print current board" << endl;
    cout << yellow << "(3)" << def << " Print any player's ticket" << endl;
    cout << yellow << "(4)" << def << " Declare winner for a prize" << endl;
    cout << yellow << "(5)" << def << " Print remaining prizes" << endl;
    cout << yellow << "(6)" << def << " End game and print results" << endl;
    cout << endl << yellow << "Enter -> " << def;
    int input;
    cin >> input;
    while (!cin.good() || (input < 1 || input > 6)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << endl;
        cout << red << "You can only enter 1-6. Please enter input again." << def << endl;
        cout << yellow << "Enter -> " << def;
        cin >> input;
    }
    cout << endl << endl;
    return input;
}

void add_winnings(int prize_index, int winner1, int winner2, vector <Ticket> &tickets, vector <Prize> &prizes) {
    bool one_winner = false;
    if (winner2 == 0) {one_winner = true;}
    if (one_winner) {
        tickets[winner1-1].money_won += prizes[prize_index-1].value;
        cout << green << "Winner for " << yellow << prizes[prize_index-1].name << green << " has been declared as " << yellow << tickets[winner1-1].holder << def << endl << endl;
    }
    else {
        tickets[winner1-1].money_won += prizes[prize_index-1].value/2;
        cout << green << "Winner 1 for " << yellow << prizes[prize_index-1].name << green << " has been declared as " << yellow << tickets[winner1-1].holder << def << endl << endl;
        tickets[winner2-1].money_won += prizes[prize_index-1].value/2;
        cout << green << "Winner 2 for " << yellow << prizes[prize_index-1].name << green << " has been declared as " << yellow << tickets[winner2-1].holder << def << endl << endl;
    }
    
    cout << "Enter " << yellow << 1 << def << " to confirm, or enter " << yellow << 2  << def <<" to discard." << endl;
    cout << yellow << "Enter -> " << def;
    int input;
    cin >> input;
    while (!cin.good() || input > 2 || input < 1) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << endl;
        cout << red << "You can only enter 1 or 2." << def << endl;
        cout << yellow << "Enter -> " << def;
        cin >> input;
    }
    prizes[prize_index-1].complete = true;
    cout << endl;
    if (input == 2) {
        prizes[prize_index-1].complete = false;
        if (one_winner) {
            tickets[winner1-1].money_won -= prizes[prize_index-1].value;
        }
        else {
            tickets[winner1-1].money_won -= prizes[prize_index-1].value/2;
            tickets[winner2-1].money_won -= prizes[prize_index-1].value/2;
        }
        cout << endl << red << "Winners have been removed." << def << endl << endl;
    }
}







