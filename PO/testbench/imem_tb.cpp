#include <systemc.h>
#include "imem.h"

/*
    Testbench para o módulo de memória de instruções (IMEM).
    Testa a leitura de instruções.
    Gera um arquivo VCD para visualização de waveforms.
    O arquivo VCD é gerado com o nome "imem_waves.vcd".
    O testbench executa as seguintes operações:
        1. Lê instruções de 0 a 4 e imprime os resultados.
        2. Fecha o arquivo VCD.
        3. Finaliza o testbench.
*/

int sc_main(int argc, char* argv[]) {
    //sinais
    sc_clock clock("clock", 10, SC_NS); 
    sc_signal<bool> imem_enable;
    sc_signal<bool> imem_write;
    sc_signal<sc_uint<32>> imem_address;
    sc_signal<sc_uint<32>> imem_instruction;

    //instâncias
    IMEM imem("IMEM");
    imem.clock(clock);
    imem.imem_enable(imem_enable);
    imem.imem_write(imem_write);
    imem.imem_address(imem_address);
    imem.imem_instruction(imem_instruction);

    for (int i = 0; i < IMEM_SIZE; i++) {
        imem.imem[i] = 0x1000 + i; //instruções fictícias 0x1000, 0x1001, ...
    }

    // tracefile para waveform
    sc_trace_file *tf = sc_create_vcd_trace_file("imem_waves");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clock, "clock");
    sc_trace(tf, imem_enable, "imem_enable");
    sc_trace(tf, imem_write, "imem_write");
    sc_trace(tf, imem_address, "imem_address");
    sc_trace(tf, imem_instruction, "imem_instruction");

    std::cout << "IMEM Testbench starting..." << std::endl;

    imem_enable = true;
    imem_write = false;

    //leitura de algumas instruções
    for (int i = 0; i < 5; ++i) {
        imem_address = i;
        sc_start(10, SC_NS); // espera um ciclo de clock
        std::cout << "[READ] Addr=" << i << " -> Instr=0x"
                  << std::hex << imem_instruction.read() << std::dec << std::endl;
    }

    sc_close_vcd_trace_file(tf);
    std::cout << "IMEM Testbench completed." << std::endl;

    return 0;
}
