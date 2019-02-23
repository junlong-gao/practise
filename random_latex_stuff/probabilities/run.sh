#!/bin/bash

docker run -i \
           -t \
           -p 8888:8888 \
           -v $(pwd):$(pwd) \
           continuumio/anaconda3 \
           /bin/bash \
           -c "/opt/conda/bin/jupyter notebook --notebook-dir=$(pwd) --ip='*' --port=8888 --no-browser --allow-root"

