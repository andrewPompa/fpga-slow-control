#!/usr/bin/env bash
mkdir ./app
cp -R /run/media/mmcblk0p2/app/* ./app/
cd ./app/python-libs/
cd setuptools-41.0.1/ &&
python setup.py install &&
cd ../gunicorn-19.9.0/ &&
python setup.py install &&
cd ../falcon-2.0.0/ &&
python setup.py install &&
cd ../..
mkdir historic-data
mkdir historic-configurations
mkdir historic-configurations/inactive
mkdir configurations
cd rest-api/
gunicorn -b 172.168.1.201:8000 --reload rest-api:application