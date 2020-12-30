#ifndef RALINK_HWDEF_H
#define RALINK_HWDEF_H
/*
 * Board memory type offset
 *
 */
#define ONEK                            1024
#define FLASH_LENGTH_BOOT_ROM           (128*2*ONEK)

/* for NAND block alignment : Peter.Lee.MitraStar 2013-04-17*/
#ifdef TCSUPPORT_BB_NAND
#define FLASH_LENGTH_CFG 				(128*2*ONEK)
#else
#define FLASH_LENGTH_CFG 				(64*ONEK)
#endif
#define ROMFILE_BUFFER_LENGTH			(512 * ONEK)

#define FLASH_RESERVED_AT_END           (64*ONEK) /*reserved for PSI, scratch pad*/
#define FLASH_IMAGE_MAX_SIZE            (6*ONEK*ONEK)
#define BOARD_IMAGE_DOWNLOAD_ADDRESS

#define MAX_SERIAL_NUMBER_81_SIZE 20

/*modify for NAND flash : Peter.Lee.MitraStar 2013-03-27*/
#ifdef TCSUPPORT_BB_NAND
#define BOOT_OFFSET 	 0x0
#else
#define BOOT_OFFSET 	 0xbc000000
#endif

#define IMAGE_BASE 		 BOOT_OFFSET

#ifdef TCSUPPORT_BB_NAND

#ifdef TCSUPPORT_NAND_BMT
/*Since MTK new bad block managment method will take good block to transform logic block
We should use logic size to replace phsical size.
: Peter.Lee.MitraStar 2013-06-06*/
extern int nand_logic_size;
#define FLASH_WHOLE_SIZE  nand_logic_size
#else
#define FLASH_WHOLE_SIZE  nandflash_chip_size() * 1024 * 1024
#endif

#elif TCSUPPORT_BB_SPI
#define FLASH_WHOLE_SIZE  spiflash_sizeInfo()
#else
#define FLASH_WHOLE_SIZE  flash_sizeInfo()
#endif

#define BUFF_BASE_ADDR 0x80020000
#ifdef TCSUPPORT_7526G_AVOID_EXCEPTION_RAM
#define BUFF_32M_BASE_ADDR 0x82000000
#define RAM_SIZE_128MB 0x8000000
#endif
#define BUFF_STORE_ADDR (BUFF_BASE_ADDR + (calculate_dram_size()<<19)) /* start from half of dram */
#define BUFF_CHECKIMAGE_ADDR (BUFF_BASE_ADDR + (calculate_dram_size()<<19) + (calculate_dram_size()<<18)) 
#define BUFF_MULTIBOOT_ADDR BUFF_CHECKIMAGE_ADDR
#define FLASH_BOOT_ADDR 0x0 /* 0xb0000000 */

//peter, for NAND flash, consider chip boundry
#ifdef TCSUPPORT_BB_NAND
#define FLASH_ROM_ADDR 0x40000 /* 0x00020000 */ // reverse 128k for bootloader
#define FLASH_RAS_ADDR 0x80000 /* 0x00040000 */ // reverse 128k for ROM file
#else
#define FLASH_ROM_ADDR 0x20000 /* 0xb0010000 */
#define FLASH_RAS_ADDR 0x30000 /* 0xb0020000 */
#endif

#ifdef TCSUPPORT_MTD_ENCHANCEMENT
#if ((TCSUPPORT_RESERVEAREA_BLOCK != 1)&& (TCSUPPORT_RESERVEAREA_BLOCK != 2)&& (TCSUPPORT_RESERVEAREA_BLOCK !=3)&& (TCSUPPORT_RESERVEAREA_BLOCK !=4))
#define BLOCK_NUM_FOR_RESERVEAREA 4
#else
 #define BLOCK_NUM_FOR_RESERVEAREA TCSUPPORT_RESERVEAREA_BLOCK
#endif
#define RESERVEAREA_SIZE (BLOCK_NUM_FOR_RESERVEAREA * ERASE_SIZE)
#endif

