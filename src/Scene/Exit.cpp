# include <Siv3D.hpp>
# include "../include/Asset.hpp"
# include "../include/Utility.hpp"
# include "../include/Exit.hpp"

//#####################################
// 終了シーン
//#####################################

// 終了シーンのコンストラクタ
Exit::Exit(const InitData& init)
	: IScene{ init }
{
}

// 終了シーンの更新関数
void Exit::update()
{
	// 終了
	System::Exit();
}

void Exit::draw() const
{
}
