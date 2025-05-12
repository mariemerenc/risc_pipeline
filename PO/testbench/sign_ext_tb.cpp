#include <systemc.h>
#include "sign_ext.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_uint<32>> in_sig;
    sc_signal<sc_int<32>> out_sig;

    // Instanciando o módulo
    SignExtend sign_ext("SIGN_EXT");
    sign_ext.in(in_sig);
    sign_ext.out(out_sig);

    // Gerando VCD
    sc_trace_file* tf = sc_create_vcd_trace_file("sign_ext_wave");
    tf->set_time_unit(1, SC_PS); // 1ps de resolução

    // Sinais que serão rastreados
    sc_trace(tf, in_sig, "in");
    sc_trace(tf, out_sig, "out");

    std::cout << "Starting SIGN EXTEND testbench..." << std::endl;

    // Estímulo 1: valor positivo pequeno
    in_sig.write(0x0000000F); // 15
    sc_start(10, SC_NS);
    std::cout << "Input = 0x0000000F -> Output = " << out_sig.read() << std::endl;

    // Estímulo 2: valor negativo simulado (bit 15 = 1)
    in_sig.write(0x00008000); // bit 15 = 1
    sc_start(10, SC_NS);
    std::cout << "Input = 0x00008000 -> Output = " << out_sig.read() << std::endl;

    // Estímulo 3: valor máximo de 16 bits
    in_sig.write(0x0000FFFF);
    sc_start(10, SC_NS);
    std::cout << "Input = 0x0000FFFF -> Output = " << out_sig.read() << std::endl;

    std::cout << "SIGN EXTEND testbench completed." << std::endl;

    sc_close_vcd_trace_file(tf);
    return 0;
}
