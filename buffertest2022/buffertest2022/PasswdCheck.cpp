// PasswdCheck.cpp : Defines the entry point for the console application.
//

#include <string.h>
#include <Windows.h>
#include <stdio.h>

#define CH_BUFF_SIZE 16	// buffer size for characters in password

// class that handles password check
class PasswdCheck
{
	private:
		char buffer[CH_BUFF_SIZE];
		char string[CH_BUFF_SIZE];

	public:
		int ok;


	// constructor which initialize the member variables above
	PasswdCheck(): ok(1)
	{
		memset(buffer, 0, CH_BUFF_SIZE);
		memset(string, 0, CH_BUFF_SIZE);
	}


	// open password database and check if username/password is valid
	void CheckPass(int argc, char* argv[])
	{
		char string[CH_BUFF_SIZE * 2];
		// concatenate username and password to one string with space
#pragma warning(suppress : 4996)
		printf(string, CH_BUFF_SIZE * 2, "%s %s", argv[2], argv[3]);

		// open password database
#pragma warning(suppress : 4996)
		FILE * in = fopen(argv[1], "rb");

		// check if database is valid, return if not found setting ok=-1
		if(!in) {
			ok = -1;
			return;
		}

		// while ok=1, read CH_BUFF_SIZE-1 characters from password database to buffer
		while(ok && fgets(buffer, CH_BUFF_SIZE-1, in))
		{
			// check if concatenated username and password string matches the buffer from database
			// From MSDN: strstr - Returns a pointer to the first occurrence of a search string in a string.
			if(strstr(buffer, string))
				ok = 0;
		}
		fclose(in);
	}
};

// main function which start the program
int main(int argc, char* argv[])
{
	// check valid command line input
	if(argc != 4) {
		printf("Run syntax: buffertest.exe <password database filename> <user login> <user password> \n"
			"Return values: 1-denied, 0-accessed, (other)-system error");
		return -1; // not enough parameters, system error
	}

	// create CheckPass object
	PasswdCheck pc;

	// call CheckPass with number of arguments and arguments character array
	pc.CheckPass(argc, argv);

	if(pc.ok == 0) {
		printf("Access granted for user: %s", argv[2]);
		OutputDebugString(L"Access granted!");
	}
	else if (pc.ok < 0) {
		printf("Database not found! Full path to file is expected.");
		OutputDebugString(L"Wrong database!");
	}
	else {
		printf("Access denied, username or password incorrect!");
		OutputDebugString(L"Access denied!");
	}
	// return code for the program to OS
	return pc.ok;
}
