#ifndef ID_EX_H
#define ID_EX_H

#include <systemc.h>

/*
    ID/EX Pipeline Register
    Armazena sinais de controle e dados decodificados vindos da etapa ID
    para serem usados pela etapa EX (Execução).
*/

SC_MODULE(ID_EX) {
    // Entradas
    sc_in<bool> clock{"clock"};
    sc_in<bool> reset{"reset"};
    sc_in<bool> enable{"enable"};

    sc_in<sc_int<32>> pc_in{"pc_in"};
    sc_in<sc_int<32>> rs1_in{"rs1_in"};
    sc_in<sc_int<32>> rs2_in{"rs2_in"};
    sc_in<sc_int<32>> imm_in{"imm_in"};
    sc_in<sc_int<5>> rd_in{"rd_in"};
    sc_in<sc_int<4>> aluOp_in{"aluOp_in"};
    sc_in<bool> aluSrc_in{"aluSrc_in"};
    sc_in<bool> regWrite_in{"regWrite_in"};

    // Saídas
    sc_out<sc_int<32>> pc_out{"pc_out"};
    sc_out<sc_int<32>> rs1_out{"rs1_out"};
    sc_out<sc_int<32>> rs2_out{"rs2_out"};
    sc_out<sc_int<32>> imm_out{"imm_out"};
    sc_out<sc_int<5>> rd_out{"rd_out"};
    sc_out<sc_int<4>> aluOp_out{"aluOp_out"};
    sc_out<bool> aluSrc_out{"aluSrc_out"};
    sc_out<bool> regWrite_out{"regWrite_out"};

    void process() {
        if (reset.read()) {
            pc_out.write(0);
            rs1_out.write(0);
            rs2_out.write(0);
            imm_out.write(0);
            rd_out.write(0);
            aluOp_out.write(0);
            aluSrc_out.write(false);
            regWrite_out.write(false);
        } else if (enable.read()) {
            pc_out.write(pc_in.read());
            rs1_out.write(rs1_in.read());
            rs2_out.write(rs2_in.read());
            imm_out.write(imm_in.read());
            rd_out.write(rd_in.read());
            aluOp_out.write(aluOp_in.read());
            aluSrc_out.write(aluSrc_in.read());
            regWrite_out.write(regWrite_in.read());
        }
    }

    SC_CTOR(ID_EX) {
        std::cout << "New component - ID/EX" << std::endl;
        SC_METHOD(process);
        sensitive << clock.pos();
    }
};

#endif