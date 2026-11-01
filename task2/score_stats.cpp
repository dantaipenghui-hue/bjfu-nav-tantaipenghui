#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    int n = 0;
    std::cin >> n;
    if (n <= 0)
    {
        return 0;
    }

    std::vector<double> scores(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> scores[i];
    }

    double maxScore = *std::max_element(scores.begin(), scores.end());
    double minScore = *std::min_element(scores.begin(), scores.end());
    double avg = std::accumulate(scores.begin(), scores.end(), 0.0) / n;

    std::sort(scores.begin(), scores.end(), std::greater<double>());

    std::cout << "最大值: " << maxScore << '\n';
    std::cout << "最小值: " << minScore << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "平均值: " << avg << '\n';
    std::cout << std::defaultfloat << std::setprecision(6);

    std::cout << "从高到低: ";
    for (size_t i = 0; i < scores.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << ' ';
        }
        std::cout << scores[i];
    }
    std::cout << '\n';
    return 0;
}
