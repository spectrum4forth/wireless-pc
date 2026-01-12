//---------------------------------------------------------------------------

#ifndef UARTH
#define UARTH
//---------------------------------------------------------------------------
#endif



//---------------------------------------------------------------------------

class UART
{
public:

	/* Status update */
        int UART::send(unsigned char len) ;
        bool UART:: send_and_receive(unsigned char len)   ;
        int UART::Openport(int com)   ;
        int UART::Closeport(int com);
        void UART::register_write(int address,int data) ;
        bool UART::register_read(int address,BYTE data[]) ;

protected:
	// Declare pointers and variables

};

