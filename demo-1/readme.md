## setup
apt-get install libbpf-dev bpftool

## 内核头文件生成
我们使用 bpftool 生成内核数据结构定义头文件。BTF 开启后，你可以在系统中找到 /sys/kernel/btf/vmlinux 这个文件，bpftool 正是从它生成了内核数据结构头文件。 生成命令如下：

```
sudo bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h
```


## 编译 eBPF 程序为字节码
有了 eBPF 程序，就可以使用 clang 和 bpftool 将其编译成 BPF 字节码，然后再生成其头文件 execsnoop.skel.h ：

```shell
clang -g -O2 -target bpf -D__TARGET_ARCH_x86_64 -I/usr/include/x86_64-linux-gnu -I. -c execsnoop.bpf.c -o execsnoop.bpf.o
bpftool gen skeleton execsnoop.bpf.o > execsnoop.skel.h
```
## 用户态程序
```shell
clang -g -O2 -Wall -I . -c execsnoop.c -o execsnoop.o
clang -Wall -O2 -g execsnoop.o -static -lbpf -lelf -lz -o execsnoop
```


## ref
https://blog.csdn.net/sinat_22338935/article/details/123318084
