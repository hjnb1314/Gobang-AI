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


#define p1 1		//���1
#define p2 2		//���2
#define Nochess 0	//����


#define N  24		//���̸���
#define Grid_wid 	(width/(N-1)) //������
#define Chess_R  Grid_wid/2  //���Ӱ뾶


#define player_player	3		//����
#define player_AI		4		//�˻�
#define computer_computer 5  // ������ս


// ����ȫ�ֱ����ͳ�����ͨ���ں���֮�⣩
const int board_size = 15; // ���̴�С
int chess_board[board_size][board_size]; // ��������
const int empty = 0; // �հ�λ��


const int player1 = 1; // ���1
int current_player = player1; // ��ǰ���
int player = p1;	//Ĭ�Ϻ�������


int chess[N][N];	//���̵�ͼ
int chess_num;			//��������


int black_score = 0; // ��ʼ���������Ϊ0
int white_score = 0; // ��ʼ���������Ϊ0
char param = 0;


int currentPlayer = p1; // ��ǰ��ң�Ĭ�Ϻ�������
bool isMuted = false;
bool playerIsFirst = true; // Ĭ������£����ѡ������

// ����ȫ�ֱ������洢���һ�������λ��
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
    // ��鵱ǰ�Ƿ��ǵ�������
    if (currentPlayer == p2)
    {
        if (chess_num <= 0) // ����Ϊ��ʱ
        {
            // �������������м�
            row1 = N / 2;
            col1 = N / 2;

            Chess_piece(row1, col1);
        }
        else
        {
            // ����������߼�������chesscomputer()������
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
            if (row1 == -1 && col1 == -1 && row2 == -1 && col2 == -1)//û�ҵ����Ž� ƽ��
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
        
        // �������Ϊ��ǰ���
        currentPlayer = p1;
    }
    // �������
    else
    {
        // ���������߼�
        // ����chesscomputer()������ֻ�ǽ���ҵ�������ɫ��Ϊ���壨p1��
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
        if (row1 == -1 && col1 == -1 && row2 == -1 && col2 == -1)//û�ҵ����Ž� ƽ��
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

        // ���õ���Ϊ��ǰ���
        currentPlayer = p2;
    }
}



//���Ӷ���Ч�� 
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


// �ں��ʵĵط��������һ�������λ��
void updateLastMove(int x, int y) {
    lastMoveX = x;
    lastMoveY = y;
}

// ��ȡ���һ�������λ�õĺ���
int getLastMoveX() {
    return lastMoveX;
}
int getLastMoveY() {
    return lastMoveY;
}

void computer_computer_game() {

    int x1, y1, x2, y2; // ���� x1, y1, x2 �� y2 ���������ڴ洢����λ��

    while (1) {

        x1 = y1 = x2 = y2 = -1; // ��ʼ������

        chesscomputer2(); // ����1���壬�����ݲ���
        x1 = getLastMoveX(); // ��ȡ���һ�������λ��
        y1 = getLastMoveY();

        if (judge_win(x1, y1)) {
            // ����ʤ���߼�
            if (currentPlayer == p1) {
                black_score++; // ����ʤ�������������1
            } else {
                white_score++; // ����ʤ�������������1
            }
            Msg_restart(1); // ��ʾ��Ϸ������Ϣ
            break;
        }

        // �л����
        currentPlayer = (currentPlayer == p1) ? p2 : p1;

        // ��ʱһ��ʱ��
        //Sleep(1); // ��ʱ 1000 ���루1 �룩

        chesscomputer2(); // ����2���壬�����ݲ���
        x2 = getLastMoveX(); // ��ȡ���һ�������λ��
        y2 = getLastMoveY();

        if (judge_win(x2, y2)) {
            // ����ʤ���߼�
            if (currentPlayer == p1) {
                black_score++; // ����ʤ�������������1
            } else {
                white_score++; // ����ʤ�������������1
            }
            Msg_restart(1); // ��ʾ��Ϸ������Ϣ
            break;
        }

        // �л����
        currentPlayer = (currentPlayer == p1) ? p2 : p1;

        // ��ʱһ��ʱ��
        //Sleep(1); // ��ʱ 1000 ���루1 �룩
    }
}

