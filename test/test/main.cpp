

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;


//----------------------------------��ROI_AddImage( )������----------------------------------
// ��������ROI_AddImage����
//     ���������ø���Ȥ����ROIʵ��ͼ�����
//----------------------------------------------------------------------------------------------
bool ROI_AddImage()
{

	//��1������ͼ��
	Mat srcImage1 = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage1.data) { printf("���ã���ȡsrcImage1����~�� \n"); return false; }
	if (!logoImage.data) { printf("���ã���ȡlogoImage����~�� \n"); return false; }

	//��2������һ��Mat���Ͳ������趨ROI����
	Mat imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));

	//��3��������ģ�������ǻҶ�ͼ��
	Mat mask = imread("dota_logo.jpg", 0);

	//��4������Ĥ������ROI
	logoImage.copyTo(imageROI, mask);

	//��5����ʾ���
	namedWindow("<1>����ROIʵ��ͼ�����ʾ������");
	imshow("<1>����ROIʵ��ͼ�����ʾ������", srcImage1);

	return true;
}

//---------------------------------��LinearBlending����������-------------------------------------
// ��������LinearBlending����
// ����������cv::addWeighted��������ʵ��ͼ�����Ի��
//--------------------------------------------------------------------------------------------
bool LinearBlending()
{
	//��0������һЩ�ֲ�����
	double alphaValue = 0.8;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	//��1����ȡͼ�� ( ����ͼƬ��Ϊͬ�������ͺͳߴ� )
	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");

	if (!srcImage2.data) { printf("���ã���ȡsrcImage2����~�� \n"); return false; }
	if (!srcImage3.data) { printf("���ã���ȡsrcImage3����~�� \n"); return false; }

	//��2����ͼ���ϼ�Ȩ����
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	//��3����������ʾԭͼ����
	namedWindow("<2>���Ի��ʾ�����ڡ�ԭͼ�� byǳī", 1);
	imshow("<2>���Ի��ʾ�����ڡ�ԭͼ�� byǳī", srcImage2);

	namedWindow("<3>���Ի��ʾ�����ڡ�Ч��ͼ�� byǳī", 1);
	imshow("<3>���Ի��ʾ�����ڡ�Ч��ͼ�� byǳī", dstImage);

	return true;

}


bool ROI_LinearBlending()
{

	//��1����ȡͼ��
	Mat srcImage4 = imread("dota_pa.jpg", 1);
	Mat logoImage = imread("dota_logo.jpg");

	if (!srcImage4.data) { printf("���ã���ȡsrcImage4����~�� \n"); return false; }
	if (!logoImage.data) { printf("���ã���ȡlogoImage����~�� \n"); return false; }

	//��2������һ��Mat���Ͳ������趨ROI����
	Mat imageROI;
	//����һ
	imageROI = srcImage4(Rect(200, 250, logoImage.cols, logoImage.rows));
	//������
	//imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

	//��3����logo�ӵ�ԭͼ��
	addWeighted(imageROI, 0.1, logoImage, 0.9, 0., imageROI);

	//��4����ʾ���
	namedWindow("<4>��������ͼ����ʾ������ byǳī");
	imshow("<4>��������ͼ����ʾ������ byǳī", srcImage4);

	return true;
}


