#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector> 
#include <includes.h>

using namespace std;

namespace path
{
    std::string flightplan = { "test.csv" };
}

namespace csv
{
    class read
    {
    public:
        //vector<vector<std::string> > matrix;
        std::string matrix[100][100]{"-"};
        vector<int> coma_map;

        std::string filename;

        int raw_columns = 0;
        int columns = 0;
        int rows = 0;

        // Constructor
        read(std::string& _filename);

        // Public functions
        void print();

    private:

        void get_rows();
        void get_columns();
        void create_coma_map();


        void save_in_matrix();

    };

    void read::get_columns()
    {
        std::string line;
        std::ifstream myFile(filename);

        std::getline(myFile, line); 

        raw_columns = line.length();
        columns = 0;
        for (int i = 0; i < raw_columns; i++)
        {
            if (line[i] == ',')
            {
                columns++;
            }
        }

        myFile.close();
    }

    // Para obtener el numero de filas suma 1 en cada iteración cada vez que getline encuentra una línea para extraer.
    void read::get_rows()
    {
        std::string line;
        std::ifstream myFile(filename);
 
        rows = 0;
        while (std::getline(myFile, line))
        {
            rows++;
        }

        myFile.close();
    }

    void read::create_coma_map()
    {
        std::ifstream myFile(filename);
        std::string line;
 

        std::getline(myFile, line);

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                coma_map.push_back(i);
            }
        }     

        myFile.close();
    }

    void read::save_in_matrix()
    {
        std::ifstream myFile(filename);
        std::string line;

        for (int i = 0; i < rows; i++)
        {
            std::getline(myFile, line);
                           
            coma_map.resize(0);           

            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == ',')
                {
                    coma_map.push_back(i);
                }
            }

            raw_columns = line.length();
         
            for (int j = 0; j < columns; j++)
            {               
                int size_calc = ((coma_map[j + 1] - coma_map[j]) - 1);
                int last_size_calc = ((raw_columns - coma_map[j]) - 1);


                matrix[i][j] = line.substr(static_cast<int>(coma_map[j] + 1), (j == columns - 1 ? last_size_calc : size_calc));
            }
        }       
    }

    void read::print()
    {
        std::cout << std::endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                std::cout << "[" << matrix[i][j] << "]";
            }
            std::cout << std::endl;
        }
    }

    // Constructor class
    read::read(std::string& _filename)
    {
        filename = _filename;

        get_rows();
        get_columns();

        create_coma_map();

        save_in_matrix();
    }
}



int main() {

    csv::read flightplan(path::flightplan);

    flightplan.print();
    

    std::cout << std::endl; return 0;
}