
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

## Binomial Options Pricing for American Options
This approach uses a binomial tree to generate possible paths of an option, and backtracks through the tree to find the current valuation as a recursive expression in terms of the value of the option at all other nodes in the tree. Essentially, we discretise the time and act like the underlying can either move up by $u$ ($S_{\text{up}} = S \cdot u$) or down by $d = \frac{1}{u}$ ($S_{\text{down}} = S \cdot d$).

First, the tree is generated. This model will be recombinant, which means a moves up and down commute, since we're multiplying by constant $u$ and $d$ factors. There are other models where $u$ and $d$ depend on changing factors, usually the price of the underlying. An example would be mean reversal. I am not doing that here.

If $S_n$ is the value of some node with index $n$, $S_0$ is the value of the underlying at time $T=0$, then:
$$S_n = S_{0} \cdot u^{N_u - N_d}$$

Where $N_u$ is the number of up movements and $N_d$ the number of down movememnts to get to node $n$.

This will only focus on call optoins, since we can derive the price of a put option using put-call parity.

Therefore, the price of a call option at node $n$ is $\max\{S_n - K, 0\}$, with $K$ the strike price.


The interesting part is how we price the option. We find the expected value of the option in the future, and discount it by the risk-free rate.

$$\text{Price} = p \times (\text{Price of option if it goes up}) + (1 - p) \times (\text{Price of option if it goes down})$$

$$C_{t-\Delta t, i} = e^{-r\Delta t}\left(pC_{t, i} + (1 - p)C_{t, i+1}\right)$$

Where $C_{t, i}$ is the price of the call option at node $i$ and time $t$. $\Delta t$ is the discrete time step we're taking. The smaller this is, the more accurate our simulation is.

$$p = \frac{e^{r\Delta t} - d}{u - d}$$

$p$ is set so that the binomial distribution tends to the geometric brownian motion of the underlying as $\Delta t \to 0$.

