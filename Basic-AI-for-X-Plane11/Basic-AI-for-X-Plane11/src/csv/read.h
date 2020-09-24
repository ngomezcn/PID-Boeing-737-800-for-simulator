#pragma once
#include <includes.h>

namespace path
{
    std::string flightplan = { "test.csv" };
}

namespace csv
{
    class read
    {
    public:

        std::string matrix[100][100]{ "-" };

        std::string filename;
        int columns{ 0 };
        int rows{ 0 };

        // Constructor
        read(std::string& _filename);

        // Public functions
        void print();

    private:

        std::vector<int> coma_map;
        std::ifstream myFile;
        std::string line;

        int line_len{ 0 };

        void get_rows();
        void get_columns();

        void get_dimensions();

        void save_in_matrix();
        void create_coma_map();

        bool error_manager();

        void check_file_location();
    };

    void read::check_file_location()
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

    bool read::error_manager()
    {
        check_file_location();

        if (!myFile.is_open())
        {
            prerror("File {0} could not be opened.", filename);

            return false;
        }
        myFile.close();

        return true;
    }

    void read::get_columns()
    {
        check_file_location();

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
        check_file_location();

        rows = 0;
        while (std::getline(myFile, line))
        {
            rows++;
        }

        myFile.close();
    }

    void read::get_dimensions()
    {
        get_columns();
        get_rows();
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
        check_file_location();

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
        }

        myFile.close();
    }

    void read::print()
    {
        prinfo("Printing file: {0}", filename);
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

        if (!error_manager())
        {
            prwarn("Aborting the creation of the object.");

        }
        else
        {
            get_rows();
            get_columns();

            save_in_matrix();
        }
    }
}