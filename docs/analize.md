
# Analize in StoneAnalysis

## Why analize audio files ?

Analizing audio file allow to detect sine and cosine frequencies.
This can be very usefull to detect anomaly in mechanics, acoustics, biomedical engineering, signal processing, instrumentation, communications, and more.

## Analize methods

### Discrete Fourier Transform (DFT)

#### Code

```c++
std::vector<std::complex<double>> DFT::analize(std::vector<b2> waves) {
    auto N = waves.size();
    auto K = N;
    std::vector<std::complex<double>> f;
    f.reserve(N);
    for (std::size_t k = 0; k < K; ++k) {
        std::complex<double> correlation(0.0, 0.0);
        for (std::size_t n = 0; n < N; ++n) {
            double realPart = cos(((2 * M_PI) / N) * k * n);
            double imagPart = sin(((2 * M_PI) / N) * k * n);
            std::complex<double> tmpCor(realPart, -imagPart);
            correlation += tmpCor * std::complex<double>(waves[n], 0.0);
        }
        f.push_back(correlation);
    }
    return f;
};
```

#### Limitations

As you can see, from the code above, we iterate two times in all the waves data, which cause the program to have a complexity of O(N²), which can be very ineficient for large audio files. For exemple, a 1 minute file would have ~8e+14 calcul to do (at 48kHz).

### Fast Fourier Transform (FFT)

#### Code

```c++
std::vector<std::complex<double>>
    FFT::getAmplitudes(std::vector<std::complex<double>> waves)
{
    std::size_t N = waves.size();
    std::size_t M = N / 2;
    if (N <= 1)
        return waves;

    std::vector<std::complex<double>> evenPart; 
    evenPart.reserve(M);
    std::vector<std::complex<double>> oddPart;
    oddPart.reserve(M);
    for (std::size_t k = 0; k < M; ++k) {
        evenPart.emplace_back(waves[k * 2]);
        oddPart.emplace_back(waves[(k * 2) + 1]);
    }
    std::vector<std::complex<double>> evenComputed
        = getAmplitudes(std::move(evenPart));
    std::vector<std::complex<double>> oddComputed
        = getAmplitudes(std::move(oddPart));
    std::complex<double> base(cos((2 * M_PI) / N), -sin((2 * M_PI) / N));
    std::complex<double> w(1.0, 0.0);
    std::vector<std::complex<double>> amplitudes(N);
    for (std::size_t k = 0; k < M; ++k) {
        std::complex<double> C = w * oddComputed[k];
        amplitudes[k] = evenComputed[k] + C;
        amplitudes[k + M] = evenComputed[k] - C;
        w *= base;
    }
    return amplitudes;
}
std::vector<std::complex<double>> FFT::analize(std::vector<b2> waves)
{
    std::vector<std::complex<double>> complexWaves;
    std::size_t N = waves.size();
    std::size_t next = std::__bit_ceil(N);
    complexWaves.reserve(next);
    for (std::size_t i = 0; i < N; ++i)
        complexWaves.emplace_back(waves[i], 0);
    for (std::size_t i = N; i < next; ++i)
        complexWaves.emplace_back(0, 0);
    return getAmplitudes(complexWaves);
};
```

#### Limitations

Not like the DFT, the FFT have a complexity of O(Nlog(N)), which is way faster for long audio files. Unlike the DFT, for a 1 minute .wav file would have 2e+7 wich is way faster, but not as precise for small .wav files.
