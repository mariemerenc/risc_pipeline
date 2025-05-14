#include <systemc.h>
#include "regbank.h"

/*
    Testbench para o módulo RegBank.
    
    Testa a leitura e escrita em registradores.
    Gera um arquivo VCD para visualização de waveforms.
    O arquivo VCD é gerado com o nome "regbank_waves.vcd".
    O testbench executa os seguintes testes:
        1. Escrita em R1 e R2
        2. Leitura de R1 e R2
        3. Escrita em R10
        4. Leitura de R10 e R0
*/

int sc_main(int argc, char* argv[]) {
    // Instanciação do módulo
    RegBank regbank("RegBank");

    // Sinais
    sc_signal<bool> clock;
    sc_signal<bool> regbank_enable;
    sc_signal<bool> regbank_write;
    sc_signal<sc_uint<5>> read_address1;
    sc_signal<sc_uint<5>> read_address2;
    sc_signal<sc_uint<5>> write_address;
    sc_signal<sc_int<32>> write_data;
    sc_signal<sc_int<32>> read_data1;
    sc_signal<sc_int<32>> read_data2;

    // Conexão dos sinais
    regbank.clock(clock);
    regbank.regbank_enable(regbank_enable);
    regbank.regbank_write(regbank_write);
    regbank.read_address1(read_address1);
    regbank.read_address2(read_address2);
    regbank.write_address(write_address);
    regbank.write_data(write_data);
    regbank.read_data1(read_data1);
    regbank.read_data2(read_data2);

    // Geração do VCD
    sc_trace_file *wf = sc_create_vcd_trace_file("regbank_waves");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, regbank_enable, "regbank_enable");
    sc_trace(wf, regbank_write, "regbank_write");
    sc_trace(wf, read_address1, "read_address1");
    sc_trace(wf, read_address2, "read_address2");
    sc_trace(wf, write_address, "write_address");
    sc_trace(wf, write_data, "write_data");
    sc_trace(wf, read_data1, "read_data1");
    sc_trace(wf, read_data2, "read_data2");

    // Inicialização
    clock = 0;
    regbank_enable = 1;
    regbank_write = 0;
    read_address1 = 0;
    read_address2 = 0;
    write_address = 0;
    write_data = 0;

    std::cout << "Register Bank testbench starting..." << std::endl;

    // Escrita em R1 e R2
    std::cout << "\n>> Writing 100 in R1" << std::endl;
    regbank_write = 1;
    write_address = 1;
    write_data = 100;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    std::cout << "\n>> Reading -55 from R2" << std::endl;
    write_address = 2;
    write_data = -55;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    // Leitura de R1 e R2
    std::cout << "\n>> Reading R1 and R2" << std::endl;
    regbank_write = 0;
    read_address1 = 1;
    read_address2 = 2;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    std::cout << "R1: " << read_data1.read() << std::endl;
    std::cout << "R2: " << read_data2.read() << std::endl;

    // Escrita em R10
    std::cout << "\n>> Writing 777 in R10" << std::endl;
    regbank_write = 1;
    write_address = 10;
    write_data = 777;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    // Leitura de R10
    std::cout << "\n>> Reading R10 and R0" << std::endl;
    regbank_write = 0;
    read_address1 = 10;
    read_address2 = 0;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);

    std::cout << "R10: " << read_data1.read() << std::endl;
    std::cout << "R0: " << read_data2.read() << std::endl;

    std::cout << "\nRegister Bank testbench completed." << std::endl;

    sc_close_vcd_trace_file(wf);
    return 0;
}
