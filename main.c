#include "game.h"
#include "console.h"
#include <stdio.h>

int main()
{
    // 定义游戏实例、控制台交互实例
    Game game;
    Console con;

    // 初始化控制台，开启鼠标监听
    ConsoleInit(&con);
    // 初始化棋盘数据+打印初始棋盘界面
    ConsoleInitBoard(&con, &game);

    // 游戏主循环：游戏处于进行状态时持续循环
    while(game.state == GAME_RUNNING)
    {
        // 读取鼠标事件
        if(ConsoleReadMouse(&con))
        {
            // 鼠标点击触发：屏幕坐标转棋盘坐标
            ConsoleMouseToBoard(&con);
            // 执行落子操作
            ConsoleDoDrop(&con, &game);
            // 落子后刷新棋盘画面
            ConsoleInitBoard(&con, &game);
        }
    }

    // 游戏结束，输出对局结果
    if(game.state == GAME_BLACK_WIN)
    {
        printf("游戏结束 玩家BLACK获胜 \n");
    }
    else if(game.state == GAME_WHITE_WIN)
    {
        printf("游戏结束 玩家WHITE获胜 \n");
    }
    else if(game.state == GAME_DRAW)
    {
        printf("游戏结束！棋盘填满，平局！\n");
    }
    printf("本局有效落子总步数：%d\n", game.stepCount);
    ConsoleRelease(&con);
    return 0;

}