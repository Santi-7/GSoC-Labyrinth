/** ---------------------------------------------------------------------------
 ** main.cpp
 **
 ** This program finds the length of the maximum free path in a labyrinth.
 **
 ** The input labyrinth to solve is in the file with name argv[1].
 **
 ** The labyrinth format is as specified in here:
 **     http://jderobot.org/store/jmplaza/uploads/gsoc/programming-test-c.pdf
 **
 ** Author: Santiago Gil Begué.
 ** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>

#include "Labyrinth.hpp"

// Global variable that represents the labyrinth.
Labyrinth labyrinth;

int main(int argc, char *argv[]) {
    // Check number of parameters.
    if (argc != 2) {
        std::cout << "Wrong number of arguments." << std::endl;
        std::cout << "Usage: " << argv[0] << " <labyrinth_file>" << std::endl;
        return 1;
    }

    // Read labyrinth from input file.
    std::ifstream inputFile;
    inputFile.open(argv[1]);
    if (!inputFile.is_open()) {
        std::cout << "Couldn't open file " << argv[1] << std::endl;
        return 1;
    }
    labyrinth = Labyrinth(inputFile);
    inputFile.close();

    Labyrinth result = labyrinth.solveMaxPath();

    // Write the result labyrinth.
    std::ofstream outputFile;
    outputFile.open("output.txt");
    outputFile << result.maxPath() << std::endl;
    outputFile << result;

    return 0;
}