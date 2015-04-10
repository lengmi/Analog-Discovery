// Analog Discovery.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dwf.h"
#include <iostream>

BOOL discoverAndConnect(HDWF* hdwf);

int _tmain(int argc, _TCHAR* argv[])
{
	HDWF hdwf = 0;
	discoverAndConnect(&hdwf);

	FDwfDeviceClose(hdwf);
	getchar();
	return 0;
}

BOOL discoverAndConnect(HDWF* phdwf)
{
	int numDevice = 0;
	DEVID devID = 0;
	DEVVER devVer = 0;
	BOOL ifDevOpened = 0;
	char szUserName[32];
	char szDeviceName[32];
	char szSN[32];
	BOOL ifConnect = 0;
	while (!numDevice)
	{
		FDwfEnum(enumfilterDiscovery, &numDevice);
		if (!numDevice)
		{
			printf("No Analog Discovery found, press enter to try again.\n$");
			fflush(stdin);
			getchar();
		}
	}
	for (int i = 0; i < numDevice; i++)
	{
		FDwfEnumDeviceType(i, &devID, &devVer);
		FDwfEnumUserName(i, szUserName);
		FDwfEnumDeviceName(i, szDeviceName);
		FDwfEnumSN(i, szSN);
		printf("Analog Discovery %c found.\n", devVer - 1 + 'A');
		printf("User Name: %s.\n", szUserName);
		printf("Device Name: %s\n", szDeviceName);
		printf("Device %s\n\n", szSN);
	}
	FDwfEnumDeviceIsOpened(0, &ifDevOpened);
	if (ifDevOpened)
	{
		printf("Analog Discovery is busy now.\n");
	}
	else
	{
		printf("Analog Discover is ready, trying to connect.\n");
		if (FDwfDeviceOpen(0, phdwf))
		{
			printf("The connection with Analog Discovery have been established, have fun!\n");
			ifConnect = 1;
		}
		else
		{
			printf("Connecting to Analog Discovery Failed.");
		}
	}
	return ifConnect;
}