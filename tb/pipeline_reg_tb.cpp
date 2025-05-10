#include <systemc.h>
#include "pipeline_reg.h"

SC_MODULE(PipelineRegTestbench) {
    // Signals
    sc_clock clock;
    sc_signal<bool> enable, write;
    sc_signal<sc_uint<4>> opcodeIn;
    sc_signal<sc_uint<8>> of1In, of2In;
    sc_signal<sc_uint<9>> odIn;

    sc_signal<sc_uint<4>> opcodeOut;
    sc_signal<sc_uint<8>> of1Out, of2Out;
    sc_signal<sc_uint<9>> odOut;

    // Device under test
    PipelineReg* pipelineReg;

    void test() {
        // Initialize signals
        enable = 1;
        write = 1;

        opcodeIn = 0xA;   // 1010
        of1In = 0x11;     // 00010001
        of2In = 0x22;     // 00100010
        odIn = 0x155;     // 0101010101

        wait(10, SC_NS);  // First clock edge

        std::cout << "[Cycle 1] opcodeOut: " << opcodeOut.read()
                  << ", of1Out: " << of1Out.read()
                  << ", of2Out: " << of2Out.read()
                  << ", odOut: " << odOut.read() << std::endl;

        // Update inputs
        opcodeIn = 0x2;
        of1In = 0x33;
        of2In = 0x44;
        odIn = 0x066;

        wait(10, SC_NS);  // Second clock edge

        std::cout << "[Cycle 2] opcodeOut: " << opcodeOut.read()
                  << ", of1Out: " << of1Out.read()
                  << ", of2Out: " << of2Out.read()
                  << ", odOut: " << odOut.read() << std::endl;

        // Disable write
        write = 0;

        opcodeIn = 0xF;
        of1In = 0xFF;
        of2In = 0xEE;
        odIn = 0x1FF;

        wait(10, SC_NS);  // Third clock edge

        std::cout << "[Cycle 3 - write=0] opcodeOut: " << opcodeOut.read()
                  << ", of1Out: " << of1Out.read()
                  << ", of2Out: " << of2Out.read()
                  << ", odOut: " << odOut.read() << std::endl;

        sc_stop();
    }

    SC_CTOR(PipelineRegTestbench)
        : clock("clock", 10, SC_NS)
    {
        pipelineReg = new PipelineReg("PipelineReg");
        pipelineReg->clock(clock);
        pipelineReg->enable(enable);
        pipelineReg->write(write);
        pipelineReg->opcodeIn(opcodeIn);
        pipelineReg->of1In(of1In);
        pipelineReg->of2In(of2In);
        pipelineReg->odIn(odIn);
        pipelineReg->opcodeOut(opcodeOut);
        pipelineReg->of1Out(of1Out);
        pipelineReg->of2Out(of2Out);
        pipelineReg->odOut(odOut);

        SC_THREAD(test);
    }

    ~PipelineRegTestbench() {
        delete pipelineReg;
    }
};

int sc_main(int argc, char* argv[]) {
    PipelineRegTestbench tb("tb");
    sc_start();
    return 0;
}
