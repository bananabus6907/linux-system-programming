#!/bin/bash


cd ~/analysis_project

txt_file=$(find . -type f -name "*.txt" | wc -l)
sh_file=$(find . -type f -name "*.sh" | wc -l)
hidden_file=$(find . -type f -name ".*" | wc -l)

echo "파일 종류별 개수"
echo "텍스트 파일 : $txt_file"
echo "스크립트 파일 : $sh_file"
echo "숨겨진 파일 : $hidden_file"
echo

echo "텍스트 파일 분석하기"

find . -type f -name "*.txt" | while read -r file
do
  filename=$(basename "$file")
  

  line=$(wc -l < "$file")
  word=$(wc -w < "$file")
  char=$(wc -c < "$file")

  echo "- $filename:"
  echo "  - 줄 수 : $line"
  echo "  - 단어 수 : $word"
  echo "  - 글자 수 : $char"
done

