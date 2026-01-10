#pragma once
#include <string>

struct HumanoidNode {
    std::string nodeId;
    std::string manufacturer;
    std::string model;
    std::string category;
    std::string region;
    std::string application;
    double avgPowerW;                 // W
    double embodiedCO2kg;             // kg CO2e
    double operatingHoursPerYear;     // h/year
    double recyclabilityFraction;     // 0–1
    double ecoImpactScore;            // 0–1 (from shard)
    double karmaPerKgCO2Avoided;      // Karma/kg
};
