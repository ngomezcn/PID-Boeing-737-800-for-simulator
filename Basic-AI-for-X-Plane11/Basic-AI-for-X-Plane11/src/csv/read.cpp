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
        void get_columns();

        void save_in_matrix();
    };

    void read::get_columns()
    {
        std::string line;
        std::ifstream myFile(filename);

        std::getline(myFile, line);

        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == ',')
            {
                columns++;
            }
        }

        myFile.close();
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
        
        std::string buffer;

        int len = line.length(); 

        for(int i = 0; i < rows; i++)
        {
            std::getline(myFile, line);

            for(int j = 0; j < columns; j++)
            {                
                //std::cout << line[j] << std::endl;                
            }
        }

        /*

        Code to tranform string line and put it into matrix separated by comas

        */

        myFile.close();
    }

    // Constructor class
    read::read(std::string &_filename)
    {
        filename = _filename;

        get_rows();
        get_columns();

        save_in_matrix();
        
    }
}




namespace path
{
    std::string flightplan = { "test.csv"};
}

int main() {

   
    std::string a = "0123456789";
    std::string b = a.substr(0,3);

    std::cout << b << std::endl;

    csv::read flightplan(path::flightplan);

    std::cout << "rows: " << flightplan.rows;
    std::cout << std::endl;
    std::cout << "columns: " << flightplan.columns;

    /*std::cout << std::endl;
    for (int i = 0; i < lineas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            std::cout << flightplan.matrix[i][j] << ",";
        }
        std::cout << std::endl;
    } */

    std::cout << std::endl; return 0;
}