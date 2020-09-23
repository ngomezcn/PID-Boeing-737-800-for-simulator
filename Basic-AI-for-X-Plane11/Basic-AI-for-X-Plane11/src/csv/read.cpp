#include <includes.h>

using namespace std;

const int lineas = 2;
const int columnas = 5;

std::string matrix[lineas][columnas];

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

         for (int j = 0; j < columnas + (columnas - extraComa); j++)
         {  
             if (line[j] != ',')
             {
                 matrix[i][indexColums] = line[j];
                 indexColums++;
             }
         }

         std::cout << "\n";              
    }
    
    myFile.close();
}

int main() {

  
    read_csv("tesst.csv");    

  /*  for (int i = 0; i < lineas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            std::cout << matrix[i][j] << ",";
        }
        std::cout << std::endl;
    }*/

    return 0;
}