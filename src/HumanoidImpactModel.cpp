#include "HumanoidImpactModel.hpp"
#include <stdexcept>

HumanoidImpactResult computeHumanoidImpact(
    const HumanoidNode& node,
    const HumanoidImpactConfig& cfg
) {
    if (cfg.gridCO2KgPerKWh <= 0.0 || cfg.lifetimeYears <= 0.0) {
        throw std::invalid_argument("Invalid config parameters.");
    }

    // Annual energy use of robot (kWh/year)
    const double kWhYear = (node.avgPowerW * node.operatingHoursPerYear) / 1000.0;

    // Annual CO2 from robot operation
    const double annualCO2RobotKg = kWhYear * cfg.gridCO2KgPerKWh;

    // Baseline CO2 from legacy equipment per year (e.g., diesel or less efficient machines)
    const double annualCO2BaselineKg = cfg.baselineCO2KgPerHour * node.operatingHoursPerYear;

    // Avoided CO2 per year
    const double annualCO2AvoidedKg = annualCO2BaselineKg - annualCO2RobotKg;

    // Recycling credit on embodied CO2
    const double recyclingCreditKg =
        node.embodiedCO2kg * node.recyclabilityFraction * cfg.recyclingCreditFactor;

    // Lifetime net CO2 taking embodied and recycling into account
    const double lifetimeCO2RobotKg = annualCO2RobotKg * cfg.lifetimeYears + node.embodiedCO2kg;
    const double lifetimeCO2NetKg = lifetimeCO2RobotKg - recyclingCreditKg
        - (annualCO2BaselineKg * cfg.lifetimeYears); // negative is net benefit

    // Karma: only positive avoided CO2 earns Karma; scaled by ecoImpactScore
    double annualKarma = 0.0;
    if (annualCO2AvoidedKg > 0.0) {
        annualKarma = annualCO2AvoidedKg * node.karmaPerKgCO2Avoided * node.ecoImpactScore;
    }

    HumanoidImpactResult r{};
    r.annualCO2BaselineKg = annualCO2BaselineKg;
    r.annualCO2RobotKg    = annualCO2RobotKg;
    r.annualCO2AvoidedKg  = annualCO2AvoidedKg;
    r.lifetimeCO2NetKg    = lifetimeCO2NetKg;
    r.annualKarma         = annualKarma;
    return r;
}
