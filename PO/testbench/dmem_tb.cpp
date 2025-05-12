#include <systemc.h>
#include "dmem.h"

int sc_main(int argc, char* argv[]) {
    DMEM dmem("DMEM");

    sc_signal<bool> clock;
    sc_signal<bool> enable;
    sc_signal<bool> write;
    sc_signal<sc_uint<32>> address;
    sc_signal<sc_int<32>> dataIn;
    sc_signal<sc_int<32>> dataOut;

    dmem.clock(clock);
    dmem.enable(enable);
    dmem.write(write);
    dmem.address(address);
    dmem.dataIn(dataIn);
    dmem.dataOut(dataOut);

    sc_trace_file *wf = sc_create_vcd_trace_file("dmem_wave");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, enable, "enable");
    sc_trace(wf, write, "write");
    sc_trace(wf, address, "address");
    sc_trace(wf, dataIn, "dataIn");
    sc_trace(wf, dataOut, "dataOut");

    clock = 0;
    enable = 0;
    write = 0;
    address = 0;
    dataIn = 0;

    std::cout << "Starting DMEM testbench..." << std::endl;

    // 1. Escrever valor 42 no endereço 10
    enable = 1;
    write = 1;
    address = 10;
    dataIn = 42;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);

    // 2. Escrever valor -15 no endereço 20
    address = 20;
    dataIn = -15;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);

    // 3. Ler do endereço 10
    write = 0;
    address = 10;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);
    std::cout << "Read from address 10: " << dataOut.read() << std::endl;

    // 4. Ler do endereço 20
    address = 20;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);
    std::cout << "Read from address 20: " << dataOut.read() << std::endl;

    // 5. Tentar ler com enable desativado
    enable = 0;
    address = 10;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);
    std::cout << "Read from address 10 with enable = 0: " << dataOut.read() << std::endl;

    sc_close_vcd_trace_file(wf);
    std::cout << "DMEM testbench completed." << std::endl;

    return 0;
}
