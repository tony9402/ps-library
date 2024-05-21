# e.g. python generate_test_code.py 2d_segment_tree c++
import os
import sys


def read_test_code(path: str) -> list:
    code = ""
    with open(path, 'r') as f:
        code = f.readlines()
        f.close()
    return code # line by line


def parsing(langauge):
    if langauge in ['c++', 'cpp', 'c', 'cc']:
        return ('cpp', 'cpp')
    if langauge in ['python', 'py', 'python3', 'py3']:
        return ('python', 'py')
    if langauge in ['java']:
        return ('java', 'java')
    
    raise NotImplementedError(f"{langauge} is not supported")


def check_template_snippet(line: str) -> bool:
    left = line.find('[[')
    if left == -1:
        return False, ""
    right = line.find(']]', left)
    if right == -1:
        return False, ""
    
    stripped_line = line.strip()
    if not stripped_line.startswith('[[') or not stripped_line.endswith(']]'):
        return False

    substring = line[left+2:right].strip()
    if ' ' in substring:
        return False, ""
    
    path = os.path.join(template_root_path, f"{substring}.{extension}")
    return os.path.exists(path), path


def change_template_code(line: str, path: str) -> list:
    return [f"{x.rstrip()}\n" for x in open(path, 'r').readlines()]


def calculate_padding(line: str, extension: str, padding: int, tab_size: int = 4) -> int:
    if extension == 'cpp':
        return padding + tab_size * (line.count('{') - line.count('}'))
    if extension == 'java':
        return padding + tab_size * (line.count('{') - line.count('}'))
    if extension == 'python':
        if check_template_snippet(line)[0]:
            return len(line) - len(line.lstrip())
    return 0


def convert_template(code: list):
    ret = []
    padding = 0
    for line in code:
        chk, path = check_template_snippet(line)
        padding = calculate_padding(line, extension, padding, tab_size=4)
        if chk: ret.extend([f"{' '*padding}{s}" for s in change_template_code(line, path)])
        else: ret.append(line)
    return ret


def save_code(code: list, extension: str) -> None:
    if type(code) != list:
        raise TypeError(f"Not list type found")
    with open(f"main.{extension}", 'w') as f:
        f.writelines(code)
        f.close()


if __name__ == "__main__":
    if len(sys.argv) < 3:
        raise Exception("Check `argv` again.\nHow to run this code: python generate_test_code.py 2d_segment_tree c++")
    algorithm = sys.argv[1]
    language, extension = parsing(sys.argv[2])
    target = sys.argv[3]
    test_root_path = f"test/{language}/basic"
    template_root_path = f"src/{language}/{target}"

    code = read_test_code(os.path.join(test_root_path, f"{algorithm}.{extension}"))
    while True:
        pre = code[:]
        code = convert_template(pre)
        if ''.join(pre) == ''.join(code): break
    save_code(code, extension=extension)
