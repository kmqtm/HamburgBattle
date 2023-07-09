#pragma once
# include <Siv3D.hpp>
# include "Utility.hpp"

// 遊び方説明シーンの定義
class HowToPlay : public App::Scene
{
public:

	HowToPlay(const InitData& init);

	void update() override;

	void draw() const override;
};
