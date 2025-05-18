#include <systemc.h>
#include "ID_EX.h"

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_clock clock("clock", 10, SC_NS);
    sc_signal<bool> reset, enable;
    sc_signal<sc_uint<32>> pc_in;
    sc_signal<sc_int<32>> rs1_in, rs2_in, imm_in;
    sc_signal<sc_uint<5>> rd_in;
    sc_signal<sc_uint<4>> aluOp_in;
    sc_signal<bool> aluSrc_in, regWrite_in;

    sc_signal<sc_uint<32>> pc_out;
    sc_signal<sc_int<32>> rs1_out, rs2_out, imm_out;
    sc_signal<sc_uint<5>> rd_out;
    sc_signal<sc_uint<4>> aluOp_out;
    sc_signal<bool> aluSrc_out, regWrite_out;

    // Instância
    ID_EX id_ex("ID_EX");
    id_ex.clock(clock);
    id_ex.reset(reset);
    id_ex.enable(enable);
    id_ex.pc_in(pc_in);
    id_ex.rs1_in(rs1_in);
    id_ex.rs2_in(rs2_in);
    id_ex.imm_in(imm_in);
    id_ex.rd_in(rd_in);
    id_ex.aluOp_in(aluOp_in);
    id_ex.aluSrc_in(aluSrc_in);
    id_ex.regWrite_in(regWrite_in);

    id_ex.pc_out(pc_out);
    id_ex.rs1_out(rs1_out);
    id_ex.rs2_out(rs2_out);
    id_ex.imm_out(imm_out);
    id_ex.rd_out(rd_out);
    id_ex.aluOp_out(aluOp_out);
    id_ex.aluSrc_out(aluSrc_out);
    id_ex.regWrite_out(regWrite_out);

    // Waveform
    sc_trace_file* tf = sc_create_vcd_trace_file("id_ex_wave");
    sc_trace(tf, clock, "clock");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, reset, "reset");
    sc_trace(tf, pc_in, "pc_in");
    sc_trace(tf, rs1_in, "rs1_in");
    sc_trace(tf, rs2_in, "rs2_in");
    sc_trace(tf, imm_in, "imm_in");
    sc_trace(tf, rd_in, "rd_in");
    sc_trace(tf, aluOp_in, "aluOp_in");
    sc_trace(tf, aluSrc_in, "aluSrc_in");
    sc_trace(tf, regWrite_in, "regWrite_in");
    sc_trace(tf, pc_out, "pc_out");
    sc_trace(tf, rs1_out, "rs1_out");
    sc_trace(tf, rs2_out, "rs2_out");
    sc_trace(tf, imm_out, "imm_out");
    sc_trace(tf, rd_out, "rd_out");
    sc_trace(tf, aluOp_out, "aluOp_out");
    sc_trace(tf, aluSrc_out, "aluSrc_out");
    sc_trace(tf, regWrite_out, "regWrite_out");

    std::cout << "Iniciando testbench do ID_EX..." << std::endl;

    reset = true;
    enable = true;
    sc_start(10, SC_NS);
    reset = false;

    // Estímulo de entrada
    pc_in = 100;
    rs1_in = 10;
    rs2_in = 20;
    imm_in = 4;
    rd_in = 3;
    aluOp_in = 5;
    aluSrc_in = true;
    regWrite_in = true;

    for (int i = 0; i < 3; ++i) {
        sc_start(10, SC_NS);
    }

    std::cout << "Finalizando testbench do ID_EX." << std::endl;
    sc_close_vcd_trace_file(tf);
    return 0;
}
