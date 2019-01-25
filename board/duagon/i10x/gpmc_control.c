#ifndef CONFIG_SPL_BUILD

#include <serial.h>

#define GPMC_BASE_CONTROL     0x50000000
#define GPMC_REVISION         (GPMC_BASE_CONTROL + 0x0)
#define GPMC_SYSCONFIG        (GPMC_BASE_CONTROL + 0x10)
#define GPMC_SYSSTATUS        (GPMC_BASE_CONTROL + 0x14)
#define GPMC_IRQSTATUS        (GPMC_BASE_CONTROL + 0x18)
#define GPMC_IRQENABLE        (GPMC_BASE_CONTROL + 0x1C)
#define GPMC_TIMEOUT_CONTROL  (GPMC_BASE_CONTROL + 0x40)
#define GPMC_ERR_ADDRESS      (GPMC_BASE_CONTROL + 0x44)
#define GPMC_ERR_TYPE         (GPMC_BASE_CONTROL + 0x48)
#define GPMC_CONFIG           (GPMC_BASE_CONTROL + 0x50)
#define GPMC_STATUS           (GPMC_BASE_CONTROL + 0x54)
#define GPMC_CONFIG1_0        (GPMC_BASE_CONTROL + 0x60)
#define GPMC_CONFIG2_0        (GPMC_BASE_CONTROL + 0x64)
#define GPMC_CONFIG3_0        (GPMC_BASE_CONTROL + 0x68)
#define GPMC_CONFIG4_0        (GPMC_BASE_CONTROL + 0x6C)
#define GPMC_CONFIG5_0        (GPMC_BASE_CONTROL + 0x70)
#define GPMC_CONFIG6_0        (GPMC_BASE_CONTROL + 0x74)
#define GPMC_CONFIG7_0        (GPMC_BASE_CONTROL + 0x78)
#define GPMC_NAND_COMMAND_0   (GPMC_BASE_CONTROL + 0x7C)
#define GPMC_NAND_ADDRESS_0   (GPMC_BASE_CONTROL + 0x80)
#define GPMC_NAND_DATA_0      (GPMC_BASE_CONTROL + 0x84)
#define GPMC_PREFETCH_CONFIG1 (GPMC_BASE_CONTROL + 0x1E0)
#define GPMC_PREFETCH_CONFIG2 (GPMC_BASE_CONTROL + 0x1E4)
#define GPMC_PREFETCH_CONTROL (GPMC_BASE_CONTROL + 0x1EC)
#define GPMC_PREFETCH_STATUS  (GPMC_BASE_CONTROL + 0x1F0)
#define GPMC_ECC_CONFIG       (GPMC_BASE_CONTROL + 0x1F4)
#define GPMC_ECC_CONTROL      (GPMC_BASE_CONTROL + 0x1F8)
#define GPMC_ECC_SIZE_CONFIG  (GPMC_BASE_CONTROL + 0x1FC)
#define GPMC_ECCj_RESULT      (GPMC_BASE_CONTROL + 0x200)
#define GPMC_BCH_RESULT0_1    (GPMC_BASE_CONTROL + 0x240)
#define GPMC_BCH_RESULT1_1    (GPMC_BASE_CONTROL + 0x244)
#define GPMC_BCH_RESULT2_1    (GPMC_BASE_CONTROL + 0x248)
#define GPMC_BCH_RESULT3_1    (GPMC_BASE_CONTROL + 0x24C)
#define GPMC_BCH_RESULT4_1    (GPMC_BASE_CONTROL + 0x300)
#define GPMC_BCH_RESULT5_1    (GPMC_BASE_CONTROL + 0x304)
#define GPMC_BCH_RESULT6_1    (GPMC_BASE_CONTROL + 0x308)
#define GPMC_BCH_SWDATA       (GPMC_BASE_CONTROL + 0x2D0)

