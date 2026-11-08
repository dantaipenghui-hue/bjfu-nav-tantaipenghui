#ifndef TASK2_SWAP_HPP
#define TASK2_SWAP_HPP

// 传值：交换的只是形参副本，原变量不受影响
void swapByValue(int a, int b);

// 传指针：通过地址直接修改原变量
void swapByPointer(int *a, int *b);

// 传引用：形参就是原变量的别名
void swapByReference(int &a, int &b);

#endif // TASK2_SWAP_HPP