#ifdef ROMD_SUPPORT
#define ROMD_FILE_LEN FLASH_LENGTH_CFG
#else
#define ROMD_FILE_LEN 0
#endif

#ifdef DOUBLE_ROMFILE_SUPPORT
#define SECONDROM_FILE_LEN FLASH_LENGTH_CFG
#else
#define SECONDROM_FILE_LEN 0
#endif

#ifdef TCSUPPORT_MTD_ENCHANCEMENT
#define RESERVED_LEN RESERVEAREA_SIZE
#else
#define RESERVED_LEN 0
#endif

#ifdef DOUBLE_ROMFILE_SUPPORT
#define FLASH_SECONDROM_ADDR (FLASH_WHOLE_SIZE-SECONDROM_FILE_LEN) /* 0xb07f0000 */
#endif

#ifdef ROMD_SUPPORT
#define FLASH_ROMD_ADDR (FLASH_WHOLE_SIZE-ROMD_FILE_LEN-SECONDROM_FILE_LEN)
#define IMAGE_ROMD		(IMAGE_BASE + FLASH_ROMD_ADDR)
#endif

#ifdef	MSTC_DATA_PARTITION
#define RESERVEAREA_FILE_LEN (512 * ONEK)
#define FLASH_RESERVEAREA_ADDR (FLASH_WHOLE_SIZE-ROMD_FILE_LEN-SECONDROM_FILE_LEN-RESERVEAREA_FILE_LEN)
#define	DATA_FILE_LEN	(4 * ONEK * ONEK)
#define	FLASH_DATA_ADDR	(FLASH_WHOLE_SIZE-DATA_FILE_LEN-BOSA_FILE_LEN-NOERASE_FILE_LEN-QTNFW_FILE_LEN-RESERVED_LEN-ROMD_FILE_LEN-SECONDROM_FILE_LEN)
#define	BOSA_FILE_LEN	(2 * ONEK * ONEK)
#define	FLASH_BOSA_ADDR	(FLASH_WHOLE_SIZE-BOSA_FILE_LEN-NOERASE_FILE_LEN-QTNFW_FILE_LEN-RESERVED_LEN-ROMD_FILE_LEN-SECONDROM_FILE_LEN)
#define	NOERASE_FILE_LEN	(2 * ONEK * ONEK)
#define	FLASH_NOERASE_ADDR	(FLASH_WHOLE_SIZE-NOERASE_FILE_LEN-QTNFW_FILE_LEN-RESERVED_LEN-ROMD_FILE_LEN-SECONDROM_FILE_LEN)
#else
#define	DATA_FILE_LEN	0
#define	BOSA_FILE_LEN	0
#define	NOERASE_FILE_LEN	0
#endif	/* MSTC_DATA_PARTITION */

#ifdef	MSTC_APP_PARTITION
#define	QTNFW_FILE_LEN	(9 * ONEK * ONEK)
#define	FLASH_QTNFW_ADDR	(FLASH_WHOLE_SIZE-QTNFW_FILE_LEN-RESERVED_LEN-ROMD_FILE_LEN-SECONDROM_FILE_LEN)
#else
#define	QTNFW_FILE_LEN	0
#endif	/* MSTC_APP_PARTITION */

#ifdef CONFIG_DUAL_IMAGE
#define FLASH_SLAVE_IMAGE_BASE  IMAGE_BASE 
#define CUTDOWN_SIZE  (RESERVED_LEN + ROMD_FILE_LEN + SECONDROM_FILE_LEN + FLASH_RAS_ADDR + QTNFW_FILE_LEN + DATA_FILE_LEN + BOSA_FILE_LEN + NOERASE_FILE_LEN)
#ifdef TCSUPPORT_BB_NAND
#define ERASE_SIZE 0x20000
#ifdef MSTC_FWUPGRADE_PARTITION
#define FLASH_MAIN_IMAGE_SIZE (((FLASH_WHOLE_SIZE - CUTDOWN_SIZE)/3)/ERASE_SIZE)*ERASE_SIZE // Make sure the size plus FLASH_RAS_ADDR is 128KB boundary
#else
#define FLASH_MAIN_IMAGE_SIZE (((FLASH_WHOLE_SIZE - CUTDOWN_SIZE)/2)/ERASE_SIZE)*ERASE_SIZE // Make sure the size plus FLASH_RAS_ADDR is 128KB boundary
#endif
#define FLASH_SLAVE_IMAGE_SIZE FLASH_MAIN_IMAGE_SIZE
#else
#define ERASE_SIZE 0x10000
#define FLASH_MAIN_IMAGE_SIZE ((FLASH_WHOLE_SIZE -CUTDOWN_SIZE)/2&0xFFFF0000)
#define FLASH_SLAVE_IMAGE_SIZE (FLASH_WHOLE_SIZE -FLASH_MAIN_IMAGE_SIZE - CUTDOWN_SIZE)
#endif
#endif

