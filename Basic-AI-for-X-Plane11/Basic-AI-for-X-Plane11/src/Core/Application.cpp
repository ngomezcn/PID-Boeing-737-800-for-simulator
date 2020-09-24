#include <includes.h>

int main() {

    Init::Log();

    csv::read flightplan(path::flightplan);

    flightplan.print(); 
}