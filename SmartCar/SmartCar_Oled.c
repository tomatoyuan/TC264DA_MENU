/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            SmartCar_Encoder
 * @company         哈工大智能车创新俱乐部
 * @author          李洋 qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2021-2-05
 *
 * @note：oled显示
 *      RES:P15_1    DC:P15_0   其他CS/MOSI/MISO/CLK根据具体选用QSPI模组选择

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#include "SmartCar_Oled.h"

IfxQspi_SpiMaster oled_spi;
IfxQspi_SpiMaster_Channel oled_spiChannel;
#define SPI_BUFFER_SIZE 8       //缓存数据大小
uint8    spiTxBuffer[SPI_BUFFER_SIZE];
uint8    spiRxBuffer[SPI_BUFFER_SIZE];

void SmartCar_Oled_Config_Init()
{
    IfxCpu_disableInterrupts();
    IfxQspi_SpiMaster_Config oled_spiMasterConfig;
    IfxQspi_SpiMaster_initModuleConfig(&oled_spiMasterConfig, &OLED_QSPI_MODULE);
    oled_spiMasterConfig.base.mode  = SpiIf_Mode_master;
    oled_spiMasterConfig.base.maximumBaudrate  = 10000000;
    oled_spiMasterConfig.base.txPriority       = IFX_INTPRIO_DMA_CH1;
    oled_spiMasterConfig.base.rxPriority       = IFX_INTPRIO_DMA_CH2;
    oled_spiMasterConfig.base.erPriority       = IFX_INTPRIO_QSPI0_ER;
    oled_spiMasterConfig.dma.txDmaChannelId = IfxDma_ChannelId_23;
    oled_spiMasterConfig.dma.rxDmaChannelId = IfxDma_ChannelId_24;
    oled_spiMasterConfig.dma.useDma = 1;
    const IfxQspi_SpiMaster_Pins qspi_pins = {
        &OLED_CLK_PIN, IfxPort_OutputMode_pushPull, // SCLK
        &OLED_MTSR_PIN, IfxPort_OutputMode_pushPull, // MTSR
        &OLED_MRST_PIN, IfxPort_InputMode_pullDown,  // MRST IfxQspi2_MRSTA_P15_4_IN
        IfxPort_PadDriver_cmosAutomotiveSpeed3 // pad driver mode
    };
    oled_spiMasterConfig.pins = &qspi_pins;
    IfxQspi_SpiMaster_initModule(&oled_spi, &oled_spiMasterConfig);
    // create channel config
    IfxQspi_SpiMaster_ChannelConfig oled_spiMasterChannelConfig;
    IfxQspi_SpiMaster_initChannelConfig(&oled_spiMasterChannelConfig, &oled_spi);
    oled_spiMasterChannelConfig.base.baudrate = OLED_BAUDRATE;
    oled_spiMasterChannelConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleHigh;
    oled_spiMasterChannelConfig.base.mode.shiftClock = SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;
//    oled_spiMasterChannelConfig.base.mode.dataHeading = SpiIf_DataHeading_msbFirst;
//    oled_spiMasterChannelConfig.base.mode.dataWidth = 8;
//    oled_spiMasterChannelConfig.base.mode.csActiveLevel = Ifx_ActiveState_low;
    oled_spiMasterChannelConfig.base.mode.csLeadDelay = SpiIf_SlsoTiming_1;
    oled_spiMasterChannelConfig.base.mode.csTrailDelay = SpiIf_SlsoTiming_1;
    oled_spiMasterChannelConfig.base.mode.csInactiveDelay = SpiIf_SlsoTiming_1;
    // select pin configuration,这部分不可省略
    const IfxQspi_SpiMaster_Output slsOutput = {
        &OLED_CS_PIN,
        IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    oled_spiMasterChannelConfig.sls.output = slsOutput;
    //initialize channel
    IfxQspi_SpiMaster_initChannel(&oled_spiChannel, &oled_spiMasterChannelConfig);
        /*spi初始化结束*/
    IfxCpu_enableInterrupts();
    /*初始化res，dc*/
    IfxPort_setPinMode(&OLED_RES_PIN_MODULE, OLED_RES_PIN_NUM,  IfxPort_Mode_outputPushPullGeneral);//res,推挽式输出,初始化为高电平
    IfxPort_setPinPadDriver(&OLED_RES_PIN_MODULE, OLED_RES_PIN_NUM, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinHigh(&OLED_RES_PIN_MODULE, OLED_RES_PIN_NUM);
    IfxPort_setPinMode(&OLED_DC_PIN_MODULE, OLED_DC_PIN_NUM,  IfxPort_Mode_outputPushPullGeneral);//dc，推挽式输出,初始化为高电平
    IfxPort_setPinPadDriver(&OLED_DC_PIN_MODULE, OLED_DC_PIN_NUM, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinHigh(&OLED_DC_PIN_MODULE, OLED_DC_PIN_NUM);
    /*引脚res,dc初始化结束*/
}

void SmartCar_Oled_Init(void)
{
    int i =50;
    SmartCar_Oled_Config_Init();
    IfxPort_setPinHigh(&OLED_RES_PIN_MODULE, OLED_RES_PIN_NUM);
    while(i--){};
    IfxPort_setPinLow(&OLED_RES_PIN_MODULE, OLED_RES_PIN_NUM);
    i = 50;
    while(i--){};
    IfxPort_setPinHigh(&OLED_RES_PIN_MODULE, OLED_RES_PIN_NUM);
    OLED_WrtCmd(0xae); //--turn off oled panel
    OLED_WrtCmd(0x00); //---set low column address
    OLED_WrtCmd(0x10); //---set high column address
    OLED_WrtCmd(0x40); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrtCmd(0x81); //--set contrast control register
    OLED_WrtCmd(0xcf); // Set SEG Output Current OLED_SSD1306_Brightness
    OLED_WrtCmd(0xa1);
    OLED_WrtCmd(0xc8);

    OLED_WrtCmd(0xa6); //--set normal display
    OLED_WrtCmd(0xa8); //--set multiplex ratio(1 to 64)
    OLED_WrtCmd(0x3f); //--1/64 duty
    OLED_WrtCmd(0xd3); //-set display offset  Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WrtCmd(0x00); //-not offset
    OLED_WrtCmd(0xd5); //--set display clock divide ratio/oscillator frequency
    OLED_WrtCmd(0x80); //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrtCmd(0xd9); //--set pre-charge period
    OLED_WrtCmd(0xf1); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrtCmd(0xda); //--set com pins hardware configuration
    OLED_WrtCmd(0x12);
    OLED_WrtCmd(0xdb); //--set vcomh
    OLED_WrtCmd(0x40); //Set VCOM Deselect Level
    OLED_WrtCmd(0x20); //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrtCmd(0x02); //
    //OLED_WRTCMD(0x00);//@ C.M. change to page address mode. enable frame buffer.
    OLED_WrtCmd(0x8d); //--set Charge Pump enable/disable
    OLED_WrtCmd(0x14); //--set(0x10) disable
    OLED_WrtCmd(0xa4); // Disable Entire Display On (0xa4/0xa5)
    OLED_WrtCmd(0xa6); // Disable Inverse Display On (0xa6/a7)
    OLED_WrtCmd(0xaf); //--turn on oled panel
    SmartCar_OLED_Fill(0x00);
    //SmartCar_OLED_Fill(0xff);
    OLED_Set_Pos(0,0);
}

void OLED_WrtCmd(uint8 cmd)
{
    int i =0;
    spiTxBuffer[i] = cmd;
    while( IfxQspi_SpiMaster_getStatus(&oled_spiChannel) == SpiIf_Status_busy );
    IfxPort_setPinLow(&OLED_DC_PIN_MODULE, OLED_DC_PIN_NUM);
    IfxQspi_SpiMaster_exchange(&oled_spiChannel, &spiTxBuffer[i], NULL_PTR, 1U);
}

void OLED_WrtData(uint8 data)
{
    int i =0;
    spiTxBuffer[i] = data;
    while( IfxQspi_SpiMaster_getStatus(&oled_spiChannel) == SpiIf_Status_busy );
    IfxPort_setPinHigh(&OLED_DC_PIN_MODULE, OLED_DC_PIN_NUM);
    IfxQspi_SpiMaster_exchange(&oled_spiChannel, &spiTxBuffer[i], NULL_PTR, 1U);
}

void SmartCar_OLED_Fill(uint8 bmp_data)
{
    uint8 y, x;

    for (y = 0; y < 8; y++)
    {
        OLED_WrtCmd(0xb0 + y);
        OLED_WrtCmd(0x01);
        OLED_WrtCmd(0x10);
        for (x = 0; x < 128; x++)   OLED_WrtData(bmp_data);
    }
}

void OLED_Set_Pos(uint8 x,uint8 y)
{
    OLED_WrtCmd(0xb0+y);
    OLED_WrtCmd(((x & 0xf0)>>4)|0x10);
    OLED_WrtCmd((x & 0x0f)|0x00);
}

void OLED_PutPixel(uint8 x, uint8 y, uint8 data)
{
    OLED_Set_Pos(x, y);
    OLED_WrtCmd(0xb0 + y);
    OLED_WrtCmd(((x&0xf0) >> 4) | 0x10);
    OLED_WrtCmd((x&0x0f) | 0x00);
    OLED_WrtData(data);
}

void OLED_ClrPixel(uint8 x,uint8 y)
{
    OLED_Set_Pos(x, y);
    OLED_WrtCmd(0xb0 + y);
    OLED_WrtCmd(((x&0xf0) >> 4) | 0x10);
    OLED_WrtCmd((x&0x0f) | 0x00);
    OLED_WrtData(0x00);
}

void SmartCar_OLED_P6x8Str(uint8 x, uint8 y, const char* ch)
{
    uint8 c = 0;
    uint8 i = 0;
    uint8 j = 0;
    while(ch[j]!='\0')
    {
        c= ch[j] - 32;
        if(ch[j] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        if(x>126)
        {
            x = 0;
            y++;
        }
        if(y>7)
        {
            break;
        }
        OLED_Set_Pos(x, y);
        for(i = 0;i < 6;i++)
        {
            OLED_WrtData(font_6x8[c][i]);//填入数组
        }
        x += 6;
        j++;
    }
}

void SmartCar_OLED_P6x8Reverse(uint8 x, uint8 y,const char* ch)
{
    uint8 c = 0;
    uint8 i = 0;
    uint8 j = 0;
    while(ch[j]!='\0')
    {
        c= ch[j] - 32;
        if(ch[j] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        if(x>126)
        {
            x = 0;
            y++;
        }
        if(y>7)
        {
            break;
        }
        OLED_Set_Pos(x, y);
        for(i = 0;i < 6;i++)
        {
            OLED_WrtData(~font_6x8[c][i]);//反色显示
        }
        x += 6;
        j++;
    }
}

void SmartCar_OLED_P8x16Str(uint8 x, uint8 y, const char* ch)
{
    uint8 c = 0;
    uint8 i = 0;
    uint8 j = 0;
    while(ch[j] != '\0')
    {
        c = ch[j] - 32;
        if(ch[j] == '\n')
        {
            y += 2;
            x = 0;
            continue;
        }
        if(x>120)
        {
            x = 0;
            y += 2;
        }
        if(y > 6)
        {
            break;
        }
        OLED_Set_Pos(x, y);
        for(i = 0;i<8;i++)
        {
            OLED_WrtData(font_8x16[c][i]);//填入数组
        }
        OLED_Set_Pos(x, y+1);
        for(i = 0;i<8;i++)
        {
            OLED_WrtData(font_8x16[c][i+8]);//填入数组
        }
        x += 8;
        j++;
    }
}


void SmartCar_OLED_Printf6x8(uint8 x, uint8 y, const char* ftm, ...)
{
    va_list args;
    va_start(args, ftm);
    char buf[64] = {0};
    vsnprintf(buf, 64, ftm, args);
    SmartCar_OLED_P6x8Str(x, y, buf);
}

void SmartCar_OLED_Printf8x16(uint8 x,uint8 y, const char* ftm, ...)
{
    va_list args;
    va_start(args, ftm);
    char buf[64] = {0};
    vsnprintf(buf, 64, ftm, args);
    SmartCar_OLED_P8x16Str(x, y, buf);
}
void SmartCar_Buffer_Upload(const uint8 *buffer)
{
    const uint8 *ptr = buffer;
    for (uint8 y = 0; y < 8; ++y)
    {
        OLED_WrtCmd(0xb0 + y);
        OLED_WrtCmd(0x01);
        OLED_WrtCmd(0x10);

       for (uint8 x = 0; x < 128; x++)
           OLED_WrtData(*(ptr++)); //aka (y * 128 + x)

    }
}

void image_size_half_forOLED(uint8 *src, uint8 *dst, const uint16 row, const uint16 col)
{
    int col_half = col/2;

  for(uint16 rowt=0;rowt<row;rowt++)
  {
   int rowt_half = rowt/2;
    for(uint16 colt=0;colt<col;colt++)
    {
      if(rowt%2==0&&colt%2==0)
      {
           *(dst+ (rowt_half)*(col_half)+ colt/2  )    = *( src+rowt*col+colt );
      }
    }

  }

}

void dis_bmp(uint16 high, uint16 width, uint8 *p,uint8 value)
{
    uint16 i;
    uint16 j;
    uint16 temp;
    uint16 temp1;
    uint8 dat;


    temp1 = high%8;
    if(temp1 == 0) temp = high/8;
    else           temp = high/8+1;


    for(i=0; i<temp; i++)
    {
        OLED_Set_Pos(0,(uint8 )i);
        for(j=0; j<width; j++)
        {
            dat = 0;
            if( i<(temp-1) || !temp1 || temp1>=1)dat |= (*(p+i*8*width+j+width*0) > value? 1: 0)<<0;
            if( i<(temp-1) || !temp1 || temp1>=2)dat |= (*(p+i*8*width+j+width*1) > value? 1: 0)<<1;
            if( i<(temp-1) || !temp1 || temp1>=3)dat |= (*(p+i*8*width+j+width*2) > value? 1: 0)<<2;
            if( i<(temp-1) || !temp1 || temp1>=4)dat |= (*(p+i*8*width+j+width*3) > value? 1: 0)<<3;
            if( i<(temp-1) || !temp1 || temp1>=5)dat |= (*(p+i*8*width+j+width*4) > value? 1: 0)<<4;
            if( i<(temp-1) || !temp1 || temp1>=6)dat |= (*(p+i*8*width+j+width*5) > value? 1: 0)<<5;
            if( i<(temp-1) || !temp1 || temp1>=7)dat |= (*(p+i*8*width+j+width*6) > value? 1: 0)<<6;
            if( i<(temp-1) || !temp1 || temp1>=8)dat |= (*(p+i*8*width+j+width*7) > value? 1: 0)<<7;

            OLED_WrtData(dat);
        }
    }
}

void dis_IMG(uint16 high, uint16 width, uint8 *p)
{
    uint16 i;
    uint16 j;
    uint16 temp;
    uint16 temp1;
    uint8 dat;


    temp1 = high%8;
    if(temp1 == 0) temp = high/8;
    else           temp = high/8+1;


    for(i=0; i<temp; i++)
    {
        OLED_Set_Pos(0,(uint8 )i);
        for(j=0; j<width; j++)
        {
            dat = 0;
            //uint8 data_temp =
            if( i<(temp-1) || !temp1 || temp1>=1)
            {
                if(*(p+i*8*width+j+width*0)==1)
                {
                    dat |= 1<<0;
                }
                else
                {
                    dat |= 0<<0;
                }
            }
            if( i<(temp-1) || !temp1 || temp1>=2)
            {
                if(*(p+i*8*width+j+width*1)==1)
                                {
                                    dat |= 1<<1;
                                }
                                else
                                {
                                    dat |= 0<<1;
                                }
            }
            if( i<(temp-1) || !temp1 || temp1>=3)
            {
                if(*(p+i*8*width+j+width*2)==1)
                                {
                                    dat |= 1<<2;
                                }
                                else
                                {
                                    dat |= 0<<2;
                                }
            }
            if( i<(temp-1) || !temp1 || temp1>=4)
            {
                if(*(p+i*8*width+j+width*3)==1)
                                {
                                    dat |= 1<<3;
                                }
                                else
                                {
                                    dat |= 0<<3;
                                }            }
            if( i<(temp-1) || !temp1 || temp1>=5)
            {
                if(*(p+i*8*width+j+width*4)==1)
                                {
                                    dat |= 1<<4;
                                }
                                else
                                {
                                    dat |= 0<<4;
                                }            }
            if( i<(temp-1) || !temp1 || temp1>=6)
            {
                if(*(p+i*8*width+j+width*5)==1)
                                {
                                    dat |= 1<<5;
                                }
                                else
                                {
                                    dat |= 0<<5;
                                }            }
            if( i<(temp-1) || !temp1 || temp1>=7)
            {
                if(*(p+i*8*width+j+width*6)==1)
                                {
                                    dat |= 1<<6;
                                }
                                else
                                {
                                    dat |= 0<<6;
                                }            }
            if( i<(temp-1) || !temp1 || temp1>=8)
            {
                if(*(p+i*8*width+j+width*7)==1)
                                {
                                    dat |= 1<<7;
                                }
                                else
                                {
                                    dat |= 0<<7;
                                }
            }

            OLED_WrtData(dat);
        }
    }
}



