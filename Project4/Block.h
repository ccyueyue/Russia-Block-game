#pragma once
#include<graphics.h> //��Ҫ�߰�װeasyxͼ�ο�
#include<vector>
struct Point {
	int row;
	int col;
};
class Block
{
public:
	Block();

	void down(); //�½�

	void moveLeftRight(int offset);//��������

	void rotate();//��ת

	void draw(int leftMargin, int topMargin);//��������˹����

	static IMAGE** getImages();

	Block& operator = (const Block& other);

	bool blockInMap(const std::vector<std::vector<int>>&map);
	
	void solidify(std::vector<std::vector<int>>& map);

	int getBlockType();

private:
	int blockType;//��������
	Point smallBlocks[4];
	IMAGE* img;

	static IMAGE* imgs[7];

	static int size;



};

