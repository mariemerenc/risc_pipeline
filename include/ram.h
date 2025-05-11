#ifndef RAM_H
#define RAM_H

#include <systemc.h>
#include <vector>
#include <string>

template<typename TData = sc_uint<32>, int TSize = 256>
SC_MODULE(RAM) {
    sc_in<bool> clock{"clock"};
    sc_in<bool> enable{"enable"};
    sc_in<bool> write{"write"};
    sc_in<sc_uint<9>> address{"address"};
    sc_in<TData> dataIn{"dataIn"};
    sc_out<TData> dataOut{"dataOut"};

    sc_signal<TData> *memory;

    std::string moduleName;

    void process();

    void load(const std::vector<TData>& data);
    void print(int count);

    SC_CTOR(RAM) {
        std::cout << "New component - RAM" << std::endl;
        moduleName = name();
        memory = new sc_signal<TData>[TSize];

        SC_THREAD(process);
        sensitive << clock.pos();
    }

    ~RAM() {
        delete[] memory;
    }
};

template<typename TData, int TSize>
void RAM<TData, TSize>::process() {
    while (true) {
        wait();
        if (enable.read()) {
            if (write.read()) {
                memory[address.read()] = dataIn.read();
            } else {
                dataOut.write(memory[address.read()]);
            }
        }
    }
}

template<typename TData, int TSize>
void RAM<TData, TSize>::load(const std::vector<TData>& data) {
    for (size_t i = 0; i < data.size() && i < TSize; ++i) {
        memory[i] = data[i];
    }
}

template<typename TData, int TSize>
void RAM<TData, TSize>::print(int count) {
    for (int i = 0; i < count && i < TSize; ++i) {
        std::cout << moduleName << "[" << i << "] = " << memory[i] << std::endl;
    }
    std::cout << std::endl;
}

#endif
