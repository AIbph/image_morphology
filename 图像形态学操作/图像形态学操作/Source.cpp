#include <opencv2/opencv.hpp> 
#include <iostream> 
using namespace cv;

// 定义Mat对象, 定义窗口名字, 起始数值， 最大值
Mat src, dst;
int element_size = 3;
int max_size = 20;

// 函数申明
void CallBack(int, void*);

int main(int argc, char** argv) {
	// 形态学操作
	/*
		移除噪声
		孤立一些单独的元素和聚合一些分散的元素
		找到图像中的局部块状或者孔
	*/

	// 读取图片并展示
	src = imread("D:/OpenCVProject/day1211/图像形态学操作/图像形态学操作/test.jpg");
	imshow("input image", src);

	// 生成窗口
	namedWindow("膨胀后的图片", CV_WINDOW_AUTOSIZE);

	// 添加滑动控件
	createTrackbar("Element Size :", "膨胀后的图片", &element_size, max_size, CallBack);

	// 调用膨胀或者腐蚀函数
	CallBack(0, 0);

	Mat open_test, kernel;
	kernel = getStructuringElement(MORPH_RECT, Size(11, 11), Point(-1, -1));

	/*
		void morphologyEx(InputArray src, OutputArray dst, int op, InputArray kernel, Point anchor=Point(-1,-1), intiterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )
		第一个参数，输入图像
		第二个参数，输出图像
		第三个参数，使用的形态学方法
	*/
	// 开运算
	morphologyEx(src, open_test, MORPH_OPEN, kernel);
	imshow("开运算后的结果", open_test);

	// 闭运算
	morphologyEx(src, open_test, MORPH_CLOSE, kernel);
	imshow("闭运算后的结果", open_test);

	// 形态学梯度
	morphologyEx(src, open_test, MORPH_GRADIENT, kernel);
	imshow("形态学梯度运算后的结果", open_test);

	// 顶帽
	morphologyEx(src, open_test, MORPH_TOPHAT, kernel);
	imshow("顶帽运算后的结果", open_test);

	// 黑帽
	morphologyEx(src, open_test, MORPH_BLACKHAT, kernel);
	imshow("黑帽运算后的结果", open_test);


	waitKey(0);
	return 0;
}

void CallBack(int, void*) {
	int s = element_size * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));

	// 膨胀函数  先腐蚀后膨胀，可以去掉小的对象，假设对象是前景色，背景是黑色
	/*
		void dilate( const Mat& src, Mat& dst, const Mat& element,Point anchor=Point(-1,-1), int iterations=1,int borderType=BORDER_CONSTANT,
const Scalar& borderValue=morphologyDefaultBorderValue() );
		src:原图像。
		dst：目标图像。
		element:腐蚀操作的内核。 如果不指定，默认为一个简单的 3x3 矩阵。否则，我们就要明确指定它的形状，可以使用函数getStructuringElement().
		anchor:默认为Point(-1,-1),内核中心点。省略时为默认值。
		iterations:腐蚀次数。省略时为默认值1。
		borderType:推断边缘类型，具体参见borderInterpolate函数。默认为BORDER_DEFAULT，省略时为默认值。
		borderValue:边缘值，具体可参见createMorphoogyFilter函数。可省略。
	*/
	dilate(src, dst, structureElement, Point(-1, -1), 1);

	// 腐蚀函数	 先膨胀后腐蚀，可以填充小的洞（fill hole），假设对象是前景色，背景是黑色
	/*
		void erode( const Mat& src, Mat& dst, const Mat& element,Point anchor=Point(-1,-1), int iterations=1,int borderType=BORDER_CONSTANT,
const Scalar& borderValue=morphologyDefaultBorderValue() );
		src:原图像。
		dst：目标图像。
		element:腐蚀操作的内核。 如果不指定，默认为一个简单的 3x3 矩阵。否则，我们就要明确指定它的形状，可以使用函数getStructuringElement().
		anchor:默认为Point(-1,-1),内核中心点。省略时为默认值。
		iterations:腐蚀次数。省略时为默认值1。
		borderType:推断边缘类型，具体参见borderInterpolate函数。默认为BORDER_DEFAULT，省略时为默认值。
		borderValue:边缘值，具体可参见createMorphoogyFilter函数。可省略。
	*/
	//erode(src, dst, structureElement);

	// 展示图片
	imshow("膨胀后的图片", dst);
	return;
}