#include <systemc.h>

#include "PO/include/program_counter.h"
#include "PO/include/adder.h"
#include "PO/include/mux2x1.h"
#include "PO/include/imem.h"
#include "PO/include/IF_ID.h"
#include "PO/include/regbank.h"
#include "PO/include/sign_ext.h"
#include "PO/include/ID_EX.h"
#include "PO/include/shift.h"
#include "PO/include/alu.h"
#include "PO/include/EX_MEM.h"
#include "PO/include/dmem.h"
#include "PO/include/MEM_WB.h"
#include "PC/include/control_unit.h"

int sc_main(int argc, char* argv[]) {
    sc_clock clock("clock", 10, SC_NS);
    sc_signal<bool> reset, pc_enable, pc_load;
    sc_signal<sc_int<32>> instruction;
    sc_signal<sc_int<32>> pc_in, pc_out;

    // Estágio IF
    ProgramCounter pc("ProgramCounter");
    sc_signal<sc_int<32>> pc_next;
    pc.clock(clock);
    pc.pc_reset(reset);
    pc.pc_enable(pc_enable);
    pc.pc_load(pc_load);
    pc.pc_in(pc_next);
    pc.pc_out(pc_out);

    Adder pc_adder("AdderPC");
    sc_signal<sc_int<32>> pc_ext, pc_plus4;
    pc_adder.a(pc_ext);
    pc_adder.b(sc_signal<sc_int<32>>("const_4", 4));
    pc_adder.sum(pc_plus4);

    IMEM imem("InstructionMemory");
    sc_signal<bool> imem_en, imem_wr;
    sc_signal<sc_int<32>> imem_data;
    imem.clock(clock);
    imem.imem_enable(imem_en);
    imem.imem_write(imem_wr);
    imem.imem_address(pc_ext);
    imem.imem_instruction(imem_data);

    // IF/ID
    IF_ID ifid("IF_ID");
    sc_signal<bool> ifid_en, ifid_reset;
    sc_signal<sc_int<32>> ifid_pc, ifid_instr;
    ifid.clock(clock);
    ifid.enable(ifid_en);
    ifid.reset(ifid_reset);
    ifid.pc_in(pc_plus4);
    ifid.instruction_in(imem_data);
    ifid.pc_out(ifid_pc);
    ifid.instruction_out(ifid_instr);

    // Controle
    ControlUnit cu("ControlUnit");
    sc_signal<sc_uint<4>> opcode;
    sc_signal<bool> regWrite, memRead, memWrite, aluSrc, memToReg, regDst, branch, jump;
    sc_signal<sc_int<4>> aluOp;
    sc_signal<bool> flagZ, flagN;
    opcode.write((ifid_instr.read().range(31, 28)).to_uint());
    cu.opcode(opcode);
    cu.flagN(flagN);
    cu.flagZ(flagZ);
    cu.regWrite(regWrite);
    cu.memRead(memRead);
    cu.memWrite(memWrite);
    cu.aluSrc(aluSrc);
    cu.memToReg(memToReg);
    cu.regDst(regDst);
    cu.branch(branch);
    cu.jump(jump);
    cu.aluOp(aluOp);

    // Banco de registradores
    RegBank regbank("RegBank");
    sc_signal<sc_int<5>> rs1, rs2, rd;
    sc_signal<sc_int<32>> reg_data1, reg_data2;
    sc_signal<sc_int<32>> wb_data;
    regbank.clock(clock);
    regbank.regbank_enable(sc_signal<bool>("regbank_en", true));
    regbank.regbank_write(regWrite);
    regbank.read_address1(rs1);
    regbank.read_address2(rs2);
    regbank.write_address(rd);
    regbank.write_data(wb_data);
    regbank.read_data1(reg_data1);
    regbank.read_data2(reg_data2);

    // Sign extend
    SignExtend sext("SignExt");
    sc_signal<sc_int<32>> imm_ext;
    sext.sign_ext_in(ifid_instr);
    sext.sign_ext_out(imm_ext);

    // ID/EX
    ID_EX idex("ID_EX");
    sc_signal<sc_int<4>> aluOp_idex;
    sc_signal<bool> aluSrc_idex, regWrite_idex;
    sc_signal<sc_int<5>> rd_idex;
    sc_signal<sc_int<32>> rs1_idex, rs2_idex, imm_idex;
    sc_signal<sc_int<32>> pc_idex;
    idex.clock(clock);
    idex.enable(sc_signal<bool>("idex_en", true));
    idex.reset(sc_signal<bool>("idex_rst", false));
    idex.pc_in(ifid_pc);
    idex.rs1_in(reg_data1);
    idex.rs2_in(reg_data2);
    idex.imm_in(imm_ext);
    idex.rd_in(rd);
    idex.aluOp_in(aluOp);
    idex.aluSrc_in(aluSrc);
    idex.regWrite_in(regWrite);
    idex.pc_out(pc_idex);
    idex.rs1_out(rs1_idex);
    idex.rs2_out(rs2_idex);
    idex.imm_out(imm_idex);
    idex.rd_out(rd_idex);
    idex.aluOp_out(aluOp_idex);
    idex.aluSrc_out(aluSrc_idex);
    idex.regWrite_out(regWrite_idex);

    // ALU
    ALU alu("ALU");
    sc_signal<sc_int<32>> alu_in2, alu_out;
    alu.alu_in1(rs1_idex);
    alu.alu_in2(alu_in2);
    alu.alu_op(aluOp_idex);
    alu.alu_out(alu_out);
    alu.alu_Z(flagZ);
    alu.alu_N(flagN);

    // Mux ALU
    Mux2x1 mux_alu("MuxALU");
    mux_alu.mux_in1(rs2_idex);
    mux_alu.mux_in2(imm_idex);
    mux_alu.mux_sel(aluSrc_idex);
    mux_alu.mux_out(alu_in2);

    // EX/MEM
    EX_MEM exmem("EX_MEM");
    sc_signal<sc_int<32>> rs2_exmem, alu_result_exmem;
    sc_signal<sc_int<32>> pc_exmem;
    sc_signal<sc_int<5>> rd_exmem;
    sc_signal<bool> memRead_exmem, memWrite_exmem, memToReg_exmem, regWrite_exmem;
    exmem.clock(clock);
    exmem.reset(reset);
    exmem.enable(sc_signal<bool>("exmem_en", true));
    exmem.pc_in(pc_idex);
    exmem.alu_result_in(alu_out);
    exmem.rs2_data_in(rs2_idex);
    exmem.rd_in(rd_idex);
    exmem.memRead_in(memRead);
    exmem.memWrite_in(memWrite);
    exmem.regWrite_in(regWrite_idex);
    exmem.memToReg_in(memToReg);
    exmem.pc_out(pc_exmem);
    exmem.alu_result_out(alu_result_exmem);
    exmem.rs2_data_out(rs2_exmem);
    exmem.rd_out(rd_exmem);
    exmem.memRead_out(memRead_exmem);
    exmem.memWrite_out(memWrite_exmem);
    exmem.regWrite_out(regWrite_exmem);
    exmem.memToReg_out(memToReg_exmem);

    // Data Memory
    DMEM dmem("DMEM");
    sc_signal<sc_int<32>> mem_data_out;
    dmem.clock(clock);
    dmem.dmem_enable(sc_signal<bool>("dmem_en", true));
    dmem.dmem_write(memWrite_exmem);
    dmem.dmem_address(alu_result_exmem);
    dmem.dmem_dataIn(rs2_exmem);
    dmem.dmem_dataOut(mem_data_out);

    // MEM/WB
    MEM_WB memwb("MEM_WB");
    sc_signal<sc_int<5>> rd_memwb;
    sc_signal<sc_int<32>> alu_result_memwb, mem_data_memwb;
    sc_signal<sc_int<32>> pc_memwb;
    sc_signal<bool> regWrite_memwb, memToReg_memwb;
    memwb.clock(clock);
    memwb.reset(reset);
    memwb.enable(sc_signal<bool>("memwb_en", true));
    memwb.pc_in(pc_exmem);
    memwb.mem_data_in(mem_data_out);
    memwb.alu_result_in(alu_result_exmem);
    memwb.rd_in(rd_exmem);
    memwb.regWrite_in(regWrite_exmem);
    memwb.memToReg_in(memToReg_exmem);
    memwb.pc_out(pc_memwb);
    memwb.mem_data_out(mem_data_memwb);
    memwb.alu_result_out(alu_result_memwb);
    memwb.rd_out(rd_memwb);
    memwb.regWrite_out(regWrite_memwb);
    memwb.memToReg_out(memToReg_memwb);


    // Mux para write back
    Mux2x1 mux_wb("MuxWB");
    mux_wb.mux_in1(alu_result_memwb);
    mux_wb.mux_in2(mem_data_memwb);
    mux_wb.mux_sel(memToReg_memwb);
    mux_wb.mux_out(wb_data);


    // Inicialização e simulação
    reset = true;
    pc_enable = true;
    pc_load = false;
    imem_en = true;
    imem_wr = false;


    //TODO: corrigir segmentation fault. a partir daqui, o código não roda mais
    sc_start(10, SC_NS);  // Reset
    reset = false;

    for (int cycle = 0; cycle < 20; ++cycle) {
        sc_start(10, SC_NS);

    }

    return 0;
}
