#include<iostream>
#include<nilibddc.h>

int main(int argc, char* argv[]){
	if(argc!=2){
		std::cout<<"ARGUMENT NOT ENOUGH!"<<std::endl;
		return 1;
	}
	int ddcError=0;
	DDCFileHandle file=0;

//	std::cout<<argv[1]<<std::endl;

	//open file
	//ddcError=DDC_OpenFileEx(argv[1],DDC_FILE_TYPE_TDM_STREAMING,1,&file);
	ddcError=DDC_OpenFileEx(argv[1],"TDMS",1,&file);
	if(ddcError==0){
		unsigned int ncg;
		ddcError=DDC_GetNumChannelGroups(file,&ncg);

		unsigned int numberOfProperties;
		DDC_GetNumFileProperties(file,&numberOfProperties);
		if(ddcError==0){
			std::cout<<"Number of Channal Groups: "<<ncg<<std::endl;
			std::cout<<"Number of File Properties: "<<numberOfProperties<<std::endl;
		}else{
			std::cout<<"ddcError: GetNum Error, "<<ddcError<<" ,"<<DDC_GetLibraryErrorDescription(ddcError)<<std::endl;
		}	
	}else{
		std::cout<<"ddcError: OpenFile Error, "<<ddcError<<" ,"<<DDC_GetLibraryErrorDescription(ddcError)<<std::endl;
	}
	DDC_CloseFile(file);
	return 0;
}
