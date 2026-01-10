#include "HumanoidImpactModel.hpp"
#include <iostream>

int main() {
    HumanoidNode unitreeH1 {
        "CN-UNITREE-H1-IND-01",
        "Unitree",
        "H1",
        "Humanoid",
        "China",
        "Industrial-Logistics",
        900.0,    // W
        5200.0,   // kg CO2e
        2500.0,   // hours/year
        0.72,
        0.81,
        6.7e5
    };

    HumanoidImpactConfig cfg {
        0.45,   // kg CO2/kWh (typical coal–gas heavy grid mix) [web:5]
        4.0,    // kg CO2/h baseline (approx small diesel forklift or LPG stacker) [web:6]
        8.0,    // years design life
        0.5     // 50% of recyclable embodied CO2 counts as credit
    };

    const auto res = computeHumanoidImpact(unitreeH1, cfg);

    std::cout << "Annual baseline CO2 (kg): " << res.annualCO2BaselineKg << "\n";
    std::cout << "Annual robot CO2 (kg):   " << res.annualCO2RobotKg << "\n";
    std::cout << "Annual CO2 avoided (kg): " << res.annualCO2AvoidedKg << "\n";
    std::cout << "Lifetime net CO2 (kg):   " << res.lifetimeCO2NetKg << "\n";
    std::cout << "Annual Karma:            " << res.annualKarma << "\n";

    return 0;
}
