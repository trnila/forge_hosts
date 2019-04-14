# Forge /etc/hosts in applications without root

```sh
$ make
$ export LD_PRELOAD=$PWD/change_hosts.so INJECT_HOSTS=$PWD/hosts
$ ./test
$ curl example.com
$ wget -O - example.com
$ firefox example.com
```
