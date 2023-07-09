#pragma once
# include <Siv3D.hpp>
# include "Utility.hpp"

// リザルトシーンのフォントサイズ
# define ResultFontSize 40

// リザルトシーンの定義
class Result : public App::Scene
{
public:

	Result(const InitData& init);

	void update() override;

	void draw() const override;
};
