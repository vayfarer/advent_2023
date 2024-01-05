// Michael Chen
// Advent of Code 2023 Day 11 part 1 and 2
// 1/4/2024

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Galaxy{
    public:
        int x, y;

        Galaxy(int row, int col){
            x = col;
            y = row;
        }

        int manhattan(Galaxy other){
            return abs(other.x - x) + abs(other.y - y);
        }
};

int main () {
    clock_t timer = clock();
    string line;
    ifstream read_file;
    int p1 = 0, p2 = 0;
    vector <string> image;

    read_file.open ("input");
    if (read_file.is_open()){
        while(getline(read_file, line)){
            image.push_back(line);


        }
        read_file.close();
    }    

    // expand rows
    int rows_added = 0;
    int image_original_size = image.size();
    for (int i = 0; i < image_original_size; i++){
        regex e ("(#)");
        smatch sm;

        if (!regex_search(image[i+rows_added], sm, e)){
            image.insert(image.begin() + i + rows_added, image[i+rows_added]);
            rows_added ++;
        }
    }

    // expand columns
    int columns_added = 0;
    image_original_size = image[0].size();
    for (int i = 0; i < image_original_size; i++){
        bool no_galaxy = true;
        int j = 0;
        while (no_galaxy && j < image.size()){
            if (image[j][i+columns_added] == '#'){
                no_galaxy = false;
            }
            j++;
        }
        if (no_galaxy){
            for (string &s: image){
                s.insert(i + columns_added, "."); 
            }
            columns_added++;               
        }
    }

    // locate all galaxies
    vector <Galaxy> galaxies;
    for (int i = 0; i < image.size(); i++){
        string row = image[i];
        regex e ("(#)");
        smatch sm;
        int offset = 0;
        while(regex_search(row, sm, e)){
            Galaxy galobj(i, sm.position() + offset);
            offset += sm.position() + 1;
            galaxies.push_back(galobj);
            row = sm.suffix().str();
        }
    }

    // calculate distance between all galaxies
    for (int i = 0; i < galaxies.size(); i++){
        for (int j = i; j < galaxies.size(); j++){
            p1 += galaxies[i].manhattan(galaxies[j]);
        }
    }

    timer = clock() - timer;
    cout << "runtime: " << (float)timer/CLOCKS_PER_SEC * 1000 << "ms \n";
    
    cout << "Day 10 part 1: " << p1 << '\n';
    cout << "Day 10 part 2: " << p2 << '\n';

    return 0;
}