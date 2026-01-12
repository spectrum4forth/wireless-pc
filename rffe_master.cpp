#include <vcl.h>
#include <stdio.h>
#include <io.h>
#pragma hdrstop
#include "rffe_master.h"

    int addr,bit;
    int addrbit[16];
    int t0=20,td=20;
    short int send_flag=0x0053  ;
    FILE *fspi_cs;
    FILE *fspi_clk;
    FILE *fspi_data;
    unsigned char i;
    unsigned char SPI_SLV_CSN  = 1;
    unsigned char SPI_SLV_CLK  = 1;
    unsigned char SPI_SLV_MOSI = 1;

//------------------------------------------------------------------------------

void SPI_master::spi_write(unsigned char data)
{
    SPI_SLV_CSN  = 0;
    SPI_SLV_CLK  = 0;
//    unsigned char ii;
//    ii=  data & 1<<8;
    SPI_SLV_MOSI = data>127 ?1:0;
    t0++;
    fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
    fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
    fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;
    t0+=10;
    fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
    fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
    fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;

    for (int i=1;i<=8;i++)
    {
        t0++;
        SPI_SLV_CLK = 1;
        fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
        fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
        fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;
        t0+=10;
        fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
        fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
        fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;
        t0++;
        SPI_SLV_CLK = 0;
        if(i<8) SPI_SLV_MOSI = (data & 1<<(7-i))?1:0;
        else    SPI_SLV_MOSI = 0;
        fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
        fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
        fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;
        t0+=10;
        fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
        fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
        fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;
    }


}


//---------------------------------------------------------------------------

void SPI_master::spi_write_addr(unsigned char addr,short int data)
{
    unsigned char a;
    int d;
    a= addr<<1 | 1;
    d=(data & 0xff00)>>8 ;
    spi_write(a);
    spi_write(d);
    d=(data & 0xff);
    spi_write(d);
    t0++;
    SPI_SLV_CSN  = 1;
    SPI_SLV_CLK  = 1;
    SPI_SLV_MOSI = 1;
    fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
    fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
    fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;
    t0+=30;
    fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
    fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
    fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;

}
void SPI_master::spi_open(void)
{
    fspi_cs = fopen("spi_cs.csv", "w+");
    fspi_clk = fopen("spi_clk.csv", "w+");
    fspi_data = fopen("spi_data.csv", "w+");

    fclose(fspi_cs);
    fclose(fspi_clk);
    fclose(fspi_data);

    fspi_cs = fopen("spi_cs.csv", "a");
    fspi_clk = fopen("spi_clk.csv", "a");
    fspi_data = fopen("spi_data.csv", "a");
                                           
    fprintf(fspi_cs,    "%d%s    %d  \n",t0,"n",SPI_SLV_CSN)  ;
    fprintf(fspi_clk,   "%d%s    %d  \n",t0,"n",SPI_SLV_CLK)  ;
    fprintf(fspi_data,  "%d%s    %d  \n",t0,"n",SPI_SLV_MOSI)  ;

}


void SPI_master::spi_close(void)
{
    fclose(fspi_cs);
    fclose(fspi_clk);
    fclose(fspi_data);

}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

