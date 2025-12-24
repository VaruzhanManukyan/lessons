#include <iostream>

void processData(int value) {
#ifdef DEBUG
    std::cout << "[DEBUG] Start processData, value = " << value << std::endl;
#endif

    int result = value * 2;

#ifdef DEBUG
    std::cout << "[DEBUG] Computed result = " << result << std::endl;
#endif

    std::cout << "Result: " << result << std::endl;
}

int main() {
    std::cout << "start program" << std::endl;
#ifdef DEBUG
    std::cout << "[DEBUG] Program started in debug mode" << std::endl;
#endif

    processData(10);

    std::cout << "finished program" << std::endl;
#ifdef DEBUG
    std::cout << "[DEBUG] Program finished" << std::endl;
#endif

    return 0;
}