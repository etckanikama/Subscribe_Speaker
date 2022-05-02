#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <iostream>
#include <string.h>
#include <typeinfo>

using std::placeholders::_1;


class EspeakSubscriber : public rclcpp::Node
{
public:
  EspeakSubscriber()
  : Node("string_publisher")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic_name", 10, std::bind(&EspeakSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String & msg) const
  {

    std::string st = "espeak ' " + std::string(msg.data) + "'";
    system(st.c_str());
  }
  
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<EspeakSubscriber>());
  rclcpp::shutdown();
  return 0;
}
