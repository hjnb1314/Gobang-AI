#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>
#include <mmsystem.h>
#include <limits.h>
#include <algorithm>
#include <cmath>
#include <math.h>


#define _USE_MATH_DEFINES
#define width  560 //240
#define heigth 560 //320
#define MAX_SCORE 1000000000


#define p1 1		//玩家1
#define p2 2		//玩家2
#define Nochess 0	//空棋


#define N  24		//棋盘格数
#define Grid_wid 	(width/(N-1)) //网格宽度
#define Chess_R  Grid_wid/2  //棋子半径


#define player_player	3		//人人
#define player_AI		4		//人机
#define computer_computer 5  // 机机对战


// 定义全局变量和常量（通常在函数之外）
const int board_size = 15; // 棋盘大小
int chess_board[board_size][board_size]; // 棋盘数组
const int empty = 0; // 空白位置


const int player1 = 1; // 玩家1
int current_player = player1; // 当前玩家
int player = p1;	//默认黑棋先手


int chess[N][N];	//棋盘地图
int chess_num;			//总棋子数


int black_score = 0; // 初始化黑棋分数为0
int white_score = 0; // 初始化白棋分数为0
char param = 0;


int currentPlayer = p1; // 当前玩家，默认黑棋先手
bool isMuted = false;
bool playerIsFirst = true; // 默认情况下，玩家选择先手

// 声明全局变量来存储最后一次下棋的位置
int lastMoveX = -1;
int lastMoveY = -1;


int judge(int x, int y);
int judge_win(int x, int y);
int Chess_piece(int x, int y);
int mod_xy(int xy);
void changeplayer();
void draw_checkboard();
int chessscore(int x, int y, int worb);
void chesscomputer();
void Mouse();
void Start_Game();
void restart();
void exitgame();
void Msg_restart(int par);
void computer_computer_game();
void drawCircle(int x, int y, int radius, int color);
void Oninit(); 
void show_game_rules();
void chesscomputer2();

void chesscomputer2()
{
    int i, j, cscore, cscorel, pscore, pscorel, row1, col1, row2, col2;
    cscore = pscore = 0;
    row1 = row2 = col1 = col2 = -1;
		currentPlayer = p2	;
    // 检查当前是否是电脑下棋
    if (currentPlayer == p2)
    {
        if (chess_num <= 0) // 棋盘为空时
        {
            // 电脑先下在正中间
            row1 = N / 2;
            col1 = N / 2;

            Chess_piece(row1, col1);
        }
        else
        {
            // 电脑下棋的逻辑（仿照chesscomputer()函数）
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                {
                    if (judge(i, j))
                    {
                        cscorel = chessscore(i, j, p2);
                        if (cscorel > cscore)
                        {
                            cscore = cscorel;
                            row1 = i;
                            col1 = j;
                        }
                        pscorel = chessscore(i, j, p1);
                        if (pscorel > pscore)
                        {
                            pscore = pscorel;
                            row2 = i;
                            col2 = j;
                        }
                    }
                }
            }
            if (row1 == -1 && col1 == -1 && row2 == -1 && col2 == -1)//没找到最优解 平局
            {
                Msg_restart(2);
            }
            else
            {
                if (chess_num == 3)
                {
                    Chess_piece(row2, col2);
                }
                else
                {
                    if (cscore > pscore)
                    {
                        Chess_piece(row1, col1);                            
                    }
                    else
                    {
                        Chess_piece(row2, col2);
                    }
                }
            }
        }
        
        // 设置玩家为当前玩家
        currentPlayer = p1;
    }
    // 玩家下棋
    else
    {
        // 玩家下棋的逻辑
        // 仿照chesscomputer()函数，只是将玩家的棋子颜色改为白棋（p1）
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (judge(i, j))
                {
                    cscorel = chessscore(i, j, p1);
                    if (cscorel > cscore)
                    {
                        cscore = cscorel;
                        row1 = i;
                        col1 = j;
                    }
                    pscorel = chessscore(i, j, p2);
                    if (pscorel > pscore)
                    {
                        pscore = pscorel;
                        row2 = i;
                        col2 = j;
                    }
                }
            }
        }
        if (row1 == -1 && col1 == -1 && row2 == -1 && col2 == -1)//没找到最优解 平局
        {
            Msg_restart(2);
        }
        else
        {
            if (chess_num == 3)
            {
                Chess_piece(row2, col2);
            }
            else
            {
                if (cscore > pscore)
                {
                    Chess_piece(row1, col1);                            
                }
                else
                {
                    Chess_piece(row2, col2);
                }
            }
        }

        // 设置电脑为当前玩家
        currentPlayer = p2;
    }
}



//棋子动画效果 
void drawCircle(int x, int y, int radius, int color) {
    setcolor(color);
   for (int r = 0; r <= radius; r++) {
        for (int i = 0; i < 360; i++) {
            int x1 = x + r * cos(i * M_PI / 180);
            int y1 = y + r * sin(i * M_PI / 180);
            putpixel(x1, y1, color);
        }
        if(param == computer_computer){
        	Sleep(5);
		}else{
			Sleep(10);
		}
    }
}


// 在合适的地方更新最后一次下棋的位置
void updateLastMove(int x, int y) {
    lastMoveX = x;
    lastMoveY = y;
}

// 获取最后一次下棋的位置的函数
int getLastMoveX() {
    return lastMoveX;
}
int getLastMoveY() {
    return lastMoveY;
}

