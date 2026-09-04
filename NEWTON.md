# newton — a fork of judge0

Fork of [judge0/judge0](https://github.com/judge0/judge0) tuned for one
job: executing Swift for the exercises of a text-first iOS curriculum,
and serving the course frontend from the same host.

## Layout

```
newton/                 deployment-only additions (never touch upstream code)
  Dockerfile.newton     image layer: isolate v2.7 sandbox (kernel 6.x / cgroup v2 fix)
  compat.h              UAPI shims for the EOL buster toolchain used to build isolate
  docker-compose.prod.yml   production stack (API not published; Caddy fronts it)
  Caddyfile.newton      site block: /api/* -> API, /* -> frontend/dist
frontend/               the site (starts static; will grow into the course frontend)
  index.html            placeholder aligned to the byescaleira design system
```

The Rails API stays byte-identical to upstream so the fork stays
mergeable; every newton-specific change lives in `newton/` or `frontend/`.

## Why the sandbox image is replaced

The stock image ships isolate 1.8.1, which crashes on modern kernels
(dynamic-loader segfault inside the sandbox) and predates cgroup v2.
Submissions returned "Internal Error" until isolate was replaced with
v2.7. Inside the container, cgroup controllers cannot be delegated
("no internal processes" rule), so the compose file enables
per-process/thread limits — isolate then enforces limits with RLIMITs
instead of cgroups, which is fully supported by v2.7.

## Deploy (VPS, Caddy, one host)

```bash
/opt/newton $ docker compose -f newton/docker-compose.prod.yml up -d --build
# Caddy: import newton/Caddyfile.newton into the site block, then
systemctl reload caddy
```

API: `https://newton.byescaleira.com/api`
Frontend: `https://newton.byescaleira.com/`

Swift is language id 83 (5.2.3). Upgrade to 6.x is planned; the host
toolchain at `/opt/swift` (6.0.3) is the candidate.