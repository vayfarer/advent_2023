// Michael Chen
// Advent of Code 2023 Day 7 part 1 and 2
// 12/24/2023

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>
#include <map>
#include <ctime>
#include <cctype>
#include <algorithm>    // std::sort
#include <forward_list>
using namespace std;

int card_to_i (char c){
    map<char, int> faces;
    faces ['A'] = 14;
    faces ['K'] = 13;
    faces ['Q'] = 12;
    faces ['J'] = 11;
    faces ['T'] = 10;

    if (isdigit(c)){
        return c - '0';
    } else {
        return faces[c];
    }
}

int card_to_i_p2 (char c){
    map<char, int> faces;
    faces ['A'] = 14;
    faces ['K'] = 13;
    faces ['Q'] = 12;
    faces ['J'] = 1;
    faces ['T'] = 10;

    if (isdigit(c)){
        return c - '0';
    } else {
        return faces[c];
    }
}

int rank_hand (vector<int> hand){
    int high = 0;
    int num_kind1 = 0, num_kind2 = 0;
    map <int, int> h_map;

    for (int &n: hand){
        if (n > high) {high = n;}
        if (h_map.count(n)){h_map[n]++;} else {h_map[n] = 1;}
    }

    for(const auto& card : h_map){
        if (card.second > num_kind1){
            num_kind2 = num_kind1;
            num_kind1 = card.second;
        } else if (card.second > num_kind2) {
            num_kind2 = card.second;
        }
    }

    switch (num_kind1){
        case 5:
            return 6;
        case 4:
            return 5;
        case 3:
            if (num_kind2 == 2){return 4;} else {return 3;}
        case 2:
            if (num_kind2 == 2){return 2;} else {return 1;}
        case 1: 
            return 0;
        default:
            cout << "ERROR!!";
            return 0;            // how did you get here??
    }
}

int rank_hand_p2 (vector<int> hand){
    int high = 0;
    int num_kind1 = 0, num_kind2 = 0;
    map <int, int> h_map;

    for (int &n: hand){
        if (n > high) {high = n;}
        if (h_map.count(n)){h_map[n]++;} else {h_map[n] = 1;}
    }

    for(const auto& card : h_map){
        if (card.second > num_kind1){
            num_kind2 = num_kind1;
            num_kind1 = card.second;
        } else if (card.second > num_kind2) {
            num_kind2 = card.second;
        }
    }

    if (h_map.count(1)){
        // has at least one joker
        if (h_map[1] <= num_kind2){
            // jokers are at most second most common. add to most common. 
            num_kind1 += h_map[1];
        } else {num_kind1 += num_kind2;} // else jokers are most common.
    }

    switch (num_kind1){
        case 5:
            return 6;
        case 4:
            return 5;
        case 3:
            if (num_kind2 == 2){return 4;} else {return 3;}
        case 2:
            if (num_kind2 == 2){return 2;} else {return 1;}
        case 1: 
            return 0;
        default:
            cout << num_kind1 << ' ';
            cout << "ERROR!!\n";
            return 0;            // how did you get here??
    }
}

bool h_less_than (pair<string, int> hand1, pair<string, int> hand2) {
    // true if hand1 is greater than hand2.

    string h1 = hand1.first, h2 = hand2.first;
    vector <int> h1_nums, h2_nums;
    bool order_rank, ranked = false;

    for (int i = 0; i <5; i++){
        char &ch1 = h1[i], &ch2 = h2[i];
        int h1_num = card_to_i(ch1), h2_num = card_to_i(ch2);
        h1_nums.push_back(h1_num); h2_nums.push_back(h2_num);
        if (!ranked){
            if (h1_num == h2_num){continue;}
            order_rank = (h1_num > h2_num)? false : true;
            ranked = true;
        }
    }

    int h1_rank = rank_hand(h1_nums), h2_rank = rank_hand(h2_nums);

    if (h1_rank > h2_rank){
        return false;
    }
    
    if (h1_rank == h2_rank) {
        return order_rank;
    }

    return true;
}

bool h_less_than_p2 (pair<string, int> hand1, pair<string, int> hand2) {
    // true if hand1 is greater than hand2.

    string h1 = hand1.first, h2 = hand2.first;
    vector <int> h1_nums, h2_nums;
    bool order_rank, ranked = false;

    for (int i = 0; i <5; i++){
        char &ch1 = h1[i], &ch2 = h2[i];
        int h1_num = card_to_i_p2(ch1), h2_num = card_to_i_p2(ch2);
        h1_nums.push_back(h1_num); h2_nums.push_back(h2_num);
        if (!ranked){
            if (h1_num == h2_num){continue;}
            order_rank = (h1_num > h2_num)? false : true;
            ranked = true;
        }
    }

    int h1_rank = rank_hand_p2(h1_nums), h2_rank = rank_hand_p2(h2_nums);

    if (h1_rank > h2_rank){
        return false;
    }
    
    if (h1_rank == h2_rank) {
        return order_rank;
    }

    return true;
}

int main () {

    clock_t timer = clock();

    string line;
    ifstream read_file;
    int p1 = 0, p2 = 0;
    vector<pair<string, int>> hands;
    string temp_nums = "";

    read_file.open ("input");
    if (read_file.is_open()){
        //get times
        regex e ("(\\w+) (\\d+)");
        smatch hand;
        while(getline(read_file, line)){
            regex_match(line, hand, e);
            hands.push_back(make_pair(hand.str(1), stoi(hand.str(2))));
        }
    }    

    sort(hands.begin(), hands.end(), h_less_than);
    for (int i = 0; i < hands.size(); i++){
        p1 += (i+1) * hands[i].second;
    }

    sort(hands.begin(), hands.end(), h_less_than_p2);
    for (int i = 0; i < hands.size(); i++){
        p2 += (i+1) * hands[i].second;
    }

    timer = clock() - timer;
    cout << "runtime: " << (float)timer/CLOCKS_PER_SEC * 1000 << "ms \n";
    
    cout << "Day 7 part 1: " << p1 << '\n';
    cout << "Day 7 part 2: " << p2 << '\n';

    return 0;
}