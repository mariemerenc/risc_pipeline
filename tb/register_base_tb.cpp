#include <systemc.h>
#include "register_base.h"

int sc_main(int argc, char* argv[]) {
    // Signals
    sc_clock clock("clock", 10, SC_NS);
    sc_signal<bool> enable, write;
    sc_signal<sc_uint<8>> addrSrc1, addrSrc2;
    sc_signal<sc_uint<9>> addrDest;
    sc_signal<sc_uint<32>> dataIn;
    sc_signal<sc_uint<32>> dataOut1, dataOut2;

    // Instantiate RegisterBase
    RegisterBase<sc_uint<32>, 32> regbank("RegisterBank");
    regbank.clock(clock);
    regbank.enable(enable);
    regbank.write(write);
    regbank.addressSource1(addrSrc1);
    regbank.addressSource2(addrSrc2);
    regbank.addressDest(addrDest);
    regbank.dataToWrite(dataIn);
    regbank.dataSource1(dataOut1);
    regbank.dataSource2(dataOut2);

    // Initialize control signals
    enable = 0;
    write = 0;
    addrSrc1 = 0;
    addrSrc2 = 1;
    addrDest = 0;
    dataIn = 0;

    sc_start(5, SC_NS); // Half clock cycle before enabling

    // Write data to register 3
    enable = 1;
    write = 1;
    addrDest = 3;
    dataIn = 0xDEADBEEF;
    sc_start(10, SC_NS);

    // Write data to register 5
    addrDest = 5;
    dataIn = 0xCAFEBABE;
    sc_start(10, SC_NS);

    // Read data from register 3 and 5
    write = 0;
    addrSrc1 = 3;
    addrSrc2 = 5;
    sc_start(10, SC_NS);

    std::cout << "[READ] Register[3] = 0x" << std::hex << dataOut1.read() << std::endl;
    std::cout << "[READ] Register[5] = 0x" << std::hex << dataOut2.read() << std::endl;

    // Disable register access
    enable = 0;
    sc_start(10, SC_NS);

    std::cout << "Simulation complete." << std::endl;
    sc_stop();
    return 0;
}
