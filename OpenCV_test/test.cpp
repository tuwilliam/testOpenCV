#include<opencv2\core\core.hpp>  
#include<opencv2\highgui\highgui.hpp>  
#include<opencv2\imgproc\imgproc.hpp>  
using namespace cv;
#include<iostream>  
#include<vector>  
using namespace std;
/*----定义鼠标事件--画矩形区域：作用当两个车灯----*/
//第一步：全局变量  
bool drawing_box = false;
bool gotBox = false;
Rect box;
Point downPoint;
/*
void mouseRectHandler(int event, int x, int y, int flags, void *param)
{
switch (event)
{
case CV_EVENT_MOUSEMOVE:
if (drawing_box)
{
box.width = x - box.x;
box.height = y - box.y;
}
break;
case CV_EVENT_LBUTTONDOWN:
drawing_box = true;
box = Rect(x, y, 0, 0);
break;
case CV_EVENT_LBUTTONUP:
drawing_box = false;
gotBox = true;
if (box.width < 0)
{
box.x += box.width;
box.width *= -1;
}
if( box.height < 0 )
{
box.y += box.height;
box.height *= -1;
}
break;
default:
break;
}
}
*/

void mouseRectHandler(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			//鼠标的移动到downPoint的右下角  
			if (x >= downPoint.x && y >= downPoint.y)
			{
				box.x = downPoint.x;
				box.y = downPoint.y;
				box.width = x - downPoint.x;
				box.height = y - downPoint.y;
			}
			//鼠标的移动到downPoint的右上角  
			if (x >= downPoint.x && y <= downPoint.y)
			{
				box.x = downPoint.x;
				box.y = y;
				box.width = x - downPoint.x;
				box.height = downPoint.y - y;
			}
			//鼠标的移动到downPoint的左上角  
			if (x <= downPoint.x && y <= downPoint.y)
			{
				box.x = x;
				box.y = y;
				box.width = downPoint.x - x;
				box.height = downPoint.y - y;
			}
			//鼠标的移动到downPoint的左下角  
			if (x <= downPoint.x && y >= downPoint.y)
			{
				box.x = x;
				box.y = downPoint.y;
				box.width = downPoint.x - x;
				box.height = y - downPoint.y;
			}
		}
		break;

	case CV_EVENT_LBUTTONDOWN:
		//按下鼠标，代表可以可以开始画矩形  
		drawing_box = true;
		//记录起点  
		downPoint = Point(x, y);
		break;

	case CV_EVENT_LBUTTONUP:

		//松开鼠标，代表结束画矩形  
		drawing_box = false;
		gotBox = true;
		break;
	default:
		break;
	}
}

int main(int argc, char*argv[])
{
	//读取视频    
	VideoCapture video(0);

	//判断视频是否打开    
	if (!video.isOpened())
		return 0;

	//视频帧    
	Mat frame,frameGaussian;

	namedWindow("video", 1);
	namedWindow("video_Gaussian", 1);
	//视频继续    
	for (;;)
	{
		//读取视频   
		video >> frame;
		//判断是否有当前帧  
		if (!frame.data)
			break;
		GaussianBlur(frame, frameGaussian, Size(5, 5), 2, 1);

		imshow("video", frame);
		imshow("video_Gaussian", frameGaussian);

		if (waitKey(33) == 'q')
			break;
	}
	return 0;
}