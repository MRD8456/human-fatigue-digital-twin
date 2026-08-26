#ifndef WORKER_H
#define WORKER_H

#include <string>

// --- Homeostatic process (Process S) constants ---
// Models sleep pressure, which builds while awake and dissipates during sleep (Åkerstedt & Folkard)
extern const double ha;  // upper asymptote: max sleep pressure reached while awake (fully fatigued)
extern const double d;   // decay rate controlling how fast S rises toward ha

// --- Circadian process (Process C) constants ---
// Models the biological clock's influence on alertness, independent of sleep/wake history
extern const double PI;  // Mathematical constant for circadian rhythm calculations
extern const double Ca;  // Amplitude of the circadian rhythm (peak alertness effect)
extern const double p;   // Phase shift: time of peak circadian alertness (in hours)
extern const double Cm;  // Baseline circadian alertness level

// --- KSS (Karolinska Sleepiness Scale) conversion constants ---
extern const double MIN_RAW;  // Minimum raw alertness value (maps to KSS=9)
extern const double MAX_RAW;  // Maximum raw alertness value (maps to KSS=1)

// --- Asleep-phase S formula constants ---
// Models the dissipation of sleep pressure during sleep
extern const double la;  // lower asymptote : min sleep pressure (fully rested)
extern const double g;   // Decay rate of S during sleep (exponential phase)
extern const double bl;  // Threshold S-value where dissipation switches to linear

// --- Break-bonus mechanism constants ---
extern const double k;   // Decay rate of break bonus over time

class Worker {
private:
    int id;
    std::string name;
    double sw;            // S-value at wake (initial sleep pressure)
    double ss;            // S-value at sleep onset
    double wake_time;     // Time of waking (in hours, 24h format)
    double sleep_time;    // Time of sleep onset (in hours, 24h format)
    double shift_start;   // Start time of the worker's shift
    double shift_end;     // End time of the worker's shift
    double break_time;    // Time when the break starts (in hours)
    double break_duration; // Duration of the break in minutes

public:
    // Constructor
    Worker(int workerId, std::string workerName, double sW, double sS,
           double wakeTime, double sleepTime, double shiftStart, double shiftEnd,
           double breakTime, double breakDuration);

    // Getters
    double getShiftStart();
    double getShiftEnd();
    double getBreakTime();
    double getBreakDuration();

    // Methods
    double calculateTaw(double current_time);  // Time awake since wake_time
    double calculateS(double taw);              // Homeostatic S-value
    double calculateCrossoverTime();            // Time when S switches from exponential to linear decay
    double calculateSleepS(double t_sleep);     // S-value during sleep
    void displaySummary(double hour, double kss, std::string status);  // Display worker status
};

#endif