#include "Tetris.h"
#include<ctime>
#include<cstdlib>
#include"Block.h"
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

const int SPEED_NORMAL = 500; //ms
const int SPEED_QUICK = 50;//ms
Tetris::Tetris(int row, int cols, int left, int top, int blockSize){
	this->rows = row;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;
	for (int i = 0; i < rows; i++) {
		std::vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::init()
{
	m_delay = SPEED_NORMAL;

	//m_delay = false;

	//配置随机种子
	srand(time(NULL));

	initgraph(938,896);//创建游戏窗口

	loadimage(&imgBg,"res/bg2.png");//加载背景图片

	//初始化游戏区的数据
	char data[20][10];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = 0;
		}
	}
	score = 0;
}

void Tetris::play()
{
	init();
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;

	while (1) {
		//接收用户输入
		keyEvent();

		timer += getDelay();
		if (timer > m_delay ) {
			timer = 0;
			down();
			m_update = true;
		
		}
		if (m_update) {
			m_update = false;
			//渲染游戏画面
			updateWindow();

			//更新游戏的数据 
			clearLine();
		}
		


	}
}

void Tetris::keyEvent()
{
	bool rotateFlag = false;
	unsigned char ch; //0`255
	
	int dx = 0;

	if (_kbhit()) {
		ch = _getch();
		//如果按下方向键，会自动返回两个字符
		//如果按向上方向键，会返回 224 72  向下键 224 80 向左键 224 75 向右键224 77
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				rotateFlag = true;
				break;
			case 80:
				m_delay = SPEED_QUICK;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;
			}
		}
	}
	if (rotateFlag) {
		rotate();
		m_update = true;
	}
	if (dx != 0) {
		moveLeftRight(dx);
		m_update = true;
	}
	
}

void Tetris::updateWindow()
{
	putimage(0, 0, &imgBg);//绘制背景图片

	IMAGE** imgs = Block::getImages();
	BeginBatchDraw();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0)continue; 
			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, imgs[map[i][j]-1]);

		}
	}

	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(689, 150);

	drawScore();//绘制分数

	EndBatchDraw();
}

int Tetris::getDelay()//第一次调用返回0，之后再调用返回与上一次调用的间隔时间
{
	static unsigned long long lastTime = 0;

	unsigned long long currentTime = GetTickCount();
	
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

void Tetris::down()
{
	backBlock = *curBlock;
	curBlock->down();
	if (!curBlock->blockInMap(map)) {
		//把这个方块固化
		backBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}
	m_delay = SPEED_NORMAL;
	
}

void Tetris::clearLine()
{
	int k = rows - 1;//存储数据的行数
	int lines = 0;
	for (int i = rows - 1; i >= 0; i--) {
		//检查第i行是否满行
		int count = 0;
		for (int j = 0; j < cols; j++) {
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j];//一边扫描一边存储
		}
		if (count < cols) {//不是满行
				k--;
		}
		else {
			lines++;
		}
	}
	if (lines > 0) {
		//计算得分
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];

		mciSendString("play res/xiaochu1.mp3", 0, 0, 0);
		m_update = true;
	}
}

void Tetris::moveLeftRight(int offset)
{
	backBlock = *curBlock;
	curBlock->moveLeftRight(offset);

	if (!curBlock->blockInMap(map)) {
		*curBlock = backBlock;
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7) return;

	backBlock = *curBlock;
	curBlock->rotate();
	
	if (!curBlock->blockInMap(map)) {
		*curBlock = backBlock;
	}
}

void Tetris::drawScore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);

	setcolor(RGB(180, 180, 180));
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;//设置字体为“抗锯齿”效果

	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);//设置字体背景为透明效果
	outtextxy(670, 727, scoreText);
}