bool MultiChannelBlending()
{
	//��0��������ر���
	Mat srcImage;
	Mat logoImage;
	vector<Mat>channels;
	Mat  imageBlueChannel;

	//=================����ɫͨ�����֡�=================
	//     ��������ͨ�����-��ɫ��������
	//============================================

	//��1������ͼƬ
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) { printf("Oh��no����ȡlogoImage����~��\n"); return false; }
	if (!srcImage.data) { printf("Oh��no����ȡsrcImage����~��\n"); return false; }

	//��2����һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	split(srcImage, channels);//����ɫ��ͨ��

	//��3����ԭͼ����ɫͨ�����÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageBlueChannel = channels.at(0);
	//��4����ԭͼ����ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageBlueChannel��
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//��5����������ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	//��6����ʾЧ��ͼ
	namedWindow("<1>��Ϸԭ��+logo��ɫͨ�� byǳī");
	imshow("<1>��Ϸԭ��+logo��ɫͨ�� byǳī", srcImage);


	//=================����ɫͨ�����֡�=================
	//     ��������ͨ�����-��ɫ��������
	//============================================

	//��0��������ر���
	Mat  imageGreenChannel;

	//��1�����¶���ͼƬ
	logoImage = imread("mogu.jpg", 0);
	srcImage = imread("pic.jpg");

	if (!logoImage.data) { printf("Oh��no����ȡlogoImage����~��\n"); return false; }
	if (!srcImage.data) { printf("Oh��no����ȡsrcImage����~��\n"); return false; }

	//��2����һ����ͨ��ͼ��ת����������ͨ��ͼ��
	split(srcImage, channels);//����ɫ��ͨ��

	//��3����ԭͼ����ɫͨ�������÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageGreenChannel = channels.at(1);
	//��4����ԭͼ����ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageGreenChannel��
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//��5�������������ĵ�ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	//��6����ʾЧ��ͼ
	namedWindow("<2>��Ϸԭ��+logo��ɫͨ�� byǳī");
	imshow("<2>��Ϸԭ��+logo��ɫͨ�� byǳī", srcImage);



	//=================����ɫͨ�����֡�=================
	//     ��������ͨ�����-��ɫ��������
	//============================================

	//��0��������ر���
	Mat  imageRedChannel;

	//��1�����¶���ͼƬ
	logoImage = imread("mogu.jpg", 0);
	srcImage = imread("pic.jpg");

	if (!logoImage.data) { printf("Oh��no����ȡlogoImage����~��\n"); return false; }
	if (!srcImage.data) { printf("Oh��no����ȡsrcImage����~��\n"); return false; }

	//��2����һ����ͨ��ͼ��ת����������ͨ��ͼ��
	split(srcImage, channels);//����ɫ��ͨ��

	//��3����ԭͼ�ĺ�ɫͨ�����÷��ظ�imageBlueChannel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	imageRedChannel = channels.at(2);
	//��4����ԭͼ�ĺ�ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageRedChannel��
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	//��5�������������ĵ�ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	//��6����ʾЧ��ͼ
	namedWindow("<3>��Ϸԭ��+logo��ɫͨ�� byǳī");
	imshow("<3>��Ϸԭ��+logo��ɫͨ�� byǳī", srcImage);

	return true;
}


int main()
{
	MultiChannelBlending();


#if 0
	Mat girl = imread("girl.jpg"); //����ͼ��Mat
	namedWindow("girl"); //����һ����Ϊ "��1������ͼ"�Ĵ��� 
	imshow("girl", girl);//��ʾ��Ϊ "��1������ͼ"�Ĵ��� 

	//����ͼƬ
	Mat data = imread("data.jpg");
	namedWindow("data");
	imshow("data", data);


	Mat logo = imread("logo.jpg");
	namedWindow("logo");
	imshow("logo", logo);

	//����һ��Mat���ͣ����ڴ�ţ�ͼ���ROI
	Mat imageROI;
	//����һ
	imageROI = data(Rect(280,500,  logo.cols, logo.rows));

	//������
	//imageROI = data(Range(350, 350 + logo.rows), Range(800, 800 + logo.cols));

	//��logo�ӵ�ԭͼ��
	//addWeighted(imageROI, 0.7, logo, 0.3, 1, imageROI);
	addWeighted(imageROI, 0.7, logo, 0.3, 1, imageROI);

	//��ʾ���
	namedWindow("��4��ԭ��+logoͼ");
	imshow("��4��ԭ��+logoͼ", image);

	//-----------------------------------������ͼ��������--------------------------------------
	//     ��������һ��Matͼ�������ͼ���ļ�
	//-----------------------------------------------------------------------------------------------
	//���һ��jpgͼƬ������Ŀ¼��
	imwrite("��ϲ����dota2 byǳī.jpg", image);
#endif 
	waitKey();

	return 0;
}
