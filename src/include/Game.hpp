#pragma once
# include <Siv3D.hpp>
# include "Utility.hpp"

// ゲームスコアの参照
int32 GetGameScore(void);
// ゲームスコアのリセット
void ResetGameScore(void);

// ゲームBGMを再生
void PlayGameBGM(void);

// ゲームシーンの定義
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
