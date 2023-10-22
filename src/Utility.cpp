# include <Siv3D.hpp>
# include "include/Utility.hpp"


// 1フレームで1カウント
void CountControl(int32& Count)
{
	Count++;
	if (Count > 60)
	{
		Count = 0;
	}
}
