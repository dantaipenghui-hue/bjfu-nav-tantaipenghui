# bjfu-nav--tantaipenghhui-

bjfu-forest wolf-

## 简介

这是 BJFU 用于 Git / GitHub 培训的个人练习仓库（已合并 main 与 dev 两分支的修改）。

## 任务目录

| 任务 | 内容 | 文档 |
| ---- | ---- | ---- |
| task1 | Ubuntu 22.04 环境部署与 Git 基础操作 | [task1/README.md](./task1/README.md) |
| task2 | C++ 基础练习（hello_world / score_stats / swap）+ VS Code 断点单步调试 | [task2/README.md](./task2/README.md) |

## 快速验证 task2

干净终端中 clone 后按下面步骤即可一次编译通过：

```bash
git clone git@github.com:dantaipenghui-hue/bjfu-nav-tantaipenghui.git
cd bjfu-nav-tantaipenghui/task2

cmake -S . -B build
cmake --build build

./build/hello_world            # Hello World
./build/score_stats scores.txt # 最大值 96 / 最小值 78 / 平均值 87.80 / 从高到低 96 92 88 85 78
./build/swap                   # 传值不交换，传指针/传引用交换成功
```

三个程序的断点与单步调试截图（01~15，按顺序编号）见
[task2/screenshots/debug](./task2/screenshots/debug/)，对应说明见 [task2/README.md](./task2/README.md#五vs-code-断点单步调试截图按顺序)。
