

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;


//----------------------------------【ROI_AddImage( )函数】----------------------------------
// 函数名：ROI_AddImage（）
//     描述：利用感兴趣区域ROI实现图像叠加
//----------------------------------------------------------------------------------------------
bool ROI_AddImage()
{

	//【1】读入图像
	Mat srcImage1 = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage1.data) { printf("你妹，读取srcImage1错误~！ \n"); return false; }
	if (!logoImage.data) { printf("你妹，读取logoImage错误~！ \n"); return false; }

	//【2】定义一个Mat类型并给其设定ROI区域
	Mat imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));

	//【3】加载掩模（必须是灰度图）
	Mat mask = imread("dota_logo.jpg", 0);

	//【4】将掩膜拷贝到ROI
	logoImage.copyTo(imageROI, mask);

	//【5】显示结果
	namedWindow("<1>利用ROI实现图像叠加示例窗口");
	imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);

	return true;
}

//---------------------------------【LinearBlending（）函数】-------------------------------------
// 函数名：LinearBlending（）
// 描述：利用cv::addWeighted（）函数实现图像线性混合
//--------------------------------------------------------------------------------------------
bool LinearBlending()
{
	//【0】定义一些局部变量
	double alphaValue = 0.8;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	//【1】读取图像 ( 两幅图片需为同样的类型和尺寸 )
	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");

	if (!srcImage2.data) { printf("你妹，读取srcImage2错误~！ \n"); return false; }
	if (!srcImage3.data) { printf("你妹，读取srcImage3错误~！ \n"); return false; }

	//【2】做图像混合加权操作
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	//【3】创建并显示原图窗口
	namedWindow("<2>线性混合示例窗口【原图】 by浅墨", 1);
	imshow("<2>线性混合示例窗口【原图】 by浅墨", srcImage2);

	namedWindow("<3>线性混合示例窗口【效果图】 by浅墨", 1);
	imshow("<3>线性混合示例窗口【效果图】 by浅墨", dstImage);

	return true;

}


bool ROI_LinearBlending()
{

	//【1】读取图像
	Mat srcImage4 = imread("dota_pa.jpg", 1);
	Mat logoImage = imread("dota_logo.jpg");

	if (!srcImage4.data) { printf("你妹，读取srcImage4错误~！ \n"); return false; }
	if (!logoImage.data) { printf("你妹，读取logoImage错误~！ \n"); return false; }

	//【2】定义一个Mat类型并给其设定ROI区域
	Mat imageROI;
	//方法一
	imageROI = srcImage4(Rect(200, 250, logoImage.cols, logoImage.rows));
	//方法二
	//imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

	//【3】将logo加到原图上
	addWeighted(imageROI, 0.1, logoImage, 0.9, 0., imageROI);

	//【4】显示结果
	namedWindow("<4>区域线性图像混合示例窗口 by浅墨");
	imshow("<4>区域线性图像混合示例窗口 by浅墨", srcImage4);

	return true;
}


bool MultiChannelBlending()
{
	//【0】定义相关变量
	Mat srcImage;
	Mat logoImage;
	vector<Mat>channels;
	Mat  imageBlueChannel;

	//=================【蓝色通道部分】=================
	//     描述：多通道混合-蓝色分量部分
	//============================================

	//【1】读入图片
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
	if (!srcImage.data) { printf("Oh，no，读取srcImage错误~！\n"); return false; }

	//【2】把一个3通道图像转换成3个单通道图像
	split(srcImage, channels);//分离色彩通道

	//【3】将原图的蓝色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageBlueChannel = channels.at(0);
	//【4】将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//【5】将三个单通道重新合并成一个三通道
	merge(channels, srcImage);

	//【6】显示效果图
	namedWindow("<1>游戏原画+logo蓝色通道 by浅墨");
	imshow("<1>游戏原画+logo蓝色通道 by浅墨", srcImage);


	//=================【绿色通道部分】=================
	//     描述：多通道混合-绿色分量部分
	//============================================

	//【0】定义相关变量
	Mat  imageGreenChannel;

	//【1】重新读入图片
	logoImage = imread("mogu.jpg", 0);
	srcImage = imread("pic.jpg");

	if (!logoImage.data) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
	if (!srcImage.data) { printf("Oh，no，读取srcImage错误~！\n"); return false; }

	//【2】将一个三通道图像转换成三个单通道图像
	split(srcImage, channels);//分离色彩通道

	//【3】将原图的绿色通道的引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageGreenChannel = channels.at(1);
	//【4】将原图的绿色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageGreenChannel中
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//【5】将三个独立的单通道重新合并成一个三通道
	merge(channels, srcImage);

	//【6】显示效果图
	namedWindow("<2>游戏原画+logo绿色通道 by浅墨");
	imshow("<2>游戏原画+logo绿色通道 by浅墨", srcImage);



	//=================【红色通道部分】=================
	//     描述：多通道混合-红色分量部分
	//============================================

	//【0】定义相关变量
	Mat  imageRedChannel;

	//【1】重新读入图片
	logoImage = imread("mogu.jpg", 0);
	srcImage = imread("pic.jpg");

	if (!logoImage.data) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
	if (!srcImage.data) { printf("Oh，no，读取srcImage错误~！\n"); return false; }

	//【2】将一个三通道图像转换成三个单通道图像
	split(srcImage, channels);//分离色彩通道

	//【3】将原图的红色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	imageRedChannel = channels.at(2);
	//【4】将原图的红色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageRedChannel中
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//【5】将三个独立的单通道重新合并成一个三通道
	merge(channels, srcImage);

	//【6】显示效果图
	namedWindow("<3>游戏原画+logo红色通道 by浅墨");
	imshow("<3>游戏原画+logo红色通道 by浅墨", srcImage);

	return true;
}


int main()
{
	MultiChannelBlending();


#if 0
	Mat girl = imread("girl.jpg"); //载入图像到Mat
	namedWindow("girl"); //创建一个名为 "【1】动漫图"的窗口 
	imshow("girl", girl);//显示名为 "【1】动漫图"的窗口 

	//载入图片
	Mat data = imread("data.jpg");
	namedWindow("data");
	imshow("data", data);


	Mat logo = imread("logo.jpg");
	namedWindow("logo");
	imshow("logo", logo);

	//定义一个Mat类型，用于存放，图像的ROI
	Mat imageROI;
	//方法一
	imageROI = data(Rect(280,500,  logo.cols, logo.rows));

	//方法二
	//imageROI = data(Range(350, 350 + logo.rows), Range(800, 800 + logo.cols));

	//将logo加到原图上
	//addWeighted(imageROI, 0.7, logo, 0.3, 1, imageROI);
	addWeighted(imageROI, 0.7, logo, 0.3, 1, imageROI);

	//显示结果
	namedWindow("【4】原画+logo图");
	imshow("【4】原画+logo图", image);

	//-----------------------------------【三、图像的输出】--------------------------------------
	//     描述：将一个Mat图像输出到图像文件
	//-----------------------------------------------------------------------------------------------
	//输出一张jpg图片到工程目录下
	imwrite("我喜欢打dota2 by浅墨.jpg", image);
#endif 
	waitKey();

	return 0;
}
