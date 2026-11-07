/*
? [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/i2c_host/i2c1.h"  // TODO: Replace X with I2C instance number
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/timer/delay.h"

// Note:  MCP23008 - 8-Bit I2C I/O Expander with I2C (& SPI) Serial Interface(s) 
//        Reference to the MCP23008 data sheet:  https://www.microchip.com/DS20001919 
//        MCP23008 register addresses are in Table 1-2 (page 5) of the data sheet
//        The Curiosity Nano Explorer (EV58G97A) has 2 x MCP23008 IO Expanders

// ADDR = bit6 bit5 bit4:bit3 bit2 bit1 bit0
#define I2C_ADDRESS_1  ((uint8_t)0x55)
#define I2C_ADDRESS_2  ((uint8_t)0x2A)
#define I2C_ERROR_NONE              0

uint8_t errorState = I2C_HOST_ERROR_NONE;

static uint8_t I2C_Write(uint8_t address, uint8_t data)
{
    uint8_t txBuffer[1] = {0};
    size_t txLength = sizeof txBuffer / sizeof txBuffer[0];

    txBuffer[0] = data;
    
    I2C_Host.Write(address, txBuffer, txLength);
    while (I2C_Host.IsBusy())
    {
        IO_LED_Toggle();
    }
    
    errorState = I2C_Host.ErrorGet();
    return errorState;
}

static uint8_t I2C_Read(uint8_t address)
{
    uint8_t txBuffer[1] = {0};
    size_t txLength = sizeof txBuffer / sizeof txBuffer[0];

    I2C_Host.Read(address, txBuffer, txLength);
    while (I2C_Host.IsBusy())
    {
        IO_LED_Toggle();
    }
    
    errorState = I2C_Host.ErrorGet();
    return errorState;
}

int main(void)
{
    int pins = 0;
    
    SYSTEM_Initialize();
    
    while(1)
    {
        if (pins++ % 2)
            errorState = I2C_Write(I2C_ADDRESS_1, 0);
        else
            errorState = I2C_Read(I2C_ADDRESS_2); 
        IO_LED_Toggle();
        DELAY_milliseconds(1000);
    }
}
