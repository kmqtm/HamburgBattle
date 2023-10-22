# include <Siv3D.hpp>
# include "../include/Asset.hpp"
# include "../include/Utility.hpp"
# include "../include/Option.hpp"
# include "../include/Button.hpp"

//#####################################
// オプションシーン
//#####################################

// ボタンのインスタンス化
static const Button SIZE1(OptionFontSize, U"DEFAULT", 200.0, 320.0, true);
static const Button SIZE2(OptionFontSize, U"600 x 450", 390.0, 320.0, false);
static const Button SIZE3(OptionFontSize, U"1200 x 900", 610.0, 320.0, false);
// ボタンインスタンスの配列
static Array<Button> OptionButtons = { SIZE1, SIZE2, SIZE3 };

// アセット管理用クラスのインスタンス化
static AssetControlClass OptionAssetControl;

// オプションシーンのコンストラクタ
Option::Option(const InitData& init)
	: IScene{ init }
{
	// オプションシーンアセットの準備
	OptionAssetControl.AssetPrepare(U"Option");
}

// オプションシーンのデコンストラクタ
Option::~Option()
{
	// アセットの登録解除
	OptionAssetControl.AssetUnregister();
}

// オプションシーンの更新関数
void Option::update()
{
	// Escキーが押されたら
	if (KeyEscape.down())
	{
		// 画面上の文字を消去
		ClearPrint();

		// キャンセル音
		AudioAsset(U"Cancel").play();

		// タイトルシーンに遷移
		changeScene(SceneState::Title, 0.8s);
	}

	// Zキーが押されたら
	else if (KeyZ.down())
	{
		// 決定音
		AudioAsset(U"Decide").setVolume(0.4);
		AudioAsset(U"Decide").play();

		// DEFAULT
		if (OptionButtons.at(0).ButtonSelected == true)
		{
			// ウィンドウサイズを800x600にする
			Window::Resize(800, 600);
		}
		// 600 x 450
		else if (OptionButtons.at(1).ButtonSelected == true)
		{
			// ウィンドウサイズを600x450にする
			Window::Resize(600, 450);
		}
		// 1200 x 800
		else if (OptionButtons.at(2).ButtonSelected == true)
		{
			// ウィンドウサイズを1200x800にする
			Window::Resize(1200, 800);
		}
	}

	// 左矢印の入力
	else if (KeyLeft.down())
	{
		ButtonSelectLeft(OptionButtons);
	}
	// 右矢印の入力
	else if (KeyRight.down())
	{
		ButtonSelectRight(OptionButtons);
	}
}

// オプションシーンの描画関数
void Option::draw() const
{
	FontAsset(U"GridGazer")(U"Select your preferred window size\nWindow size can also be changed manually").drawAt(400, 180);
	FontAsset(U"GridGazer")(U"Press ESC key to return to the title").drawAt(400, 420);

	// OptionButtons配列の中のボタンについて
	for (auto const& button : OptionButtons)
	{
		// ボタンを描画
		button.Draw(U"GridGazer");
	}
}
