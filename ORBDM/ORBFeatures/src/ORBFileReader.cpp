//////////////////////////////////////////////////////////////////////////////
/* This is a source file containing a class ORBFileReader
 *
 * This class parses a csv file with all the file names. It then creates a vector
 * with all the file names and also reads all the images from the folder
 *
 */
////////////////////////////////////////////////////////////////////////////////

#include "ORBFileReader.h"

/**
 * @func: ORBDM_parseCSVFile()
 *
 * @brief: The function parses a csv file containing the name of the images
 *
 * @ret : NULL
*/
void ORBDM::FileReader::parseCSVfile()
{
	std::fstream fCSVHandler;
	std::string sImageName;
	std::string sText;
	std::istringstream iss(sText);	

	fCSVHandler.open(csvFileName,std::ios::in);
	
	if(fCSVHandler == NULL)
		std::cout<<"Can't open the file! "<<std::endl;
	
	while(!fCSVHandler.eof())
	{	
		fCSVHandler>>sText;	
		sImageName = sText.substr(20,sText.size());
		fileNames.push_back(imageFolder+sImageName);
	}
	
	//Close the file
	fCSVHandler.close();
}


int ORBDM::FileReader::readFrame(cv::Mat &amImgIn)
{
	if(nFrame == fileNames.size())
		return END_OF_STREAM;

	amImgIn = cv::imread(fileNames[nFrame].c_str());
	std::cout<<nFrame<<"\t"<<fileNames[nFrame]<<std::endl;
	nFrame++;

	return VALID_FRAME;
	
}

