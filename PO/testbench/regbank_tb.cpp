#include <systemc.h>
#include "regbank.h"

int sc_main(int argc, char* argv[]) {
    // Instanciação do módulo
    RegBank regbank("RegBank");

    // Sinais
    sc_signal<bool> clock;
    sc_signal<bool> enable;
    sc_signal<bool> write;
    sc_signal<sc_uint<5>> addressSource1;
    sc_signal<sc_uint<5>> addressSource2;
    sc_signal<sc_uint<5>> addressDest;
    sc_signal<sc_int<32>> dataToWrite;
    sc_signal<sc_int<32>> dataSource1;
    sc_signal<sc_int<32>> dataSource2;

    // Conexão dos sinais
    regbank.clock(clock);
    regbank.enable(enable);
    regbank.write(write);
    regbank.addressSource1(addressSource1);
    regbank.addressSource2(addressSource2);
    regbank.addressDest(addressDest);
    regbank.dataToWrite(dataToWrite);
    regbank.dataSource1(dataSource1);
    regbank.dataSource2(dataSource2);

    // Geração do VCD
    sc_trace_file *wf = sc_create_vcd_trace_file("regbank_waves");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, enable, "enable");
    sc_trace(wf, write, "write");
    sc_trace(wf, addressSource1, "addressSource1");
    sc_trace(wf, addressSource2, "addressSource2");
    sc_trace(wf, addressDest, "addressDest");
    sc_trace(wf, dataToWrite, "dataToWrite");
    sc_trace(wf, dataSource1, "dataSource1");
    sc_trace(wf, dataSource2, "dataSource2");

    // Inicialização
    clock = 0;
    enable = 1;
    write = 0;
    addressSource1 = 0;
    addressSource2 = 0;
    addressDest = 0;
    dataToWrite = 0;

    std::cout << "Register Bank testbench starting..." << std::endl;

    // Escrita em R1 e R2
    std::cout << "\n>> Writing 100 in R1" << std::endl;
    write = 1;
    addressDest = 1;
    dataToWrite = 100;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    std::cout << "\n>> Reading -55 from R2" << std::endl;
    addressDest = 2;
    dataToWrite = -55;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    // Leitura de R1 e R2
    std::cout << "\n>> Reading R1 and R2" << std::endl;
    write = 0;
    addressSource1 = 1;
    addressSource2 = 2;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    std::cout << "R1: " << dataSource1.read() << std::endl;
    std::cout << "R2: " << dataSource2.read() << std::endl;

    // Escrita em R10
    std::cout << "\n>> Writing 777 in R10" << std::endl;
    write = 1;
    addressDest = 10;
    dataToWrite = 777;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    // Leitura de R10
    std::cout << "\n>> Reading R10 and R0" << std::endl;
    write = 0;
    addressSource1 = 10;
    addressSource2 = 0;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    std::cout << "R10: " << dataSource1.read() << std::endl;
    std::cout << "R0: " << dataSource2.read() << std::endl;

    std::cout << "\nRegister Bank testbench completed." << std::endl;

    sc_close_vcd_trace_file(wf);
    return 0;
}
