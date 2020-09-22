#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <iostream>

std::string output[2][6];

std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<int>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    int val;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        int count = 0;
        // Extract each column name
        while(std::getline(ss, colname, ',')){
            ++count;
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, std::vector<int> {}});
         //   std::cout << colname << ",";
            output[0][count-1] = colname;
        }
    }

    // Read data, line by line
    while(std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);
        
        // Keep track of the current column index
        int colIdx = 0;
        int count  = 0;

        // Extract each integer
        while(ss >> val){

            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);
            output[count][colIdx] = val;
            std::cout << colIdx << std::endl;
            std::cout << count;
            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();
            
            // Increment the column index
            ++count;
            colIdx++;
        }
    }

    // Close file
    myFile.close();

    return result;
}

int main() {

    std::vector<std::pair<std::string, std::vector<int>>> read = read_csv("foo.csv");

    std::cout << "\nint main()" << std::endl;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            std::cout << output[i][j] << ",";
        }
        std::cout <<std::endl;
    }

    return 0;
}
