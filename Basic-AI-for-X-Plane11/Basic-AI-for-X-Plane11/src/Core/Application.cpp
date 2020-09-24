#include <includes.h>
#include <processenv.h>

int main() {

    Init::Log();

    csv::read flightplan(path::flightplan);

    flightplan.print();
}