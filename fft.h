//
// Created by Severin on 07.10.2022.
//

#ifndef NUMERICAL_TASK_7_FFT_H
#define NUMERICAL_TASK_7_FFT_H

#include <complex>
#include <vector>

void dft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>>& output, std::vector<double>& mods, bool forward);
void fft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>>& result, std::vector<double>& mods, bool forward);

void rec_fft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>> &result, bool forward);
void iter_dft(std::vector<std::complex<double>> &input, std::vector<std::complex<double>> &result, bool forward);

#endif //NUMERICAL_TASK_7_FFT_H
