#!/bin/bash

set -e  # 오류 발생 시 즉시 종료

# 1. 파라미터 검사
if [ $# -lt 2 ]; then
    echo "사용법: $0 <디렉토리 경로> <확장자1> [확장자2] ..."
    exit 1
fi

TARGET_DIR="$1"
shift

if [ ! -d "$TARGET_DIR" ]; then
    echo "오류: 디렉토리가 존재하지 않습니다."
    exit 1
fi

cd "$TARGET_DIR"

# ✅ 2. 입력 확장자 파일 존재 여부 먼저 검사
for ext in "$@"
do
    if [ "$ext" = "jpg" ]; then
        COUNT=$(find . -maxdepth 1 -type f \( -iname "*.jpg" -o -iname "*.jpeg" \) | wc -l)
    else
        COUNT=$(find . -maxdepth 1 -type f -iname "*.$ext" | wc -l)
    fi

    if [ "$COUNT" -eq 0 ]; then
        echo "$ext 확장자 파일이 존재하지 않습니다. 스크립트를 종료합니다."
        exit 1
    fi
done

# ✅ 3. 검사 통과 → 실제 정리 시작
for ext in "$@"
do
    mkdir -p "$ext"

    if [ "$ext" = "jpg" ]; then
        find . -maxdepth 1 -type f \( -iname "*.jpg" -o -iname "*.jpeg" \) -exec mv {} "$ext/" \;
    else
        find . -maxdepth 1 -type f -iname "*.$ext" -exec mv {} "$ext/" \;
    fi
done

# ✅ 4. 남은 모든 파일 others로 이동
mkdir -p others
find . -maxdepth 1 -type f -exec mv {} others/ \;

