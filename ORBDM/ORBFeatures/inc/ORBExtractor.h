////////////////////////////////////////////////////////////////////////////////
/* This file contains a class ORBDetectMatch. 
 * It is used to extract features from an image using ORB from a training image. 
 *
 * The extracted features are then matched using a brute-force matcher with the  
 * testing image to see whether the image matches with the training image. 
 */
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <opencv2/features2d.hpp> 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#define NN_RATIO 0.6 //Ratio used to retain good features

using namespace cv; 

typedef struct ImageFeatures
{
	Mat img; //Image
	std::vector<KeyPoint> kp; //KeyPoints
	Mat des; //Descriptors
}tPPImageFeatures;

namespace ORBDM 
{
class Tracker
{
   	Ptr<ORB> detector;

	//Vector depicting the number of features being tracked
	std::vector<uchar> trackerStatus;
	
   	public:
	Tracker();

   	void detectFeatures(tPPImageFeatures *apsIn);

   	void matchBruteForce(tPPImageFeatures *apsRef, 
						 tPPImageFeatures *apsIn );
	
	void matchFLANN ( tPPImageFeatures *apsRef,
					  tPPImageFeatures *apsIn);

	void kltTracker ( tPPImageFeatures *apsRef,
					  tPPImageFeatures *apsIn);
};   

}