void computer_computer_game() {

    int x1, y1, x2, y2; // 声明 x1, y1, x2 和 y2 变量，用于存储下棋位置

    while (1) {

        x1 = y1 = x2 = y2 = -1; // 初始化变量

        chesscomputer2(); // 机器1下棋，不传递参数
        x1 = getLastMoveX(); // 获取最后一次下棋的位置
        y1 = getLastMoveY();

        if (judge_win(x1, y1)) {
            // 处理胜利逻辑
            if (currentPlayer == p1) {
                black_score++; // 黑棋胜利，黑棋分数加1
            } else {
                white_score++; // 白棋胜利，白棋分数加1
            }
            Msg_restart(1); // 显示游戏结束信息
            break;
        }

        // 切换玩家
        currentPlayer = (currentPlayer == p1) ? p2 : p1;

        // 延时一段时间
        //Sleep(1); // 延时 1000 毫秒（1 秒）

        chesscomputer2(); // 机器2下棋，不传递参数
        x2 = getLastMoveX(); // 获取最后一次下棋的位置
        y2 = getLastMoveY();

        if (judge_win(x2, y2)) {
            // 处理胜利逻辑
            if (currentPlayer == p1) {
                black_score++; // 黑棋胜利，黑棋分数加1
            } else {
                white_score++; // 白棋胜利，白棋分数加1
            }
            Msg_restart(1); // 显示游戏结束信息
            break;
        }

        // 切换玩家
        currentPlayer = (currentPlayer == p1) ? p2 : p1;

        // 延时一段时间
        //Sleep(1); // 延时 1000 毫秒（1 秒）
    }
}

void Oninit()
{
	setfillcolor(BLACK);
	player = p1;	//默认黑棋先手
	for (int i = 0; i < N;i++)//棋盘清零
	{
		for (int j = 0; j < N; j++)
		{
			chess[i][j] = Nochess;
		}
	}
	chess_num = 0;			//总棋子数清零
}

int judge(int x, int y)
{
	return chess[x][y] ? 0 : 1;
}

int judge_win(int x, int y)
{
	int i, j, k;
	const int step[4][2] = { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 1, -1 } };
	for (i = 0; i < 4; ++i)
	{
		const int d[2] = { -1, 1 };
		int count = 1;
		for (j = 0; j < 2; ++j)
		for (k = 1; k <= 4; ++k){
			int row = x + k*d[j] * step[i][0];
			int col = y + k*d[j] * step[i][1];
			if (row >= 1 && row <= N &&
				col >= 1 && col <= N &&
				chess[x][y] == chess[row][col])
				count += 1;
			else
				break;
		}
		if (count >= 5)
			return 1;
	}
	if (chess_num == N*N)
		Msg_restart(2);

	return 0;
}

int Chess_piece(int x1, int y1)
{
    if (x1 == -1 || y1 == -1) {
        return 0;
    }
    

    if (judge(x1, y1)) {
        // 绘制棋子（可添加动画效果）
        drawCircle(x1 * Grid_wid, y1 * Grid_wid, Chess_R, player == p1 ? BLACK : BROWN);
        
        chess[x1][y1] = player;
        chess_num++;
        if (judge_win(x1, y1)) {
            Msg_restart(1);
        }
        changeplayer();
        return 1;
    }
    return 0;
}


int mod_xy(int xy)
{
	int res = (int)((double)xy / Grid_wid + 0.5);
	if (res < N && res >= 0)
	{
		return res;
	}
	else
	{
		return -1;
	}
}

void changeplayer()//玩家交换
{
	player = p1 + p2 - player;
	if (player == p1)
		setfillcolor(BLACK);
	else
		setfillcolor(WHITE);
}

void draw_checkboard() // 画棋盘
{
    // 加载背景图片
    IMAGE bgImage;
    loadimage(&bgImage, _T("2.jpg"));
	setbkcolor(WHITE);


    // 绘制背景图片
    putimage(0, 0, &bgImage);

    // 绘制网格线和星位标记
    setlinecolor(BLACK);
    for (int i = 0; i < N; i++) {
        line(1 + i * Grid_wid, 1, 1 + i * Grid_wid, Grid_wid * (N - 1));
        line(1, 1 + i * Grid_wid, Grid_wid * (N - 1), 1 + i * Grid_wid);
    }
    setfillcolor(BLACK);
	// 中心
	int centerX = (N / 2) * Grid_wid;
	int centerY = (N / 2) * Grid_wid;
	setfillcolor(BLACK);
	solidcircle(centerX, centerY, 5);
	
	// 左上角
	int topLeftX = 3 * Grid_wid;
	int topLeftY = 3 * Grid_wid;
	setfillcolor(BLACK);
	solidcircle(topLeftX, topLeftY, 5);
	
	// 左下角
	int bottomLeftX = 3 * Grid_wid;
	int bottomLeftY = (N - 4) * Grid_wid;  // 下角位置
	setfillcolor(BLACK);
	solidcircle(bottomLeftX, bottomLeftY, 5);
	
	// 右上角
	int topRightX = (N - 4) * Grid_wid;  // 右角位置
	int topRightY = 3 * Grid_wid;
	setfillcolor(BLACK);
	solidcircle(topRightX, topRightY, 5);
	
	// 右下角
	int bottomRightX = (N - 4) * Grid_wid;  // 右下角位置
	int bottomRightY = (N - 4) * Grid_wid;
	setfillcolor(BLACK);
	solidcircle(bottomRightX, bottomRightY, 5);
    
	
	if (param != computer_computer) {
    // 绘制返回按钮
    setcolor(WHITE);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("黑体"));
    outtextxy(width + 40, heigth - 60, _T("返回"));
	
}
	
	
	 // 绘制计分板
    settextstyle(20, 0, _T("黑体"));
    settextcolor(BLACK);
    outtextxy(width + 20, 20, _T("计分板"));
    outtextxy(width + 20, 100, _T("黑棋分数:")); // 初始分数为0
    outtextxy(width + 20, 120, _T("白棋分数:")); // 初始分数为0
    
     // 更新计分板上的分数显示
    TCHAR black_score_str[10];
    TCHAR white_score_str[10];
    snprintf(black_score_str, sizeof(black_score_str), "%d", black_score);
    snprintf(white_score_str, sizeof(white_score_str), "%d", white_score);

    settextstyle(20, 0, _T("黑体"));
    settextcolor(BLACK);
    outtextxy(width + 20, 100, _T("黑棋分数: "));
    outtextxy(width + 150, 100, black_score_str);
    outtextxy(width + 20, 120, _T("白棋分数: "));
    outtextxy(width + 150, 120, white_score_str);

    
}


