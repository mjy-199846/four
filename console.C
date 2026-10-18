#include "console.h"
#include <stdio.h>
//初始化控制台，开始鼠标事件捕获
//con为控制台结构体指针
void ConsoleInit(Console* con)
{
    //获取句柄：控制台输入鼠标键盘等
    con->hIn = GetStdHandle(STD_INPUT_HANDLE);
//STD_OUTPUT_HANDLE：标准输出设备，控制台黑色窗口屏幕
//获取句柄：控制台屏幕输出，移动光标使用
    con->hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;//DWORD：windows.h定义的无符号长整数类型，用来保存控制台模式标记
    //获取控制台当前输入模式
    GetConsoleMode(con->hIn, &mode);//GetConsoleMode：WindowsAPI，读取当前控制台输入所有开关状态，存入mode变量
    //修改控制台模式，开启鼠标事件捕获
    SetConsoleMode(con->hIn, mode | ENABLE_MOUSE_INPUT);
    
}
//读取鼠标事件，左键点击
int ConsoleReadMouse(Console* con)
{
    //INPUT_RECORD：windows控制台输入事件结构体，可以捕获鼠标，键盘事件
    INPUT_RECORD rec;
    //rec局部变量，临时存放，函数执行结束就销毁
    DWORD cnt;
    //保存本次读取，实际读到了多少条输入条件
    if (!ReadConsoleInput(con->hIn, &rec, 1, &cnt))
    //读取控制台输入事件，传地址
    {
        return 0;
    }
    //判断事件类型：是否为鼠标事件
if(rec.EventType == MOUSE_EVENT)
{
    //取出鼠标事件数据
    MOUSE_EVENT_RECORD* me = &rec.Event.MouseEvent;
    //MOUSE_EVENT_RECORD：鼠标事件子结构体，存放鼠标坐标、哪个按键按下。
   //&rec.Event.MouseEvent：取鼠标事件部分的地址，赋值给指针me，后面用me访问鼠标信息

    //鼠标字符坐标保存进Console结构体mousePos
    con->mousePos = me->dwMousePosition;
     
    //判断，是否按下鼠标左键
    //FROM_LEFT_1ST_BUTTON_PRESSED 代表鼠标左键按下的标记位
    if(me->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
    //dwButtonState：记录鼠标按键状态，二进制每一位代表一个按键
    {
        return 1;
    }
    }  
    return 0;
} 
//鼠标屏幕坐标转为棋盘数组行列下标
//con控制台结构体，输入mousePos，输出boardRow boardCol
void ConsoleMouseToBoard(Console* con)
{
    //每个棋子占两个字符，横向x坐标每增加2，对应棋盘的一列；y方向每一行打印一行棋盘，y值等于棋盘行下标
    con->boardCOL = con->mousePos.X / 2;
    con->boardRow = con->mousePos.Y;
}

void ConsoleInitBoard(Console* con, Game* g)
{
        // 调用game模块函数，初始化游戏数据：清空棋盘、设置游戏状态、设置先手玩家
    GameInit(g);
// COORD,Windows坐标结构体，X=0,Y=0代表控制台左上角位置
    COORD pos = {0,0};
    // 将光标移动到控制台左上角，实现刷新屏幕，覆盖旧画面，不产生大量滚动
    SetConsoleCursorPosition(con->hOut, pos);
    //SetConsoleCursorPosition WindowsAPI：移动控制台光标
    printf("====五子棋游戏====\n");
    // 遍历棋盘所有行
    for(int i=0; i<ROW; i++)
    {
        // 遍历棋盘所有列
        for(int j=0; j<COL; j++)
        //两层循环：i控制行，j控制列，完整遍历二维数组board
        {
            // 打印棋盘格子内容，空格=空棋盘，black/white=玩家棋子
            printf("%c ", g->board[i][j]);
          }
          // 一行棋盘打印完成，换行
        printf("\n");

    }
}
//落子
void ConsoleDoDrop(Console* con, Game* g)
{
    // 取出转换后的棋盘行列坐标
    int r = con->boardRow;
    int c = con->boardCOL;
    // 调用游戏模块落子函数，尝试在r行c列落子
    DropResult ret = GameDrop(g, r, c);
    // 判断落子结果
    //落子成功
    if(ret == DROP_OK)
    {
        g->stepCount++;//有效步数+1
        // 落子成功后，调用游戏模块函数，检查是否分出胜负或者平局
        GameCheckState(g);
        // 切换玩家：X玩家下完轮到O，O下完轮到X
        if(g->currentPlayer == "BLACK")
            g->currentPlayer = "WHITE";
        else
            g->currentPlayer = "BLACK";

}
// 如果落子失败（越界/已有棋子），什么都不做，等待下一次点击
}