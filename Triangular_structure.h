#pragma once
#include"base_pic_process.h"


class MatrixHandler :public Base_pic_process
{
public:
	// ���������
	int step;
	int AccumulateUpperTrangle(const Mat& a, int x = 0);
	

	// ���������
	int AccumulateLowerTrangle(const Mat& a, int x = 0);
	
};

// ͼ�����
class ImgMatrixHandler : public MatrixHandler {
public:
	// ���ش�С
	int normalized_pixel = 500;
	// ����ֵ���� ɫֵ >= threads_hold, ���ɰ�ɫ����
	int threads_hold = 255;
	// ��׼��Matrix
	Mat NormalizeMatrix(const cv::Mat& pic);
	
};

// TriangularHandler ��
class TriangularHandler : public ImgMatrixHandler {
public:
	using DataType = int;
	using Edge = tuple<DataType, DataType, DataType, DataType>;
	using Trangle = tuple<DataType, DataType, DataType, DataType, DataType>;

	// �������� ����ɫ
	int set_up_trangle = 255;
	// �������� ����ɫ
	int set_lo_trangle = 40;
	// ����߶ε���ɫ
	int set_edge = 1;

	// �꣬���� Matlab �� cpp �±껥��
#define MatLab(x) ((x)-1)
  // �����
	int MyLogTwo(int x) { return log2(x); }

	// �ճ���ʦMatlab����
	void Encode(const Mat& picture, vector<Edge>& edges,
		vector<Trangle>& trangles, int& num_of_point, int& num_of_edge,
		int& num_of_tran);
	

	// �ճ���ʦMatlab����
	void Decode(Mat& res, const vector<Edge>& edges,
		const vector<Trangle>& trangles);
	
};

// Raster ������
class BaseRaster {
	virtual cv::Mat Handle(const cv::Mat& mat, int& cost_time, int& point,
		int& line, int& tran) = 0;
};

// TriangularRaster ��
class TriangularRaster : public TriangularHandler, public BaseRaster {
public:
	// ʵ���� BaseRaster �� Handle ����
	cv::Mat Handle(const cv::Mat& mat, int& cost_time, int& point, int& line,
		int& tran) override {
		// 1.��ʼ��ʱ
		auto startTime = clock();
		// 2.��׼��Ԥ����
		auto vec = NormalizeMatrix(mat);
		vector<Edge> edges;
		vector<Trangle> trans;
		// 3.����

		Encode(vec, edges, trans, point, line, tran);
		// 4.���룬���� vec ����Ϊ��Ҫ֪�����صĶ���
		Decode(vec, edges, trans);
		// 5.������ʱ
		auto endTime = clock();
		// 6.����ʱ�䣨��λ�����룩
		cost_time = (int)(endTime - startTime) / (CLOCKS_PER_SEC / 1000);
		return vec;
	}
};
