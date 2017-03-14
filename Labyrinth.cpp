/** ---------------------------------------------------------------------------
 ** Labyrinth.cpp
 **
 ** Implementation for Labyrinth.hpp
 **
 ** Author: Santiago Gil Begué.
 ** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>

#include "Labyrinth.hpp"

Labyrinth::Labyrinth(const std::vector<std::vector<int>> &board)
{
    mBoard = board;
    mMaxPath = 0;
}

Labyrinth::Labyrinth(std::ifstream &inputFile)
{
    // Loop all lines
    std::string fileLine;
    while (!inputFile.eof()) {
        std::vector<int> line;
        line.reserve(fileLine.size());
        inputFile >> fileLine;
        // Loop all characters in the current line.
        for (unsigned long i = 0; i < fileLine.size(); ++i) {
            switch (fileLine[i]) {
                // It's a wall.
                case WALL_FILE:
                    line.push_back(WALL);
                    break;
                    // It's a free path.
                case FREE_FILE:
                    line.push_back(FREE);
                    break;
                    // Character not valid.
                default:
                    std::cout << "'" << fileLine[i] << "' is not a valid input character." << std::endl;
                    throw 1;
            }
        }
        mBoard.push_back(line);
    }
}

Labyrinth Labyrinth::solveMaxPath() const
{
    Labyrinth max = *this;
    // First row.
    for (unsigned long j = 0; j < columns(); ++j) {
        max = std::max(max, solveMaxPath(0, j));
    }
    // First and last column.
    for (unsigned long i = 1; i < rows()-1; ++i) {
        max = std::max(max, solveMaxPath(i, 0));
        max = std::max(max, solveMaxPath(i, columns()-1));
    }
    // Last row.
    for (unsigned long j = 0; j < columns(); ++j) {
        max = std::max(max, solveMaxPath(rows()-1, j));
    }
    return max;
}

Labyrinth Labyrinth::solveMaxPath(const unsigned long i, const unsigned long j) const
{
    // Current position out ouf labyrinth limits.
    if (i < 0 | j < 0 | i >= rows() | j >= columns()) return *this;

    // Check if current position is free.
    if (mBoard[i][j] == FREE) {
        Labyrinth nextStep = *this;
        nextStep.set(i, j, nextStep.mMaxPath++);
        // Return the maximum labyrinth going in the four directions from current position.
        return std::max(std::max(nextStep.solveMaxPath(i-1, j), nextStep.solveMaxPath(i+1, j)),
                        std::max(nextStep.solveMaxPath(i, j-1), nextStep.solveMaxPath(i, j+1)));
    }
    // Not free, return same labyrinth.
    else return *this;
}

unsigned long Labyrinth::rows() const
{
    return mBoard.size();
}

unsigned long Labyrinth::columns() const
{
    return mBoard[0].size();
}

int Labyrinth::maxPath() const
{
    return mMaxPath;
}

int Labyrinth::at(const unsigned long i, const unsigned long j) const
{
    return mBoard[i][j];
}

void Labyrinth::set(const unsigned long i, const unsigned long j, const int value)
{
    mBoard[i][j] = value;
}

bool Labyrinth::operator<(const Labyrinth &l) const
{
    return mMaxPath < l.mMaxPath;
}

std::ostream& operator<<(std::ostream &out, const Labyrinth &l)
{
    for (unsigned long i = 0; i < l.rows(); ++i) {
        for (unsigned long j = 0; j < l.columns(); ++j) {
            switch (l.at(i, j)) {
                case WALL:
                    out << WALL_FILE;
                    break;
                case FREE:
                    out << FREE_FILE;
                    break;
                default:
                    out << l.at(i, j);
            }
        }
        out << std::endl;
    }
}