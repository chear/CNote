#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include "7_ioctl.h"

HI_OS_SOCKET_T hi_os_socket( hi_int32 i_af, hi_int32 i_type,hi_int32 i_protocol );
hi_char8*  hi_os_strcpy( hi_char8 *pc_dest, const hi_char8 *pc_src );
hi_int32 hi_os_close(hi_int32 i_fd);
hi_int32 hi_os_ioctl( HI_OS_SOCKET_T ui_socket,hi_int32  i_cmd,hi_void *pv_arg );
hi_void* hi_os_memcpy( hi_void *pv_buf1, const hi_void *pv_buf2, hi_uint32 ui_count);


int main (int argc, char **argv){

    hi_os_ifreq_s	st_ifr;
    hi_int32	i_sockfd;
    hi_char8	ac_mac[6];
    hi_char8	auc_brmac[18];
    printf(" ===> 7_ioctl Startr\r\n");

    hi_uint32 count = 0;
    while(count < 10000){
        i_sockfd = hi_os_socket(AF_INET, SOCK_DGRAM, 0);
        if (-1 == i_sockfd)
            return 1;
#if 1 
        hi_os_strcpy(st_ifr.ifr_name, "br-lan");
#else
        hi_os_strcpy(st_ifr.ifr_name, "eth0");
#endif
        if (0 == hi_os_ioctl(i_sockfd, SIOCGIFHWADDR, &st_ifr))
        {
            hi_os_memcpy(ac_mac, (const hi_void *)st_ifr.ifr_hiaddr.a_c_sadata, 6);
            sprintf(auc_brmac, 
                    "%02x:%02x:%02x:%02x:%02x:%02x",
                    ac_mac[0], ac_mac[1], ac_mac[2], 
                    ac_mac[3], ac_mac[4], ac_mac[5]);
        }
        else
        {
            hi_os_close(i_sockfd);
            return 1;
        }
        hi_os_close(i_sockfd);
        printf("chear_count = %d,   auc_brmac[%s]\r\n",count ,auc_brmac);
        count ++;
    }

    return 0;
}


/*****************************************************************************
 函 数 名  : hi_os_socket
 功能描述  :建立一个socket通信
 输入参数  :i_af:指定使用何种的地址类型
                         i_type:通信类型
                         i_protocol:用来指定socket所使用的传输协议编号，
                         通常此参考不用管它，设为0即可。
*****************************************************************************/
HI_OS_SOCKET_T hi_os_socket( hi_int32 i_af, hi_int32 i_type,hi_int32 i_protocol )
{
    return socket(i_af,i_type,i_protocol);
}


/*****************************************************************************
 函 数 名  : hi_os_strcpy
 功能描述  : 字符串拷贝，会将源字符串拷贝至目的地址。
 输入参数  : 指向拷贝的源字符串和目的字符串的指针
 返 回 值  :返回参数dest的字符串起始地址。
*****************************************************************************/
hi_char8*  hi_os_strcpy( hi_char8 *pc_dest, const hi_char8 *pc_src )
{
    return (hi_char8*)strcpy(pc_dest,pc_src);
}


/*****************************************************************************
 函 数 名  : HI_IoctlSocket
 功能描述  :SOCKET ioctl
 输入参数  :ui_socket:套接字
                         i_cmd:命令字
                         pv_arg: 参数
*****************************************************************************/
hi_int32 hi_os_ioctl( HI_OS_SOCKET_T ui_socket,hi_int32  i_cmd,hi_void *pv_arg )
{
   return ioctl(ui_socket,(hi_uint32)i_cmd,pv_arg);
}


hi_int32 hi_os_close(hi_int32 i_fd)
{
    return close(i_fd);
}

hi_void* hi_os_memcpy( hi_void *pv_buf1, const hi_void *pv_buf2, hi_uint32 ui_count)
{
    return memcpy(pv_buf1, pv_buf2, ui_count);
}
