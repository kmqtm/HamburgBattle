# include <Siv3D.hpp>
# include "../include/Asset.hpp"
# include "../include/Utility.hpp"
# include "../include/Game.hpp"

//#####################################
// ゲームシーン
//#####################################

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
	TextureAsset(U"GageBack").draw(251,351);

	if (AnimeControl == true)
	{
		Rect{ 251 + 5, 351, ((291 * GageLevel) / (FPS - 1)), 200 }.draw(Palette::Red);
	}
	else if (AnimeControl == false)
	{
		// 6 ~ 300 - 4
		// 左上の基準点, 幅, 高さ
		Rect{ 251 + 5, 351, ((291 * GameSceneFrameCount) / (FPS - 1)), 200 }.draw(Palette::Red);
	}
	TextureAsset(U"GageFront").draw(251, 351);
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
	if (AnimeTime.msF() > 1000)
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

// ゲームシーンのコンストラクタ
Game::Game(const InitData& init)
	: IScene{ init }
{
	// ゲームシーン用アセットを登録
	GameAssetLoad();
}

// ゲームシーンの更新関数
void Game::update()
{
	CountControl(GameSceneFrameCount);

	GageLevelControl();

	AnimeTimeControl();

	PlayGameBGM();

	// ゲームがZキーで進行するとき
	if (KeyZ.down() && AnimeControl == false)
	{
		GagePressCount++;
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
	DrawGameBack();

	DrawGage();

	DrawFire();

	DrawHamburg();

	DrawArmAndPan();
}
