#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;



class EspeakPublisher : public rclcpp::Node
{
  public:
    EspeakPublisher()
    : Node("string_publisher"),count_(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic_name", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&EspeakPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "arrived at waypoint 1";
      RCLCPP_INFO(this->get_logger(), "Publishing: %s", message.data.c_str());
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("string_publisher");
  rclcpp::spin(std::make_shared<EspeakPublisher>());
  RCLCPP_INFO(node->get_logger(),"hello\n");
  rclcpp::shutdown();
  return 0;
}