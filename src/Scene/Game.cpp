# include <Siv3D.hpp>
# include "../include/Asset.hpp"
# include "../include/Utility.hpp"
# include "../include/Game.hpp"

//#####################################
// ゲームシーン
//#####################################

// アセット管理用クラスのインスタンス化
static AssetControlClass GameAssetControl;

// ゲームシーン用カウンタ(1フレームで1カウント)
static int32 GameSceneFrameCount = 0;

// アニメーション用変数
static bool AnimeControl = false;
static Stopwatch AnimeTime;

// ゲージレベルを保存
static int32 GageLevel = 0;

// 何回ゲージを止めたかのかをカウント
static int32 GagePressCount = 0;

// ゲームスコア(ボタン押下時のゲージレベルの乗算)
static int32 GameScore = 1;
int32 GetGameScore(void)
{
	return GameScore;
}
void ResetGameScore(void)
{
	GameScore = 1;
}

// ゲームBGMを再生
void PlayGameBGM(void)
{
	// ゲームBGMが再生されていないなら
	if (not AudioAsset(U"GameBGM").isPlaying())
	{
		// ゲームBGMの再生(音量0.1倍)
		AudioAsset(U"GameBGM").setVolume(0.1);
		AudioAsset(U"GameBGM").play();
		AudioAsset(U"GameBGM").seekTime(0.1);
	}
}

// ゲージを描画
void DrawGage(void)
{
	if (AnimeControl == true)
	{
		if (GageLevel != 60)
		{
			Rect{ 250 + 5, 410, ((290 * GageLevel) / (FPS - 1)), 180 }.draw(Palette::Red);
		}
		else
		{
			Rect{ 250 + 5, 410, ((290 * GageLevel) / (FPS - 1)), 180 }.draw(Palette::Yellow);
		}
	}
	else if (AnimeControl == false)
	{
		if (GameSceneFrameCount != 60)
		{
			// 6 ~ 300 - 4
			// 左上の基準点, 幅, 高さ
			Rect{ 250 + 5, 410, ((290 * GameSceneFrameCount) / (FPS - 1)), 180 }.draw(Palette::Red);
		}
		else
		{
			Rect{ 250 + 5, 410, ((290 * GameSceneFrameCount) / (FPS - 1)), 180 }.draw(Palette::Yellow);
		}
	}
	TextureAsset(U"GageFront").draw(0, 350);
}

// 背景を描画
void DrawGameBack(void)
{
	TextureAsset(U"GameBack").draw();
}

// 炎を描画
void DrawFire(void)
{
	// 2枚の画像の炎アニメーション
	if (GameSceneFrameCount % 10 < 5)
	{
		TextureAsset(U"Fire1").draw();
	}
	else if (GameSceneFrameCount % 10 >= 5)
	{
		TextureAsset(U"Fire2").draw();
	}
}

// 腕&フライパンを描画
void DrawArmAndPan(void)
{
	if (AnimeControl == true)
	{
		TextureAsset(U"Cook").rotatedAt(Vec2{ 800, 100 }, ((10_deg * AnimeTime.msF() / 10) / (FPS - 1))).draw(30, -40);
	}
	else if (AnimeControl == false)
	{
		TextureAsset(U"Cook").rotatedAt(Vec2{ 800, 100 }, ((2_deg * GameSceneFrameCount) / (FPS - 1))).draw(30, -40);
	}
}

// ハンバーグを描画
void DrawHamburg(void)
{
	if (AnimeControl == true)
	{
		if (GagePressCount < 3)
		{
			TextureAsset(U"Hamburg").rotatedAt(Vec2{ 100, 50 }, ((GageLevel * 7_deg * AnimeTime.msF() / 10) / (FPS - 1))).draw(300, 200 - AnimeTime.msF() / 5);
		}
		else
		{
			TextureAsset(U"Hamburg").rotatedAt(Vec2{ 100, 50 }, ((GageLevel * 7_deg * AnimeTime.msF() / 10) / (FPS - 1))).draw(300, 200 - AnimeTime.msF());
		}
		
	}
	else if (AnimeControl == false)
	{
		TextureAsset(U"Hamburg").rotatedAt(Vec2{ 100, 50 }, ((4_deg * GameSceneFrameCount) / (FPS - 1))).draw(300, 200 - GameSceneFrameCount);
	}
}

// アニメーションに用いるストップウォッチとブール値の管理
void AnimeTimeControl(void)
{
	if (AnimeTime.msF() >= 1000)
	{
		AnimeTime.reset();
		AnimeControl = false;
	}
}

// ゲージレベルの管理
void GageLevelControl(void)
{
	// ボタン押下前にのみ保存
	if (AnimeControl == false)
	{
		GageLevel = GameSceneFrameCount;
	}
}

// ゲージ押下回数の描画
void DrawGagePressCount()
{
	// 左上の基準点, 幅, 高さ
	Rect{ 50, 470, 38 * GagePressCount, 38 }.draw(Palette::Lightgreen);
}

// ゲームシーンのコンストラクタ
Game::Game(const InitData& init)
	: IScene{ init }
{
	// ゲームシーンアセットの準備
	GameAssetControl.AssetPrepare(U"Game");
}

// ゲームシーンのデコンストラクタ
Game::~Game()
{
	// アセットの登録解除
	GameAssetControl.AssetUnregister();
}

// ゲームシーンの更新関数
void Game::update()
{
	// フレームをカウント
	CountControl(GameSceneFrameCount);

	// ゲージレベルを管理
	GageLevelControl();

	// アニメーション時間の管理
	AnimeTimeControl();

	// BGMの再生
	PlayGameBGM();

	// ゲームがZキーで進行するとき
	if (KeyZ.down() && AnimeControl == false)
	{
		GagePressCount++;
		GameSceneFrameCount = 1;
		GameScore *= (GageLevel + 1);

		AudioAsset(U"GameZPressed").setVolume(0.4);
		AudioAsset(U"GameZPressed").play();

		AnimeControl = true;
		AnimeTime.start();
	}

	if (GagePressCount >= 3 && AnimeControl == false)
	{
		GagePressCount = 0;
		GameSceneFrameCount = 0;
		changeScene(SceneState::Result, 0.2s);
	}
}

// ゲームシーンの描画関数
void Game::draw() const
{
	// 背景描画
	DrawGameBack();

	// 炎を描画
	DrawFire();

	// ゲージ押下回数の描画
	DrawGagePressCount();

	// ゲージを描画
	DrawGage();

	// ハンバーグを描画
	DrawHamburg();

	// 腕とフライパンを描画
	DrawArmAndPan();
}
