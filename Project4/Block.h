#pragma once
#include<graphics.h> //需要线安装easyx图形库
#include<vector>
struct Point {
	int row;
	int col;
};
class Block
{
public:
	Block();

	void down(); //下降

	void moveLeftRight(int offset);//左移右移

	void rotate();//旋转

	void draw(int leftMargin, int topMargin);//画出俄罗斯方块

	static IMAGE** getImages();

	Block& operator = (const Block& other);

	bool blockInMap(const std::vector<std::vector<int>>&map);
	
	void solidify(std::vector<std::vector<int>>& map);

	int getBlockType();

private:
	int blockType;//方块类型
	Point smallBlocks[4];
	IMAGE* img;

	static IMAGE* imgs[7];

	static int size;



};

