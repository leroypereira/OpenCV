////////////////////////////////////////////////////////////////////////////////
/*  @Author: Leroy Francisco Pereira
 *  @Date  : 28th August, 2017
 *
 *  Copyright (c) of PathPartner Technology Private Ltd.
 */
////////////////////////////////////////////////////////////////////////////////
#include "ORBExtractor.h"
#include "ORBFileReader.h"
#include <opencv2/opencv.hpp>


using namespace cv;
using ORBDM::FileReader;

int testFLANNMatcher(char *apsImgRef, char *apsImgIn)
{
	tPPImageFeatures imgRef, imgIn;
	ORBDM::Tracker tracker;
	Mat out;


	//Read the Reference Image
	imgRef.img = imread(apsImgRef);
	if(!imgRef.img.data)
	{
	   std::cout << "No Reference image data \n";
	   return -1;
	}
	
	//Read normal image
	imgIn.img = imread(apsImgIn);
	if(!imgIn.img.data)
	{
	   std::cout << "No image data \n";
	   return -1;
	}
	

    //Detect the keypoints and descriptors in the reference image
	tracker.detectFeatures(&imgRef);

	//Detect the keypoints and descriptors in the normal image
	tracker.detectFeatures(&imgIn);
	
	tracker.matchFLANN(&imgRef, &imgIn); 
	
	
	return 0;
}
int main(int argc, char** argv)
{

	//To test the FLANN based matcher
	//testFLANNMatcher(argv[1], argv[2]);
	
	
	tPPImageFeatures currFrame, prevFrame;
	ORBDM::Tracker tracker;
	//argv[1] => path to the image names
    //argv[2] => path to the image folder
	ORBDM::FileReader reader(argv[1], argv[2]);
	
	reader.readFrame(prevFrame.img);
	tracker.detectFeatures(&prevFrame);

	while(reader.readFrame(currFrame.img) != END_OF_STREAM)
	{
		tracker.detectFeatures(&currFrame);
		
		//tracker.kltTracker(&prevFrame, &currFrame);

		tracker.matchFLANN(&prevFrame, &currFrame);

		//prevFrame = currFrame;
		//imshow("Frame",currFrame.img);
		if(waitKey(10)==27) break;
	}
	//waitKey(0);

	return 0;
}



