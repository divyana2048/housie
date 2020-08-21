//
//  main.cpp
//  Housie Player
//
//  Created by Divyansh Agarwal on 25/04/20.
//  Copyright © 2020 Divyansh Agarwal. All rights reserved.
//

#include "board.cpp"
#include <iostream>

using namespace std;

int main() {
    print_intial_header();
    if (print_start_game() == 2) {
        print_ending();
        return 0;
    }
    vector <Prize> prizes;
    vector <Ticket> tickets;
    vector <bool> prizes_won;
    for (int i = 0; i < 12; i++) {
        prizes_won.push_back(false);
    }
    prizes = input_prizes();
    tickets = input_participants(prizes);
    Grid grid;
    
    while(!do_menu(tickets, prizes, prizes_won, grid)) {}
    print_results(tickets);
    print_ending();
    return 0;
}
