#ifndef REGISTER_BASE_H
#define REGISTER_BASE_H

#include <systemc.h>

template<typename TData = sc_uint<32>, int TSize = 32>
SC_MODULE(RegisterBase) {
    sc_in<bool> clock;
    sc_in<bool> enable;
    sc_in<bool> write;

    sc_in<sc_uint<8>> addressSource1;
    sc_in<sc_uint<8>> addressSource2;
    sc_in<sc_uint<9>> addressDest;

    sc_in<TData> dataToWrite;
    sc_out<TData> dataSource1;
    sc_out<TData> dataSource2;

    sc_signal<TData>* regdata;

    void process();

    void print(int count);

    SC_CTOR(RegisterBase) {
        std::cout << "New component - Register Base" << std::endl;
        regdata = new sc_signal<TData>[TSize];
        SC_METHOD(process);
        sensitive << clock.pos();
    }

    ~RegisterBase() {
        delete[] regdata;
    }
};

template<typename TData, int TSize>
void RegisterBase<TData, TSize>::process() {
    if (enable.read()) {
        if (write.read()) {
            regdata[addressDest.read()] = dataToWrite.read();
        } else {
            dataSource1.write(regdata[addressSource1.read()]);
            dataSource2.write(regdata[addressSource2.read()]);
        }
    }
}

template<typename TData, int TSize>
void RegisterBase<TData, TSize>::print(int count) {
    for (int i = 0; i < count && i < TSize; ++i) {
        std::cout << "[" << i << "] = " << regdata[i] << std::endl;
    }
    std::cout << std::endl;
}

#endif
