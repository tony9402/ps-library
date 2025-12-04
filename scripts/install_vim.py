import os
import shutil
from glob import glob


HOME_DIR=os.environ.get("HOME", "")
CPP_TEMPLATE=f"{HOME_DIR}/.ps/template/cpp"
CPP_VIM_TEMPLATE="src/cpp/vim"


def get_vim_templates() -> list[str]:
    return glob(f"{CPP_VIM_TEMPLATE}/**.cpp", recursive=True)


def clear_legacy_files():
    if not os.path.exists(CPP_TEMPLATE):
        print("Clear")
        return
    files = glob(f"{CPP_TEMPLATE}/*.cpp")
    print(f"Found {len(files)} legacy files")
    for file_path in files:
        print(f"Remove {file_path}")
        os.remove(file_path)


def main():
    clear_legacy_files()
    os.makedirs(CPP_TEMPLATE, exist_ok=True)
    templates = get_vim_templates()
    for file_path in templates:
        filename = os.path.basename(file_path)
        shutil.copyfile(file_path, f"{CPP_TEMPLATE}/{filename}")
        print(f"Install {filename} to {CPP_TEMPLATE}/{filename}")


if __name__ == "__main__":
    main()
