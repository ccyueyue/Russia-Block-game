#pragma once
#include <vector>
#include<graphics.h>
#include"Block.h"
class Tetris
{
public:
	//构造函数
	Tetris(int row, int cols, int left, int right, int blockSize);

	void init();//初始化

	void play();//开始游戏

private:
	void keyEvent();

	void updateWindow();

	int getDelay();//返回距离上一次调用该函数，间隔了多少时间（ms）,第一次调用函数 ，返回0

	void down();

	void clearLine();

	void moveLeftRight(int offset);

	void rotate();

	void drawScore();

private:
	int m_delay;
	
	bool m_update;

	std::vector<std::vector<int>> map;//0:没有方块 5:第5钟方块
	
	int rows;
	
	int cols;

	int leftMargin;

	int topMargin;

	int blockSize;

	IMAGE imgBg;

	Block* curBlock;//当前方块

	Block* nextBlock;//预告方块

	Block backBlock;//当前方块下落过程中，用来备份上一个合法位置

	int score;//current score
};

