# include <Siv3D.hpp>
# include "include/Utility.hpp"
# include "include/Asset.hpp"
# include "include/Title.hpp"
# include "include/Option.hpp"
# include "include/HowToPlay.hpp"
# include "include/Game.hpp"
# include "include/Result.hpp"

void Main()
{
	// ウィンドウサイズを800x600にする
	Window::Resize(800, 600);
	// ウィンドウサイズは自由に変形可能
	Window::SetStyle(WindowStyle::Sizable);
	// シーン画面のサイズは一定
	Scene::SetResizeMode(ResizeMode::Keep);
	// ウィンドウの名前
	Window::SetTitle(U"Hamburger Battle");

	// シーン追加
	App manager;
	manager.add<Title>(SceneState::Title);
	manager.add<Option>(SceneState::Option);
	manager.add<HowToPlay>(SceneState::HowToPlay);
	manager.add<Game>(SceneState::Game);
	manager.add<Result>(SceneState::Result);
	// シーン遷移時のフェイドイン/アウトの色を設定
	manager.setFadeColor(ColorF{ 0, 0, 0 });

	// タイトル画面用のアセットを作成
	CommonAssetLoad();

	// FPS固定のためのストップウォッチ
	Stopwatch FPS_SW;
	// FPS用カウントダウン開始
	FPS_SW.start();

	// エスケープキーを押しても終了しない
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	while (System::Update())
	{
		ClearPrint();

		// シーン管理
		if (not manager.update())
		{
			break;
		}

		// 1/60秒が経過するまでループ
		while (FPS_SW.msF() < 1000.0 / FPS) {}
		//ストップウォッチをリスタート
		FPS_SW.restart();
	}
}
