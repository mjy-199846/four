#include "game.h"
#include <stdio.h>
//初始化五子棋游戏
void GameInit(Game* g)
{
    //遍历棋盘，全部清空为empty
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            g->board[i][j] = EMPTY;
        }
    }
  g->currentPlayer = BLACK;//默认黑棋先手
  g->stepCount = 0;//开局有效步数为0
    g->state = GAME_RUNNING;//开局游戏处于进行状态
}
//落子
DropResult GameDrop(Game* g, int x, int y)
{
    //判断坐标是否超出棋盘
    if(x < 0 || x >= ROW || y < 0 || y >= COL)
    {
        return DROP_ILLEGAL;
    }
    //判断这个位置上有没有棋子，避免重复落子
    if(g->board[x][y] != EMPTY)
    {
        return DROP_OCCUPIED;
    }
   //满足上方两个条件即可落子
   g->board[x][y] = g->currentPlayer;
   return DROP_OK;
}
//在游戏进行的前提下，检查是否五子相连
void GameCheckState(Game* g)
{
    //如果游戏语=已经分出胜负就不再判断
    if(g->state != GAME_RUNNING)
    return;
    //双层遍历棋盘上每一个格子
    for(int i= 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
           int chess = g->board[i][j];//保存当前棋子值
            if(chess == EMPTY) continue; // 空格子跳过 
            //四个方向水平、竖直、右斜下、左斜下
            // dx dy：方向增量
            int dir[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};//不需要反向，循环会遍历到另一端棋子
            for(int d = 0; d < 4; d++)
            {
                int count = 1; // 连续棋子计数，当前这个棋子本身算1颗
                //沿当前方向往前走一步
                int nx = i + dir[d][0];
                int ny = j + dir[d][1];
                // 沿着这个方向，统计连续相同棋子数量
                while(nx>=0 && nx<ROW && ny>=0 && ny<COL && g->board[nx][ny]==chess)//下一格棋子和当前棋子颜色一样
                {
                    count++;
                    nx += dir[d][0];
                    ny += dir[d][1];
                }
                // 连成5颗及以上，判定胜利
                if(count >= WIN_COUNT)
                {
                    if(chess == BLACK)
                        g->state = GAME_BLACK_WIN;
                    else
                        g->state = GAME_WHITE_WIN;
                    return; // 判定胜负，直接退出整个函数，不用继续遍历
            }
        }
    }
}
// 判断平局：棋盘填满没有空位
    int emptyNum = 0;
    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
            if(g->board[i][j]==EMPTY) emptyNum++;//若格子为空，空格子数量+1
    if(emptyNum == 0)
    {
        g->state = GAME_DRAW;//判平局
    }
}
