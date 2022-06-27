# Assignment 02

## Requirements
- The solution must use the **C language**.
- Define a vector structure with specific operations using a **dynamically allocated array**.
- Use modular programming.
- Source code must be specified and include tests for all non-UI functions.
- The program must not leak memory!
- Use a layered architecture for your application (domain, repository, controller, UI). User interface, domain and data access elements will be stored in different modules. The user interface module will only contain the user interface part.
- Have at least 10 entries available at application startup.
- Handle user input errors gracefully (replace program crashes with nice error messages :blush:).

## Problem Statement
### Tourism Agency
The employees of *“Happy Holidays”* need an application to manage the offers that the agency has. Each **Offer** has a `type` (one of `seaside, mountain or city break`), a `destination`, a `departure date` and a `price`. The employees need the application to help them in the following ways:\
**(a)** Add, delete and update an offer. An offer is uniquely identified by its destination and departure dates.\
**(b)** Display all tourism offers whose destinations contain a given string (if the string is empty, all destinations are considered), and show them sorted ascending by price.\
**(c)** Display all offers of a given type, having their departure after a given date.\
**(d)** Provide multiple undo and redo functionality. Each step will undo/redo the previous operation performed by the user.