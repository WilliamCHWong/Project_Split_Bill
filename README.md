# Bill Splitter Application

This is a command-line application designed to practice C++ Standard Template Library (STL) algorithms. 
The application helps calculate the distribution of expenses among a group of friends, ensuring a fair and accurate division of a shared bill, including taxes and tips.

## Features

- **Dynamic Creation of Participants**: Allows the user to create as many participants as needed.
- **Itemized Billing**: Facilitates entering prices for each item and assigning the cost to the corresponding participants only.
- **Accurate Distribution**: Distributes the rounding amount accurately instead of simply rounding off.
- **Settlement Calculation**: Calculates how much each participant owes or needs to receive and provides a list of who pays to whom.

- ## Usage

1. **Input Participant Names**: Enter the names of participants. To finish entering names, input `0`.
2. **Enter Item Prices**: Input the price of each item. Assign items to specific participants or the entire group. Enter `0` when finished.
3. **Enter Subtotal, Tax, and Tip**: Provide the subtotal, the calculated tax (HST), and the tip amount.
4. **Calculate Payments**: The application will compute the amount owed or receivable by each participant.
5. **Display Settlement**: The application displays the transactions needed to settle the bill.

6. ## Example

Here is a simple example of the application's flow:

```
Enter a name (or '0' to finish): Alice
Enter a name (or '0' to finish): Benjamin
Enter a name (or '0' to finish): Clara
Enter a name (or '0' to finish): David
Enter a name (or '0' to finish): Emily
Enter a name (or '0' to finish): Frank
Enter a name (or '0' to finish): Grace
Enter a name (or '0' to finish): Henry
Enter a name (or '0' to finish): 0
Enter item price (or '0' to finish): 35.82
< 1 : Alice > < 2 : Benjamin > < 3 : Clara > < 4 : David > < 5 : Emily > < 6 : Frank > < 7 : Grace > < 8 : Henry > < 9 : All >
Enter the person to pay for this item (or '0' to finish): 1
Enter the person to pay for this item (or '0' to finish): 2
Enter the person to pay for this item (or '0' to finish): 4
Enter the person to pay for this item (or '0' to finish): 5
Enter the person to pay for this item (or '0' to finish): 6
Enter the person to pay for this item (or '0' to finish): 7
Enter the person to pay for this item (or '0' to finish): 0
Enter item price (or '0' to finish): 231.89
< 1 : Alice > < 2 : Benjamin > < 3 : Clara > < 4 : David > < 5 : Emily > < 6 : Frank > < 7 : Grace > < 8 : Henry > < 9 : All >
Enter the person to pay for this item (or '0' to finish): 9
Enter item price (or '0' to finish): 0
Enter Subtotal: 267.71
Enter HST: 0
Enter Tip: 0
< 1 : Alice > < 2 : Benjamin > < 3 : Clara > < 4 : David > < 5 : Emily > < 6 : Frank > < 7 : Grace > < 8 : Henry > 
Enter the person who paid (or '0' to finish): 5
Enter the amount paid: 35.82
Enter the person who paid (or '0' to finish): 2
Enter the amount paid: 98.19
Enter the person who paid (or '0' to finish): 6
Enter the amount paid: 66.85
Enter the person who paid (or '0' to finish): 8
Enter the amount paid: 66.85
Enter the person who paid (or '0' to finish): 0
Clara pays 28.98 to Benjamin
Grace pays 34.25 to Benjamin
Grace pays 0.7 to Henry
David pays 34.96 to Henry
Alice pays 2.21 to Henry
Alice pays 31.89 to Frank
Alice pays 0.86 to Emily
```

## Project Structure

- **Header.h**: Contains the class definitions and helper functions for handling participant data, payment processing, and calculations.
- **main.cpp**: The main source file that drives the application's functionality, including user interaction and overall flow.

- ## Learning Focus

This project is designed for practicing:

- C++ Standard Template Library (STL) algorithms, such as `std::sort`, `std::transform`, and `std::accumulate`.
- C++ class structures and object-oriented programming principles.
- Lambda expressions for concise function definitions.
- Command-line interface (CLI) programming in C++.

- ## License

This project is open-source and available for anyone to use or modify for learning purposes.

## Acknowledgments

Thanks for trying out this application! Feel free to suggest improvements or contribute to the project.

