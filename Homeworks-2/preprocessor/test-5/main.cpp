#include <iostream>

#define CONCAT(a, b) a##b
#define DECLARE_VARIABLE(num) int CONCAT(variable_, num) = num * 100;

#define REPEAT_0 DECLARE_VARIABLE(0)
#define REPEAT_1 REPEAT_0 DECLARE_VARIABLE(1)
#define REPEAT_2 REPEAT_1 DECLARE_VARIABLE(2)
#define REPEAT_3 REPEAT_2 DECLARE_VARIABLE(3)
#define REPEAT_4 REPEAT_3 DECLARE_VARIABLE(4)
#define REPEAT_5 REPEAT_4 DECLARE_VARIABLE(5)

#define REPEAT(num) REPEAT_##num

int main() {
    REPEAT(3)

    std::cout << variable_0 << " " << variable_1 << " " << variable_2 << " " << variable_3<< std::endl;

    return 0;
}
