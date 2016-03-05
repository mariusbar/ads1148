// File ads1148_conf.c


void ads1148_pwrup(void)
{
	OUT_RSET_ADS_RESET();
	cyg_thread_delay(1);
	OUT_SET_ADS_START();
	OUT_SET_ADS_RESET();
	
	cyg_thread_delay(16);
}

void ads1148_conf_read(void)
{// transfer all config registers ----------------------------------------------------------------------------------------------
const char ads_tx_data[8] = {(RREG | MUX0),5,NOP,NOP,NOP,NOP,NOP ,NOP};
//const char ads_tx_data[8] = {(RREG | OFC0),5,NOP,NOP,NOP,NOP,NOP ,NOP};
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 8, ads_tx_data, ads_rx_data, 1);
	cyg_thread_delay(1);	
}

void ads1148_rdata(void)
{// transfer all config registers ----------------------------------------------------------------------------------------------
const char ads_tx_data[3] = {(RDATA),NOP,NOP};
//const char ads_tx_data[8] = {(RREG | OFC0),5,NOP,NOP,NOP,NOP,NOP ,NOP};
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 3, ads_tx_data, ads_rx_data, 1);
	cyg_thread_delay(1);	
}

void ads1148_init(void)
{// transfer all config registers ----------------------------------------------------------------------------------------------
const char ads_tx_data[5] = {(WREG | VBIAS),2, VBIAS_DIS, MUX1_INTVREF, SYS0_P64_S5 };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 5, ads_tx_data, NULL, 1);
	cyg_thread_delay(1);	
}

void ads1148_sdatac(void)
{
const char ads_tx_data[1] = {SDATAC };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 1, ads_tx_data, NULL, 1);
	cyg_thread_delay(1);	
}

void ads1148_selfocal(void)
{
const char ads_tx_data[1] = {SELFOCAL };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 1, ads_tx_data, NULL, 1);
	cyg_thread_delay(4000);	
}

void ads1148_sysocal(void)
{
const char ads_tx_data[1] = {SYSOCAL };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 1, ads_tx_data, NULL, 1);
	cyg_thread_delay(4000);	
}

void ads1148_sysgcal(void)
{
const char ads_tx_data[1] = {SYSGCAL };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 1, ads_tx_data, NULL, 1);
	cyg_thread_delay(4000);	
}

void ads1148_conf_ch(char mux)
{// transfer all config registers ----------------------------------------------------------------------------------------------
const char ads_tx_data[3] = {(WREG | MUX0),0,mux };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 3, ads_tx_data, NULL, 1);
//	cyg_thread_delay(1);	
}

void ads1148_conf_ch0(void)
{// transfer all config registers ----------------------------------------------------------------------------------------------
const char ads_tx_data[3] = {(WREG | MUX0),0,MUX_CH0 };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 3, ads_tx_data, NULL, 1);
//	cyg_thread_delay(1);	
}

void ads1148_conf_ch1(void)
{// transfer all config registers ----------------------------------------------------------------------------------------------
const char ads_tx_data[3] = {(WREG | MUX0),0,MUX_CH1 };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 3, ads_tx_data, NULL, 1);
//	cyg_thread_delay(1);	
}

void ads1148_idac_ch(char idac)
{// transfer all config registers ----------------------------------------------------------------------------------------------
const char ads_tx_data[4] = {(WREG | IDAC0),1, IDAC0_DRDY_100uA, idac };// DRDY switched on
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 4, ads_tx_data, NULL, 1);
//	cyg_thread_delay(1);	
}

void ads1148_idac_ch0(void)
{// transfer all config registers ----------------------------------------------------------------------------------------------
const char ads_tx_data[4] = {(WREG | IDAC0),1, IDAC0_DRDY_100uA, IDAC1_A0_A1 };// DRDY switched on
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 4, ads_tx_data, NULL, 1);
//	cyg_thread_delay(1);	
}

void ads1148_conf_ch0_rd(void)
{
const char ads_tx_data[3] = {(WREG | MUX0),0,MUX_CH0 };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 3, ads_tx_data, ads_rx_data, 1);
//	cyg_thread_delay(1);
}

void ads1148_conf_ch1_rd(void)
{
const char ads_tx_data[3] = {(WREG | MUX0),0,MUX_CH1 };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 3, ads_tx_data, ads_rx_data, 1);
	cyg_thread_delay(1);	
}

void ads1148_conf_test(void)
{
const char ads_tx_data[5] = {(WREG | OFC0),2,0xFF,0xFF,0xFF };
cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 5, ads_tx_data, NULL, 1);
	cyg_thread_delay(1);	
}


void temperature(cyg_addrword_t data)
{
	int n,i;
	ads1148_pwrup();

	
cyg_spi_transaction_begin(&ads1148.spi_device);
	ads1148_init();
//	ads1148_selfocal();
//	ads1148_conf_read();
	ads1148_conf_ch0();
	ads1148_idac_ch0();
//	ads1148_sysocal();
//	ads1148_sysgcal();
//	ads1148_conf_test();
	
for(;;){
//	ads1148_conf_ch1_rd();
//	ads1148_conf_ch0_rd();
//	ads1148_conf_read();
//	ads1148_rdata();  // previous continuous read
	/*
	ads1148_conf_ch0();
	ads1148_idac_ch0();
	cyg_thread_delay(1);
	OUT_RSET_ADS_CS();
	cyg_thread_delay(1);
		
	IN_READ_ADS_MISO(n);
	while (n!=0)
	{
		cyg_thread_delay(1);
		IN_READ_ADS_MISO(n);
	}
	OUT_RSET_ADS_CS();
	ads1148_rdata();
	*/
	
	for (i=0;i<ADS_INPUTS;i++)
	{
		ads1148_conf_ch(mux0_conf[i]);
		ads1148_idac_ch(idac1_conf[i]);
		cyg_thread_delay(10);
		ADC_SCK_CONF_OUT();
		OUT_RSET_ADC_SCK();
		OUT_RSET_ADS_CS();
		cyg_thread_delay(10);
		IN_READ_ADS_MISO(n);
		while (n!=0)
		{
			cyg_thread_delay(1);
			IN_READ_ADS_MISO(n);
		}
		OUT_SET_ADS_CS();
		ADC_SCK_CONF_ALT();
		ads1148_rdata();
		temper_channel[i]=((((int)ads_rx_data[2])|(((int)ads_rx_data[1])<<8))-TEMPERAT_ZERO)*TEMPERAT_NUM/TEMPERAT_DEN;
		
	}
	
}
	
// Read back the status
//cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 1, NULL, ads_rx_data, 0);
//if (!ads_rx_data[0]) {
// Command failed, generate some extra ticks to drop the chip select
//cyg_spi_transaction_tick(&ads1148.spi_device, 0, 1);
//} else {
// Transfer the data, then read back the final status. The
// chip select should be dropped at the end of this.
//cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 4, ads_tx_data, NULL, 0);
//cyg_spi_transaction_transfer(&ads1148.spi_device, 0, 2, NULL, ads_rx_data, 1);
// Code for checking the final status should go here
//}
// Transaction complete so clean up
cyg_spi_transaction_end(&ads1148.spi_device);

	
}