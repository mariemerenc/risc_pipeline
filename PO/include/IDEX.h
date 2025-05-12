#ifndef IDEX_H
#define IDEX_H

#include "systemc.h"

SC_MODULE(IDEX) {
    sc_in<sc_uint<32>> pc_in, reg_data1_in, reg_data2_in, imm_ext_in;
    sc_in<sc_uint<5>> rs_in, rt_in, rd_in;
    sc_in<sc_uint<3>> alu_op_in;
    sc_in<bool> alu_src_in, reg_dst_in, reg_write_in, mem_read_in, mem_write_in, mem_to_reg_in, branch_in;

    sc_out<sc_uint<32>> pc_out, reg_data1_out, reg_data2_out, imm_ext_out;
    sc_out<sc_uint<5>> rs_out, rt_out, rd_out;
    sc_out<sc_uint<3>> alu_op_out;
    sc_out<bool> alu_src_out, reg_dst_out, reg_write_out, mem_read_out, mem_write_out, mem_to_reg_out, branch_out;

    void process() {
        pc_out.write(pc_in.read());
        reg_data1_out.write(reg_data1_in.read());
        reg_data2_out.write(reg_data2_in.read());
        imm_ext_out.write(imm_ext_in.read());
        rs_out.write(rs_in.read());
        rt_out.write(rt_in.read());
        rd_out.write(rd_in.read());
        alu_op_out.write(alu_op_in.read());
        alu_src_out.write(alu_src_in.read());
        reg_dst_out.write(reg_dst_in.read());
        reg_write_out.write(reg_write_in.read());
        mem_read_out.write(mem_read_in.read());
        mem_write_out.write(mem_write_in.read());
        mem_to_reg_out.write(mem_to_reg_in.read());
        branch_out.write(branch_in.read());
    }

    SC_CTOR(IDEX) {
        SC_METHOD(process);
        sensitive << pc_in << reg_data1_in << reg_data2_in << imm_ext_in
                  << rs_in << rt_in << rd_in << alu_op_in << alu_src_in
                  << reg_dst_in << reg_write_in << mem_read_in
                  << mem_write_in << mem_to_reg_in << branch_in;
    }
};

#endif
