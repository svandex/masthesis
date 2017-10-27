#include<iostream>
#include<nilibddc.h>
#include<ion.h>

int main(int argc, char* argv[]){
	if(argc!=3){
	   std::cerr<<"Argument Not Enough."<<std::endl;}

	ion i(argv[1],argv[2]);
}
