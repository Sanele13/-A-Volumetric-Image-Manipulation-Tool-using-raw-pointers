/*
Name: Sanele Mpangalala
Date: 23 March 2016
Assignment 2

*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "volimage.h"
#include <ios>
#include <cmath>

using namespace std;

MPNSAN005::VolImage::VolImage(){
	//initialisation	
	width = 0;
	height=0;
}

MPNSAN005::VolImage::~VolImage(){
	int vectorSize = slices.size();	
	for (int i=0; i<vectorSize; i++){
		for(int j=0; j< height; j++){
			delete [] slices[i][j];		
		}	
		delete slices[i];
	}

}

//Method to read the image files

bool MPNSAN005::VolImage::readImages(std::string baseName){
	string headerFileName = baseName+".data";
	ifstream headerFile(headerFileName.c_str(), ios::binary);
	string line; //line read from file
	int num; //number of images

	if(headerFile.is_open()){
		getline(headerFile, line);
		istringstream iss(line);
		//getting the header information
		iss>>width;
		iss>>height;
		iss>>num;
		
		headerFile.close();
	}
	else{ cout<<"Unable to open file."<<endl; return false;}
	
	unsigned char** imageBuffer;
	for(int i = 0; i< num; i++){
      		stringstream ss;
      		ss << i;
      		string strNum = ss.str(); //number to string
      		string fileName = baseName + strNum +".raw";
      		ifstream image(fileName.c_str(),  ios::binary);
      
		if (image.is_open()){
         		imageBuffer = new unsigned char*[height];
         		unsigned char* row;
         		for(int j =0; j< height; j++){
            			row = new unsigned char[width];
            			image.read((char*)row, width); //store in the array pointed to by 'row'
            			imageBuffer[j]= row; //[row0,row1,row2,...]
         		}
	        slices.push_back(imageBuffer);
        	image.close();
     		}
         
	}
	return true;
     
}

//extraction method
void MPNSAN005::VolImage::extract(int sliceId, std::string output_prefix){
	string headerFilename = output_prefix + ".data";
	ofstream headerFile(headerFilename.c_str(), ios::out);
	//create header	
	if(headerFile.is_open()){
		headerFile<<width<<" "<<height<<" "<<1<<endl;
		headerFile.close();
	}else{cout<<"Unable to open file."<<endl;}

	string outputFilename = output_prefix + ".raw";
	ofstream output(outputFilename.c_str(), ios::binary);
	if(output.is_open()){
		for(int i=0;i<height;i++){
			char* theByte = (char*)slices[sliceId][i];
			output.write(theByte, width);		
		}
		output.close();
	}else{cout<<"Unable to open file"<<endl;}

}

//number of bytes required to store image data
int MPNSAN005::VolImage::volImageSize(void){
	int size = slices.size();
	return size*height*(sizeof(unsigned char**)+width);
}

//number of images
int MPNSAN005::VolImage::imageNum(void){
	int number = slices.size();
	return number;
}

//diffmap
void MPNSAN005::VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
	string headerFilename = output_prefix + ".data";
	ofstream headerFile(headerFilename.c_str(), ios::out);
	if(headerFile.is_open()){
		headerFile<<width<<" "<<height<<" "<<1<<endl;
		headerFile.close();
	}else{cout<<"Unable to open file."<<endl;}
	string outputFile = output_prefix + ".raw";
	ofstream output(outputFile.c_str(), ios::binary);
	if(output.is_open()){
		for(int i =0; i<height; i++){
			for(int j = 0; j<width; j++){
				char theByte = abs(((float)slices[sliceI][i][j]- (float)slices[sliceJ][i][j])/2);
				output.write(&theByte, 1); //write diffmap to output file	
			}		
		}
		output.close();
	}else{cout<<"Unable to open the file."<<endl;}
}

//new operation [-g i], which extracts an image along row i of the volume, across all slice

void MPNSAN005::VolImage::rowExtract(int rowId, std::string output_prefix){
	string headerFilename = output_prefix + ".data";
	ofstream headerFile(headerFilename.c_str(), ios::out);
	if(headerFile.is_open()){
		cout<<"Creating header file."<<endl;
		headerFile<<width<<" "<<height<<" "<<1<<endl;
		cout<<"Header file created."<<endl;
		headerFile.close();
	}else{cout<<"Unable to open file"<<endl;}
	string output = output_prefix+".raw";
	ofstream out(output.c_str(), ios::binary);
	if(out.is_open()){
		for(int i=0; i<slices.size(); i++){
			char* theByte = (char*)slices[i][rowId];
			out.write(theByte, width);
		}
		out.close();
	}
}

