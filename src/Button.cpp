# include <Siv3D.hpp>
# include "include/Button.hpp"

// ボタンクラスのコンストラクタ
Button::Button(int32 FontSize, String DisplayName, double X, double Y, bool IsSelected)
{
	// ボタンの表示名を代入
	ButtonDisplayName = DisplayName;
	// ボタンの中心座標を代入
	ButtonPosition = Vec2{ X, Y };
	// ボタンの選択判定を代入
	ButtonSelected = IsSelected;
	// ボタンのフォントサイズを代入
	ButtonFontSize = FontSize;
}

// ボタンを描画する
void Button::Draw(String Asset) const
{
	// ボタンの表示名を座標上に描画
	FontAsset(Asset)(ButtonDisplayName).drawAt(ButtonPosition.x, ButtonPosition.y);

	// ボタンが選択されているなら
	if (ButtonSelected == true)
	{
		// 左上の基準点，幅，高さから成る長方形の外側に2pxの幅の線で枠を描く(縦横に5px余裕を持たせる)
		Rect{ (int32)ButtonPosition.x - ((int32)(ButtonFontSize / 1.5) * ButtonDisplayName.size()) / 2,
				(int32)ButtonPosition.y - (ButtonFontSize / 2),
				((int32)(ButtonFontSize / 1.5) * ButtonDisplayName.size()),
				ButtonFontSize }
		.drawFrame(0, 2);
	}
}

// ボタンが左右に並ぶ時の矢印キーによる選択の処理
// 左矢印キーが入力されたとき
void ButtonSelectLeft(Array<Button>& Buttons)
{
	// Buttonsから選択されているボタンを探す
	for (int32 i = 1; i < Buttons.size(); i++)
	{
		// ボタンが選択されていれば
		if (Buttons.at(i).ButtonSelected == true)
		{
			// 配列で一つ前のボタンを選択状態にする
			Buttons.at((size_t)i - 1).ButtonSelected = true;
			// 現在選択しているボタンを非選択状態にする
			Buttons.at(i).ButtonSelected = false;

			// ボタンカーソル移動音
			AudioAsset(U"Select").setVolume(0.3);
			AudioAsset(U"Select").play();

			return;
		}
	}

	// 選択中のボタンが左端でカーソル移動しない場合
	AudioAsset(U"Oops").setVolume(0.5);
	AudioAsset(U"Oops").play();

	return;
}

// 右矢印キーが入力されたとき
void ButtonSelectRight(Array<Button>& Buttons)
{
	// Buttonsから選択されているボタンを探す
	for (int32 i = 0; i < Buttons.size() - 1; i++)
	{
		// ボタンが選択されていれば
		if (Buttons.at(i).ButtonSelected == true)
		{
			// 配列で一つ後のボタンを選択状態にする
			Buttons.at((size_t)i + 1).ButtonSelected = true;
			// 現在選択しているボタンを非選択状態にする
			Buttons.at(i).ButtonSelected = false;

			// ボタンカーソル移動音
			AudioAsset(U"Select").setVolume(0.3);
			AudioAsset(U"Select").play();

			return;
		}
	}

	// 選択中のボタンが右端でカーソル移動しない場合
	AudioAsset(U"Oops").setVolume(0.5);
	AudioAsset(U"Oops").play();

	return;
}
