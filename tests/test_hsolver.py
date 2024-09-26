from __future__ import annotations

import pytest
from py_davsubspace import hsolver
import numpy as np
import scipy

def diag_pyabacus(h_sparse, nband, method):
    algo = {
        'dav_subspace': hsolver.dav_subspace
    }
    def mm_op(x):
        return h_sparse.dot(x)

    nbasis = h_sparse.shape[0]

    v0 = np.random.rand(nbasis, nband)

    diag_elem = h_sparse.diagonal()
    diag_elem = np.where(np.abs(diag_elem) < 1e-8, 1e-8, diag_elem)
    precond = 1.0 / np.abs(diag_elem)

    e, _ = algo[method](
        mm_op,
        v0,
        nbasis,
        nband,
        precond,
        dav_ndim=8,
        tol=1e-12,
        max_iter=5000
    )
    
    return e

def diag_eigsh(h_sparse, nband):
    e, _ = scipy.sparse.linalg.eigsh(h_sparse, k=nband, which='SA', maxiter=5000, tol=1e-12)
    return e

@pytest.mark.parametrize("method", [
    ('dav_subspace'),
    # ('davidson'),
])
def test_random_matrix_diag(method):
    np.random.seed(12)
    n = 500
    h_sparse = np.random.rand(n,n)
    h_sparse = h_sparse + h_sparse.conj().T + np.diag(np.random.random(n))*10
    
    e_pyabacus = diag_pyabacus(h_sparse, 8, method)
    e_scipy = diag_eigsh(h_sparse, 8)
    np.testing.assert_allclose(e_pyabacus, e_scipy, atol=1e-8)

@pytest.mark.parametrize("file_name, nband, atol, method", [
    ('./test_diag/Si2.mat', 16, 1e-8, 'dav_subspace'),
    # ('./test_diag/Si2.mat', 16, 1e-8, 'davidson'),
    ('./test_diag/Na5.mat', 16, 1e-8, 'dav_subspace'),
    # ('./test_diag/Na5.mat', 16, 1e-8, 'davidson'),
])
def test_diag(file_name, nband, atol, method):
    h_sparse = scipy.io.loadmat(file_name)['Problem']['A'][0, 0]
    e_pyabacus = diag_pyabacus(h_sparse, nband, method)
    e_scipy = diag_eigsh(h_sparse, nband)
    np.testing.assert_allclose(e_pyabacus, e_scipy, atol=atol)