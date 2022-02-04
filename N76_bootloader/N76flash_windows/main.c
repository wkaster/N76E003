/**
*  N76flash utility by Wiliam Kaster
*  Visit https://github.com/wkaster/N76E003 for more info
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
*
*  Version 1.0: 2022-02-04
*       First working version
*/
#include<windows.h>
#include<stdio.h>
#include<stdbool.h>

#define BLOCK_SIZE      16
#define CMD_SOH			0x01    // [SOH] Start of Heading
#define CMD_STX			0x02	// [STX] Start of Text
#define CMD_ETX			0x03	// [ETX] End of Text
#define CMD_EOT         0x04    // [EOT] End of Transmission
#define CMD_ACK			0x06	// [ACK] Acknowledge
#define CMD_NACK		0x15	// [NAK] Negative Acknowledge
#define CMD_SUB         0x1A    // [SUB] Substitute
#define CMD_DEL         0x7F    // [DEL] Delete


unsigned char dallas_crc8(unsigned char*, unsigned char);

void help();

int main(int argc, char** argv)
{
    int nIgnorePorts[5];
    int nIgnoreIdx = 0;
    int nReturnCode = 0;
    bool bIgnore = false;
    bool bFixPort = false;
    bool bFlag = true;
    char szTemp[4];
    char szTargetPath[256]; // buffer to store the path of the COMPORTS
    char szFileName[256] = "";
    FILE * pFile;
    long lFileSize;
    int nFileBlocks;
    char szPortNumber[3];
    char szPortName[6];
    char szDefaultPort[6];
    char szFullPortName[15];
    DWORD dwResult;
    DWORD dwBytesActuallyRead;
    DWORD dwBytesActuallyWritten;
    int nPortsFound=0; // number of serial ports found
    int nTries=25;
    COMMTIMEOUTS TimeOuts;
    //OVERLAPPED writeOverlapped;
    unsigned char byWriteBuffer[128];
    unsigned char byReadBuffer;             // just 1 byte needed (usually ack)
    unsigned char byFileBuffer[BLOCK_SIZE];
    unsigned char byCRC;
    int nBytesRead = 0;
    int i,j;

    //serial
    HANDLE hCom;
    DCB dcb;
    bool bSuccess;


    if (argc > 1) {
        for(i=1 ; i<argc ; i++) {
            if(strcmp("-ignore", argv[i]) == 0 || strcmp("-i", argv[i]) == 0) {
                strcpy(szTemp,argv[i+1]);
                if(isdigit(szTemp[0])) {
                    nIgnorePorts[nIgnoreIdx] = atoi(szTemp);
                    if(nIgnoreIdx < 4) nIgnoreIdx++;
                }
                else {
                    printf("Error: port parameter is not a number.\n");
                    nReturnCode = 1;
                    goto error;
                }
            }
            if(strcmp("-file", argv[i]) == 0 || strcmp("-f", argv[i]) == 0) {
                strcpy(szFileName,argv[i+1]);
            }
            if(strcmp("-tries", argv[i]) == 0 || strcmp("-t", argv[i]) == 0) {
                strcpy(szTemp,argv[i+1]);
                if(isdigit(szTemp[0])) {
                    nTries = atoi(szTemp);
                }
                else {
                    printf("Error: tries parameter is not a number.\n");
                    nReturnCode = 1;
                    goto error;
                }
            }
            if(strcmp("-port", argv[i]) == 0 || strcmp("-p", argv[i]) == 0) {
                strcpy(szTemp,argv[i+1]);
                if(isdigit(szTemp[0])) {
                    strcpy(szDefaultPort,"COM");
                    strcat(szDefaultPort,szTemp);
                    bFixPort = true;
                }
                else {
                    printf("Error: port parameter is not a number.\n");
                    nReturnCode = 1;
                    goto error;
                }
            }
            if(strcmp("-help", argv[i]) == 0 || strcmp("-h", argv[i]) == 0) {
                help();
                exit(0);
            }
        }
    }
    else {
        help();
        exit(0);
    }

    if(strlen(szFileName)==0) {
        printf("Error: no input file specified.\n");
        nReturnCode = 1;
        goto error;
    }

    if(!bFixPort) {
        for(int i=0; i<=99; i++) // checking ports from COM0 to COM99
        {
            for(j=0 ; j<=nIgnoreIdx ; j++) {
                if(nIgnorePorts[j] == i) bIgnore = true;
            }

            if(bIgnore) {
                bIgnore = false;
                continue;
            }

            strcpy(szPortName,"COM");
            itoa(i, szPortNumber, 10);
            strcat(szPortName, szPortNumber);

            dwResult = QueryDosDevice(szPortName, szTargetPath, 5000);

            if(dwResult!=0) //QueryDosDevice returns zero if it didn't find an object
            {
                if(bFlag) {
                    printf("Port(s) Found:\n");
                    bFlag = false;
                }
                printf("%s\n", szPortName);
                strcpy(szDefaultPort,szPortName);
                nPortsFound++; // found port
            }
        }

        if(nPortsFound == 0) {
            printf("Error: no avaliable serial port found.\n");
            nReturnCode = 1;
            goto error;
        }

        if(nPortsFound > 1) {
            printf("Enter port number: ");
            scanf("%d", &i);
            strcpy(szDefaultPort,"COM");
            itoa(i, szPortNumber, 10);
            strcat(szDefaultPort, szPortNumber);
        }
    }

    printf("Default Port: %s\n", szDefaultPort);

    pFile = fopen(szFileName,"rb");
    if (pFile==NULL) {
        printf("Error: cannot open the specified file %ld.\n", GetLastError());
        exit(1);
    }

    fseek(pFile, 0, SEEK_END);
    lFileSize = ftell(pFile);
    nFileBlocks = (int) lFileSize / BLOCK_SIZE;
    rewind(pFile);

    printf("File: %s (size: %ld bytes)\n", szFileName, lFileSize);

    strcpy(szFullPortName,"\\\\.\\");
    strcat(szFullPortName,szDefaultPort);

    hCom = CreateFile(szFullPortName,  //port name
        GENERIC_READ | GENERIC_WRITE,   //Read/Write
        0,                              // No Sharing
        NULL,                           // No Security
        OPEN_EXISTING,                  // Open existing port only
        0,                              // Non Overlapped I/O
        NULL);                          // Null for Comm Devices

    if (hCom == INVALID_HANDLE_VALUE) {
        printf("Error: opening serial port\n");
        nReturnCode = 1;
        goto error;
    }

    //  Initialize the DCB structure.
    SecureZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);


    //  19200 bps, 8 data bits, no parity, and 1 stop bit.
    dcb.BaudRate = CBR_19200;     //  baud rate
    dcb.ByteSize = 8;             //  data size, xmit and rcv
    dcb.Parity   = NOPARITY;      //  parity bit
    dcb.StopBits = ONESTOPBIT;    //  stop bit

    bSuccess = SetCommState(hCom, &dcb);

    if(!bSuccess)
    {
        //  Handle the error.
        printf("SetCommState failed with error %ld.\n", GetLastError());
        nReturnCode = 1;
        goto error;
    }

    TimeOuts.ReadIntervalTimeout = MAXDWORD;
    TimeOuts.ReadTotalTimeoutMultiplier = 1;
    TimeOuts.ReadTotalTimeoutConstant = 200;
    TimeOuts.WriteTotalTimeoutMultiplier = MAXDWORD;
    TimeOuts.WriteTotalTimeoutConstant = MAXDWORD;

    bSuccess = SetCommTimeouts(hCom, &TimeOuts);

    if(!bSuccess)
    {
        //  Handle the error.
        printf("SetCommTimeouts failed with error %ld.\n", GetLastError());
        nReturnCode = 1;
        goto error;
    }

    byWriteBuffer[0] = 0x01;    // [SOH] Start of Heading: Are you there?
    byReadBuffer = 0x00;     // zero receive buffer byte

    printf("Connecting, please RESET the microcontroller...\n");

    for(i=0;i<=nTries;i++) {
        bSuccess = WriteFile(hCom,
                 &byWriteBuffer[0],
                 1,
                 &dwBytesActuallyWritten,
                 NULL);

        if (!bSuccess) {
            //  Handle the error.
            printf("Error %ld.\n", GetLastError());
            nReturnCode = 1;
            goto error;
        }

        bSuccess = ReadFile(hCom,
                 &byReadBuffer,
                 1,
                 &dwBytesActuallyRead,
                 NULL);

        if (!bSuccess) {
            //  Handle the error.
            printf("Error %ld.\n", GetLastError());
            nReturnCode = 1;
            goto error;
        }

        if(byReadBuffer==CMD_ACK) {
            printf("Handshake OK!\n");
            byReadBuffer=0x00;
            break;
        }
        else {
            printf("Try %d...", i);
            if(byReadBuffer!=0x00) {
                byReadBuffer=0x00;              // returning garbage or application data
                Sleep(200);                     // forcing wait
                PurgeComm(hCom,PURGE_RXCLEAR);  // clearing for next try
            }
            if(i==nTries) {
                printf ("Give up!\n");
                nReturnCode=1;
            }
            else printf("\r");
        }
    }

    if(nReturnCode==1) goto error;  // gave up connecting


    TimeOuts.ReadIntervalTimeout = MAXDWORD;
    TimeOuts.ReadTotalTimeoutMultiplier = 1;
    TimeOuts.ReadTotalTimeoutConstant = 6000;
    TimeOuts.WriteTotalTimeoutMultiplier = MAXDWORD;
    TimeOuts.WriteTotalTimeoutConstant = MAXDWORD;

    bSuccess = SetCommTimeouts(hCom, &TimeOuts);

    if(!bSuccess)
    {
        //  Handle the error.
        printf("SetCommTimeouts failed with error %ld.\n", GetLastError());
        nReturnCode = 1;
        goto error;
    }


    printf("Erasing... ");

    byWriteBuffer[0] = CMD_SUB;
    byWriteBuffer[1] = CMD_DEL;

    bSuccess = WriteFile(hCom,
             &byWriteBuffer[0],
             2,
             &dwBytesActuallyWritten,
             NULL);

    if (!bSuccess) {
        //  Handle the error.
        printf("Error %ld.\n", GetLastError());
        nReturnCode = 1;
        goto error;
    }

    bSuccess = ReadFile(hCom,
             &byReadBuffer,
             1,
             &dwBytesActuallyRead,
             NULL);

    if (!bSuccess) {
        //  Handle the error.
        printf("Error %ld.\n", GetLastError());
        nReturnCode = 1;
        goto error;
    }

    if(byReadBuffer==CMD_ACK) {
        printf("Done!\n");
        byReadBuffer=0x00;
    }
    else {
        printf("Error erasing chip.\n");
        nReturnCode = 1;
        goto error;
    }

    i=0;
    while(!feof(pFile)) {
        nBytesRead = fread(&byFileBuffer[0], sizeof(unsigned char), BLOCK_SIZE, pFile);

        // fill with 0xFF if needed
        if(nBytesRead < BLOCK_SIZE) {
            memset(&byFileBuffer[nBytesRead], (unsigned char) 0xFF, BLOCK_SIZE - nBytesRead);
            nFileBlocks = i;  // end of file reached: percentage round
        }

        byCRC = dallas_crc8(&byFileBuffer[0],BLOCK_SIZE);

        /* The package */
        byWriteBuffer[0] = CMD_STX;
        memcpy(&byWriteBuffer[1], &byFileBuffer[0], BLOCK_SIZE);
        byWriteBuffer[BLOCK_SIZE + 1] = byCRC;
        byWriteBuffer[BLOCK_SIZE + 2] = CMD_ETX;

        bSuccess = WriteFile(hCom,
                 &byWriteBuffer[0],
                 BLOCK_SIZE + 3,
                 &dwBytesActuallyWritten,
                 NULL);

        if (!bSuccess) {
            //  Handle the error.
            printf("Error %ld.\n", GetLastError());
            nReturnCode = 1;
            goto error;
        }

        bSuccess = ReadFile(hCom,
                 &byReadBuffer,
                 1,
                 &dwBytesActuallyRead,
                 NULL);

        if (!bSuccess) {
            //  Handle the error.
            printf("Error %ld.\n", GetLastError());
            nReturnCode = 1;
            goto error;
        }

        if(byReadBuffer==CMD_ACK) {
            printf("Writing: %d%%", (i*100)/nFileBlocks);
            if(i==nFileBlocks) printf("\n"); else printf("\r");
            byReadBuffer=0x00;
            i++;
        }

        if(byReadBuffer==CMD_NACK) {
            printf("error!\n");
            break;
        }

    }

    printf("Soft reset... ");

    byWriteBuffer[0] = CMD_EOT;

    bSuccess = WriteFile(hCom,
             &byWriteBuffer[0],
             1,
             &dwBytesActuallyWritten,
             NULL);

    if (!bSuccess) {
        //  Handle the error.
        printf("Error %ld.\n", GetLastError());
        nReturnCode = 1;
        goto error;
    }

    bSuccess = ReadFile(hCom,
             &byReadBuffer,
             1,
             &dwBytesActuallyRead,
             NULL);

    if (!bSuccess) {
        //  Handle the error.
        printf("Error %ld.\n", GetLastError());
        nReturnCode = 1;
        goto error;
    }

    if(byReadBuffer==CMD_ACK) {
        printf("Done!\n");
        byReadBuffer=0x00;
    }
    else {
        printf("Error reseting.\n");
        nReturnCode = 1;
        goto error;
    }

    error:

    if(hCom != NULL) CloseHandle(hCom);     //Closing the Serial Port
    if(pFile != NULL) fclose(pFile);        //Closing binary file
    return nReturnCode;
}

unsigned char dallas_crc8(unsigned char* data, unsigned char size)
{
    unsigned char crc = 0;
    for ( unsigned char i = 0; i < size; ++i )
    {
        unsigned char inbyte = data[i];
        for ( unsigned char j = 0; j < 8; ++j )
        {
            unsigned char mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if ( mix ) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}

void help() {
    printf("Nuvoton N76E003 / MS51xx flash utility V1.0 - Windows version\n");
    printf("Visit https://github.com/wkaster/N76E003 for more info.\n");
    printf("Options:\n");
    printf(" -file [-f] binary file to flash\n");
    printf(" -ignore [-i] serial port number to ignore 1-99 (up to five ports)\n");
    printf(" -port [-p] fix serial port to use\n");
    printf(" -tries [-t] number of connecting tries. Default is 25 tries of 200ms each\n");
    printf(" -help [-h] this screen\n");
}
