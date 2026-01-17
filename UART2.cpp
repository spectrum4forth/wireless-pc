#include <vcl.h>
#include <stdio.h>
#include <io.h>
#pragma hdrstop
#include "UART2.h"

HANDLE m_hCommPort2;
DCB config = {0};
    int com=6;
    bool abContinue = true;
    int isRead = false;
    int rxdata[16];
    int addr,bit;
    int addrbit[16];
    int yyy[33];
    short int send_flag=0x0053  ;
    BYTE buf2[10] = {0x53, 0x80, 0x20, 0x31, 0x0D};
    BYTE rx_buf2[6] = {0};
//------------------------------------------------------------------------------
unsigned char HexToInt (char ch)
{
    if (ch >= '0' && ch <= '9') return (ch - '0');        // Handle numerals
    if (ch >= 'A' && ch <= 'F') return (ch - 'A' + 0xA);  // Handle capitol hex digits
    if (ch >= 'a' && ch <= 'f') return (ch - 'a' + 0xA);  // Handle small hex digits
    return(0);

}
//------------------------------------------------------------------------------


int UART2::send2(unsigned char len)
{
    DWORD dwBytesWritten=5;
    COMMTIMEOUTS timeouts;

    DWORD written;
   int xx;

    if (!SetCommState(m_hCommPort2, &config))
    {

        printf( "Failed to Set Comm State Reason: %d\n",GetLastError());
        xx=0;
    }
      //  int isWritten =
//        WriteFile(m_hCommPort, &data,(DWORD) sizeof(data), &dwBytesWritten, NULL);
        WriteFile(m_hCommPort2, buf2, len, &dwBytesWritten, NULL);

   return xx ;
}

bool UART2::send_and_receive2(unsigned char len)
{
        DWORD dwBytesWritten=2;
        COMMTIMEOUTS timeouts;

        if (!SetCommState(m_hCommPort2, &config))
        {

                printf( "Failed to Set Comm State Reason: %d\n",GetLastError());
        }
        //       WriteFile(m_hCommPort, &data,(DWORD) sizeof(data), &dwBytesWritten, NULL);
        WriteFile(m_hCommPort2, buf2, len, &dwBytesWritten, NULL);

        // set short timeouts on the comm port.
         timeouts.ReadIntervalTimeout = 1;
         timeouts.ReadTotalTimeoutMultiplier = 1;
         timeouts.ReadTotalTimeoutConstant = 1;
         timeouts.WriteTotalTimeoutMultiplier = 1;
         timeouts.WriteTotalTimeoutConstant = 1;

         if (!SetCommTimeouts(m_hCommPort2, &timeouts))
         //system_error("setting port time-outs.");
          {
           printf( "Failed to Set Comm State Reason: %d\n",GetLastError());

          }

        DWORD total_read = 0;
        BOOL success   ;
        DWORD bytes_this_time = 0;
        success = ReadFile(m_hCommPort2,rx_buf2,6,&bytes_this_time,NULL);
        /*
        while (total_read < 6)
        {

                success = ReadFile(
                        m_hCommPort,
                        rx_buf + total_read,          // ? continue filling from current position
                        6 - total_read,               // ? ask for remaining bytes
                &bytes_this_time,
                NULL
                );
        }
        */
   return success ;
}


//---------------------------------------------------------------------------

int UART2::Closeport2(int com)
{
        char * ComX="COM1";
        if(com==2) ComX="COM2";
        else if (com==3) ComX="COM3";
        else if (com==4) ComX="COM4";
        else if (com==5) ComX="COM5";
        else if (com==6) ComX="COM6";
        else if (com==7) ComX="COM7";
        else if (com==8) ComX="COM8";
        else if (com==9) ComX="COM9";
        else if(com==10) ComX="COM10";

        m_hCommPort2 = ::CreateFile(ComX,
        GENERIC_READ|GENERIC_WRITE,//access ( read and write)

        0,    //(share) 0:cannot share the COM port

        0,    //security  (None)

        OPEN_EXISTING,// creation : open_existing

        0,    // we dont want overlapped operation

        0// no templates file for COM port...

        );

    config.DCBlength = sizeof(config);
    CloseHandle(m_hCommPort2)  ;
    return 0;
}
//---------------------------------------------------------------------------


int UART2::Openport2(int com)
{
        char * ComX="COM1";
        if(com==2) ComX="COM2";
        else if (com==3) ComX="COM3";
        else if (com==4) ComX="COM4";
        else if (com==5) ComX="COM5";
        else if (com==6) ComX="COM6";
        else if (com==7) ComX="COM7";
        else if (com==8) ComX="COM8";
        else if (com==9) ComX="COM9";
        else if(com==10) ComX="COM10";

        m_hCommPort2 = ::CreateFile(ComX,
        GENERIC_READ|GENERIC_WRITE,//access ( read and write)

        0,    //(share) 0:cannot share the COM port

        0,    //security  (None)

        OPEN_EXISTING,// creation : open_existing

        0,    // we dont want overlapped operation

        0// no templates file for COM port...

        );

    config.DCBlength = sizeof(config);


    if((GetCommState(m_hCommPort2, &config) == 0))
    {
        printf("Get configuration port has a problem.");
        return 0;
    }

    config.BaudRate = 19200 ; //115200;
    config.StopBits = ONESTOPBIT;
   // config.Parity = PARITY_EVEN;
    config.ByteSize = DATABITS_8;
    config.Parity = 0;          //2=even, 1=odd,o=none
    config.fDtrControl = 0;
    config.fRtsControl = 0;

    if (!SetCommState(m_hCommPort2, &config))
    {

     //   printf( "Failed to Set Comm State Reason: %d\n",GetLastError());
        return 0;
    }
   else
    {
    printf("Current Settings\n Baud Rate %d\n Parity %d\n Byte Size %d\n Stop Bits %d", config.BaudRate,
        config.Parity, config.ByteSize, config.StopBits);
   return 1;
     }
}
//---------------------------------------------------------------------------


void UART2::register_write2(int address,int data)
{

      unsigned char sa;
      sa =  (data & 0xff00) >>8  ;
      data = data & 0xff ;
      buf2[0] = 0x53; //{0x53,sa,address,data,0xd}   ;
      buf2[1] = sa;
      buf2[2] = address;
      buf2[3] = data;
      buf2[4] = 0xd;
      send2(5);

}
//---------------------------------------------------------------------------

bool UART2::register_read2(int address, BYTE data[])
{
      unsigned char sa;
      sa = (address & 0xff00) >>8;
      address = address;
      buf2[0] = 0x52;
      buf2[1] = sa;
      buf2[2] = address;
      buf2[3] = 0x30;
      buf2[4] = 0xd;
      bool good = send_and_receive2 (5);
      data[0] = rx_buf2[0];
      data[1] = rx_buf2[1];
      data[2] = rx_buf2[2];
      data[3] = rx_buf2[3];
      data[4] = rx_buf2[4];
      data[5] = rx_buf2[5];

     return good;

 }
//---------------------------------------------------------------------------

