////////////////////////////////////////////////////////////////////////////////
/*  @Author: Leroy Francisco Pereira
 *  @Date  : 28th August, 2017
 *
 *  Copyright (c) of PathPartner Technology Private Ltd.
 *
 * 	This is a header file containing a class FileReader
 *
 * 	This class parses a csv file with all the file names. It then creates a vector
 * 	with all the file names and also reads all the images from the folder
 */
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

#include <opencv2/opencv.hpp>

#define END_OF_STREAM 0x01
#define VALID_FRAME   0x02

namespace ORBDM
{
	class FileReader
	{
		std::vector<std::string> fileNames;
		const char *csvFileName;
		const char *imageFolder;

		uint32_t nFrame;

		public:
		FileReader(const char *arg1, const char *arg2)
		{
			csvFileName = arg1;
			imageFolder = arg2;
			
			nFrame = 0;	
			//parse the CSV file
			parseCSVfile();
		}

		void parseCSVfile();
		
		int readFrame(cv::Mat &amImgIn);
	};
}
