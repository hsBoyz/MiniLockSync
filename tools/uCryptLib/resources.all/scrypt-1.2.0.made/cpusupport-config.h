#define CPUSUPPORT_X86_CPUID
#define CPUSUPPORT_X86_SSE2
#define CPUSUPPORT_X86_AESNI
#ifdef cpusupport_dummy
export CFLAGS_X86_AESNI="-maes"
#endif
