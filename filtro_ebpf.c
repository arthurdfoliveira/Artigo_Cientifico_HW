#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 1024);
    __type(key, __u32);
    __type(value, __u32);
} tabela_redirecionamento SEC(".maps");

SEC("tc")
int interceptor_trafego(struct __sk_buff *skb) {
    return BPF_OK;
}

char _license[] SEC("license") = "GPL";