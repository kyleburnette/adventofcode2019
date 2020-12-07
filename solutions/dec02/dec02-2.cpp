#include <iostream>
#include <fstream>
#include <vector>

/* 
dec02-1.cpp:
Solution for Day 2, Part 2 of AoC 2019.

Notes:
I kinda reverse engineered how the input noun and verb yield the final output, noticing
that increasing the verb increases the second half of the output and the noun increases
the first half of the output. Since they do not affect each other, that means you can solve
for them separately. That being said, I have not looked into why this works exactly,
so if I hadn't noticed that, I would have had to brute force it entirely.

The formula for the output is: output = 250 + (noun * 360) * 1000 + 635 + verb
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

int process_intcode(std::vector<int>& intcode, bool debug){
    int instr_pointer = 0;
    const int ADD = 1;
    const int MULTIPLY = 2;
    const int HALT = 99;

    while (intcode[instr_pointer] != HALT){
        if (debug){
            std::cout << "opcode: " << intcode[instr_pointer] << " | Position: " << intcode[instr_pointer + 1] << "(" << intcode[intcode[instr_pointer + 1]] 
            << ") Position: " << intcode[instr_pointer + 2] << "(" << intcode[intcode[instr_pointer + 2]] << ") Store Position: " << intcode[instr_pointer + 3] << std::endl;
        }
        switch(intcode[instr_pointer]){
            case ADD:
                intcode[intcode[instr_pointer + 3]] = intcode[intcode[instr_pointer + 1]] + intcode[intcode[instr_pointer + 2]]; 
                break;
            case MULTIPLY:
                intcode[intcode[instr_pointer + 3]] = intcode[intcode[instr_pointer + 1]] * intcode[intcode[instr_pointer + 2]];
                break;
            default:
                break;     
        }
        instr_pointer += 4;
    }

    return intcode[0];
}

void set_noun_and_verb(std::vector<int>& intcode, int noun, int verb){
    intcode[1] = noun;
    intcode[2] = verb;
}

void reset_intcode_memory(std::vector<int>& intcode, const std::vector<int>& original){
    for(int i = 0; i < original.size(); i++){
        intcode[i] = original[i];
    }
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
    std::vector<int> original_memory = read_input("input.txt");
    std::vector<int> working_memory = original_memory;
    int noun = 0;
    int verb = 0;
    int output = 0;
    
    for(int i = 0; output < 19690720; i++){
        set_noun_and_verb(working_memory, i, 0);
        output = process_intcode(working_memory, false);
        reset_intcode_memory(working_memory, original_memory);
        noun = i - 1;
    }

    output = 0;

    for(int i = 0; output < 19690720; i++){
        set_noun_and_verb(working_memory, noun, i);
        output = process_intcode(working_memory, false);
        reset_intcode_memory(working_memory, original_memory);
        verb = i;
    }

    reset_intcode_memory(working_memory, original_memory);
    set_noun_and_verb(working_memory, noun, verb);
    std::cout << "Noun: " << noun << " | Verb: " << verb << " -> " << process_intcode(working_memory, false) << std::endl;

    return 0;
}