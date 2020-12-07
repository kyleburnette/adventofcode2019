#include <iostream>
#include <fstream>
#include <vector>

/* 
dec02-1.cpp:
Solution for Day 2, Part 1 of AoC 2019.

Notes:
I'd like to beautify the output of the vector in the future (padding between elements is 
especially needed).
*/

std::vector<int> read_input(std::string filename){
    std::vector<int> values;
    std::ifstream file("input.txt");

    for (int i; file >> i;) {
        values.push_back(i);    
        if (file.peek() == ',')
            file.ignore();
    }
    
    file.close();

    return values;
}

void process_intcode(std::vector<int>& intcode, bool debug){
    int curr = 0;
    const int ADD = 1;
    const int MULTIPLY = 2;
    const int HALT = 99;

    while (intcode[curr] != HALT){
        if (debug){
            std::cout << "opcode: " << intcode[curr] << " | Position: " << intcode[curr + 1] << "(" << intcode[intcode[curr + 1]] 
            << ") Position: " << intcode[curr + 2] << "(" << intcode[intcode[curr + 2]] << ") Store Position: " << intcode[curr + 3] << std::endl;
        }
        switch(intcode[curr]){
            case ADD:
                intcode[intcode[curr + 3]] = intcode[intcode[curr + 1]] + intcode[intcode[curr + 2]]; 
                break;
            case MULTIPLY:
                intcode[intcode[curr + 3]] = intcode[intcode[curr + 1]] * intcode[intcode[curr + 2]];
                break;
            default:
                break;     
        }
        curr += 4;
    }
}

void reset_intcode(std::vector<int>& intcode){
    intcode[1] = 12;
    intcode[2] = 2;
}

template <typename T>
void print_vector(const std::vector<T>& vec, int columns){
    int column_tracker = 0;
    for (auto value : vec){ 
        std::cout << value << " ";
        column_tracker++;
        if (column_tracker == columns){
            std::cout << std::endl;
            column_tracker = 0;
        }     
    }
}

int main(){
    std::vector<int> values = read_input("input.txt");
    reset_intcode(values);
    process_intcode(values, false);

    std::cout << std::endl << values[0] << std::endl;

    return 0;
}