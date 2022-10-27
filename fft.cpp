//
// Created by Severin on 07.10.2022.
//

#include "fft.h"
#include <iostream>

std::complex<double> W(uint32_t q, uint32_t p, int8_t sign);

void iter_dft(const std::vector<std::complex<double>> &input, std::vector<std::complex<double>> &result, bool forward)
{
    uint32_t N = input.size();
    int8_t sign = forward ? -1 : 1;

    for (uint32_t k = 0; k < N; ++k)
    {
        for (uint32_t n = 0; n < N; ++n)
        {
            result.at(k) += input.at(n) * W(n * k, N, sign);
        }
    }
}

void rec_fft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>> &result, bool forward)
{
    uint32_t n = input.size();

    if (n < 64){
        iter_dft(input, result, forward);
        return;
    }

    std::vector<std::complex<double>> even_input(n/2);
    std::vector<std::complex<double>> even_result(n/2);

    std::vector<std::complex<double>> odd_input(n/2);
    std::vector<std::complex<double>> odd_result(n/2);

    for (uint32_t i = 0; 2 * i < n; i++) {
        even_input.at(i) = input.at(2 * i);
        odd_input.at(i) = input.at(2 * i + 1);
    }

    rec_fft(even_input, even_result, forward);
    rec_fft(odd_input, odd_result, forward);

    for (uint32_t i = 0; 2 * i < n; ++i)
    {
        result.at(2 * i) = even_result.at(i);
        result.at(2 * i + 1) = odd_result.at(i);
    }

    for (uint32_t i = 0; 2 * i < n; ++i)
    {
        result.at(i) = even_result.at(i) + odd_result.at(i) * W(i, n, forward? -1: 1);
        result.at(i + n/2) = even_result.at(i) + odd_result.at(i) * W(i + n/2, n, forward? -1: 1);
    }
}

/*
 * Performs fast Furrier transform
 */
void fft(std::vector<std::complex<double>> &input,
         std::vector<std::complex<double>> &result,
         std::vector<double> &mods, bool forward)
{
    uint32_t n = input.size();
    double n_inverse_sqrt = 1 / sqrt((double) n);

    rec_fft(input, result, forward);

    for (uint32_t i = 0; i < n; ++i)
    {
        result.at(i) *= n_inverse_sqrt;
    }

    for (uint32_t i = 0; i < n; ++i)
    {
        mods.at(i) = std::abs(result.at(i));
    }
}

/*
 * Performs discrete (not fast) Furrier transform
 */
void dft(std::vector<std::complex<double>> &input,
         std::vector<std::complex<double>> &output,
         std::vector<double> &mods,
         bool forward)
{
    uint32_t N = input.size();
    double N_inverse_sqrt = 1 / sqrt((double) N);
    int8_t sign = forward ? -1 : 1;

    for (uint32_t k = 0; k < N; ++k)
    {
        for (uint32_t n = 0; n < N; ++n)
        {
            output.at(k) += input.at(n) * W(n * k, N, sign);
        }
    }

    for (uint32_t i = 0; i < N; ++i)
    {
        output.at(i) *= N_inverse_sqrt;
    }

    for (uint32_t i = 0; i < N; ++i)
    {
        mods.at(i) = std::abs(output.at(i));
    }
}

/*
 * Returns coefficients of discrete Furrier transform
 */
std::complex<double> W(uint32_t q, uint32_t p, int8_t sign)
{
    return std::exp(sign * 2 * M_PI * std::complex(0.0, 1.0) * (double) q / (double) p);
}
