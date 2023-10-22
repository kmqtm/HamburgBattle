#pragma once
# include <Siv3D.hpp>
# include "Utility.hpp"

// 終了シーンの定義
class Exit : public App::Scene
{
public:

	Exit(const InitData& init);

	void update() override;

	void draw() const override;
};
