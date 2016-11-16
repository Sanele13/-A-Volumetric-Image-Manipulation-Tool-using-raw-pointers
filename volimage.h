/*
Name: Sanele Mpangalala
Date: 23 March 2016
Assignment 2

*/
#ifndef VOLIMAGE_H
#define VOLIMAGE_H

namespace MPNSAN005{

class VolImage
{
private:
	// private members
	int width, height;// width and height of image stack
	std::vector<unsigned char**> slices;// data for each slice, in order
public:
	// public members
	VolImage();// default constructor
	~VolImage();// destructor
	bool readImages(std::string baseName);
	// compute difference map and write out;  define in .cpp
	void diffmap(int sliceI, int sliceJ, std::string output_prefix);
	// extract slice sliceId and write to output - define in .cpp
	void extract(int sliceId, std::string output_prefix);
	// number of bytes uses to store image data bytes
	//and pointers (ignore vector<> container, dims etc)
	int imageNum(void);
	int volImageSize(void);
	//for extra credit
	void rowExtract(int rowId, std::string output_prefix);
};
}
#endif
