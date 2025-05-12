#include <systemc.h>
#include "adder.h"

int sc_main(int argc, char* argv[]) {
    std::cout << "Starting ADDER testbench..." << std::endl;

    // Sinais
    sc_signal<sc_uint<32>> a_sig, b_sig, sum_sig;

    // Instância do módulo
    Adder adder("adder");
    adder.a(a_sig);
    adder.b(b_sig);
    adder.sum(sum_sig);

    // Geração de waveform
    sc_trace_file *wf = sc_create_vcd_trace_file("adder_wave");
    sc_trace(wf, a_sig, "a");
    sc_trace(wf, b_sig, "b");
    sc_trace(wf, sum_sig, "sum");

    // Teste 1
    a_sig.write(10);
    b_sig.write(15);
    sc_start(1, SC_NS);
    std::cout << "a = 10, b = 15 -> sum = " << sum_sig.read() << std::endl;

    // Teste 2
    a_sig.write(100);
    b_sig.write(200);
    sc_start(1, SC_NS);
    std::cout << "a = 100, b = 200 -> sum = " << sum_sig.read() << std::endl;

    // Teste 3
    a_sig.write(0xFFFFFFFF);
    b_sig.write(1);
    sc_start(1, SC_NS);
    std::cout << "a = 0xFFFFFFFF, b = 1 -> sum = " << sum_sig.read() << std::endl;

    sc_close_vcd_trace_file(wf);
    std::cout << "ADDER testbench completed." << std::endl;
    return 0;
}
