# include <Siv3D.hpp>
# include "../include/Asset.hpp"
# include "../include/Utility.hpp"
# include "../include/Game.hpp"
# include "../include/Result.hpp"

//#####################################
// リザルトシーン
//#####################################

// リザルトシーン用カウンタ(1フレームで1カウント)
static int32 ResultSceneFrameCount = 0;

// リザルトシーン用ストップウォッチ
static Stopwatch ResultSceneStopwatch;

// 物体ごとの衝突音の再生判定をする
static bool Bump1 = false, Bump2 = false, Bump3 = false;

// ゲームオーバーか判定
static bool IsGameOver = false;

// 背景スクロールの管理
static bool BackScrollControl = true;
static int32 ScrollPosition = 0;
// 背景のスクロール状態を保存
void ReserveScrollPosition(void)
{
	if (BackScrollControl == true)
	{
		ScrollPosition = ResultSceneFrameCount;
	}
}
// 背景画像を描画
void DrawResultBack(String Assetname)
{
	// 背景をスクロール
	if (BackScrollControl == true)
	{
		TextureAsset(Assetname).draw(0, (ResultSceneFrameCount * 10) - 600);
		TextureAsset(Assetname).draw(0, ResultSceneFrameCount * 10);
	}
	// 背景を固定
	else if (BackScrollControl == false)
	{
		TextureAsset(Assetname).draw(0, (ScrollPosition * 10) - 600);
		TextureAsset(Assetname).draw(0, ScrollPosition * 10);
	}
}

// ハンバーグの跳ね返り
static int32 HamburgBounce = 0;
// ハンバーグの跳ね返り計算
void HamburgBounceCalculate(void)
{
	if (IsGameOver == true)
	{
		HamburgBounce += 10;
	}
}
// リザルトシーン用ハンバーグを描画
void DrawResultHamburg(void)
{
	TextureAsset(U"Hamburg").rotatedAt(Vec2{ 100, 50 }, (12_deg * ResultSceneFrameCount)).draw(300, 330 + HamburgBounce);
}

// 出現するべき物体の識別
static int32 ObjectNumberCount = 1;
// リザルト上で出る物体の描画
void DrawObject(void)
{
	// Satellite
	if (ObjectNumberCount == 1 && Bump1 == false)
	{
		// 3000msでy軸300へ到達
		TextureAsset(U"Satellite").draw(300, (ResultSceneStopwatch.msF() / 10) * 3 - 600);
	}
	// Moon
	else if (ObjectNumberCount == 2 && Bump2 == false)
	{
		// 6000msでy軸300へ到達
		TextureAsset(U"Moon").draw(300, (ResultSceneStopwatch.msF() / 10) * 3 - 1500);
	}
	// UFO
	else if (ObjectNumberCount == 3 && Bump3 == false)
	{
		// 9000msでy軸300へ到達
		TextureAsset(U"UFO").draw(300, (ResultSceneStopwatch.msF() / 10) * 3 - 2400);
	}
}

// 出現するべき物体のフラグ管理
void ObjectNumberCountControl(void)
{
	if (ResultSceneStopwatch.msF() > 3000 && GetGameScore() >= 50000)
	{
		ObjectNumberCount = 2;
	}

	if (ResultSceneStopwatch.msF() > 6000 && GetGameScore() >= 100000)
	{
		ObjectNumberCount = 3;
	}
}

// 時間に沿った勝敗の処理
void ResultTimeWinLose(void)
{
	// Satelliteに敗北
	if (IsGameOver == false && ObjectNumberCount == 1 && GetGameScore() < 50000 && ResultSceneStopwatch.msF() > 3000)
	{
		AudioAsset(U"Bounce").setVolume(0.4);
		AudioAsset(U"Bounce").play();
		IsGameOver = true;
	}
	// Moonに敗北
	if (IsGameOver == false && ObjectNumberCount == 2 && GetGameScore() < 100000 && ResultSceneStopwatch.msF() > 6000)
	{
		AudioAsset(U"Bounce").setVolume(0.4);
		AudioAsset(U"Bounce").play();
		IsGameOver = true;
	}
	// UFOに敗北
	if (IsGameOver == false && ObjectNumberCount == 3 && GetGameScore() < 200000 && ResultSceneStopwatch.msF() > 9000)
	{
		AudioAsset(U"Bounce").setVolume(0.4);
		AudioAsset(U"Bounce").play();
		IsGameOver = true;
	}
}

// 時間に沿ったリザルトでの勝利(破壊)音の再生
void ResultTimeWinSound(void)
{
	// Satelliteに勝利
	if (IsGameOver == false && ResultSceneStopwatch.msF() > 3000 && Bump1 == false)
	{
		Bump1 = true;
		AudioAsset(U"SatelliteBump").setVolume(0.5);
		AudioAsset(U"SatelliteBump").play();
	}
	// Moonに勝利
	if (IsGameOver == false && ResultSceneStopwatch.msF() > 6000 && Bump2 == false)
	{
		Bump2 = true;
		AudioAsset(U"MoonBump").setVolume(0.5);
		AudioAsset(U"MoonBump").play();
	}
	// UFOに勝利
	if (IsGameOver == false && ResultSceneStopwatch.msF() > 9000 && Bump3 == false)
	{
		Bump3 = true;
		AudioAsset(U"UFOBump").setVolume(0.5);
		AudioAsset(U"UFOBump").play();
	}
	// 全てに勝利
	if (IsGameOver == false && ObjectNumberCount == 3 && GetGameScore() > 200000 && ResultSceneStopwatch.msF() > 10000)
	{
		AudioAsset(U"Cheers").setVolume(0.4);
		AudioAsset(U"Cheers").play();
		IsGameOver = true;
	}
}

// 変数のリセット
void ResetVariable(void)
{
	Bump1 = false;
	Bump2 = false;
	Bump3 = false;
	HamburgBounce = 0;
	BackScrollControl = true;
	ObjectNumberCount = 1;
	ResetGameScore();
	ResultSceneStopwatch.reset();
	IsGameOver = false;
}

// リザルトシーンのコンストラクタ
Result::Result(const InitData& init)
	: IScene{ init }
{
	ResultAssetLoad();

	ResultSceneStopwatch.start();
};

// リザルトシーンの更新関数
void Result::update()
{
	CountControl(ResultSceneFrameCount);

	ResultTimeWinLose();

	ResultTimeWinSound();

	ObjectNumberCountControl();

	ObjectNumberCountControl();

	ReserveScrollPosition();

	HamburgBounceCalculate();

	PlayGameBGM();

	// ゲームオーバーであれば
	if (IsGameOver == true)
	{
		BackScrollControl = false;

		if (KeyEscape.down())
		{
			// 変数リセット
			ResetVariable();

			AudioAsset(U"GameBGM").stop();
		
			changeScene(SceneState::Title, 0.8s);
		}
	}
}

// リザルトシーンの描画関数
void Result::draw() const
{
	DrawResultBack(U"Universe");

	DrawResultHamburg();

	DrawObject();

	// ゲームオーバーであれば
	if (IsGameOver == true)
	{
		FontAsset(U"ResultText")(U"Score: ", GetGameScore()).drawAt(400, 250);
		FontAsset(U"ResultText")(U"Escキーでタイトルへ戻る").drawAt(400, 350);
	}
}
