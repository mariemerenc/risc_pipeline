#ifndef PIPELINE_REG_H
#define PIPELINE_REG_H

#include <systemc.h>

SC_MODULE(PipelineReg) {
    sc_in<bool> clock{"clock"};
    sc_in<bool> reset{"reset"};
    sc_in<bool> enable{"enable"};
    sc_in<bool> write{"write"};

    // inputs
    sc_in<sc_uint<4>>  opcodeIn{"opcodeIn"};
    sc_in<sc_uint<8>>  of1In{"of1In"};
    sc_in<sc_uint<8>>  of2In{"of2In"};
    sc_in<sc_uint<9>>  odIn{"odIn"};

    // outputs
    sc_out<sc_uint<4>>  opcodeOut{"opcodeOut"};
    sc_out<sc_uint<8>>  of1Out{"of1Out"};
    sc_out<sc_uint<8>>  of2Out{"of2Out"};
    sc_out<sc_uint<9>>  odOut{"odOut"};

    // internal registers
    sc_uint<4>  _opcode;
    sc_uint<8>  _of1, _of2;
    sc_uint<9>  _od;

    void process();

    SC_CTOR(PipelineReg) {
        std::cout << "New component - Pipeline Register" << std::endl;
        SC_THREAD(process);
        sensitive << clock.pos();
        async_reset_signal_is(reset, true);
    }
};

#endif
