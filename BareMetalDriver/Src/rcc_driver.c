#include "rcc_driver.h"

uint32_t RCC_GetPLLOutputClock(void){
    return 8000000;
}

uint16_t AHB_Prescaler[8] = {2,4,8,16,64,128,256, 512};
uint16_t APB1_Prescaler[4] = {2,4,8,16};

uint16_t APB2_Prescaler[4] = {2,4,8,16};

uint32_t RCC_GetPCLK1Value(void){
    uint32_t pclk1, SystemClk;
    uint8_t clksrc, temp, ahbp, apb1p;

    //AHB
    //determind clock source: HSI, HSE, PLL
    clksrc = ((RCC->CFGR >> 2) & 0x3);

    if(clksrc == 0){//HSI
        SystemClk = 16000000;
    }
    else if(clksrc == 1){//HSE
        SystemClk = 8000000;
    }
    else{//PLL
        SystemClk = RCC_GetPLLOutputClock();
    }

    //AHB
    temp = ((RCC->CFGR >> 4) & 0xF);

    if(temp<8){
        ahbp = 1;
    } else {
        ahbp = AHB_Prescaler[temp-8];
    }

    //APB1
    temp = ((RCC->CFGR >> 10) & 0x7);
    if(temp<4){
        apb1p = 1;
    } else {
        apb1p = APB1_Prescaler[temp-4];
    }

    pclk1 = SystemClk / (apb1p*ahbp);
    return pclk1;
}

uint32_t RCC_GetPCLK2Value(void){
    uint32_t pclk2, SystemClk;
    uint8_t clksrc, temp, ahbp, apb2p;

    //AHB
    //determind clock source: HSI, HSE, PLL
    clksrc = ((RCC->CFGR >> 2) & 0x3);

    if(clksrc == 0){//HSI
        SystemClk = 16000000;
    }
    else if(clksrc == 1){//HSE
        SystemClk = 8000000;
    }
    else{//PLL
        SystemClk = RCC_GetPLLOutputClock();
    }

    //AHB
    temp = ((RCC->CFGR >> 4) & 0xF);

    if(temp<8){
        ahbp = 1;
    } else {
        ahbp = AHB_Prescaler[temp-8];
    }

    //APB2
    temp = ((RCC->CFGR >> 13) & 0x7);
    if(temp<4){
        apb2p = 1;
    } else {
        apb2p = APB2_Prescaler[temp-4];
    }

    pclk2 = SystemClk / (apb2p*ahbp);
    return pclk2;
}

