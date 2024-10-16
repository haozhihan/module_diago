# module_diago

`module_diago` is a minimal eigenvalue solver package using davidson subspace method with [pybind11](https://github.com/pybind/pybind11) and scikit-build-core.

# Installation

- Create and activate a new conda env
```shell
conda create -n diag_env python=3.8
conda activate diag_env
conda install numpy
conda install scipy
conda install pytest
```
- Clone this repository
```shell
git clone https://github.com/haozhihan/module_diago.git
cd module_diago
git submodule update --init --recursive
```
- Build pyabacus by `pip install -v .` or install test dependencies & build  pyabacus by `pip install .[test]`. (Use `pip install -v .[test] -i https://pypi.tuna.tsinghua.edu.cn/simple` to accelerate installation process.)

# Test

This project is tested by pytest. Run `pytest -v` in the `tests` directory to test the project.

```shell
cd tests
pytest -v
```

# Usage

To use the package, you should first import the package by `import module_diago`.

Currently, `module_diago` implements a diagonalization algorithms in Python, namely `hsolver.dav_subspace`. The function signatures are as follows:

```python
def dav_subspace(
    # Matrix-vector multiplication function, takes a numpy array and returns a numpy array
    mvv_op: Callable[[NDArray[np.complex128]], NDArray[np.complex128]],
    # Initial guess for the set of eigenvectors during diagonalization
    init_v: NDArray[np.complex128],
    # Matrix dimension
    dim: int,
    # Number of eigenvalues required, starting from the smallest eigenvalue, the algorithm will solve for num_eigs eigenvalues
    num_eigs: int,
    # Preconditioning vector
    pre_condition: NDArray[np.float64],
    # Number of vectors allowed in the basis set (dav_ndim * nband)
    dav_ndim: int = 2,
    # Iteration tolerance
    tol: float = 1e-2,
    # Maximum number of iterations
    max_iter: int = 1000,
    # Whether to use subspace function
    need_subspace: bool = False
) -> Tuple[NDArray[np.float64], NDArray[np.complex128]]:
```

`dav_subspace` returns a tuple consisting of an array of eigenvalues and the corresponding set of eigenvectors.

Before calling this function, we need to read a matrix first, which can be downloaded from [https://sparse.tamu.edu/PARSEC](https://sparse.tamu.edu/PARSEC). Then, we could use `scipy` to read it and determine the number of eigenvalues required (8 in this example):

```python
import scipy

h_mat = scipy.io.loadmat(mat_file)['Problem']['A'][0, 0]
dim = h_mat.shape[0]
num_eigs = 8
```

We can also generate a diagonally dominant Hermitian matrix using `numpy`:

```python
import numpy as np

n = 500
h_mat = np.random.rand(n, n)
h_mat = h_mat + h_mat.conj().T + np.diag(np.random.random(n)) * 10
```

Next, we can define the `mvv_op` operator:

```python
def mvv_op(x):
    return h_mat.dot(x)
# Alternatively, you can define it as a lambda function
# mvv_op = lambda x: h_mat.dot(x)
```

Select the initial guess `v0`:

```python
v0 = np.random.rand(nbasis, nband)
```

Compute the preconditioner `precond`. Since the matrix we read is a diagonally dominant sparse matrix, we can calculate the approximate inverse of the diagonal elements of `h_mat` as the preconditioner:

```python
diag_elem = h_mat.diagonal()
# For numerical stability, to prevent some diagonal elements 
# from being too small (close to 0) and causing
# their reciprocals to be infinite, 
# we set points less than 1e-8 to 1e-8
diag_elem = np.where(np.abs(diag_elem) < 1e-8, 1e-8, diag_elem)
precond = 1.0 / np.abs(diag_elem)
```

After completing the above preparations, we can call the pyabacus algorithm to solve the eigenvalue problem!

```python
e, v = dav_subspace(
    mvv_op,
    v0,
    nbasis,
    nband,
    precond,
    dav_ndim=8,
    tol=1e-8,
    max_iter=1000
)

print(f'eigenvalues calculated by pyabacus are: \n', e)
```

You can also refer to the `examples` directory for more examples.
