/*
 * main.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/20
 *
 */

#include <iostream>

#include <nlohmann/json.hpp>


using json = nlohmann::json;

int main() {
  json hello = {
    {"hello", "IndoorJson!"},
  };
  std::cout << hello.dump() << std::endl;
  return 0;
}