int scorejudge(int row,int col)
{
	if ((row >= 0 && row < N) && (col >= 0 && col < N))
	{
		return 1;
	} 
	else
	{
		return 0;
	}
}


int chessscore(int x, int y, int worb)   //棋盘权值函数
{
	int sumscore = 0;
    char u, d, l, r, lu, ld, ru, rd; // u上 d下 l左 r右 lu左上 ld左下 ru右上 rd右下
    int row, col, count1, count2, count3, count4; // 1横 2竖 3斜上 4斜下
    count1 = count2 = count3 = count4 = 1;
    l = r = u = d = lu = ld = ru = rd = 0;
    chess[x][y] = worb; // 模拟下棋

	// 检查自己是否有获胜的机会
    if (count1 >= 4 || count2 >= 4 || count3 >= 4 || count4 >= 4) {
        // 如果有四子相连，返回一个很高的分数
        return MAX_SCORE;
    }
    
	//横向
	row = x, col = y + 1;
	
	while (chess[row][col] == worb && scorejudge(row,col))
	{
		count1++;
		col++;
	}
	
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		r++;
		col++;
	}
	
	row = x, col = y - 1;
	
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count1++;
		col--;
	}
	
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		l++;
		col--;
	}


	//竖向
	row = x + 1, col = y;
	
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count2++;
		row++;
	}
	
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		d++;
		row++;
	}
	
	row = x - 1, col = y;
	
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count2++;
		row--;
	}
	
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		u++;
		row--;
	}

	//斜上
	row = x - 1, col = y + 1;
	
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count3++;
		col++;
		row--;
	}
	
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		ru++;
		col++;
		row--;
	}
	
	row = x + 1, col = y - 1;
	
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count3++;
		col--;
		row++;
	}
	
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		ld++;
		col--;
		row++;
	}
	

	//斜下
	row = x + 1, col = y + 1;
	
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count4++;
		col++;
		row++;
	}
	
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		rd++;
		col++;
		row++;
	}
	
	row = x - 1, col = y - 1;
	
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count4++;
		col--;
		row--;
	}
	
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		lu++;
		col--;
		row--;
	}

	chess[x][y] = Nochess;

	if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5)//成五
	{
		return sumscore = 5000000;
	}


	if ((count1 == 4 && count2 == 4 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
		(count1 == 4 && count3 == 4 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
		(count1 == 4 && count4 == 4 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
		(count2 == 4 && count3 == 4 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
		(count2 == 4 && count4 == 4 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
		(count3 == 4 && count4 == 4 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
		//双活四
	{
		return sumscore = 4000000;
	}


	if ((count1 == 4 && l >= 1 && r >= 1) || (count2 == 4 && u >= 1 && d >= 1) ||
		(count3 == 4 && ru >= 1 && ld >= 1) || (count4 == 4 && lu >= 1 && rd >= 1))
		//活四
	{
		return sumscore = 800000;
	}

	if ((count1 == 4 && ((l == 0 && r >= 1) || (l >= 1 && r == 0))) 
		|| (count2 == 4 && ((u == 0 && d >= 1) || (u >= 1 && d == 0))) 
		||(count3 == 4 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0))) 
		|| (count4 == 4 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
	{
		sumscore = sumscore + 70000; //成四
	}

	if ((count1 == 3 && count2 == 3 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
		(count1 == 3 && count3 == 3 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
		(count1 == 3 && count4 == 3 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
		(count2 == 3 && count3 == 3 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
		(count2 == 3 && count4 == 3 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
		(count3 == 3 && count4 == 3 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1)) 
		//双活三
	{
		return sumscore + 400000;
	}


	if ((count1 == 3 && l >= 1 && r >= 1) || (count2 == 3 && u >= 1 && d >= 1) ||
		(count3 == 3 && ru >= 1 && ld >= 1) || (count4 == 3 && lu >= 1 && rd >= 1))
		//活三
	{
		sumscore = sumscore + 60000;
		return sumscore;
	} 


	if ((count1 == 2 && count2 == 2 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
		(count1 == 2 && count3 == 2 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
		(count1 == 2 && count4 == 2 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
		(count2 == 2 && count3 == 2 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
		(count2 == 2 && count4 == 2 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
		(count3 == 2 && count4 == 2 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
		//双活二
	{
		sumscore = sumscore + 20000;
	}

	if ((count1 == 2 && l >= 1 && r >= 1) || (count2 == 2 && u >= 1 && d >= 1) ||
		(count3 == 2 && ru >= 1 && ld >= 1) || (count4 == 2 && lu >= 1 && rd >= 1))
		//单活二
	{
		sumscore = sumscore + 10000;
	}
	
	if ((count1 == 3 && ((l == 0 && r >= 1) || (l >= 1 && r == 0)))
		|| (count2 == 3 && ((u == 0 && d >= 1) || (u >= 1 && d == 0)))
		|| (count3 == 3 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0)))
		|| (count4 == 3 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
	{
		sumscore = sumscore + 5000; //成三
	}
	
	// 单子（即没有相邻棋子的位置）
    if ((count1 == 1 && l == 0 && r == 0) ||
        (count2 == 1 && u == 0 && d == 0) ||
        (count3 == 1 && lu == 0 && rd == 0) ||
        (count4 == 1 && ru == 0 && ld == 0))
    {
        sumscore += 50;
    }

	// 跳活三
    if ((count1 == 3 && l == 1 && r == 1 && u == 1 && d == 1) ||
        (count2 == 3 && l == 1 && r == 1 && u == 1 && d == 1) ||
        (count3 == 3 && lu == 1 && rd == 1 && ru == 1 && ld == 1) ||
        (count4 == 3 && lu == 1 && rd == 1 && ru == 1 && ld == 1)) {
        sumscore += 1500; // 跳活三的分数
    }

    // 双三
    if ((count1 == 3 && l == 1 && r == 1 && u == 1 && d == 1) && 
        (count2 == 3 && l == 1 && r == 1 && u == 1 && d == 1) ||
        (count1 == 3 && l == 1 && r == 1 && u == 1 && d == 1) && 
        (count3 == 3 && lu == 1 && rd == 1 && ru == 1 && ld == 1) ||
        (count1 == 3 && l == 1 && r == 1 && u == 1 && d == 1) && 
        (count4 == 3 && lu == 1 && rd == 1 && ru == 1 && ld == 1) ||
        (count2 == 3 && l == 1 && r == 1 && u == 1 && d == 1) && 
        (count3 == 3 && lu == 1 && rd == 1 && ru == 1 && ld == 1) ||
        (count2 == 3 && l == 1 && r == 1 && u == 1 && d == 1) && 
        (count4 == 3 && lu == 1 && rd == 1 && ru == 1 && ld == 1)) {
        sumscore += 3000; // 双三的分数
    }
    
    // 四三
    if ((count1 == 3 && (l == 0 || r == 0) && (u == 1 || d == 1)) ||
        (count2 == 3 && (u == 0 || d == 0) && (l == 1 || r == 1)) ||
        (count3 == 3 && (lu == 0 || rd == 0) && (ru == 1 || ld == 1)) ||
        (count4 == 3 && (ru == 0 || ld == 0) && (lu == 1 || rd == 1))) {
        sumscore += 2000; // 四三的分数
    }
    
    // 活二
    if ((count1 == 2 && l == 0 && r == 0) ||
        (count2 == 2 && u == 0 && d == 0) ||
        (count3 == 2 && lu == 0 && rd == 0) ||
        (count4 == 2 && ru == 0 && ld == 0))
    {
        sumscore += 300;
    }

    // 防守对方的棋型，如果对方有四、活三等棋型，则减分
    if ((count1 == 4 && (l == 0 || r == 0)) ||
        (count2 == 4 && (u == 0 || d == 0)) ||
        (count3 == 4 && (lu == 0 || rd == 0)) ||
        (count4 == 4 && (ru == 0 || ld == 0)))
    {
        sumscore -= 5000;
    }
    
    // 冲四：在一个方向上有四颗己方棋子，两端至少有一个空位。
	if (count1 == 4) {
	    if ((l == 0 && r == 1) || (l == 1 && r == 0)) {
	        sumscore += 5000; // 冲四
	    }
	}
	
	if (count2 == 4) {
	    if ((u == 0 && d == 1) || (u == 1 && d == 0)) {
	        sumscore += 5000; // 冲四
	    }
	}
	
	if (count3 == 4) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 5000; // 冲四
	    }
	}
	
	if (count4 == 4) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 5000; // 冲四
	    }
	}
	
	// 眠三：在一个方向上有三颗己方棋子，两端至少有一个空位。
	if (count1 == 3) {
	    if ((l == 0 && r == 1) || (l == 1 && r == 0)) {
	        sumscore += 1000; // 眠三
	    }
	}
	
	if (count2 == 3) {
	    if ((u == 0 && d == 1) || (u == 1 && d == 0)) {
	        sumscore += 1000; // 眠三
	    }
	}
	
	if (count3 == 3) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 1000; // 眠三
	    }
	}
	
	if (count4 == 3) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 1000; // 眠三
	    }
	}
	
	// 活二：在一个方向上有两颗己方棋子，两端至少有一个空位。
	if (count1 == 2) {
	    if ((l == 0 && r == 1) || (l == 1 && r == 0)) {
	        sumscore += 300; // 活二
	    }
	}
	
	if (count2 == 2) {
	    if ((u == 0 && d == 1) || (u == 1 && d == 0)) {
	        sumscore += 300; // 活二
	    }
	}
	
	if (count3 == 2) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 300; // 活二
	    }
	}
	
	if (count4 == 2) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 300; // 活二
	    }
	}
	
	// 眠二：在一个方向上有两颗己方棋子，两端都没有空位。
	if (count1 == 2 && l == 1 && r == 1) {
	    sumscore += 50; // 眠二
	}
	
	if (count2 == 2 && u == 1 && d == 1) {
	    sumscore += 50; // 眠二
	}
	
	if (count3 == 2 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1))) {
	    sumscore += 50; // 眠二
	}
	
	if (count4 == 2 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1))) {
	    sumscore += 50; // 眠二
	}

    // 检查眠二、死四、半活三、跳活三、冲三等棋型
    if (count1 == 2 && l >= 1 && r >= 1 && (l + r) < 4 && (l + r) > 1) {
        sumscore += 1000; // 眠二
    }
    
    if (count1 == 4 && (l == 0 || r == 0)) {
        sumscore -= 2000; // 死四
    }

    if (count1 == 3 && l >= 1 && r == 0) {
        sumscore += 800; // 半活三
    }

    if (count1 == 3 && l == 1 && r == 1) {
        sumscore += 2000; // 跳活三
    }

    if (count1 == 3 && (l + r) == 1) {
        sumscore += 400; // 冲三
    }
	
	 // 添加对双活三、双三和冲四的评估
    int doubleActiveThree = 0;
    int doubleThree = 0;
    int specialFour = 0;

    // 判断横向、竖向、斜上和斜下是否有双活三、双三或冲四
    if (count1 == 3) {
        if ((l == 1 && r == 1) || (u == 1 && d == 1)) {
            doubleActiveThree++;
        }
        if ((l == 1 && r == 1) || (u == 1 && d == 1 && lu == 1 && rd == 1)) {
            doubleThree++;
        }
        if ((l == 0 && r == 1) || (u == 0 && d == 1)) {
            specialFour++;
        }
    }

    if (count2 == 3) {
        if ((l == 1 && r == 1) || (u == 1 && d == 1)) {
            doubleActiveThree++;
        }
        if ((l == 1 && r == 1) || (u == 1 && d == 1 && lu == 1 && rd == 1)) {
            doubleThree++;
        }
        if ((l == 0 && r == 1) || (u == 0 && d == 1)) {
            specialFour++;
        }
    }

    if (count3 == 3) {
        if ((lu == 1 && rd == 1) || (ru == 1 && ld == 1)) {
            doubleActiveThree++;
        }
        if ((lu == 1 && rd == 1) || (ru == 1 && ld == 1 && l == 1 && r == 1 && u == 1 && d == 1)) {
            doubleThree++;
        }
        if ((lu == 1 && rd == 1) || (ru == 1 && ld == 1 && lu == 0 && rd == 0)) {
            specialFour++;
        }
    }

    if (count4 == 3) {
        if ((lu == 1 && rd == 1) || (ru == 1 && ld == 1)) {
            doubleActiveThree++;
        }
        if ((lu == 1 && rd == 1) || (ru == 1 && ld == 1 && l == 1 && r == 1 && u == 1 && d == 1)) {
            doubleThree++;
        }
        if ((lu == 1 && rd == 1) || (ru == 1 && ld == 1 && lu == 0 && rd == 0)) {
            specialFour++;
        }
    }

    // 根据评估的棋型来调整分数
    if (doubleActiveThree >= 2) {
        // 两个双活三
        sumscore += 1000000;
    } else if (doubleThree >= 2) {
        // 两个双三
        sumscore += 500000;
    } else if (specialFour >= 1) {
        // 一个冲四和一个活三
        sumscore += 300000;
    }
	
	// 死三和半活三评估
	if ((count1 == 3 && l == 1 && r == 1) || (count2 == 3 && u == 1 && d == 1) ||
	    (count3 == 3 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1))) ||
	    (count4 == 3 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1)))) {
	    // 死三的情况
	    sumscore += 200; // 死三的分数
	
	    // 半活三的情况，如果两端有空位
	    if ((count1 == 3 && (l == 1 || r == 1)) ||
	        (count2 == 3 && (u == 1 || d == 1)) ||
	        (count3 == 3 && ((lu == 1 && rd == 1 && (l == 1 || r == 1)) || (ru == 1 && ld == 1 && (l == 1 || r == 1)))) ||
	        (count4 == 3 && ((lu == 1 && rd == 1 && (l == 1 || r == 1)) || (ru == 1 && ld == 1 && (l == 1 || r == 1))))) {
	        sumscore += 100; // 半活三的分数
	    }
	}
	
	// 冲三评估
	if ((count1 == 3 && (l == 0 || r == 0)) ||
	    (count2 == 3 && (u == 0 || d == 0)) ||
	    (count3 == 3 && ((lu == 0 || rd == 0) || (ru == 0 || ld == 0))) ||
	    (count4 == 3 && ((lu == 0 || rd == 0) || (ru == 0 || ld == 0)))) {
	    sumscore += 300; // 冲三的分数
	}
	
	// 双四评估
	if ((count1 == 4 && l == 1 && r == 1) || (count2 == 4 && u == 1 && d == 1) ||
	    (count3 == 4 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1))) ||
	    (count4 == 4 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1)))) {
	    sumscore += 100000; // 双四的分数
	}
	
	// 长连检测
	if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5) {
	    sumscore = 5000000; // 长连直接获胜
	}

	// 活一：在一个方向上有一颗己方棋子，两端至少有一个空位。
	if ((count1 == 1 && ((l == 0 && r >= 1) || (l >= 1 && r == 0))) ||
	    (count2 == 1 && ((u == 0 && d >= 1) || (u >= 1 && d == 0))) ||
	    (count3 == 1 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0))) ||
	    (count4 == 1 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
	{
	    sumscore += 50; // 活一
	}
	
	// 冲二：在一个方向上有两颗己方棋子，但两端至少有一个空位，并且对方的棋子没有堵住。
	if ((count1 == 2 && l == 0 && r == 1 && scorejudge(x, y - 2) && scorejudge(x, y + 2)) ||
	    (count2 == 2 && u == 0 && d == 1 && scorejudge(x - 2, y) && scorejudge(x + 2, y)) ||
	    (count3 == 2 && lu == 0 && rd == 1 && scorejudge(x - 2, y - 2) && scorejudge(x + 2, y + 2)) ||
	    (count4 == 2 && ld == 0 && ru == 1 && scorejudge(x - 2, y + 2) && scorejudge(x + 2, y - 2)) ||
	    (count1 == 2 && r == 0 && l == 1 && scorejudge(x, y - 2) && scorejudge(x, y + 2)) ||
	    (count2 == 2 && d == 0 && u == 1 && scorejudge(x - 2, y) && scorejudge(x + 2, y)) ||
	    (count3 == 2 && rd == 0 && lu == 1 && scorejudge(x - 2, y - 2) && scorejudge(x + 2, y + 2)) ||
	    (count4 == 2 && ru == 0 && ld == 1 && scorejudge(x - 2, y + 2) && scorejudge(x + 2, y - 2)))
	{
	    sumscore += 100; // 冲二
	}
	
	// 眠一：在一个方向上有一颗己方棋子，但两端都被对方阻挡。
	if ((count1 == 1 && ((l >= 1 && r >= 1) || (l == 1 && r == 1))) ||
	    (count2 == 1 && ((u >= 1 && d >= 1) || (u == 1 && d == 1))) ||
	    (count3 == 1 && ((ld >= 1 && ru >= 1) || (ld == 1 && ru == 1))) ||
	    (count4 == 1 && ((lu >= 1 && rd >= 1) || (lu == 1 && rd == 1))))
	{
	    sumscore += 10; // 眠一
	}
	
	// 死二：在一个方向上有两颗己方棋子，但两端都被对方阻挡。
	if ((count1 == 2 && ((l >= 1 && r >= 1) || (l == 1 && r == 1))) ||
	    (count2 == 2 && ((u >= 1 && d >= 1) || (u == 1 && d == 1))) ||
	    (count3 == 2 && ((ld >= 1 && ru >= 1) || (ld == 1 && ru == 1))) ||
	    (count4 == 2 && ((lu >= 1 && rd >= 1) || (lu == 1 && rd == 1))))
	{
	    sumscore += 20; // 死二
	}


    chess[x][y] = Nochess;

	
	return sumscore;

}

