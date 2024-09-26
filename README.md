# module_diago

This is a minimal eigenvalue solver package using davidson subspace method with [pybind11](https://github.com/pybind/pybind11) and scikit-build-core.

# Installation

- Create and activate a new conda env
```shell
conda create -n pydav python=3.8 & conda activate pydav
```
- Clone this repository
```shell
git clone https://github.com/haozhihan/module_diago.git
git submodule update --init --recursive
cd module_diago
```
- Build pyabacus by `pip install -v .` or install test dependencies & build  pyabacus by `pip install .[test]`. (Use `pip install -v .[test] -i https://pypi.tuna.tsinghua.edu.cn/simple` to accelerate installation process.)

# Test

This project is tested by pytest. Run `pytest -v` in the `tests` directory to test the project.

```shell
cd tests
pytest -v
```

# Usage