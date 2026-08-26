#include "worker.h"
#include "simulation.h"
#include <vector>

// Purpose: Sets up test workers with realistic shift patterns and break schedules,
// then runs the 24-hour alertness simulation for all of them.
// The three workers represent:
//   - John Doe: Day shift (8:00-17:00) with a 30-minute break at 12:30.
//   - Jane Smith: Afternoon shift (12:00-20:00) with a 30-minute break at 15:00.
//   - Bob Johnson: Overnight shift (22:00-6:00) with a 30-minute break at 2:00.

int main() {
    // Create a vector of workers with different shift times and breaks
    std::vector<Worker> workers = {
        Worker(1, "John Doe", 2.4, 14.0, 6.0, 22.0, 8.0, 17.0, 12.5, 30.0),  // Day shift
        Worker(2, "Jane Smith", 2.4, 14.0, 6.0, 22.0, 12.0, 20.0, 15.0, 30.0), // Afternoon shift
        Worker(3, "Bob Johnson", 3.0, 14.0, 15.0, 7.0, 22.0, 6.0, 2.0, 30.0)   // Overnight shift
    };

    // Run the simulation
    runSimulation(workers);

    return 0;
}