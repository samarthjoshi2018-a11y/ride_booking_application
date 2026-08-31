# Ride Booking Application — LLD

A C++ Low Level Design implementation of a simplified **Ride Booking System**, designed to demonstrate Object-Oriented Programming principles, SOLID principles, and commonly used design patterns.

##  Contributor

**Samarth Joshi**

---

## Problem Statement

The system models a basic ride-booking workflow:

- A user creates a ride request.
- Available drivers are identified and ordered using a strategy.
- The first available driver is assigned the ride.
- A ride is created using a factory.
- The ride is completed through payment and completion stages.

The project focuses on **LLD and design patterns**, rather than building a production-ready ride-booking application.

---

## Architecture

```text
Client
  ↓
Controller
  ↓
Service
  ↓
Main Manager
  ↓
Driver Manager
  ↓
Strategy
  ↓
Available Driver
  ↓
Ride Factory
  ↓
Ride
  ↓
Payment Processing
  ↓
Completed

```

---

## Main Components

### Location

Represents the geographical location of a user or driver using latitude and longitude.

### Request

Stores ride-request information such as:

- User name
- Source
- Destination
- User location

### Driver

Represents a driver and maintains:

- Driver name
- Location
- Current ride
- Current request
- Driver state (`idle` / `busy`)

A driver can accept a request only when it is idle.

### Ride

Represents an active ride and is responsible for:

- Starting the ride
- Calculating distance
- Calculating fare
- Initiating ride completion

The current fare calculation is:

```text
Fare = Distance × 20

```

### Driver Manager

Maintains the collection of drivers and is responsible for:

- Adding/removing drivers
- Selecting the driver-selection strategy
- Ordering drivers
- Assigning requests to available drivers

---

# Design Patterns

## 1. Strategy Pattern

Used for selecting and ordering drivers.

```text
Strategy
   ├── Shortest Radius
   └── Less Traffic

```

The `Driver_manager` works with the `strategy` abstraction, making it possible to add new strategies without changing the manager's core logic.

Possible future strategies:

- Nearest driver
- Highest-rated driver
- Fastest pickup
- Lowest fare

---

## 2. Factory Pattern

Factories are used to separate object creation from business logic.

### Driver Factory

Creates `Driver` objects.

### Ride Factory

Creates `Ride` objects for drivers.

This allows different ride types to be introduced later without significantly changing the driver implementation.

---

## 3. Singleton Pattern

Singleton is used for manager/factory classes such as:

```text
Driver_manager
Main_manager
Driver_Factory

```

A single shared instance is accessed using:

```cpp
getInstance()

```

This ensures that driver management is centralized within the application.

---

## 4. State-Based Ride Completion

Ride completion is represented through multiple stages:

```text
Completing
    ↓
Payment Processing
    ↓
Completed

```

This provides a structure where additional stages such as payment validation, receipt generation, or database persistence can be added later.

---

# SOLID Principles

### Single Responsibility Principle

Responsibilities are separated across different classes:

```text
Driver Manager → Driver management
Strategy        → Driver ordering
Factory         → Object creation
Driver          → Driver/ride state
Ride            → Ride and fare processing
Controller      → Request handling
Service         → Application logic

```

### Open/Closed Principle

New driver-selection strategies can be added without modifying the existing manager logic.

### Liskov Substitution Principle

Concrete strategies can be used through the `strategy` interface.

### Dependency Inversion Principle

`Driver_manager` depends on the `strategy` abstraction rather than directly depending on a particular driver-selection algorithm.

---

# ⚙️ Assumptions

The following assumptions are made to keep the implementation simple:

1. **Location:** Latitude and longitude are represented using integers.
2. **Distance:** Manhattan distance is used instead of real road/GPS distance.
3. **Driver Location:** Driver locations are randomly generated for demonstration.
4. **Fare:** Fare is calculated as `Distance × 20`.
5. **Traffic:** `less_traffic` currently uses the same distance-based logic and is a placeholder for future traffic integration.
6. **Payment:** Payment processing is simulated using console output.
7. **Database:** Database storage is simulated and no real database is connected.
8. **Notifications:** Notifications are represented using console messages.
9. **Concurrency:** The application is single-threaded.
10. **Persistence:** Drivers and rides exist only during program execution.

---

# 🚀 Future Improvements

The system can be extended with:

- Multiple ride types such as Economy, Premium, and Shared.
- Real GPS and Maps integration.
- Traffic-aware driver selection.
- Dynamic/surge pricing.
- Ride cancellation.
- Driver ratings.
- Payment gateways.
- Database persistence.
- Notification service.
- Ride history.
- Authentication and authorization.
- Thread-safe/concurrent ride assignment.
- Smart pointers instead of raw pointers.

---

# ▶️ Example Flow

```text
User creates Request
        ↓
Client sends request
        ↓
Controller
        ↓
Service
        ↓
Main Manager
        ↓
Driver Manager
        ↓
Strategy orders drivers
        ↓
First available Driver accepts
        ↓
Ride Factory creates Ride
        ↓
Ride starts
        ↓
Ride completed
        ↓
Payment processed
        ↓
Ride marked Completed

```

---

## Concepts Demonstrated

- C++ OOP
- Encapsulation
- Abstraction
- Inheritance
- Polymorphism
- SOLID Principles
- Strategy Pattern
- Factory Pattern
- Singleton Pattern
- State-based design
- Layered Architecture

---

##  Contributor

**Samarth Joshi**

This project is developed for learning and demonstrating **Low Level Design and Design Patterns in C++**.give me the text without icons
