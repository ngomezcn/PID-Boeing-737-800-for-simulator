#pragma once
#include "build_csv.h"

namespace csv
{   
    bool csv_manager::verify_standard()
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

    void csv_manager::reset_func_getline()
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

    bool csv_manager::check_file_location()
    {
        reset_func_getline();

        if (!myFile.is_open())
        {
            return false;
        }
        myFile.close();

        return true;
    }

    void csv_manager::get_columns()
    {
        reset_func_getline();

        std::getline(myFile, line);
        line_length = line.length();
        columns = 0;
        for (int i = 0; i < line_length; i++)
        {
            if (line[i] == ',')
            {
                columns++;
            }
        }

        myFile.close();
    }

    // Para obtener el numero de filas suma 1 en cada iteración cada vez que getline encuentra una línea para extraer.
    void csv_manager::get_rows()
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
    void csv_manager::create_coma_map()
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
    void csv_manager::save_in_matrix()
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


                //matrix[i][j] = line.substr(coma_map[j] + 1, (j == columns - 1 ? last_size_calc : size_calc));

                if (j == (columns - 1))
                {
                    matrix[i][j] = line.substr(coma_map[j] + 1, last_size_calc );
                }
                else
                {
                    matrix[i][j] = line.substr(coma_map[j] + 1, size_calc);

                }
            }

            matrix[i].insert(matrix[i].begin(), line.substr(0, coma_map[0]));
        }

        myFile.close();
    }

    void csv_manager::print()
    {

        if (getError)
        {
            prerror("Unable to print due to an error that occurred during execution.");
        }
        else
        {

            std::vector<int> size_map;

            int max_size = 0;
            for (int i = 0; i < columns; i++)
            {
                max_size = 0;
                for (int j = 0; j < rows; j++)
                {
                    if (matrix[j][i].length() > max_size)
                    {
                        max_size = matrix[j][i].length();
                    }
                }
                size_map.push_back(max_size);
            }

            prinfo("Printing file: {0}", filename);
            for (int i = 0; i < rows; i++)
            {

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
    void csv_manager::read_file()
    {
        getError = false;

        if (!check_file_location())
        {
            getError = true;

            prerror("File {0} could not be opened.", filename);
            prerror("Aborting the creation of the object.\n");
        }
        else
        {
            // Get the dimensions.
            get_rows();
            get_columns();

            if (!verify_standard())
            {
                getError = true;
                prerror("The file {0} have not the same columns in each row. It error will cause problems.", filename);
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
    csv_manager::csv_manager(std::string& _filename)
    {
        filename = _filename;

        read_file();
    }

    void csv_manager::variable_alloc(const char* row_id, const char* columns_id, int& address)
    {
        int row_search = 0;
        int colum_search = 0;
        getError = false;

        if (getError || !check_file_location() || !verify_standard())
        {
            prerror("Unable to allocate variable due to an error that occurred during execution.");

            address = 0;

            return;
        }

        for (int i = 0; i < rows; i++)
        {
            if (matrix[i][0] == row_id)
            {
                row_search = i;
            }
        }

        for (int i = 0; i < columns; i++)
        {
            if (matrix[0][i] == columns_id)
            {
                colum_search = i;
            }
        }

        // Si no se ha encontrado alguna de las dos variables devolvemos un error. 
        if (row_search == 0)
        {
            prwarn("Keyword not found: {0}, the program could have an undefined behavior", row_id);
            getError = true;
            return;
        }

        if (colum_search == 0)
        {
            prwarn("Keyword not found: {0}, the program could have an undefined behavior", columns_id);
            getError = true;
            return;
        }

        address = std::stoi(matrix[row_search][colum_search]);  

        if (!getError)
        {
            prdebug("{0}[{1}] = {2}", row_id, columns_id, address, filename);
        }

    }

    void csv_manager::variable_alloc(const char* row_id, const char* columns_id, double& address)
    {
        int row_search = 0;
        int colum_search = 0;
        getError = false;           

        if (getError || !check_file_location() || !verify_standard())
        {
            prerror("Unable to allocate variable due to an error that occurred during execution.");

            address = 0;

            return;
        }

        for (int i = 0; i < rows; i++)
        {
            if (matrix[i][0] == row_id)
            {
                row_search = i;
            }
        }

        for (int i = 0; i < columns; i++)
        {
            if (matrix[0][i] == columns_id)
            {
                colum_search = i;
            }
        }

        // Si no se ha encontrado alguna de las dos variables devolvemos un error. 
        if (row_search == 0)
        {
            prwarn("Keyword not found: {0}, the program could have an undefined behavior", row_id);
            getError = true;
            return;
        }

        if (colum_search == 0)
        {
            prwarn("Keyword not found: {0}, the program could have an undefined behavior", columns_id);
            getError = true;
            return;
        }

        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < columns; j++)
            {
                for (int k = 0; k < matrix[i][j].size(); k++)
                {
                    if (static_cast<int>(matrix[i][j][k]) < 48 || static_cast<int>(matrix[i][j][k]) > 57)
                    {
                        if (matrix[i][j][k] == '.')
                        {

                        }
                        else
                        {
                            if (row_search == i && colum_search == j)
                            {
                                prerror("{2}[{3}] = [Character found during extraction aborting] -> Row: {0} Column: {1} ", i, j, row_id, columns_id );
                                return;
                            }
                        }
                    }
                }
            }
        }

        address = std::stod(matrix[row_search][colum_search]);

        if (!getError)
        {
            prdebug("{0}[{1}] = {2}", row_id, columns_id, address, filename);
        }
    }

    void csv_manager::variable_alloc(const char* row_id, const char* columns_id, std::string& address)
    {
        int row_search = 0;
        int colum_search = 0;
        getError = false;

        if (getError || !check_file_location() || !verify_standard())
        {
            prerror("Unable to allocate variable pos[] due to an error that occurred during execution.");

            address = "NULL";

            return;
        }

        for (int i = 0; i < rows; i++)
        {
            if (matrix[i][0] == row_id)
            {
                row_search = i;
            }
        }

        for (int i = 0; i < columns; i++)
        {
            if (matrix[0][i] == columns_id)
            {
                colum_search = i;
            }
        }

        // Si no se ha encontrado alguna de las dos variables devolvemos un error. 
        if (row_search == 0)
        {
            prwarn("Keyword not found: {0}, the program could have an undefined behavior", row_id);
            getError = true;
            return;
        }

        if (colum_search == 0)
        {
            prwarn("Keyword not found: {0}, the program could have an undefined behavior", columns_id);
            getError = true;
            return;
        }

        address = matrix[row_search][colum_search];

        if (!getError)
        {
            prdebug("{0}[{1}] = {3}{2}{3}", row_id, columns_id, address, '"');
        }

    }
     
}
