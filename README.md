# Black-Scholes Model with Monte Carlo Simulation

## Overview

This project implements a C++ Black-Scholes model to calculate option pricing using a Monte Carlo simulation. It employs Cholesky matrix decomposition for efficient computation, utilizes the Boost library for generating random values, and provides seamless user input for stock values related to both call and put options.

## Features

- **Monte Carlo Simulation**: Generates multiple matrix paths to simulate stock price movements, allowing for accurate option pricing.
- **Cholesky Matrix Decomposition**: Enhances computational efficiency by transforming covariance matrices, ensuring faster calculations.
- **Boost Library Integration**: Utilizes the Boost library to generate high-quality random values for the simulations.
- **User-Friendly Input**: Enables users to input stock values effortlessly, facilitating real-time analysis.
- **Fast Greek Value Generation**: Quickly calculates and outputs Greek values, providing insights into option sensitivity and risk management.

## Getting Started

### Prerequisites

- C++ Compiler (e.g., g++, clang++)
- Boost Library (ensure it's installed and configured)
- CMake (optional for build management)


## Getting Started

### Prerequisites

- C++ Compiler (e.g., g++, clang++)
- Boost Library (ensure it's installed and configured)
- CMake (optional for build management)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/blackscholes.git
   cd blackscholes
If you're using CMake, create a build directory:

bash
Copy code
mkdir build
cd build
cmake ..
make
Alternatively, compile the source files directly:

bash
Copy code
g++ -o blackscholes main.cpp -lboost_system -lboost_filesystem
Usage
Run the executable:

bash
Copy code
./blackscholes
Follow the prompts to enter the stock values for the call and put options.

The program will output the calculated option prices along with Greek values.


# Example Outputs

Enter stock price: 100
Enter strike price: 100
Enter time to maturity (in years): 1
Enter risk-free rate: 0.05
Enter volatility: 0.2
Enter option type: call

Call Option Price: $10.45
Delta: 0.54
Gamma: 0.02
Theta: -0.03
Rho: -0.5
Vega: 0.23


Monte Carlo Values: $11.02



# Contributing
Contributions are welcome! Please feel free to open issues or submit pull requests.

# Acknowledgments
Boost Library for its powerful utilities and random number generation.
The foundational concepts of the Black-Scholes model and Monte Carlo simulations for financial modeling.
Investopedia and Columbia School of Economics and Business for research papers for Black Schole and Monte Carlo Simulation.
