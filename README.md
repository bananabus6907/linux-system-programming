# 🐧 Linux System Programming

> 운영체제 · 리눅스 시스템 프로그래밍 실습과 과제 모음

리눅스 시스템 콜(프로세스, 환경 변수, 시간 측정, IPC)을 C로 다뤄 보고, Bash 스크립트로 파일을 정리·분석한 실습 코드입니다.

| 항목 | 내용 |
|---|---|
| 언어 | C · Bash |
| 환경 | Ubuntu 22.04 · GCC 11 (저장소의 실습 바이너리 빌드 기준) |
| 주제 | fork/exec/wait · 좀비 프로세스 · 파이프 · System V 공유 메모리 · times() · 환경 변수 · find/wc 기반 스크립트 |

---

## 목차
| 폴더 | 주제 | 핵심 시스템 콜 / 명령 |
|---|---|---|
| [`practice/`](practice) | 시스템 정보, PID, 시간, 환경 변수 실습 | `sysinfo` `getpid` `getppid` `times` `environ` `getenv` `putenv` `setenv` |
| [`fork/`](fork) | 프로세스 복제와 프로그램 교체 | `fork` `execlp` |
| [`homework/`](homework) | 환경 변수 변경, 시스템 콜 실행 시간 측정 | `setenv` `times` `open` `write` |
| [`assignment6/`](assignment6) | 좀비 프로세스 만들기 | `fork` `wait` `exit` |
| [`assignment10/`](assignment10) | 프로세스 간 통신 | `pipe` `shmget` `shmat` `shmdt` `shmctl` |
| [`assignment11/`](assignment11) | 확장자별 파일 자동 정리 스크립트 | `find` `mv` `set -e` |
| 루트 · [`files/`](files) | 분석용 샘플 파일 생성, 파일 통계, 로그 압축 스크립트 | `find` `wc` `tar` `date` |

## 실습 (`practice/`, `fork/`, `homework/`)

| 파일 | 내용 |
|---|---|
| `practice/main.cpp` | `sysinfo()`로 전체·여유 RAM과 프로세스 수 출력 |
| `practice/main1.cpp` | 현재 프로세스의 PID, 부모 PID 출력 |
| `practice/main2.cpp` | `times()`로 반복문 수행 전후의 clock tick 비교 |
| `practice/main3.cpp`, `main4.cpp` | 전역 `environ`과 `main`의 세 번째 인자 `envp`로 환경 변수 전체 출력 |
| `practice/main5.cpp` ~ `main7.cpp` | `getenv`로 조회, `putenv`·`setenv`로 변경 (`setenv` 덮어쓰기 플래그 0/1 차이 확인) |
| `fork/main.cpp` | `fork()`를 중첩 호출했을 때 출력이 몇 번, 어떤 순서로 나오는지 관찰 |
| `fork/exec.cpp` | `execlp("ls", ...)`로 프로세스 이미지를 바꾸면 그 뒤 코드가 실행되지 않음을 확인 |
| `homework/main.cpp` | `LANG` 환경 변수를 읽고 `setenv`로 `ko_KR.UTF-8`로 변경 |
| `homework/time_pra.c` | `write()`를 100만 번 호출해 파일을 쓰고 `times()`로 실제·사용자·시스템 시간 측정 |

`practice/practice1~8`, `homework/homework`, `homework/time_pra`는 위 소스를 빌드한 실행 파일입니다.

## Assignment 6 — 좀비 프로세스 ([`zombie.c`](assignment6/zombie.c))

부모가 자식 두 개를 만든 뒤 `wait()`를 **한 번만** 호출하고 무한 루프에 들어갑니다.
먼저 끝난 자식은 회수되지만, 10초 뒤 끝나는 다른 자식은 부모가 회수하지 않아 **좀비(Z) 상태**로 남습니다.

```bash
gcc assignment6/zombie.c -o zombie && ./zombie &
ps -o pid,ppid,stat,cmd | grep zombie     # 10초 뒤 STAT이 Z인 자식 확인
kill %1                                   # 부모를 끝내면 좀비도 정리됨
```
`assignment6/programs/p1~p6`은 소스 없이 실행 파일만 들어 있습니다.

## Assignment 10 — 프로세스 간 통신

### 파이프 양방향 통신 ([`pipecode.c`](assignment10/pipecode.c))
파이프 두 개(부모→자식, 자식→부모)를 만들고 `fork()` 후 쓰지 않는 끝을 닫아, 부모와 자식이 메시지를 한 번씩 주고받습니다.
```bash
gcc assignment10/pipecode.c -o pipe_comm && ./pipe_comm
```

