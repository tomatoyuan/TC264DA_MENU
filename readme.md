# 适配 TC264 单片机的菜单

大二参加了智能车比赛，充实而快乐，结识了很多好友，能力也得到了提升。

校内赛时期使用的是 TC264 单片机，为了方便调试，避免反复烧录代码，搭配 flash 写了一个功能比较完整的菜单。

>   可以方便的利用菜单项中的指针函数 调用调试函数 或者 修改参数 。
>
>   只需要简单修改接口和引脚就可以适配其他单片机。

## 零. 代码结构说明

`source` 中是代码的实现部分：

```
-source
    Cpu0_Main.c
    Cpu0_Main.h
    Cpu1_Main.c
    Function.c
    Function.h
    Menu.c
    Menu.h
    Param.c
    Param.h
    SmartCar_Isr.c
    SmartCar_Isr.h
```

TC264 是双核单片机，但是暂时还没用起来，只用到CPU0。 `Cpu0_Main.c` 是 Cpu0 的主函数（函数入口）。

*   `Menu.c` 中实现了菜单的基本结构和与按键的交互，菜单页或者项的增加在这里实现；
*   `Function.c` 中实现了参数修改等函数；
*   `Param.c` 中定义了一些全局变量，是需要加入菜单进行修改的参数。

## 一、基本功能

+ **1. 菜单结构:** 

    - [ ] **多级菜单 ：** 实现多级菜单（即在菜单中包含能够跳转子菜单的条目）。
    - [ ] **翻页/滚动效果：** 对于同级菜单，实现滚动效果。

+ **2. 数据操作：**

    - [ ] **数据绑定：** 需要调整的参数为在其他文件中定义的全局变量，要绑定到菜单中修改。
    - [ ] **多态（支持两种数据类型）：** 小车可调的参数包括 `int32` 和 `float` 型两种。同时支持对于这两种类型的修改。
    - [ ] **数据修改：** 菜单能够实时修改对应参数。有两种调参方式：快速调参/跳转新界面按数量级调参。
    - [ ] **设置档位：** 考虑到智能车比赛的复杂性，一般设置多个档位（即每个档位都是一套独立的参数，针对不同车况进行调节），并能通过菜单来切换当前调节的挡位。

+ **3. Flash存取：**

    Flash存储器掉电不消失，把参数存入Flash可以避免重新烧程序后参数改变或消失。

    - [ ] **数据读取：** 使用底层库中的Flash读写程序进行数据读取。单片机上电后，能够实现自动从单片机Flash读入菜单参数。
    - [ ] **数据写入：** 菜单同样应有将参数存入Flash的功能，考虑到Flash的物理原理，过多的擦除操作会显著降低其寿命。设计一个减少擦除次数的策略，不用一修改参数就存储。

## 二、拓展性

- **菜单项添加：** 添加一个菜单项，修改代码方便。
- **菜单项删除：** 删除中间的一个菜单项，修改代码方便。
- **菜单结构变更：** 对于多级菜单，添加一级菜单方便。

## 三、用户体验

- **代码规范：** 遵守代码规范，添加足够的注释。
- **屏幕刷新策略：** 关爱视力，保护眼睛。尽量降低屏幕刷新频率。
- **状态栏：** 菜单界面的第一行为状态栏：
    - [ ] **滚动菜单** 实现了一个指示器，用以提示用户当前光标指向的条目是该级菜单的第几项。

## 四、视频演示

见 `菜单操作演示.mp4` 文件。