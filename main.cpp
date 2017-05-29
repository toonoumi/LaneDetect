#include<iostream>
#include"LaneDetector.h"
using namespace std;
int main() {
	LaneDetector rb("road.avi");
	rb.StartCapturing();
	return 0;
}