Car Dealership Management System

=======================================================================================

Overview

This project is a Car Dealership Management System written in C. It allows users to:

View available cars (including brand, year, price, and stock)

Purchase cars with optional discounts

Provide feedback on their experience

View sales statistics, including customer details, discounts, and total sales

Store and retrieve sales data from a file
=======================================================================================

Running the Program

Run the executable file using:

./car_dealership

Follow the on-screen menu options:

Press 'a' to buy a car

Press 'b' to view sales statistics

Press 'x' to exit the program
=======================================================================================

Features

1. View Available Cars

Displays car brands, manufacturing years, prices, and available stock

Sorts cars by manufacturing year in descending order

2. Purchase Cars

Asks for user's name (validates input)

Asks for user's age (must be 18 or above)

Offers a 30% discount for purchasing a second car from the same brand

Stores customer feedback

Updates sales records and car stock

3. View Sales Statistics

Displays details for each sale:

Customer name and age

Amount spent

Discount applied

Feedback provided

Shows the total sales amount

Saves sales details to carTabs.txt

4. Persistent Sales Data

Reads past sales data from carTabs.txt on startup

Appends new sales data to the file
=======================================================================================

