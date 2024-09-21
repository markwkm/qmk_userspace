#!/bin/sh

podman run \
        --rm \
        -it \
        --user "$(id -u):$(id -g)" \
        --userns=keep-id \
        -v "$(dirname "$(realpath "${0}")")/..:/usr/local/src/qmk_userspace:rw,Z" \
        -w /usr/local/src/qmk_userspace \
        ghcr.io/qmk/qmk_cli \
        util/build.sh
