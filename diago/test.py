import sys
sys.path.append('/home/haozhihan/11-test/module_diago_1/diago/build')


import diago_dav_subspace

diag_comm = diago_dav_subspace.diag_comm_info(1, 4)

print(f'Rank: {diag_comm.rank}, Nproc: {diag_comm.nproc}')


precondition = [1.0, 2.0, 3.0]
obj = diago_dav_subspace.Diago_DavSubspace(precondition, 10, 100, 2, 1e-5, 200, False, diag_comm)

print(obj.get_nbase_x())