# include <Siv3D.hpp>
# include "include/Asset.hpp"
# include "include/Title.hpp"
# include "include/Option.hpp"
# include "include/Game.hpp"
# include "include/Result.hpp"

// 共通アセットの登録
void CommonAssetLoad(void)
{
	// 音
	AudioAsset::Register(U"Oops", U"resources/Sound/Effect/back.wav");
	AudioAsset::Register(U"AnyKeyPressed", U"resources/Sound/Effect/any_key_pressed.mp3");
	AudioAsset::Register(U"Select", U"resources/Sound/Effect/select.wav");
	AudioAsset::Register(U"Cancel", U"resources/Sound/Effect/cancel.mp3");
	AudioAsset::Register(U"Start", U"resources/Sound/Effect/game_start.mp3");
	AudioAsset::Register(U"Decide", U"resources/Sound/Effect/decide.mp3");
	// 画像
	TextureAsset::Register(U"Hamburg", U"resources/Picture/hamburg.png");
}

// タイトルシーン用アセットの登録
void TitleAssetLoad(void)
{
	// フォント
	FontAsset::Register(U"TitleText", TitleFontSize, U"resources/Font/rounded-mplus-2c-thin.ttf");
	// 音
	AudioAsset::Register(U"Grilling", U"resources/Sound/BGM/grilling.mp3");
	// 画像
	TextureAsset::Register(U"TitlePicture", U"resources/Picture/title(hamburg_battle).png");
}

// オプションシーン用アセットの登録
void OptionAssetLoad(void)
{
	// フォント
	FontAsset::Register(U"OptionText", OptionFontSize, U"resources/Font/rounded-mplus-2c-thin.ttf");
}

// 遊び方説明シーン用アセットの登録
void HowToPlayAssetLoad(void)
{
	// 画像
	TextureAsset::Register(U"HowToPlay", U"resources/Picture/HowToPlay.png");
}

// ゲームシーン用アセットの登録
void GameAssetLoad(void)
{
	// 音
	AudioAsset::Register(U"GameBGM", U"resources/Sound/BGM/ryunomai.mp3");
	AudioAsset::Register(U"GameZPressed", U"resources/Sound/Effect/game_scene_z_pressed.mp3");
	// 画像
	TextureAsset::Register(U"GameBack", U"resources/Picture/Game_Back.png");
	TextureAsset::Register(U"Cook", U"resources/Picture/cook.png");
	TextureAsset::Register(U"Fire1", U"resources/Picture/fire_1.png");
	TextureAsset::Register(U"Fire2", U"resources/Picture/fire_2.png");
	TextureAsset::Register(U"GageBack", U"resources/Picture/gage_back.png");
	TextureAsset::Register(U"GageFront", U"resources/Picture/gage_front.png");
}

// リザルトシーン用アセットの登録
void ResultAssetLoad(void)
{
	// フォント
	FontAsset::Register(U"ResultText", ResultFontSize, U"resources/Font/rounded-mplus-2c-thin.ttf");
	// 音
	AudioAsset::Register(U"SatelliteBump", U"resources/Sound/Effect/satellite_bump.mp3");
	AudioAsset::Register(U"MoonBump", U"resources/Sound/Effect/moon_bump.mp3");
	AudioAsset::Register(U"UFOBump", U"resources/Sound/Effect/ufo_bump.mp3");
	AudioAsset::Register(U"Bounce", U"resources/Sound/Effect/bounce.mp3");
	AudioAsset::Register(U"Cheers", U"resources/Sound/Effect/cheers.mp3");
	// 画像
	TextureAsset::Register(U"Universe", U"resources/Picture/universe.png");
	TextureAsset::Register(U"Satellite", U"resources/Picture/satellite.png");
	TextureAsset::Register(U"Moon", U"resources/Picture/moon.png");
	TextureAsset::Register(U"UFO", U"resources/Picture/ufo.png");
}
