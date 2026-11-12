# Linux System Programming & Analysis

리눅스 시스템 프로그래밍 및 운영체제 과제 모음입니다.

## 프로젝트 개요

리눅스 환경에서의 시스템 프로그래밍, 프로세스 간 통신(IPC), 파일 시스템 분석 등을 다루는 과제들로 구성되어 있습니다.

## 과제 목록

### Assignment 6: Process Management
**주제**: 프로세스 생성 및 좀비 프로세스 관리

- `zombie.c`: 좀비 프로세스 생성 및 처리
- fork(), wait() 시스템 콜 활용
- 프로세스 생명주기 이해

### Assignment 10: Inter-Process Communication (IPC)
**주제**: 공유 메모리를 이용한 프로세스 간 통신

**파일 구성**:
- `talker.c`: 메시지 송신 프로세스
- `listener.c`: 메시지 수신 프로세스
- `pipecode.c`: 파이프 통신 예제

**기술**:
- Shared Memory (shmget, shmat, shmdt)
- 양방향 통신 구현
- 동기화 메커니즘

**실행 방법**:
```bash
# 컴파일
gcc talker.c -o talker
gcc listener.c -o listener

# 실행 (두 개의 터미널 필요)
# 터미널 1
./talker

# 터미널 2
./listener
```

### Assignment 11: File System Analysis & Organization
**주제**: 파일 분류 및 시스템 분석 자동화

**주요 스크립트**:
- `assignmnet.sh`: 확장자별 파일 자동 정리
  - 입력한 확장자별 폴더 생성 및 파일 이동
  - 남은 파일은 `others/` 폴더로 자동 분류
  - 오류 처리 및 입력 검증

**사용법**:
```bash
# 디렉토리 경로와 정리할 확장자들을 지정
./assignmnet.sh /path/to/directory jpg png txt pdf

# 결과 구조:
# target_directory/
# ├── jpg/       # .jpg, .jpeg 파일들
# ├── png/       # .png 파일들
# ├── txt/       # .txt 파일들
# ├── pdf/       # .pdf 파일들
# └── others/    # 나머지 모든 파일
```

**특징**:
- 대소문자 구분 없이 확장자 인식 (`-iname`)
- jpg와 jpeg를 동일하게 처리
- 파일 존재 여부 사전 검사
- 오류 발생 시 즉시 종료 (`set -e`)

## 유틸리티 스크립트

### analysis.sh
**기능**: 프로젝트 내 파일 통계 분석

```bash
./analysis.sh
```

**출력 정보**:
- 파일 종류별 개수 (텍스트, 스크립트, 숨김 파일)
- 텍스트 파일 상세 분석 (줄/단어/글자 수)

### pt.sh / tar.sh
백업 및 압축 관련 유틸리티 스크립트

## 프로젝트 구조

```
analysis_project/
├── assignment6/           # 프로세스 관리
│   ├── zombie.c
│   └── programs/
├── assignment10/          # IPC
│   ├── talker.c
│   ├── listener.c
│   └── pipecode.c
├── assignment11/          # 파일 시스템
│   ├── assignmnet.sh
│   └── test_files/
├── homework/              # 연습 과제
├── practice/              # 실습 코드
├── data/                  # 테스트 데이터
└── files/                 # 추가 파일

utils/
├── analysis.sh            # 파일 분석 도구
├── pt.sh                  # 백업 유틸리티
└── tar.sh                 # 압축 유틸리티
```

## 학습 주제

### 시스템 프로그래밍
- Process Management (fork, exec, wait)
- Inter-Process Communication (Shared Memory, Pipes)
- Signal Handling
- File I/O System Calls

### Shell Scripting
- Bash 스크립트 작성
- 파일 시스템 조작 (find, mv, mkdir)
- 조건문 및 반복문
- 오류 처리 및 입력 검증

### Linux Tools
- GCC 컴파일러
- find, grep, wc
- IPC 관련 명령어 (ipcs, ipcrm)

## 개발 환경

- **OS**: Ubuntu 24.04 LTS
- **Compiler**: GCC
- **Shell**: Bash

## 빌드 및 실행

### C 프로그램 컴파일
```bash
cd assignment10
gcc talker.c -o talker
gcc listener.c -o listener
```

### Shell 스크립트 실행 권한 부여
```bash
chmod +x analysis.sh
chmod +x assignment11/assignmnet.sh
```

## 학습 내용

1. **프로세스 간 통신 (IPC)**
   - 공유 메모리 메커니즘 이해
   - key_t를 이용한 메모리 세그먼트 식별
   - shmget, shmat, shmdt API 활용

2. **파일 시스템 조작**
   - find 명령어의 고급 옵션 활용
   - 파일 확장자 기반 분류 알고리즘
   - 안전한 파일 이동 로직 구현

3. **Shell 스크립트 Best Practices**
   - 입력 검증 및 오류 처리
   - set -e를 통한 안전한 실행
   - 파라미터 처리 ($#, shift)

## 참고 자료

- Advanced Programming in the UNIX Environment (APUE)
- Linux System Programming
- Bash Reference Manual

## 라이선스

Educational Project
