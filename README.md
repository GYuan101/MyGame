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
更改initobj的参数，考虑objtype、objstate、string，string为了FindICON而添加，
另一种思路是对FindICON进行重载以便根据enum类型搜索，<br> 
只不过需要建立string和enum之间的同名转换，由于不存在直接的转换函数如tostring（java），过于繁琐；<br> 
解决了无效外部链接的问题，抽象类不能实例化，基类虚函数不能无实现；<br> 

! [5.16效果图] (https://github.com/GYuan101/MyGame/blob/master/5.16show.png)

5.20
---
素材图片的背景透明化<br> 
地图网格化，确定防御塔位置，选定了几个可能的防御塔所在的坐标，根据0.5维步长可以找到地图上道路的坐标轨迹，
存在static const QList<QList<double>>中<br> 
三个出怪口随机按时间出怪，建立第二个槽函数每2s更新一次，增加一个怪兽，最多一百只，怪兽出生点和出生形态随机产生<br> 
完成怪兽在道路上行走，并且在道路进到转向，重新建立obj（更换怪兽方向）<br> 
用static vector<Monster>存在所有怪兽的坐标和信息<br> 
出现问题initmonster好好的，但是出了这个函数在另一个文件保存的monster信息的一个枚举变量出现乱码，不知道出现什么问题
  解决方法，用两层友元函数，由monster到rpgobj再到icon，在init之后对icon.objstate重新赋值，可间接解决问题<br> 

5.22
---
完成rpgobj派生类tower<br> 
实现了tower类，每个对象有一个mymonster的vector还是list，存放在这个tower攻击范围之内的怪兽指针，所有怪兽在world对象的静态vetor里存储<br>
每次怪兽移动，都会更新每个塔的mymonster容器，遍历并且将离开攻击范围的怪兽指针删除，将其指针存入freemonster的list容器，<br>
用来存放所有的无法被攻击到的怪兽<br>
本来考虑使用优先队列的数据结构对mymonster和freemonster进行存储，因为每个tower在怪移动并更新完自己的可攻击范围后，可能需要重新定位攻击的对象（尤其是怪兽死亡和怪兽离开攻击区域）<br>
这里默认会最先攻击离终点最近的怪兽，因此在怪兽下面放一个私有成员更新其距离终点的步数，正好优先队列每次让距离最小的出列，内部的堆结构使得摊还时间复杂度很低，然而发现C++封装的queue容器不能动态更新怪兽的坐标，存指针也不可以，无奈只好选择用vetor存储，希望不要卡帧，而freemonter由于要进行大量的遍历和删除插入动作，考虑可用索引的链表数据结构QList，存储怪兽的指针，但又遇到了很严重的问题：<br><br>
每次move发生，上一次存储的freemonster中的指针出错，有时候怪兽整个飞了，有时候怪兽的私有成员距离（判断是否可攻击、是否需要更新freemonster和mymonster的关键依据），尚未发现问题！一步一步调试，真的就是出了{}就错了，TMD，和上面出现的问题一个性质，当时我把丢了的值重新赋值，但是这次无法找到原址，我想换成引用的QList貌似也不可以，失败失败<br>
防御塔根据怪兽位置进行转向，通过redirect实现，根据怪兽和塔的相对位置，分为八个方向，对应八种怪兽形态<br>
在选定的17个塔基处随机生成（计时）防御塔<br>

### 问题：
QMediaplayer找不到文件，include后全篇飙红<br> 


### 下面解决：
每种攻击状态的连续播放（Qtimer，repaint）<br> 
提取2-3种防御塔图片素材，2-3种怪兽素材（我可能只能拿到这一个素材了对不起）<br> 
怪兽血条建立<br> 
攻击特效素材提取<br> 
金币、升级系统<br>  
实现手动安装塔<br>
