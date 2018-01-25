#!/bin/bash
DIR="$(dirname "$(readlink -f "$0")")"
sudo ln -snf $DIR/include /usr/local/include/StealthNLP
make lib
sudo ln -sf $DIR/lib/libstealthnlp.so /usr/local/lib/libstealthnlp.so
sudo ldconfig
