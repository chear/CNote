## 1. insmod modules

```shell
# sudo insmod netl.ko
```
## 2. running netlink userspace app
```shell
# ./client
state_smg
waiting
Received message: I am from
```

dmesg
``` shell
# dmesg
[ 545.278040] my_net_link: self module exited
[ 679.799672] PPP MPPE Compression module registered
[ 4368.567435] netlink_init: create netlink socket ok.
[ 4379.239327] Message received:Hello from
[ 4379.239331] pid:100
[ 4379.239333] my_net_link:send message 'I am from kernel!'.
```

## 3. rmmod netl

``` shell
# sudo rmmod netl
```