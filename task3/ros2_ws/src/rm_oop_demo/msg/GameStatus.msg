std_msgs/Header header

# 比赛阶段，对齐 RM 裁判系统 game_progress 字段
# 0 未开始 1 准备阶段 2 自检 3 倒计时 4 比赛中 5 结算
uint8 game_progress

# 当前阶段剩余时间（秒）
uint16 stage_remain_time

# 当前局数 / 总局数
uint16 current_round
uint16 total_rounds
