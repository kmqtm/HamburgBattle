#pragma once
# include <Siv3D.hpp>

// アセット管理クラス
class AssetControlClass
{
public:
	// アセットの用意
	void AssetPrepare(String scene_name);

	// アセットの登録解除
	void AssetUnregister();

private:
	// JSONファイル読み込み変数
	JSON asset_json;

	// 現在のシーン名
	String now_scene_name;

	// アセットタイプ配列
	const Array<String> type = { U"Font", U"Sound", U"Picture" };

	// アセットタイプの保存用文字列
	String asset_type;

	// アセットファイル名
	String asset_file_name;

	// 拡張子を除くファイル名
	String asset_base_name;

	// アセットのファイルパス
	String asset_filepath;

	// アセットの登録とロード
	void AssetRegisterAndLoad(String asset_type_a);
};
