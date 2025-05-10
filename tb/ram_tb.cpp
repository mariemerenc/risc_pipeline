#include "systemc.h"
#include "ram.h"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 10, SC_NS);

    sc_signal<bool> enable, write;
    sc_signal<sc_uint<9>> address;
    sc_signal<sc_uint<32>> dataIn;
    sc_signal<sc_uint<32>> dataOut;

    RAM<sc_uint<32>, 256> ram("RAM");
    ram.clock(clk);
    ram.enable(enable);
    ram.write(write);
    ram.address(address);
    ram.dataIn(dataIn);
    ram.dataOut(dataOut);

    // inicialização
    enable = 0;
    write = 0;
    address = 0;
    dataIn = 0;

    // start simulation
    sc_start(5, SC_NS); // meio ciclo inicial

    // escreve na posição 10
    enable = 1;
    write = 1;
    address = 10;
    dataIn = 0xCAFEBABE;
    sc_start(10, SC_NS);

    // escreve na posição 42
    address = 42;
    dataIn = 0x12345678;
    sc_start(10, SC_NS);

    // lê da posição 10
    write = 0;
    address = 10;
    sc_start(10, SC_NS);
    std::cout << "[READ] RAM[10] = 0x" << std::hex << dataOut.read() << std::endl;

    // lê da posição 42
    address = 42;
    sc_start(10, SC_NS);
    std::cout << "[READ] RAM[42] = 0x" << std::hex << dataOut.read() << std::endl;

    // desliga a RAM
    enable = 0;
    sc_start(10, SC_NS);

    std::cout << "Ending simulation." << std::endl;
    sc_stop();
    return 0;
}
