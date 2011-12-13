#include <fcntl.h>

int main(int argc, char **argv) {
	int i=1;
	if(argc != 3) {
		write(1,"please run this program with two arguments.\n",sizeof("please run this program with two arguments.\n"));

	}
	else{
		int first , second;
		char byte1[1], byte2[1];
		int bf,bs;
		if ( (first = open(argv[1],O_RDONLY)) == 0)
			write(1,"file argv[1] couldn't be opened\n",sizeof("file argv[1] couldn't be opened\n"));
		if ( (second = open(argv[2],O_RDONLY)) == 0)
		       write(1,"file argv[2] couldn't be opened\n",sizeof("file argv[2] couldn't be opened\n"));
		else{
			for(;;) {
				bf= read(first,byte1,1);
				bs= read(second,byte2,1);
				if(!bf && !bs)
				      break;
				if (!bf){
					write(1,"file argv[2] is longer than file argv[1].\n",sizeof("file argv[2] is longer than file argv[1].\n"));
					break;	
				}
			  	if (!bs){
					write(1,"file argv[1] is longer than file argv[2].\n",sizeof("file argv[1] is longer than file argv[2].\n"));
					break;
				}
				if (byte1[0]!=byte2[0]){
					write(1,"byte i -byte1[0] +byte2[0]\n",sizeof("byte i -byte1[0] +byte2[0]\n"));
				}
				++i;					
			}
		}
	}
	return 0;
}
