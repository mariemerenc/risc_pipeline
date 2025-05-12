#include <systemc.h>
#include "IDEX.h"

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_signal<sc_uint<32>> pc_in, reg_data1_in, reg_data2_in, imm_ext_in;
    sc_signal<sc_uint<5>> rs_in, rt_in, rd_in;
    sc_signal<sc_uint<3>> alu_op_in;
    sc_signal<bool> alu_src_in, reg_dst_in, reg_write_in, mem_read_in, mem_write_in, mem_to_reg_in, branch_in;

    sc_signal<sc_uint<32>> pc_out, reg_data1_out, reg_data2_out, imm_ext_out;
    sc_signal<sc_uint<5>> rs_out, rt_out, rd_out;
    sc_signal<sc_uint<3>> alu_op_out;
    sc_signal<bool> alu_src_out, reg_dst_out, reg_write_out, mem_read_out, mem_write_out, mem_to_reg_out, branch_out;

    // Instância
    IDEX idex("IDEX");
    idex.pc_in(pc_in); idex.reg_data1_in(reg_data1_in); idex.reg_data2_in(reg_data2_in); idex.imm_ext_in(imm_ext_in);
    idex.rs_in(rs_in); idex.rt_in(rt_in); idex.rd_in(rd_in);
    idex.alu_op_in(alu_op_in); idex.alu_src_in(alu_src_in); idex.reg_dst_in(reg_dst_in);
    idex.reg_write_in(reg_write_in); idex.mem_read_in(mem_read_in); idex.mem_write_in(mem_write_in);
    idex.mem_to_reg_in(mem_to_reg_in); idex.branch_in(branch_in);

    idex.pc_out(pc_out); idex.reg_data1_out(reg_data1_out); idex.reg_data2_out(reg_data2_out); idex.imm_ext_out(imm_ext_out);
    idex.rs_out(rs_out); idex.rt_out(rt_out); idex.rd_out(rd_out);
    idex.alu_op_out(alu_op_out); idex.alu_src_out(alu_src_out); idex.reg_dst_out(reg_dst_out);
    idex.reg_write_out(reg_write_out); idex.mem_read_out(mem_read_out); idex.mem_write_out(mem_write_out);
    idex.mem_to_reg_out(mem_to_reg_out); idex.branch_out(branch_out);

    // Trace
    sc_trace_file *tf = sc_create_vcd_trace_file("idex_wave");
    sc_trace(tf, pc_in, "pc_in");
    sc_trace(tf, reg_data1_in, "reg_data1_in");
    sc_trace(tf, reg_data2_in, "reg_data2_in");
    sc_trace(tf, imm_ext_in, "imm_ext_in");
    sc_trace(tf, rs_in, "rs_in");
    sc_trace(tf, rt_in, "rt_in");
    sc_trace(tf, rd_in, "rd_in");
    sc_trace(tf, alu_op_in, "alu_op_in");
    sc_trace(tf, alu_src_in, "alu_src_in");
    sc_trace(tf, reg_dst_in, "reg_dst_in");
    sc_trace(tf, reg_write_in, "reg_write_in");
    sc_trace(tf, mem_read_in, "mem_read_in");
    sc_trace(tf, mem_write_in, "mem_write_in");
    sc_trace(tf, mem_to_reg_in, "mem_to_reg_in");
    sc_trace(tf, branch_in, "branch_in");

    // Estímulo
    pc_in = 0x00000004;
    reg_data1_in = 0x00000011;
    reg_data2_in = 0x00000022;
    imm_ext_in = 0x00000010;
    rs_in = 1;
    rt_in = 2;
    rd_in = 3;
    alu_op_in = 0b010;
    alu_src_in = 1;
    reg_dst_in = 1;
    reg_write_in = 1;
    mem_read_in = 0;
    mem_write_in = 0;
    mem_to_reg_in = 0;
    branch_in = 0;

    sc_start(10, SC_NS);

    sc_close_vcd_trace_file(tf);
    return 0;
}
