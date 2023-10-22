#pragma once
# include <Siv3D.hpp>
# include "Utility.hpp"

// タイトル画面に用いるフォントのサイズ
# define TitleFontSize 40

// タイトルシーンの定義
class Title : public App::Scene
{
public:
	// タイトル画面で任意のキーが押された判定を保存
	bool ANY_KEY;

	Title(const InitData& init);

	~Title();

	void update() override;

	void draw() const override;
};
