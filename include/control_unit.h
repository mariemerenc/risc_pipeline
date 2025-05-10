#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include "systemc.h"
 
SC_MODULE(ControlUnit) {
public:
    // Inputs
    sc_in_clk clock;
    sc_in<sc_uint<4>> opcode;
    sc_in<sc_uint<8>> src1;
    sc_in<sc_uint<8>> src2;
    sc_in<sc_uint<9>> dest;
    sc_in<bool> flagN;
    sc_in<bool> flagZ;

    // Program Counter
    sc_out<bool> enablePC, loadPC, resetPC;
    sc_out<sc_uint<9>> jumpAddress;

    // Instruction Memory
    sc_out<bool> enableIM, writeIM;

    // Data Memory
    sc_out<bool> enableDM, writeDM;

    // Instruction Register
    sc_out<bool> enableIR, writeIR;
    sc_out<sc_uint<8>> immediateValue;
    sc_out<sc_uint<9>> immediateDest;

    // Register Bank
    sc_out<bool> enableRB, writeRB;

    // Pipeline Register
    sc_out<bool> enablePipeReg, writePipeReg, resetPipeReg;

    // ULA flags
    sc_out<bool> resetFlags;

    // Multiplexers
    sc_out<sc_uint<2>> muxRegWrite;
    sc_out<sc_uint<2>> muxDMAddr;

    // Constructor
    SC_CTOR(ControlUnit) {
        SC_METHOD(stateMachine);
        sensitive << clock.pos();
    }

private:
    int curState = 0;
    bool pipelineRestart = false;

    // Internal helper methods
    void fetchInstruction();
    void fetchToIR();
    void IRToPipeline();
    void stopIR();

    void stateMachine();
};

// -- Method definitions --

void ControlUnit::fetchInstruction() {
    enableIM.write(1);
    writeIM.write(0);
    enablePC.write(1);
}

void ControlUnit::fetchToIR() {
    enableIM.write(0);
    enableIR.write(1);
    writeIR.write(1);
    enablePC.write(0);
}

void ControlUnit::IRToPipeline() {
    enableIR.write(0);
    enablePipeReg.write(1);
    writePipeReg.write(1);
}

void ControlUnit::stopIR() {
    enableIR.write(0);
}

void ControlUnit::stateMachine() {
    switch (curState) {
        case 0:
            fetchInstruction();
            curState = 1;
            break;

        case 1:
            fetchToIR();
            curState = 2;
            break;

        case 2:
            if (!pipelineRestart) {
                IRToPipeline();
                curState = 3;
            } else {
                curState = 0;
                pipelineRestart = false;
            }
            break;

        case 3:
            enablePipeReg.write(0);
            curState = 5;
            fetchInstruction(); // Continue pipeline
            break;

        case 5:
            fetchToIR(); // Pipeline fetch

            if (opcode.read() == 13) { // LRI
                enableRB.write(1);
                writeRB.write(1);
                immediateDest.write(dest.read());
                immediateValue.write(src1.read());
                muxRegWrite.write(2);
                curState = 9;
            }
            else if (opcode.read() == 8) { // LD
                enableRB.write(1);
                writeRB.write(1);
                enableDM.write(1);
                writeDM.write(0);
                muxRegWrite.write(1);
                muxDMAddr.write(1);
                curState = 10;
            }
            else if (opcode.read() == 9) { // ST
                enableRB.write(1);
                writeRB.write(0);
                muxDMAddr.write(0);
                curState = 7;
            }
            else if (opcode.read() == 10) { // JUMP
                enablePC.write(0);
                loadPC.write(1);
                jumpAddress.write(dest);
                pipelineRestart = true;
                curState = 8;
            }
            else if (opcode.read() == 11 && flagN.read()) { // JN
                jumpAddress.write(dest);
                enablePC.write(0);
                loadPC.write(1);
                resetFlags.write(1);
                pipelineRestart = true;
                curState = 8;
            }
            else if (opcode.read() == 12 && flagZ.read()) { // JZ
                jumpAddress.write(dest);
                enablePC.write(0);
                loadPC.write(1);
                resetFlags.write(1);
                pipelineRestart = true;
                curState = 8;
            }
            else if (opcode.read() != 0) { // ALU Ops
                enableRB.write(1);
                writeRB.write(0);
                muxRegWrite.write(0);
                curState = 6;
            }
            else {
                sc_stop(); // HALT
            }
            break;

        case 6:
            enableRB.write(1);
            writeRB.write(1);
            stopIR();
            curState = 9;
            break;

        case 7:
            enableDM.write(1);
            writeDM.write(1);
            stopIR();
            curState = 9;
            break;

        case 8:
            loadPC.write(0);
            curState = 2;
            break;

        case 9:
            enableRB.write(0);
            enableDM.write(0);
            stopIR();
            curState = 2;
            break;

        case 10:
            enableRB.write(1);
            writeRB.write(1);
            curState = 9;
            break;
    }
}

#endif
