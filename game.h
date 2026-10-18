//头文件保护宏，防止头文件被多次包含，造成重复定义报错
#ifndef __GAME_H__
#define __GAME_H__

//定义棋盘常量
#define ROW 9   //9行
#define COL 9   //9列
#define EMPTY 0  //格子为空，没有棋子
#define BLACK 1  //数字1为黑棋
#define WHITE 2  //数字2为白棋
#define WIN_COUNT 5  //获胜条件:连成5颗棋子

// game state-枚举法
typedef enum {
    GAME_RUNNING,//正在进行
    GAME_BLACK_WIN,//黑棋获胜
    GAME_WHITE_WIN,//白棋获胜
   GAME_DRAW//下满，平局
} GAMEState;

//枚举落子结果
typedef enum 
{
    DROP_OK,//落子成功
    DROP_ILLEGAL,//非法落子（下在棋盘外面）
    DROP_OCCUPIED//已有棋子，无法落子

} DropResult;

//game struct-打包数据
typedef struct
{
    int board[ROW][COL];//棋盘二维数组
    int currentPlayer;//轮到谁下棋
    GAMEState state;//当前游戏状态
    int stepCount;//有效步数计数
} Game;

//函数声明
//初始化游戏：清空棋盘，开局默认黑棋先走
void GameInit(Game* g);//GAME*指针，函数直接修改原始棋盘数据
//落子函数：传入游戏对象，坐标，返回落子结果
DropResult GameDrop(Game* g, int x, int y);

//判断输赢，更新游戏状态
void GameCheckState(Game* g);
//打印棋盘
void GamePrint(const Game* g);
#endif//头文件保护结束，和开头配对




