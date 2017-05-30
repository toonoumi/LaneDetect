#include<iostream>
#include"LaneDetector.h"
using namespace std;
int main() {
	LaneDetector rb("Cam");
	rb.StartCapturing();
	return 0;
}