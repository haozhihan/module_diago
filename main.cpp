#include "diago/diago_dav_subspace.h"
#include "diago/module_hsolver/kernels/math_kernel_op.h"
#include <complex>

int main(int argc, char **argv) {

#ifdef __MPI
    const hsolver::diag_comm_info comm_info = {MPI_COMM_WORLD, 0, 1};
#else
    const hsolver::diag_comm_info comm_info = {0, 1};
#endif

    // Diago_DavSubspace<T, Device> dav_subspace()
    const int nbasis = 25;
    const int nband = 5;

    std::vector<double> pre_condition(nbasis, 1.0);

    hsolver::Diago_DavSubspace<std::complex<double>, base_device::DEVICE_CPU>
        dav_subspace(pre_condition, nband, nbasis,
                     2,    // GlobalV::PW_DIAG_NDIM,
                     1e-2, // hsolver::DiagoIterAssist<double,
                           // base_device::DEVICE_CPU>::PW_DIAG_THR,
                     100,  // hsolver::DiagoIterAssist<double,
                           // base_device::DEVICE_CPU>::PW_DIAG_NMAX,
                     false, comm_info);

    auto hpsi_func = [](std::complex<double> *hpsi_out,
                        std::complex<double> *psi_in, const int nband_in,
                        const int nbasis_in, const int band_index1,
                        const int band_index2) {
        const int row = nbasis_in;
        const int col = nbasis_in;

        std::vector<std::complex<double>> h_mat(25 * 25,
                                                std::complex<double>(0.0, 0.0));

        // 填充对角线元素
        for (int i = 0; i < 25; ++i) {
            h_mat[i * 26 + i] = std::complex<double>(1.0, 1.0); // 一个示例值
        }

        // 填充上三角部分
        for (int i = 1; i < 25; ++i) {
            for (int j = 0; j < i; ++j) {
                // 这里使用随机数作为示例，实际应用中应根据问题来填充
                std::complex<double> random_value = std::complex<double>(
                    static_cast<double>(rand() % 100), // 随机实部
                    static_cast<double>(rand() % 100)  // 随机虚部
                );
                h_mat[i * 26 + j] = random_value;
                h_mat[j * 26 + i] =
                    std::conj(random_value); // 填充下三角部分的共轭
            }
        }

        const std::complex<double> *one_ = nullptr, *zero_ = nullptr;
        one_ = new std::complex<double>(1.0, 0.0);
        zero_ = new std::complex<double>(0.0, 0.0);

        base_device::DEVICE_CPU *ctx = {};

        hsolver::gemm_op<std::complex<double>, base_device::DEVICE_CPU>()(
            ctx, 'N', 'N', row, band_index2 - band_index1 + 1, nbasis_in, one_,
            h_mat.data(), nband_in, psi_in + band_index1 * nbasis_in, nbasis_in,
            zero_, hpsi_out + band_index1 * nbasis_in, nbasis_in);
    };

    std::vector<std::complex<double>> psi(nbasis * nband, {1.0, 0.0});

    std::vector<double> eigenvalue(nband, 1.0);

    std::vector<bool> is_occupied(nband, true);

    int res = dav_subspace.diag(hpsi_func, nullptr, psi.data(), nbasis,
                                eigenvalue.data(), is_occupied, true);

    std::cout << "res: " << res << std::endl;

    return 0;
}