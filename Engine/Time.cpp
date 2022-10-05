#include "Time.h"
#include "Direct3D.h"

void Time::TimeDraw(int x, int y)
{
	if (Direct3D::GetStatus() == 0)
	{
		//trueなら
		if (Timeflag_)
		{
			time_ += 000.016; //60Fpsだから約毎フレーム0.016
			char buf[12];
			snprintf(buf, 12, "Time:%.2f", time_);

			//値を表示
			text_->Draw(x, y, buf,3);
		}
		else
		{
			//falseならこれを表示
			text_->Draw(x, y, "Time:0.00",3);
		}
	}
}
