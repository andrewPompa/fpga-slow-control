#!/usr/bin/env bash
cp -R /run/media/mmcblk0p2/python-falcon/* ./ &&
cd setuptools-41.0.1/ &&
python setup.py install &&
cd ../gunicorn-19.9.0/ &&
python setup.py install &&
cd ../falcon-2.0.0/ &&
python setup.py install &&
cd .. &&
gunicorn -b 172.168.1.200:8000 --reload bram:application