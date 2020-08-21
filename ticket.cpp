//
//  ticket.cpp
//  Housie Player
//
//  Created by Divyansh Agarwal on 01/05/20.
//  Copyright © 2020 Divyansh Agarwal. All rights reserved.
//

#include "prizes.cpp"

class Ticket {
public:
    Ticket(string holder_in, int ticket_num_in) {
        money_won = 0;
        holder = holder_in;
        ticket_num = ticket_num_in;
        for (int i = 0; i < (int)prizes_won.size(); i++) {
            prizes_won.push_back(false);
        }
        
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                num[i][j] = 0;
            }
        }
        
        vector <int> v = generate_ticket();
        bool inv = (v[2] < 10);
        int count = 0;
        for (int i = 0; i < 10; i++) {
            if ((inv && i%2 == 0) || (!inv && i%2 == 1)) {
                num[0][i] = v[count];
                count++;
                num[2][i] = v[count];
                count++;
                num[4][i] = v[count];
                count++;
            }
            else {
                num[1][i] = v[count];
                count++;
                num[3][i] = v[count];
                count++;
            }
        }
        
        
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                if (num[i][j] == 0) {
                    num_marked[i][j] = -1;
                }
                else {
                    num_marked[i][j] = 0;
                }
            }
        }
    }
    
    void check_number(int n) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                if (num[i][j] == n) {
                    num_marked[i][j] = 1;
                    return;
                }
            }
        }
    }
    
    vector <int> generate_ticket() {
        srand((int)time(NULL));
//        srand(rand()%1000);
        bool inv = (rand()%100)%2;
        vector <int> v;
        vector <int> full;
        for (int i = 1; i < 100; i++) {
            full.push_back(i);
        }
        
        for (int i = 0; i < 10; i++) {
            int rand1 = 10*i+(rand()%10);
            while (rand1 == 0) {
                rand1 = 10*i+(rand()%10);
            }
            int rand2 = 10*i+(rand()%10);
            while (rand2 == rand1 || rand2 == 0) {
                rand2 = 10*i+(rand()%10);
            }
            v.push_back(rand1);
            v.push_back(rand2);
            
            if ((inv && i%2 == 0) || (!inv && i%2 == 1)) {
                int rand3 = 10*i+(rand()%10);
                while (rand3 == rand1 || rand3 == 0 || rand3 == rand2) {
                    rand3 = 10*i+(rand()%10);
                }
                v.push_back(rand3);
            }
        }
        sort(v.begin(), v.end());
        return v;
    }
    
    void print_ticket() {
        
        cout << endl << endl;
        int size = (int)to_string(ticket_num).length() + (int)holder.length() + 32;
        cout << bg_white;
        for (int i = 0; i < 52; i++) {
            cout << " ";
        }
        cout << bg_def << endl;
        cout << bg_white << black << "  Ticket Number: " << blue << ticket_num;
        cout << black << "  Player Name: " << blue << holder;
        for (int i = size; i < 51; i++) {
            cout << " ";
        }
        cout << def << bg_def << endl;
        cout << bg_white;
        for (int i = 0; i < 52; i++) {
            cout << " ";
        }
        cout << bg_def << endl;
        
        cout << bg_white << yellow << "|----|----|----|----|----|----|----|----|----|----|";
        cout << def << bg_def << endl;
        for (int i = 0; i < 5; i++) {
            cout << bg_white;
            for (int j = 0; j < 10; j++) {
                if (j == 0) {
                    cout << yellow << "| " << def;
                }
                if (num[i][j] == 0) {
                    cout << yellow << "   | " << def;
                }
                else {
                    if (num_marked[i][j]) {
                        cout << red;
                        if (num[i][j] < 10) {
                            cout << " ";
                        }
                        cout << num[i][j] << def << yellow << " | " << def;
                    }
                    else {
                        if (num[i][j] < 10) {
                            cout << " ";
                        }
                        cout << black << num[i][j] << yellow << " | " << def;
                    }
                }
            }
            cout << bg_def << endl << bg_white << yellow << "|----|----|----|----|----|----|----|----|----|----|" << def << bg_def << endl;
        }
        cout <<  bg_white << "                                                    ";
        cout << bg_def << endl << endl;
    }

    
    string holder;
    int ticket_num;
    int money_won;
    vector <bool> prizes_won;
    
private:
    int num[5][10];
    int num_marked[5][10];
};
