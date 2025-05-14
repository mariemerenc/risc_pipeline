#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include <systemc.h>

/*
    * Componente: ControlUnit
    * Descrição: Unidade de Controle para o processador.
    * 
    * Entradas:
    * - opcode: código da operação (4 bits)
    * - flagN: flag de negativo (1 bit)
    * - flagZ: flag de zero (1 bit)
    * 
    * Saídas:
    * - regWrite: habilita escrita no banco de registradores (1 bit)
    * - memRead: habilita leitura da memória de dados (1 bit)
    * - memWrite: habilita escrita na memória de dados (1 bit)
    * - aluSrc: seleciona a fonte do segundo operando da ALU (0 = registrador, 1 = imediato ou offset) (1 bit)
    * - memToReg: seleciona a fonte do dado a ser escrito no registrador (0 = ALU→WB, 1 = MEM→WB) (1 bit)
    * - regDst: seleciona o destino do dado a ser escrito no registrador (0 = imediato, 1 = campo rd) (1 bit)
    * - branch: habilita comparação de branch (1 bit)
    * - jump: habilita salto incondicional (1 bit)
    * - aluOp: operação a ser realizada pela ALU (4 bits)
*/

// Conjunto de instruções
enum Opcodes : uint8_t {
    OP_NOP = 0x0,
    OP_AND = 0x1,
    OP_OR  = 0x2,
    OP_XOR = 0x3,
    OP_NOT = 0x4,
    OP_CMP = 0x7,
    OP_ADD = 0x5,
    OP_SUB = 0x6,
    OP_LD  = 0x8,
    OP_ST  = 0x9,
    OP_J   = 0x10,
    OP_JN  = 0x11,
    OP_JZ  = 0x12
};

SC_MODULE(ControlUnit) {
    //entradas
    sc_in<sc_uint<4>> opcode{"opcode"};  // 4 bits para as 12 instruções
    sc_in<bool>       flagN{"flagN"};    // negativo
    sc_in<bool>       flagZ{"flagZ"};    // zero

    //saídas de controle
    sc_out<bool>        regWrite{"regWrite"}; // habilita escrita no banco de registradores
    sc_out<bool>        memRead{"memRead"};   // leitura de memória de dados
    sc_out<bool>        memWrite{"memWrite"}; // escrita em memória de dados
    sc_out<bool>        aluSrc{"aluSrc"};     // 0 = registrador, 1 = imediato ou offset
    sc_out<bool>        memToReg{"memToReg"}; // 0 = ALU→WB, 1 = MEM→WB
    sc_out<bool>        regDst{"regDst"};     // 0 = destino imediato (LDI), 1 = campo rd
    sc_out<bool>        branch{"branch"};     // habilita comparação de branch
    sc_out<bool>        jump{"jump"};         // habilita salto incondicional
    sc_out<sc_uint<4>>  aluOp{"aluOp"};       // operação p/ ALU (4 bits)

    void process() {
        // valores defaults (NOP)
        regWrite.write(false);
        memRead.write(false);
        memWrite.write(false);
        aluSrc.write(false);
        memToReg.write(false);
        regDst.write(false);
        branch.write(false);
        jump.write(false);
        aluOp.write(OP_NOP);

        switch (opcode.read()) {
            case OP_AND:
                aluOp.write(OP_AND);
                regWrite.write(true);
                break;

            case OP_OR:
                aluOp.write(OP_OR);
                regWrite.write(true);
                break;

            case OP_XOR:
                aluOp.write(OP_XOR);
                regWrite.write(true);
                break;

            case OP_NOT:
                aluOp.write(OP_NOT);
                regWrite.write(true);
                break;

            case OP_CMP:
                aluOp.write(OP_CMP);
                // CMP não escreve em registrador, só ajusta flags
                break;

            case OP_ADD:
                aluOp.write(OP_ADD);
                regWrite.write(true);
                break;

            case OP_SUB:
                aluOp.write(OP_SUB);
                regWrite.write(true);
                break;

            case OP_LD:
                aluOp.write(OP_ADD);      // calcula endereço: base + offset
                aluSrc.write(true);       // usa immediate como segundo operando
                memRead.write(true);
                memToReg.write(true);     // escreve o dado da memória
                regWrite.write(true);
                break;

            case OP_ST:
                aluOp.write(OP_ADD);      // calcula endereço
                aluSrc.write(true);
                memWrite.write(true);
                break;

            case OP_J:
                jump.write(true);
                break;

            case OP_JN:
                if (flagN.read()) jump.write(true);
                break;

            case OP_JZ:
                if (flagZ.read()) jump.write(true);
                break;

            default:
                // NOP e instruções não definidas
                break;
        }
    }

    SC_CTOR(ControlUnit) {
        SC_METHOD(process);
        sensitive << opcode << flagN << flagZ;
        std::cout << "New component - ControlUnit" << std::endl;
    }
};

#endif