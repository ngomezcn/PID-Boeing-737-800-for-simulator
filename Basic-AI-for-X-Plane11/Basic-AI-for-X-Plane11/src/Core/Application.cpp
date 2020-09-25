#include <includes.h>
#include <processenv.h>

int main() {

    Init::Log();

    csv::read flightplan(path::flightplan);

    flightplan.print();
    
   while (true)
    {
        flightplan.read_file();
        if (!flightplan.getError)
        {
            std::cout << std::string(100, '\n');
        }
        flightplan.print();

        Sleep(10);

    }
   }