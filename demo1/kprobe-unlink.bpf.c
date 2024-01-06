#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

char LICENSE[] SEC("license") = "Dual BSD/GPL";

SEC("kprobe/do_linkat")
int BPF_KPROBE(do_linkat, int dfd, struct filename *name, struct  filename *newfile)
{
    pid_t pid;
    const char* filename;
    const char* newfilename;
    pid = bpf_get_current_pid_tgid() >>32;
    filename = BPF_CORE_READ(name, name);
    newfilename = BPF_CORE_READ(newfile, name);
    bpf_printk("KPROBE ENTRY pid = %d, filename = %s newfilename = %s\n", pid, filename, newfilename);
    return  0;
}

SEC("kretprobe/do_linkat")
int BPF_KRETPROBE(do_linkat_exit, long ret)
{
    pid_t pid;
    pid = bpf_get_current_pid_tgid() >> 32;
    bpf_printk("KPROBE EXIT: pid = %d, ret = %ld\n", pid, ret);
    return 0;
}

