#include "systemc.h"
#include "program_counter.h"

/*
    Testbench para o módulo ProgramCounter.
    
    Testa o funcionamento do contador de programa (PC).
    Gera um arquivo VCD para visualização de waveforms.
    O arquivo VCD é gerado com o nome "pc_wave.vcd".
    O testbench executa os seguintes testes:
        1. Reset do PC
        2. Incremento do PC
        3. Carregamento de um valor no PC
        4. Incremento após o carregamento
*/

int sc_main(int argc, char* argv[]) {
    sc_clock clock("clock", 10, SC_NS);

    sc_signal<bool> pc_reset;
    sc_signal<bool> pc_enable;
    sc_signal<bool> pc_load;
    sc_signal<sc_uint<8>> counterIn;
    sc_signal<sc_uint<8>> counterOut;

    ProgramCounter pc("ProgramCounter");
    pc.clock(clock);
    pc.pc_reset(pc_reset);
    pc.pc_enable(pc_enable);
    pc.pc_load(pc_load);
    pc.pc_in(counterIn);
    pc.pc_out(counterOut);

    sc_trace_file *tf = sc_create_vcd_trace_file("pc_trace");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clock, "clock");
    sc_trace(tf, pc_reset, "pc_reset");
    sc_trace(tf, pc_enable, "pc_enable");
    sc_trace(tf, pc_load, "pc_load");
    sc_trace(tf, counterIn, "pc_in");
    sc_trace(tf, counterOut, "pc_out");

    std::cout << "ProgramCounter testbench starting..." << std::endl;

    pc_reset.write(false);
    pc_enable.write(false);
    pc_load.write(false);
    counterIn.write(0);

    sc_start(10, SC_NS);

    pc_reset.write(true);
    sc_start(10, SC_NS);
    pc_reset.write(false);
    std::cout << "[RESET] pc_out = " << counterOut.read() << std::endl;

    // INCREMENTAR 3 vezes
    pc_enable.write(true);
    for (int i = 0; i < 3; ++i) {
        sc_start(10, SC_NS);
        std::cout << "[INCREMENT " << i+1 << "] pc_out = " << counterOut.read() << std::endl;
    }
    pc_enable.write(false);

    counterIn.write(100);
    pc_load.write(true);
    sc_start(10, SC_NS);
    pc_load.write(false);
    std::cout << "[LOAD 100] pc_out = " << counterOut.read() << std::endl;

    pc_enable.write(true);
    sc_start(10, SC_NS);
    pc_enable.write(false);
    std::cout << "[POST-LOAD INCREMENT] pc_out = " << counterOut.read() << std::endl;

    std::cout << "ProgramCounter testbench completed." << std::endl;
    sc_close_vcd_trace_file(tf);
    return 0;
}