#ifdef GPMC_DEBUG_CS
int print_GPMC_CONFIG_CS_register ( int CS_ID )
{
    /*Register value*/
    volatile unsigned int registerValue = 0;
    /*content value */
    unsigned int content = 0;
    
    if (CS_ID <0 || CS_ID> 6)
    {
        printf ( "print_GPMC_CONFIG_register (int CS_ID): CS_ID not in range [0..6]");
        return -1;
    }
    printf ("\nGPMC configuration for CSn (%i)\n", CS_ID);
    
    
/* GPMC_CONFIG1 */
    printf ("\nGPMC_CONFIG1(%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_CONFIG1_0 + CS_ID * 0x30));
    content = (registerValue & 0x80000000) >> 31;
    printf ("  WRAPBURST                 [0 | 1] = %2i: %s\n", content, content ? "Synchronous wrapping burst supported": "Synchronous wrapping burst not supported");
    content = (registerValue & 0x40000000) >> 30;
    printf ("  READMULTIPLE              [0 | 1] = %2i: %s\n", content, content ? "Multiple access (burst if synchonous, page if asynchronous)": "Single access");
    content = (registerValue & 0x20000000) >> 29;
    printf ("  READTYPE                  [0 | 1] = %2i: %s\n", content, content ? "Read Synchronous": "Read Asynchronous");
    content = (registerValue & 0x10000000) >> 28;
    printf ("  WRITEMULTIPLE             [0 | 1] = %2i: %s\n", content, content ? "Multiple access (burst if synchronous, considered as single if asynchronous)": "Single access");
    content = (registerValue & 0x08000000) >> 27;
    printf ("  WRITETYPE                 [0 | 1] = %2i: %s\n", content, content ? "Write Synchronous": "Write Asynchronous");
    content = (registerValue & 0x06000000) >> 25;
    printf ("  CLKACTIVATIONTIME         [0.. 3] = %2i: %s\n", content, (content == 3)?"Reserved":(content == 2)?"First rising edge of GPMC_CLK two GPMC_FCLK cycles after start access time":(content == 1)?"First rising edge of GPMC_CLK one GPMC_FCLK cycle after start access time": "First rising edge of GPMC_CLK at start access time"); 
    content = (registerValue & 0x01800000) >> 23;
    printf ("  ATTACHEDDEVICE_PAGELENGTH [0.. 3] = %2i: %s\n", content, (content == 3)?"Reserved":(content == 2)?"16 Words":(content == 1)?"8 Words": "4 Words");
    content = (registerValue & 0x00400000) >> 22;
    printf ("  WAITREADMONITORING        [0 | 1] = %2i: %s\n", content, content ? "WAIT pin is monitored for read accesses": "WAIT pin is not monitored for read accesses");
    content = (registerValue & 0x00200000) >> 21;
    printf ("  WAITWRITEMONITORING       [0 | 1] = %2i: %s\n", content, content ? "WAIT pin is monitored for write accesses": "WAIT pin is not monitored for write accesses");
    content = (registerValue & 0x00060000) >> 18;
    printf ("  WAITMONITORINGTIME        [0 | 1] = %2i: %s\n", content, (content == 3)?"Reserved":(content == 2)?"WAIt pin is monitored two GPMC_CLK cycle before valid data":(content == 1)?"WAIT pin is monitored one GPMC_CLK cycle before valid data": "WAIT pin is monitored with valid data");
    content = (registerValue & 0x00010000) >> 16;
    printf ("  WAITPINSELECT             [0.. 3] = %2i: %s\n", content, (content == 3)?"Reserved":(content == 2)?"Reserved":(content == 1)?"WAIT input pin is WAIT1": "WAIT input pin is WAIT0");
    content = (registerValue & 0x00003000) >> 12;
    printf ("  DEVICESIZE                [0.. 3] = %2i: %s\n", content, (content == 3)?"Reserved":(content == 2)?"Reserved":(content == 1)?"16 bit": "8 bit");
    content = (registerValue & 0x00000C00) >> 10;
    printf ("  DEVICETYPE                [0.. 3] = %2i: %s\n", content, (content == 3)?"Reserved":(content == 2)?"NAND Flash like devices, stream mode":(content == 1)?"Reserved": "NOR Flash like, asynchronous and synchronous devices");
    content = (registerValue & 0x00000300) >>  8;
    printf ("  MUXADDDATA                [0.. 3] = %2i: %s\n", content, (content == 3)?"Reserved":(content == 2)?"Address and data multiplexed attached device":(content == 1)?"AAD-multiplexed protocol device": "Non-multiplexed attached device");
    content = (registerValue & 0x00000010) >>  4;
    printf ("  TIMEPARA_GRANULARITY      [0 | 1] = %2i: %s\n", content, content ? "x2 latencies": "x1 latencies");
    content = (registerValue & 0x00000003) >>  0;
    printf ("  GPMCFCLKDIVIDER           [0.. 3] = %2i: %s\n", content, (content == 3)?"GPMC_CLK frequency = GPMC_FCLK frequency/4":(content == 2)?"GPMC_CLK frequency = GPMC_FCLK frequency/3":(content == 1)?"GPMC_CLK frequency = GPMC_FCLK frequency/2": "GPMC_CLK frequency = GPMC_FCLK frequency");


/* GPMC_CONFIG2 */
    printf ("\nGPMC_CONFIG2(%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_CONFIG2_0 + CS_ID * 0x30));
    content = (registerValue & 0x001F0000) >> 16;
    printf ("  CSWROFFTIME               [0..31] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    content = (registerValue & 0x00001F00) >>  8;
    printf ("  CSRDOFFTIME               [0..31] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    content = (registerValue & 0x00000080) >>  7;
    printf ("  CSEXTRADELAY              [0 | 1] = %2i: %s\n", content, content ? "CS i Timing control signal is delayed of half GPMC_FCLK clock cycle": "CS i Timing control signal is not delayed" );
    content = (registerValue & 0x0000000F) >>  0;
    printf ("  CSONTIME                  [0..15] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    
    
/* GPMC_CONFIG3 */
    printf ("\nGPMC_CONFIG3 (%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_CONFIG3_0 + CS_ID * 0x30));
    content = (registerValue & 0x70000000) >> 28;
    printf ("  ADVAADMUXWROFFTIME        [0.. 7] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x07000000) >> 24;
    printf ("  ADVAADMUXRDOFFTIME        [0.. 7] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x001F0000) >> 16;
    printf ("  ADVWROFFTIME              [0..31] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x00001F00) >>  8;
    printf ("  ADVRDOFFTIME              [0..31] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x00000080) >>  7;
    printf ("  ADVEXTRA_DELAY            [0 | 1] = %2i: %s\n", content, content ? "ADVn Timing control signal is delayed of half GPMC_FCLK clock cycle": "ADVn Timing control signal is not delayed" );
    content = (registerValue & 0x00000070) >>  4;
    printf ("  ADVAADMUXONTIME           [0.. 7] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x0000000F) >>  0;
    printf ("  ADVONTIME                 [0..15] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    
    
/* GPMC_CONFIG4 */
    printf ("\nGPMC_CONFIG4 (%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_CONFIG4_0 + CS_ID * 0x30));

    content = (registerValue & 0x1F000000) >> 24;
    printf ("  WEOFFTIME                 [0..31] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x00800000) >> 23;
    printf ("  WEEXTRADELAY              [0 | 1] = %2i: %s\n", content, content ?"WEn Timing control signal is delayed of half GPMC_FCLK clock cycle": "WEn Timing control signal is not delayed" );
    content = (registerValue & 0x000F0000) >> 16;
    printf ("  WEONTIME                  [0..15] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x0000E000) >> 13;
    printf ("  OEAADMUXOFFTIME           [0.. 7] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x00001F00) >> 8;
    printf ("  OEOFFTIME                 [0..31] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x00000080) >> 7;
    printf ("  OEEXTRA_DELAY             [0 | 1] = %2i: %s\n", content, content ?"OEn Timing control signal is delayed of half GPMC_FCLK clock cycle": "OEn Timing control signal is not delayed" );
    content = (registerValue & 0x00000070) >> 4;
    printf ("  OEAADMUXONTIME            [0.. 7] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    content = (registerValue & 0x0000000F) >> 0;
    printf ("  OEONTIME                  [0..15] = %2i: %s\n", content, "GPMC_FCLK cycle" );
    
    
/* GPMC_CONFIG5 */
    printf ("\nGPMC_CONFIG5 (%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_CONFIG5_0 + CS_ID* 0x30));

    content = (registerValue & 0x0F000000) >> 24;
    printf ("  PAGEBURSTACCESSTIME       [0..15] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    content = (registerValue & 0x001F0000) >> 16;
    printf ("  RDACCESSTIME              [0..31] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    content = (registerValue & 0x00001F00) >> 8;
    printf ("  WRCYCLETIME               [0..31] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    content = (registerValue & 0x0000001F) >> 0;
    printf ("  RDCYCLETIME               [0..31] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    
    
/* GPMC_CONFIG6 */
    printf ("\nGPMC_CONFIG6 (%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_CONFIG6_0 + CS_ID * 0x30));

    content = (registerValue & 0x1F000000) >> 24;
    printf ("  WRACCESSTIME              [0..31] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    content = (registerValue & 0x000F0000) >> 16;
    printf ("  WRDATAONADMUXBUS          [0..15] = %2i: %s\n", content, "GPMC_FCLK cycles (rising_edge)" );
    content = (registerValue & 0x00000F00) >> 8;
    printf ("  CYCLE2CYCLEDELAY          [0..15] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    content = (registerValue & 0x00000080) >> 7;
    printf ("  CYCLE2CYCLE_SAMECSEN      [0 | 1] = %2i: %s\n", content, content ? "Add CYCLE2CYCLEDELAY": "No delay between the two accesses" );
    content = (registerValue & 0x00000040) >> 6;
    printf ("  CYCLE2CYCLE_DIFFCSEN      [0 | 1] = %2i: %s\n", content, content ? "Add CYCLE2CYCLEDELAY": "No delay between the two accesses" );
    content = (registerValue & 0x0000000F) >> 0;
    printf ("  BUSTURNAROUND             [0..15] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    
    
/* GPMC_CONFIG7 */
    printf ("\nGPMC_CONFIG7 (%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_CONFIG7_0 + CS_ID * 0x30));
    
    content = (registerValue & 0x00000F00) >> 8;
    printf ("  MASKADDRESS               [0..15] = %2i: %s\n", content, (content == 15)?"16 MBytes":(content == 14)?"32 MBytes":(content == 12)?"64 MBytes":(content == 8)?"128 MBytes":(content == 0)?"256 MBytes": "not allowed" );
    content = (registerValue & 0x00000040) >> 6;
    printf ("  CSVALID                   [0 | 1] = %2i: %s\n", content, content ? "CSn enabled": "CSn disabled" );
    content = (registerValue & 0x0000003F) >> 0;
    printf ("  BASEADDRESS               [0..63] = %2i: %08x\n", content, content << 24 );
    return 0;
}
#endif

#ifdef GPMC_DEBUG_NAND
int print_GPMC_CONFIG_NAND_register ( int CS_ID )
{
/* Warning: Be careful the CPU crashes if GPMC CS and address ranged is not configured correctly. NAND access is generated if the following registers are read or written*/

    /*Register value*/
    volatile unsigned int registerValue = 0;
    /*content value */
    
    if (CS_ID <0 || CS_ID> 6)
    {
        printf ( "print_GPMC_CONFIG_NAND_register(int CS_ID): CS_ID not in range [0..6]");
        return -1;
    }
    printf ("\nGPMC NAND configuration for CSn (%i)\n", CS_ID);
    

/* GPMC_NAND_COMMAND */
    printf ("GPMC_NAND_COMMAND (%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_NAND_COMMAND_0 + CS_ID * 0x30));

    printf ("  GPMC_NAND_COMMAND         [ 4 G ] = 0x%08x\n", registerValue );
    

/* GPMC_NAND_ADDRESS */
    printf ("GPMC_NAND_ADDRESS (%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_NAND_ADDRESS_0 + CS_ID * 0x30));
    
    printf ("  GPMC_NAND_ADDRESS         [ 4 G ] = 0x%08x\n", registerValue );


/* GPMC_NAND_DATA */
    printf ("GPMC_NAND_DATA (%i)\n", CS_ID);
    registerValue = *((volatile unsigned int*)(GPMC_NAND_ADDRESS_0 + CS_ID * 0x30));

    printf ("  GPMC_NAND_DATA            [ 4 G ] = 0x%08x\n", registerValue );
    
    return 0;

}
#endif

#ifdef GPMC_DEBUG_BCH
int print_GPMC_CONFIG_BCH_register ( int BCH_ID )
{
    /*Register value*/
    volatile unsigned int registerValue = 0;
    /*content value */
    
    if (BCH_ID < 0 || BCH_ID > 6)
    {
        printf ( "print_GPMC_CONFIG_BCH_register (%i): BCH_ID not in range [0..6]\n", BCH_ID);
        return -1;
    }
    printf ("\nGPMC CONFIG BCH configuration for BCH_ID (%i)\n", BCH_ID);
    

/* GPMC_BCH_RESULT0 */
    registerValue = *((volatile unsigned int*)(GPMC_BCH_RESULT0_1 + BCH_ID * 0x10));
    printf ("  GPMC_BCH_RESULT0 (%i)     [ 4 G ] = 0x%08x\n", BCH_ID, registerValue );
    
/* GPMC_BCH_RESULT1 */
    registerValue = *((volatile unsigned int*)(GPMC_BCH_RESULT1_1 + BCH_ID * 0x10));
    printf ("  GPMC_BCH_RESULT1 (%i)     [ 4 G ] = 0x%08x\n", BCH_ID, registerValue );

/* GPMC_BCH_RESULT2 */
    registerValue = *((volatile unsigned int*)(GPMC_BCH_RESULT2_1 + BCH_ID * 0x10));
    printf ("  GPMC_BCH_RESULT2 (%i)     [ 4 G ] = 0x%08x\n", BCH_ID, registerValue );

/* GPMC_BCH_RESULT3 */
    registerValue = *((volatile unsigned int*)(GPMC_BCH_RESULT3_1 + BCH_ID * 0x10));
    printf ("  GPMC_BCH_RESULT3 (%i)     [ 4 G ] = 0x%08x\n", BCH_ID, registerValue );

/* GPMC_BCH_RESULT4 */
    registerValue = *((volatile unsigned int*)(GPMC_BCH_RESULT4_1 + BCH_ID * 0x10));
    printf ("  GPMC_BCH_RESULT4 (%i)     [ 4 G ] = 0x%08x\n", BCH_ID, registerValue );

/* GPMC_BCH_RESULT5 */
    registerValue = *((volatile unsigned int*)(GPMC_BCH_RESULT5_1 + BCH_ID * 0x10));
    printf ("  GPMC_BCH_RESULT5 (%i)     [ 4 G ] = 0x%08x\n", BCH_ID, registerValue );

/* GPMC_BCH_RESULT6 */
    registerValue = *((volatile unsigned int*)(GPMC_BCH_RESULT6_1 + BCH_ID * 0x10));
    printf ("  GPMC_BCH_RESULT6 (%i)     [ 4 G ] = 0x%08x\n", BCH_ID, registerValue );

    return 0;
}
#endif

#ifdef GPMC_DEBUG_general
int print_GPMC_CONFIG_register ( void )
{

    /*Register value*/
    volatile unsigned int registerValue = 0;
    /*content value */
    unsigned int content = 0;
    
    printf ("\nGPMC configuration register\n");
    

/* GPMC_REVISION */
    printf ("\nGPMC_REVISION\n");
    registerValue = *((volatile unsigned int*)(GPMC_REVISION));
    content = (registerValue & 0x000000F0) >> 4;
    printf ("  GPMC_REVISION             [fixed] = %01x.", content);
    content = (registerValue & 0x0000000F) >> 0;
    printf ("%01x\n", content );
    
/* GPMC_SYSCONFIG */
    printf ("\nGPMC_SYSCONFIG\n");
    registerValue = *((volatile unsigned int*)GPMC_SYSCONFIG);
    content = (registerValue & 0x00000018) >> 3;
    printf ("  SIDLEMODE                 [0.. 3] = %2i: %s\n", content, (content == 3) ? "Reserved" :(content == 2) ? "Smart-idle. Acknowledgement to an idle request is given based on the internal activity of themodule" :(content == 1) ? "No-idle. An idle request is never acknowledged" : "Force-idle. An idle request is acknowledged unconditionally" );
    content = (registerValue & 0x00000002) >> 1;
    printf ("  SOFTRESET                 [0 | 1] = %2i: %s\n", content, content ? "The module is reset" : "Normal mode" );
    content = (registerValue & 0x00000001) >> 0;
    printf ("  AUTOIDLE                  [0 | 1] = %2i: %s\n", content, content ? "Automatic Interface clock gating strategy is applied, based on the Interconnect activity" : "Interface clock is free-running" );

/* GPMC_SYSSTATUS */
    printf ("\nGPMC_SYSSTATUS\n");
    registerValue = *((volatile unsigned int*)(GPMC_SYSSTATUS));
    content = (registerValue & 0x00000001) >> 0;
    printf ("  RESETDONE                 [0 | 1] = %2i: %s\n", content, content ? "Reset completed": "Internal module reset in on-going" );
    
/* GPMC_IRQSTATUS */
    printf ("\nGPMC_IRQSTATUS\n");
    registerValue = *((volatile unsigned int*)(GPMC_IRQSTATUS));
    content = (registerValue & 0x00000200) >> 9;
    printf ("  WAIT1EDGE_DETECTIONSTATUS [0 | 1] = %2i: %s\n", content, content ? "A transition on WAIT1 input pin has been detected": "A transition on WAIT1 input pin has not been detected" );
    content = (registerValue & 0x00000100) >> 8;
    printf ("  WAIT0EDGE_DETECTIONSTATUS [0 | 1] = %2i: %s\n", content, content ? "A transition on WAIT0 input pin has been detected": "A transition on WAIT0 input pin has not been detected" );
    content = (registerValue & 0x00000002) >> 1;
    printf ("  TERMINAL_COUNTSTATUS      [0 | 1] = %2i: %s\n", content, content ? "Indicates that CountValue is equal to 0": "Indicates that CountValue is greater than 0" );
    content = (registerValue & 0x00000001) >> 0;
    printf ("  FIFOEVENT_STATUS          [0 | 1] = %2i: %s\n", content, content ? "Indicates available data bytes, check documentation.": "Indicates not enough available data bytes, check documentation." );

/* GPMC_IRQENABLE */
    printf ("\nGPMC_IRQENABLE\n");
    registerValue = *((volatile unsigned int*)(GPMC_IRQENABLE));
    content = (registerValue & 0x00000200) >> 9;
    printf ("  WAIT1EDGEDETECTIONENABLE  [0 | 1] = %2i: %s\n", content, content ? "Wait1EdgeDetection event generates an interrupt if occurs": "Wait1EdgeDetection interrupt is masked");
    content = (registerValue & 0x00000100) >> 8;
    printf ("  WAIT0EDGEDETECTIONENABLE  [0 | 1] = %2i: %s\n", content, content ? "Wait0EdgeDetection event generates an interrupt if occurs": "Wait0EdgeDetection interrupt is masked");
    content = (registerValue & 0x00000002) >> 1;
    printf ("  TERMINALCOUNTEVENTENABLE  [0 | 1] = %2i: %s\n", content, content ? "TerminalCountEvent interrupt is not masked": "TerminalCountEvent interrupt is masked");
    content = (registerValue & 0x00000001) >> 0;
    printf ("  FIFOEVENTENABLE           [0 | 1] = %2i: %s\n", content, content ? "FIFOEvent interrupt is not masked": "FIFOEvent interrupt is masked");

    
/* GPMC_TIMEOUT_CONTROL */
    printf ("\nGPMC_TIMEOUT_CONTROL\n");
    registerValue = *((volatile unsigned int*)(GPMC_TIMEOUT_CONTROL));
    content = (registerValue & 0x00001FF0) >> 4;
    printf ("  TIMEOUTSTARTVALUE         [0.511] = %2i: %s\n", content, "Start value of the time-out counter in GPMC.FCLK");
    content = (registerValue & 0x00000001) >> 0;
    printf ("  TIMEOUTENABLE             [0 | 1] = %2i: %s\n", content, content ? "TimeOut feature is enabled": "TimeOut feature is disabled");
    
/* GPMC_ERR_ADDRESS */
    printf ("\nGPMC_ERR_ADDRESS\n");
    registerValue = *((volatile unsigned int*)(GPMC_ERR_ADDRESS));
    content = (registerValue & 0x7fffffff) >> 0;
    printf ("  GPMC_ERR_ADDRESS          [ 2 G ] = 0x%08x: %s\n", content, "Address of illegal access: A30 (0 for memory region, 1 for GPMC register region) and A29-A0 (1GByte maximum)");
        
/* GPMC_ERR_TYPE */
    printf ("\nGPMC_ERR_TYPE\n");
    registerValue = *((volatile unsigned int*)(GPMC_ERR_TYPE));
    content = (registerValue & 0x00000700) >> 8;
    printf ("  ILLEGALMCMD               [0.. 7] = %2i: %s\n", content, "System Command of the transaction that caused the error" );
    content = (registerValue & 0x00000010) >> 4;
    printf ("  ERRORNOTSUPPADD           [0 | 1] = %2i: %s\n", content, content ? "The error is due to a non supported Address" : "No error occurs");
    content = (registerValue & 0x00000008) >> 3;
    printf ("  ERRORNOTSUPPMCMD          [0 | 1] = %2i: %s\n", content, content ? "The error is due to a non supported Command" : "No error occurs");
    content = (registerValue & 0x00000004) >> 2;
    printf ("  ERRORTIMEOUT              [0 | 1] = %2i: %s\n", content, content ? "The error is due to a time out" : "No error occurs");
    content = (registerValue & 0x00000001) >> 0;
    printf ("  ERRORVALID                [0 | 1] = %2i: %s\n", content, content ? "Error detected and logged in the other error fields" : "All error fields no longer valid");
    
/* GPMC_CONFIG */
    printf ("\nGPMC_CONFIG\n");
    registerValue = *((volatile unsigned int*)(GPMC_CONFIG));
    content = (registerValue & 0x00000200) >> 9;
    printf ("  WAIT1PINPOLARITY          [0 | 1] = %2i: %s\n", content, content ? "WAIT1 active high" : "WAIT1 active low" );
    content = (registerValue & 0x00000100) >> 8;
    printf ("  WAIT0PINPOLARITY          [0 | 1] = %2i: %s\n", content, content ? "WAIT0 active high" : "WAIT0 active low" );
    content = (registerValue & 0x00000010) >> 4;
    printf ("  WRITEPROTECT              [0 | 1] = %2i: %s\n", content, content ? "WPn output pin is high" : "WPn output pin is low" );
    content = (registerValue & 0x00000002) >> 1;
    printf ("  LIMITEDADDRESS            [0 | 1] = %2i: %s\n", content, content ? "1 Limited Address device support" : "0 Limited Address device support" );
    content = (registerValue & 0x00000001) >> 0;
    printf ("  NANDFORCEPOSTEDWRITE      [0 | 1] = %2i: %s\n", content, content ? "Enables Force Posted Write" : "Disables Force Posted Write" );
    
/* GPMC_STATUS */
    printf ("\nGPMC_STATUS\n");
    registerValue = *((volatile unsigned int*)(GPMC_STATUS));
    content = (registerValue & 0x00000020) >> 9;
    printf ("  EMPTYWRITEBUFFERSTATUS    [0 | 1] = %2i: %s\n", content, content ? "WAIT1 de-asserted" : "WAIT1 asserted (inactive state)" );
    content = (registerValue & 0x00000010) >> 8;
    printf ("  WAIT0STATUS               [0 | 1] = %2i: %s\n", content, content ? "WAIT0 de-asserted" : "WAIT0 asserted (inactive state)" );
    content = (registerValue & 0x00000001) >> 0;
    printf ("  WAIT1STATUS               [0 | 1] = %2i: %s\n", content, content ? "Write Buffer is empty" : "Write Buffer is not empty" );

    return 0;
}
#endif

#ifdef GPMC_DEBUG_PREFETCH
int print_GPMC_PREFETCH_register ( void )
{
    /*Register value*/
    volatile unsigned int registerValue = 0;
    /*content value */
    unsigned int content = 0;

/* GPMC_PREFETCH_CONFIG1 */
    printf ("\nGPMC_PREFETCH_CONFIG1\n");
    registerValue = *((volatile unsigned int*)(GPMC_PREFETCH_CONFIG1));
    content = (registerValue & 0x70000000) >> 28;
    printf ("  CYCLEOPTIMIZATION         [0...7] = %2i: %s\n", content, "GPMC_FCLK cycles" );
    content = (registerValue & 0x08000000) >> 27;
    printf ("  ENABLEOPTIMIZED_ACCESS    [0 | 1] = %2i: %s\n", content, content ? "Access cycle optimization is enabled" : "Access cycle optimization is disabled" );
    content = (registerValue & 0x07000000) >> 24;
    printf ("  ENGINECSSELECTOR          [0...7] = %2i: %s\n", content, "Selects the CS where Prefetch Postwrite engine is active" );
    content = (registerValue & 0x00800000) >> 23;
    printf ("  PFPWENROUNDROBIN          [0 | 1] = %2i: %s\n", content, content ? "Prefetch Postwrite engine round robin arbitration is enabled" : "Prefetch Postwrite engine round robin arbitration is disabled" );
    content = (registerValue & 0x000F0000) >> 16;
    printf ("  PFPWWEIGHTEDPRIO          [0..15] = %2i: %s\n", content, ( content == 0 ) ? "The next access is granted to the PFPW engine" : ("The next number of value accesses are granted to the PFPW engine") );
    content = (registerValue & 0x00007F00) >> 8;
    printf ("  FIFOTHRESHOLD             [0..64] = %2i %s\n", content, (content <=0x40)? "bytes": "illegal value" );
    content = (registerValue & 0x00000080) >> 7;
    printf ("  ENABLEENGINE              [0 | 1] = %2i: %s\n", content, content ? "Prefetch Postwrite engine is enabled" : "Prefetch Postwrite engine is disabled" );
    content = (registerValue & 0x00000030) >> 4;
    printf ("  WAITPINSELECTOR           [0...3] = %2i: %s\n", content, (content == 3 ) ? "Reserved" : (content == 2 ) ? "Reserved" : (content == 1 ) ? "Selects Wait1EdgeDetection" : "Selects WaitoEdgeDetection" );
    content = (registerValue & 0x00000008) >> 3;
    printf ("  SYNCHROMODE               [0 | 1] = %2i: %s\n", content, content ? "Engine starts the access to CS as soon as STARTENGINE is set AND wait to non wait edge detection on the selected wait pin" : "Engine starts the access to CS as soon as STARTENGINE is set" );
    content = (registerValue & 0x00000004) >> 2;
    printf ("  DMAMODE                   [0 | 1] = %2i: %s\n", content, content ? "DMA request synchronization is enabled. A DMA request protocol is used." : "Interrupt synchronization is enabled. Only interrupt line will be activated on FIFO threshold crossing." );
    content = (registerValue & 0x00000001) >> 0;
    printf ("  ACCESSMODE                [0 | 1] = %2i: %s\n", content, content ? "Write-posting mode" : "Prefetch read mode" );
    
/* GPMC_PREFETCH_CONFIG2 */
    printf ("\nGPMC_PREFETCH_CONFIG2\n");
    registerValue = *((volatile unsigned int*)(GPMC_PREFETCH_CONFIG2));

    content = (registerValue & 0x00003FFF) >> 0;
    printf ("  TRANSFERCOUNT             [0..8K] = %2i: %s\n", content, (content <= 8192 ) ? "Bytes" : "(illegal value)" );
    
/* GPMC_PREFETCH_CONTROL */
    printf ("\nGPMC_PREFETCH_CONTROL\n");
    registerValue = *((volatile unsigned int*)(GPMC_PREFETCH_CONTROL));

    content = (registerValue & 0x00000001) >> 0;
    printf ("  STARTENGINE               [0 | 1] = %2i: %s\n", content, content ? "Engine is running" : "Engine is stopped" );
    
/* GPMC_PREFETCH_STATUS */
    printf ("\nGPMC_PREFETCH_STATUS\n");
    registerValue = *((volatile unsigned int*)(GPMC_PREFETCH_STATUS));
    content = (registerValue & 0x7F000000) >> 24;
    printf ("  FIFOPOINTER               [0 | 1] = %2i: %s\n", content, (content <= 64)? "bytes available to be read or empty places to be written" : "(illegal value)" );
    content = (registerValue & 0x00010000) >> 16;
    printf ("  FIFOTHRESHOLDSTATUS       [0 | 1] = %2i: %s\n", content, content ? "FIFOPointer greater than FIFOThreshold. Writing to this bit has no effect" : "FIFOPointer smaller or equal to FIFOThreshold. Writing to this bit has no effect" );
    content = (registerValue & 0x00003FFF) >> 0;
    printf ("  COUNTVALUE                [0 | 1] = %2i: %s\n", content, (content <= 8192 ) ? "bytes remaining to be read or to be written" : "(illegal value)" );

    return 0;
}
#endif

#ifdef GPMC_DEBUG_ECC
int print_GPMC_ECC_register ( void )
{

    /*Register value*/
    volatile unsigned int registerValue = 0;
    /*content value */
    unsigned int content = 0;

/* GPMC_ECC_CONFIG */
    printf ("\nGPMC_ECC_CONFIG\n");
    registerValue = *((volatile unsigned int*)(GPMC_ECC_CONFIG));
    content = (registerValue & 0x00010000) >> 16;
    printf ("  ECCALGORITHM              [0 | 1] = %2i: %s\n", content, content ? "BCH code" : "Hamming code" );
    content = (registerValue & 0x00003000) >> 12;
    printf ("  ECCBCHTSEL                [0.. 3] = %2i: %s\n", content, (content == 3 )? "Reserved" :(content == 2 )? "Up to 16 bits error correction (t = 16)" :(content == 1 )? "Up to 8 bits error correction (t = 8)" : "Up to 4 bits error correction (t = 4)" );
    content = (registerValue & 0x00000F00) >> 8;
    printf ("  ECCWRAPMODE               [0..15] = %2i: %s\n", content, "Spare area organization definition for the BCH algorithm. See the BCH syndrome/parity calculator module functional specification for more details" );
    content = (registerValue & 0x00000080) >> 7;
    printf ("  ECC16B                    [0 | 1] = %2i: %s\n", content, content ? "ECC calculated on 16 columns" : "ECC calculated on 8 columns" );
    content = (registerValue & 0x00000070) >> 4;
    printf ("  ECCTOPSECTOR              [0.. 7] = %2i: %i sectors (total: %i kB page)", content, content + 1, (content + 1 ) * 512);
    content = (registerValue & 0x0000000E) >> 1;
    printf ("  ECCCS                     [0.. 7] = %2i: %s\n", content, (content<=6) ? "Chip select ID" : "Reserved" );
    content = (registerValue & 0x00000001) >> 0;
    printf ("  ECCENABLE                 [0 | 1] = %2i: %s\n", content, content ? "ECC enabled" : "ECC disabled" );
    
/* GPMC_ECC_CONTROL */
    printf ("\nGPMC_ECC_CONTROL\n");
    registerValue = *((volatile unsigned int*)(GPMC_ECC_CONTROL));

    content = (registerValue & 0x00000100) >> 8;
    printf ("  ECCCLEAR                  [0 | 1] = %2i: %s\n", content, content ? "(illegal value)" : "All reads return 0" );
    content = (registerValue & 0x0000000F) >> 0;
    printf ("  ECCPOINTER                [0..15] = %2i: %s\n", content, (content == 0)? "Writing 0 disables the ECC engine (ECCENABLE bit of GPMC_ECC_CONFIG cleared to 0)" : (content>9 )? "(ECC disabled)" : "ECC result register number selected");
    
/* GPMC_ECC_SIZE_CONFIG */
    printf ("\nGPMC_ECC_SIZE_CONFIG\n");
    registerValue = *((volatile unsigned int*)(GPMC_ECC_SIZE_CONFIG));

    content = (registerValue & 0x00000000) >> 22;
    printf ("  ECCSIZE1                  [0.255] = %2i: %2i Bytes\n", content, (content + 1) * 2);
    content = (registerValue & 0x00000000) >> 12;
    printf ("  ECCSIZE0                  [0.255] = %2i: %2i Bytes\n", content, (content + 1) * 2);
    content = (registerValue & 0x00000000) >> 8;
    printf ("  ECC9RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    content = (registerValue & 0x00000000) >> 7;
    printf ("  ECC8RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    content = (registerValue & 0x00000000) >> 6;
    printf ("  ECC7RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    content = (registerValue & 0x00000000) >> 5;
    printf ("  ECC6RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    content = (registerValue & 0x00000000) >> 4;
    printf ("  ECC5RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    content = (registerValue & 0x00000000) >> 3;
    printf ("  ECC4RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    content = (registerValue & 0x00000000) >> 2;
    printf ("  ECC3RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    content = (registerValue & 0x00000000) >> 1;
    printf ("  ECC2RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    content = (registerValue & 0x00000000) >> 0;
    printf ("  ECC1RESULTSIZE            [0 | 1] = %2i: %s\n", content, content ? "ECCSIZE1 selected" : "ECCSIZE0 selected" );
    
/* GPMC_ECCj_RESULT */
    int j = 1;
    for (j = 1; j <=9; j++ )
    {
        printf ("\nGPMC_ECCj_RESULT\n");
        registerValue = *((volatile unsigned int*)(GPMC_ECCj_RESULT));

        content = (registerValue & 0x0FF80000) >> 19;
        printf ("  Odd Row Parity            [0.. ] = 0x%03x: %s\n", content, "Odd Row Parity bits" );
        content = (registerValue & 0x00070000) >> 16;
        printf ("  Odd Column Parity         [0.. ] = 0x%01x: %s\n", content, "Odd Column Parity bits" );
        content = (registerValue & 0x00000FF8) >> 3;
        printf ("  Even Row Parity           [0.. ] = 0x%03x: %s\n", content, "Even Row Parity bits");
        content = (registerValue & 0x00000007) >> 0;
        printf ("  Even Column Parity        [0.. ] = 0x%01x: %s\n", content, "Even Column Parity bits");
    }
         
/* GPMC_BCH_SWDATA */
    printf ("\nGPMC_BCH_SWDATA\n");
    registerValue = *((volatile unsigned int*)(GPMC_BCH_SWDATA));

    content = (registerValue & 0x0000FFFF) >> 0;
    printf ("  BCH_DATA                  [64K-1] = 0x%04x: %s\n", content, content ? "Data to be included in the BCH calculation" : "Reserved" );

    return 0;
}
#endif

int gpmc_init_general (void)
{   
/*Sets general configuration parameters of GPMC */
/* GPMC_SYSCONFIG */

    /* 0x00000008 0b */
    *((volatile unsigned int*)(GPMC_SYSCONFIG)) = 0
    + ( 2 <<  3) /* SIDLEMODE                 [0: "Force-idle. An idle request is acknowledged unconditionally",
                                               1: "No-idle. An idle request is never acknowledged",
                                               2: "Smart-idle. Acknowledgement to an idle request is given based on the internal activity of the module",
                                               3: "Reserved"] */
    + ( 0 <<  1) /* SOFTRESET                 [0: "Normal mode",
                                               1: "The module is reset"] */
    + ( 0 <<  0) /* AUTOIDLE                  [0: "Interface clock is free-running",
                                               1: "Automatic Interface clock gating strategy is applied, based on the Interconnect activity"] */
    ;
/* GPMC_SYSCONFIG */

/* GPMC_IRQSTATUS */
    /* 0x00000000 0b  */
    *((volatile unsigned int*)(GPMC_IRQSTATUS)) = 0
    + ( 0 <<  9) /* WAIT1EDGE_DETECTIONSTATUS [0: "WAIT1EDGEDETECTIONSTATUS bit unchanged",
                                               1: "WAIT1EDGEDETECTIONSTATUS bit is reset"] */
    + ( 0 <<  8) /* WAIT0EDGE_DETECTIONSTATUS [0: "WAIT0EDGEDETECTIONSTATUS bit unchanged",
                                               1: "WAIT0EDGEDETECTIONSTATUS bit is reset"] */
    + ( 0 <<  1) /* TERMINAL_COUNTSTATUS      [0: "TERMINALCOUNTSTATUS bit unchanged",
                                               1: "TERMINALCOUNTSTATUS bit is reset"] */
    + ( 0 <<  0) /* FIFOEVENT_STATUS          [0: "FIFOEVENTSTATUS bit unchanged",
                                               1: "FIFOEVENTSTATUS bit is reset"] */
    ;
/* GPMC_IRQSTATUS */

/* GPMC_IRQENABLE */
    /* 0x00000200 0b  */
    *((volatile unsigned int*)(GPMC_IRQENABLE)) = 0
    + ( 0 <<  9) /* WAIT1EDGEDETECTIONENABLE [0: "Wait1EdgeDetection interrupt is masked", TODO Check this was set to 1 after poweron
                                              1: "Wait1EdgeDetection event generates an interrupt if occurs"] */
    + ( 0 <<  8) /* WAIT0EDGEDETECTIONENABLE [0: "Wait0EdgeDetection interrupt is masked",
                                              1: "Wait0EdgeDetection event generates an interrupt if occurs"] */
    + ( 0 <<  1) /* TERMINALCOUNTEVENTENABLE [0: "TerminalCountEvent interrupt is masked",
                                              1: "TerminalCountEvent interrupt is not masked"] */
    + ( 0 <<  0) /* FIFOEVENTENABLE          [0: "FIFOEvent interrupt is masked",
                                              1: "FIFOEvent interrupt is not masked"] */
    ;
/* GPMC_IRQENABLE */

/* GPMC_TIMEOUT_CONTROL */
    /* 0x00001ff0 0b  */
    *((volatile unsigned int*)(GPMC_TIMEOUT_CONTROL)) = 0
    + (511<<  4) /*                     [0..511: "Start value of the time-out counter in GPMC.FCLK" */
    + ( 0 <<  0) /*                          [0: "TimeOut feature is disabled",
                                              1: "TimeOut feature is enabled"] */
    ;
/* GPMC_TIMEOUT_CONTROL */
    
/* GPMC_ERR_ADDRESS */
    /* 0x00000000 0b  */
    *((volatile unsigned int*)(GPMC_ERR_ADDRESS)) = 0
    + ( 0 <<  0) /* GPMC_ERR_ADDRESS       [2 G: "Address of illegal access: A30 (0 for memory region, 1 for GPMC register region) and A29-A0 (1GByte maximum)"] */
    ;
/* GPMC_ERR_ADDRESS */
        
/* GPMC_ERR_TYPE */
    /* 0x00000000 0b  */
    *((volatile unsigned int*)(GPMC_ERR_TYPE)) = 0
    + ( 0 <<  8) /* ILLEGALMCMD             [0: "System Command of the transaction that caused the error",
                                             1: "System Command of the transaction that caused the error",
                                             2: "System Command of the transaction that caused the error",
                                             3: "System Command of the transaction that caused the error",
                                             4: "System Command of the transaction that caused the error",
                                             5: "System Command of the transaction that caused the error",
                                             6: "System Command of the transaction that caused the error",
                                             7: "System Command of the transaction that caused the error"] */
    + ( 0 <<  4) /* ERRORNOTSUPPADD         [0: "No error occurs",
                                             1: "The error is due to a non supported Address"] */
    + ( 0 <<  3) /* ERRORNOTSUPPMCMD        [0: "No error occurs",
                                             1: "The error is due to a non supported Command"] */
    + ( 0 <<  2) /* ERRORTIMEOUT            [0: "No error occurs",
                                             1: "The error is due to a time out"] */
    + ( 0 <<  0) /* ERRORVALID              [0: "All error fields no longer valid",
                                             1: "Error detected and logged in the other error fields"] */
    ;
/* GPMC_ERR_TYPE */
    
/* GPMC_CONFIG */
    /* 0x00000012 0b  */
    *((volatile unsigned int*)(GPMC_CONFIG)) = 0
    + ( 0 <<  9) /* WAIT1PINPOLARITY        [0: "WAIT1 active low",
                                             1: "WAIT1 active high"] */
    + ( 0 <<  8) /* WAIT0PINPOLARITY        [0: "WAIT0 active low",
                                             1: "WAIT0 active high"] */
    + ( 1 <<  4) /* WRITEPROTECT            [0: "WPn output pin is low",
                                             1: "WPn output pin is high"] */
    + ( 1 <<  1) /* LIMITEDADDRESS          [0: "0 Limited Address device support",
                                             1: "1 Limited Address device support"] */
    + ( 0 <<  0) /* NANDFORCEPOSTEDWRITE    [0: "Disables Force Posted Write",
                                             1: "Enables Force Posted Write"] */
    ;
/* GPMC_CONFIG */
    
/* GPMC_STATUS */
    /* 0x00000101 0b  */
    *((volatile unsigned int*)(GPMC_STATUS)) = 0
    + ( 0 <<  9) /* EMPTYWRITEBUFFERSTATUS  [0: "WAIT1 asserted (inactive state)",
                                             1: "WAIT1 de-asserted"] */
    + ( 1 <<  8) /* WAIT0STATUS             [0: "WAIT0 asserted (inactive state)",
                                             1: "WAIT0 de-asserted"] */
    + ( 1 <<  0) /* WAIT1STATUS             [0: "Write Buffer is not empty",
                                             1: "Write Buffer is empty"] */
    ;
/* GPMC_STATUS */

    return 0;
}

int gpmc_init_NAND (void)
{
    /* the current values may not work, check NAND parameters, check if
    concurrent implementation exists*/
    
    /*Sets physical address map of NAND*/
    printf ("1 GByte NAND:      Physical address map (256 MByte): 0x08000000..0x17FFFFFF\n");

/*  GPMC_CONFIG1_0 0x00000800 0xb0 0 0 0 0 00 00 00 0 00 00 0000 10 00 0000 0000 ok*/
     
    *((volatile unsigned int*)(GPMC_CONFIG1_0 + 0 * 0x30)) = 0
    + (0 << 31) /* WRAPBURST               [0: "Synchronous wrapping burst not supported",   
                                            1: "Synchronous wrapping burst supported"] */
    + (0 << 30) /* READMULTIPLE            [0: "Single access":,
                                            1: "Multiple access (burst if synchonous, page if asynchronous)"] */
    + (0 << 29) /* READTYPE                [0: "Read Asynchronous",
                                            1: "Read Synchronous"] */
    + (0 << 28) /* WRITEMULTIPLE           [0: "Single access",
                                            1: "Multiple access (burst if synchronous, considered as single if asynchronous)"] */
    + (0 << 27) /* WRITETYPE               [0: "Write Asynchronous",
                                            1: "Write Synchronous"] */
    + (0 << 25) /* CLKACTIVATIONTIME       [0: "First rising edge of GPMC_CLK at start access time",
                                            1: "First rising edge of GPMC_CLK one GPMC_FCLK cycle after start access time",
                                            2: "First rising edge of GPMC_CLK two GPMC_FCLK cycles after start access time",
                                            3: "Reserved" ] */
    + (0 << 23) /* ATTACHEDDEVICE_PAGELEN  [0: "4 Words", 
                                            1: "8 Words",
                                            2: "16 Words",
                                            3: "Reserved" ] */
    + (0 << 22) /* WAITREADMONITORING      [0: "WAIT pin is not monitored for read accesses",
                                            1: "WAIT pin is monitored for read accesses"] */
    + (0 << 21) /* WAITWRITEMONITORING     [0: "WAIT pin is not monitored for write accesses",
                                            1: "WAIT pin is monitored for write accesses"] */
    + (0 << 18) /* WAITMONITORINGTIME      [0: "WAIT pin is monitored with valid data",
                                            1: "WAIT pin is monitored one GPMC_CLK cycle before valid data",
                                            2: "WAIT pin is monitored two GPMC_CLK cycle before valid data",
                                            3: "Reserved" ] */
    + (0 << 16) /* WAITPINSELECT           [0: "WAIT input pin is WAIT0",
                                            1: "WAIT input pin is WAIT1",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (0 << 12) /* DEVICESIZE              [0: "8 bit",
                                            1: "16 bit",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (2 << 10) /* DEVICETYPE              [0: "NOR Flash like, asynchronous and synchronous devices",
                                            1: "Reserved", 
                                            2: "NAND Flash like devices, stream mode",
                                            3: "Reserved" ] */
    + (0 <<  8) /* MUXADDDATA              [0: "Non-multiplexed attached device",
                                            1: "AAD-multiplexed protocol device",
                                            2: "Address and data multiplexed attached device",
                                            3: "Reserved" ] */
    + (0 <<  4) /* TIMEPARAGRANULARITY     [0: "x1 latencies",
                                            1: "x2 latencies"] */
    + (0 <<  0) /* GPMCFCLKDIVIDER         [0: "GPMC_CLK frequency = GPMC_FCLK frequency",
                                            1: "GPMC_CLK frequency = GPMC_FCLK frequency/2",
                                            2: "GPMC_CLK frequency = GPMC_FCLK frequency/3",
                                            3: "GPMC_CLK frequency = GPMC_FCLK frequency/4"] */
    ;
/*  GPMC_CONFIG1_0 */

/*  GPMC_CONFIG2_0 */
    /* 0x001e1e00 0b 0000000000011110 00011110 0 0000000*/
    *((volatile unsigned int*)(GPMC_CONFIG2_0 + 0 * 0x30)) = 0
    + ( 30 << 16) /* CSWROFFTIME       30  [0..31 GPMC_FCLK cycles] ok*/
    + ( 30 <<  8) /* CSRDOFFTIME       30  [0..31 GPMC_FCLK cycles] ok*/
    + (  0 <<  7) /* CSEXTRADELAY       0  [0: "CS i Timing control signal is not delayed", 
                                            1: "CS i Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (  0 <<  0) /* CSONTIME           0  [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG2_0 */

/*  GPMC_CONFIG3_0 */
    /* 0x001e1e00 0b 0000 0000 00011110 00011110 0 000 0000*/
    *((volatile unsigned int*)(GPMC_CONFIG3_0 + 0 * 0x30)) = 0
    + (  0 << 28) /* ADVAADMUXWROFFTIME 0  [0.. 7 GPMC_FCLK cycles] ok*/
    + (  0 << 24) /* ADVAADMUXRDOFFTIME 0  [0.. 7 GPMC_FCLK cycles] ok*/
    + ( 30 << 16) /* ADVWROFFTIME      30  [0..31 GPMC_FCLK cycles] */
    + ( 30 <<  8) /* ADVRDOFFTIME      30  [0..31 GPMC_FCLK cycles] */
    + (  0 <<  7) /* ADVEXTRA_DELAY     0  [0: "ADVn Timing control signal is not delayed", 
                                            1: "ADVn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (  0 <<  4) /* ADVAADMUXONTIME    0  [0.. 7 GPMC_FCLK cycles] ok*/
    + (  0 <<  0) /* ADVONTIME          0  [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG3_0  */

/*  GPMC_CONFIG4_0 */
    /* 0x0b050c07 0b00001011 0 0000101 000 01100 0 000 0111 New*/
    /* 0x15051807 0b00010101 0 0000101 000 11000 0 000 0111 OLD*/
    *((volatile unsigned int*)(GPMC_CONFIG4_0 + 0 * 0x30)) = 0
    + ( 22 << 24) /* WEOFFTIME     21  [0..31: GPMC_FCLK cycles] */
    + (  0 << 23) /* WEEXTRADELAY       0  [0: "WEn Timing control signal is not delayed",
                                            1: "WEn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (  5 << 16) /* WEONTIME       5  [0..15: GPMC_FCLK cycles] */
    + (  0 << 13) /* OEAADMUXOFFTIME 0 [0.. 7: GPMC_FCLK cycles] ok*/
    + ( 24 <<  8) /* OEOFFTIME     24  [0..31: GPMC_FCLK cycles] */
    + (  0 <<  7) /* OEEXTRA_DELAY      0  [0: "OEn Timing control signal is not delayed", 
                                            1: "OEn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (  0 <<  4) /* OEAADMUXONTIME 0  [0.. 7: GPMC_FCLK cycles] ok*/
    + (  7 <<  0) /* OEONTIME       7  [0..15: GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG4_0 */

/*  GPMC_CONFIG5_0 */
    /* 0x00151e1e 0b00000000 00010101 00011110 00011110 OLD*/
    *((volatile unsigned int*)(GPMC_CONFIG5_0 + 0 * 0x30)) = 0
    + (  0 << 24) /* PAGEBURSTACCESSTIME 0 [0..15: GPMC_FCLK cycles] */
    + ( 21 << 16) /* RDACCESSTIME       21 [0..31: GPMC_FCLK cycles] */
    + ( 30 <<  8) /* WRCYCLETIME        30 [0..31: GPMC_FCLK cycles] */
    + ( 30 <<  0) /* RDCYCLETIME        30 [0..31: GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG5_0 */

/*  GPMC_CONFIG6_0 */
    /* 0x16000f80 0b00010110 00000000 00001111 1 0 000000 */
    * ((volatile unsigned int*)(GPMC_CONFIG6_0 + 0 * 0x30)) = 0
    + ( 22 << 24) /* WRACCESSTIME       22 [0..31: GPMC_FCLK cycles] */
    + (  0 << 16) /* WRDATAONADMUXBUS    0 [0..15: GPMC_FCLK cycles (rising_edge)] */
    + ( 15 <<  8) /* CYCLE2CYCLEDELAY   15 [0..15: GPMC_FCLK cycles] */
    + (  1 <<  7) /* CYCLE2CYCLE_SAMECSEN  [0: "No delay between the two accesses",
                                         1  1: "Add CYCLE2CYCLEDELAY"] */
    + (  0 <<  6) /* CYCLE2CYCLE_DIFFCSEN  [0: "No delay between the two accesses",
                                         0  1: "Add CYCLE2CYCLEDELAY"] */
    + (  0 <<  0) /* BUSTURNAROUND   0 [0..15: GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG6_0 */

/*  GPMC_CONFIG7_0 */ 
    /* 0x00000048 0b000000000000000000000000 01 001000 ok */
    *((volatile unsigned int*)(GPMC_CONFIG7_0 + 0 * 0x30)) = 0
    + ( 0 << 8) /* MASKADDRESS             [15: "16 MBytes", Todo change to 16 MByte later on
                                            14: "32 MBytes"
                                            12: "64 MBytes"
                                             8: "128 MBytes"
                                             0: "256 MBytes" */
    + ( 1 << 6) /* CSVALID                 [ 0: "CSn disabled",
                                             1: "CSn enabled"]: */
    + ( 0x08 << 0) /* BASEADDRESS      [ 0..63: ""] */
    ;
/*  GPMC_CONFIG7_0 */


/* GPMC_PREFETCH_CONFIG1 */
    /* 0x00004000 0b  */
    *((volatile unsigned int*)(GPMC_PREFETCH_CONFIG1)) = 0
    + ( 0 << 28) /* CYCLEOPTIMIZATION   [0...7: "GPMC_FCLK cycles"] */
    + ( 0 << 27) /* ENABLEOPTIMIZED_ACCESS  [0: "Access cycle optimization is disabled",
                                             1: "Access cycle optimization is enabled"] */
    + ( 0 << 24) /* ENGINECSSELECTOR        [0: "CS0n",
                                             1: "CS1n",
                                             2: "CS2n",
                                             3: "CS3n",
                                             4: "CS4n",
                                             5: "CS5n",
                                             6: "CS6n",
                                             7: "CS7n"] */
    + ( 0 << 23) /* PFPWENROUNDROBIN        [0: "Prefetch Postwrite engine round robin arbitration is disabled",
                                             1: "Prefetch Postwrite engine round robin arbitration is enabled"] */
    + ( 0 << 16) /* PFPWWEIGHTEDPRIO        [0: "The next access is granted to the PFPW engine"
                                         1..15: "The next number of value accesses are granted to the PFPW engine"] */
    + (64 <<  8) /* FIFOTHRESHOLD       [0..64: "bytes"] */
    + ( 0 <<  7) /* ENABLEENGINE            [0: "Prefetch Postwrite engine is disabled",
                                             1: "Prefetch Postwrite engine is enabled"] */
    + ( 0 <<  4) /* WAITPINSELECTOR         [0: "Selects WaitoEdgeDetection",
                                             1: "Selects Wait1EdgeDetection",
                                             2: "Reserved",
                                             3: "Reserved"] */
    + ( 0 <<  3) /* SYNCHROMODE             [0: "Engine starts the access to CS as soon as STARTENGINE is set",
                                             1: "Engine starts the access to CS as soon as STARTENGINE is set AND wait to non wait edge detection on the selected wait pin"] */
    + ( 0 <<  2) /* DMAMODE                 [0: "Interrupt synchronization is enabled. Only interrupt line will be activated on FIFO threshold crossing.",
                                             1: "DMA request synchronization is enabled. A DMA request protocol is used."] */
    + ( 0 <<  0) /* ACCESSMODE              [0: "Prefetch read mode",
                                             1: "Write-posting mode"] */
    ;
/* GPMC_PREFETCH_CONFIG1 */
    
/* GPMC_PREFETCH_CONFIG2 */
    /* 0x00000000 0b  */
    *((volatile unsigned int*)(GPMC_PREFETCH_CONFIG2)) = 0
    + ( 0 <<  0) /* TRANSFERCOUNT           [0..8192: "Bytes",
                                          8193..16383: "(illegal value)"] */
    ;
/* GPMC_PREFETCH_CONFIG2 */
    
/* GPMC_PREFETCH_CONTROL */
    /* 0x00000000 0b  */
    *((volatile unsigned int*)(GPMC_PREFETCH_CONTROL)) = 0
    + ( 0 <<  0) /*                         [0: "Stops the engine",
                                             1: "Resets the FIFO pointer to 0 in prefetch mode and 40h in postwrite mode and starts the engine"] */
    ;
/* GPMC_PREFETCH_CONTROL */
    
/* GPMC_ECC_CONFIG */ /* TODO seams to be wrong with NAND */
    /* 0x0001030 0b  */
    *((volatile unsigned int*)(GPMC_ECC_CONFIG)) = 0
    + ( 1 << 16) /* ECCALGORITHM            [0: "Hamming code",
                                             1: "BCH code"] */
    + ( 1 << 12) /* ECCBCHTSEL              [0: "Up to 4 bits error correction (t = 4)",
                                             1: "Up to 8 bits error correction (t = 8)",
                                             2: "Up to 16 bits error correction (t = 16)",
                                             3: "Reserved"] */
    + ( 0 <<  8) /* ECCWRAPMODE         [0..15: "Spare area organization definition for the BCH algorithm. See the BCH syndrome/parity calculator module functional specification for more details"] */
    + ( 0 <<  7) /* ECC16B                  [0: "ECC calculated on 8 columns",
                                             1: "ECC calculated on 16 columns"] */
    + ( 3 <<  4) /* ECCTOPSECTOR            [0: "1 sector (512kB page)",
                                             1: "2 sectors",
                                             2: "3 sectors",
                                             3: "4 sectors (2kB page)",
                                             4: "5 sectors",
                                             5: "6 sectors",
                                             6: "7 sectors",
                                             7: "8 sectors (4kB page)"] */
    + ( 0 <<  1) /* ECCCS                   [0: "CS0n",
                                             1: "CS1n",
                                             2: "CS2n",
                                             3: "CS3n",
                                             4: "CS4n",
                                             5: "CS5n",
                                             6: "CS6n",
                                             7: "Reserved"] */
    + ( 1 <<  0) /* ECCENABLE               [0: "ECC disabled",
                                             1: "ECC enabled"] */
    ;
/* GPMC_ECC_CONFIG */
    
/* GPMC_ECC_CONTROL */
    /* 0x00000001 0b  */
    *((volatile unsigned int*)(GPMC_ECC_CONTROL)) = 0
    + ( 0 <<  8) /* ECCCLEAR                [0: "Ignored",
                                             1: "Clears all ECC result registers"] */
    + ( 1 <<  0) /* ECCPOINTER              [0: "Writing 0 disables the ECC engine (ECCENABLE bit of GPMC_ECC_CONFIG cleared to 0)",
                                          1..9: "ECC result register number selected",
                                        10..15: "(ECC disabled)"] */
    ;
/* GPMC_ECC_CONTROL */
    
/* GPMC_ECC_SIZE_CONFIG */ /* Todo: Seams to be wrong with NAND config */
    /* 0x3fcff000 0b00 11111111 00 11111111 000 0 0 0 0 0 0 0 0 0  */
    *((volatile unsigned int*)(GPMC_ECC_SIZE_CONFIG)) = 0
    + (255<< 22) /* ECCSIZE1           [0..255: "2 x ( number + 1 ) Bytes"] */
    + (255<< 12) /* ECCSIZE0           [0..255: "2 x ( number + 1 ) Bytes"] */
    + ( 0 <<  8) /* ECC9RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    + ( 0 <<  7) /* ECC8RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    + ( 0 <<  6) /* ECC7RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    + ( 0 <<  5) /* ECC6RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    + ( 0 <<  4) /* ECC5RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    + ( 0 <<  3) /* ECC4RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    + ( 0 <<  2) /* ECC3RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    + ( 0 <<  1) /* ECC2RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    + ( 0 <<  0) /* ECC1RESULTSIZE          [0: "ECCSIZE0 selected",
                                             1: "ECCSIZE1 selected"] */
    ;
/* GPMC_ECC_SIZE_CONFIG */
         
/* GPMC_BCH_SWDATA */
    *((volatile unsigned int*)(GPMC_BCH_SWDATA)) = 0
    + ( 0 <<  0) /*                  [0..64K-1: "Data to be included in the BCH calculation",
                                   64K..128K-1: "Reserved"] */
    ;
/* GPMC_BCH_SWDATA */

    int BCH_ID = 0;
    for (BCH_ID=0;BCH_ID<=6;BCH_ID++)
    {
    /* GPMC_BCH_RESULT0_i */
        /* 0x 0b  */
        *((volatile unsigned int*)(GPMC_BCH_RESULT0_1 + BCH_ID * 0x10)) = 0
        + ( 0 <<  0) /*                    [0..4G-1: ""] */
        ;
    /* GPMC_BCH_RESULT0_i */

    /* GPMC_BCH_RESULT1_i */
        /* 0x 0b  */
        *((volatile unsigned int*)(GPMC_BCH_RESULT1_1 + BCH_ID * 0x10)) = 0
        + ( 0 <<  0) /*                    [0..4G-1: ""] */
        ;
    /* GPMC_BCH_RESULT1_i */

    /* GPMC_BCH_RESULT2_i */
        /* 0x 0b  */
        *((volatile unsigned int*)(GPMC_BCH_RESULT2_1 + BCH_ID * 0x10)) = 0
        + ( 0 <<  0) /*                    [0..4G-1: ""] */
        ;
    /* GPMC_BCH_RESULT2_i */

    /* GPMC_BCH_RESULT3_i */
        /* 0x 0b  */
        *((volatile unsigned int*)(GPMC_BCH_RESULT3_1 + BCH_ID * 0x10)) = 0
        + ( 0 <<  0) /*                    [0..4G-1: ""] */
        ;
    /* GPMC_BCH_RESULT3_i */

    /* GPMC_BCH_RESULT4_i */
        /* 0x 0b  */
        *((volatile unsigned int*)(GPMC_BCH_RESULT4_1 + BCH_ID * 0x10)) = 0
        + ( 0 <<  0) /*                    [0..4G-1: ""] */
        ;
    /* GPMC_BCH_RESULT4_i */

    /* GPMC_BCH_RESULT5_i */
        /* 0x 0b  */
        *((volatile unsigned int*)(GPMC_BCH_RESULT5_1 + BCH_ID * 0x10)) = 0
        + ( 0 <<  0) /*                    [0..4G-1: ""] */
        ;
    /* GPMC_BCH_RESULT5_i */

    /* GPMC_BCH_RESULT6_i */
        /* 0x 0b  */
        *((volatile unsigned int*)(GPMC_BCH_RESULT6_1 + BCH_ID * 0x10)) = 0
        + ( 0 <<  0) /*                    [0..4G-1: ""] */
        ;
    /* GPMC_BCH_RESULT6_i */
    }

    return 0;
}

int gpmc_init_FRAM (void)
{
    
    /*Sets physical address map of FRAM*/
    printf ("1 MBytes FRAM:     Physical address map ( 16 MByte): 0x01000000..0x01FFFFFF\n");

/*  GPMC_CONFIG1_1 */ /*0x00001200 0b0 0 0 0 0 00 00 00 0 00 00 0001 00 10 0000 0000 */
     
    *((volatile unsigned int*)(GPMC_CONFIG1_0 + 1 * 0x30)) = 0
    + (0 << 31) /* WRAPBURST               [0: "Synchronous wrapping burst not supported",   
                                            1: "Synchronous wrapping burst supported"] */
    + (0 << 30) /* READMULTIPLE            [0: "Single access":,
                                            1: "Multiple access (burst if synchonous, page if asynchronous)"] */
    + (0 << 29) /* READTYPE                [0: "Read Asynchronous",
                                            1: "Read Synchronous"] */
    + (0 << 28) /* WRITEMULTIPLE           [0: "Single access",
                                            1: "Multiple access (burst if synchronous, considered as single if asynchronous)"] */
    + (0 << 27) /* WRITETYPE               [0: "Write Asynchronous",
                                            1: "Write Synchronous"] */
    + (0 << 25) /* CLKACTIVATIONTIME       [0: "First rising edge of GPMC_CLK at start access time",
                                            1: "First rising edge of GPMC_CLK one GPMC_FCLK cycle after start access time",
                                            2: "First rising edge of GPMC_CLK two GPMC_FCLK cycles after start access time",
                                            3: "Reserved" ] */
    + (0 << 23) /* ATTACHEDDEVICE_PAGELEN  [0: "4 Words", 
                                            1: "8 Words",
                                            2: "16 Words",
                                            3: "Reserved" ] */
    + (0 << 22) /* WAITREADMONITORING      [0: "WAIT pin is not monitored for read accesses",
                                            1: "WAIT pin is monitored for read accesses"] */
    + (0 << 21) /* WAITWRITEMONITORING     [0: "WAIT pin is not monitored for write accesses",
                                            1: "WAIT pin is monitored for write accesses"] */
    + (0 << 18) /* WAITMONITORINGTIME      [0: "WAIT pin is monitored with valid data",
                                            1: "WAIT pin is monitored one GPMC_CLK cycle before valid data",
                                            2: "WAIT pin is monitored two GPMC_CLK cycle before valid data",
                                            3: "Reserved" ] */
    + (0 << 16) /* WAITPINSELECT           [0: "WAIT input pin is WAIT0",
                                            1: "WAIT input pin is WAIT1",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (1 << 12) /* DEVICESIZE              [0: "8 bit",
                                            1: "16 bit",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (0 << 10) /* DEVICETYPE              [0: "NOR Flash like, asynchronous and synchronous devices",
                                            1: "Reserved", 
                                            2: "NAND Flash like devices, stream mode",
                                            3: "Reserved" ] */
    + (2 <<  8) /* MUXADDDATA              [0: "Non-multiplexed attached device",
                                            1: "AAD-multiplexed protocol device",
                                            2: "Address and data multiplexed attached device",
                                            3: "Reserved" ] */
    + (0 <<  4) /* TIMEPARAGRANULARITY     [0: "x1 latencies",
                                            1: "x2 latencies"] */
    + (0 <<  0) /* GPMCFCLKDIVIDER         [0: "GPMC_CLK frequency = GPMC_FCLK frequency",
                                            1: "GPMC_CLK frequency = GPMC_FCLK frequency/2",
                                            2: "GPMC_CLK frequency = GPMC_FCLK frequency/3",
                                            3: "GPMC_CLK frequency = GPMC_FCLK frequency/4"] */
    ;
/*  GPMC_CONFIG1_1 */

/*  GPMC_CONFIG2_1 */
    /* 0x00101001 0b0000000000010000 00010000 0 0000001*/
    *((volatile unsigned int*)(GPMC_CONFIG2_0 + 1 * 0x30)) = 0
    + (16 << 16) /* CSWROFFTIME            [0..31 GPMC_FCLK cycles] */
    + (16 <<  8) /* CSRDOFFTIME            [0..31 GPMC_FCLK cycles] min CS active 60 ns*/
    + ( 0 <<  7) /* CSEXTRADELAY           [0: "CS i Timing control signal is not delayed", 
                                            1: "CS i Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + ( 3 <<  0) /* CSONTIME               [0..15 GPMC_FCLK cycles] min 5ns after address valid */
    ;
/*  GPMC_CONFIG2_1 */

/*  GPMC_CONFIG3_1 */
    /* 0x22060514 0b 0010 0010 00000110 00000101 0 001 0100*/
    *((volatile unsigned int*)(GPMC_CONFIG3_0 + 1 * 0x30)) = 0
    + (0 << 28) /* ADVAADMUXWROFFTIME      [0.. 7 GPMC_FCLK cycles] */
    + (0 << 24) /* ADVAADMUXRDOFFTIME      [0.. 7 GPMC_FCLK cycles] */
    + (1 << 16) /* ADVWROFFTIME            [0..31 GPMC_FCLK cycles] */
    + (1 <<  8) /* ADVRDOFFTIME            [0..31 GPMC_FCLK cycles] */
    + (0 <<  7) /* ADVEXTRA_DELAY          [0: "ADVn Timing control signal is not delayed", 
                                            1: "ADVn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (0 <<  4) /* ADVAADMUXONTIME         [0.. 7 GPMC_FCLK cycles] */
    + (0 <<  0) /* ADVONTIME               [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG3_1 */

/*  GPMC_CONFIG4_1 */
    /* 0x10057016 0b00010000 0 0000101 011 10000 0 001 0011 */
    *((volatile unsigned int*)(GPMC_CONFIG4_0 + 1 * 0x30)) = 0
    + ( 17 << 24) /* WEOFFTIME             [0..31 GPMC_FCLK cycles] */
    + (  0 << 23) /* WEEXTRADELAY          [0: "WEn Timing control signal is not delayed",
                                            1: "WEn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (  2 << 16) /* WEONTIME              [0..15 GPMC_FCLK cycles] */
    + (  0 << 13) /* OEAADMUXOFFTIME       [0.. 7 GPMC_FCLK cycles] */
    + ( 17 <<  8) /* OEOFFTIME             [0..31 GPMC_FCLK cycles] */
    + (  0 <<  7) /* OEEXTRA_DELAY         [0: "OEn Timing control signal is not delayed",
                                            1: "OEn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (  0 <<  4) /* OEAADMUXONTIME        [0.. 7 GPMC_FCLK cycles] */
    + ( 11 <<  0) /* OEONTIME              [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG4_1 */

/*  GPMC_CONFIG5_1 */
    /* 0x010f1111 0b00000001 00001111 00010001 00010001 */
    *((volatile unsigned int*)(GPMC_CONFIG5_0 + 1 * 0x30)) = 0
    + (  1 << 24) /* PAGEBURSTACCESSTIME   [0..15 GPMC_FCLK cycles] */
    + ( 16 << 16) /* RDACCESSTIME          [0..31 GPMC_FCLK cycles] */
    + ( 24 <<  8) /* WRCYCLETIME           [0..31 GPMC_FCLK cycles] min 115 ns*/
    + ( 24 <<  0) /* RDCYCLETIME           [0..31 GPMC_FCLK cycles] min 115 ns*/
    ;
/*  GPMC_CONFIG5_1 */

/*  GPMC_CONFIG6_1 */
    /* 0x8f070000 0b10001111 00000111 00000000 0 0 000000 */ /*Todo check first bit, initial set, not like docu*/ 
    *((volatile unsigned int*)(GPMC_CONFIG6_0 + 1 * 0x30)) = 0
    + (  4 << 24) /* WRACCESSTIME          [0..31 GPMC_FCLK cycles] */
    + (  2 << 16) /* WRDATAONADMUXBUS      [0..15 GPMC_FCLK cycles (rising_edge)] */
    + (  0 <<  8) /* CYCLE2CYCLEDELAY      [0..15 GPMC_FCLK cycles] */
    + (  0 <<  7) /* CYCLE2CYCLE_SAMECSEN  [0: "No delay between the two accesses",
                                            1: "Add CYCLE2CYCLEDELAY"] */
    + (  0 <<  6) /* CYCLE2CYCLE_DIFFCSEN  [0: "No delay between the two accesses",
                                            1: "Add CYCLE2CYCLEDELAY"] */
    + (  0 <<  0) /* BUSTURNAROUND         [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG6_1 */

/*  GPMC_CONFIG7_1 */    
    /* 0x00000f41 0b000000000000000000001111 01 000001 */
    *((volatile unsigned int*)(GPMC_CONFIG7_0 + 1 * 0x30)) = 0
    + (15 << 8) /* MASKADDRESS             [15: "16 MBytes",
                                            14: "32 MBytes"
                                            12: "64 MBytes"
                                             8: "128 MBytes"
                                             0: "256 MBytes" */
    + ( 1 << 6) /* CSVALID                 [ 0: "CSn disabled",
                                             1: "CSn enabled"]: */
    + ( 1 << 0) /* BASEADDRESS             [ 0..63] << 24 ] */
    ;
/*  GPMC_CONFIG7_1 */

    return 0;
}

int gpmc_init_FPGA_ASYNC (void)
{
    /*Sets physical address map of FPGA in asynchronous mode*/
    printf ("FPGA async access: Physical address map ( 64 MByte): 0x18000000..0x1BFFFFFF\n");
    
    
/*  GPMC_CONFIG1_2 */
    /* 0x00001201 0b0 0 0 0 0 00 00 00 0 00 00 0001 00 10 0000 0001*/
    *((volatile unsigned int*)(GPMC_CONFIG1_0 + 2 * 0x30)) = 0
    + (0 << 31) /* WRAPBURST               [0: "Synchronous wrapping burst not supported",   
                                            1: "Synchronous wrapping burst supported"] */
    + (0 << 30) /* READMULTIPLE            [0: "Single access":,
                                            1: "Multiple access (burst if synchonous, page if asynchronous)"] */
    + (0 << 29) /* READTYPE                [0: "Read Asynchronous",
                                            1: "Read Synchronous"] */
    + (0 << 28) /* WRITEMULTIPLE           [0: "Single access",
                                            1: "Multiple access (burst if synchronous, considered as single if asynchronous)"] */
    + (0 << 27) /* WRITETYPE               [0: "Write Asynchronous",
                                            1: "Write Synchronous"] */
    + (0 << 25) /* CLKACTIVATIONTIME       [0: "First rising edge of GPMC_CLK at start access time",
                                            1: "First rising edge of GPMC_CLK one GPMC_FCLK cycle after start access time",
                                            2: "First rising edge of GPMC_CLK two GPMC_FCLK cycles after start access time",
                                            3: "Reserved" ] */
    + (0 << 23) /* ATTACHEDDEVICE_PAGELEN  [0: "4 Words", 
                                            1: "8 Words",
                                            2: "16 Words",
                                            3: "Reserved" ] */
    + (0 << 22) /* WAITREADMONITORING      [0: "WAIT pin is not monitored for read accesses",
                                            1: "WAIT pin is monitored for read accesses"] */
    + (0 << 21) /* WAITWRITEMONITORING     [0: "WAIT pin is not monitored for write accesses",
                                            1: "WAIT pin is monitored for write accesses"] */
    + (0 << 18) /* WAITMONITORINGTIME      [0: "WAIT pin is monitored with valid data",
                                            1: "WAIT pin is monitored one GPMC_CLK cycle before valid data",
                                            2: "WAIT pin is monitored two GPMC_CLK cycle before valid data",
                                            3: "Reserved" ] */
    + (0 << 16) /* WAITPINSELECT           [0: "WAIT input pin is WAIT0",
                                            1: "WAIT input pin is WAIT1",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (1 << 12) /* DEVICESIZE              [0: "8 bit",
                                            1: "16 bit",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (0 << 10) /* DEVICETYPE              [0: "NOR Flash like, asynchronous and synchronous devices",
                                            1: "Reserved", 
                                            2: "NAND Flash like devices, stream mode",
                                            3: "Reserved" ] */
    + (2 <<  8) /* MUXADDDATA              [0: "Non-multiplexed attached device",
                                            1: "AAD-multiplexed protocol device",
                                            2: "Address and data multiplexed attached device",
                                            3: "Reserved" ] */
    + (0 <<  4) /* TIMEPARAGRANULARITY     [0: "x1 latencies",
                                            1: "x2 latencies"] */
    + (1 <<  0) /* GPMCFCLKDIVIDER         [0: "GPMC_CLK frequency = GPMC_FCLK frequency",
                                            1: "GPMC_CLK frequency = GPMC_FCLK frequency/2",
                                            2: "GPMC_CLK frequency = GPMC_FCLK frequency/3",
                                            3: "GPMC_CLK frequency = GPMC_FCLK frequency/4"] */
    ;
/*  GPMC_CONFIG1_2 */

/*  GPMC_CONFIG2_2 */
    /* 0x00070b00 0b 0000000000000111 00001011 0 0000000*/
    *((volatile unsigned int*)(GPMC_CONFIG2_0 + 2 * 0x30)) = 0
    + ( 7 << 16) /* CSWROFFTIME            [0..31 GPMC_FCLK cycles] */
    + (11 <<  8) /* CSRDOFFTIME            [0..31 GPMC_FCLK cycles] */
    + ( 0 <<  7) /* CSEXTRADELAY           [0: "CS i Timing control signal is not delayed", 
                                            1: "CS i Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + ( 0 <<  0) /* CSONTIME               [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG2_2 */

/*  GPMC_CONFIG3_2 */
    /* 0x00030301 0b 0000 0000 00000011 00000011 0 000 0001 */
    *((volatile unsigned int*)(GPMC_CONFIG3_0 + 2 * 0x30)) = 0
    + ( 0 << 28) /* ADVAADMUXWROFFTIME     [0.. 7 GPMC_FCLK cycles] */
    + ( 0 << 24) /* ADVAADMUXRDOFFTIME     [0.. 7 GPMC_FCLK cycles] */
    + ( 3 << 16) /* ADVWROFFTIME           [0..31 GPMC_FCLK cycles] */
    + ( 3 <<  8) /* ADVRDOFFTIME           [0..31 GPMC_FCLK cycles] */
    + ( 0 <<  7) /* ADVEXTRA_DELAY         [0: "ADVn Timing control signal is not delayed", 
                                            1: "ADVn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + ( 0 <<  4) /* ADVAADMUXONTIME        [0.. 7 GPMC_FCLK cycles] */
    + ( 1 <<  0) /* ADVONTIME              [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG3_2 */

/*  GPMC_CONFIG4_2 */
    /* 0x07036b13 0b 00000111 0 0000011 011 01011 0 001 0011 */
    *((volatile unsigned int*)(GPMC_CONFIG4_0 + 2 * 0x30)) = 0
    + ( 7 << 24) /* WEOFFTIME              [0..31 GPMC_FCLK cycles] */
    + ( 0 << 23) /* WEEXTRADELAY           [0: "WEn Timing control signal is not delayed",
                                            1: "WEn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + ( 3 << 16) /* WEONTIME               [0..15 GPMC_FCLK cycles] */
    + ( 3 << 13) /* OEAADMUXOFFTIME        [0.. 7 GPMC_FCLK cycles] */
    + (11 <<  8) /* OEOFFTIME              [0..31 GPMC_FCLK cycles] */
    + ( 0 <<  7) /* OEEXTRA_DELAY          [0: "OEn Timing control signal is not delayed",
                                            1: "OEn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + ( 1 <<  4) /* OEAADMUXONTIME         [0.. 7 GPMC_FCLK cycles] */
    + ( 3 <<  0) /* OEONTIME               [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG4_2 */

/*  GPMC_CONFIG5_2 */
    /* 0x010A080C 0b 00000001 00001010 00001000 00001100 */
    *((volatile unsigned int*)(GPMC_CONFIG5_0 + 2 * 0x30)) = 0
    + (  1 << 24) /* PAGEBURSTACCESSTIME   [0..15 GPMC_FCLK cycles] */
    + ( 10 << 16) /* RDACCESSTIME          [0..31 GPMC_FCLK cycles] */
    + (  8 <<  8) /* WRCYCLETIME           [0..31 GPMC_FCLK cycles] */
    + ( 12 <<  0) /* RDCYCLETIME           [0..31 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG5_2 */

/*  GPMC_CONFIG6_2 */
    /* 0x04030101 0b 00000100 00000011 00000001 0 0 000001 */ 
    *((volatile unsigned int*)(GPMC_CONFIG6_0 + 2 * 0x30)) = 0
    + (  4 << 24) /* WRACCESSTIME          [0..31 GPMC_FCLK cycles] */
    + (  3 << 16) /* WRDATAONADMUXBUS      [0..15 GPMC_FCLK cycles (rising_edge)] */
    + (  1 <<  8) /* CYCLE2CYCLEDELAY      [0..15 GPMC_FCLK cycles] */
    + (  0 <<  7) /* CYCLE2CYCLE_SAMECSEN  [0: "No delay between the two accesses",
                                            1: "Add CYCLE2CYCLEDELAY"] */
    + (  0 <<  6) /* CYCLE2CYCLE_DIFFCSEN  [0: "No delay between the two accesses",
                                            1: "Add CYCLE2CYCLEDELAY"] */
    + (  1 <<  0) /* BUSTURNAROUND         [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG6_2 */

/*  GPMC_CONFIG7_2 */
    /* 0x00000c58 0b000000000000000000001100 01 011000 */
    *((volatile unsigned int*)(GPMC_CONFIG7_0 + 2 * 0x30)) =
    0 \
    + (12 << 8) /* MASKADDRESS             [15: "16 MBytes",
                                            14: "32 MBytes"
                                            12: "64 MBytes"
                                             8: "128 MBytes"
                                             0: "256 MBytes" */
    + ( 1 << 6) /* CSVALID                 [ 0: "CSn disabled",
                                             1: "CSn enabled"]: */
    + ( 0x18 << 0)/* BASEADDRESS           [ 0..63] << 24 */
    ;

    return 0;
/*  GPMC_CONFIG7_2 */
}

int gpmc_init_FPGA_SYNC (void)
{
    /*Sets physical address map of FPGA in synchronous mode*/
    printf ("FPGA  sync access: Physical address map ( 64 MByte): 0x1C000000..0x1FFFFFFF\n");
    
/*  GPMC_CONFIG1_3 */
    /* 0xf9091101 0b1 1 1 1 1 00 10 00 0 10 01 0001 00 01 0000 0001 */
    *((volatile unsigned int*)(GPMC_CONFIG1_0 + 3 * 0x30)) = 
    0 \
    + (0 << 31) /* WRAPBURST               [0: "Synchronous wrapping burst not supported",   
                                            1: "Synchronous wrapping burst supported"] */
    + (0 << 30) /* READMULTIPLE            [0: "Single access":,
                                            1: "Multiple access (burst if synchonous, page if asynchronous)"] */
    + (1 << 29) /* READTYPE                [0: "Read Asynchronous",
                                            1: "Read Synchronous"] */
    + (0 << 28) /* WRITEMULTIPLE           [0: "Single access",
                                            1: "Multiple access (burst if synchronous, considered as single if asynchronous)"] */
    + (1 << 27) /* WRITETYPE               [0: "Write Asynchronous",
                                            1: "Write Synchronous"] */
    + (0 << 25) /* CLKACTIVATIONTIME       [0: "First rising edge of GPMC_CLK at start access time",
                                            1: "First rising edge of GPMC_CLK one GPMC_FCLK cycle after start access time",
                                            2: "First rising edge of GPMC_CLK two GPMC_FCLK cycles after start access time",
                                            3: "Reserved" ] */
    + (2 << 23) /* ATTACHEDDEVICE_PAGELEN  [0: "4 Words", 
                                            1: "8 Words",
                                            2: "16 Words",
                                            3: "Reserved" ] */
    + (0 << 22) /* WAITREADMONITORING      [0: "WAIT pin is not monitored for read accesses",
                                            1: "WAIT pin is monitored for read accesses"] */
    + (0 << 21) /* WAITWRITEMONITORING     [0: "WAIT pin is not monitored for write accesses",
                                            1: "WAIT pin is monitored for write accesses"] */
    + (2 << 18) /* WAITMONITORINGTIME      [0: "WAIT pin is monitored with valid data",
                                            1: "WAIT pin is monitored one GPMC_CLK cycle before valid data",
                                            2: "WAIT pin is monitored two GPMC_CLK cycle before valid data",
                                            3: "Reserved" ] */
    + (0 << 16) /* WAITPINSELECT           [0: "WAIT input pin is WAIT0",
                                            1: "WAIT input pin is WAIT1",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (1 << 12) /* DEVICESIZE              [0: "8 bit",
                                            1: "16 bit",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (0 << 10) /* DEVICETYPE              [0: "NOR Flash like, asynchronous and synchronous devices",
                                            1: "Reserved", 
                                            2: "NAND Flash like devices, stream mode",
                                            3: "Reserved" ] */
    + (2 <<  8) /* MUXADDDATA              [0: "Non-multiplexed attached device",
                                            1: "AAD-multiplexed protocol device",
                                            2: "Address and data multiplexed attached device",
                                            3: "Reserved" ] */
    + (0 <<  4) /* TIMEPARAGRANULARITY     [0: "x1 latencies",
                                            1: "x2 latencies"] */
    + (1 <<  0) /* GPMCFCLKDIVIDER         [0: "GPMC_CLK frequency = GPMC_FCLK frequency",
                                            1: "GPMC_CLK frequency = GPMC_FCLK frequency/2",
                                            2: "GPMC_CLK frequency = GPMC_FCLK frequency/3",
                                            3: "GPMC_CLK frequency = GPMC_FCLK frequency/4"] */
    ;

/*  GPMC_CONFIG1_3 */

/*  GPMC_CONFIG2_3 */
    /* 0x00101001 0b0000000000010000 00010000 0 0000001*/
    *((volatile unsigned int*)(GPMC_CONFIG2_0 + 3 * 0x30)) = 0
    + (16 << 16) /* CSWROFFTIME            [0..31 GPMC_FCLK cycles] */
    + (16 <<  8) /* CSRDOFFTIME            [0..31 GPMC_FCLK cycles] */
    + (0 <<  7) /* CSEXTRADELAY            [0: "CS i Timing control signal is not delayed", 
                                            1: "CS i Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (1 <<  0) /* CSONTIME                [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG2_3 */

/*  GPMC_CONFIG3_3 */
    /* 0x22060514 0b 0010 0010 00000110 00000101 0 001 0100*/
    *((volatile unsigned int*)(GPMC_CONFIG3_0 + 3 * 0x30)) = 0
    + (2 << 28) /* ADVAADMUXWROFFTIME      [0.. 7 GPMC_FCLK cycles] */
    + (2 << 24) /* ADVAADMUXRDOFFTIME      [0.. 7 GPMC_FCLK cycles] */
    + (6 << 16) /* ADVWROFFTIME            [0..31 GPMC_FCLK cycles] */
    + (5 <<  8) /* ADVRDOFFTIME            [0..31 GPMC_FCLK cycles] */
    + (0 <<  7) /* ADVEXTRA_DELAY          [0: "ADVn Timing control signal is not delayed", 
                                            1: "ADVn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (1 <<  4) /* ADVAADMUXONTIME         [0.. 7 GPMC_FCLK cycles] */
    + (4 <<  0) /* ADVONTIME               [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG3_3 */

/*  GPMC_CONFIG4_3 */
    /* 0x10057016 0b00010000 0 0000101 011 10000 0 001 0110 */
    *((volatile unsigned int*)(GPMC_CONFIG4_0 + 3 * 0x30)) = 0
    + ( 16 << 24) /* WEOFFTIME             [0..31 GPMC_FCLK cycles] */
    + (  0 << 23) /* WEEXTRADELAY          [0: "WEn Timing control signal is not delayed",
                                            1: "WEn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (  5 << 16) /* WEONTIME              [0..15 GPMC_FCLK cycles] */
    + (  3 << 13) /* OEAADMUXOFFTIME       [0.. 7 GPMC_FCLK cycles] */
    + ( 16 <<  8) /* OEOFFTIME             [0..31 GPMC_FCLK cycles] */
    + (  0 <<  7) /* OEEXTRA_DELAY         [0: "OEn Timing control signal is not delayed",
                                            1: "OEn Timing control signal is delayed of half GPMC_FCLK clock cycle"] */
    + (  1 <<  4) /* OEAADMUXONTIME        [0.. 7 GPMC_FCLK cycles] */
    + (  6 <<  0) /* OEONTIME              [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG4_3 */

/*  GPMC_CONFIG5_3 */
    /* 0x010f1111 0b00000001 00001111 00010001 00010001 */
    *((volatile unsigned int*)(GPMC_CONFIG5_0 + 3 * 0x30)) = 0
    + (  1 << 24) /* PAGEBURSTACCESSTIME   [0..15 GPMC_FCLK cycles] */
    + ( 15 << 16) /* RDACCESSTIME          [0..31 GPMC_FCLK cycles] */
    + ( 17 <<  8) /* WRCYCLETIME           [0..31 GPMC_FCLK cycles] */
    + ( 17 <<  0) /* RDCYCLETIME           [0..31 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG5_3 */

/*  GPMC_CONFIG6_3 */
    /* 0x8f070000 0b10001111 00000111 00000000 0 0 000000 */ /*Todo check first bit, initial set, not like docu*/ 
    *((volatile unsigned int*)(GPMC_CONFIG6_0 + 3 * 0x30)) = 0
    + ( 15 << 24) /* WRACCESSTIME          [0..31 GPMC_FCLK cycles] */
    + (  7 << 16) /* WRDATAONADMUXBUS      [0..15 GPMC_FCLK cycles (rising_edge)] */
    + (  0 <<  8) /* CYCLE2CYCLEDELAY      [0..15 GPMC_FCLK cycles] */
    + (  0 <<  7) /* CYCLE2CYCLE_SAMECSEN  [0: "No delay between the two accesses",
                                            1: "Add CYCLE2CYCLEDELAY"] */
    + (  0 <<  6) /* CYCLE2CYCLE_DIFFCSEN  [0: "No delay between the two accesses",
                                            1: "Add CYCLE2CYCLEDELAY"] */
    + (  0 <<  0) /* BUSTURNAROUND         [0..15 GPMC_FCLK cycles] */
    ;
/*  GPMC_CONFIG6_3 */

/*  GPMC_CONFIG7_3 */    
    /* 0x00000c5c 0b000000000000000000 001100 01 011100 */
    *((volatile unsigned int*)(GPMC_CONFIG7_0 + 3 * 0x30)) =
    0 \
    + (12 << 8) /* MASKADDRESS             [15: "16 MBytes",
                                            14: "32 MBytes"
                                            12: "64 MBytes"
                                             8: "128 MBytes"
                                             0: "256 MBytes" */
    + ( 1 << 6) /* CSVALID                 [ 0: "CSn disabled",
                                             1: "CSn enabled"]: */
    + (0x1C << 0)/* BASEADDRESS            [ 0..63] << 24 */
    ;
/*  GPMC_CONFIG7_3 */    

    return 0;
}

int gpmc_init_CS4 (void)
{
    /*Sets physical address map for CS4*/
/*    printf ("CS4 (not used):    Physical address map ( 16 MByte): 0x04000000..0x04FFFFFF\n");*/
    

/*  GPMC_CONFIG1_4 */
     
    *((volatile unsigned int*)(GPMC_CONFIG1_0 + 4 * 0x30)) = 
    0 \
    + (0 << 31) /* WRAPBURST               [0: "Synchronous wrapping burst not supported",   
                                            1: "Synchronous wrapping burst supported"] */
    + (0 << 30) /* READMULTIPLE            [0: "Single access":,
                                            1: "Multiple access (burst if synchonous, page if asynchronous)"] */
    + (0 << 29) /* READTYPE                [0: "Read Asynchronous",
                                            1: "Read Synchronous"] */
    + (0 << 28) /* WRITEMULTIPLE           [0: "Single access",
                                            1: "Multiple access (burst if synchronous, considered as single if asynchronous)"] */
    + (0 << 27) /* WRITETYPE               [0: "Write Asynchronous",
                                            1: "Write Synchronous"] */
    + (0 << 25) /* CLKACTIVATIONTIME       [0: "First rising edge of GPMC_CLK at start access time",
                                            1: "First rising edge of GPMC_CLK one GPMC_FCLK cycle after start access time",
                                            2: "First rising edge of GPMC_CLK two GPMC_FCLK cycles after start access time",
                                            3: "Reserved" ] */
    + (0 << 23) /* ATTACHEDDEVICE_PAGELEN  [0: "4 Words", 
                                            1: "8 Words",
                                            2: "16 Words",
                                            3: "Reserved" ] */
    + (0 << 22) /* WAITREADMONITORING      [0: "WAIT pin is not monitored for read accesses",
                                            1: "WAIT pin is monitored for read accesses"] */
    + (0 << 21) /* WAITWRITEMONITORING     [0: "WAIT pin is not monitored for write accesses",
                                            1: "WAIT pin is monitored for write accesses"] */
    + (0 << 18) /* WAITMONITORINGTIME      [0: "WAIT pin is monitored with valid data",
                                            1: "WAIT pin is monitored one GPMC_CLK cycle before valid data",
                                            2: "WAIT pin is monitored two GPMC_CLK cycle before valid data",
                                            3: "Reserved" ] */
    + (0 << 16) /* WAITPINSELECT           [0: "WAIT input pin is WAIT0",
                                            1: "WAIT input pin is WAIT1",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (1 << 12) /* DEVICESIZE              [0: "8 bit",
                                            1: "16 bit",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (0 << 10) /* DEVICETYPE              [0: "NOR Flash like, asynchronous and synchronous devices",
                                            1: "Reserved", 
                                            2: "NAND Flash like devices, stream mode",
                                            3: "Reserved" ] */
    + (2 <<  8) /* MUXADDDATA              [0: "Non-multiplexed attached device",
                                            1: "AAD-multiplexed protocol device",
                                            2: "Address and data multiplexed attached device",
                                            3: "Reserved" ] */
    + (0 <<  4) /* TIMEPARAGRANULARITY     [0: "x1 latencies",
                                            1: "x2 latencies"] */
    + (1 <<  0) /* GPMCFCLKDIVIDER         [0: "GPMC_CLK frequency = GPMC_FCLK frequency",
                                            1: "GPMC_CLK frequency = GPMC_FCLK frequency/2",
                                            2: "GPMC_CLK frequency = GPMC_FCLK frequency/3",
                                            3: "GPMC_CLK frequency = GPMC_FCLK frequency/4"] */
    ;

/*  GPMC_CONFIG7_4 */    
    *((volatile unsigned int*)(GPMC_CONFIG7_0 + 4 * 0x30)) =
    0 \
    + (15 << 8) /* MASKADDRESS             [15: "16 MBytes",
                                            14: "32 MBytes"
                                            12: "64 MBytes"
                                             8: "128 MBytes"
                                             0: "256 MBytes" */
    + ( 1 << 6) /* CSVALID                 [ 0: "CSn disabled",
                                             1: "CSn enabled" ]: */
    + ( 4 << 0)  /* BASEADDRESS            [ 0..63] << 24 */
    ;

    return 0;
}

int gpmc_init_CS5 (void)
{
    /*Sets physical address map for CS5*/
/*    printf ("CS5 (not used):    Physical address map ( 16 MByte): 0x05000000..0x05FFFFFF\n");*/
    

/*  GPMC_CONFIG1_5 */
     
    *((volatile unsigned int*)(GPMC_CONFIG1_0 + 5 * 0x30)) = 
    0 \
    + (0 << 31) /* WRAPBURST               [0: "Synchronous wrapping burst not supported",   
                                            1: "Synchronous wrapping burst supported"] */
    + (0 << 30) /* READMULTIPLE            [0: "Single access":,
                                            1: "Multiple access (burst if synchonous, page if asynchronous)"] */
    + (0 << 29) /* READTYPE                [0: "Read Asynchronous",
                                            1: "Read Synchronous"] */
    + (0 << 28) /* WRITEMULTIPLE           [0: "Single access",
                                            1: "Multiple access (burst if synchronous, considered as single if asynchronous)"] */
    + (0 << 27) /* WRITETYPE               [0: "Write Asynchronous",
                                            1: "Write Synchronous"] */
    + (0 << 25) /* CLKACTIVATIONTIME       [0: "First rising edge of GPMC_CLK at start access time",
                                            1: "First rising edge of GPMC_CLK one GPMC_FCLK cycle after start access time",
                                            2: "First rising edge of GPMC_CLK two GPMC_FCLK cycles after start access time",
                                            3: "Reserved" ] */
    + (0 << 23) /* ATTACHEDDEVICE_PAGELEN  [0: "4 Words", 
                                            1: "8 Words",
                                            2: "16 Words",
                                            3: "Reserved" ] */
    + (0 << 22) /* WAITREADMONITORING      [0: "WAIT pin is not monitored for read accesses",
                                            1: "WAIT pin is monitored for read accesses"] */
    + (0 << 21) /* WAITWRITEMONITORING     [0: "WAIT pin is not monitored for write accesses",
                                            1: "WAIT pin is monitored for write accesses"] */
    + (0 << 18) /* WAITMONITORINGTIME      [0: "WAIT pin is monitored with valid data",
                                            1: "WAIT pin is monitored one GPMC_CLK cycle before valid data",
                                            2: "WAIT pin is monitored two GPMC_CLK cycle before valid data",
                                            3: "Reserved" ] */
    + (0 << 16) /* WAITPINSELECT           [0: "WAIT input pin is WAIT0",
                                            1: "WAIT input pin is WAIT1",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (1 << 12) /* DEVICESIZE              [0: "8 bit",
                                            1: "16 bit",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (0 << 10) /* DEVICETYPE              [0: "NOR Flash like, asynchronous and synchronous devices",
                                            1: "Reserved", 
                                            2: "NAND Flash like devices, stream mode",
                                            3: "Reserved" ] */
    + (2 <<  8) /* MUXADDDATA              [0: "Non-multiplexed attached device",
                                            1: "AAD-multiplexed protocol device",
                                            2: "Address and data multiplexed attached device",
                                            3: "Reserved" ] */
    + (0 <<  4) /* TIMEPARAGRANULARITY     [0: "x1 latencies",
                                            1: "x2 latencies"] */
    + (1 <<  0) /* GPMCFCLKDIVIDER         [0: "GPMC_CLK frequency = GPMC_FCLK frequency",
                                            1: "GPMC_CLK frequency = GPMC_FCLK frequency/2",
                                            2: "GPMC_CLK frequency = GPMC_FCLK frequency/3",
                                            3: "GPMC_CLK frequency = GPMC_FCLK frequency/4"] */
    ;

/*  GPMC_CONFIG7_5 */    
    *((volatile unsigned int*)(GPMC_CONFIG7_0 + 5 * 0x30)) =
    0 \
    + (15 << 8) /* MASKADDRESS             [15: "16 MBytes",
                                            14: "32 MBytes"
                                            12: "64 MBytes"
                                             8: "128 MBytes"
                                             0: "256 MBytes" */
    + ( 1 << 6) /* CSVALID                 [ 0: "CSn disabled",
                                             1: "CSn enabled"]: */
    + ( 5 << 0)  /* BASEADDRESS            [ 0..63] << 24 */
    ;

    return 0;
}

int gpmc_init_CS6 (void)
{
    /*Sets physical address map for CS6*/
/*    printf ("CS6 (not used):    Physical address map ( 16 MByte): 0x06000000..0x06FFFFFF\n");*/
    
    
/*  GPMC_CONFIG1_6 */
     
    *((volatile unsigned int*)(GPMC_CONFIG1_0 + 6 * 0x30)) = 
    0 \
    + (0 << 31) /* WRAPBURST               [0: "Synchronous wrapping burst not supported",   
                                            1: "Synchronous wrapping burst supported"] */
    + (0 << 30) /* READMULTIPLE            [0: "Single access":,
                                            1: "Multiple access (burst if synchonous, page if asynchronous)"] */
    + (0 << 29) /* READTYPE                [0: "Read Asynchronous",
                                            1: "Read Synchronous"] */
    + (0 << 28) /* WRITEMULTIPLE           [0: "Single access",
                                            1: "Multiple access (burst if synchronous, considered as single if asynchronous)"] */
    + (0 << 27) /* WRITETYPE               [0: "Write Asynchronous",
                                            1: "Write Synchronous"] */
    + (0 << 25) /* CLKACTIVATIONTIME       [0: "First rising edge of GPMC_CLK at start access time",
                                            1: "First rising edge of GPMC_CLK one GPMC_FCLK cycle after start access time",
                                            2: "First rising edge of GPMC_CLK two GPMC_FCLK cycles after start access time",
                                            3: "Reserved" ] */
    + (0 << 23) /* ATTACHEDDEVICE_PAGELEN  [0: "4 Words", 
                                            1: "8 Words",
                                            2: "16 Words",
                                            3: "Reserved" ] */
    + (0 << 22) /* WAITREADMONITORING      [0: "WAIT pin is not monitored for read accesses",
                                            1: "WAIT pin is monitored for read accesses"] */
    + (0 << 21) /* WAITWRITEMONITORING     [0: "WAIT pin is not monitored for write accesses",
                                            1: "WAIT pin is monitored for write accesses"] */
    + (0 << 18) /* WAITMONITORINGTIME      [0: "WAIT pin is monitored with valid data",
                                            1: "WAIT pin is monitored one GPMC_CLK cycle before valid data",
                                            2: "WAIT pin is monitored two GPMC_CLK cycle before valid data",
                                            3: "Reserved" ] */
    + (0 << 16) /* WAITPINSELECT           [0: "WAIT input pin is WAIT0",
                                            1: "WAIT input pin is WAIT1",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (1 << 12) /* DEVICESIZE              [0: "8 bit",
                                            1: "16 bit",
                                            2: "Reserved",
                                            3: "Reserved"] */
    + (0 << 10) /* DEVICETYPE              [0: "NOR Flash like, asynchronous and synchronous devices",
                                            1: "Reserved", 
                                            2: "NAND Flash like devices, stream mode",
                                            3: "Reserved" ] */
    + (2 <<  8) /* MUXADDDATA              [0: "Non-multiplexed attached device",
                                            1: "AAD-multiplexed protocol device",
                                            2: "Address and data multiplexed attached device",
                                            3: "Reserved" ] */
    + (0 <<  4) /* TIMEPARAGRANULARITY     [0: "x1 latencies",
                                            1: "x2 latencies"] */
    + (1 <<  0) /* GPMCFCLKDIVIDER         [0: "GPMC_CLK frequency = GPMC_FCLK frequency",
                                            1: "GPMC_CLK frequency = GPMC_FCLK frequency/2",
                                            2: "GPMC_CLK frequency = GPMC_FCLK frequency/3",
                                            3: "GPMC_CLK frequency = GPMC_FCLK frequency/4"] */
    ;

/*  GPMC_CONFIG7_6 */    
    *((volatile unsigned int*)(GPMC_CONFIG7_0 + 6 * 0x30)) =
    0 \
    + (15 << 8) /* MASKADDRESS             [15: "16 MBytes",
                                            14: "32 MBytes"
                                            12: "64 MBytes"
                                             8: "128 MBytes"
                                             0: "256 MBytes" */
    + ( 1 << 6) /* CSVALID                 [ 0: "CSn disabled",
                                             1: "CSn enabled"]: */
    + ( 6 << 0)  /* BASEADDRESS            [ 0..63] << 24 */
    ;

    return 0;
}

int CLKOUT2_activate (void)
{
    #define CM_DEVICE_BASE 0x44E00700
    #define CM_CLKOUT_CTRL (CM_DEVICE_BASE + 0x0)
    
    #define ControlModule_BASE 0x44E10000
    #define conf_xdma_event_intr1 (ControlModule_BASE + 0x9B4)
    
    /* Sets CLKOUT2 to 200MHz for synchronous FPGA communication*/
    
    printf ("Configures CLKOUT2 to 200 MHz FCLK\n");
    
    *((volatile unsigned int*) CM_CLKOUT_CTRL) =
    0
    + (1 << 7) /* CLKOUT2EN               [ 0: "SYS_CLKOUT2 is disabled",
                                            1: "SYS_CLKOUT2 is enabled" ] */
    + (0 << 3) /* CLKOUT2DIV              [ 0: "SYS_CLKOUT2 / 1",
                                            1: "SYS_CLKOUT2 / 2",
                                            2: "SYS_CLKOUT2 / 3",
                                            3: "SYS_CLKOUT2 / 4",
                                            4: "SYS_CLKOUT2 / 5",
                                            5: "SYS_CLKOUT2 / 6",
                                            6: "SYS_CLKOUT2 / 7",
                                            7: "SYS_CLKOUT2 / 8" ] */
    + (1 << 0)  /* CLKOUT2SOURCE          [ 0: "Select 32KHz Oscillator O/P",
                                            1: "Select L3 Clock",
                                            2: "Select DDR PHY Clock",
                                            3: "Select 192Mhz clock from PER PLL",
                                            4: "Select LCD Pixel Clock",
                                            5: "Reserved",
                                            6: "Reserved",
                                            7: "Reserved" ] */
    ;
    
    /*Check setting:*/
    if (((*((volatile unsigned int *) CM_CLKOUT_CTRL) ) & 0x000000BF ) != 0x00000081)
    {
        printf ("Configuration of CLKOUT2 PLL was not successful.\n");
        return -1;
    }
    /* Set pin muxing */
    *((volatile unsigned int *) conf_xdma_event_intr1) =
    0
    + (0 << 6) /* slew_ctrl               [ 0: "Fast"
                                            1: "Slow" ]*/
    + (0 << 5) /* rx_active               [ 0: "Receiver disabled"
                                            1: "Receiver enabled" ]*/
    + (1 << 4) /* pu_type_sel             [ 0: "Pulldown selected"
                                            1: "Pullup selected" ]*/
    + (1 << 3) /* pu_d_en                 [ 0: "Pullup/pulldown enabled"
                                            1: "Pullup/pulldown disabled" ]*/
    + (3 << 0) /* mode                    [ 0: "XMDA_event_intr1"
                                            1: "reserved"
                                            2: "tclkin"
                                            3: "clkout2"
                                            4: "timer7"
                                            5: "pr1_pru0_pru_r31_16"
                                            6: "EMU3"
                                            7: "gpio0_20" ]*/
    ;

    /* Check setting:*/
    if ( ( (*( (volatile unsigned int *) conf_xdma_event_intr1) ) & 0x0000007F ) != 0x0000001B)
    {
        printf ("Configuration of conf_xdma_event_intr1 pin was not successful.\n");
        return -1;
    }
    return 0;
}


int gpmc_init_duagon_i10x (void)
{
    
    /*Activate Synchron Clock of FCLK to CLKOUT2*/
    CLKOUT2_activate ();
    
    if (gpmc_init_NAND ()) /* Todo check, Is already in TI81xx activated*/
    {
        printf ("gpmc_init_duagon_i10x (): gpmc_init_NAND () returned error. Aborting gpmc_init_duagon_i10x().\n");
        return -1;
    }
    if (gpmc_init_FRAM ())
    {
        printf ("gpmc_init_duagon_i10x (): gpmc_init_FRAM () returned error. Aborting gpmc_init_duagon_i10x().\n");
        return -1;
    }
    if (gpmc_init_FPGA_ASYNC ())
    {
        printf ("gpmc_init_duagon_i10x (): gpmc_init_FPGA_ASYNC () returned error. Aborting gpmc_init_duagon_i10x().\n");
        return -1;
    }
    if (gpmc_init_FPGA_SYNC ())
    {
        printf ("gpmc_init_duagon_i10x (): gpmc_init_FPGA_SYNC () returned error. Aborting gpmc_init_duagon_i10x().\n");
        return -1;
    }
    if (gpmc_init_CS4 ())
    {
        printf ("gpmc_init_duagon_i10x (): gpmc_init_CS4 () returned error. Aborting gpmc_init_duagon_i10x().\n");
        return -1;
    }
    if (gpmc_init_CS5 ())
    {
        printf ("gpmc_init_duagon_i10x (): gpmc_init_CS5 () returned error. Aborting gpmc_init_duagon_i10x().\n");
        return -1;
    }
    if (gpmc_init_CS6 ())
    {
        printf ("gpmc_init_duagon_i10x (): gpmc_init_CS6 () returned error. Aborting gpmc_init_duagon_i10x().\n");
        return -1;
    }
    if (gpmc_init_general ())
    {
        printf ("gpmc_init_duagon_i10x (): gpmc_init_general () returned error. Aborting gpmc_init_duagon_i10x().\n");
        return -1;
    }

#ifdef GPMC_DEBUG_general
    if (print_GPMC_CONFIG_register ())
        {
            printf ("print_GPMC_CONFIG_register () returned ERROR. Aborting gpmc_init_duagon_i10x ()\n");
            return -1;
        }
#endif
#ifdef GPMC_DEBUG_CS
    int CS_ID = 0;
    for ( CS_ID = 0; CS_ID <= 0; CS_ID++)
        if (print_GPMC_CONFIG_CS_register (CS_ID))
        {
            printf ("print_GPMC_CONFIG_CS_register () returned ERROR. Aborting gpmc_init_duagon_i10x ()\n");
            return -1;
        }
#endif
#ifdef GPMC_DEBUG_NAND
    int NAND_ID = 0;
    for ( NAND_ID = 0; NAND_ID <= 0; NAND_ID++)
        if (print_GPMC_CONFIG_NAND_register (NAND_ID))
        {
            printf ("print_GPMC_CONFIG_NAND_register () returned ERROR. Aborting gpmc_init_duagon_i10x ()\n");
            return -1;
        }
#endif
#ifdef GPMC_DEBUG_PREFETCH
    if (print_GPMC_PREFETCH_register ())
    {
        printf ("print_GPMC_PREFETCH_register () returned ERROR. Aborting gpmc_init_duagon_i10x ()\n");
        return -1;
    }
#endif
#ifdef GPMC_DEBUG_ECC
    if (print_GPMC_ECC_register ())
    {
        printf ("print_GPMC_ECC_register () returned ERROR. Aborting gpmc_init_duagon_i10x ()\n");
        return -1;
    }
#endif
#ifdef GPMC_DEBUG_BCH
    int BCH_ID = 0;
    for ( BCH_ID = 0; BCH_ID <= 0; BCH_ID++)
        if (print_GPMC_CONFIG_BCH_register (BCH_ID))
        {
            printf ("print_GPMC_CONFIG_BCH_register () returned ERROR. Aborting gpmc_init_duagon_i10x ()\n");
            return -1;
        }
#endif
    return 0;
}
#endif
