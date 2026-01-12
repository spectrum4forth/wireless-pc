//---------------------------------------------------------------------------

#ifndef rffe_masterH
#define rffe_masterH
//---------------------------------------------------------------------------
#endif



//---------------------------------------------------------------------------

class SPI_master
{
public:

	/* Status update */
        void SPI_master::spi_write(unsigned char data)   ;
        void SPI_master::spi_write_addr(unsigned char addr, short int data)   ;
        void SPI_master::spi_open(void);
        void SPI_master::spi_close(void);

protected:
	// Declare pointers and variables

};

