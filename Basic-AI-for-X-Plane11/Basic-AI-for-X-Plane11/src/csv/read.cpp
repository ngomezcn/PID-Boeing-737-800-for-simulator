//#include <includes.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector> 

using namespace std;

const int lineas = 5;
const int columnas = 10;

std::string matrix[lineas][columnas];

void read_csv(std::string filename) {


    std::ifstream myFile(filename);

   // if (!myFile.is_open()) prerror("No se ha podido abrir el archivo: {0}", filename);            

    std::string line;
    std::string val;   

    // Convierte las lineas en extraidas en crudo e introduce cada valor en la casilla que corresponde dentro del array.
    int coun = 0;
    for (int i = 0; i < lineas; i++)
    {              
         std::getline(myFile, line);
         
         int indexColums = 0;

         for (int j = 0; j < line.length(); j++)
         {  
             if (line[j] != ',')
             {
                 coun++;
                 matrix[i][indexColums] = line[j];
              //  std::cout << indexColums << "/";
                 indexColums++;
             }
         }
    }

    myFile.close();
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
        void save_in_matrix();
    };

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

        for (int i = 0; i < rows; i++)
        {              
            std::getline(myFile, line);
            
            int indexColums = 0;

            for (int j = 0; j < line.length(); j++)
            {  
                if (line[j] != ',')
                {
                    columns++;
                    matrix[i][indexColums] = line[j];
                    indexColums++;
                }
            }
        }
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
    //std::cout << "columns: " << flightplan.columns << " -";

  
    //get_dimension("test.csv");
    read_csv("test.csv");    

    /*std::cout << std::endl;
    for (int i = 0; i < lineas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            std::cout << matrix[i][j] << ",";
        }
        std::cout << std::endl;
    }*/

    return 0;
}