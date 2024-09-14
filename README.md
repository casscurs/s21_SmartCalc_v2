# SmartCalc v2.0

## Overview

SmartCalc v2.0 is an enhanced version of a basic calculator application developed in C++ that supports a variety of arithmetic operations, including handling complex mathematical expressions and functions. This version builds upon the SmartCalc v1.0 project, adding support for plotting functions involving the variable `x`, and incorporating additional features like a credit and deposit calculator.

The application follows the Model-View-Controller (MVC) architectural pattern, ensuring a clean separation between the interface (view), logic (model), and user interaction (controller). Additionally, it implements Dijkstra's algorithm to handle the conversion of infix expressions to reverse Polish notation, allowing for accurate evaluation of expressions.

### Key Features

1. **Arithmetic Calculations**: Supports basic arithmetic operations like addition, subtraction, multiplication, division, modulus, and power operations. It also handles expressions with parentheses and respects the standard order of operations.
  
2. **Mathematical Functions**: Includes support for functions like sine, cosine, tangent, square root, logarithms (natural and common), and inverse trigonometric functions.
  
3. **Variable Support (`x`)**: Allows users to input expressions that contain the variable `x`. The calculator can compute the expression by substituting a specific value for `x` or by plotting the graph of the function involving `x`.
  
4. **Graph Plotting**: Users can plot functions that involve the variable `x`. The graph includes coordinate axes, an adaptive grid, and labels for the axes and scale. The plotting range is customizable, allowing users to specify the domain and codomain.

5. **High-Precision Calculations**: Ensures accuracy up to at least 7 decimal places for floating-point numbers.

6. **Credit and Deposit Calculators**: Provides special modes to calculate monthly payments and overpayments for different types of credit, as well as profitability for deposits with customizable parameters.

## Architecture: MVC Pattern

SmartCalc v2.0 is designed using the **MVC (Model-View-Controller)** pattern to promote modularity and code reusability:

- **Model**: Contains all the business logic, including the core calculation functions for evaluating arithmetic expressions and handling mathematical operations. This is the heart of the application, providing the functionality for SmartCalc.
  
- **View**: Handles the graphical user interface (GUI) for the application. It is responsible for displaying the calculator, input fields, and graphing capabilities, and for interacting with the user.
  
- **Controller**: Acts as an intermediary between the model and the view. It processes user input from the view, updates the model, and refreshes the view accordingly.

### Why MVC?

The MVC pattern separates the core logic from the user interface, making it easier to manage and modify either aspect independently. This modular approach ensures that the business logic can be reused, while keeping the interface adaptable for future improvements.

## Detailed Features

### 1. Arithmetic Operations and Expression Handling

SmartCalc v2.0 handles the following arithmetic operators:

| Operator         | Infix Notation | Reverse Polish Notation |
| ---------------- | -------------- | ----------------------- |
| Addition         | `a + b`        | `a b +`                 |
| Subtraction      | `a - b`        | `a b -`                 |
| Multiplication   | `a * b`        | `a b *`                 |
| Division         | `a / b`        | `a b /`                 |
| Power            | `a ^ b`        | `a b ^`                 |
| Modulus          | `a mod b`      | `a b mod`               |
| Unary plus       | `+a`           | `a +`                   |
| Unary minus      | `-a`           | `a -`                   |

### 2. Supported Functions

The following mathematical functions are available:

| Function         | Notation        |
| ---------------- | --------------- |
| Cosine           | `cos(x)`        |
| Sine             | `sin(x)`        |
| Tangent          | `tan(x)`        |
| Arccosine        | `acos(x)`       |
| Arcsine          | `asin(x)`       |
| Arctangent       | `atan(x)`       |
| Square root      | `sqrt(x)`       |
| Natural log      | `ln(x)`         |
| Common log       | `log(x)`        |

### 3. Graphing Capabilities

SmartCalc v2.0 provides graph plotting functionality for expressions involving the variable `x`. The graph is plotted with the following features:

- Coordinate axes with labels and tick marks.
- Adaptive grid based on the function's range.
- Customizable domain and codomain for the graph.

The domain and codomain are limited to a minimum range of `-1,000,000` to `1,000,000` for both axes, ensuring sufficient range for most practical calculations.

### 4. Credit Calculator (Bonus)

The credit calculator mode allows users to calculate loan repayments with two different methods:

- **Input**: Total loan amount, loan term, interest rate, and type (annuity or differentiated payments).
- **Output**: Monthly payment, overpayment on the loan, and total payment.

### 5. Deposit Calculator (Bonus)

The deposit calculator mode computes the profitability of deposits based on various parameters:

- **Input**: Deposit amount, term, interest rate, tax rate, payment frequency, interest capitalization, replenishment list, and partial withdrawal list.
- **Output**: Accrued interest, tax amount, and final deposit amount at the end of the term.

## Development Requirements

- **C++17**: The program is developed using the C++17 standard.
- **Google Style Guide**: All code follows the Google C++ style guide.
- **Namespace**: All classes and methods are implemented under the `s21` namespace.
- **Unit Testing**: Full unit test coverage is provided for all modules, using the GTest framework.
- **Makefile**: The project includes a Makefile with standard targets (all, install, uninstall, clean, tests).
- **Cross-Platform GUI**: The program uses a cross-platform GUI library (e.g., Qt or GTK+ for Linux, Mac) to implement the graphical interface.

## Conclusion

SmartCalc v2.0 is a powerful, feature-rich calculator application designed for a wide range of arithmetic operations, function evaluations, and graph plotting. The additional credit and deposit calculator features make it a practical tool for financial calculations. Its modular design and adherence to the MVC pattern make it easy to maintain and extend.