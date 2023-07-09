#pragma once
# include <Siv3D.hpp>
# include "Utility.hpp"

// タイトル画面に用いるフォントのサイズ
# define OptionFontSize 35

// オプションシーンの定義
class Option : public App::Scene
{
public:

	Option(const InitData& init);

	void update() override;

	void draw() const override;
};
