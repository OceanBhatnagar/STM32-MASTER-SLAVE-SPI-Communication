
#ifndef INC_SPI_DRIVER_H_
#define INC_SPI_DRIVER_H_

#include<stdint.h>
#include<stm32f410rb.h>

//SPI Pin Configuration

typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_DFF;
	uint8_t SPI_CPHA;
	uint8_t SPI_CPHO;
	uint8_t SPI_SSM;
	uint8_t SPI_Speed;
}SPI_Config_t;

//SPI HANDLE

typedef struct{
	SPI_REGDEF_t *pSPIx;
	SPI_Config_t SPI_CONFIG;
}SPI_HANDLE_t;

//API Prototype

//Initialization
void SPI_init(SPI_HANDLE_t *SPIHandle);

//SPI PERIPHERAL ENABLE
void SPI_PeripheralControl(SPI_REGDEF_t *pSPIx,uint8_t EnorDi);

//SSI CONFIG FOR SOFTWARE PIN MANAGEMENT
void SSI_config(SPI_REGDEF_t *pSPIx,uint8_t EnorDi);
//SSOE FOR NSS
void SSOE_config(SPI_REGDEF_t *pSPIx,uint8_t EnorDi);

// DATA SEND AND RECEIVE
void SPI_SEND_DATA(SPI_REGDEF_t *pSPIx,uint8_t *TX_Buffer,uint32_t Len);

void SPI_RECEIVE_DATA(SPI_REGDEF_t *pSPIx,uint8_t *RX_Buffer,uint32_t Len);

//INTERRUPT
void SPI_IRQCONFIG(uint8_t IRQNO,uint8_t EnableDisable);
void SPI_IRQHandling(SPI_HANDLE_t *SPIHandle);
void SPI_IRQPriority(uint32_t IRQNumber,uint8_t Priority);

void SPI_SEND_DATA_INTERRUPT(SPI_HANDLE_t *SPIHandle,uint8_t *TX_Buffer,uint32_t Len);

void SPI_RECEIVE_DATA_INTERRUPT(SPI_HANDLE_t *SPIHandle,uint8_t *RX_Buffer,uint32_t Len);
//SPI MACROS IN SPI control register 1

//DEVICE MODE
#define SPI_MASTER_MODE 1
#define SPI_SLAVE_MODE 0

//BUS_CONFIG
#define SPI_FULL_DUPLEX  1
#define SPI_HALF_DUPLEX  2
#define SPI_SIMPLEX_RX   3


//SPEED
#define SPI_SCLK_DIV2     1
#define SPI_SCLK_DIV4     2
#define SPI_SCLK_DIV8     3
#define SPI_SCLK_DIV16    4
#define SPI_SCLK_DIV32    5
#define SPI_SCLK_DIV64    6
#define SPI_SCLK_DIV128   7
#define SPI_SCLK_DIV256   8
//DFF

#define SPI_DFF_8B 0
#define SPI_DFF_16B 1

//CPOL
#define SPI_CPOL_LOW 0
#define SPI_CPOL_HIGH 1

//CPHA
#define SPI_CPHA_LOW 0
#define SPI_CPHA_HIGH 1

//SSM
#define SSM_SOFTWARE 1
#define SSM_HARDWARE 0


uint8_t SPI_GETFLAG(SPI_REGDEF_t *pSPIx,uint32_t FlagName);
//SPI STATUS REGISTER
#define FLAG_RESET 0
#define FLAG_SET   1
#define SPI_TXE_FLAG  (1<<1)
#define SPI_RXE_FLAG  (1<<0)
#define SPI_BSY_FLAG  (1<<7)

#endif /* INC_SPI_DRIVER_H_ */
