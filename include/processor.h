#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <systemc.h>
#include "program_counter.h"
#include "alu.h"
#include "ram.h"
#include "control_unit.h"
#include "pipeline_reg.h"
#include "mux2x1.h"
#include "mux3x1.h"
#include "register_base.h"
#include "instruction_register.h"

SC_MODULE(Processor) {
    // global signals
    sc_clock clock;
    sc_signal<bool> reset, resetPC, resetFlags;
    sc_signal<bool> enablePC, loadPC, enableIM, writeIM, enableDM, writeDM;
    sc_signal<bool> enableIR, writeIR, enableRB, writeRB;
    sc_signal<bool> enablePipeReg, writePipeReg, resetPipeReg;
    sc_signal<sc_uint<9>> jumpAddress, immediateDest;
    sc_signal<sc_uint<8>> immediateValue;
    sc_signal<sc_uint<2>> muxRegWrite, muxDMAddr;
    sc_signal<sc_int<32>> muxRegWrite_output;
    sc_signal<sc_int<32>> dmem_dataOut;
    sc_signal<sc_uint<9>> muxDmAddr_output; 
    sc_signal<sc_uint<64>> imem_dataOut;   // Saída da IMEM
    sc_signal<sc_uint<64>> ir_instruction; // Saída do IR

    
    // cu
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_uint<8>> src1, src2;
    sc_signal<sc_uint<9>> dest;
    sc_signal<bool> flagN, flagZ;
    
    // datapath
    sc_signal<sc_uint<9>> pc_value;
    sc_signal<sc_uint<64>> instruction;
    sc_signal<sc_int<32>> alu_result;
    sc_signal<sc_int<32>> reg_data1, reg_data2;

    // components
    ProgramCounter* pc;
    ALU* alu;
    RAM<sc_uint<64>, 256>* imem;
    RAM<sc_int<32>, 256>* dmem;
    ControlUnit* cu;
    PipelineReg* pipe_reg;
    Mux2x1* mux_dm_addr;
    Mux3x1* mux_reg_write;
    RegisterBase<sc_int<32>, 32>* regbank;
    InstructionRegister* ir;

    SC_CTOR(Processor) : clock("clock", 10, SC_NS) {
        // components
        pc = new ProgramCounter("ProgramCounter"); 
        alu = new ALU("ALU"); 
        imem = new RAM<sc_uint<64>, 256>("InstructionMemory");
        dmem = new RAM<sc_int<32>, 256>("DataMemory");
        cu = new ControlUnit("ControlUnit");
        pipe_reg = new PipelineReg("PipelineReg");
        mux_dm_addr = new Mux2x1("DM_Addr_Mux");
        mux_reg_write = new Mux3x1("RegWrite_Mux");
        regbank = new RegisterBase<sc_int<32>, 32>("RegisterBank");
        ir = new InstructionRegister("InstructionReg");

        // pc
        pc->clock(clock);
        pc->reset(cu->resetPC);
        pc->enable(cu->enablePC);
        pc->load(cu->loadPC);
        pc->counterIn(cu->jumpAddress);
        pc->counterOut(pc_value);

        // memory instructions
        imem->clock(clock);
        imem->enable(cu->enableIM);
        imem->write(cu->writeIM);
        imem->address(pc_value);
        imem->dataIn(instruction);
        imem->dataOut(imem_dataOut);

        // instruction register
        ir->clock(clock);
        ir->enable(cu->enableIR);
        ir->write(cu->writeIR);
        ir->instructionIn(imem_dataOut);
        ir->instructionOut(ir_instruction);

        // pipeline register
        pipe_reg->clock(clock);
        pipe_reg->reset(cu->resetPipeReg);
        pipe_reg->enable(cu->enablePipeReg);
        pipe_reg->write(cu->writePipeReg);
        pipe_reg->opcodeIn(opcode);
        pipe_reg->of1In(src1);
        pipe_reg->of2In(src2);
        pipe_reg->odIn(dest);
        pipe_reg->odOut(dest);
        pipe_reg->of1Out(src1);
        pipe_reg->of2Out(src2);
        pipe_reg->opcodeOut(opcode);

        // register base
        regbank->clock(clock);
        regbank->enable(cu->enableRB);
        regbank->write(cu->writeRB);
        regbank->addressSource1(src1);
        regbank->addressSource2(src2);
        regbank->addressDest(dest);
        regbank->dataToWrite(muxRegWrite_output);
        regbank->dataSource1(reg_data1);
        regbank->dataSource2(reg_data2);

        // alu
        alu->in1(reg_data1);
        alu->in2(reg_data2);
        alu->op(opcode);
        alu->out(alu_result);
        alu->Z(flagZ);
        alu->N(flagN);

        // mux
        mux_reg_write->selector(cu->muxRegWrite);
        mux_reg_write->aluResult(alu_result);
        mux_reg_write->dataMemory(dmem_dataOut);
        mux_reg_write->immediateValue(cu->immediateValue);
        mux_reg_write->output(muxRegWrite_output);

        mux_dm_addr->selector(cu->muxDMAddr);
        mux_dm_addr->aluInput(dest);
        mux_dm_addr->memoryInput(cu->immediateDest);
        mux_dm_addr->output(muxDmAddr_output);
        

        // memory data
        dmem->clock(clock);
        dmem->enable(cu->enableDM);
        dmem->write(cu->writeDM);
        dmem->address(mux_dm_addr->output);
        dmem->dataIn(reg_data2);
        dmem->dataOut(dmem_dataOut);
        
        

        // cu
        cu->clock(clock);
        cu->opcode(opcode);
        cu->src1(src1);
        cu->src2(src2);
        cu->dest(dest);
        cu->flagN(flagN);
        cu->flagZ(flagZ);
        cu->enablePC(enablePC);
        cu->loadPC(loadPC);
        cu->resetPC(resetPC);
        cu->jumpAddress(jumpAddress);
        cu->enableIM(enableIM);
        cu->writeIM(writeIM);
        cu->enableDM(enableDM);
        cu->writeDM(writeDM);
        cu->enableIR(enableIR);
        cu->writeIR(writeIR);
        cu->immediateValue(immediateValue);
        cu->immediateDest(immediateDest);
        cu->enableRB(enableRB);
        cu->writeRB(writeRB);
        cu->enablePipeReg(enablePipeReg);
        cu->writePipeReg(writePipeReg);
        cu->resetPipeReg(resetPipeReg);
        cu->resetFlags(resetFlags);
        cu->muxRegWrite(muxRegWrite);
        cu->muxDMAddr(muxDMAddr);

        // loading program into instruction memory
        std::vector<sc_uint<64>> program = {
            0x10000000, // LRI R0, 0
            0x1100000A, // LRI R1, 10
            0x12000005, // LRI R2, 5
            0x20120000, // ADD R3, R1, R2  (R3 = 15)
            0x30000000  // HALT
        };
        imem->load(program);
    }

    ~Processor() {
        delete pc;
        delete alu;
        delete imem;
        delete dmem;
        delete cu;
        delete pipe_reg;
        delete mux_dm_addr;
        delete mux_reg_write;
        delete regbank;
        delete ir;
    }
};

#endif