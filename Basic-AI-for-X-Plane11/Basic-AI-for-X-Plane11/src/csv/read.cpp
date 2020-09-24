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
        vector<vector<std::string> > matrix;
        vector<int> coma_map;

        std::string filename;

        int raw_columns = 0;
        int columns = 0;
        int rows = 0;


        // Constructor
        read(std::string& _filename);

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
        int len = line.length();

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
        int len = line.length();

        string arr[5];

        std::getline(myFile, line);
        
        //map: 1-3-5-7
        //line: 1 , 2 , 3 , 4 , 5  
        // coma    coma+   
        //   1   -    3 = 
        for (int i = 0; i < columns; i++)
        {
            if (i == 0)
            {
                arr[i] = line.substr(0, coma_map[i]);
                cout << "substr: " << "( " << 0 << " , " << coma_map[i] << endl;
            }


            int size_calc = ((coma_map[i + 1] - coma_map[i]) - 1);        
            int last_size_calc = ((line.length() - coma_map[i]) - 1);
            
             cout << "i: " << i << " expresion. " << (i == (columns - 1)) << "  substr: " << "( " << coma_map[i]+1 << " , " << ( i == columns-1 ? last_size_calc : size_calc) << endl;
        
             arr[i] = line.substr(coma_map[i] + 1, (i == columns - 1 ? last_size_calc : size_calc) );
        }

        cout << "\nMat:\n";
        for (int i = 0; i < columns; i++)
        {
            cout << arr[i] << "/";
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

    std::cout << std::endl;
    //std::cout << "rows: " << flightplan.rows;
    std::cout << std::endl;
    //std::cout << "columns: " << flightplan.columns;

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