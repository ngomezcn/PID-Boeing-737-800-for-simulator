#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector> 

using namespace std;

namespace csv
{
    class read
    {
    public:
        std::string filename;
        int columns = 0;
        int rows = 0;
        vector<vector<std::string> > matrix; 

        read(std::string &_filename);
    private:
        void get_rows();
        void save_in_matrix();
    };

    void read::get_columns()
    {
        // Code to get the columns from to string line
    }

    void read::get_rows()
    {
        std::string line;
        std::ifstream myFile(filename);

        while (std::getline(myFile, line))
        {
            rows++;
        }

        myFile.close();
    }

    void read::save_in_matrix()
    {
        std::ifstream myFile(filename);

        std::string line;

       /*

        Code to tranform string line into a matrix

        */

        myFile.close();
    }

    // Constructor class
    read::read(std::string &_filename)
    {
        filename = _filename;

        get_rows();

        save_in_matrix();
        
    }
}




namespace path
{
    std::string flightplan = { "test.csv"};
}

int main() {

   
    csv::read flightplan(path::flightplan);

    std::cout << "rows: " << flightplan.rows << " -";
    std::cout << "columns: " << flightplan.columns << " -";


    /*std::cout << std::endl;
    for (int i = 0; i < lineas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            std::cout << flightplan.matrix[i][j] << ",";
        }
        std::cout << std::endl;
    } */

    return 0;
}