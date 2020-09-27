#pragma once
#include <includes.h>

namespace csv
{
    namespace paths
    {
        std::string PID = { "csv_files/pid.csv" };
        std::string FlightPlan = { "csv_files/flightplan.csv" };
        std::string TakeFff = { "csv_files/takeoff.csv" };
        std::string Config = { "csv_files/config.csv" };

        std::string test = { "csv_files/test.csv" };
    }   

    class csv_manager
    {
    public:
        std::vector<std::vector<std::string>> matrix;

        std::string filename;
        int columns{ 0 };
        int rows{ 0 };

        bool getError = false;

        // Constructor
        csv_manager(std::string& _filename);

        // Public functions
        void print();
        void read_file();

        void variable_alloc(const char* row_id, const char* columns_id, int& address);
        void variable_alloc(const char* row_id, const char* columns_id, double& address);
        void variable_alloc(const char* row_id, const char* columns_id, std::string& address);


    private:

        std::vector<int> coma_map;
        std::ifstream myFile;
        std::string line;
        int line_length{ 0 };

        void get_rows();
        void get_columns();

        void save_in_matrix();
        void create_coma_map();


        // Exceptions and error handling csv_manager
        bool check_file_location();
        bool verify_standard();
        void reset_func_getline();
    };

}
