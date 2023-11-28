import os
import sys
import json


def read_code(path: str) -> list:
    code = ""
    with open(path, 'r') as f:
        code = f.readlines()
        f.close()
    return code


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
    
    path = f"{template_root_path}/{substring}.cpp"
    return os.path.exists(path), path


def change_template_code(line: str, path: str) -> list:
    return [f"{x.rstrip()}\n" for x in open(path, 'r').readlines()]


def calculate_padding(line: str, padding: int, extension: str = "cpp", tab_size: int = 4) -> int:
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
        padding = calculate_padding(line, padding, tab_size=4)
        if chk: ret.extend([f"{' '*padding}{s}" for s in change_template_code(line, path)])
        else: ret.append(line)
    return ret


def read_json(path: str) -> dict:
    with open(path, "r") as f:
        data = json.load(f)
        f.close()
    return data


if __name__ == "__main__":
    vscode_template = "docs/index.json"
    test_root_path = f"test/cpp/basic"
    template_root_path = f"src/cpp/basic"

    json_data = read_json(vscode_template)

    snippet = {}
    for k, v in json_data.items():
        filepath = os.path.join(template_root_path, f"{v['name']}.cpp")

        code: list[str] = read_code(filepath)
        while True:
            pre = code[:]
            code = convert_template(pre)
            if "".join(pre) == "".join(code):
                break
        
        code: list[str] = [f"\"{x}\"" for x in code]
        snippet[k] = {
            "prefix": v["prefix"],
            "body": code,
            "description": k
        }
    
    with open("cpp.json", "w") as f:
        json.dump(snippet, f, indent=4, ensure_ascii=False)
        f.close()
