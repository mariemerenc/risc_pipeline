#include <systemc.h>
#include "MEMWB.h"

int sc_main(int argc, char* argv[]) {
    // Sinais
    sc_signal<sc_uint<32>> mem_data_in, alu_result_in;
    sc_signal<sc_uint<5>> write_reg_in;
    sc_signal<bool> reg_write_in, mem_to_reg_in;

    sc_signal<sc_uint<32>> mem_data_out, alu_result_out;
    sc_signal<sc_uint<5>> write_reg_out;
    sc_signal<bool> reg_write_out, mem_to_reg_out;

    // Instância
    MEMWB memwb("MEMWB");
    memwb.mem_data_in(mem_data_in); memwb.alu_result_in(alu_result_in); memwb.write_reg_in(write_reg_in);
    memwb.reg_write_in(reg_write_in); memwb.mem_to_reg_in(mem_to_reg_in);

    memwb.mem_data_out(mem_data_out); memwb.alu_result_out(alu_result_out); memwb.write_reg_out(write_reg_out);
    memwb.reg_write_out(reg_write_out); memwb.mem_to_reg_out(mem_to_reg_out);

    // Trace
    sc_trace_file *tf = sc_create_vcd_trace_file("memwb_wave");
    sc_trace(tf, mem_data_in, "mem_data_in");
    sc_trace(tf, alu_result_in, "alu_result_in");
    sc_trace(tf, write_reg_in, "write_reg_in");
    sc_trace(tf, reg_write_in, "reg_write_in");
    sc_trace(tf, mem_to_reg_in, "mem_to_reg_in");

    // Estímulo
    mem_data_in = 0xABCD1234;
    alu_result_in = 0x56781234;
    write_reg_in = 7;
    reg_write_in = true;
    mem_to_reg_in = false;

    sc_start(10, SC_NS);

    sc_close_vcd_trace_file(tf);
    return 0;
}
