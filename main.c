/**
 * MAIN.C
 */

//#define _DEBUG			// デバッグメッセージを表示
#define _NODEBUG			// デバッグメッセージを非表示

#define ERROR_ARGC	0xAC15D1FF	// コマンドライン引数の個数が違う場合
#define ERROR_BADSIZE	0xBAD512E	// 行列や画面などのサイズが違う場合
#define ERROR_NOTODD	0x2070DD	// 偶数でない場合

#define default_width	17		// 生成したい迷路のデフォルトの幅
#define default_height	17		// 生成したい迷路のデフォルトの高さ

#include "stdafx.h"			// make時にstdafx.hを参照することで、更新が必要なファイルを判断する。

/* MAIN */
int main(int argc, char **argv)		// argcはコマンドライン引数の個数である。 argvにはコマンドライン引数の配列が格納され、argv[0]には常にこのプログラムのpathが格納される。
{
	if(argc != 3 && argc != 1)	// 引数を指定せずに実行されるか、生成するマップの行数と列数が入力されることを期待している。
	{
		error(ERROR_ARGC, "Number of argments is different .");
	}
	if(!argv[1]%2 || !argv[2]%2)	// 行数と列数がともに奇数であることを期待している。
	{
		error(ERROR_NOTODD, "コマンドライン引数には奇数を入力してください");
	}

	Mat *maze;			// 今回生成する迷路のポインタ。 Mat型の実装はmatrix.hならびにmatrix.cを参照のこと。
	if(argc == 3)			// 行数と列数が指定された場合、そのサイズの迷路を生成する。
	{
		maze = genMaze(atoi(argv[1]), atoi(argv[2]));
	} else {			// そうでなければ、当ファイルの先頭で定義されたサイズを使う。
		maze = genMaze(default_width, default_height);
	}
	showMaze(maze);			// 生成した迷路を表示する。穴掘り法を使う前提なので、この時点ではすべてのマスが壁である。

	initMaze(maze);			// 生成した迷路を初期化する。

	digMaze(maze, 1, 1);		// 穴掘り法により通路を生成する。この処理が完了した時点で迷路は完成である。

	printf("maze generated. \n");

	struct winsize ws;		// ターミナルの画面サイズを格納する構造体インスタンス。

		
	for(;;)				// 割り込みによる操作などを期待したループ
	{
		// 取得したターミナルの画面サイズが不正ならばエラーを吐いて終了。
		if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		{
			error(ERROR_BADSIZE, "WINDOWSIZE IS BAD");
			exit(1);
		}

		// 割り込み処理があった場合の条件分岐
		switch(isInterrupt())
		{
			case 'q':	// qが入力された場合は強制終了
				exit(0);

			case (char)0x0A:// ENTERが入力された場合の処理は未実装である。
				break;

			default:	//
				break;
		}
	}

	return 0;			// 滞りなく終われば0を返して終了
}