void Msg_restart(int par)
{
	 // 游戏结束后更新分数
    if (par == 1) {
        if (player == p1) {
            black_score++; // 黑棋胜利，黑棋分数加1
        } else {
            white_score++; // 白棋胜利，白棋分数加1
        }
    }
	
    int res;
    if (par == 1) {
        if (player == p1) {
            res = MessageBoxA(0, "黑棋胜,是否重开？", "五子棋", MB_YESNO | MB_SYSTEMMODAL);
        } else {
            res = MessageBoxA(0, "白棋胜,是否重开？", "五子棋", MB_YESNO | MB_SYSTEMMODAL);
        }
    } else {
        res = MessageBoxA(0, "平局,是否重开？", "五子棋", MB_YESNO | MB_SYSTEMMODAL);
    }

    if (res == IDYES)
        restart();
    else
    {
    	
    	 Start_Game();
	}
       
        
}

void chesscomputer()
{
	int i, j, cscore, cscorel, pscore, pscorel, row1, col1, row2, col2;
	cscore = pscore = 0; row1 = row2 = col1 = col2 = -1;
	
if (chess_num <= 1)
{
    srand((unsigned)time(NULL));

    // 找到离黑棋最近的位置
    int minDistance = N * N; // 初始化为最大可能距离
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (chess[i][j] == p1) // 如果是黑棋
            {
                // 计算距离
                int distance = abs(i - 6) + abs(j - 6); // 假设棋盘大小是N*N
                if (distance < minDistance)
                {
                    minDistance = distance;
                    row1 = i;
                    col1 = j;
                }
            }
        }
    }

    // 在离黑棋最近的位置附近随机选择一个位置
    int offset = rand() % 3 - 1; // 随机选择 -1、0、1 中的一个偏移
    row1 += offset;
    col1 += offset;

    // 确保选择的位置是合法的
    if (row1 < 0) row1 = 0;
    if (row1 >= N) row1 = N - 1;
    if (col1 < 0) col1 = 0;
    if (col1 >= N) col1 = N - 1;

    while (!judge(row1, col1))
    {
        // 如果选择的位置不合法，继续随机选择
        offset = rand() % 3 - 1;
        row1 += offset;
        col1 += offset;
        if (row1 < 0) row1 = 0;
        if (row1 >= N) row1 = N - 1;
        if (col1 < 0) col1 = 0;
        if (col1 >= N) col1 = N - 1;
    }

    Chess_piece(row1, col1);
}

	else
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (judge(i, j))
				{
					cscorel = chessscore(i, j, p1);
					if (cscorel > cscore)
					{
						cscore = cscorel;
						row1 = i;
						col1 = j;
					}
					pscorel = chessscore(i, j, p2);
					if (pscorel > pscore)
					{
						pscore = pscorel;
						row2 = i;
						col2 = j;
					}
				}
			}
		}
		if (row1 == -1 && col1 == -1 && row2 == -1 && col2 == -1)//没找到最优解 平局
		{
			Msg_restart(2);
		}
		else
		{
			if (chess_num == 3)
			{
				Chess_piece(row2, col2);
			}
			else
			{
				if (cscore > pscore)
				{
					Chess_piece(row1, col1);							
				}
				else
				{
					Chess_piece(row2, col2);
				}
			}
		}
	}
}

