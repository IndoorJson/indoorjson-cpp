/*
 * File Name: test_deserialization.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */

#include <glog/logging.h>
#include <serialization.h>

#include <fstream>

#include "test_entry.h"

using nlohmann::json;
using namespace indoor_json;

TEST(INDOOR_JSON, DESERIALIZATION) {
  std::string file_path = TEST_RESOURCES "/case1.json";
  LOG(INFO) << file_path;

  std::ifstream file_stream(file_path);

  if (file_stream.is_open()) {
    std::string file_content((std::istreambuf_iterator<char>(file_stream)),
                             std::istreambuf_iterator<char>());

    file_stream.close();

    try {
      json j;
      j = json::parse(file_content);
      LOG(INFO) << "parse to json dom";

      auto indoor_features = j.get<IndoorFeatures>();

      LOG(INFO) << "get features";
      LOG(INFO) << indoor_features.connections[0]->comment;

    } catch (json::exception &e) {
      LOG(ERROR) << "parse error: " << e.what();
    }

  } else {
    LOG(ERROR) << "Error opening the file.";
  }
}
