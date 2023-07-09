#pragma once
# include <Siv3D.hpp>

// ボタンクラス
class Button
{
public:
	// ボタンが選択されているか判定
	bool ButtonSelected;

	// ボタンクラスのコンストラクタ
	Button(int32 FontSize, String DisplayName, double X, double Y, bool IsSelected);

	// ボタンの描画
	void Draw(String Asset) const;
	
private:
	// ボタンの描画座標
	Vec2 ButtonPosition;
	// ボタンの表示名
	String ButtonDisplayName;
	// ボタンのフォントサイズ
	int32 ButtonFontSize;
};

// ボタンが左右に並ぶ時の矢印キーによる選択の処理
// 左矢印キーが入力されたとき
void ButtonSelectLeft(Array<Button>& Buttons);

// 右矢印キーが入力されたとき
void ButtonSelectRight(Array<Button>& Buttons);
