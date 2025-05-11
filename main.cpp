#include <systemc.h>
#include "processor.h"

int sc_main(int argc, char* argv[]) {
    std::cout << "SystemC Processor Simulation Starting..." << std::endl;

    Processor proc("RISC_Processor");

    sc_trace_file *tf = sc_create_vcd_trace_file("processor_trace");
    sc_trace(tf, proc.clock, "clock");
    sc_trace(tf, proc.pc_value, "PC");
    sc_trace(tf, proc.instruction, "Instruction");
    sc_trace(tf, proc.alu_result, "ALU_Result");
    sc_trace(tf, proc.reg_data1, "Reg1");
    sc_trace(tf, proc.reg_data2, "Reg2");
    sc_trace(tf, proc.flagZ, "FlagZ");
    sc_trace(tf, proc.flagN, "FlagN");

 
    proc.reset.write(1);
    sc_start(1, SC_NS);
    proc.reset.write(0);

  
    sc_start(200, SC_NS);


    sc_close_vcd_trace_file(tf);
    std::cout << "SystemC Processor Simulation Completed." << std::endl;
    return 0;
}
