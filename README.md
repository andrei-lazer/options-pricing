
# Options Pricing
An exploration of various different options pricing methods in C++.

## Black-Scholes European Options Pricing
Here, I have used the common closed form solution for the value of a european option derived from the Black-Scholes equation:
$$\frac{\partial V}{\partial t} + \frac{1}{2}\sigma S^2 \frac{\partial^2 V}{\partial S^2} + rS\frac{\partial V}{\partial S} - rV = 0$$

Solving this for the boundary conditions of a call option,
$$C(0, t) = 0  \enspace \forall t$$
$$C(S, t) \rightarrow S \enspace \text{as} \enspace S \rightarrow \infty$$
$$C(S, T) = \max\{S-K, 0\}$$

gives the following closed form:

$$C(S, t) = N(d_+)S - N(d_-)Ke^{-r(T-t)}$$

$$d_+ = \frac{1}{\sqrt{T - t}}\left[\ln\left(\frac{S}{K}\right) + \left(r + \frac{\sigma^2}{2}\right)\left(T - t\right)\right]$$

$$d_- = d_+ - \sigma\sqrt{T - t}.$$


Where $N(x)$ is the c.d.f of the normal distribution.

This first model simply uses this explicit formula to calcuate prices for a call or put European vanilla option. I've done this to acquaint myself with the mathematics behind options pricing, as well as to have a way of testing any future approaches to the same problem.

Below are some test parameters, as well as the predicted call and put prices. All of the time units are in years.

```
Price of underlying: 100
Strike price: 100
Risk-free rate: 0.05
Volatility: 0.1
Time to expiry: 1
Call price: 6.80496
Put price: 1.9279
```

