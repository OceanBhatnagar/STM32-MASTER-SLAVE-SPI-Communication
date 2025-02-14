
#include<stm32f410rb.h>
#include<stdint.h>
#include<string.h>

//PB15  SPI2_MOSI
//PB14  SPI2_MISO
//PB12  SPI2_NSS
//PB13  SPI2_SCK
//ALT 5
void SPI2_GPIO_INIT(void){
	GPIO_HANDLE_t SPI_Pin;
	SPI_Pin.pGPIOx= GPIOB;
	SPI_Pin.GPIO_CONFIG_t.PinMode=GPIOMODE_AltFunction;
	SPI_Pin.GPIO_CONFIG_t.PinAltFunMode=5;
	SPI_Pin.GPIO_CONFIG_t.PinOPType=OUTPUT_PUSHPULL;
	SPI_Pin.GPIO_CONFIG_t.PinSpeed=SPEED_HIGH;
	SPI_Pin.GPIO_CONFIG_t.PinPuPdControl=NOPULL;

	//MOSI
	SPI_Pin.GPIO_CONFIG_t.PinNumber=15;
	GPIO_init(&SPI_Pin);

	//MISO
		//SPI_Pin.GPIO_CONFIG_t.PinNumber=14;
		//GPIO_init(&SPI_Pin);

	//NSS
			//SPI_Pin.GPIO_CONFIG_t.PinNumber=12;
			//GPIO_init(&SPI_Pin);
	//SCK
				SPI_Pin.GPIO_CONFIG_t.PinNumber=13;
				GPIO_init(&SPI_Pin);

}



void SPI1_INIT(void){
	SPI_HANDLE_t spiHandle;
	spiHandle.pSPIx=SPI2;
	spiHandle.SPI_CONFIG.SPI_BusConfig=SPI_FULL_DUPLEX;
	spiHandle.SPI_CONFIG.SPI_DeviceMode=SPI_MASTER_MODE;
	spiHandle.SPI_CONFIG.SPI_Speed=SPI_SCLK_DIV2;
	spiHandle.SPI_CONFIG.SPI_DFF=SPI_DFF_8B;
	spiHandle.SPI_CONFIG.SPI_CPHO=SPI_CPOL_LOW;
	spiHandle.SPI_CONFIG.SPI_CPHA=SPI_CPHA_LOW;
	spiHandle.SPI_CONFIG.SPI_SSM=SSM_SOFTWARE;

	SPI_init(&spiHandle);
}
int main(){

	char user[]="Hello";
	//RCC GPIO
	uint32_t *RCC=(uint32_t*)0x40023830;
	*RCC=*RCC & ~(1<<1);
	*RCC=*RCC | (1<<1);

	//GPIO AS SPI PINS
	SPI2_GPIO_INIT();

	//RCC SPI
	uint32_t *RCC_SPI=(uint32_t*)0x40023840;
	*RCC_SPI=*RCC_SPI & ~(1<<14);
	*RCC_SPI=*RCC_SPI | (1<<14);

	//SPI INITIALIZATION
	SPI1_INIT();

	//SPI ENABLE
	SPI_PeripheralControl(SPI2,1);
	SSI_config(SPI2,1);
	//SPI SEND DATA
	SPI_SEND_DATA(SPI2,(uint8_t*)user,strlen(user));
	//SPI DISABLE
	SPI_PeripheralControl(SPI2,0);
    while(1);

return 0;
}
