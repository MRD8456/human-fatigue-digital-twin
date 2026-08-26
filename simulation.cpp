#include "simulation.h"
#include <cmath>
#include <iostream>

// Standalone function to calculate circadian C-value
// Models the biological clock's contribution to alertness using a cosine function.
// Peak alertness occurs at phase p (16.8 hours, or ~4:48 PM in a 24-hour cycle),
// with amplitude Ca (2.5) determining the strength of the circadian rhythm.
double calculateC(double tod) {
    return Ca * cos(2 * PI * (tod - p) / 24) + Cm;
}

// Standalone function to convert raw alertness to KSS (Karolinska Sleepiness Scale)
// Linearly maps the raw alertness value (C - S + break_bonus) from [MIN_RAW, MAX_RAW] to [1, 9].
// KSS=1 is "very alert," KSS=9 is "very sleepy, fighting sleep."
double convertToKSS(double raw) {
    return 9 - ((raw - MIN_RAW) / (MAX_RAW - MIN_RAW)) * (9 - 1);
}

// Standalone function to calculate B0 (base break bonus)
// Computes the break-recovery bonus's starting magnitude, scaled by break length.
// Capped at 60 minutes (B0=2.0) — roughly 12% of the model's total alertness range,
// deliberately conservative since real microbreak research shows only a small effect
// size (Cohen's d≈0.35), and overestimating recovery risks false safety reassurance.
double calculateB0(double duration) {
    if (duration <= 60) {
        return 0.033 * duration;
    } else {
        return 2.0;  // Capped at 2.0 for durations beyond 60 minutes
    }
}

// Standalone function to calculate break bonus
// Models the exponential decay of the break's alertness recovery effect over time.
// Uses the decay rate k (4.0) to determine how quickly the bonus fades after the break ends.
double calculateBreakBonus(double duration, double t_since_break_end) {
    return calculateB0(duration) * exp(-k * t_since_break_end);
}

// Standalone function to get safety status based on KSS
// Categorizes alertness into actionable safety levels:
// KSS < 5: "Alert" — safe to continue working.
// KSS 5 to just under 7: "Mild sleepiness, monitor" — caution advised.
// KSS >= 7: "Fatigue risk — recommend break" — immediate action needed.
std::string getSafetyStatus(double kss) {
    if (kss < 5) {
        return "Alert";
    } else if (kss >= 5 && kss < 7) {
        return "Mild sleepiness, monitor";
    } else {
        return "Fatigue risk — recommend break";
    }
}

// Function to run the simulation for a vector of workers
// Structured hour-outer, worker-inner 
// Because of the fact that if this digital twin were to be used in an actual working place
// the supervisor would need to see the results and how they vary during the day by hourly bases 
// other wise the given information would lose their value because they were represented on the wrong time bases
void runSimulation(std::vector<Worker>& workers) {
    // Loop through each 15-minute step of the day (0 to 23.75)
    for (double hour = 0; hour < 24; hour += 0.25) {
        // Loop through each worker
        for (Worker& w : workers) {
            // Check if the current hour falls within the worker's shift
            bool inShift;
            if (w.getShiftStart() <= w.getShiftEnd()) {
                // Normal shift (same day)
                inShift = (hour >= w.getShiftStart() && hour <= w.getShiftEnd());
            } else {
                // Overnight shift (crosses midnight)
                inShift = (hour >= w.getShiftStart() || hour <= w.getShiftEnd());
            }

            if (inShift) {
                // Calculate time awake at the current hour
                double taw = w.calculateTaw(hour);

                // Calculate S-value using the homeostatic formula
                double S = w.calculateS(taw);

                // Calculate C-value using the standalone circadian function
                double C = calculateC(hour);

                // Calculate break bonus dynamically
                double break_end = w.getBreakTime() + w.getBreakDuration() / 60.0;
                double break_bonus = 0.0;  // default: no bonus yet

                if (hour > break_end) {
                    double t_since_break_end = hour - break_end;
                    break_bonus = calculateBreakBonus(w.getBreakDuration(), t_since_break_end);
                }

                // Calculate raw alertness (now including break bonus)
                double alertness_raw = C - S + break_bonus;

                // Convert raw alertness to KSS
                double KSS = convertToKSS(alertness_raw);

                // Get safety status based on KSS
                std::string safety_status = getSafetyStatus(KSS);

                // Display clean summary for the current hour
                w.displaySummary(hour, KSS, safety_status);
            }
        }
    }
}