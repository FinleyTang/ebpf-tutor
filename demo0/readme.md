


## eBPF 程序的基本框架
如上所述， eBPF 程序的基本框架包括：

- 包含头文件：需要包含 <linux/bpf.h> 和 <bpf/bpf_helpers.h> 等头文件。
- 定义许可证：需要定义许可证，通常使用 "Dual BSD/GPL"。
- 定义 BPF 函数：需要定义一个 BPF 函数，例如其名称为 handle_tp，其参数为 void *ctx，返回值为 int。通常用 C 语言编写。
- 使用 BPF 助手函数：在例如 BPF 函数中，可以使用 BPF 助手函数 bpf_get_current_pid_tgid() 和 bpf_printk()。
返回值

## 下载安装 eunomia-bpf 开发工具
下载 ecli 工具，用于运行 eBPF 程序：

```
$ wget https://aka.pw/bpf-ecli -O ecli && chmod +x ./ecli
$ ./ecli -h
Usage: ecli [--help] [--version] [--json] [--no-cache] url-and-args
```
下载编译器工具链，用于将 eBPF 内核代码编译为 config 文件或 WASM 模块：
```shell
$ wget https://github.com/eunomia-bpf/eunomia-bpf/releases/latest/download/ecc && chmod +x ./ecc
$ ./ecc -h
eunomia-bpf compiler
Usage: ecc [OPTIONS] <SOURCE_PATH> [EXPORT_EVENT_HEADER]
....
```

## 执行 
使用 ecc 编译程序：
```shell
../tools/ecli 
ecli
```

然后使用 ecli 运行编译后的程序：
```shell
root@ftang-virtual-machine:/home/ftang/mylab/ebpf-tutor/demo0# ../tools/ecli run package.json 
INFO [faerie::elf] strtab: 0x25c symtab 0x298 relocs 0x2e0 sh_offset 0x2e0
INFO [bpf_loader_lib::skeleton::preload::section_loader] User didn't specify custom value for variable pid_filter, use the default one in ELF
INFO [bpf_loader_lib::skeleton::poller] Running ebpf program...

```

查看 /sys/kernel/debug/tracing/trace_pipe 文件来查看 eBPF 程序的输出
```shell
$ sudo cat /sys/kernel/debug/tracing/trace_pipe | grep "BPF triggered sys_enter_write"
           <...>-3840345 [010] d... 3220701.101143: bpf_trace_printk: write system call from PID 3840345.
           <...>-3840345 [010] d... 3220701.101143: bpf_trace_printk: write system call from PID 3840345.

```