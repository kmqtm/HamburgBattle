# include <Siv3D.hpp>
# include "../include/Asset.hpp"
# include "../include/Utility.hpp"
# include "../include/Title.hpp"
# include "../include/Button.hpp"

//#####################################
// タイトルシーン
//#####################################

// ボタンのインスタンス化
static const Button PLAY_GAME(TitleFontSize, U"PLAY GAME", 220.0, 358.0, true);
static const Button OPTION(TitleFontSize, U"OPTION", 450.0, 358.0, false);
static const Button EXIT(TitleFontSize, U"EXIT", 620.0, 358.0, false);
// ボタンインスタンスの配列
static Array<Button> TitleButtons = {PLAY_GAME, OPTION, EXIT};

// アセット管理用クラスのインスタンス化
static AssetControlClass TitleAssetControl;

// 任意のキー入力が無い場合の追加処理
void TitleAnyKeyInput(bool* ANY_KEY)
{
	// キーによる何らかの入力があることを判定する
	const Array<Input> keys = Keyboard::GetAllInputs();

	// 任意のキーが押されたら(つまりkeys配列が空ではない)
	if (keys.begin() != keys.end() && *ANY_KEY == false)
	{
		// 任意のキーが押された判定をtrueに変更
		*ANY_KEY = true;
		// 任意のキーの入力音(音量0.4倍)
		AudioAsset(U"AnyKeyPressed").setVolume(0.4);
		AudioAsset(U"AnyKeyPressed").play();
	}
}

// タイトルBGM停止
void StopTitleBGM(void)
{
	AudioAsset(U"Grilling").stop();
}

// タイトルシーンのコンストラクタ
Title::Title(const InitData& init)
	: IScene{ init }
{
	// タイトルシーンアセットの準備
	TitleAssetControl.AssetPrepare(U"Title");

	// 任意のキーが押されていない状態で初期化
	ANY_KEY = false;
}


// タイトルシーンのデコンストラクタ
Title::~Title()
{
	// アセットの登録解除
	TitleAssetControl.AssetUnregister();
}


// タイトルシーン更新関数
void Title::update()
{
	// タイトルBGMが再生されていないなら
	if (not AudioAsset(U"Grilling").isPlaying())
	{
		// タイトルBGMの再生(音量0.1倍)
		AudioAsset(U"Grilling").setVolume(0.1);
		AudioAsset(U"Grilling").play();
	}

	// 任意のキー入力が無ければ
	if (ANY_KEY == false)
	{
		TitleAnyKeyInput(&ANY_KEY);
	}

	// 決定キーを押したときの処理
	// 決定キーの入力
	else if (KeyZ.down())
	{
		// PLAY GAME
		if (TitleButtons.at(0).ButtonSelected == true)
		{
			// ゲーム開始音
			AudioAsset(U"Start").setVolume(0.5);
			AudioAsset(U"Start").play();
			// タイトルBGM停止
			StopTitleBGM();

			// 遊び方説明シーンに遷移
			changeScene(SceneState::HowToPlay, 0.8s);
		}
		// OPTION
		else if (TitleButtons.at(1).ButtonSelected == true)
		{
			// ゲーム開始音
			AudioAsset(U"Start").setVolume(0.5);
			AudioAsset(U"Start").play();
			// タイトルBGM停止
			StopTitleBGM();

			// オプションシーンに遷移
			changeScene(SceneState::Option, 0.8s);
		}
		// EXIT
		else if (TitleButtons.at(2).ButtonSelected == true)
		{
			// キャンセル音
			AudioAsset(U"Cancel").setVolume(0.5);
			AudioAsset(U"Cancel").play();
			while (AudioAsset(U"Cancel").isPlaying()) {}

			// 終了シーンに遷移
			changeScene(SceneState::Exit, 0.1s);
		}
	}

	// 左矢印の入力
	else if (KeyLeft.down())
	{
		ButtonSelectLeft(TitleButtons);
	}
	// 右矢印の入力
	else if (KeyRight.down())
	{
		ButtonSelectRight(TitleButtons);
	}
}

// タイトルシーン描画関数
void Title::draw() const
{
	// タイトル画面の画像を描画
	TextureAsset(U"TitlePicture").draw();

	// 任意のキーが押されていない
	if (ANY_KEY == false)
	{
		// 1/2秒間間隔
		if (Periodic::Square0_1(1s))
		{
			// タイトル画面でPRESS SPACE KEYを表示
			FontAsset(U"GridGazer")(U"PRESS ANY KEY").drawAt(400, 358);
		}
	}
	// 任意のキーが押された
	else if (ANY_KEY == true)
	{
		// TitleButtons配列の中のボタンについて
		for (auto const& button : TitleButtons)
		{
			// ボタンを描画
			button.Draw(U"GridGazer");
		}
	}
}
