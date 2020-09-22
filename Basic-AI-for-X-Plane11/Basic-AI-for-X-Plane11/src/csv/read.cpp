#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <iostream>

using namespace std;

std::string matrix[2][5];

void read_csv(std::string filename) {

    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line;
    std::string val;

    for (int i = 0; i < 6; i++)
    {
        // Cada vez que se llama salta a la siguiente linea y la extrae
        std::getline(myFile, line);
        
        std::cout << line;
        
        std::cout << "\n";
    }
    
    myFile.close();

}



int main() {
    //Read three_cols.csv and ones.csv
    read_csv("dataflight/takeoff.csv");

    std::cout << std::endl << "======" << std::endl;
    //myOwn();

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            std::cout << matrix[i][j] << ",";
        }
        std::cout << std::endl;
    }

    return 0;
}