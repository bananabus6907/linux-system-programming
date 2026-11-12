#! /bin/bash

day = $(date +'%Y%m%d')

cd ~/analysis_project/data/

find . -type f -name "*.log" ! -name "$day.log" | tar -czf logs.tar.gz -T -

echo "logs.tar.gz로 압축되었습니다."
