# ps-library 분석

## 목적과 현재 범위

PS 문제 풀이에 사용하는 자료구조와 알고리즘 구현 라이브러리입니다.

파일별 구현을 찾아 사용하는 풀이·알고리즘 자료 모음입니다. 하나의 서비스로 일괄 실행하는 구조로 보기보다 문제 번호나 주제별 소스, 구현 예제와 보조 도구를 구분해서 읽는 것이 적절합니다.

## 주요 구성과 역할

| 경로 | 역할 또는 확인한 내용 |
| --- | --- |
| [docs/](docs/) | 프로젝트 문서 |
| [scripts/](scripts/) | Python 4개 |
| [src/cpp/](src/cpp/) | C++ 76개 |
| [test/](test/) | 테스트·사용 예제 |
| [tags.md](tags.md) | 프로젝트 문서 |

파일 구성에서 확인되는 형식은 C++ 103개, Python 4개입니다. 헤더와 예제·보조 코드를 포함한 파일 수이며 기능 개수나 구현 완성도를 뜻하지 않습니다.

## 소스에서 확인한 인터페이스

| 파일 | 정적으로 확인한 정의 |
| --- | --- |
| [scripts/generate_test_code.py](scripts/generate_test_code.py) | `read_test_code`, `parsing`, `check_template_snippet`, `change_template_code`, `calculate_padding`, `convert_template` |
| [scripts/install_vim.py](scripts/install_vim.py) | `get_vim_templates`, `clear_legacy_files`, `main` |
| [scripts/make_vscode_snippets.py](scripts/make_vscode_snippets.py) | `read_code`, `parsing`, `check_template_snippet`, `change_template_code`, `calculate_padding`, `convert_template` |

이 목록은 파일의 함수·클래스 이름과 라우트 정의를 정적으로 읽은 결과입니다. 모든 정의가 공개 API라는 뜻은 아니며 실제 호출 관계와 입력 형식은 각 구현을 함께 확인해야 합니다.

## 설치와 사용을 확인하는 방법

공통 설치 명령을 확인할 수 없는 구성입니다. 사용할 파일의 import, 입력·출력 경로와 개발 환경을 먼저 확인하고 원래 문서의 예제가 있으면 함께 참고합니다.

Python 소스에서 환경 변수 조회에 사용되는 이름으로 `HOME`를 확인했습니다. 값은 자신의 실행 환경에서 설정해야 하며 이 문서에는 접속 정보나 인증 값을 싣지 않습니다.

## 근거와 분석 범위

분석일: 2026-10-13 (Asia/Seoul). 문서 변경 전 소스 기준 커밋: `3fb14f0dd907f38b1e1f2ec25be055dd895cc32a`.

근거는 해당 기본 브랜치의 파일 목록, [README.md](README.md) 및 위에 연결한 소스·설정입니다. Python 파일과 표에 명시한 Notebook은 코드를 실행하지 않고 정적으로 살펴봤습니다. 그 외 파일은 구성과 원래 문서를 기준으로 설명했습니다. 의존성 설치, 학습, 서버·하드웨어 실행과 외부 서비스 연결은 검증하지 않았으므로 운영 상태나 성능의 증거로 사용할 수는 없습니다.