void Mouse() // 鼠标移动
{

    if (param == player_player)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            switch (msg.uMsg)
            {
            case WM_LBUTTONDOWN://左键按下
                int x1 = mod_xy(msg.x);
                int y1 = mod_xy(msg.y);
                int x = msg.x;
                int y = msg.y;

                if (x >= width + 20 && x <= width + 100 && y >= heigth - 80 && y <= heigth - 30) {
                    // 玩家点击了返回按钮
                    Start_Game();
                }

                Chess_piece(x1, y1);

                break;
            }
        }
    }
    else
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            switch (msg.uMsg)
            {
            case WM_LBUTTONDOWN://左键按下
                int x1 = mod_xy(msg.x);
                int y1 = mod_xy(msg.y);
                int x = msg.x;
                int y = msg.y;

                if (x >= width + 20 && x <= width + 100 && y >= heigth - 80 && y <= heigth - 30) {
                    // 玩家点击了返回按钮
                    Start_Game();
                }

                if (Chess_piece(x1, y1))
                {
                    chesscomputer();
                }
                break;
            }
        }
    }
}



void Start_Game() {
	// 定义一个 IMAGE 类型的变量，用于存储背景图片
	IMAGE img;
	
	// 加载背景图片
	loadimage(&img, _T("3.jpg"));

		 // 定义按钮状态
    bool playerAIClicked = false;
    bool playerPlayerClicked = false;
    bool computerComputerClicked = false;
    bool helpClicked = false;

        // 清零分数
	    black_score = 0;
	    white_score = 0;
	    
    initgraph(width*1.3, heigth); // 初始化窗口
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    setbkcolor(WHITE); // 设置背景色为白色
    cleardevice();
    
    // 加载背景图片
    IMAGE bgImage;
    loadimage(&bgImage, _T("2.jpg"));

    // 绘制背景图片
    putimage(0, 0, &bgImage);
   
    // 在屏幕上创建美化的初始界面，包括按钮
    settextstyle(30, 0, _T("黑体"));
    settextcolor(BLACK); // 将文本颜色设置为黑色
    outtextxy(200, 200, _T("请选择游戏模式："));

    // 绘制AI对战按钮
    
    settextstyle(20, 0, _T("黑体"));
    outtextxy(260, 265, _T("人机对战"));

    // 绘制双人对战按钮
    
    outtextxy(260, 335, _T("双人对战"));
    
    // 绘制机机对战按钮
	
	outtextxy(260, 405, _T("机机对战"));


    // 绘制帮助按钮（放在右上角并缩小）
	
	settextstyle(16, 0, _T("宋体"));
	outtextxy(560, 55, _T("必读")); // 调整文本的位置
    
	// 绘制音乐按钮
	 // 调整按钮的坐标和大小
	settextstyle(16, 0, _T("宋体"));
	if (isMuted) {
	    setcolor(RED); // 设置红色
	}
	outtextxy(560, 105, _T("音乐")); // 调整文本的位置


    
    // 播放音乐
    if (mciSendString("open \"2.mp3\" alias music", NULL, 0, NULL) == 0) {
        // 打开音频文件成功

        // 播放音频文件
        if (mciSendString("play music repeat", NULL, 0, NULL) != 0) {
            // 处理错误，无法播放音频文件
        }
    } else {
        // 处理错误，无法打开音频文件
    }

    int choice = 0; // 用于记录玩家的选择，0表示未选择
	int computer_mode = 0; // 用于记录机机对战的选择
	
 while (choice == 0) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                int x = msg.x;
                int y = msg.y;
				
				     if (x >= 550 && x <= 600 && y >= 100 && y <= 130) {
					    // 点击了音乐按钮
					    if (isMuted) {
					        // 恢复音乐播放
					        settextcolor(BLACK);
					        isMuted = false;
					        mciSendString("play music repeat", NULL, 0, NULL);
					    } else {
					        // 静音音乐
					        isMuted = true;
					        mciSendString("stop music", NULL, 0, NULL);
					    }
					    
					    // 绘制音乐按钮
					    rectangle(550, 100, 600, 130); // 调整按钮的坐标和大小
					    settextstyle(16, 0, _T("宋体"));
					  	  
								if (isMuted) {
					    // 重新绘制背景
					    putimage(550, 100, &img);
					
					    settextcolor(RED); // 设置红色
					    setbkmode(TRANSPARENT); // 设置背景混合模式为透明
					    outtextxy(560, 105, _T("静音")); // 调整文本的位置并显示"静音"
					} else {
					    // 重新绘制背景
					    putimage(550, 100, &img);
					
					    settextcolor(BLACK); // 设置文本颜色为白色或其他颜色
					    setbkmode(TRANSPARENT); // 设置背景混合模式为透明
					    outtextxy(560, 105, _T("音乐")); // 调整文本的位置并显示"音乐"
					}



					}


                // 检查是否点击了不同按钮，设置相应的按钮状态
                if (x >= 200 && x <= 400 && y >= 250 && y <= 300) {
                    playerAIClicked = true;
                    playerPlayerClicked = false;
                    computerComputerClicked = false;
                    helpClicked = false;
                } else if (x >= 200 && x <= 400 && y >= 320 && y <= 370) {
                    playerAIClicked = false;
                    playerPlayerClicked = true;
                    computerComputerClicked = false;
                    helpClicked = false;
                } else if (x >= 200 && x <= 400 && y >= 390 && y <= 440) {
                    playerAIClicked = false;
                    playerPlayerClicked = false;
                    computerComputerClicked = true;
                    helpClicked = false;
                } else if (x >= 550 && x <= 600 && y >= 50 && y <= 80) {
                    helpClicked = true;
                }
            } else if (msg.uMsg == WM_LBUTTONUP) {
                int x = msg.x;
                int y = msg.y;

                // 在鼠标松开时跳转到相应的页面
                if (x >= 200 && x <= 400 && y >= 250 && y <= 300 && playerAIClicked) {
                    choice = player_AI; // 玩家选择人机对战
                } else if (x >= 200 && x <= 400 && y >= 320 && y <= 370 && playerPlayerClicked) {
                    choice = player_player; // 玩家选择双人对战
                } else if (x >= 200 && x <= 400 && y >= 390 && y <= 440 && computerComputerClicked) {
                      computer_mode = computer_computer; // 玩家选择机机对战
                    choice = computer_computer; // 设置choice为computer_computer以退出选择循环
                } else if (x >= 550 && x <= 600 && y >= 50 && y <= 80 && helpClicked) {
                    // 点击了帮助按钮，处理显示游戏规则的逻辑
                    show_game_rules();
                }

                // 恢复按钮状态
                playerAIClicked = false;
                playerPlayerClicked = false;
                computerComputerClicked = false;
                helpClicked = false;
            
			

            }
            
        }

        // 清除画面
        //cleardevice();

        // 绘制按钮
        if (playerAIClicked) {
            setcolor(RED); // 红框颜色
            settextstyle(20, 0, _T("黑体"));
            outtextxy(260, 265, _T("人机对战"));
        } else {
            setcolor(WHITE); // 白框颜色
        }
        

        if (playerPlayerClicked) {
            setcolor(RED); // 红框颜色
            settextstyle(20, 0, _T("黑体"));
            outtextxy(260, 335, _T("双人对战"));
        } else {
            setcolor(WHITE); // 白框颜色
        }
        

        if (computerComputerClicked) {
            setcolor(RED); // 红框颜色
            settextstyle(20, 0, _T("黑体"));
            outtextxy(260, 405, _T("机机对战"));
        } else {
            setcolor(WHITE); // 白框颜色
        }
        

        if (helpClicked) {
            setcolor(RED); // 红框颜色
            settextstyle(16, 0, _T("宋体"));
			outtextxy(560, 55, _T("必读")); // 调整文本的位置
        } else {
            setcolor(WHITE); // 白框颜色
        }
        
		
		
    }


	param = choice; // 设置游戏模式
	
	
	 if (computer_mode == computer_computer) {
	    param = computer_mode; // 设置游戏模式为机机对战
	    cleardevice(); // 清除初始界面
	    draw_checkboard(); // 绘制游戏棋盘
	    Oninit(); // 初始化游戏数据
	    // 如果选择了机机对战，进入机机对战函数
	    computer_computer_game();
	} else {


  if (param == player_AI) {
        // 如果玩家选择人机对战
        int result = MessageBox(NULL, "是否选择后手", "选择游戏模式", MB_YESNO);
        if (result == IDYES) {
            playerIsFirst = true; // 玩家选择后手
            // 否则，进入人机或双人对战
        param = choice; // 设置游戏模式
        cleardevice(); // 清除初始界面
        draw_checkboard(); // 绘制游戏棋盘
        Oninit(); // 初始化游戏数据
		chesscomputer2(); // 让电脑先下棋
  
            
        } else {
            playerIsFirst = false; // 玩家选择先手
        

        // 否则，进入人机或双人对战
        param = choice; // 设置游戏模式
        cleardevice(); // 清除初始界面
        draw_checkboard(); // 绘制游戏棋盘
        Oninit(); // 初始化游戏数据

        // 进入游戏循环
        while (1) {
            Mouse();
        }
    }
    }else{
	
       // 否则，进入人机或双人对战
        param = choice; // 设置游戏模式
        cleardevice(); // 清除初始界面
        draw_checkboard(); // 绘制游戏棋盘
        Oninit(); // 初始化游戏数据

        // 进入游戏循环
        while (1) {
            Mouse();
        }

}
}
}

