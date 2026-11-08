#ifndef TASK2_SCORE_STATS_HPP
#define TASK2_SCORE_STATS_HPP

#include <vector>

// 返回最高分
double maxScore(const std::vector<double> &scores);

// 返回最低分
double minScore(const std::vector<double> &scores);

// 返回平均分
double averageScore(const std::vector<double> &scores);

// 返回从高到低排序后的副本（不修改原 vector）
std::vector<double> sortDescending(std::vector<double> scores);

#endif // TASK2_SCORE_STATS_HPP
