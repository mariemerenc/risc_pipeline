#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include "systemc.h"

SC_MODULE(ControlUnit) {
public:
    // Inputs
    sc_in_clk       clock;
    sc_in<sc_uint<4>> opcode;
    sc_in<sc_uint<8>> src1, src2;
    sc_in<sc_uint<9>> dest;
    sc_in<bool>     flagN, flagZ;

    // Outputs
    sc_out<bool>        enablePC{"enablePC"}, loadPC{"loadPC"}, resetPC{"resetPC"};
    sc_out<sc_uint<9>>  jumpAddress{"jumpAddress"};
    sc_out<bool>        enableIM{"enableIM"}, writeIM{"writeIM"};
    sc_out<bool>        enableDM{"enableDM"}, writeDM{"writeDM"};
    sc_out<bool>        enableIR{"enableIR"}, writeIR{"writeIR"};
    sc_out<sc_uint<8>>  immediateValue{"immediateValue"};
    sc_out<sc_uint<9>>  immediateDest{"immediateDest"};
    sc_out<bool>        enableRB{"enableRB"}, writeRB{"writeRB"};
    sc_out<bool>        enablePipeReg{"enablePipeReg"}, writePipeReg{"writePipeReg"}, resetPipeReg{"resetPipeReg"};
    sc_out<bool>        resetFlags{"resetFlags"};
    sc_out<sc_uint<2>>  muxRegWrite{"muxRegWrite"}, muxDMAddr{"muxDMAddr"};

    SC_CTOR(ControlUnit) {
        std::cout << "New component - CU" << std::endl;
        SC_METHOD(stateMachine);
        sensitive << clock.pos();
    }

private:
    int  curState = 0;
    bool pipelineRestart = false;

    void fetchInstruction(){
        enableIM.write(1); 
        writeIM.write(0);
        enablePC.write(1);
    }

    void fetchToIR(){
        enableIM.write(0);
        enableIR.write(1); 
        writeIR.write(1);
        enablePC.write(0);
    }

    void IRToPipeline(){
        enableIR.write(0);
        enablePipeReg.write(1); 
        writePipeReg.write(1);
    }

    void stopIR(){
        enableIR.write(0);
        writeIR.write(0);
    }

    void stateMachine(){

        switch(curState){
            case 0:
                fetchInstruction(); 
                curState = 1; 
                break;

            case 1:
                fetchToIR(); 
                curState = 2; 
                break;

            case 2:
                if(!pipelineRestart){
                    IRToPipeline(); 
                    curState = 3;
                } 
                else{
                    pipelineRestart = false;
                    curState = 0;
                }
                break;

            case 3:
                enablePipeReg.write(0);
                curState = 5;
                fetchInstruction();
                break;

            case 5:
                enableDM.write(0); 
                writeDM.write(0);
                fetchToIR();

                switch (opcode.read()) {
                    case 13:  // LRI
                        enableRB.write(1); 
                        writeRB.write(1);
                        immediateDest.write(dest.read());
                        immediateValue.write(src1.read());
                        muxRegWrite.write(2);
                        curState = 9;
                        break;

                    case 8:   // LD
                        enableRB.write(1); 
                        writeRB.write(1);
                        enableDM.write(1); 
                        writeDM.write(0);
                        muxRegWrite.write(1);
                        muxDMAddr.write(1);
                        curState = 10;
                        break;

                    case 9:   // ST
                        enableRB.write(1); 
                        writeRB.write(0);
                        muxDMAddr.write(0);
                        curState = 7;
                        break;

                    case 10:  // JUMP
                        loadPC.write(1);
                        jumpAddress.write(dest.read());
                        pipelineRestart = true;
                        curState = 8;
                        break;

                    case 11:  // JN
                        if (flagN.read()) {
                            loadPC.write(1);
                            jumpAddress.write(dest.read());
                            resetFlags.write(1);
                            pipelineRestart = true;
                        }
                        curState = 8;
                        break;

                    case 12:  // JZ
                        if(flagZ.read()){
                            loadPC.write(1);
                            jumpAddress.write(dest.read());
                            resetFlags.write(1);
                            pipelineRestart = true;
                        }
                        curState = 8;
                        break;

                    case 0:   // HALT
                        sc_stop();
                        break;

                    default:  // ALU ops
                        enableRB.write(1); 
                        writeRB.write(0);
                        muxRegWrite.write(0);
                        curState = 6;
                        break;
                }
                break;

            case 6:  // ALU result write-back
                enableRB.write(1); 
                writeRB.write(1);
                stopIR();
                curState = 9;
                break;

            case 7:  // ST: memory write
                enableDM.write(1); 
                writeDM.write(1);
                stopIR();
                curState = 9;
                break;

            case 8:  // After jump
                curState = 2;
                break;

            case 9:
                enableRB.write(0);
                enableDM.write(1);
                stopIR();
                curState = 2;
                break;

            case 10: // LD final write-back
                enableRB.write(1); 
                writeRB.write(1);
                curState = 9;
                break;
        }
    }
};

#endif

// continua apresentando erros!! em JN, resetFlags deveria ser 1, não 0
