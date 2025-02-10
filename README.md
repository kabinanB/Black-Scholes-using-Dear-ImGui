<script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
<script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>

# Black-Scholes-using-Dear-ImGui

#### You could download DearImGui here: https://github.com/ocornut/imgui
#### Include these files in the same project directory
# Black-Scholes Formula and Greeks

## Black-Scholes Formula for a Call Option

The price of a European call option is given by:

\[
C = S_0 N(d_1) - K e^{-rT} N(d_2)
\]

Where:
- \( C \) = Price of the call option
- \( S_0 \) = Current price of the underlying asset
- \( K \) = Strike price of the option
- \( r \) = Risk-free interest rate
- \( T \) = Time to maturity
- \( N(\cdot) \) = Cumulative distribution function of the standard normal distribution
- \( d_1 \) and \( d_2 \) are calculated as:

\[
d_1 = \frac{\ln\left(\frac{S_0}{K}\right) + \left(r + \frac{\sigma^2}{2}\right)T}{\sigma \sqrt{T}}
\]

\[
d_2 = d_1 - \sigma \sqrt{T}
\]

- \( \sigma \) = Volatility of the underlying asset

---

## Black-Scholes Formula for a Put Option

The price of a European put option is given by:

\[
P = K e^{-rT} N(-d_2) - S_0 N(-d_1)
\]

Where:
- \( P \) = Price of the put option
- All other variables are the same as in the call option formula.

---

## Greeks

### Delta (\( \Delta \))

Delta measures the sensitivity of the option price to changes in the price of the underlying asset.

- **Call Option Delta:**
\[
\Delta_C = N(d_1)
\]

- **Put Option Delta:**
\[
\Delta_P = N(d_1) - 1
\]

---

### Gamma (\( \Gamma \))

Gamma measures the rate of change of Delta with respect to changes in the underlying asset price.

- **Call and Put Option Gamma:**
\[
\Gamma = \frac{N'(d_1)}{S_0 \sigma \sqrt{T}}
\]

Where \( N'(d_1) \) is the probability density function of the standard normal distribution:

\[
N'(d_1) = \frac{1}{\sqrt{2\pi}} e^{-\frac{d_1^2}{2}}
\]

---

### Vega (\( \nu \))

Vega measures the sensitivity of the option price to changes in volatility.

- **Call and Put Option Vega:**
\[
\nu = S_0 N'(d_1) \sqrt{T}
\]

---

## Summary of Symbols

- \( S_0 \): Current price of the underlying asset
- \( K \): Strike price
- \( r \): Risk-free interest rate
- \( T \): Time to maturity
- \( \sigma \): Volatility of the underlying asset
- \( N(\cdot) \): Cumulative distribution function of the standard normal distribution
- \( N'(\cdot) \): Probability density function of the standard normal distribution
#### Output is this:
![Alt text](Option.png)
![Alt text](Greek.png)
