//---------------------------------------------------------------------------

#ifndef UART2H
#define UART2H
//---------------------------------------------------------------------------
#endif



//---------------------------------------------------------------------------

class UART2
{
public:

	/* Status update */
        int UART2::send2(unsigned char len) ;
        bool UART2:: send_and_receive2(unsigned char len)   ;
        int UART2::Openport2(int com)   ;
        int UART2::Closeport2(int com);
        void UART2::register_write2(int address,int data) ;
        bool UART2::register_read2(int address,BYTE data[]) ;

protected:
	// Declare pointers and variables

};

