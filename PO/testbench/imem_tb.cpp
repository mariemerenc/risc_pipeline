#include <systemc.h>
#include "imem.h"

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_clock clock("clock", 10, SC_NS);  // Clock de 10ns
    sc_signal<bool> enable;
    sc_signal<bool> write;
    sc_signal<sc_uint<32>> address;
    sc_signal<sc_uint<32>> instruction;

    // Instância do módulo
    IMEM imem("IMEM");
    imem.clock(clock);
    imem.enable(enable);
    imem.write(write);
    imem.address(address);
    imem.instruction(instruction);

    // Inicialização manual da memória de instruções
    for (int i = 0; i < IMEM_SIZE; i++) {
        imem.imem[i] = 0x1000 + i; // Ex: instruções fictícias 0x1000, 0x1001, ...
    }

    // Tracefile para waveform
    sc_trace_file *tf = sc_create_vcd_trace_file("imem_waves");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clock, "clock");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, write, "write");
    sc_trace(tf, address, "address");
    sc_trace(tf, instruction, "instruction");

    std::cout << "IMEM Testbench starting..." << std::endl;

    enable = true;
    write = false;

    // Simula leitura de algumas instruções
    for (int i = 0; i < 5; ++i) {
        address = i;
        sc_start(10, SC_NS); // Espera um ciclo de clock
        std::cout << "[READ] Addr=" << i << " -> Instr=0x"
                  << std::hex << instruction.read() << std::dec << std::endl;
    }

    sc_close_vcd_trace_file(tf);
    std::cout << "IMEM Testbench completed." << std::endl;

    return 0;
}
