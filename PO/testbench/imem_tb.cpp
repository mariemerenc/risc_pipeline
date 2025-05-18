#include <systemc.h>
#include "imem.h"  // Inclua seu módulo IMEM com suporte a leitura e escrita

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_clock clock("clock", 10, SC_NS);
    sc_signal<bool> enable;
    sc_signal<bool> write;
    sc_signal<sc_uint<32>> address;
    sc_signal<sc_uint<32>> instruction;

    // Instância do módulo IMEM
    IMEM imem("IMEM");
    imem.clock(clock);
    imem.imem_enable(enable);
    imem.imem_write(write);
    imem.imem_address(address);
    imem.imem_instruction(instruction);

    // Arquivo VCD para GTKWave
    sc_trace_file* tf = sc_create_vcd_trace_file("imem_waves");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clock, "clock");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, write, "write");
    sc_trace(tf, address, "address");
    sc_trace(tf, instruction, "instruction");

    std::cout << "Starting IMEM testbench..." << std::endl;

    // Inicialização
    enable = true;
    write = true;
    address = 0;
    instruction = 0;

    // 1. Escreve 5 instruções fictícias nos endereços 0 a 4
    for (int i = 0; i < 5; ++i) {
        address = i;
        instruction = 0xA000 + i;
        sc_start(10, SC_NS);
        std::cout << "[WRITE] Addr=" << i << " <- Instr=0x"
                  << std::hex << instruction.read() << std::dec << std::endl;
    }

    // 2. Lê de volta os valores escritos
    write = false;
    for (int i = 0; i < 5; ++i) {
        address = i;
        sc_start(10, SC_NS);
        std::cout << "[READ] Addr=" << i << " -> Instr=0x"
                  << std::hex << instruction.read() << std::dec << std::endl;
    }

    // 3. Desabilita acesso à memória
    enable = false;
    address = 2;
    sc_start(10, SC_NS);
    std::cout << "[READ (enable=0)] Addr=2 -> Instr=0x"
              << std::hex << instruction.read() << std::dec << std::endl;

    std::cout << "IMEM testbench completed." << std::endl;
    sc_close_vcd_trace_file(tf);
    return 0;
}
