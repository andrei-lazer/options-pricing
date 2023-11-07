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
    double S = 100.0;  // Option price
    double K = 100.0;  // Strike price
    double r = 0.05;   // Risk-free rate (5%)
    double v = 0.2;    // Volatility of the underlying (20%)
    double T;    // One year until expiry
    std::cout << "Enter time to expiry:"; std::cin >> T;
    //std::cout << t;
    std::cout << "Call price: " << call_price(S, v, T, K, r, 0) << "\nPut price: " << put_price(S, v, T, K, r, 0) << std::endl;

}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
