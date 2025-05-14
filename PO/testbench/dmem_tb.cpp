#include <systemc.h>
#include "dmem.h"

/*
    Testbench para a DMEM (Data Memory)
    Testa leitura e escrita na memória.
    Gera um arquivo VCD para visualização de waveforms.
    O arquivo VCD é gerado com o nome "dmem_wave.vcd".
    O testbench executa as seguintes operações:
        1. Escrever valor 42 no endereço 10
        2. Escrever valor -15 no endereço 20
        3. Ler do endereço 10
        4. Ler do endereço 20
        5. Tentar ler com enable desativado
*/

int sc_main(int argc, char* argv[]) {
    DMEM dmem("DMEM");

    sc_signal<bool> clock;
    sc_signal<bool> dmem_enable;
    sc_signal<bool> dmem_write;
    sc_signal<sc_uint<32>> dmem_address;
    sc_signal<sc_int<32>> dmem_dataIn;
    sc_signal<sc_int<32>> dmem_dataOut;

    dmem.clock(clock);
    dmem.dmem_enable(dmem_enable);
    dmem.dmem_write(dmem_write);
    dmem.dmem_address(dmem_address);
    dmem.dmem_dataIn(dmem_dataIn);
    dmem.dmem_dataOut(dmem_dataOut);

    sc_trace_file *wf = sc_create_vcd_trace_file("dmem_wave");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, dmem_enable, "enable");
    sc_trace(wf, dmem_write, "write");
    sc_trace(wf, dmem_address, "address");
    sc_trace(wf, dmem_dataIn, "dataIn");
    sc_trace(wf, dmem_dataOut, "dataOut");

    clock = 0;
    dmem_enable = 0;
    dmem_write = 0;
    dmem_address = 0;
    dmem_dataIn = 0;

    std::cout << "Starting DMEM testbench..." << std::endl;

    // 1. Escrever valor 42 no endereço 10
    dmem_enable = 1;
    dmem_write = 1;
    dmem_address = 10;
    dmem_dataIn = 42;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);

    // 2. Escrever valor -15 no endereço 20
    dmem_address = 20;
    dmem_dataIn = -15;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);

    // 3. Ler do endereço 10
    dmem_write = 0;
    dmem_address = 10;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);
    std::cout << "Read from address 10: " << dmem_dataOut.read() << std::endl;

    // 4. Ler do endereço 20
    dmem_address = 20;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);
    std::cout << "Read from address 20: " << dmem_dataOut.read() << std::endl;

    // 5. Tentar ler com enable desativado
    dmem_enable = 0;
    dmem_address = 10;

    clock = 1; sc_start(1, SC_NS); clock = 0; sc_start(1, SC_NS);
    std::cout << "Read from address 10 with enable = 0: " << dmem_dataOut.read() << std::endl;

    sc_close_vcd_trace_file(wf);
    std::cout << "DMEM testbench completed." << std::endl;

    return 0;
}
