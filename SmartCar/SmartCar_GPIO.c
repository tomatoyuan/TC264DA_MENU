/*
 * SmartCar_GPIO.c
 *
 *  Created on: 2021Äê1ÔÂ22ÈÕ
 *      Author: ËïÎ¨
 */

#include "SmartCar_GPIO.h"



void GPIO_Init(Ifx_P *port, uint8 pinIndex,GPIOMODE_enum pinmode,uint8 dat)
{
    IfxPort_Mode port_mode;
    switch(pinmode)
    {
        case NO_PULL:   port_mode = IfxPort_Mode_inputNoPullDevice;      break;
        case PULLUP:    port_mode = IfxPort_Mode_inputPullUp;            break;
        case PULLDOWN:  port_mode = IfxPort_Mode_inputPullDown;          break;
        case OPENDRAIN: port_mode = IfxPort_Mode_outputOpenDrainGeneral; break;
        case PUSHPULL:  port_mode = IfxPort_Mode_outputPushPullGeneral; break;
        default:        port_mode = IfxPort_Mode_outputPushPullGeneral;  break;
    }
    IfxPort_setPinMode(port, pinIndex, port_mode);
    IfxPort_setPinPadDriver(port, pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    if(pinmode == PUSHPULL || pinmode == OPENDRAIN)
    {
        if(dat) IfxPort_setPinHigh(port, pinIndex);
        else       IfxPort_setPinLow(port, pinIndex);
    }
}


void GPIO_Set(Ifx_P *port, uint8 pinIndex, uint8 dat)
{
    if(dat) IfxPort_setPinHigh(port, pinIndex);
    else    IfxPort_setPinLow(port, pinIndex);
}


uint8 GPIO_Read(Ifx_P *port, uint8 pinIndex)
{
    return IfxPort_getPinState(port, pinIndex);
}


void GPIO_Toggle(Ifx_P *port, uint8 pinIndex)
{
    IfxPort_togglePin(port, pinIndex);
}


