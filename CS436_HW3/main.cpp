#include <stdio.h>
#include <iostream>

using namespace std;

// An unsigned char can store 1 Bytes (8bits) of data (0-255)
typedef unsigned char BYTE;
typedef unsigned int TWOBYTES;
typedef unsigned long FOURBYTES;


unsigned int twobytes(BYTE bytes[]);
unsigned long fourbytes(BYTE bytes[]);
unsigned int fourbits(BYTE byte);
unsigned int onebit(BYTE byte);

//TODO define all the contents of a tcpHeader and store it
struct tcpHeader
{
	TWOBYTES srcPort;
} header; //this is an instantiation of tcpHeader type

// Get the size of a file
long getFileSize(FILE *file)
{
    long lCurPos, lEndPos;
    lCurPos = ftell(file);
    fseek(file, 0, 2);
    lEndPos = ftell(file);
    fseek(file, lCurPos, 0);
    return lEndPos;
}

int main()
{
    const char *filePath = "sampleTcpDump.dat";
    BYTE *fileBuf;          // Pointer to our buffered data
    FILE *file = NULL;      // File pointer

    // Open the file in binary mode using the "rb" format string
    // This also checks if the file exists and/or can be opened for reading correctly
    if ((file = fopen(filePath, "rb")) == NULL)
    {
        cout << "Could not open specified file" << endl;
        return -1;
    }
    else
        cout << "File contents:" << endl;

    // Get the size of the file in bytes
    long fileSize = getFileSize(file);

    // Allocate space in the buffer for the whole file
    fileBuf = new BYTE[fileSize];

    // Read the file in to the buffer
    fread(fileBuf, fileSize, 1, file);

    // Now that we have the entire file buffered, we can take a look at some binary infomation
    // Lets take a look in hexadecimal
    for (int i = 0; i < fileSize; i++)
    {
    	if((i+1) % 10 == 0)
    		printf("%02X\n", fileBuf[i]);
    	else
    		printf("%02X ", fileBuf[i]);
    }


    //TWOBYTES srcPort =  twobytes(&fileBuf[0]);
    header.srcPort = twobytes(&fileBuf[0]);
    printf("\nSource Port: %d", header.srcPort);
    //TWOBYTES destPort =  twobytes(&fileBuf[2]);
    printf("\nDestination Port: %d", twobytes(&fileBuf[2]));


    //example combination: 32 bits of the file
    //FOURBYTES seqNum = fourbytes(&fileBuf[4]);
    printf("\nSequence Number: %lu", fourbytes(&fileBuf[4]));

    //FOURBYTES ackNum = fourbytes(&fileBuf[8]);
    printf("\nAcknowledgement Number: %lu", fourbytes(&fileBuf[8]));

    delete[]fileBuf;
    fclose(file);
    return 0;
}

unsigned int twobytes(BYTE bytes[])
{
	return((bytes[0] << 8) + bytes[1]);
}

unsigned long fourbytes(BYTE bytes[])
{
	return((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3]);
}

unsigned int fourbits(BYTE byte)
{
	return(byte >> 4);
}

unsigned int onebit(BYTE byte)
{
	return(byte >> 7);
}
