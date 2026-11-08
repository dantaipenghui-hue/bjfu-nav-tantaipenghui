#include "score_stats.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    // 支持命令行传文件名：./score_stats scores.txt；不传则默认 scores.txt
    const std::string path = (argc > 1) ? argv[1] : "scores.txt";

    std::ifstream fin(path);
    if (!fin)
    {
        std::cerr << "无法打开文件: " << path << '\n';
        return 1;
    }

    // 第一行：分数个数
    int n = 0;
    fin >> n;
    if (!fin || n <= 0)
    {
        std::cerr << "文件格式错误：第一行应为正整数（分数个数）\n";
        return 1;
    }

    // 随后读取 n 个分数
    std::vector<double> scores(n);
    for (int i = 0; i < n; ++i)
    {
        if (!(fin >> scores[i]))
        {
            std::cerr << "文件中的分数不足 " << n << " 个\n";
            return 1;
        }
    }

    std::cout << "最大值: " << maxScore(scores) << '\n';
    std::cout << "最小值: " << minScore(scores) << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "平均值: " << averageScore(scores) << '\n';
    std::cout << std::defaultfloat << std::setprecision(6);

    std::vector<double> sorted = sortDescending(scores);
    std::cout << "从高到低: ";
    for (size_t i = 0; i < sorted.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << ' ';
        }
        std::cout << sorted[i];
    }
    std::cout << '\n';
    return 0;
}
