#include <systemc.h>
#include "EXMEM.h"

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_signal<sc_uint<32>> alu_result_in, pc_branch_in, reg_data2_in;
    sc_signal<sc_uint<5>> reg_dst_in;
    sc_signal<bool> zero_in, reg_write_in, mem_read_in, mem_write_in, mem_to_reg_in, branch_in;

    sc_signal<sc_uint<32>> alu_result_out, pc_branch_out, reg_data2_out;
    sc_signal<sc_uint<5>> reg_dst_out;
    sc_signal<bool> zero_out, reg_write_out, mem_read_out, mem_write_out, mem_to_reg_out, branch_out;

    // Instância
    EXMEM exmem("EXMEM");
    exmem.alu_result_in(alu_result_in); exmem.pc_branch_in(pc_branch_in); exmem.reg_data2_in(reg_data2_in);
    exmem.reg_dst_in(reg_dst_in); exmem.zero_in(zero_in); exmem.reg_write_in(reg_write_in);
    exmem.mem_read_in(mem_read_in); exmem.mem_write_in(mem_write_in); exmem.mem_to_reg_in(mem_to_reg_in);
    exmem.branch_in(branch_in);

    exmem.alu_result_out(alu_result_out); exmem.pc_branch_out(pc_branch_out); exmem.reg_data2_out(reg_data2_out);
    exmem.reg_dst_out(reg_dst_out); exmem.zero_out(zero_out); exmem.reg_write_out(reg_write_out);
    exmem.mem_read_out(mem_read_out); exmem.mem_write_out(mem_write_out); exmem.mem_to_reg_out(mem_to_reg_out);
    exmem.branch_out(branch_out);

    // Trace
    sc_trace_file *tf = sc_create_vcd_trace_file("exmem_wave");
    sc_trace(tf, alu_result_in, "alu_result_in");
    sc_trace(tf, pc_branch_in, "pc_branch_in");
    sc_trace(tf, reg_data2_in, "reg_data2_in");
    sc_trace(tf, reg_dst_in, "reg_dst_in");
    sc_trace(tf, zero_in, "zero_in");
    sc_trace(tf, reg_write_in, "reg_write_in");
    sc_trace(tf, mem_read_in, "mem_read_in");
    sc_trace(tf, mem_write_in, "mem_write_in");
    sc_trace(tf, mem_to_reg_in, "mem_to_reg_in");
    sc_trace(tf, branch_in, "branch_in");

    // Estímulo
    alu_result_in = 0x00000040;
    pc_branch_in = 0x00000080;
    reg_data2_in = 0x12345678;
    reg_dst_in = 10;
    zero_in = false;
    reg_write_in = true;
    mem_read_in = true;
    mem_write_in = false;
    mem_to_reg_in = true;
    branch_in = false;

    sc_start(10, SC_NS);

    sc_close_vcd_trace_file(tf);
    return 0;
}
