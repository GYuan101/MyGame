# MyGame

塔防游戏
===
基于口袋妖怪的怪兽形象作为防御塔（4-6）和敌军（4-6）,建立不同地图（3-6）<br> 
由QT实现（基于QTMap）<br> 

5.9
---
建立项目，开始搜集素材、编写代码<br> 

5.16
---
完成了素材搜集，并进行像素大小调整（map1080*960， obj64*64）<br> 
配置OpenCV并使用图片截取、拼接功能（include lib）<br> 
rpgobj Charmander素材截取完成，可升级两次的三个形态，后两种形态可面向八个方向攻击，每个攻击动作包含蓄力和进攻<br> 
部分攻击方向不存在素材图片，使用mirrored进行镜像翻转和scaled进行大小调整<br> 
导入全地图并且找到敌军道路的主要坐标，将测试obj放在道路上<br> 
匹配地图道路和素材大小，将可移动的步幅变为0.5*64<br> 
建立rpgobj的派生类Guard，作为玩家可操作的tower，可以根据wasd进行移动和交战<br> 
将rpgobj中的OnErase和Move定义为虚函数，由派生类实现<br> 
将rpgobj的取值定义为两层枚举变量，objtype和objstate（由于攻击动作较多取值较多）<br> 
更改initobj的参数，考虑objtype、objstate、string，string为了FindICON而添加，另一种思路是对FindICON进行重载以便根据enum类型搜索，<br> 
只不过需要建立string和enum之间的同名转换，由于不存在直接的转换函数如tostring（java），过于繁琐；<br> 
解决了无效外部链接的问题，抽象类不能实例化，基类虚函数不能无实现；<br> 

! [5.16效果图] (https://github.com/GYuan101/MyGame/blob/master/5.16show.png)

### 问题：
QMediaplayer找不到文件，include后全篇飙红<br> 

### 下面解决：
素材图片的背景透明化<br> 
每种攻击状态的连续播放（Qtimer，repaint）<br> 
地图网格化，确定防御塔位置<br> 
三个出怪口随机按时间出怪<br> 
完成rpgobj派生类tower<br> 
提取2-3种防御塔图片素材，2-3种怪兽素材<br> 
怪兽血条建立<br> 
防御塔根据怪兽位置进行转向<br> 
攻击特效素材提取<br> 
金币、升级系统<br> 
音乐tm的怎么办<br> 
