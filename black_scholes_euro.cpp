// European options pricing using Black-Scholes (analytic).

#include <iostream>
#include <cmath>
#include <string>

double N(double value) {
    return 0.5 * erfc(-value * pow(0.5, 0.5));
}

double call_price(double S, double sigma, double T, double K, double r, double t) {
    double d_plus = (1 / (sigma * pow(T - t, 0.5))) * (log(S / K) + (r + sigma * sigma * 0.5) * (T - t));
    double d_minus = d_plus - sigma * pow(T - t, 0.5);

    return N(d_plus) * S - N(d_minus) * K * exp(-r * (T - t));
}

double put_price(double S, double sigma, double T, double K, double r, double t) {
    return call_price(S, sigma, T, K, r, t) - S + K * exp(-r * (T - t));
}


int main()
{
    double S = 100.0;  // Underlying price
    double K = 100.0;  // Strike price
    double r = 0.05;   // Risk-free rate
    double v = 0.1;    // Volatility of the underlying
    double T;          // One year until expiry
    std::cout << "Enter time to expiry (in years): "; std::cin >> T;

    std::cout << "\nPrice of underlying: " << S << "\nStrike price: " << K << "\nRisk-free rate: " << r << "\nVolatility: " << v << "\nTime to expiry: " << T << std::endl;
    std::cout << "Call price: " << call_price(S, v, T, K, r, 0) << "\nPut price: " << put_price(S, v, T, K, r, 0) << std::endl;

}