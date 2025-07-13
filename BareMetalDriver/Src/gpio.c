#include <stdint.h>
#include "gpio.h"
#include <string.h>

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi){
    if(EnOrDi == ENABLE){
        if(pGPIOx == GPIOA){
            GPIOA_CLK_ENABLE();
        }else if(pGPIOx == GPIOB){
            GPIOB_CLK_ENABLE();
        }else if(pGPIOx == GPIOC){
            GPIOC_CLK_ENABLE();
        }else if(pGPIOx == GPIOD){
            GPIOD_CLK_ENABLE();
        }else if(pGPIOx == GPIOE){
            GPIOE_CLK_ENABLE();
        }else if(pGPIOx == GPIOF){
            GPIOF_CLK_ENABLE();
        }else if(pGPIOx == GPIOG){
            GPIOG_CLK_ENABLE();
        }else if(pGPIOx == GPIOH){
            GPIOH_CLK_ENABLE();
        }
    }else {
        if(pGPIOx == GPIOA){
            GPIOA_CLK_DISABLE();
        }else if(pGPIOx == GPIOB){
            GPIOB_CLK_DISABLE();
        }else if(pGPIOx == GPIOC){
            GPIOC_CLK_DISABLE();
        }else if(pGPIOx == GPIOD){
            GPIOD_CLK_DISABLE();
        }else if(pGPIOx == GPIOE){
            GPIOE_CLK_DISABLE();
        }else if(pGPIOx == GPIOF){
            GPIOF_CLK_DISABLE();
        }else if(pGPIOx == GPIOG){
            GPIOG_CLK_DISABLE();
        }else if(pGPIOx == GPIOH){
            GPIOH_CLK_DISABLE();
        }
    }
}
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
    uint32_t temp;
    //1.config mode
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ANALOG){
        //non interupt mode
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
        pGPIOHandle->pGPIOx->MODER |= temp;
    }else {
        //interupt mode
        //1. enable detection change from Input signal
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ITFT ){
            //1.config ftsr
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //clear responding rtsr bit
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ITRT){
            //1.config rtsr
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //clear responding ftsr bit
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_RFT){
            //1.config rtsr and ftsr
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        //2. config port selection in SYSCFG_EXTICR
        //select PoRT A or B or C to take over exti line
        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
        uint8_t portcode = GPIOB_BASE_ADDRESS_TO_CODE(pGPIOHandle->pGPIOx);
        SYSCFG_CLK_ENABLE();
        SYSCFG->EXTICR[temp1] |= (portcode << (4 * temp2));
        //3. enable exti interupt using IMR
        //mask request irq
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    temp = 0;
    //2.config speed
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    temp = 0;
    //3.config output type
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOutputType<< (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    temp = 0;
    //4.config pull up pull down
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PullUpPullDown << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
    pGPIOHandle->pGPIOx->PUPDR |= temp;
    //5.config alternate function

    temp = 0;
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
        //note GPIO_AFRH & GPIO_AFRL both contain 8 pins
        uint32_t temp1, temp2;
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%8;
        if(temp1 == 0){
            pGPIOHandle->pGPIOx->AFRL &= ~(0xF << (4 * temp2));//clearing
            pGPIOHandle->pGPIOx->AFRL |= (pGPIOHandle->GPIO_PinConfig.GPIO_AltFuncMode << (4 * temp2));
        }else if(temp1 == 1){
            pGPIOHandle->pGPIOx->AFRH &= ~(0xF << (4 * temp2));//clearing
            pGPIOHandle->pGPIOx->AFRH |= (pGPIOHandle->GPIO_PinConfig.GPIO_AltFuncMode << (4 * temp2));
        }
    }
}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
    if(pGPIOx == GPIOA){
        GPIOA_RESET();
    }else if(pGPIOx == GPIOB){
        GPIOB_RESET();
    }else if(pGPIOx == GPIOC){
        GPIOC_RESET();
    }else if(pGPIOx == GPIOD){
        GPIOD_RESET();
    }else if(pGPIOx == GPIOE){
        GPIOE_RESET();
    }else if(pGPIOx == GPIOF){
        GPIOF_RESET();
    }else if(pGPIOx == GPIOG){
        GPIOG_RESET();
    }else if(pGPIOx == GPIOH){
        GPIOH_RESET();
    }
}
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber){
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> GPIO_PinNumber) & 0x01);
    return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
    uint16_t value;
    value = (uint16_t)pGPIOx->IDR;
    return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber, uint8_t value){
    if(value == GPIO_PIN_SET){
        pGPIOx->ODR |= (1 << GPIO_PinNumber);
    }else{
        pGPIOx->ODR &= ~(1 << GPIO_PinNumber);
    }
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value){
    pGPIOx->ODR = value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber){
    pGPIOx->ODR ^= (1 << GPIO_PinNumber);
}
void GPIO_IRQConfiguration(uint8_t IRQNumber,  uint8_t EnorDi){
    if(EnorDi == ENABLE){
        if(IRQNumber <= 31){
            //program ISR0 Register
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64){
            //program ISR1 Register
            *NVIC_ISER1 |= (1 << IRQNumber);
        }
        else if(IRQNumber >= 64 && IRQNumber <= 96){
            //program ISR2 Register
        }    *NVIC_ISER3 |= (1 << IRQNumber);
    }else{
        if(IRQNumber <= 31){
            //program ICE0 Register
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64){
            //program ICE1 Register
            *NVIC_ICER1 |= (1 << IRQNumber);

        }
        else if(IRQNumber >= 64 && IRQNumber <= 96){
            //program CE2  Register
            *NVIC_ICER3 |= (1 << IRQNumber);
        }
    }
}

void GPIO_IRQInterruptConfiguration(uint8_t IRQPriority, uint8_t PinNumber){
    //1. find out IPR register
    uint8_t iprx = IRQPriority/4;
    uint8_t iprx_section = IRQPriority%4;
    uint8_t shift_amount = iprx_section*8 + ( 8 - NO_PR_BITS_IMPLEMENTED );
    *(NVIC_PR_BASE_ADDRESS +(iprx*4)) |= (IRQPriority << shift_amount);

}
void GPIO_IRQHandling(uint8_t PinNumber){
    //clear exti pr register corresponding to pin number
    if(EXTI->PR & (1 << PinNumber)){
        EXTI->PR |= (1 << PinNumber);
    }
}

