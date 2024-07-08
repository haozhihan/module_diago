#include "diago/diago_dav_subspace.h"
#include <complex>
// #include "module_hsolver/diago_iter_assist.h"


int main(int argc, char** argv)
{

#ifdef __MPI
        const hsolver::diag_comm_info comm_info = {MPI_COMM_WORLD, 0, 1};
#else
        const hsolver::diag_comm_info comm_info = { 0, 1};
#endif

    // Diago_DavSubspace<T, Device> dav_subspace()
    const int nbasis = 10;
    const int nband = 10;

    std::vector<std::complex<double>> pre_condition(nbasis, {1.0, 0.0});

    hsolver::Diago_DavSubspace<std::complex<double>, base_device::DEVICE_CPU> dav_subspace(
                pre_condition,
                nband,
                nbasis,
                4, // GlobalV::PW_DIAG_NDIM,
                1e-2, // hsolver::DiagoIterAssist<double, base_device::DEVICE_CPU>::PW_DIAG_THR,
                100, // hsolver::DiagoIterAssist<double, base_device::DEVICE_CPU>::PW_DIAG_NMAX,
                false,
                comm_info);
                
        // bool scf;
        // if (GlobalV::CALCULATION == "nscf")
        // {
        //         scf = false;
        // }
        // else
        // {
        //         scf = true;
        // }

        // auto hpsi_func = [](T* hpsi_out,
        //                                 T* psi_in,
        //                                 const int nband_in,
        //                                 const int nbasis_in,
        //                                 const int band_index1,
        //                                 const int band_index2)
        // {
        //         base_device::DEVICE_CPU ctx = {};

        //         const int row = nbasis_in;
        //         const int col = nbasis_in;

        //         gemv_op<double, base_device::DEVICE_CPU>()
        //         (
        //                 ctx,
        //                 'N',
        //                 row,
        //                 col,
                        

        //         )
                

        // }




    return 0;
}