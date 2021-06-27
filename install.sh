#!/bin/bash
git clone  https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake .. && make -j
sudo make install