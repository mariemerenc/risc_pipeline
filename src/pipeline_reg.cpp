#include "pipeline_reg.h"

void PipelineReg::process() {
    while (true) {
        wait();

        if (reset.read()) { 
            _opcode = 0;
            _of1 = 0;
            _of2 = 0;
            _od = 0;
        } 
        else if (enable.read() && write.read()) {
            _opcode = opcodeIn.read();
            _of1 = of1In.read();
            _of2 = of2In.read();
            _od = odIn.read();
        }

        opcodeOut.write(_opcode);
        of1Out.write(_of1);
        of2Out.write(_of2);
        odOut.write(_od);
    }
}
