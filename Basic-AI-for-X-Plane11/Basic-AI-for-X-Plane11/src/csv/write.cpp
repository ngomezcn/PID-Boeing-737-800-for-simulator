#include <fstream>
#include <iostream>

using namespace std;

int main() {
    // Create an output filestream object
    std::ofstream myFile("foo.csv");
    
    char output[2][6] = {{'1','2','3','4','5','6'},
                        {'7','8','9','0','1','2'}};

    int output2[2][6] = {{1,2,3,4,5,6},
                        {7,8,9,0,1,5}};
    
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            std::cout << output2[i][j] << ",";
            myFile << output2[i][j] << ",";
        }
        std::cout << std::endl;
        myFile << "\n";
    }

    // Send data to the stream
   // myFile << "Foo\n";
   // myFile << "1,2,3\n";
   // myFile << "2\n";
   // myFile << "3\n";
    
    // Close the file
    myFile.close();
    
    return 0;
}