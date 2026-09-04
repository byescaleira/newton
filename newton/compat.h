/*
 * newton/compat.h
 *
 * UAPI definitions missing from Debian buster's kernel headers (x86_64).
 * isolate v2.7 targets kernel 5.x+ APIs that buster's glibc 2.28 /
 * linux-libc-dev predate. This header is force-included at the top of
 * every isolate source file during the image build (see Dockerfile.newton).
 */

#ifndef _NEWTON_COMPAT_H
#define _NEWTON_COMPAT_H

#include <sys/syscall.h>
#include <stdint.h>

/* syscall numbers introduced after buster's kernel headers */
#ifndef __NR_pidfd_send_signal
#define __NR_pidfd_send_signal 424
#endif
#ifndef __NR_io_uring_setup
#define __NR_io_uring_setup 425
#endif
#ifndef __NR_io_uring_enter
#define __NR_io_uring_enter 426
#endif
#ifndef __NR_io_uring_register
#define __NR_io_uring_register 427
#endif
#ifndef __NR_pidfd_open
#define __NR_pidfd_open 434
#endif
#ifndef __NR_clone3
#define __NR_clone3 435
#endif
#ifndef __NR_close_range
#define __NR_close_range 436
#endif
#ifndef __NR_openat2
#define __NR_openat2 437
#endif
#ifndef __NR_faccessat2
#define __NR_faccessat2 439
#endif

/* struct clone_args: UAPI since kernel 5.2, absent in buster */
struct clone_args {
  uint64_t flags;
  uint64_t pidfd;
  uint64_t child_tid;
  uint64_t parent_tid;
  uint64_t exit_signal;
  uint64_t stack;
  uint64_t stack_size;
  uint64_t tls;
  uint64_t set_tid;
  uint64_t set_tid_size;
  uint64_t cgroup;
};

/* glibc SYS_* aliases for the syscalls above */
#ifndef SYS_clone3
#define SYS_clone3 __NR_clone3
#endif
#ifndef SYS_pidfd_open
#define SYS_pidfd_open __NR_pidfd_open
#endif
#ifndef SYS_close_range
#define SYS_close_range __NR_close_range
#endif
#ifndef SYS_quotactl_fd
#define SYS_quotactl_fd 443
#endif

/* clone3 flag, kernel 5.7+ */
#ifndef CLONE_INTO_CGROUP
#define CLONE_INTO_CGROUP 0x200000000
#endif

#endif /* _NEWTON_COMPAT_H */