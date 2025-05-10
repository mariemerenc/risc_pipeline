#ifndef PIPELINE_REG_H
#define PIPELINE_REG_H

#include <systemc.h>

SC_MODULE(PipelineReg) {
    sc_in<bool> clock;
    sc_in<bool> enable;
    sc_in<bool> write;

    // inputs
    sc_in<sc_uint<4>>  opcodeIn;
    sc_in<sc_uint<8>>  of1In;
    sc_in<sc_uint<8>>  of2In;
    sc_in<sc_uint<9>>  odIn;

    // outputs
    sc_out<sc_uint<4>>  opcodeOut;
    sc_out<sc_uint<8>>  of1Out;
    sc_out<sc_uint<8>>  of2Out;
    sc_out<sc_uint<9>>  odOut;

    // internal registers
    sc_uint<4>  _opcode;
    sc_uint<8>  _of1, _of2;
    sc_uint<9>  _od;

    void process();

    SC_CTOR(PipelineReg) {
        SC_THREAD(process);
        sensitive << clock.pos();
    }
};

#endif
