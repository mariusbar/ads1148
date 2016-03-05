// ADS 1148 configuration

// Registers addresses
#define MUX0	0x00
#define VBIAS	0x01
#define MUX1	0x02
#define SYS0	0x03
#define OFC0	0x04
#define OFC1	0x05
#define OFC2	0x06
#define FSC0	0x07
#define FSC1	0x08
#define FSC2	0x09
#define IDAC0	0x0A
#define IDAC1	0x0B
#define GPIOCFG 0x0C
#define GPIODIR 0x0D
#define GPIODAT 0x0E

// SPI Commands
//System Control
#define WAKEUP 	0x00
#define SLEEP 	0x02
#define SYNC	 	0x04
#define RESET 	0x06
#define NOP	 	0xFF

//Data Read
#define RDATA	 	0x12
#define RDATAC 	0x14
#define SDATAC 	0x16

//Register Read / Write
#define RREG		0x20
#define WREG		0x40

//Calibration
#define SYSOCAL	0x60
#define SYSGCAL	0x61
#define SELFOCAL	0x62

// ADS1148 init data
#define ADS_INIT 

// MUX0 Config
#define MUX_CH0 0x01
#define MUX_CH1 0x13

// VBIAS Config
#define VBIAS_DIS 	0x00 // VBIAS disable

// MUX1 Config
#define MUX1_INTVREF	0x40// Internal voltage reference ON

// SYS0 Config
#define SYS0_P64_S5	0x60// PGA=64, SPS=5

// IDAC0 Config
#define IDAC0_DRDY_100uA	0x0A// DRDY On, IDAC=100uA
#define IDAC0_100uA	0x02// DRDY Off, IDAC=100uA

// IDAC1 Config
#define IDAC1_A0_A1	0x01// I1DIR0, I2DIR1
#define IDAC1_A2_A3	0x23// I1DIR2, I2DIR3

// Input channels
#define ADS_INPUTS 2

// SPI SCK pin lock down
#define ADC_SCK_PORT        CYGHWR_HAL_STM32_GPIOB// 
#define ADC_SCK_MASK    0x0000f000    // 
#define ADC_SCK_OUT    0x00002000     // Output configuration
#define ADC_SCK_ALT    0x00009000     // Alternate configuration 10MHz
#define ADC_SCK_PIN	0x00000008

#define ADC_SCK_CONF_OUT( _n_)                                  \
    CYG_MACRO_START                                             \
        cyg_uint32 _t_;                                         \
        HAL_READ_UINT32(ADC_SCK_PORT +        \
                        CYGHWR_HAL_STM32_GPIO_CRL, _t_);    \
	_t_ &= ~ADC_SCK_MASK;		\
        _t_ |= ADC_SCK_OUT;                                          \
        HAL_WRITE_UINT32(ADC_SCK_PORT +       \
                        CYGHWR_HAL_STM32_GPIO_CRL, _t_);    \
	CYG_MACRO_END
	
#define ADC_SCK_CONF_ALT( _n_)                                  \
    CYG_MACRO_START                                             \
        cyg_uint32 _t_;                                         \
        HAL_READ_UINT32(ADC_SCK_PORT +        \
                        CYGHWR_HAL_STM32_GPIO_CRL, _t_);    \
	_t_ &= ~ADC_SCK_MASK;		\
        _t_ |= ADC_SCK_ALT;                                          \
        HAL_WRITE_UINT32(ADC_SCK_PORT +       \
                        CYGHWR_HAL_STM32_GPIO_CRL, _t_);    \
	CYG_MACRO_END
	
#define OUT_RSET_ADC_SCK( _n_)                                  \
    CYG_MACRO_START                                             \
        cyg_uint32 _t_;                                         \
        HAL_READ_UINT32(ADC_SCK_PORT +        \
                        CYGHWR_HAL_STM32_GPIO_ODR, _t_);    \
	_t_ &=	~ADC_SCK_PIN;		\
        HAL_WRITE_UINT32(ADC_SCK_PORT +       \
                        CYGHWR_HAL_STM32_GPIO_ODR, _t_);    \
    CYG_MACRO_END

// Data declaration
externC cyg_spi_cortexm_stm32_bus_t cyg_spi_stm32_bus1;


//---------------------------------------------------------------------------
// SPI device driver data structures.

cyg_spi_cortexm_stm32_device_t ads1148 = {
    .spi_device.spi_bus = &cyg_spi_stm32_bus1.spi_bus,
    .dev_num = 0 ,                      // Only 1 device. 
    .cl_pol = 1,
    .cl_pha = 0,
    .cl_brate = 2000000,                // Nominal 8Mhz.
    .cs_up_udly = 1,
    .cs_dw_udly = 1,
    .tr_bt_udly = 1,
    .bus_16bit = false,
};


//---------------------------------------------------------------------------

char ads_tx_data[16] = {0x0F,0x0F};
char ads_rx_data [16];
cyg_bool polled=false;

char idac1_conf[ADS_INPUTS]={IDAC1_A0_A1,IDAC1_A2_A3};
char mux0_conf[ADS_INPUTS]={MUX_CH0,MUX_CH1};
int temper_channel[ADS_INPUTS];