/****************************************************************************/
/*
* Copyright (C) 2011-2013 Mitrastar Communications, Corp.
* All Rights Reserved.
*
* Mitrastar Confidential; 
* Protected as an unpublished work, treated as confidential, 
* and hold in trust and in strict confidence by receiving party. 
* Only the employees who need to know such Mitrastar confidential information 
* to carry out the purpose granted under NDA are allowed to access. 
* 
* The computer program listings, specifications and documentation 
* herein are the property of Mitrastar Communications, Corp. and shall 
* not be reproduced, copied, disclosed, or used in whole or in part 
* for any reason without the prior express written permission of 
* Mitrastar Communications, Corp. 
*/
/****************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter_bridge.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_ipv6.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/version.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/etherdevice.h>
#include <linux/proc_fs.h>
#include <linux/wait.h>
#include <linux/jhash.h>
#include <linux/random.h>
#include <asm/unaligned.h>
#include <linux/ppp_defs.h>
#include <linux/rtnetlink.h>
#include <linux/netlink.h>
#include <asm/byteorder.h>


/* TBD to fix this with relative paths */
//#include "../net/bridge/br_private.h"
//
//
//
//#if LINUX_VERSION_CODE>= KERNEL_VERSION(3,18,0)
//static inline unsigned compare_ether_addr(const u8 *addr1, const u8 *addr2)
//{
//	const u16 *a = (const u16 *) addr1;
//	const u16 *b = (const u16 *) addr2;
//
//	//BUILD_BUG_ON(ETH_ALEN != 6);
//	return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2])) != 0;
//}
//#endif

unsigned int httpd_syn_flood_hook_fun(const struct nf_hook_ops *ops,
			       struct sk_buff *skb,
			       const struct net_device *in,
			       const struct net_device *out,
			       int (*okfn)(struct sk_buff *)) {

    struct iphdr *iph;
    iph = ip_hdr(skb);
    char ipaddr[17] = {0};

    /* 'likely' and 'unlikely' used to tell compiler the if block possible can be execute or not,
     *  this should expect the if blocks to be reordered appropriately.
     *  (减少指令跳转带来的损耗)
     */
    if( unlikely(!skb)  ) {
        return NF_ACCEPT;
    }

    if( unlikely(!iph)  ) {
        return NF_ACCEPT;
    }


//    if(trans_port(iph,skb,&sport,&dport) == NO)
//        return ;


    printk(KERN_INFO " httpd_syn_flood_hook: protocol = %d  \n", iph->protocol);

    if( likely(iph->protocol != IPPROTO_TCP )) {
        printk(KERN_INFO " httpd_syn_flood_hook: accept hook_fun \n");
        memset(ipaddr, 0, sizeof(ipaddr));
        uint32_t ip;
        ip =  ntohl(iph->saddr);
        printk(KERN_INFO "receive from %d.%d.%d.%d\n", (ip >> 24)&0xff, (ip>>16)&0xff , (ip>>8)&0xff ,ip&0xff);
        snprintf(ipaddr, sizeof(ipaddr), "%d.%d.%d.%d", (ip >> 24) & 0xff, (ip>>16) & 0xff, (ip >> 8) & 0xff, ip & 0xff);

        if( strcmp(ipaddr, "192.168.1.7") == 0  ) {
            printk(KERN_INFO "receive from 192.168.1.7\n");
        }
    
        return NF_DROP;
    } else {
        printk(KERN_INFO " httpd_syn_flood_hook:nf_accept \n");
        return NF_ACCEPT;	
    }
}

unsigned int httpd_syn_flood_hook_fun_v6(const struct nf_hook_ops *ops,
			       struct sk_buff *skb,
			       const struct net_device *in,
			       const struct net_device *out,
			       int (*okfn)(struct sk_buff *)) {

    struct iphdr *iph;
    iph = ip_hdr(skb);
    char ipaddr[17] = {0};
    
    memset(ipaddr, 0, sizeof(ipaddr));
    uint32_t ip;
    ip =  ntohl(iph->saddr);
    printk(KERN_INFO "httpd_syn_flood_hook_v6 protocol = %d  receive from %d.%d.%d.%d\n",
            iph->protocol,(ip >> 24)&0xff, (ip>>16)&0xff , (ip>>8)&0xff ,ip&0xff);  
    return NF_DROP;
    
}

static struct nf_hook_ops httpd_hook_v4 = { 	
	.hook = httpd_syn_flood_hook_fun,
	.pf = NFPROTO_IPV4 , //  NFPROTO_IPV6, NFPROTO_INET 
	.owner = THIS_MODULE, 	
	.hooknum = 	NF_BR_PRE_ROUTING , //NF_BR_LOCAL_IN, 
	.priority = NF_IP_PRI_FIRST, // NF_IP_PRI_FIRST, //NF_IP_PRI_LAST ;NF_IP_PRI_MANGLE;
};



static struct nf_hook_ops httpd_hook_v6 = { 	
	.hook = httpd_syn_flood_hook_fun_v6,
	.pf = NFPROTO_IPV6 , //  NFPROTO_IPV6, NFPROTO_INET 
	.owner = THIS_MODULE, 	
	.hooknum = 	NF_BR_PRE_ROUTING , //NF_BR_LOCAL_IN, 
	.priority = NF_IP_PRI_FIRST, // NF_IP_PRI_FIRST, //NF_IP_PRI_LAST ;NF_IP_PRI_MANGLE;
};



static int __init httpd_syn_flood_hook_init(void) {


    if ( nf_register_hook(&httpd_hook_v4) != 0  ) {
        printk(KERN_WARNING "register hook error!\n");
        goto err;
    }

    if ( nf_register_hook(&httpd_hook_v6) != 0  ) {
        printk(KERN_WARNING "register hook error!\n");
        goto err;
    }

	printk(KERN_INFO "httpd syn_flood hook Kernel Module Initialized\n");
	return 0;

err:
   	nf_unregister_hook(&httpd_hook_v4);
    return -1;
}


static void __exit httpd_syn_flood_hook_exit(void) {
	nf_unregister_hook(&httpd_hook_v4);
	printk(KERN_INFO "httpd syn_flood hook Kernel Module Deinitialized\n");
	return 0;
}



module_init(httpd_syn_flood_hook_init);
module_exit(httpd_syn_flood_hook_exit);


MODULE_LICENSE("Proprietary");
MODULE_AUTHOR("chear.huang@mitrastar.cn");
MODULE_DESCRIPTION("to fix issue for syn_flood DDos attects");


