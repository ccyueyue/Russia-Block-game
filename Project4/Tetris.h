#pragma once
#include <vector>
#include<graphics.h>
#include"Block.h"
class Tetris
{
public:
	//���캯��
	Tetris(int row, int cols, int left, int right, int blockSize);

	void init();//��ʼ��

	void play();//��ʼ��Ϸ

private:
	void keyEvent();

	void updateWindow();

	int getDelay();//���ؾ�����һ�ε��øú���������˶���ʱ�䣨ms��,��һ�ε��ú��� ������0

	void down();

	void clearLine();

	void moveLeftRight(int offset);

	void rotate();

	void drawScore();

private:
	int m_delay;
	
	bool m_update;

	std::vector<std::vector<int>> map;//0:û�з��� 5:��5�ӷ���
	
	int rows;
	
	int cols;

	int leftMargin;

	int topMargin;

	int blockSize;

	IMAGE imgBg;

	Block* curBlock;//��ǰ����

	Block* nextBlock;//Ԥ�淽��

	Block backBlock;//��ǰ������������У�����������һ���Ϸ�λ��

	int score;//current score
};

