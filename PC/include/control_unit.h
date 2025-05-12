#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include "systemc.h"

SC_MODULE(ControlUnit) {
    // Entradas
    sc_in<sc_uint<6>> opcode;

    // Saídas
    sc_out<sc_uint<3>> aluOp;
    sc_out<bool> aluSrc;
    sc_out<bool> regDst;
    sc_out<bool> regWrite;
    sc_out<bool> memRead;
    sc_out<bool> memWrite;
    sc_out<bool> memToReg;
    sc_out<bool> branch;

    void process() {
        switch(opcode.read()) {
            case 0x01: // AND
                aluOp.write(2);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            case 0x13: // OR
                aluOp.write(3);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            case 0x24: // XOR
                aluOp.write(4);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            case 0x36: // NOT
                aluOp.write(6);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            case 0x45: // CMP
                aluOp.write(5);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            case 0x05: // ADD
                aluOp.write(0);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            case 0x57: // ADDI
                aluOp.write(7);
                aluSrc.write(1);
                regDst.write(0);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            case 0x61: // SUB
                aluOp.write(1);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            case 0x10: // não definido
            case 0x17: // não definido
            case 0x21: // não definido
            case 0x30: // não definido
            case 0x20: // não definido
            case 0x3F: // não definido
                aluOp.write(0);
                aluSrc.write(0);
                regDst.write(0);
                regWrite.write(0);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;

            default:
                aluOp.write(0);
                aluSrc.write(0);
                regDst.write(0);
                regWrite.write(0);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
        }
    }

    SC_CTOR(ControlUnit) {
        SC_METHOD(process);
        sensitive << opcode;
    }
};

#endif // CONTROL_UNIT_H
