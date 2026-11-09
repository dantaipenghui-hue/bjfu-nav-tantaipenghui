# bjfu-nav-tantaipenghui

BJFU 森林狼战队算法组 · 零基础培训个人练习仓库（Git / GitHub + C++ 基础）。

## 仓库结构

```text
.
├── README.md               # 本文件：仓库说明与验收指引
├── .gitignore              # C++ 构建产物与编辑器配置忽略规则
├── task1/                  # 任务一：Ubuntu 22.04 环境部署与 Git 基础操作
│   ├── README.md           # 部署方法、环境验证与整改对照
│   ├── commands.md         # 终端常用命令练习笔记
│   └── screenshots/        # 环境验证截图
└── task2/                  # 任务二：C++ 基础练习 + VS Code 断点单步调试
    ├── README.md           # 工程说明、调试步骤与截图讲解
    ├── CMakeLists.txt      # CMake 构建脚本
    ├── include/            # 头文件
    ├── src/                # hello_world / score_stats / swap 源码
    ├── scores.txt          # score_stats 输入数据
    └── screenshots/debug/  # 01~15 断点单步调试截图（按顺序）
```

## 任务索引

| 任务 | 内容 | 文档 |
| ---- | ---- | ---- |
| task1 | Ubuntu 22.04 环境部署与 Git 基础操作 | [task1/README.md](./task1/README.md) |
| task2 | C++ 基础练习（hello_world / score_stats / swap）+ VS Code 断点单步调试 | [task2/README.md](./task2/README.md) |

## 快速验收 task2

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

断点与单步调试截图（01~15，按顺序编号）见
[task2/screenshots/debug](./task2/screenshots/debug/)，逐张说明见
[task2/README.md](./task2/README.md#五vs-code-断点单步调试截图按顺序)。

## 分支说明

`dev` 分支上的修改已合并回 `main`，当前 `main` 为唯一有效分支，仓库内容以 `main` 为准。
