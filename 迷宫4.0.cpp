// 迷宫4.0.cpp

#include<iostream>
#include<cmath>
#include<ctime>
using namespace std;
void mazeGenerator(); //随机生成迷宫 提供起始点坐标
int searchpath(int, int);
int mazeTraverse(int, int, int);  //寻找最短路径 '.' ->'X'
void printmaze();
void printshortestpath();

#define maze_max 10000
char maze[maze_max][maze_max];
int n, m, min = 100000000; //迷宫的长宽
int xx, yy; //迷宫坐标
int book[maze_max][maze_max];
int fpath[maze_max][maze_max];
int path[maze_max][maze_max];


int main()
{
loop:
	cout << "请输入迷宫行列(奇数)：" << endl;
	while (cin >> n >> m) {
		cout << "行：" << n << " " << "列：" << m << endl;
		for (int i = 0; i <= (n + 2); i++) {
			for (int j = 0; j <= (m + 2); j++) {
				maze[i][j] = 1;  //初始化为墙
			}
		}

		mazeGenerator();
		printmaze();

		for (int i = 0; i <= (n + 2); i++) {
			for (int j = 0; j <= (m + 2); j++) {
				fpath[i][j] = maze[i][j];
			}
		}
		mazeTraverse(2, 1, 0);  //递归

		cout << "最短路径为：" << min << "步" << endl;
		cout << "过程如下：" << endl;
		printshortestpath();

		min = 100000000; goto loop;
	}
	return 0;
}

void printmaze() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			fputs(maze[i][j] == 0 ? ". " : "# ", stdout);
		}cout << endl;
	}cout << endl;
}

void printshortestpath()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (path[i][j] == 0)cout << ". ";
			else if (path[i][j] == 1)cout << "# ";
			else if (path[i][j] == 2)cout << "X ";
		}cout << endl;
	}cout << endl;
}

int searchpath(int x, int y)
{
	static int direc[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
	int dx, dy;

	dx = (x + 1) * 2;
	dy = (y + 1) * 2;
	maze[dx][dy] = 0;

	int next, change;
	change = rand() % 2 ? 1 : 3;
	for (int i = 0, next = rand() % 4; i < 4; i++, next = (next + change) % 4) {
		if (maze[dx + 2 * direc[next][0]][dy + 2 * direc[next][1]] == 1) {
			maze[dx + direc[next][0]][dy + direc[next][1]] = 0;
			searchpath(x + direc[next][0], y + direc[next][1]);
		}
	}
	return 0;
}

void mazeGenerator() {

	for (int i = 0; i <= n + 1; i++) {
		maze[i][0] = 0;
		maze[i][m + 1] = 0;
	}
	for (int i = 0; i <= m + 1; i++) {
		maze[0][i] = 0;
		maze[n + 1][i] = 0;
	}

	maze[2][1] = 0;
	maze[n - 1][m] = 0;

	srand((unsigned)time(NULL));
	searchpath(rand() % (n / 2), rand() % (m / 2));
}



int mazeTraverse(int x, int y, int step)
{
	if (x == (n - 1) && y == m) { //判断是否到达终点 并记录最短路径
		if (step < min)
			min = step;
		for (int i = 0; i <= (n + 2); i++) {
			for (int j = 0; j <= (m + 2); j++) {
				path[i][j] = fpath[i][j];
			}
		}
		return min;
	}

	int nx, ny;
	for (int i = 0; i <= 3; i++) {
		int next[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } }; //右上左下

		nx = x + next[i][0];
		ny = y + next[i][1];

		fpath[2][1] = 2;



		if (nx<1 || nx>n || ny<1 || ny>m)
			continue;
		else if (maze[nx][ny] == 0 && book[nx][ny] == 0) {
			book[nx][ny] = 1; //标记当前为走过的路
			fpath[nx][ny] = 2;
			mazeTraverse(nx, ny, step + 1);
			fpath[nx][ny] = 0;
			book[nx][ny] = 0;


		}

	}
	return 0;
}

/*心得
跟迷宫1.0的差距主要在maze Generater部分改用了srand函数，以及后续的searchpath都搭配rand函数，
因为前面先学了【深度优先算法】用来查找最短路径。结果导致mazeGenerater的部分也采用了相同的观念
但深度优先算法的迷宫生成，长宽只能用奇数啊。。。
跟迷宫2.0的差距主要在mazeTraversor部分增加了二维数组fpath&path来记录最短路径&脚印，
将原本打印的部分printmaze 函数新增了printshortestpath函数来输出最短路径~ 最可惜的就是依旧无法支持偶数行列QAQ
再想办法再想办法啊啊啊啊
*/
