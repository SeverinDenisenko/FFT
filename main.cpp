#include <fstream>
#include <iostream>
#include <bit>

#include "fft.h"

int main()
{
    std::ifstream input_file("data.dat");

    uint32_t N;
    std::string s;
    input_file >> s >> N;
    N = std::bit_ceil(N);

    std::vector<std::complex<double>> input = std::vector<std::complex<double>>(N);

    for (uint32_t i = 0; i < N; ++i)
    {
        double a, b;
        input_file >> a >> b;
        input.emplace_back(a, b);
    }

    std::vector<std::complex<double>> result = std::vector<std::complex<double>>(N);
    std::vector<double> mods = std::vector<double>(N);

    fft(input, result, mods, true);

    std::ofstream result_file("result.dat");

    result_file << "# " << N << std::endl;

    for (uint32_t i = 0; i < N; ++i)
    {
        result_file << result[i].real() << " " << result[i].imag() << std::endl;
    }

    std::ofstream mods_file("abs.dat");

    mods_file << "# " << N << std::endl;

    for (uint32_t i = 0; i < N; ++i)
    {
        mods_file << mods[i] << std::endl;
    }

    return 0;
}
