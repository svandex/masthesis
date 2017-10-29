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
	errorChk(DDC_OpenFileEx(tdmspath,DDC_FILE_TYPE_TDM_STREAMING,1,&file));
	errorChk(DDC_GetNumChannelGroups(file,&numOfChannelGroups));

	//Determine number of cycles of TDMS file
	numOfCycle=0;//TODO LIST
}

//Show All channel properties
void ion::showProperty() const{
	ddcChk errorChk;
	DDCChannelGroupHandle* cghtemp=(DDCChannelGroupHandle*)calloc(numOfChannelGroups,sizeof(DDCChannelGroupHandle));
	if(cghtemp == nullptr){std::cerr<<"DDCChannelGroupHandle allocation failed! "<<std::endl;return;}
	for(size_t i=1;i<=numOfChannelGroups;i++){
		std::cout<<"Channel Groups : "<<i<<std::endl;
		unsigned int numOfChannels;
		errorChk(DDC_GetNumChannels(cghtemp[i-1],&numOfChannels));
		DDCChannelHandle* chtemp = (DDCChannelHandle* )calloc(numOfChannels,sizeof(DDCChannelHandle));
	if(chtemp == nullptr){std::cerr<<"DDCChannelHandle allocation failed! "<<std::endl;return;}
		errorChk(DDC_GetChannels(cghtemp[i-1],chtemp,numOfChannels));

		for(size_t j=1;j<=numOfChannels;j++){
			std::cout<<"	Channel : "<<j<<std::endl;
			unsigned int numOfProperties;
			errorChk(DDC_GetNumChannelProperties(chtemp[j-1],&numOfProperties));
			char* property=0;
			unsigned int length;

			errorChk(DDC_GetChannelStringPropertyLength(chtemp[j-1],DDC_CHANNEL_NAME,&length));

			property = (char*)malloc(length+1);
			DDC_GetChannelProperty(chtemp[j-1],DDC_CHANNEL_NAME,property,length+1);
			std::cout<<"		Property: "<<property<<std::endl;
			free(property);
		}
	}
}

template<unsigned M, unsigned N>
decltype(auto) ion::getHandle(){
	if(M==0){
		std::cerr<<"getHandle error: M cannot be 0.";
		return nullptr;
	}

	ddcChk errorChk;
	if(M>numOfChannelGroups){std::cerr<<"getHandle error: M exceeds channel groups number";return nullptr;}
	DDCChannelGroupHandle* cghtemp=(DDCChannelGroupHandle*)calloc(numOfChannelGroups,sizeof(DDCChannelGroupHandle));
	errorChk(DDC_GetChannelGroups(file,cghtemp,numOfChannelGroups));	
	if(N==0){
		return cghtemp[M];
	}else{
		unsigned int numOfChannels;
		errorChk(DDC_GetNumChannels(cghtemp[M],&numOfChannels));	
		if(N>numOfChannelGroups){std::cerr<<"getHandle error: N exceeds channels number";return nullptr;}
		DDCChannelHandle* chtemp = (DDCChannelHandle* )calloc(numOfChannels,sizeof(DDCChannelHandle));
		errorChk(DDC_GetChannels(cghtemp[M],chtemp,numOfChannels));
		return chtemp[N];
	}


}
