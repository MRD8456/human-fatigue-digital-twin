#include "worker.h"
#include <cmath>
#include <iostream>
#include <iomanip> // For std::setw and std::setfill

// --- Global constants ---
// Homeostatic process (Process S) constants — models sleep pressure,
// which builds while awake and dissipates during sleep (Åkerstedt & Folkard)
const double ha = 14.3;  // upper asymptote: max sleep pressure reached while awake
const double d = -0.0353; // decay rate controlling how fast S rises toward ha

// Circadian process (Process C) constants — models the biological clock's influence on alertness
const double PI = 3.14159265358979; // Mathematical constant for circadian rhythm calculations
const double Ca = 2.5;   // Amplitude of the circadian rhythm (peak alertness effect)
const double p = 16.8;   // Phase shift: time of peak circadian alertness (in hours)
const double Cm = 0.0;   // Baseline circadian alertness level

// KSS (Karolinska Sleepiness Scale) conversion constants
const double MIN_RAW = -16.8; // Minimum raw alertness value (maps to KSS=9)
const double MAX_RAW = 0.1;   // Maximum raw alertness value (maps to KSS=1)

// Asleep-phase S formula constants — models the dissipation of sleep pressure during sleep
const double la = 2.4;   // as rested as this model allows (fully rested)
const double g = -0.3813; // Decay rate of S during sleep (exponential phase)
const double bl = 12.2;  // Threshold S-value where dissipation switches to linear

// Break-bonus mechanism constants
const double k = 4.0; // Decay rate of break bonus over time

// --- Constructor with validation checks ---
// Initializes a Worker with physiological parameters and validates input ranges
Worker::Worker(int workerId, std::string workerName, double sW, double sS,
               double wakeTime, double sleepTime, double shiftStart, double shiftEnd,
               double breakTime, double breakDuration)
    : id(workerId), name(workerName), sw(sW), ss(sS),
      wake_time(wakeTime), sleep_time(sleepTime),
      shift_start(shiftStart), shift_end(shiftEnd),
      break_time(breakTime), break_duration(breakDuration) {

    // Validate homeostatic sleep pressure at wake (sw)
    if (sw < la || sw > ha) {
        std::cerr << "Warning: Worker " << id << " (" << name << ") has sw=" << sw
                  << " outside valid range [" << la << ", " << ha << "]" << std::endl;
    }

    // Validate homeostatic sleep pressure at sleep (ss)
    if (ss < la || ss > ha) {
        std::cerr << "Warning: Worker " << id << " (" << name << ") has ss=" << ss
                  << " outside valid range [" << la << ", " << ha << "]" << std::endl;
    }

    // Validate shift times (must be within 0-24)
    if (shiftStart < 0 || shiftStart > 24) {
        std::cerr << "Warning: Worker " << id << " (" << name << ") has shift_start=" << shiftStart
                  << " outside valid range [0, 24]" << std::endl;
    }
    if (shiftEnd < 0 || shiftEnd > 24) {
        std::cerr << "Warning: Worker " << id << " (" << name << ") has shift_end=" << shiftEnd
                  << " outside valid range [0, 24]" << std::endl;
    }

    // Validate break duration (must not be negative)
    if (breakDuration < 0) {
        std::cerr << "Warning: Worker " << id << " (" << name << ") has break_duration=" << breakDuration
                  << " which is negative" << std::endl;
    }
}

// --- Getters ---
double Worker::getShiftStart() { return shift_start; }
double Worker::getShiftEnd() { return shift_end; }
double Worker::getBreakTime() { return break_time; }
double Worker::getBreakDuration() { return break_duration; }

// --- Methods ---

// Calculates time awake (taw) since wake_time, accounting for midnight wrap-around
// (e.g., if wake_time=22 and current_time=6, taw=8 hours, not -16)
double Worker::calculateTaw(double current_time) {
    double taw = current_time - wake_time;
    if (taw < 0) {
        taw += 24;  // Correct for wrapping past midnight
    }
    return taw;
}

// Calculates homeostatic S-value (sleep pressure) using the formula:
// S = ha - (ha - sw) * exp(d * taw)
// This models how sleep pressure builds exponentially toward ha the longer someone is awake
double Worker::calculateS(double taw) {
    return ha - (ha - sw) * exp(d * taw);
}

// Calculates the crossover time when S switches from exponential to linear decay during sleep
// finds the exact moment S drops to the brake threshold (bl), where recovery switches from fast exponential decay to a slower linear phase
double Worker::calculateCrossoverTime() {
    return log(9.8 / (ss - la)) / g;
}

// Calculates S-value during sleep. Recovery follows two phases: exponential decay
// while significantly sleep-deprived (fast initial recovery), switching to a linear
// phase once close to full rest (bl threshold) — because a purely exponential curve
// would predict recovery nearly stalling out near full rest, which real sleepiness
// data does not support (Åkerstedt et al., 2008). The exact slope used here is our
// own reconstruction from boundary conditions, since the paper's precise published
// value was not accessible to us
double Worker::calculateSleepS(double t_sleep) {
    if (ss > bl) {
        double crossover = calculateCrossoverTime();
        if (t_sleep < crossover) {
            return la + (ss - la) * exp(g * t_sleep);  // Exponential decay phase
        }
    }
    return 12.2 - 1.225 * t_sleep;  // Linear decay phase
}

// Displays worker status with time formatted as HH:MM for clarity
void Worker::displaySummary(double hour, double kss, std::string status) {
    int wholeHour = (int)hour;
    int minutes = (int)((hour - wholeHour) * 60);

    std::cout << "Hour: " << wholeHour << ":" << std::setw(2) << std::setfill('0') << minutes
              << " | Worker ID: " << id << " | Name: " << name
              << " | KSS: " << kss << " | Status: " << status << std::endl;
}