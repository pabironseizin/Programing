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
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.csvが開けませんでした\n");
	}

	//対象ファイルから読み込む
	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%6d,%2d,%[^,],\n", &score[i], &rank[i], name[i], 15);
	}

	//ファイルクローズ
	fclose(fp);

	//末尾データの設定
	score[5] = 0;
	rank[5] = 0;
	name[5][0] = '\0';
}

//終了処理
void RankingDate::Finalize()
{

}

//データ設定処理
void RankingDate::SetRankingDate(int score, const char* name)
{
	this->score[5] = score;
	strcpy_s(this->name[5], name);

	SortData();
}

//スコア取得処理
int RankingDate::GetScore(int value) const
{
	return score[value];
}

//ランク取得処理
int RankingDate::GetRank(int value) const
{
	return rank[value];
}

//名前取得処理
const char* RankingDate::GetName(int value) const
{
	return name[value];
}

//データ入れ替え処理
void RankingDate::SortData()
{
	//選択ソートを使用し、降順で入れ替える
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (score[i] <= score[j])
			{
				int tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;

				char buf[15] = {};
				strcpy_s(buf, name[i]);
				strcpy_s(name[i], name[j]);
				strcpy_s(name[j], buf);
			}
		}
	}

	//順位を整列させる
	for (int i = 0; i < 5; i++)
	{
		rank[i] = 1;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (score[i] > score[j])
			{
				rank[j]++;
			}
		}
	}

	//ランキングデータの書き込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.csvが開けませんでした\n");
	}

	//対象ファイルに書き込み
	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%d,%d,%s,\n", score[i], rank[i], name[i]);
	}

	//ファイルクローズ
	fclose(fp);
}