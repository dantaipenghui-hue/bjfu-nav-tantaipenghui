#include "swap.hpp"

#include <iostream>

int main()
{
    int x = 10;
    int y = 20;

    std::cout << "初始:        x = " << x << ", y = " << y << '\n';

    swapByValue(x, y);
    std::cout << "传值后:      x = " << x << ", y = " << y << "   <- 没有交换\n";

    swapByPointer(&x, &y);
    std::cout << "传指针后:    x = " << x << ", y = " << y << "   <- 交换了\n";

    swapByReference(x, y);
    std::cout << "传引用后:    x = " << x << ", y = " << y << "   <- 又交换回来\n";

    return 0;
}
