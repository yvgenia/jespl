#include <stdio.h>

int atod(char* str){
	
	int ans=0;
	int i,size,factor;
	size=0;
	factor=1;
	
	for(i=0; str[i]!=0; ++i){
	      ++size;
	}
	
	for(i=size-1; i>=0; --i){
	      ans+= factor*(str[i]-'0');
	      factor*=10;
	}
	
	return ans;
}