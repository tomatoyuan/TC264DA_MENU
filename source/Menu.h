/*
 * Menu.h
 *
 *  Created on: 2021年10月15日
 *      Author: awellfrog
 */

#ifndef SOURCE_MENU_H_
#define SOURCE_MENU_H_


#include "Param.h"
#include "Function.h"
#include "SmartCar_Oled.h"
#include "SmartCar_Systick.h"
#include <stdlib.h>
#include "SmartCar_Flash.h"
#include "SmartCar_GPIO.h"

/** Flash 读取，在"SmartCar_Flash.h"中定义了，如果链接不上，将下面的定义解注释即可  */
//#define Page_Read(sector_num,page_num,type) (*(type *)((uint32)((EEPROM_BASE_ADDR + (sector_num)*EEPROM_SECTOR_SIZE)+ ((page_num)*8))))

extern uint32 Current_Gear; // 当前模式

/** 五项按键定义 */
#define BT_UP       1
#define BT_OK       2
#define BT_RIGHT    3
#define BT_DOWN     4
#define BT_LEFT     5

#define SHOW_LINE   7                   // 屏幕显示行数（除去最上一层）

extern int8 aaa[20];                    // 用于将不同类型数据转为 int8 型显示
extern uint32 key;                      // 按键读取
extern uint32 Times;

/** 用于显示光标位置 */
extern uint32 selectItem_current, selectItem_hidden, selectItem;
      /* 当前在第几行              前面隐藏的行数    光标在当前目录的位置*/

/******参数加入***************************************************************************/

/***类型设置******/
enum Parameter_Type {
    uint32_T = 1, float_T = 2, gear_T = 4
};


/** 参数信息设置 */
typedef struct Para {
        int8 *Para_Name_Output; // 参数名称
        void *Parameter;        // 当前参数值
        uint32 Parameter_Type;  // 需要修改的参数类型 0 -> int8  1->uint32  2->float
        uint32 Save_order;      // 删除一个参数仍然不会读取错误
} _Para;

/** 菜单目录 */
typedef struct MenuItem {
        uint32 MenuCount;               // 当前菜单项总数
        int8 *DisplayString;            // 当前项目要显示的字符
        _Para Para_information;
        void(*Subs) ();                 // 选择某一菜单后执行的功能函数
        struct MenuItem *Child_Menus;   // 当前项目的子菜单
        struct MenuItem *Parent_Menus;  // 当前项目的父菜单
} _MENU;

extern _MENU *MenuPoint;                // 当前菜单的地址

/** 主菜单生成
 * MainMenu_NUM                         主菜单的选项数
 * MainMenu_F                           主菜单的上一级目录
 * MainMenu[MainMenu_NUM]               存放主菜单选项的数组
 * */

// 添加一个子菜单，需要修改一下目录数，Para文档中加入声明，加一行菜单

#define MainMenu_NUM 9                  // 目录子项数
#define MainMenu_F NULL                 // 指向上一级的指针
extern _MENU MainMenu[MainMenu_NUM];

#define Setmenu1_NUM 3
#define Setmenu1_F MainMenu
extern _MENU Setmenu1[Setmenu1_NUM];

#define Setmenu2_NUM 6
#define Setmenu2_F MainMenu
extern _MENU Setmenu2[Setmenu2_NUM];

#define Setmenu3_NUM 4
#define Setmenu3_F MainMenu
extern _MENU Setmenu3[Setmenu3_NUM];

#define Setmenu11_NUM 2
#define Setmenu11_F Setmenu1
extern _MENU Setmenu11[Setmenu11_NUM];


/** 用于存储光标信息 */
typedef struct Mouse{
        struct Mouse *pre;
        uint32 Cur_Select;
        uint32 Hid_Select;
} _MOUSE;

extern _MOUSE *Mouse_pos;

/** 菜单初始化：建立文件夹级次关系 */
void Menu_Init();

/** 利用五项按键控制菜单选择，实现了滚动翻页
 * key 传入的按键操作
 * */
void Run_Menus(uint32 key);

/** 显示菜单和光标位置
 * MenuPoint                            当前菜单的指针地址
 * selectItem_current                   当前光标在屏幕的第几行
 * selectItem_hidden                    菜单有几行被隐藏在屏幕上方
 * selectItem                           目前光标在当前菜单的第几行
 * */
void Display(_MENU * MenuPoint, uint32 selectItem_current, uint32 selectItem_hidden, uint32 selectItem);

/** Flash写入（保存） */
void Save_para();


#endif /* SOURCE_MENU_H_ */
