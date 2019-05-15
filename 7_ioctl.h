#define   hi_void              void
#define   hi_char8 char                    /**< char */
#define   hi_uchar8 unsigned char         /**< unsigned char */
#define   hi_short16 short                 /**< short */
#define   hi_ushort16 unsigned short      /**< unsigned short */
#define   hi_int32 int                     /**< int */
#define   hi_uint32 unsigned int           /**< unsigned int */


//#define AF_INET		2	/* Internet IP Protocol 	*/
#define HI_IFNAMSIZ      (16)
#define ifr_name      ifr_ifrn.a_c_ifrnname  /* interface name     */
#define ifr_hiaddr    ifr_ifru.ifru_hiaddr   /* MAC address         */

typedef hi_int32    HI_OS_SOCKET_T;

typedef struct {
    hi_uint32   ui_memstart;
    hi_uint32   ui_memend;
    hi_ushort16 uc_baseaddr;
    hi_uchar8   uc_irq;
    hi_uchar8   uc_dma;
    hi_uchar8   uc_port;
    hi_uchar8   uc_resv[3];
}hi_os_ifmap_s;


/* 通用的SOCKET地址结构 */
typedef struct {
  hi_ushort16 us_safamily;
  hi_char8    a_c_sadata[14];
}hi_os_socket_addr_s;

typedef struct hi_ifreq
{
    union
    {
        char a_c_ifrnname[HI_IFNAMSIZ];        /* if name, e.g. "en0" */
    } ifr_ifrn;

    union
    {
        hi_os_socket_addr_s ifru_addr;
        hi_os_socket_addr_s ifru_dstaddr;
        hi_os_socket_addr_s ifru_broadaddr;
        hi_os_socket_addr_s ifru_netmask;
        hi_os_socket_addr_s ifru_hiaddr;
        hi_short16 ifru_flags;
        hi_int32 ifru_ivalue;
        hi_int32 ifru_mtu;
        hi_os_ifmap_s ifru_map;
        hi_char8 ifru_slave[HI_IFNAMSIZ];    /* Just fits the size */
        hi_char8 ifru_newname[HI_IFNAMSIZ];
        hi_char8 * ifru_data;
    } ifr_ifru;
}hi_os_ifreq_s;


