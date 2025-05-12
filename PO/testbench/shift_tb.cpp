#include <systemc.h>
#include "shift.h"

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_signal<sc_uint<32>> in_sig;
    sc_signal<sc_uint<5>> shift_amt_sig;
    sc_signal<bool> dir_sig;
    sc_signal<sc_uint<32>> out_sig;

    // Instanciação
    Shift shift("shift");
    shift.in(in_sig);
    shift.shift_amount(shift_amt_sig);
    shift.shift_dir(dir_sig);
    shift.out(out_sig);

    // VCD trace
    sc_trace_file* tf = sc_create_vcd_trace_file("shift_wave");
    sc_trace(tf, in_sig, "in");
    sc_trace(tf, shift_amt_sig, "shift_amount");
    sc_trace(tf, dir_sig, "shift_dir");
    sc_trace(tf, out_sig, "out");

    std::cout << "Starting SHIFT testbench..." << std::endl;

    // Teste 1: desloca para a esquerda
    in_sig.write(0x00000001);
    shift_amt_sig.write(2);
    dir_sig.write(0); // esquerda
    sc_start(1, SC_NS);
    std::cout << "Shift left: in = 1, amount = 2 -> out = " << out_sig.read() << std::endl;

    // Teste 2: desloca para a direita
    in_sig.write(0x00000008);
    shift_amt_sig.write(3);
    dir_sig.write(1); // direita
    sc_start(1, SC_NS);
    std::cout << "Shift right: in = 8, amount = 3 -> out = " << out_sig.read() << std::endl;

    // Teste 3: deslocamento zero
    in_sig.write(0xF0000000);
    shift_amt_sig.write(0);
    dir_sig.write(0); // esquerda
    sc_start(1, SC_NS);
    std::cout << "No shift (left 0): in = F0000000 -> out = " << out_sig.read() << std::endl;

    sc_close_vcd_trace_file(tf);
    std::cout << "SHIFT testbench completed." << std::endl;

    return 0;
}
