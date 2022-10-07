#include <fstream>
#include <complex>
#include <vector>

void fft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>>& output, std::vector<double>& mods, bool forward);

int main()
{
    std::ifstream input_file("data.dat");

    int N;
    std::string s;
    input_file >> s >> N;

    std::vector<std::complex<double>> input = std::vector<std::complex<double>>(N);

    for (int i = 0; i < N; ++i)
    {
        double a, b;
        input_file >> a >> b;
        input.push_back(std::complex<double>(a, b));
    }

    std::vector<std::complex<double>> result = std::vector<std::complex<double>>(N);
    std::vector<double> mods = std::vector<double>(N);

    fft(input, result, mods, true);

    std::ofstream result_file("result.dat");

    result_file << "# " << N << std::endl;

    for (int i = 0; i < N; ++i)
    {
        result_file << result[i].real() << " " << result[i].imag() << std::endl;
    }

    std::ofstream mods_file("abs.dat");

    mods_file << "# " << N << std::endl;

    for (int i = 0; i < N; ++i)
    {
        result_file << mods[i] << std::endl;
    }

    return 0;
}

void fft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>>& output, std::vector<double>& mods, bool forward){

}