void Oninit()
{
	setfillcolor(BLACK);
	player = p1;	//Ĭ�Ϻ�������
	for (int i = 0; i < N;i++)//��������
	{
		for (int j = 0; j < N; j++)
		{
			chess[i][j] = Nochess;
		}
	}
	chess_num = 0;			//������������
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
        // �������ӣ�����Ӷ���Ч����
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

void changeplayer()//��ҽ���
{
	player = p1 + p2 - player;
	if (player == p1)
		setfillcolor(BLACK);
	else
		setfillcolor(WHITE);
}

void draw_checkboard() // ������
{
    // ���ر���ͼƬ
    IMAGE bgImage;
    loadimage(&bgImage, _T("2.jpg"));
	setbkcolor(WHITE);


    // ���Ʊ���ͼƬ
    putimage(0, 0, &bgImage);

    // ���������ߺ���λ���
    setlinecolor(BLACK);
    for (int i = 0; i < N; i++) {
        line(1 + i * Grid_wid, 1, 1 + i * Grid_wid, Grid_wid * (N - 1));
        line(1, 1 + i * Grid_wid, Grid_wid * (N - 1), 1 + i * Grid_wid);
    }
    setfillcolor(BLACK);
	// ����
	int centerX = (N / 2) * Grid_wid;
	int centerY = (N / 2) * Grid_wid;
	setfillcolor(BLACK);
	solidcircle(centerX, centerY, 5);
	
	// ���Ͻ�
	int topLeftX = 3 * Grid_wid;
	int topLeftY = 3 * Grid_wid;
	setfillcolor(BLACK);
	solidcircle(topLeftX, topLeftY, 5);
	
	// ���½�
	int bottomLeftX = 3 * Grid_wid;
	int bottomLeftY = (N - 4) * Grid_wid;  // �½�λ��
	setfillcolor(BLACK);
	solidcircle(bottomLeftX, bottomLeftY, 5);
	
	// ���Ͻ�
	int topRightX = (N - 4) * Grid_wid;  // �ҽ�λ��
	int topRightY = 3 * Grid_wid;
	setfillcolor(BLACK);
	solidcircle(topRightX, topRightY, 5);
	
	// ���½�
	int bottomRightX = (N - 4) * Grid_wid;  // ���½�λ��
	int bottomRightY = (N - 4) * Grid_wid;
	setfillcolor(BLACK);
	solidcircle(bottomRightX, bottomRightY, 5);
    
	
	if (param != computer_computer) {
    // ���Ʒ��ذ�ť
    setcolor(WHITE);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("����"));
    outtextxy(width + 40, heigth - 60, _T("����"));
	
}
	
	
	 // ���ƼƷְ�
    settextstyle(20, 0, _T("����"));
    settextcolor(BLACK);
    outtextxy(width + 20, 20, _T("�Ʒְ�"));
    outtextxy(width + 20, 100, _T("�������:")); // ��ʼ����Ϊ0
    outtextxy(width + 20, 120, _T("�������:")); // ��ʼ����Ϊ0
    
     // ���¼Ʒְ��ϵķ�����ʾ
    TCHAR black_score_str[10];
    TCHAR white_score_str[10];
    snprintf(black_score_str, sizeof(black_score_str), "%d", black_score);
    snprintf(white_score_str, sizeof(white_score_str), "%d", white_score);

    settextstyle(20, 0, _T("����"));
    settextcolor(BLACK);
    outtextxy(width + 20, 100, _T("�������: "));
    outtextxy(width + 150, 100, black_score_str);
    outtextxy(width + 20, 120, _T("�������: "));
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


int chessscore(int x, int y, int worb)   //����Ȩֵ����
{
	int sumscore = 0;
    char u, d, l, r, lu, ld, ru, rd; // u�� d�� l�� r�� lu���� ld���� ru���� rd����
    int row, col, count1, count2, count3, count4; // 1�� 2�� 3б�� 4б��
    count1 = count2 = count3 = count4 = 1;
    l = r = u = d = lu = ld = ru = rd = 0;
    chess[x][y] = worb; // ģ������

	// ����Լ��Ƿ��л�ʤ�Ļ���
    if (count1 >= 4 || count2 >= 4 || count3 >= 4 || count4 >= 4) {
        // �������������������һ���ܸߵķ���
        return MAX_SCORE;
    }
    
	//����
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


	//����
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

	//б��
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
	

	//б��
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

	if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5)//����
	{
		return sumscore = 5000000;
	}


	if ((count1 == 4 && count2 == 4 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
		(count1 == 4 && count3 == 4 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
		(count1 == 4 && count4 == 4 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
		(count2 == 4 && count3 == 4 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
		(count2 == 4 && count4 == 4 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
		(count3 == 4 && count4 == 4 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
		//˫����
	{
		return sumscore = 4000000;
	}


	if ((count1 == 4 && l >= 1 && r >= 1) || (count2 == 4 && u >= 1 && d >= 1) ||
		(count3 == 4 && ru >= 1 && ld >= 1) || (count4 == 4 && lu >= 1 && rd >= 1))
		//����
	{
		return sumscore = 800000;
	}

	if ((count1 == 4 && ((l == 0 && r >= 1) || (l >= 1 && r == 0))) 
		|| (count2 == 4 && ((u == 0 && d >= 1) || (u >= 1 && d == 0))) 
		||(count3 == 4 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0))) 
		|| (count4 == 4 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
	{
		sumscore = sumscore + 70000; //����
	}

	if ((count1 == 3 && count2 == 3 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
		(count1 == 3 && count3 == 3 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
		(count1 == 3 && count4 == 3 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
		(count2 == 3 && count3 == 3 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
		(count2 == 3 && count4 == 3 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
		(count3 == 3 && count4 == 3 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1)) 
		//˫����
	{
		return sumscore + 400000;
	}


	if ((count1 == 3 && l >= 1 && r >= 1) || (count2 == 3 && u >= 1 && d >= 1) ||
		(count3 == 3 && ru >= 1 && ld >= 1) || (count4 == 3 && lu >= 1 && rd >= 1))
		//����
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
		//˫���
	{
		sumscore = sumscore + 20000;
	}

	if ((count1 == 2 && l >= 1 && r >= 1) || (count2 == 2 && u >= 1 && d >= 1) ||
		(count3 == 2 && ru >= 1 && ld >= 1) || (count4 == 2 && lu >= 1 && rd >= 1))
		//�����
	{
		sumscore = sumscore + 10000;
	}
	
	if ((count1 == 3 && ((l == 0 && r >= 1) || (l >= 1 && r == 0)))
		|| (count2 == 3 && ((u == 0 && d >= 1) || (u >= 1 && d == 0)))
		|| (count3 == 3 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0)))
		|| (count4 == 3 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
	{
		sumscore = sumscore + 5000; //����
	}
	
	// ���ӣ���û���������ӵ�λ�ã�
    if ((count1 == 1 && l == 0 && r == 0) ||
        (count2 == 1 && u == 0 && d == 0) ||
        (count3 == 1 && lu == 0 && rd == 0) ||
        (count4 == 1 && ru == 0 && ld == 0))
    {
        sumscore += 50;
    }

	// ������
    if ((count1 == 3 && l == 1 && r == 1 && u == 1 && d == 1) ||
        (count2 == 3 && l == 1 && r == 1 && u == 1 && d == 1) ||
        (count3 == 3 && lu == 1 && rd == 1 && ru == 1 && ld == 1) ||
        (count4 == 3 && lu == 1 && rd == 1 && ru == 1 && ld == 1)) {
        sumscore += 1500; // �������ķ���
    }

    // ˫��
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
        sumscore += 3000; // ˫���ķ���
    }
    
    // ����
    if ((count1 == 3 && (l == 0 || r == 0) && (u == 1 || d == 1)) ||
        (count2 == 3 && (u == 0 || d == 0) && (l == 1 || r == 1)) ||
        (count3 == 3 && (lu == 0 || rd == 0) && (ru == 1 || ld == 1)) ||
        (count4 == 3 && (ru == 0 || ld == 0) && (lu == 1 || rd == 1))) {
        sumscore += 2000; // �����ķ���
    }
    
    // ���
    if ((count1 == 2 && l == 0 && r == 0) ||
        (count2 == 2 && u == 0 && d == 0) ||
        (count3 == 2 && lu == 0 && rd == 0) ||
        (count4 == 2 && ru == 0 && ld == 0))
    {
        sumscore += 300;
    }

    // ���ضԷ������ͣ�����Է����ġ����������ͣ������
    if ((count1 == 4 && (l == 0 || r == 0)) ||
        (count2 == 4 && (u == 0 || d == 0)) ||
        (count3 == 4 && (lu == 0 || rd == 0)) ||
        (count4 == 4 && (ru == 0 || ld == 0)))
    {
        sumscore -= 5000;
    }
    
    // ���ģ���һ�����������Ŀż������ӣ�����������һ����λ��
	if (count1 == 4) {
	    if ((l == 0 && r == 1) || (l == 1 && r == 0)) {
	        sumscore += 5000; // ����
	    }
	}
	
	if (count2 == 4) {
	    if ((u == 0 && d == 1) || (u == 1 && d == 0)) {
	        sumscore += 5000; // ����
	    }
	}
	
	if (count3 == 4) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 5000; // ����
	    }
	}
	
	if (count4 == 4) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 5000; // ����
	    }
	}
	
	// ��������һ�������������ż������ӣ�����������һ����λ��
	if (count1 == 3) {
	    if ((l == 0 && r == 1) || (l == 1 && r == 0)) {
	        sumscore += 1000; // ����
	    }
	}
	
	if (count2 == 3) {
	    if ((u == 0 && d == 1) || (u == 1 && d == 0)) {
	        sumscore += 1000; // ����
	    }
	}
	
	if (count3 == 3) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 1000; // ����
	    }
	}
	
	if (count4 == 3) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 1000; // ����
	    }
	}
	
	// �������һ�������������ż������ӣ�����������һ����λ��
	if (count1 == 2) {
	    if ((l == 0 && r == 1) || (l == 1 && r == 0)) {
	        sumscore += 300; // ���
	    }
	}
	
	if (count2 == 2) {
	    if ((u == 0 && d == 1) || (u == 1 && d == 0)) {
	        sumscore += 300; // ���
	    }
	}
	
	if (count3 == 2) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 300; // ���
	    }
	}
	
	if (count4 == 2) {
	    if (((lu == 0 && rd == 1) || (lu == 1 && rd == 0)) ||
	        ((ru == 0 && ld == 1) || (ru == 1 && ld == 0))) {
	        sumscore += 300; // ���
	    }
	}
	
	// �߶�����һ�������������ż������ӣ����˶�û�п�λ��
	if (count1 == 2 && l == 1 && r == 1) {
	    sumscore += 50; // �߶�
	}
	
	if (count2 == 2 && u == 1 && d == 1) {
	    sumscore += 50; // �߶�
	}
	
	if (count3 == 2 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1))) {
	    sumscore += 50; // �߶�
	}
	
	if (count4 == 2 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1))) {
	    sumscore += 50; // �߶�
	}

    // ����߶������ġ��������������������������
    if (count1 == 2 && l >= 1 && r >= 1 && (l + r) < 4 && (l + r) > 1) {
        sumscore += 1000; // �߶�
    }
    
    if (count1 == 4 && (l == 0 || r == 0)) {
        sumscore -= 2000; // ����
    }

    if (count1 == 3 && l >= 1 && r == 0) {
        sumscore += 800; // �����
    }

    if (count1 == 3 && l == 1 && r == 1) {
        sumscore += 2000; // ������
    }

    if (count1 == 3 && (l + r) == 1) {
        sumscore += 400; // ����
    }
	
	 // ��Ӷ�˫������˫���ͳ��ĵ�����
    int doubleActiveThree = 0;
    int doubleThree = 0;
    int specialFour = 0;

    // �жϺ�������б�Ϻ�б���Ƿ���˫������˫�������
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

    // ������������������������
    if (doubleActiveThree >= 2) {
        // ����˫����
        sumscore += 1000000;
    } else if (doubleThree >= 2) {
        // ����˫��
        sumscore += 500000;
    } else if (specialFour >= 1) {
        // һ�����ĺ�һ������
        sumscore += 300000;
    }
	
	// �����Ͱ��������
	if ((count1 == 3 && l == 1 && r == 1) || (count2 == 3 && u == 1 && d == 1) ||
	    (count3 == 3 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1))) ||
	    (count4 == 3 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1)))) {
	    // ���������
	    sumscore += 200; // �����ķ���
	
	    // ��������������������п�λ
	    if ((count1 == 3 && (l == 1 || r == 1)) ||
	        (count2 == 3 && (u == 1 || d == 1)) ||
	        (count3 == 3 && ((lu == 1 && rd == 1 && (l == 1 || r == 1)) || (ru == 1 && ld == 1 && (l == 1 || r == 1)))) ||
	        (count4 == 3 && ((lu == 1 && rd == 1 && (l == 1 || r == 1)) || (ru == 1 && ld == 1 && (l == 1 || r == 1))))) {
	        sumscore += 100; // ������ķ���
	    }
	}
	
	// ��������
	if ((count1 == 3 && (l == 0 || r == 0)) ||
	    (count2 == 3 && (u == 0 || d == 0)) ||
	    (count3 == 3 && ((lu == 0 || rd == 0) || (ru == 0 || ld == 0))) ||
	    (count4 == 3 && ((lu == 0 || rd == 0) || (ru == 0 || ld == 0)))) {
	    sumscore += 300; // �����ķ���
	}
	
	// ˫������
	if ((count1 == 4 && l == 1 && r == 1) || (count2 == 4 && u == 1 && d == 1) ||
	    (count3 == 4 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1))) ||
	    (count4 == 4 && ((lu == 1 && rd == 1) || (ru == 1 && ld == 1)))) {
	    sumscore += 100000; // ˫�ĵķ���
	}
	
	// �������
	if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5) {
	    sumscore = 5000000; // ����ֱ�ӻ�ʤ
	}

	// ��һ����һ����������һ�ż������ӣ�����������һ����λ��
	if ((count1 == 1 && ((l == 0 && r >= 1) || (l >= 1 && r == 0))) ||
	    (count2 == 1 && ((u == 0 && d >= 1) || (u >= 1 && d == 0))) ||
	    (count3 == 1 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0))) ||
	    (count4 == 1 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
	{
	    sumscore += 50; // ��һ
	}
	
	// �������һ�������������ż������ӣ�������������һ����λ�����ҶԷ�������û�ж�ס��
	if ((count1 == 2 && l == 0 && r == 1 && scorejudge(x, y - 2) && scorejudge(x, y + 2)) ||
	    (count2 == 2 && u == 0 && d == 1 && scorejudge(x - 2, y) && scorejudge(x + 2, y)) ||
	    (count3 == 2 && lu == 0 && rd == 1 && scorejudge(x - 2, y - 2) && scorejudge(x + 2, y + 2)) ||
	    (count4 == 2 && ld == 0 && ru == 1 && scorejudge(x - 2, y + 2) && scorejudge(x + 2, y - 2)) ||
	    (count1 == 2 && r == 0 && l == 1 && scorejudge(x, y - 2) && scorejudge(x, y + 2)) ||
	    (count2 == 2 && d == 0 && u == 1 && scorejudge(x - 2, y) && scorejudge(x + 2, y)) ||
	    (count3 == 2 && rd == 0 && lu == 1 && scorejudge(x - 2, y - 2) && scorejudge(x + 2, y + 2)) ||
	    (count4 == 2 && ru == 0 && ld == 1 && scorejudge(x - 2, y + 2) && scorejudge(x + 2, y - 2)))
	{
	    sumscore += 100; // ���
	}
	
	// ��һ����һ����������һ�ż������ӣ������˶����Է��赲��
	if ((count1 == 1 && ((l >= 1 && r >= 1) || (l == 1 && r == 1))) ||
	    (count2 == 1 && ((u >= 1 && d >= 1) || (u == 1 && d == 1))) ||
	    (count3 == 1 && ((ld >= 1 && ru >= 1) || (ld == 1 && ru == 1))) ||
	    (count4 == 1 && ((lu >= 1 && rd >= 1) || (lu == 1 && rd == 1))))
	{
	    sumscore += 10; // ��һ
	}
	
	// ��������һ�������������ż������ӣ������˶����Է��赲��
	if ((count1 == 2 && ((l >= 1 && r >= 1) || (l == 1 && r == 1))) ||
	    (count2 == 2 && ((u >= 1 && d >= 1) || (u == 1 && d == 1))) ||
	    (count3 == 2 && ((ld >= 1 && ru >= 1) || (ld == 1 && ru == 1))) ||
	    (count4 == 2 && ((lu >= 1 && rd >= 1) || (lu == 1 && rd == 1))))
	{
	    sumscore += 20; // ����
	}


    chess[x][y] = Nochess;

	
	return sumscore;

}

