#include <includes.h>
#include <processenv.h>

int main() {

    Init::Log();

    csv::read flightplan(path::flightplan);
    
    std::vector<int> hola = {1,2,3,4};

    hola.insert(hola.begin(), 5);

    for (int i = 0; i < hola.size(); i++)
    {

    }


    //flightplan.print();
    
   /* while (true)
    {
        flightplan.read_file();
        if (!flightplan.getError)
        {
            std::cout << std::string(100, '\n');
        }
        Sleep(10);

    }*/
   }