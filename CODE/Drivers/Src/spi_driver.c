
#include<spi_driver.h>
#include<stdint.h>

void SPI_init(SPI_HANDLE_t *SPIHandle){
	uint32_t temp=0;

	//DEVICE MODE
	temp |=SPIHandle->SPI_CONFIG.SPI_DeviceMode <<2;

	//BUS CONFIG
	if(SPIHandle->SPI_CONFIG.SPI_BusConfig==SPI_FULL_DUPLEX){
		temp &=~(1<<15);
	}
	else if(SPIHandle->SPI_CONFIG.SPI_BusConfig==SPI_HALF_DUPLEX){
		temp |=(1<<15);
	}
	else if(SPIHandle->SPI_CONFIG.SPI_BusConfig==SPI_SIMPLEX_RX){
		temp &=~(1<<15);
		temp |=(1<<10);
	}
	//SPEED
  temp |=SPIHandle->SPI_CONFIG.SPI_Speed<<3;

     //DFF
     temp |=SPIHandle->SPI_CONFIG.SPI_DFF<<11;

     //CPHA
     temp |=SPIHandle->SPI_CONFIG.SPI_CPHA<<0;
     //CPHO
     temp|=SPIHandle->SPI_CONFIG.SPI_CPHO<<1;
     //SSM
     temp |=SPIHandle->SPI_CONFIG.SPI_SSM<<9;

     SPIHandle->pSPIx->SPI_CR1=temp;
}

void SPI_PeripheralControl(SPI_REGDEF_t *pSPIx,uint8_t EnorDi){
	if(EnorDi==1){
		pSPIx->SPI_CR1 |=(1<<6);
	}
	else{
		pSPIx->SPI_CR1 &=~(1<<6);
	}
}

void SSI_config(SPI_REGDEF_t *pSPIx,uint8_t EnorDi){
	if(EnorDi==1){
			pSPIx->SPI_CR1 |=(1<<8);
		}
		else{
			pSPIx->SPI_CR1 &=~(1<<8);
		}
}

void SSOE_config(SPI_REGDEF_t *pSPIx,uint8_t EnorDi){
	if(EnorDi==1){
				pSPIx->SPI_CR2 |=(1<<2);
			}
			else{
				pSPIx->SPI_CR2 &=~(1<<2);
			}
}

uint8_t SPI_GETFLAG(SPI_REGDEF_t *pSPIx,uint32_t FlagName){
	if(pSPIx->SPI_SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_SEND_DATA(SPI_REGDEF_t *pSPIx,uint8_t *TX_Buffer,uint32_t Len){
	//CHECK LENGTH
	while(Len>0){
		//CHECK TX BUFFER
		while(SPI_GETFLAG(pSPIx,SPI_TXE_FLAG)==FLAG_RESET);
		//CHECK DFF
		if(pSPIx->SPI_CR1 & (1<<11)){
			//16BIT DFF
			//LOAD THE DATA INTO DATA REGISTER

			pSPIx->SPI_DR=*((uint16_t*)TX_Buffer);
			Len--;
			Len--;
			(uint16_t*)TX_Buffer++;
		}
		else{
			//8BIT DFF
			//LOAD THE DATA INTO DATA REGISTER

			pSPIx->SPI_DR=*TX_Buffer;
			Len--;
			Len--;
			(uint8_t*)TX_Buffer++;
		}
	}
}

void SPI_RECEIVE_DATA(SPI_REGDEF_t *pSPIx,uint8_t *RX_Buffer,uint32_t Len){
	//CHECK LENGTH
	while(Len>0){
		//CHECK RX BUFFER
		while(SPI_GETFLAG(pSPIx,SPI_RXE_FLAG)==FLAG_RESET);
		//CHECK DFF
		if(pSPIx->SPI_CR1 & (1<<11)){
			//16 BIT DFF
			//READ DATA FROM DATA REGISTER
			*((uint16_t*)RX_Buffer)=pSPIx->SPI_DR;
			Len--;
			Len--;
			(uint16_t*)RX_Buffer++;
		}
		else{
			//8BIT DFF
	      //LOAD THE DATA INTO DATA REGISTER
			*RX_Buffer=pSPIx->SPI_DR;
			Len--;
			(uint8_t*)RX_Buffer++;
		}
	}
}
//***************************************************************************************


void SPI_IRQCONFIG(uint8_t IRQNO,uint8_t EnableDisable){
	if(EnableDisable==1){
			if(IRQNO <=31){
				*NVIC_ISER0 |=(1<<IRQNO);
			}
			else if(IRQNO>31 && IRQNO<64){
				*NVIC_ISER1 |=(1<<(IRQNO%32));
			}
			else if(IRQNO>=64 && IRQNO<96){
				*NVIC_ISER2 |=(1<<(IRQNO%64));
			}
		}
		else{
			if(IRQNO <=31){
						*NVIC_ICER0 |=(1<<IRQNO);
					}
					else if(IRQNO>31 && IRQNO<64){
						*NVIC_ICER1 |=(1<<(IRQNO%32));
					}
					else if(IRQNO>=64 && IRQNO<96){
						*NVIC_ICER2 |=(1<<(IRQNO%64));
					}
				}
		}

void SPI_IRQPriority(uint32_t IRQNumber,uint8_t Priority){

	uint8_t irp=IRQNumber/4;
	uint8_t irp_section=IRQNumber%4;
	uint8_t Shift=(8*irp_section)+4;

	*(NVIC_Priority +(irp*4))|=(Priority<<Shift);

}

