#define SCL_EN  0x00000010
#define SDA_EN  0x00000040


#define CCLK      60000000  //Hz
#define PCLK      CCLK/4    //Hz
#define I2C_SPEED 100000    //Hz
#define LOADVAL   ((PCLK/I2C_SPEED)/2)



#define   AA_BIT 2
#define   SI_BIT 3
#define  STO_BIT 4
#define  STA_BIT 5
#define I2EN_BIT 6


void init_i2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_write(u8);
u8   i2c_read(void);
u8 i2c_ack(void);
u8 i2c_nack(void);
u8 i2c_masterack(void);

u8 i2c_rtc_read(u8 slaveAddr,u8 rBuffAddr)
{
	u8 dat;
	i2c_start();	
  i2c_write(slaveAddr<<1); 
	i2c_write(rBuffAddr);
	i2c_restart();	
	i2c_write(slaveAddr<<1|1);  
  dat=i2c_nack();	
	i2c_stop();
	return dat;
}


void init_i2c(void)

{

	 //Configure I/O pin for SCL & SDA functions using PINSEL0

	// PINSEL0 = 0X00000050;

	  PINSEL0 |=SCL_EN|SDA_EN;

	 //Configure Speed for I2C Serial Communication

	 //Using I2CSCLL

	 I2SCLL=LOADVAL;

   //& I2CSCLH

	 I2SCLH=LOADVAL;

	//I2C Peripheral Enable for Communication

	 I2CONSET=1<<I2EN_BIT; 

}	


void i2c_start(void)

{

	// start condition

  I2CONSET=1<<STA_BIT;

	//wait for start bit status

	while(((I2CONSET>>SI_BIT)&1)==0);

	// clear start condition

	I2CONCLR=1<<STA_BIT;

}	


void i2c_restart(void)

{

	// start condition

	I2CONSET=1<<STA_BIT;

	//clr SI_BIT

	I2CONCLR=1<<SI_BIT;

	//wait for SI bit status

	while(((I2CONSET>>SI_BIT)&1)==0);

	// clear start condition

	I2CONCLR=1<<STA_BIT;

}	


void i2c_write(u8 dat)

{

	//put data into I2DAT

	I2DAT=dat;	

	//clr SI_BIT

	I2CONCLR = 1<<SI_BIT;

	//wait for SI bit status

	while(((I2CONSET>>SI_BIT)&1)==0);

	

}	


void i2c_stop(void)

{

	// issue stop condition

	I2CONSET=1<<STO_BIT;

  // clr SI bit status	

	I2CONCLR = 1<<SI_BIT;

	//stop will cleared automatically

	

}


u8 i2c_nack(void)

{	

	I2CONSET = 0x00; //Assert Not of Ack

  I2CONCLR = 1<<SI_BIT;

	while(((I2CONSET>>SI_BIT)&1)==0);

	return I2DAT;

}


u8 i2c_masterack(void)

{	

	I2CONSET = 0x04; //Assert Ack

  I2CONCLR = 1<<SI_BIT;

	while(((I2CONSET>>SI_BIT)&1)==0);

	I2CONCLR = 0x04; //Clear Assert Ack

 	return I2DAT;

}	

