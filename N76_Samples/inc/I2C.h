#define regular_I2C_pins							0
#define alternate_I2C_pins							1

#define I2C_CLOCK												0x27 //Fclk = Fsys / (4*(prescalar + 1))

#define I2C_ACK													0
#define I2C_NACK												1

#define timeout_count										1000

void I2C_GPIO_Init(int mode);
void I2C_init(void);
void I2C_start(void);
void I2C_stop(void);
unsigned char I2C_read(unsigned char ack_mode);
void I2C_write(unsigned char value);
