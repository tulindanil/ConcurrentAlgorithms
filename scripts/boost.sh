#!/bin/bash
wget https://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz/download
mv download boost.tar.gz
gzip -d boost.tar.gz && tar xvf boost.tar > /dev/null
