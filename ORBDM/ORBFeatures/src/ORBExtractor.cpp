//////////////////////////////////////////////////////////////////////////////
/* This file contains a class Tracker. 
 * It is used to extract features from an image using ORB from a training image 
 *
 * The extracted features are then matched using a brute-force matcher/FLANN 
 * based matcher with the testing image to see whether the image matches with 
 * the training image. 
 */
//////////////////////////////////////////////////////////////////////////////


#include <ORBExtractor.h>

using namespace std;
using namespace cv;
/**
 * @fuc: Tracker
 * 
 * @brief: Constructor for the class Tracker
 * 
 * @param: void
 *
 * @ret: NULL
 */
ORBDM::Tracker::Tracker()
{
	//Default ORB detector values
	int nfeatures 	 	= 500;
	float nScaleFactor 	= 1.2f;
	int nlevels 		= 8;
	int edgeThreshold 	= 15;
	int firstLevel 	 	= 0;
	int WTA_K 		 	= 2;
	int scoreType 	 	= ORB::HARRIS_SCORE;
	int patchSize 	 	= 31;
	int fastThreshold 	= 20;

	detector = ORB::create(	nfeatures, nScaleFactor, nlevels, edgeThreshold, 
							firstLevel,  WTA_K, scoreType, patchSize, 
							fastThreshold);
}


/**
 * @fuc: detectFeatures
 * 
 * @brief: Detects ORB features from a given input image
 * 
 * @param: structure containing the following parameters
 * @1: Input Image
 * @2: Vector of KeyPoints
 * @3: Descriptors
 *
 */
void ORBDM::Tracker::detectFeatures(tPPImageFeatures *apsIn)
{
	detector->detectAndCompute(apsIn->img, Mat(), apsIn->kp, apsIn->des);
   	cout<<"Found "<< apsIn->kp.size()<<" Keypoints "<< endl;
}
   
/**
 * @fuc: matchBruteForce
 * 
 * @brief: Matches the ORB features between two images using bruteforce
 * 
 * @param1: Image Feature structure to the reference image
 * @param2: Image Feature structure to the input image
 *
 */
void ORBDM::Tracker::matchBruteForce(	tPPImageFeatures *apsRef, 
							tPPImageFeatures *apsIn )
{
	Mat imgMatches;
	BFMatcher matcher(cv::NORM_HAMMING);
	vector<DMatch> matches;
	matcher.match(apsRef->des, apsIn->des, matches);

	//draw the results
	drawMatches(apsRef->img,apsRef->kp, 
				apsIn->img, apsIn->kp, 
				matches, imgMatches);
	imshow("Matches", imgMatches);
}


/**
 * @fuc: matchFLANN
 *
 * @brief: Matches the ORB features between two images using FLANN
 * 
 * @param1: Image Feature structure to the reference image
 * @param2: Image Feature structure to the input image
 *
 * @ret : NULL
 */
void ORBDM::Tracker::matchFLANN(tPPImageFeatures *apsRef, 
								tPPImageFeatures *apsIn )
{
	Mat imgMatches;
	FlannBasedMatcher matcher(new flann::LshIndexParams(20, 10, 2));
	vector<vector<DMatch> > matches;
	vector<DMatch> goodMatches;

	matcher.knnMatch(apsRef->des, apsIn->des, matches,2);
	
	cout<<"Matches: "<<matches.size()<<std::endl;

	//-- Draw only the good matches
	for(int i=0; i<std::min(apsIn->des.rows-1,(int)matches.size()); i++)
	{
		//Check if the distance is small
		if(matches[i][0].distance < NN_RATIO*(matches[i][1].distance) &&
			((int)matches[i].size()<=2 && (int)matches[i].size()>0))
			goodMatches.push_back(matches[i][0]);
	}

	cout<<"Good Matches: "<<goodMatches.size()<<endl;
		 
	//draw the results
	drawMatches(apsRef->img, apsRef->kp, 
				apsIn->img, apsIn->kp, 
				goodMatches, imgMatches);
	imshow("Matches", imgMatches);
}

/**
 * @fuc: kltTracker
 *
 * @brief: Trackes the features from one image to the outher using the lucas kanade scheme
 * 
 * @param1: Image Feature structure to the reference image
 * @param2: Image Feature structure to the input image
 *
 * @ret   : NULL
 */
void ORBDM::Tracker::kltTracker(tPPImageFeatures *apsRef,
								tPPImageFeatures *apsIn)
{
	std::vector<cv::Point2f>  pointRef, pointIn;
	std::vector<float> err;
	
	//convert the keypoints from both the images to type vector<Point2f>
	cv::KeyPoint::convert(apsRef->kp, pointRef, std::vector<int>());

	cv::KeyPoint::convert(apsIn->kp, pointIn, std::vector<int>());

	//Pass the points to the klt feature tracker
	cv::calcOpticalFlowPyrLK(apsRef->img, apsIn->img, 
							 pointRef, pointIn,
							 trackerStatus, err);
	int nMatches = 	std::count(trackerStatus.begin(), trackerStatus.end(), (uchar)1);
	
	std::cout<<"Matches = "<<nMatches<<std::endl;


}

