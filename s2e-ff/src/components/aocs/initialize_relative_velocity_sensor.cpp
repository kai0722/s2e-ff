/**
 * @file initialize_relative_velocity_sensor.cpp
 * @brief Initialize function for RelativeVelocitySensor
 */

#include "initialize_relative_velocity_sensor.hpp"

#include <components/base/initialize_sensor.hpp>
#include <library/initialize/initialize_file_access.hpp>

RelativeVelocitySensor InitializeRelativeVelocitySensor(ClockGenerator* clock_gen, const std::string file_name, const double compo_step_time_s,
                                                        const RelativeInformation& rel_info, const Dynamics& dynamics,
                                                        const int reference_sat_id_input) {
  // General
  IniAccess ini_file(file_name);
  char section[30] = "RELATIVE_VELOCITY_SENSOR";

  int prescaler = ini_file.ReadInt(section, "prescaler");
  if (prescaler <= 1) prescaler = 1;

  // RelativeVelocitySensor
  int target_sat_id = ini_file.ReadInt(section, "target_sat_id");
  int reference_sat_id = ini_file.ReadInt(section, "reference_sat_id");
  if (reference_sat_id < 0) {
    reference_sat_id = reference_sat_id_input;
  }
  std::string error_frame_string = ini_file.ReadString(section, "error_frame");
  RelativeVelocitySensorErrorFrame error_frame;

  if (error_frame_string == "INERTIAL") {
    error_frame = RelativeVelocitySensorErrorFrame::INERTIAL;
  } else if (error_frame_string == "RTN") {
    error_frame = RelativeVelocitySensorErrorFrame::RTN;
  } else {
    std::cerr << "Warnings: InitializeRelativeVelocitySensor: The error frame setting was failed. It is automatically set as RTN frame." << std::endl;
    error_frame = RelativeVelocitySensorErrorFrame::RTN;
  }

  // SensorBase
  Sensor<3> sensor_base = ReadSensorInformation<3>(file_name, compo_step_time_s * (double)(prescaler), section, "m_s");

  RelativeVelocitySensor relative_velocity_sensor(prescaler, clock_gen, sensor_base, target_sat_id, reference_sat_id, error_frame, rel_info,
                                                  dynamics);

  return relative_velocity_sensor;
}
