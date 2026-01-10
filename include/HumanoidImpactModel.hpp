#pragma once
#include "HumanoidNode.hpp"

struct HumanoidImpactResult {
    double annualCO2BaselineKg;   // replaced legacy equipment
    double annualCO2RobotKg;      // robot operation
    double annualCO2AvoidedKg;    // baseline - robot
    double lifetimeCO2NetKg;      // including embodied, recycling credit
    double annualKarma;           // EcoNet-style Karma
};

struct HumanoidImpactConfig {
    double gridCO2KgPerKWh;       // kg CO2e per kWh
    double baselineCO2KgPerHour;  // kg CO2e/h for displaced equipment
    double lifetimeYears;         // design life, years
    double recyclingCreditFactor; // fraction of embodied CO2 creditable via recycling
};

HumanoidImpactResult computeHumanoidImpact(
    const HumanoidNode& node,
    const HumanoidImpactConfig& cfg
);
