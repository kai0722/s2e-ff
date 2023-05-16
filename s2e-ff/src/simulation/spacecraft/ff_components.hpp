/**
 * @file ff_components.hpp
 * @brief Components management installed on a FF spacecraft
 */

#ifndef S2E_FF_SIMULATION_SPACECRAFT_FF_COMPONENTS_HPP_
#define S2E_FF_SIMULATION_SPACECRAFT_FF_COMPONENTS_HPP_

#include <environment/global/global_environment.hpp>
#include <environment/local/local_environment.hpp>
#include <simulation/spacecraft/installed_components.hpp>

// include for components
#include <components/ideal/force_generator.hpp>
#include <components/real/cdh/on_board_computer.hpp>

#include "../../components/analyzer/relative_orbit_analyzer.hpp"
#include "../../components/aocs/initialize_relative_distance_sensor.hpp"
#include "../../components/aocs/initialize_relative_position_sensor.hpp"
#include "../../components/aocs/initialize_relative_velocity_sensor.hpp"
#include "../../components/controller/relative_orbit_controller_chief.hpp"

class RelativeOrbitControllerChief;

/**
 * @class FfComponents
 * @brief A components class for FF satellite
 */
class FfComponents : public InstalledComponents {
 public:
  /**
   * @fn FfComponents
   * @brief Constructor
   */
  FfComponents(const Dynamics* dynamics, const Structure* structure, const LocalEnvironment* local_env, const GlobalEnvironment* glo_env,
               const SimulationConfiguration* config, ClockGenerator* clock_gen, const RelativeInformation* rel_info);
  /**
   * @fn ~FfComponents
   * @brief Destructor
   */
  ~FfComponents();

  // Override functions for InstalledComponents
  /**
   * @fn GenerateForce_b_N
   * @brief Return force generated by components in unit Newton in body fixed frame
   */
  libra::Vector<3> GenerateForce_b_N();
  /**
   * @fn GenerateTorque_b_Nm
   * @brief Return torque generated by components in unit Newton-meter in body fixed frame
   */
  libra::Vector<3> GenerateTorque_b_Nm();
  /**
   * @fn LogSetup
   * @brief Setup the logger for components
   */
  void LogSetup(Logger& logger);

  // Getter
  inline RelativeDistanceSensor& GetRelativeDistanceSensor() const { return *relative_distance_sensor_; }
  inline RelativePositionSensor& GetRelativePositionSensor() const { return *relative_position_sensor_; }
  inline RelativeVelocitySensor& GetRelativeVelocitySensor() const { return *relative_velocity_sensor_; }
  inline ForceGenerator& GetForceGenerator() const { return *force_generator_; }

 private:
  // Components
  // CDH
  OnBoardComputer* obc_;  //!< On board computer
  // Sensors
  RelativeDistanceSensor* relative_distance_sensor_;  //!< Example of Relative distance sensor
  RelativePositionSensor* relative_position_sensor_;  //!< Example of Relative position sensor
  RelativeVelocitySensor* relative_velocity_sensor_;  //!< Example of Relative velocity sensor
  // Actuators
  ForceGenerator* force_generator_;                          //!< Example of force generator

  RelativeOrbitControllerChief* relative_orbit_controller_;  // !< Relative orbit controller
  RelativeOrbitAnalyzer* relative_orbit_analyzer_;           // !< Relative orbit analyzer

  // References
  const Dynamics* dynamics_;               //!< Dynamics information of the spacecraft
  const Structure* structure_;             //!< Structure information of the spacecraft
  const LocalEnvironment* local_env_;      //!< Local environment information around the spacecraft
  const GlobalEnvironment* glo_env_;       //!< Global environment information
  const SimulationConfiguration* config_;  //!< Simulation settings
  const RelativeInformation* rel_info_;    //!< Relative information
};

#endif  // S2E_FF_SIMULATION_SPACECRAFT_FF_COMPONENTS_HPP_
