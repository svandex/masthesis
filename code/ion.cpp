#include<ion.h>

void ddcChk::operator()(const int &ddcError) const {
	if(ddcError<0){
		os<<"ddcError"<<sep<<ddcError<<":"<<DDC_GetLibraryErrorDescription(ddcError)<<std::endl;
	}else{
	//	std::cout<<"Check Pass!"<<std::endl;
	}

}

ion::~ion(){
	ddcChk exChk;
	exChk(DDC_CloseFile(file));
}

ion::ion(const char* p, const char* t):pepath(p),tdmspath(t){
	ddcChk errorChk(std::cerr);
	//Open TDMS file
	errorChk(DDC_OpenFileEx(t,DDC_FILE_TYPE_TDM_STREAMING,1,&file));

	//Acquire tdmsAttr
	errorChk(DDC_GetNumFileProperties(file,&ta.numberOfProperties));
	errorChk(DDC_GetFilePropertyNames(file,ta.propertyNames,ta.numberOfProperties));

//	std::cout<<ta.numberOfProperties<<std::endl;
	DDCDataType temp;
	for(unsigned int i=1;i<=ta.numberOfProperties;i++){
		//std::cout<<"Loop:"<<i<<std::endl;
		errorChk(DDC_GetFilePropertyType(file,*(ta.propertyNames+i-1),&temp));
		ta.propertyDataType.push_back(temp);
	}


	//Determine number of cycles of TDMS file
	numOfCycle=0;//TODO LIST

	//std::cout<<"Ion Initialization Success."<<std::endl;
}


