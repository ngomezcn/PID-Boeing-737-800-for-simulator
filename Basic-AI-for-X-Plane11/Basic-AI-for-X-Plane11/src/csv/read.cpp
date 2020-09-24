#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector> 

using namespace std;

namespace path
{
    std::string flightplan = { "test.csv"};
}

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

        std::string substract(int &begin, int &end);
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

    // Para obtener el numero de filas suma 1 en cada iteración cada vez que getline encuentra una línea para extraer.
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

    std::string read::substract(int& begin, int& end)
    {

    }


    void read::save_in_matrix()
    {
        std::ifstream myFile(filename);

        std::string line;
        
        vector<int> coma(columns);

        int len = line.length(); 

        std::getline(myFile, line);

        string arr[5];
        

        int ct = 0;
        std::cout << "IDs: ";
        for(int j = 0; j < line.length(); j++)
        {                
             if (line[j] == ',')
             {
                 coma[j] = j;
                 std::cout << coma[j];
             }                
        }

        //- 1 - 3 - 5 - 7 - 19
        for (int i = 0; i < 5; i++)
        {
            std::cout << "\nline: " << line << std::endl;
            std::cout << "line.substr " << line.substr(2,3) << std::endl;
        }
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



int main() {

    std::string a = "0123456789";
    std::string b = a.substr(0,3);
    cout << endl << b << endl;
    csv::read flightplan(path::flightplan);

    std::cout << std::endl;
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