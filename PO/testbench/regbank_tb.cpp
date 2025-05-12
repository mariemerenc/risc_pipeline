#include <systemc.h>
#include "regbank.h"

int sc_main(int argc, char* argv[]) {
    RegBank regbank("RegBank");

    sc_signal<bool> clock;
    sc_signal<bool> enable;
    sc_signal<bool> write;
    sc_signal<sc_uint<5>> addressSource1;
    sc_signal<sc_uint<5>> addressSource2;
    sc_signal<sc_uint<5>> addressDest;
    sc_signal<sc_int<32>> dataToWrite;
    sc_signal<sc_int<32>> dataSource1;
    sc_signal<sc_int<32>> dataSource2;

    regbank.clock(clock);
    regbank.enable(enable);
    regbank.write(write);
    regbank.addressSource1(addressSource1);
    regbank.addressSource2(addressSource2);
    regbank.addressDest(addressDest);
    regbank.dataToWrite(dataToWrite);
    regbank.dataSource1(dataSource1);
    regbank.dataSource2(dataSource2);

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

    std::cout << "RegisterBank testbench starting..." << std::endl;

    clock = 0;
    enable = 1;
    write = 0;
    addressSource1 = 0;
    addressSource2 = 1;
    addressDest = 0;
    dataToWrite = 0;

    
    for (int i = 0; i < 10; ++i) {
        // Escreve valores nos registradores 1 e 2
        if (i == 1) {
            write = 1;
            addressDest = 1;
            dataToWrite = 42;
        } else if (i == 2) {
            addressDest = 2;
            dataToWrite = -17;
        } else {
            write = 0; // Desliga escrita
        }

        // Leitura de R1 e R2 no ciclo 5
        if (i == 5) {
            addressSource1 = 1;
            addressSource2 = 2;
        }

        // Clock flanco de subida
        clock = 1;
        sc_start(1, SC_NS);
        clock = 0;
        sc_start(1, SC_NS);
    }

    std::cout << "RegisterBank testbench completed." << std::endl;
    sc_close_vcd_trace_file(wf);
    return 0;
}