/*
 * MRD offset and definition.
 *
 */
#define	MRD_OFFSET			0xff /* Allows 255 bytes maximum. */
#define MRD_START_OFFSET	(FLASH_LENGTH_BOOT_ROM - MRD_OFFSET - 1) 
#define MRD_LENGTH   		151       
#define MRD_MAC_OFFSET		MRD_START_OFFSET+4+32+32+4	//buntu
#define MRD_MAC_NUM_OFFSET (MRD_START_OFFSET+4+32+32+4+6+22+1+1+2+13)
#define MRD_ATHW_FEATUREBITS_IDX 6
#define MRD_CHECKID_OFFSET  15 //model ID checking 
#define MRD_PON_SN_LENGTH_HEX   16
#define MRD_WIFI_RANDOM_KEY_LEN 24
/*TEF request Wifi password mechanism version:1, generate password which contains a-z, A-Z, 0-9*/
/*Wifi password mechanism version:0, generate password which contains A-F, 0-9, lower security*/
#if defined(MSTC_RANDOM_MRD_WIFI_PSK) //&& !defined(MSTC_TELEFONICA_BRAZIL_LOCAL)
#define MRD_AUTO_GEN_WIFI_KEY_IDX 17
#endif

#define MRD_SUB_COUNTRY_CODE 16 
#define MRD_HPNA_IDX 18
#define MRD_TE_MODE 19 

#define MRD_SERIAL_NUM_LEN			14
#define MRD_VENDOR_NAME_LEN			32
#define MRD_PRODUCT_NAME_LEN		32
#define MRD_MAC_ADDR_LEN			6
#define MRD_FEATUREBITS_LEN			29
#define MRD_GPON_SERIAL_NUM_LEN		MRD_PON_SN_LENGTH_HEX
#define MRD_SN81_LEN				20
#define MRD_USERPASSWORD_LEN		8
#define MRD_WPAPSKKEY_LEN			16
#define MRD_WPARANDOMPSKKEY_LEN		24

/* Added for Data Protection*/
#if defined(MSTC_DATA_PARTITION) && defined(MSTC_DATA_PROTECTION)
/* 
 * MRD_DEBUGFLAG_OFFSET = 
 *    MRD_START_OFFSET + SDRAM_Conf + VendorName + ProductName
 *    + Function_Byte + EtherAddr + SNMP_SYSOBJID + CountryCode 
 *    + ETHER_GPIO + POWER_GPIO + SerialNumber + NumMacAddrs + MrdVer
 */
#define MRD_DEBUGFLAG_OFFSET (MRD_START_OFFSET+4+32+32+4+6+22+1+1+2+13+1+1)
#endif

