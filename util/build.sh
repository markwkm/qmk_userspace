#!/bin/sh

set -eux

qmk setup -H ./qmk_firmware -y

MAKEFLAGS="EXTRAFLAGS=-DMASTER_LEFT" CONVERT_TO=elite_pi \
        qmk compile -j "$(nproc)" -kb sofle -km rgb_markwkm
mv sofle_rev1_rgb_markwkm_elite_pi.uf2 sofle_rev1_rgb_markwkm_elite_pi-left.uf2

MAKEFLAGS="EXTRAFLAGS=-DMASTER_RIGHT" CONVERT_TO=elite_pi \
        qmk compile -j "$(nproc)" -kb sofle -km rgb_markwkm
mv sofle_rev1_rgb_markwkm_elite_pi.uf2 \
        sofle_rev1_rgb_markwkm_elite_pi-right.uf2
