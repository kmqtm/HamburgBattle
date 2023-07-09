#pragma once
# include <Siv3D.hpp>

// FPSを60に固定する
const int32 FPS = 60;

// 1フレームで1カウント
void CountControl(int32 &);

// シーンの状態
enum class SceneState
{
	Title,
	Option,
	HowToPlay,
	Game,
	Result,
};
// シーンマネージャー
using App = SceneManager<SceneState>;
