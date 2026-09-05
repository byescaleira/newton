# Newton — the iOS curriculum platform

Newton hosts a text-first iOS course (zero to specialist) on
[Frappe LMS](https://github.com/frappe/lms) (AGPL-3.0), vendored in this
repo. Lessons are markdown with fenced code blocks — no video, code is
displayed, not executed.

## Layout

```
lms/         Frappe LMS app (Python, vendored from frappe/lms develop)
frontend/    LMS web client (Vue 3 + Frappe UI, vendored)
deploy/      deployment-only additions
  docker-compose.prod.yml   production stack (ghcr.io/frappe/lms:stable)
  Caddyfile.newton          Caddy site block
NEWTON.md    this file
```

## Provenance

Vendored from frappe/lms `develop`. To update from upstream:

```bash
git remote add lms-upstream https://github.com/frappe/lms.git
git fetch lms-upstream develop
git merge lms-upstream/develop   # or subtree if restructured
```

## Deploy (VPS, Docker, Caddy)

```bash
# on the VPS
cd /opt/newton
cp deploy/env.example deploy/.env   # fill strong passwords
docker compose -f deploy/docker-compose.prod.yml up -d

# Caddy: import deploy/Caddyfile.newton, then systemctl reload caddy
```

The stack: `web` (nginx frontend, localhost:8080) + `backend` (gunicorn) +
`websocket` + `scheduler` + `queue-short/long` workers + `mariadb:11.8` +
two `redis:6.2-alpine`. Caddy fronts it at the site root.

Site name inside bench: `newton`. Admin password set on first
`create-site` run via `ADMIN_PASSWORD` in `.env`.