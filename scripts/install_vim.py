import os
import shutil
from glob import glob


HOME_DIR=os.environ.get("HOME", "")
CPP_TEMPLATE=f"{HOME_DIR}/.ps/template/cpp"
CPP_VIM_TEMPLATE="src/cpp/vim"


def get_vim_templates() -> list[str]:
    return glob(f"{CPP_VIM_TEMPLATE}/**.cpp", recursive=True)


def main():
    os.makedirs(CPP_TEMPLATE, exist_ok=True)
    templates = get_vim_templates()
    for file in templates:
        filename = os.path.basename(file)
        shutil.copyfile(file, f"{CPP_TEMPLATE}/{filename}")


if __name__ == "__main__":
    main()