typedef struct mrd
{
    unsigned char SDRAM_Conf[4];
    unsigned char VendorName[32];		// 36
    unsigned char ProductName[32];		// 68
    unsigned char Function_Byte[4]; 	// 72
    unsigned char EtherAddr[6];			// 78
    unsigned char SNMP_SYSOBJID[22];	// 100
    unsigned char CountryCode;			// 101
    unsigned char ETHER_GPIO;			// 102
    unsigned char POWER_GPIO[2];		// 104
    unsigned char SerialNumber13[13];		// 117
    unsigned char NumMacAddrs;			// 118
    unsigned char MrdVer;				// 119
    unsigned char EngDebugFlag;			// 120
    unsigned char MainFeatureBit;		// 121
    unsigned char FeatureBits[29];		// 150
    unsigned char HTP_Switch;			// 151
    unsigned char WpaPskKey[16];		// 167
	/* Generate user password randomly by production time. __TELEFONICA_SAPIN__, __MSTC__, Stan Su, 20140721. */
    unsigned char UserPassword[8];		// 175
	/*
	unsigned char ponSn[MRD_PON_SN_LENGTH_HEX]; // 191
    unsigned char WpaRandomPskKey[MRD_WIFI_RANDOM_KEY_LEN];	//215
    unsigned char SerialNumber81[20];	//235
    */
    unsigned char SerialNumber81[20];
	unsigned char SerialNumber[24];
	unsigned char WiFi24SSID[16];
} __attribute__((packed)) MRD_DATA, *PMRD_DATA;

/*
 * LED definition
 */

#define LED_HIGH			0x01
#define LED_LOW				0x00
#define GPIO_AH				0x01
#define GPIO_AL				0x00

#ifdef TCSUPPORT_CPU_MT7505
#define GPIO_WPS			0x17
#define GPIO_POWER_GREEN	0x01
#define GPIO_POWER_RED		0x08	//only used for double-colored LED power, not defined yet currently
#define GPIO_DSL			0x03
#define GPIO_INTERNET		0x72
#define GPIO_INTERNET_FAIL	0x67
#define GPIO_ETH_WAN		0x02
#define GPIO_RESET                 0x00
#endif
#ifdef TCSUPPORT_CPU_MT7510
#define GPIO_WPS			0x17
#define GPIO_POWER_GREEN	0x15
#define GPIO_POWER_RED		0x09	//only used for double-colored LED power, not defined yet currently
#define GPIO_DSL			0x66
#define GPIO_INTERNET		0x72
#define GPIO_INTERNET_FAIL	0x67
#define GPIO_ETH_WAN		0x01
#define GPIO_RESET                 0x00
#else
	#ifdef RT63365
	#define SERIAL_GPIO_MAP_OFFSET 80
	#define SERIAL_GPIO_START 0
	#define SERIAL_GPIO_END	15
	#define GPIO_WPS			0x15
	#define GPIO_POWER_GREEN	4
	#define GPIO_UPS_ORANGE		6
	#define GPIO_POWER_RED      6
	#define GPIO_DSL			0x66
	#define GPIO_INTERNET		0x72
	#define GPIO_INTERNET_FAIL	0x67
	#define GPIO_ETH_WAN		0x01
	#define GPIO_RESET                 0x00
	#endif
#endif


#define LED_WPS_OFF				LED_HIGH^GPIO_AH 
#define LED_WPS_ON				LED_LOW^GPIO_AH
#define LED_POWER_OFF			LED_HIGH^GPIO_AL
#define LED_POWER_ON			LED_LOW^GPIO_AL
#define LED_BPOWER_ON			3
#define LED_BPOWER_OFF			4

#define LED_DSL_ON				LED_HIGH^GPIO_AL
#define LED_DSL_OFF				LED_LOW^GPIO_AL
#define LED_INTERNET_ON			LED_HIGH^GPIO_AH
#define LED_INTERNET_OFF		LED_LOW^GPIO_AH
#define LED_INTERNET_FAIL_ON	LED_HIGH^GPIO_AH
#define LED_INTERNET_FAIL_OFF	LED_LOW^GPIO_AH
#define LAN_RESET_ON			LED_HIGH^GPIO_AH
#define LAN_RESET_OFF			LED_LOW^GPIO_AH
#if (defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521))
	#define GPIO_POWER_GREEN		0x06
	#define GPIO_POWER_RED			0x05	//only used for double-colored LED power, not defined yet currently
	#define LED_POWER_ON			0
	#define LED_POWER_OFF			1
	#define GPIO_RESET				0x00
#endif

#endif
