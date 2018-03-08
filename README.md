# qqGame-LinkUp-Mahjong-CheatProgram
一个用于QQ游戏中单层连连看的方块消除辅助，方式为模拟鼠标点击。使用前建议用Cheat Engine重新查找方块矩阵首地址，并修改相对应代码。
1. 准备工具：Cheat Engine、spy++、Snipaste（或其他截图工具）、vs2015（或其他c/c++ IDE）
2. 原理： 通过CE获取连连看矩阵信息，利用map将各方块进行归类，以方块的类型（像炸弹、小球等）作为map的索引、以记录该方块所有出现坐标的list作为map的value。最终模拟鼠标点击事件来实现方块消除。
3. 现贴出相关数据的获得途径，具体的程序设计可参考代码。
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/01.png)


### CE查找矩阵首地址
1. 登录qq游戏大厅，找个空房间启动游戏
2. 启动CE，载入“QQ游戏--连连看角色版”
3. 在游戏中点击练习</br>
（1）若游戏中方块矩阵首无方块，则在CE中“精确扫描”扫描值 0.（数值类型为“1字节”）</br>
（2）若游戏中方块矩阵首有方块，则在CE中“值大于”扫描值 0（数值类型为“1字节”）</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/02.png)
4. 重复上面3的步骤，直到地址列表内仅剩一个地址，即为方块矩阵首地址</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/03.png)

### spy++获取窗口、矩阵信息（vs下有集成）
1. 打开spy++与连连看程序。
2. 如图，获取连连看程序进程名（便于获取游戏窗口句柄）。</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/04.png)</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/05.png)</br></br>


3. 如图，获取连连看首方块位置，获取其xPos、yPos，便于鼠标定位。</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/06.png)</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/07.png)</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/08.png)</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/09.png)</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/10.png)</br></br>


4. 使用截图工具，截取一个方块的图片,测量图片尺寸为（31×35）,即获得方块尺寸为（31×35）。</br>
![image](https://github.com/Gaveu/qqGame-LinkUp-Mahjong-CheatProgram/blob/master/LLKfuzhu/picture/11.png)
