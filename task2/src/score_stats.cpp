#include "score_stats.hpp"

#include <algorithm>
#include <functional>
#include <numeric>

double maxScore(const std::vector<double> &scores)
{
    return *std::max_element(scores.begin(), scores.end());
}

double minScore(const std::vector<double> &scores)
{
    return *std::min_element(scores.begin(), scores.end());
}

double averageScore(const std::vector<double> &scores)
{
    return std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
}

std::vector<double> sortDescending(std::vector<double> scores)
{
    std::sort(scores.begin(), scores.end(), std::greater<double>());
    return scores;
}