void show_game_rules() {
	settextstyle(100, 0, _T("宋体"));

    const char* gameRulesText = 
    						"游戏规则：自己上网搜\n\n"
                            
                            
                            "机机对战：\n"
                            "这个模式是用来测试算法的，没事不用点\n\n"
                            
                            
                            "人机大战（重点1）：\n"
							"*****************************************************\n"
                            "点击人机大战按钮后会弹出一个弹框让你选择先手还是后手，这个弹窗有可能会隐藏在主界面后面，手动移开主界面即可看到弹窗\n" 
							"*****************************************************\n\n"
                            
                            "游戏中右下角返回键（重点2）：\n"
                            "*****************************************************\n"
                            "游戏中点击右下角返回键后会回到主界面，有时候主界面会刷新到屏幕最底下，并不是闪退，只需要从下面拉上去即可\n"
                            "*****************************************************\n\n"
                            
                            
                            "作者hj友情提供： 悔棋我是故意没加的，因为落棋无悔，绝对不是因为作者偷懒！！！\n"
							"最后，享受游戏的乐趣，祝你好运！如果有任何建议或修改方案，请自行更改源码(=.=)";


    // 使用MessageBox创建一个消息框来显示游戏规则
    MessageBox(NULL, gameRulesText, "游戏规则", MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND);
}


void restart()
{
    Oninit();
    cleardevice(); // 清除绘图窗口
    draw_checkboard(); // 绘制游戏棋盘

    // 重置棋盘状态
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            chess[i][j] = Nochess;
        }
    }

    // 重置总棋子数
    chess_num = 0;

    // 重置当前玩家为黑棋
    currentPlayer = p1; // 这里确保将玩家设置为 p1，即黑棋


	    if (param == player_AI && playerIsFirst)
    {
        // 如果是人机模式且玩家选择后手，让电脑先下一步
        chesscomputer2();
    }
	
    if (param != computer_computer)
    {
        // 玩家对玩家模式，等待玩家的动作
        while (1)
        {
            Mouse();
        }
    }
    else if (param == computer_computer)
    {
        // 机机对战模式，循环调用 computer_computer_game
        while (1)
        {
            computer_computer_game();
        }
    }


}



void exitgame()
{
	closegraph();
	exit(0);
}

int main()
{
	Start_Game();
	while (1)
	{
		Mouse();
	}
	return 0;
}

