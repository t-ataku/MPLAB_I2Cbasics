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
/**
 * I2C_HOST EXAMPLE Generated Driver File
 * 
 * @file i2c_host example.c
 * 
 * @ingroup i2c_host example
 * 
 * @version I2C_HOST EXAMPLE Example Version 1.0.1
 *
 * @brief Generated file for
 *        Example:           2. I2C IO Expander 1 - LEDs 
 *        Implementation:    Polled 
 *        Visualization:     None   
 *        MCU Device family: dsPIC
*/
/* ------------------------------------------------------------------
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/i2c_host/i2cX.h"  // TODO: Replace X with I2C instance number
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/timer/delay.h"

// Note:  MCP23008 - 8-Bit I2C I/O Expander with I2C (& SPI) Serial Interface(s) 
//        Reference to the MCP23008 data sheet:  https://www.microchip.com/DS20001919 
//        MCP23008 register addresses are in Table 1-2 (page 5) of the data sheet
//        The Curiosity Nano Explorer (EV58G97A) has 2 x MCP23008 IO Expanders

#define MCP23008_1_I2C_ADDRESS  ((uint8_t)0x25)
#define MCP23008_REG_ADDR_IODIR     0x00
#define MCP23008_REG_ADDR_GPIO      0x09
#define PINS_DIGITAL_OUTPUT         0x00
#define PINS_DIGITAL_HIGH           0xFF
#define PINS_DIGITAL_LOW            0x00
#define DATALENGTH                  2
#define I2C_ERROR_NONE              0

extern void DELAY_milliseconds(uint16_t milliseconds);
static uint8_t MCP23008_Write(uint8_t address, uint8_t reg, uint8_t data);
static uint16_t led_row_counter(void);

uint8_t errorState = I2C_HOST_ERROR_NONE;
static uint8_t *data;
static uint8_t *data_length;
static uint8_t pins = 0; 

static uint8_t MCP23008_Write(uint8_t address, uint8_t reg, uint8_t data)
{
    size_t txLength = 2;
    uint8_t txBuffer[2] = {0};

    txBuffer[0] = reg;
    txBuffer[1] = data;
    
    I2C_Host.Write(MCP23008_1_I2C_ADDRESS, txBuffer, txLength);
    while (I2C_Host.IsBusy())
    {
    }
    
    errorState = I2C_Host.ErrorGet();
    return errorState;
}


static uint16_t led_row_counter(void)
{
    for (pins = 0; pins < 64U; pins++)
    {
        // Invert the pins, since using pins 8 to 3, which are active low 
        uint8_t pins_inverted = ~(pins << 2); 
        errorState = MCP23008_Write(MCP23008_1_I2C_ADDRESS, MCP23008_REG_ADDR_GPIO, pins_inverted); 
        
        IO_LED_Toggle();
        DELAY_milliseconds(100);
    }
    return errorState;
}

int main(void)
{
    SYSTEM_Initialize();
    
    errorState = MCP23008_Write(MCP23008_1_I2C_ADDRESS, MCP23008_REG_ADDR_IODIR, PINS_DIGITAL_OUTPUT);
 
    errorState = led_row_counter(); 
    DELAY_milliseconds(1000);
   
    pins = (uint8_t) 0xFF; // Turn off active LOW LEDs
    errorState = MCP23008_Write(MCP23008_1_I2C_ADDRESS, MCP23008_REG_ADDR_GPIO, pins);    
   
    while(1)
    {
        errorState = MCP23008_Write(MCP23008_1_I2C_ADDRESS, MCP23008_REG_ADDR_GPIO, pins); 
        IO_LED_Toggle();
        DELAY_milliseconds(1000);
        pins = ~pins;   // Toggle LEDs
    }
}

------------------------------------------------------------------ */
