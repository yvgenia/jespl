int length(char* s);

int puts(const char *s){
	int len= length(s);
	return write(1, s, len);
}