### 공유 메모리 단방향 통신 ([`talker.c`](assignment10/talker.c) → [`listener.c`](assignment10/listener.c))
- `listener`가 키 `987654`로 100바이트 공유 메모리를 **만들고**(`IPC_CREAT`) 1초마다 내용을 확인해 출력합니다.
- `talker`는 같은 키로 기존 공유 메모리에 붙어 입력한 문장을 씁니다.
- `exit`을 입력하면 둘 다 종료하고, `listener`가 `shmctl(IPC_RMID)`로 공유 메모리를 지웁니다.
- 별도 동기화(세마포어) 없이 주기적으로 확인하는 방식입니다.

```bash
cd assignment10
gcc listener.c -o listener && gcc talker.c -o talker

./listener      # 터미널 1 — 반드시 먼저 실행 (공유 메모리 생성)
./talker        # 터미널 2 — 문장 입력, exit으로 종료

ipcs -m         # 남아 있는 공유 메모리 확인 (비정상 종료 시 ipcrm -m <shmid>)
```

## Assignment 11 — 확장자별 파일 정리 ([`assignmnet.sh`](assignment11/assignmnet.sh))

```bash
chmod +x assignment11/assignmnet.sh
./assignment11/assignmnet.sh <디렉토리> jpg png txt
```
```
<디렉토리>/
├── jpg/      # .jpg + .jpeg (대소문자 무시)
├── png/
├── txt/
└── others/   # 나머지 파일
```
- 인자가 2개 미만이거나 디렉토리가 없으면 사용법을 출력하고 종료
- **옮기기 전에** 입력한 모든 확장자의 파일이 있는지 먼저 검사해, 하나라도 없으면 아무것도 옮기지 않고 종료
- `find -maxdepth 1 -iname`으로 현재 폴더의 파일만 대소문자 구분 없이 찾고, `set -e`로 중간 오류 시 즉시 중단

## 파일 분석 스크립트 (루트, `files/`)

| 스크립트 | 동작 |
|---|---|
| `files/pt.sh` | `analysis_project/files/`에 분석용 텍스트 2개, 숨김 파일 1개, 스크립트 1개 생성 |
| `analysis.sh` | `~/analysis_project` 안의 `.txt`·`.sh`·숨김 파일 개수를 세고, 텍스트 파일별 줄·단어·글자 수 출력 |
| `pt.sh` | `~/analysis_project/data/`에 오늘 날짜 로그와 임의 날짜 로그 5개 생성 |
| `tar.sh` | 오늘 날짜를 뺀 `.log` 파일들을 `logs.tar.gz`로 압축 |

> `tar.sh`의 `day = $(date ...)`는 `=` 양쪽 공백 때문에 변수에 값이 들어가지 않습니다 (`day=$(date +'%Y%m%d')`로 고쳐야 오늘 로그가 제외됨). `files/date.sh`는 작성 중인 미완성 스크립트입니다.

## 디렉토리 구조

```
linux-system-programming/
├── practice/          # main*.cpp 실습 + 빌드된 practice1~8
├── fork/              # main.cpp(fork 중첩), exec.cpp(execlp)
├── homework/          # main.cpp(setenv), time_pra.c(times 측정)
├── assignment6/       # zombie.c, programs/p1~p6(실행 파일)
├── assignment10/      # pipecode.c, talker.c, listener.c
├── assignment11/      # assignmnet.sh
├── files/             # pt.sh, date.sh, analysis_project/files/(샘플 파일)
├── analysis.sh
├── pt.sh
└── tar.sh
```

## 배운 점
- **프로세스**: `fork()` 뒤 부모·자식이 같은 코드를 이어 실행한다는 점, `exec` 계열은 성공하면 돌아오지 않는다는 점, 회수(`wait`)하지 않은 자식이 좀비로 남는 이유
- **IPC**: 파이프는 방향마다 하나씩 필요하고 안 쓰는 끝을 닫아야 한다는 점, 공유 메모리는 생성 순서와 삭제(`IPC_RMID`)를 직접 관리해야 한다는 점
- **시간 측정**: 실제 시간과 사용자·시스템 CPU 시간의 차이 — `write()`를 반복하면 시스템 시간이 늘어남
- **Bash**: 인자 검사(`$#`, `shift`), 사전 검증 후 실행, `find` 옵션 조합, 변수 대입 문법

## 참고 자료
- W. Richard Stevens, *Advanced Programming in the UNIX Environment*
- Robert Love, *Linux System Programming*
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
