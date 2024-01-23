#include "RankingDate.h"
#include <stdio.h>
#include <string.h>

RankingDate::RankingDate()
{
	for (int i = 0; i < 6; i++)
	{
		score[i] = NULL;
		rank[i] = NULL;
		for (int j = 0; j < 15; j++)
		{
			name[i][j] = '\0';
		}
	}
}

RankingDate::~RankingDate()
{

}

//初期化処理
void RankingDate::Initialize()
{
	//ランキングデータの読み込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_date.csv", "r");

	//エラーチェック
	if (result != 0)
	{

	}
}
