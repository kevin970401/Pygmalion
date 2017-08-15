#include "makeBMP.h"
#include "readSTL.h"
#include "geo.h"
#include "controller.h"

using namespace cv;
using namespace std;

GLbyte data[HEIGHT * WIDTH];

geo::Hand e_hand;

int main() {

	/*while (1) {
		ex();
		for (int i = 0; i < 10; i++) {
			std::cout << "[ " << fingerPos[i][0] << ", " << fingerPos[i][1] << ", " << fingerPos[i][2] << " ]" << std::endl;
		}
	}
	return 0;*/
	/***************
	*
	* drawLine Check
	*
	***************/
	//for (int i = 0; i < 360; i += 120) {
	//	cout << i << " x: " << (10 + i) * cos(i * Deg2Rad) << " y: " << (10 + i) * sin(i * Deg2Rad) << endl;
	//	Point P1(0, 0, 0);
	//	Point P2(0 + (10 + i) * cos(i * Deg2Rad), 0 + (10 + i) * sin(i * Deg2Rad), 0);

	//	Line L1(P1, P2);
	//	drawLine(::data, L1, 1);
	//}
	//StoreIMG(::data, WIDTH, HEIGHT);


	/****************
	*
	* rotate Check
	*
	****************/
	//Line line[120];
	//for (int i = 0; i < 360; i += 3) {
	//	Point P1(0, 0, 0);
	//	Point P2((10 + i) * cos(i * Deg2Rad), (10 + i) * sin(i * Deg2Rad), 0);

	//	line[i / 3] = Line(P1, P2);
	//}

	//double degx = 3;
	//double degy = 0;
	//double degz = 0;
	//double matx[3][3] = { { 1, 0, 0 },
	//					{ 0, cos(degx * Deg2Rad), -sin(degx * Deg2Rad) },
	//					{ 0, sin(degx * Deg2Rad), cos(degx * Deg2Rad) } };
	//double matz[3][3] = { {cos(degz * Deg2Rad), -sin(degz * Deg2Rad), 0 },
	//					{ sin(degz * Deg2Rad),  cos(degz * Deg2Rad), 0 },
	//					{0, 0, 1} };
	//double maty[3][3] = { { cos(degy * Deg2Rad), 0, sin(degy * Deg2Rad) },
	//					{ 0, 1, 0 },
	//					{ -sin(degy * Deg2Rad), 0, cos(degy * Deg2Rad) } };
	//int chk = 0;
	//while (true) {
	//	for (int i = 0; i < 120; i++) {
	//		rotate(line[i].Point1, matz);
	//		rotate(line[i].Point2, matz);
	//		drawLine(::data, line[i], 1);

	//	}

	//	//StoreIMG(::data, WIDTH, HEIGHT);

	//	for (int i = 0; i < 120; i++) {
	//		drawLine(::data, line[i], 0);
	//	}
	//	if(chk++ % 1800 ==0) printf("%d ", clock());

	//	//Sleep(1000);
	//}

	Leap::Controller controller;
	Leap_Listener listener;
	controller.addListener(listener);

	geo::ObjList objlist;

	string filename("testcube.stl");
	geo::Obj* obj;
	unsigned int trigleNum;
	double extension = 1;
	obj = parseSTL2Obj(filename, trigleNum, extension);

	objlist.add(obj);

	double degx = 3;
	double degy = 3;
	double degz = 3;
	double matx[3][3] = { { 1, 0, 0 },
						{ 0, cos(degx * Deg2Rad), -sin(degx * Deg2Rad) },
						{ 0, sin(degx * Deg2Rad), cos(degx * Deg2Rad) } };
	double matz[3][3] = { { cos(degz * Deg2Rad), -sin(degz * Deg2Rad), 0 },
						{ sin(degz * Deg2Rad),  cos(degz * Deg2Rad), 0 },
						{ 0, 0, 1 } };
	double maty[3][3] = { { cos(degy * Deg2Rad), 0, sin(degy * Deg2Rad) },
						{ 0, 1, 0 },
						{ -sin(degy * Deg2Rad), 0, cos(degy * Deg2Rad) } };

	Mat img;
	img = Mat(WIDTH, HEIGHT, CV_8UC1, Scalar(0));
	namedWindow("testImage");
	if (!img.data) {
		cerr << "imread error" << endl;
		assert(false);
	}

	geo::Point P(12.15153, 150.153, 10);

	int chk = 0;

	geo::Point prevLeapFinger;
	geo::Point prevLeapPalm;
	//obj = NULL;

	geo::Hand i_hand;

	while (true) {
		objlist.rotateObjList(maty);
		geo::rotate(P, maty);
		objlist.drawObjListMat(img, 255);
		//geo::drawObjMat(img, *obj, 255);
		geo::dotMat(img, (int)P.x, (int)P.y, 255);
		i_hand = e_hand;
		geo::drawHandMat(img, i_hand, 255);

		imshow("testImage", img);
		waitKey(1000 / 1000);

		geo::drawObjMat(img, *obj, 0);
		geo::dotMat(img, (int)P.x, (int)P.y, 0);
		geo::drawHandMat(img, i_hand, 0);

		//if (geo::isPointInObj(P, *obj) == true) printf("Point (%f, %f, %f) is inside Obj\n", P.x, P.y, P.z);
		//else printf("Point (%f, %f, %f) is outside Obj\n", P.x, P.y, P.z);

		//if (geo::isFingerTouched()) {
		//	
		//	geo::Point temp = geo::getFingerCoord();
		//	if (obj != NULL) {
		//		double mat[3] = { temp.x - prevLeapFinger.x, temp.y - prevLeapFinger.y, temp.z - prevLeapFinger.z };
		//		geo::transformObj(*obj, mat);
		//	}
		//	else {
		//		obj = geo::SearchObjRelativePoint(objlist, temp);
		//	}
		//	prevLeapFinger = temp;
		//}
		//else {
		//	obj = NULL;
		//}

		if (chk++ % 120 == 0) {
			printf("%d %d\n", clock(), (int)(1000.0 / 60 * chk));
		}
	}

	getch();

	return 0;
}