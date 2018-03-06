# qqGame-LinkUp-Mahjong-CheatProgram
一个用于QQ游戏中单层连连看的方块消除辅助，方式为模拟鼠标点击。使用前建议用Cheat Engine重新查找方块矩阵首地址，并修改相对应代码。
1. 准备工具：Cheat Engine、spy++、Snipaste（或其他截图工具）、vs2015（或其他c/c++ IDE）
2. 原理： 通过CE获取连连看矩阵信息，利用map将各方块进行归类，以方块的类型（像炸弹、小球等）作为map的索引、以记录该方块所有出现坐标的list作为map的value。最终模拟鼠标点击事件来实现方块消除。
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/01.png)
