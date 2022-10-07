#include <fstream>
#include <complex>
#include <vector>

void ft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>>& output, std::vector<double>& mods, bool forward);
void fft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>>& output, std::vector<double>& mods, bool forward);
std::complex<double> W(unsigned long q, unsigned long p, bool forward);

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
        input.emplace_back(a, b);
    }

    std::vector<std::complex<double>> result = std::vector<std::complex<double>>(N);
    std::vector<double> mods = std::vector<double>(N);

    ft(input, result, mods, true);

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
        mods_file << mods[i] << std::endl;
    }

    return 0;
}

void fft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>>& output, std::vector<double>& mods, bool forward){

}

void ft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>>& output, std::vector<double>& mods, bool forward){
    unsigned long N = input.size();
    double N_sqrt = sqrt((double)N);

    for (unsigned long k = 0; k < N; ++k)
    {
        for (unsigned long n = 0; n < N; ++n)
        {
            output[k] += input[n] * W(n * k, N, forward);
        }

        output[k] *= N_sqrt;
    }

    for (unsigned long i = 0; i < N; ++i)
    {
        mods[i] = abs(output[i]);
    }
}

std::complex<double> W(unsigned long q, unsigned long p, bool forward){
    if (forward) {
        return std::exp(- 2 * M_PI * std::complex(0.0, 1.0) * (double)q / (double)p);
    } else {
        return std::exp(2 * M_PI * std::complex(0.0, 1.0) * (double)q / (double)p);
    }
}
