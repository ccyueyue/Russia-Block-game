/*
1、创建项目
2、导入素材
3、C++开发
4、设计C++项目的模块；就是类的设计；
	Block类 Tetris游戏类
5、设计各个模块的主要接口
6、启动游戏
*/
#include"Tetris.h"

int main()
{
	Tetris game(20, 10, 263, 133, 36);
	game.play();
	return 0;

}