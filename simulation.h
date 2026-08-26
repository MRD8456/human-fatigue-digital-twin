#ifndef SIMULATION_H
#define SIMULATION_H

#include "worker.h"
#include <vector>
#include <string>

// Standalone function to calculate circadian C-value
// Models the biological clock's contribution to alertness, independent of sleep/wake history
double calculateC(double tod);

// Standalone function to convert raw alertness to KSS (Karolinska Sleepiness Scale)
// Maps the combined raw alertness score (already computed from S, C, and break bonus) to a 1-9 scale
double convertToKSS(double raw);

// Standalone function to calculate B0 (base break bonus)
// Computes the break-recovery bonus's starting magnitude, scaled by break length
double calculateB0(double duration);

// Standalone function to calculate break bonus
// Models the decay of alertness recovery over time since the break ended
double calculateBreakBonus(double duration, double t_since_break_end);

// Standalone function to get safety status based on KSS
// Categorizes alertness into actionable safety levels
std::string getSafetyStatus(double kss);

// Function to run the simulation for a vector of workers
// Simulates alertness across a 24-hour period for all workers
void runSimulation(std::vector<Worker>& workers);

#endif