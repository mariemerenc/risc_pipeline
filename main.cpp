#include <systemc.h>
#include "processor.h"

int sc_main(int argc, char* argv[]) {
    std::cout << "SystemC Processor Simulation Starting..." << std::endl;

    Processor proc("RISC_Processor");

    sc_start(500, SC_NS);

    std::cout << "SystemC Processor Simulation Completed." << std::endl;
    return 0;
}
