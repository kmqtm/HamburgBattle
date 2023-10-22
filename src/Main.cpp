# include <Siv3D.hpp>
# include "include/Utility.hpp"
# include "include/Asset.hpp"
# include "include/Title.hpp"
# include "include/Option.hpp"
# include "include/HowToPlay.hpp"
# include "include/Game.hpp"
# include "include/Result.hpp"
# include "include/Exit.hpp"

void Main()
{
	// ウィンドウサイズを800x600にする
	Window::Resize(800, 600);
	// ウィンドウサイズは自由に変形可能
	Window::SetStyle(WindowStyle::Sizable);
	// シーン画面のサイズは一定
	Scene::SetResizeMode(ResizeMode::Keep);
	// ウィンドウの名前
	Window::SetTitle(U"Hamburg Battle");
	// エスケープキーを押しても終了しない
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	// シーン追加(最初に追加するシーンがデフォルトのシーンとなる)
	App manager;
	manager.add<Title>(SceneState::Title);
	manager.add<Option>(SceneState::Option);
	manager.add<HowToPlay>(SceneState::HowToPlay);
	manager.add<Game>(SceneState::Game);
	manager.add<Result>(SceneState::Result);
	manager.add<Exit>(SceneState::Exit);
	// シーン遷移時のフェイドイン/アウトの色を設定
	manager.setFadeColor(ColorF{ 0, 0, 0 });

	// FPS固定のためのストップウォッチ
	Stopwatch FPS_SW;
	// FPS用カウントダウン開始
	FPS_SW.start();

	// アセット管理用クラスのインスタンス化
	AssetControlClass CommonAssetControl;
	// 事前ロード用アセットの準備
	CommonAssetControl.AssetPrepare(U"PreLoad");

	// メインループ
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
