//定义Console结构体，声明控制交互台的全部函数
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

// 引入游戏模块头文件，使用Game结构体、枚举、落子返回类型DropResult
#include "game.h"
// Windows系统头文件，用于控制台句柄、鼠标事件、坐标COORD等Windows控制台API
#include <windows.h>

typedef struct 
{
    HANDLE hIn;//输入句柄，读取控制台内鼠标点击事件
    HANDLE hOut;//输出句柄，用来向控制台输出内容，移动光标位置，刷新屏幕
    COORD mousePos;//储存鼠标坐标
    int boardRow;//棋盘行号
    int boardCOL;//棋盘列号


}Console;
//==========函数声明部分==========
//初始化控制台
void ConsoleInit(Console* con);
//读取控制台鼠标事件
int ConsoleReadMouse(Console* con);
//将控制台鼠标屏幕坐标，转换为棋盘数组下标（行列）
void ConsoleMouseToBoard(Console* con);
//初始化棋盘画面，打印棋盘界面
void ConsoleInitBoard(Console* con,Game* g);
//执行落子操作
void ConsoleDoDrop(Console* con, Game* g);
#endif


