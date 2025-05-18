#include <systemc.h>
#include "MEM_WB.h"

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_clock clock("clock", 10, SC_NS);
    sc_signal<bool> reset, enable;
    sc_signal<sc_int<32>> pc_in;
    sc_signal<sc_int<32>> mem_data_in, alu_result_in;
    sc_signal<sc_int<5>> rd_in;
    sc_signal<bool> regWrite_in, memToReg_in;

    sc_signal<sc_int<32>> pc_out;
    sc_signal<sc_int<32>> mem_data_out, alu_result_out;
    sc_signal<sc_int<5>> rd_out;
    sc_signal<bool> regWrite_out, memToReg_out;

    // Instância
    MEM_WB mem_wb("MEM_WB");
    mem_wb.clock(clock);
    mem_wb.reset(reset);
    mem_wb.enable(enable);
    mem_wb.pc_in(pc_in);
    mem_wb.mem_data_in(mem_data_in);
    mem_wb.alu_result_in(alu_result_in);
    mem_wb.rd_in(rd_in);
    mem_wb.regWrite_in(regWrite_in);
    mem_wb.memToReg_in(memToReg_in);
    mem_wb.pc_out(pc_out);
    mem_wb.mem_data_out(mem_data_out);
    mem_wb.alu_result_out(alu_result_out);
    mem_wb.rd_out(rd_out);
    mem_wb.regWrite_out(regWrite_out);
    mem_wb.memToReg_out(memToReg_out);

    // Trace
    sc_trace_file* tf = sc_create_vcd_trace_file("mem_wb_wave");
    sc_trace(tf, clock, "clock");
    sc_trace(tf, reset, "reset");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, pc_in, "pc_in");
    sc_trace(tf, mem_data_in, "mem_data_in");
    sc_trace(tf, alu_result_in, "alu_result_in");
    sc_trace(tf, rd_in, "rd_in");
    sc_trace(tf, regWrite_in, "regWrite_in");
    sc_trace(tf, memToReg_in, "memToReg_in");

    sc_trace(tf, pc_out, "pc_out");
    sc_trace(tf, mem_data_out, "mem_data_out");
    sc_trace(tf, alu_result_out, "alu_result_out");
    sc_trace(tf, rd_out, "rd_out");
    sc_trace(tf, regWrite_out, "regWrite_out");
    sc_trace(tf, memToReg_out, "memToReg_out");

    std::cout << "== Iniciando testbench do MEM_WB ==" << std::endl;

    // Reset inicial
    reset = true;
    enable = true;
    sc_start(10, SC_NS);
    reset = false;

    // Estímulos
    pc_in = 300;
    mem_data_in = 99;
    alu_result_in = 123;
    rd_in = 5;
    regWrite_in = true;
    memToReg_in = true;

    for (int i = 0; i < 3; i++) {
        sc_start(10, SC_NS);
    }

    std::cout << "== Testbench finalizado ==" << std::endl;
    sc_close_vcd_trace_file(tf);
    return 0;
}
