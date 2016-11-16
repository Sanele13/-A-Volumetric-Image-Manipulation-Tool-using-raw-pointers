/*
Name: Sanele Mpangalala
Date: 23 March 2016
Assignment 2

*/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "volimage.h"

using namespace std;

int main(int argc, char** argv){
	if(argc<2){
		cout<<"There has to be 2 or more parameters."<<endl;
		return 0;	
	}
	//to print number of images, and number of bytes
	MPNSAN005::VolImage vol;
	vol.readImages(argv[1]);
	cout<<"Number of images: "<<vol.imageNum()<<endl;
	cout<<"Number of bytes required: "<<vol.volImageSize()<<endl;

	if(argc == 6){
		if(string(argv[2]).compare("-d")==0){
			int i;
			int j;
			istringstream iss(argv[3]);
			istringstream jss(argv[4]);
			iss>>i; 
			jss>>j;	
			vol.diffmap(i,j,argv[5]);
			cout<<"The difference has been stored in "<< argv[5]<< ".raw"<<endl;
				
		}else{
          cout<<"Please enter arguments in the following format:"<<endl;
          cout<< "volimage <imageBase> -d i j output_file_name"<<endl;}
	}else if(argc == 5 ){
      		if(string(argv[2]).compare("-x")==0){
         	int i;
         	istringstream iss(argv[3]);
         	iss>>i;
         	vol.extract(i,argv[4]);
         	cout<< "The image at "<< i<< " was extracted to "<< argv[4]<<".raw"<<endl;
		}else if(string(argv[2]).compare("-g")==0){
         	int i;
         	istringstream iss(argv[3]);
         	iss>>i;
         	vol.rowExtract(i,argv[4]);
         	cout<< "The row at "<< i<< " of all slices was extracted to "<< argv[4]<<".raw"<<endl;
		}else{
         		cout<<"Please enter arguments in one of the following formats:"<<endl;
         		cout<< "volimage <imageBase> -x i output file name"<<endl;
         		cout<<"volimage <imagebase> -g i output_file_name"<<endl;
         
      		}
	}else if(argc!=2){ //Print this out to remind user
		cout<<"Please enter arguments in one of the following formats:"<<endl;
         	cout<<"volimage <imageBase>"<<endl;
         	cout<<"volimage <imagebase> -g i output_file_name"<<endl;
         	cout<<"volimage <imageBase> -x i output file name:"<<endl;
         	cout<<"volimage <imageBase> -d i j output_file_name"<<endl;
	}
	return 0;
}
