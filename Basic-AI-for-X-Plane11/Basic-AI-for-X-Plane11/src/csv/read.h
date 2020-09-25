#pragma once
#include <includes.h>

namespace path
{
    std::string flightplan = { "flightplan.csv" };
    std::string takeoff    = { "takeoff.csv" };
    std::string config     = { "config.csv" };
}

namespace csv
{
    class read 
    {
    public:
        std::vector<std::vector<std::string>> matrix;

        std::string filename;
        int columns{ 0 };
        int rows{ 0 };

        bool getError = false;

        // Constructor
        read(std::string& _filename);

        // Public functions
        void print();

        void read_file();

    private:

        std::vector<int> coma_map;
        std::ifstream myFile;
        std::string line;

        int line_len{ 0 };

        void get_rows();
        void get_columns();

        void save_in_matrix();

        void create_coma_map();
        void reset_func_getline();

        // Exceptions and error handling manager
        bool check_file_location();
        bool verify_standard();
    };

    bool read::verify_standard()
    {
        reset_func_getline();
        create_coma_map();

        int size_arr = coma_map.size();        

        for (int i = 0; i < rows; i++)
        {
            std::getline(myFile, line);
            create_coma_map();

            if (coma_map.size() != size_arr)
            {
                return false;
            }
        }

        return true;
    }

    void read::reset_func_getline()
    {
        if (myFile.is_open())
        {
            myFile.close();
            myFile.open(filename);
        }

        if (!myFile.is_open())
        {
            myFile.open(filename);
        }
    }

    bool read::check_file_location()
    {
        reset_func_getline();

        if (!myFile.is_open())
        {
            return false;
        }
        myFile.close();

        return true;
    }

    void read::get_columns()
    {
        reset_func_getline();

        std::getline(myFile, line);
        line_len = line.length();
        columns = 0;
        for (int i = 0; i < line_len; i++)
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
        reset_func_getline();

        rows = 0;
        while (std::getline(myFile, line))
        {

            rows++;
        }

        myFile.close();
    }

    // Esta funcion sera llamada por cada linea en el archivo .csv
    void read::create_coma_map()
    {
        coma_map.resize(0);

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                coma_map.push_back(i);
            }
        }
    }

    // Extrae los caracteres linea por linea y los guarda en una matriz
    void read::save_in_matrix()
    {
        reset_func_getline();

        for (int i = 0; i < rows; i++)
        {
            std::getline(myFile, line);

            create_coma_map();

            for (int j = 0; j < columns; j++)
            {
                int size_calc = ((coma_map[j + 1] - coma_map[j]) - 1);
                int last_size_calc = ((line.length() - coma_map[j]) - 1);
                       

                matrix[i][j] = line.substr(coma_map[j] + 1, (j == columns - 1 ? last_size_calc : size_calc));
            }

            matrix[i].insert(matrix[i].begin(), line.substr(0, coma_map[0]));
        }

        myFile.close();
    }

    void read::print()
    {
       
        if (getError)
        {
            prwarn("Unable to print due to an error that occurred during execution.");
        }
        else
        {
            
            std::vector<int> size_map;
    
            int max = 0;
            for (int i = 0; i < columns; i++)
            {
                max = 0;
                for(int j = 0; j < rows; j++)
                {
                    if (matrix[j][i].length() > max)
                    {
                        max = matrix[j][i].length();
                    }
                  }
              size_map.push_back(max);
             }

            prinfo("Printing file: {0}", filename);
            for (int i = 0; i < rows; i++)
            {     
                //std::cout << max << std::endl;


                for (int j = 0; j < columns; j++)
                {                   
                    
                     std::string s(size_map[j] - matrix[i][j].length(), ' ');

                     std::cout << "[" << matrix[i][j] << s << "]";
                }
                std::cout << std::endl;
            }
        }
    }

    // Esta funcion es la main
    void read::read_file()
    {
        getError = false;

        if (!check_file_location())
        {
            getError = true;

            prerror("File {0} could not be opened.", filename);
            prwarn("Aborting the creation of the object.");
        }
        else
        {
            // Get the dimensions.
            get_rows();
            get_columns();

            if (!verify_standard())
            {
                getError = true;
                prerror("The file have not the same columns in each row");
            }
            else
            {
                matrix.resize(rows);
                for (int i = 0; i < rows; i++)
                {
                    matrix[i].resize(columns);
                }
                save_in_matrix();
            }
        }
    }

    // Constructor class
    read::read(std::string& _filename)
    {
        filename = _filename;       

        read_file();
    }
}
