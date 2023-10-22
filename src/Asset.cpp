# include <Siv3D.hpp>
# include "include/Asset.hpp"
# include "include/Title.hpp"
# include "include/Option.hpp"
# include "include/Game.hpp"
# include "include/Result.hpp"


// アセットの用意
void AssetControlClass::AssetPrepare(String scene_name)
{
	// アセット情報のJSONを読み込む
	asset_json = JSON::Load( U"resources/Control/AssetControl.json" );

	now_scene_name = scene_name;

	// アセットのタイプごとに処理
	for (int i = 0; i < 3; i++)
	{
		// アセットタイプを保存
		asset_type = type[i];

		// アセットファイル名を1つずつ取得
		for ( const auto& file_name : asset_json[now_scene_name][asset_type].arrayView() )
		{
			asset_file_name = file_name.getString();

			// アセットが無ければ
			if (asset_file_name == U"null")
			{
				break;
			}

			// アセットのファイルパスを文字列で形成
			asset_filepath = U"resources/" + asset_type + U"/" + asset_file_name;

			// タイプ別のフォルダ内に対象のアセットファイルがあるなら
			if (FileSystem::Exists(asset_filepath))
			{
				// アセットの登録とロード
				AssetRegisterAndLoad(asset_type);
			}
		}
	}
}


// アセットの登録とロード
void AssetControlClass::AssetRegisterAndLoad(String asset_type_a)
{
	// 拡張子を除くファイル名
	asset_base_name = FileSystem::BaseName(asset_filepath);

	// タイプ別で処理
	// Font
	if (asset_type_a == U"Font")
	{
		// フォントサイズの取得
		int32 font_size = asset_json[now_scene_name][U"FontSize"].get<int32>();

		// フォントアセットの登録
		FontAsset::Register(asset_base_name, font_size, asset_filepath);
		// フォントアセットのロード
		FontAsset::Load(asset_base_name);
	}
	else if (asset_type_a == U"Sound")
	{
		// オーディオアセットの登録
		AudioAsset::Register(asset_base_name, asset_filepath);
		// オーディオアセットのロード
		AudioAsset::Load(asset_base_name);
	}
	else if (asset_type_a == U"Picture")
	{
		// テクスチャアセットの登録
		TextureAsset::Register(asset_base_name, asset_filepath);
		// テクスチャアセットのロード
		TextureAsset::Load(asset_base_name);
	}
}


// アセットの登録解除
void AssetControlClass::AssetUnregister()
{
	// アセットのタイプごとに処理
	for (int i = 0; i < 3; i++)
	{
		// アセットタイプを保存
		asset_type = type[i];

		// アセットファイル名を1つずつ取得
		for (const auto& file_name : asset_json[now_scene_name][asset_type].arrayView())
		{
			// ファイル名の取得
			asset_file_name = file_name.getString();
			// 拡張子を除くファイル名
			asset_base_name = FileSystem::BaseName(asset_file_name);

			// アセットが無ければ
			if (asset_file_name == U"null")
			{
				break;
			}

			if (asset_type == U"Font")
			{
				// フォントアセットの登録解除
				FontAsset::Unregister(asset_base_name);
			}
			else if (asset_type == U"Sound")
			{
				// オーディオアセットの登録解除
				AudioAsset::Unregister(asset_base_name);
			}
			else if (asset_type == U"Picture")
			{
				// オーディオアセットの登録解除
				TextureAsset::Unregister(asset_base_name);
			}
		}
	}
}
