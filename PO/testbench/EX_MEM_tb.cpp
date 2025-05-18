#include <systemc.h>
#include "EX_MEM.h"

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_clock clock("clock", 10, SC_NS);
    sc_signal<bool> reset, enable;
    sc_signal<sc_uint<32>> pc_in;
    sc_signal<sc_int<32>> alu_result_in, rs2_data_in;
    sc_signal<sc_uint<5>> rd_in;
    sc_signal<bool> memRead_in, memWrite_in, regWrite_in, memToReg_in;

    sc_signal<sc_uint<32>> pc_out;
    sc_signal<sc_int<32>> alu_result_out, rs2_data_out;
    sc_signal<sc_uint<5>> rd_out;
    sc_signal<bool> memRead_out, memWrite_out, regWrite_out, memToReg_out;

    // Instância
    EX_MEM ex_mem("EX_MEM");
    ex_mem.clock(clock);
    ex_mem.reset(reset);
    ex_mem.enable(enable);
    ex_mem.pc_in(pc_in);
    ex_mem.alu_result_in(alu_result_in);
    ex_mem.rs2_data_in(rs2_data_in);
    ex_mem.rd_in(rd_in);
    ex_mem.memRead_in(memRead_in);
    ex_mem.memWrite_in(memWrite_in);
    ex_mem.regWrite_in(regWrite_in);
    ex_mem.memToReg_in(memToReg_in);
    ex_mem.pc_out(pc_out);
    ex_mem.alu_result_out(alu_result_out);
    ex_mem.rs2_data_out(rs2_data_out);
    ex_mem.rd_out(rd_out);
    ex_mem.memRead_out(memRead_out);
    ex_mem.memWrite_out(memWrite_out);
    ex_mem.regWrite_out(regWrite_out);
    ex_mem.memToReg_out(memToReg_out);

    // Trace
    sc_trace_file *tf = sc_create_vcd_trace_file("ex_mem_wave");
    sc_trace(tf, clock, "clock");
    sc_trace(tf, reset, "reset");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, pc_in, "pc_in");
    sc_trace(tf, alu_result_in, "alu_result_in");
    sc_trace(tf, rs2_data_in, "rs2_data_in");
    sc_trace(tf, rd_in, "rd_in");
    sc_trace(tf, memRead_in, "memRead_in");
    sc_trace(tf, memWrite_in, "memWrite_in");
    sc_trace(tf, regWrite_in, "regWrite_in");
    sc_trace(tf, memToReg_in, "memToReg_in");

    sc_trace(tf, pc_out, "pc_out");
    sc_trace(tf, alu_result_out, "alu_result_out");
    sc_trace(tf, rs2_data_out, "rs2_data_out");
    sc_trace(tf, rd_out, "rd_out");
    sc_trace(tf, memRead_out, "memRead_out");
    sc_trace(tf, memWrite_out, "memWrite_out");
    sc_trace(tf, regWrite_out, "regWrite_out");
    sc_trace(tf, memToReg_out, "memToReg_out");

    std::cout << "== Iniciando testbench do EX_MEM ==" << std::endl;

    reset = true;
    enable = true;
    sc_start(10, SC_NS);
    reset = false;

    // Estímulo
    pc_in = 200;
    alu_result_in = 42;
    rs2_data_in = -15;
    rd_in = 10;
    memRead_in = true;
    memWrite_in = false;
    regWrite_in = true;
    memToReg_in = true;

    for (int i = 0; i < 3; i++) {
        sc_start(10, SC_NS);
    }

    std::cout << "== Testbench finalizado ==" << std::endl;
    sc_close_vcd_trace_file(tf);
    return 0;
}
