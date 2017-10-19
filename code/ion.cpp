#include<ion.h>

ion::~ion(){
	if(ddcError==0){
		DDC_CloseFile(file);
	}else{
		std::cerr<<"Destructing with ddcError "<<ddcError<<" !"<<std::endl;
	}
}

ion::ion(const char* p, const char* t):pepath(p),tdmspath(t){
	//Open TDMS file
	ddcError=DDC_OpenFileEx(t,DDC_FILE_TYPE_TDM_STREAMING,1,&file);
	if(ddcError<0){
		std::cerr<<"ddcError "<<ddcError<<": "<<DDC_GetLibraryErrorDescription(ddcError)<<std::endl;
	}

	//Acquire tdmsAttr
	DDC_GetNumFileProperties(file,&ta.numberOfProperties);
	DDC_GetFilePropertyNames(file,ta.propertyNames,ta.numberOfProperties);

	//Determine number of cycles of TDMS file
	numOfCycle=0;//TODO LIST
}


