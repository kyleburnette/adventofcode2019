#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/* 
dec01-2.cpp:
Solution for Day 1, Part 2 of AoC 2019.
*/

int find_fuel(int mass){
    return mass / 3 - 2;
}

int find_total_fuel(int mass){
    int fuel = find_fuel(mass);

    if(fuel >= 0){
        return fuel + find_total_fuel(fuel);
    }
    else{
        return 0;
    }
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
        total += find_total_fuel(value);
    }

    std::cout << total;

    return 0;
}