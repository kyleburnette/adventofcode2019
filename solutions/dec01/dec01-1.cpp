#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/* 
dec01-1.cpp:
Solution for Day 1, Part 1 of AoC 2019.
*/

int find_fuel(int mass){
    return mass / 3 - 2;
}

std::vector<int> read_input(std::string filename){
    std::vector<int> values;
    std::ifstream file("input.txt");
    std::string value;

    while (std::getline(file, value)){
        values.push_back(stoi(value));
    }

    file.close();

    return values;
}

int main(){
    int total = 0;

    std::vector<int> values = read_input("input.txt");
    
    for (int value : values){
        total += find_fuel(value);
    }

    std::cout << total << std::endl;

    return 0;
}