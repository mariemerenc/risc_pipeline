#include "systemc.h"
#include "control_unit.h"

int sc_main(int argc, char* argv[]) {
    sc_clock clock("clock", 10, SC_NS);

    // Inputs
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_uint<8>> src1, src2;
    sc_signal<sc_uint<9>> dest;
    sc_signal<bool> flagN, flagZ;

    // Outputs
    sc_signal<bool> enablePC, loadPC, resetPC;
    sc_signal<sc_uint<9>> jumpAddress;
    sc_signal<bool> enableIM, writeIM;
    sc_signal<bool> enableDM, writeDM;
    sc_signal<bool> enableIR, writeIR;
    sc_signal<sc_uint<8>> immediateValue;
    sc_signal<sc_uint<9>> immediateDest;
    sc_signal<bool> enableRB, writeRB;
    sc_signal<bool> enablePipeReg, writePipeReg, resetPipeReg;
    sc_signal<bool> resetFlags;
    sc_signal<sc_uint<2>> muxRegWrite, muxDMAddr;

    ControlUnit cu("ControlUnit");
    cu.clock(clock);
    cu.opcode(opcode);
    cu.src1(src1);
    cu.src2(src2);
    cu.dest(dest);
    cu.flagN(flagN);
    cu.flagZ(flagZ);
    cu.enablePC(enablePC);
    cu.loadPC(loadPC);
    cu.resetPC(resetPC);
    cu.jumpAddress(jumpAddress);
    cu.enableIM(enableIM);
    cu.writeIM(writeIM);
    cu.enableDM(enableDM);
    cu.writeDM(writeDM);
    cu.enableIR(enableIR);
    cu.writeIR(writeIR);
    cu.immediateValue(immediateValue);
    cu.immediateDest(immediateDest);
    cu.enableRB(enableRB);
    cu.writeRB(writeRB);
    cu.enablePipeReg(enablePipeReg);
    cu.writePipeReg(writePipeReg);
    cu.resetPipeReg(resetPipeReg);
    cu.resetFlags(resetFlags);
    cu.muxRegWrite(muxRegWrite);
    cu.muxDMAddr(muxDMAddr);

    std::cout << "Running ControlUnit testbench..." << std::endl;

    // Init
    opcode.write(0);
    src1.write(0);
    src2.write(0);
    dest.write(0);
    flagN.write(false);
    flagZ.write(false);

    sc_start(20, SC_NS); // Start pipeline

    // LRI
    opcode.write(13);
    src1.write(0xAB);
    dest.write(0x12);
    sc_start(40, SC_NS);
    std::cout << "[LRI] immediateDest = " << immediateDest.read()
              << ", immediateValue = " << immediateValue.read() << std::endl;

    // LD
    opcode.write(8);
    src1.write(0x00);
    dest.write(0x55);
    sc_start(40, SC_NS);
    std::cout << "[LD] enableDM = " << enableDM.read()
              << ", writeDM = " << writeDM.read()
              << ", muxRegWrite = " << muxRegWrite.read() << std::endl;

    // ST
    opcode.write(9);
    dest.write(0x22);
    sc_start(40, SC_NS);
    std::cout << "[ST] enableDM = " << enableDM.read()
              << ", writeDM = " << writeDM.read()
              << ", muxDMAddr = " << muxDMAddr.read() << std::endl;

    // JUMP
    opcode.write(10);
    dest.write(0x1FF);
    sc_start(40, SC_NS);
    std::cout << "[JUMP] jumpAddress = " << jumpAddress.read()
              << ", loadPC = " << loadPC.read() << std::endl;

    // JN
    flagN.write(true);
    sc_start(10, SC_NS);
    opcode.write(11);
    dest.write(0x1FF);
    sc_start(40, SC_NS);
    std::cout << "[JN] jumpAddress = " << jumpAddress.read()
              << ", loadPC = " << loadPC.read()
              << ", resetFlags = " << resetFlags.read() << std::endl;
    flagN.write(false);

    // JZ
    flagZ.write(true);
    sc_start(10, SC_NS);
    opcode.write(12);
    dest.write(0x22);
    sc_start(40, SC_NS);
    std::cout << "[JZ] jumpAddress = " << jumpAddress.read()
              << ", loadPC = " << loadPC.read()
              << ", resetFlags = " << resetFlags.read() << std::endl;
    flagZ.write(false);

    // HALT
    opcode.write(0);
    sc_start(10, SC_NS);

    std::cout << "ControlUnit testbench completed." << std::endl;
    return 0;
}
