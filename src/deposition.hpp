#pragma once

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "RobotBase.hpp"  
#include "constants.hpp"
#include <cmath>
#include <chrono>

using namespace ctre::phoenix6;

class Deposition : public RobotBase, public rclcpp::Node {
public:
    Deposition();

    // RobotBase interface methods:
    void RobotInit() override;
    void RobotPeriodic() override;
    bool IsEnabled() override;
    void EnabledInit() override;
    void EnabledPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;

private:
    void joyCallback(const sensor_msgs::msg::Joy::SharedPtr msg);

    hardware::TalonFX regolith_collector_{3, CANBUS_NAME};
    hardware::TalonFX regolith_dump_{6, CANBUS_NAME};

    controls::DutyCycleOut collectorOutput_{0};
    controls::DutyCycleOut dumpOutput_{0};
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    sensor_msgs::msg::Joy latest_joy_msg_;
    bool latest_joy_received_;

    bool collector_button_prev_;
    bool collector_toggle_state_;
    bool dump_button_prev_;
    bool dump_toggle_state_;

    //rclcpp::TimerBase::SharedPtr timer_;
};