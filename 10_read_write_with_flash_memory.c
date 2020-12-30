#include "MLD/ralink_hwdefs.h"

#define MRD_FLASH_ERASE 	*
#define MRD_FLASH_READ		*
#define MRD_FLASH_WRITE 	*

/*  This Code just can running within Econet platform ,flash driver part doesn't include in this Demo
 *	source at https://svn.mitrastar.com/svn/MLD_CPE/MLD-PI-1.0.0/branch/product/2020/HGW-500TX2X2-E/dev
 */


/* MRD located at block0 of flash */
int zmrd_set_info(zmrd_info_t *mrd)
{
	char *mrdBlock=(char *)ZLD_SYS_FREE_RAM_BASE;
    PMRD_DATA private_mrd = NULL , test_tmp_mrd = NULL;
    int retry=UPGRADE_IMG_RETRY_TIMES;
    unsigned long start_offs=0;

	// MRD information located at the first block of bootloader
	start_offs = 0x0;
    private_mrd = (PMRD_DATA)(ZLD_SYS_FREE_RAM_BASE + MRD_START_OFFSET);

    /* read current MRD from flash */
    if ( MRD_FLASH_READ(start_offs, FLASH_ERASE_SIZE, mrdBlock) ) return -1;
    /* update MRD information */
    private_mrd->CountryCode  = mrd->CountryCode;
    private_mrd->EngDebugFlag   = mrd->engDebugFlag;
    private_mrd->HTP_Switch     = mrd->htpSwitch;
    private_mrd->MainFeatureBit = mrd->mainFeatureBit;
    private_mrd->NumMacAddrs    = mrd->numMacAddrs;
    memcpy(private_mrd->EtherAddr,  mrd->etherAddr, MRD_MAC_ADDR_LEN);
    memcpy(private_mrd->FeatureBits, mrd->featureBits, MRD_FEATUREBITS_LEN);
    strcpy(private_mrd->ProductName, mrd->productName);
    strcpy(private_mrd->SerialNumber, mrd->serialNumber);
    strcpy(private_mrd->VendorName,  mrd->vendorName);
    strcpy(private_mrd->SerialNumber81,  mrd->SN81);
    strcpy(private_mrd->UserPassword, mrd->UserPassword);
	strcpy(private_mrd->WiFi24SSID, mrd->WiFi24SSID);
    strcpy(private_mrd->WpaPskKey, mrd->WpaPskKey);

    /* write back to flash */
    do {
        if (MRD_FLASH_ERASE(start_offs , start_offs+FLASH_ERASE_SIZE , FLASH_ERASE_SIZE) ==0 )
            if (MRD_FLASH_WRITE(start_offs,start_offs+FLASH_ERASE_SIZE, FLASH_ERASE_SIZE, mrdBlock) ==0) break; 
    } while (--retry); 
    if ( retry == 0 ) {
        return -2;
    }
    return 0;
}