void Msg_restart(int par)
{
	 // ��Ϸ��������·���
    if (par == 1) {
        if (player == p1) {
            black_score++; // ����ʤ�������������1
        } else {
            white_score++; // ����ʤ�������������1
        }
    }
	
    int res;
    if (par == 1) {
        if (player == p1) {
            res = MessageBoxA(0, "����ʤ,�Ƿ��ؿ���", "������", MB_YESNO | MB_SYSTEMMODAL);
        } else {
            res = MessageBoxA(0, "����ʤ,�Ƿ��ؿ���", "������", MB_YESNO | MB_SYSTEMMODAL);
        }
    } else {
        res = MessageBoxA(0, "ƽ��,�Ƿ��ؿ���", "������", MB_YESNO | MB_SYSTEMMODAL);
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

    // �ҵ�����������λ��
    int minDistance = N * N; // ��ʼ��Ϊ�����ܾ���
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (chess[i][j] == p1) // ����Ǻ���
            {
                // �������
                int distance = abs(i - 6) + abs(j - 6); // �������̴�С��N*N
                if (distance < minDistance)
                {
                    minDistance = distance;
                    row1 = i;
                    col1 = j;
                }
            }
        }
    }

    // ������������λ�ø������ѡ��һ��λ��
    int offset = rand() % 3 - 1; // ���ѡ�� -1��0��1 �е�һ��ƫ��
    row1 += offset;
    col1 += offset;

    // ȷ��ѡ���λ���ǺϷ���
    if (row1 < 0) row1 = 0;
    if (row1 >= N) row1 = N - 1;
    if (col1 < 0) col1 = 0;
    if (col1 >= N) col1 = N - 1;

    while (!judge(row1, col1))
    {
        // ���ѡ���λ�ò��Ϸ����������ѡ��
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
		if (row1 == -1 && col1 == -1 && row2 == -1 && col2 == -1)//û�ҵ����Ž� ƽ��
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

void Mouse() // ����ƶ�
{

    if (param == player_player)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            switch (msg.uMsg)
            {
            case WM_LBUTTONDOWN://�������
                int x1 = mod_xy(msg.x);
                int y1 = mod_xy(msg.y);
                int x = msg.x;
                int y = msg.y;

                if (x >= width + 20 && x <= width + 100 && y >= heigth - 80 && y <= heigth - 30) {
                    // ��ҵ���˷��ذ�ť
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
            case WM_LBUTTONDOWN://�������
                int x1 = mod_xy(msg.x);
                int y1 = mod_xy(msg.y);
                int x = msg.x;
                int y = msg.y;

                if (x >= width + 20 && x <= width + 100 && y >= heigth - 80 && y <= heigth - 30) {
                    // ��ҵ���˷��ذ�ť
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
	// ����һ�� IMAGE ���͵ı��������ڴ洢����ͼƬ
	IMAGE img;
	
	// ���ر���ͼƬ
	loadimage(&img, _T("3.jpg"));

		 // ���尴ť״̬
    bool playerAIClicked = false;
    bool playerPlayerClicked = false;
    bool computerComputerClicked = false;
    bool helpClicked = false;

        // �������
	    black_score = 0;
	    white_score = 0;
	    
    initgraph(width*1.3, heigth); // ��ʼ������
    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    setbkcolor(WHITE); // ���ñ���ɫΪ��ɫ
    cleardevice();
    
    // ���ر���ͼƬ
    IMAGE bgImage;
    loadimage(&bgImage, _T("2.jpg"));

    // ���Ʊ���ͼƬ
    putimage(0, 0, &bgImage);
   
    // ����Ļ�ϴ��������ĳ�ʼ���棬������ť
    settextstyle(30, 0, _T("����"));
    settextcolor(BLACK); // ���ı���ɫ����Ϊ��ɫ
    outtextxy(200, 200, _T("��ѡ����Ϸģʽ��"));

    // ����AI��ս��ť
    
    settextstyle(20, 0, _T("����"));
    outtextxy(260, 265, _T("�˻���ս"));

    // ����˫�˶�ս��ť
    
    outtextxy(260, 335, _T("˫�˶�ս"));
    
    // ���ƻ�����ս��ť
	
	outtextxy(260, 405, _T("������ս"));


    // ���ư�����ť���������Ͻǲ���С��
	
	settextstyle(16, 0, _T("����"));
	outtextxy(560, 55, _T("�ض�")); // �����ı���λ��
    
	// �������ְ�ť
	 // ������ť������ʹ�С
	settextstyle(16, 0, _T("����"));
	if (isMuted) {
	    setcolor(RED); // ���ú�ɫ
	}
	outtextxy(560, 105, _T("����")); // �����ı���λ��


    
    // ��������
    if (mciSendString("open \"2.mp3\" alias music", NULL, 0, NULL) == 0) {
        // ����Ƶ�ļ��ɹ�

        // ������Ƶ�ļ�
        if (mciSendString("play music repeat", NULL, 0, NULL) != 0) {
            // ��������޷�������Ƶ�ļ�
        }
    } else {
        // ��������޷�����Ƶ�ļ�
    }

    int choice = 0; // ���ڼ�¼��ҵ�ѡ��0��ʾδѡ��
	int computer_mode = 0; // ���ڼ�¼������ս��ѡ��
	
 while (choice == 0) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                int x = msg.x;
                int y = msg.y;
				
				     if (x >= 550 && x <= 600 && y >= 100 && y <= 130) {
					    // ��������ְ�ť
					    if (isMuted) {
					        // �ָ����ֲ���
					        settextcolor(BLACK);
					        isMuted = false;
					        mciSendString("play music repeat", NULL, 0, NULL);
					    } else {
					        // ��������
					        isMuted = true;
					        mciSendString("stop music", NULL, 0, NULL);
					    }
					    
					    // �������ְ�ť
					    rectangle(550, 100, 600, 130); // ������ť������ʹ�С
					    settextstyle(16, 0, _T("����"));
					  	  
								if (isMuted) {
					    // ���»��Ʊ���
					    putimage(550, 100, &img);
					
					    settextcolor(RED); // ���ú�ɫ
					    setbkmode(TRANSPARENT); // ���ñ������ģʽΪ͸��
					    outtextxy(560, 105, _T("����")); // �����ı���λ�ò���ʾ"����"
					} else {
					    // ���»��Ʊ���
					    putimage(550, 100, &img);
					
					    settextcolor(BLACK); // �����ı���ɫΪ��ɫ��������ɫ
					    setbkmode(TRANSPARENT); // ���ñ������ģʽΪ͸��
					    outtextxy(560, 105, _T("����")); // �����ı���λ�ò���ʾ"����"
					}



					}


                // ����Ƿ����˲�ͬ��ť��������Ӧ�İ�ť״̬
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

                // ������ɿ�ʱ��ת����Ӧ��ҳ��
                if (x >= 200 && x <= 400 && y >= 250 && y <= 300 && playerAIClicked) {
                    choice = player_AI; // ���ѡ���˻���ս
                } else if (x >= 200 && x <= 400 && y >= 320 && y <= 370 && playerPlayerClicked) {
                    choice = player_player; // ���ѡ��˫�˶�ս
                } else if (x >= 200 && x <= 400 && y >= 390 && y <= 440 && computerComputerClicked) {
                      computer_mode = computer_computer; // ���ѡ�������ս
                    choice = computer_computer; // ����choiceΪcomputer_computer���˳�ѡ��ѭ��
                } else if (x >= 550 && x <= 600 && y >= 50 && y <= 80 && helpClicked) {
                    // ����˰�����ť��������ʾ��Ϸ������߼�
                    show_game_rules();
                }

                // �ָ���ť״̬
                playerAIClicked = false;
                playerPlayerClicked = false;
                computerComputerClicked = false;
                helpClicked = false;
            
			

            }
            
        }

        // �������
        //cleardevice();

        // ���ư�ť
        if (playerAIClicked) {
            setcolor(RED); // �����ɫ
            settextstyle(20, 0, _T("����"));
            outtextxy(260, 265, _T("�˻���ս"));
        } else {
            setcolor(WHITE); // �׿���ɫ
        }
        

        if (playerPlayerClicked) {
            setcolor(RED); // �����ɫ
            settextstyle(20, 0, _T("����"));
            outtextxy(260, 335, _T("˫�˶�ս"));
        } else {
            setcolor(WHITE); // �׿���ɫ
        }
        

        if (computerComputerClicked) {
            setcolor(RED); // �����ɫ
            settextstyle(20, 0, _T("����"));
            outtextxy(260, 405, _T("������ս"));
        } else {
            setcolor(WHITE); // �׿���ɫ
        }
        

        if (helpClicked) {
            setcolor(RED); // �����ɫ
            settextstyle(16, 0, _T("����"));
			outtextxy(560, 55, _T("�ض�")); // �����ı���λ��
        } else {
            setcolor(WHITE); // �׿���ɫ
        }
        
		
		
    }


	param = choice; // ������Ϸģʽ
	
	
	 if (computer_mode == computer_computer) {
	    param = computer_mode; // ������ϷģʽΪ������ս
	    cleardevice(); // �����ʼ����
	    draw_checkboard(); // ������Ϸ����
	    Oninit(); // ��ʼ����Ϸ����
	    // ���ѡ���˻�����ս�����������ս����
	    computer_computer_game();
	} else {


  if (param == player_AI) {
        // ������ѡ���˻���ս
        int result = MessageBox(NULL, "�Ƿ�ѡ�����", "ѡ����Ϸģʽ", MB_YESNO);
        if (result == IDYES) {
            playerIsFirst = true; // ���ѡ�����
            // ���򣬽����˻���˫�˶�ս
        param = choice; // ������Ϸģʽ
        cleardevice(); // �����ʼ����
        draw_checkboard(); // ������Ϸ����
        Oninit(); // ��ʼ����Ϸ����
		chesscomputer2(); // �õ���������
  
            
        } else {
            playerIsFirst = false; // ���ѡ������
        

        // ���򣬽����˻���˫�˶�ս
        param = choice; // ������Ϸģʽ
        cleardevice(); // �����ʼ����
        draw_checkboard(); // ������Ϸ����
        Oninit(); // ��ʼ����Ϸ����

        // ������Ϸѭ��
        while (1) {
            Mouse();
        }
    }
    }else{
	
       // ���򣬽����˻���˫�˶�ս
        param = choice; // ������Ϸģʽ
        cleardevice(); // �����ʼ����
        draw_checkboard(); // ������Ϸ����
        Oninit(); // ��ʼ����Ϸ����

        // ������Ϸѭ��
        while (1) {
            Mouse();
        }

}
}
}

void show_game_rules() {
	settextstyle(100, 0, _T("����"));

    const char* gameRulesText = 
    						"��Ϸ�����Լ�������\n\n"
                            
                            
                            "������ս��\n"
                            "���ģʽ�����������㷨�ģ�û�²��õ�\n\n"
                            
                            
                            "�˻���ս���ص�1����\n"
							"*****************************************************\n"
                            "����˻���ս��ť��ᵯ��һ����������ѡ�����ֻ��Ǻ��֣���������п��ܻ���������������棬�ֶ��ƿ������漴�ɿ�������\n" 
							"*****************************************************\n\n"
                            
                            "��Ϸ�����½Ƿ��ؼ����ص�2����\n"
                            "*****************************************************\n"
                            "��Ϸ�е�����½Ƿ��ؼ����ص������棬��ʱ���������ˢ�µ���Ļ����£����������ˣ�ֻ��Ҫ����������ȥ����\n"
                            "*****************************************************\n\n"
                            
                            
                            "����hj�����ṩ�� �������ǹ���û�ӵģ���Ϊ�����޻ڣ����Բ�����Ϊ����͵��������\n"
							"���������Ϸ����Ȥ��ף����ˣ�������κν�����޸ķ����������и���Դ��(=.=)";


    // ʹ��MessageBox����һ����Ϣ������ʾ��Ϸ����
    MessageBox(NULL, gameRulesText, "��Ϸ����", MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND);
}


void restart()
{
    Oninit();
    cleardevice(); // �����ͼ����
    draw_checkboard(); // ������Ϸ����

    // ��������״̬
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            chess[i][j] = Nochess;
        }
    }

    // ������������
    chess_num = 0;

    // ���õ�ǰ���Ϊ����
    currentPlayer = p1; // ����ȷ�����������Ϊ p1��������


	    if (param == player_AI && playerIsFirst)
    {
        // ������˻�ģʽ�����ѡ����֣��õ�������һ��
        chesscomputer2();
    }
	
    if (param != computer_computer)
    {
        // ��Ҷ����ģʽ���ȴ���ҵĶ���
        while (1)
        {
            Mouse();
        }
    }
    else if (param == computer_computer)
    {
        // ������սģʽ��ѭ������ computer_computer_game
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

