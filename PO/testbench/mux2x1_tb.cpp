#include <systemc.h>
#include "mux2x1.h"

/*
    Testbench para o módulo Mux2x1.
    
    Testa a seleção entre dois sinais de entrada.
    Gera um arquivo VCD para visualização de waveforms.
    O arquivo VCD é gerado com o nome "mux_wave.vcd".
    O testbench executa dois testes:
        1. Seleção do primeiro sinal de entrada
        2. Seleção do segundo sinal de entrada
*/

int sc_main(int argc, char* argv[]) {
    // Signals
    sc_signal<sc_uint<32>> mux_in1, mux_in2, mux_out;
    sc_signal<bool> mux_sel;

    // Mux instance
    Mux2x1 mux("MUX");
    mux.mux_in1(mux_in1);
    mux.mux_in2(mux_in2);
    mux.mux_sel(mux_sel);
    mux.mux_out(mux_out);

    // VCD dump
    sc_trace_file *wf = sc_create_vcd_trace_file("mux_wave");
    sc_trace(wf, mux_in1, "mux_in1");
    sc_trace(wf, mux_in2, "mux_in2");
    sc_trace(wf, mux_sel, "mux_sel");
    sc_trace(wf, mux_out, "mux_out");

    std::cout << "Mux 2x1 testbench starting..." << std::endl;

    // Test
    mux_in1 = 10;
    mux_in2 = 20;

    mux_sel = 0;
    sc_start(1, SC_NS);
    std::cout << "Input 1: " << mux_in1.read() << std::endl;
    std::cout << "Input 2: " << mux_in2.read() << std::endl;
    std::cout << "mux_sel = 0 -> out = " << mux_out.read() << std::endl;

    mux_sel = 1;
    sc_start(1, SC_NS);
    std::cout << "mux_sel = 1 -> out = " << mux_out.read() << std::endl;

    std::cout << "Mux 2x1 testbench completed." << std::endl;
    sc_close_vcd_trace_file(wf);
    return 0;
}
