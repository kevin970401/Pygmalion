#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#define PI 3.14159265
#define Deg2Rad PI/180
#define GLbyte char
#define WIDTH 768
#define HEIGHT 768

namespace geo {
	class Point {
	public:
		float x;
		float y;
		float z;
		Point() { }
		Point(const Point& _Point) :
			x(_Point.x), y(_Point.y), z(_Point.z)
		{ }
		Point(float _x, float _y, float _z) :
			x(_x), y(_y), z(_z)
		{ }
		void extenPoint(float extension);
	};

	class Line {
	public:
		Point Point1;
		Point Point2;
		Line() {}
		Line(Line& _Line) :
			Point1(_Line.Point1), Point2(_Line.Point2)
		{ }
		Line(const Point& P1, const Point& P2) :
			Point1(P1), Point2(P2)
		{ }
	};

	class Triangle {
	public:
		Point P1;
		Point P2;
		Point P3;
		Triangle(){ }
		Triangle(Point& _P1, Point& _P2, Point& _P3):
			P1(_P1), P2(_P2), P3(_P3)
		{ }
		Triangle(Triangle& T):
			P1(T.P1), P2(T.P2), P3(T.P3)
		{ }
	};

	class Obj {
	public:
		geo::Triangle* T;
		int num;
		Obj():
			T(NULL), num(0)
		{ }
	};

	inline void dot(GLbyte* data, int x, int y, int value);
	inline void dotMat(cv::Mat& img, int x, int y, int value);

	inline void swap(float &x, float &y);

	void rotate(Point& _Point, float Mat[][3]);

	void drawLine(GLbyte* data, const Line& _Line, int value);
	void drawLineMat(cv::Mat& img, const geo::Line& _Line, int value);
	void drawTriangleMat(cv::Mat& img, const geo::Triangle& T, int value);
	void drawObjMat(cv::Mat& img, const geo::Obj &obj, int value);

	void array8bit2Mat(cv::Mat& mat, char* data, int width, int height);
}