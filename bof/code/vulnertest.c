/* vulner.c */

void main(int argc, char *argv[]) {
	char buffer[400];
	
	printf("%x\n", argc);
	printf("%x\n", buffer);
	if (argc > 1)
		strcpy(buffer, argv[1]);
}
