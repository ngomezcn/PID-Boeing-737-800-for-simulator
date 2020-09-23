#include <includes.h>

using namespace std;

const int lineas = 5;
const int columnas = 10;

std::string matrix[lineas][columnas];

void get_dimension(std::string filename)
{
    std::ifstream myFile(filename);

    if (!myFile.is_open()) prerror("No se ha podido abrir el archivo: {0}", filename);            

    std::string line;
    std::string val;

    int a = 0;
    while (std::getline(myFile, line))
    {
        a++;
    }

    std::cout << a;

    myFile.close();
}

void read_csv(std::string filename) {


    std::ifstream myFile(filename);

    if (!myFile.is_open()) prerror("No se ha podido abrir el archivo: {0}", filename);            

    std::string line;
    std::string val;   

    // Convierte las lineas en extraidas en crudo e introduce cada valor en la casilla que corresponde dentro del array.
    for (int i = 0; i < lineas; i++)
    {              
         std::getline(myFile, line);
         
         int indexColums = 0;

         for (int j = 0; j < line.length(); j++)
         {  
             if (line[j] != ',')
             {
                 matrix[i][indexColums] = line[j];
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
        int columns;
        int rows = 0;

        read(std::string &_filename)
        {
            filename = _filename;

            std::ifstream myFile(filename);

            if (!myFile.is_open())
            {
                prerror("No se ha podido abrir el archivo: {0}", filename);
            }

            std::string line;
            std::string val;

            while (std::getline(myFile, line))
            {
                rows++;
            }

            myFile.close();

        }
    };

}

namespace path
{
    std::string flightplan = { "test.csv"};
}

int main() {

   /* int a = 1;
    int b = 2;

    */
    csv::read flightplan(path::flightplan);

    std::cout << "F: " << flightplan.rows << " -";
  
   // get_dimension("test.csv");
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