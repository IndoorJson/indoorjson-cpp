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

  std::ifstream fin(file_path);

  ASSERT_TRUE(fin.is_open());

  std::string content((std::istreambuf_iterator<char>(fin)),
                      std::istreambuf_iterator<char>());

  fin.close();

  try {
    json j;
    j = json::parse(content);
    LOG(INFO) << "parse to json dom";

    auto indoor_features = j.get<IndoorFeatures>();

    LOG(INFO) << "get features";
    LOG(INFO) << indoor_features.connections[0]->comment;

    json j2 = indoor_features;
    LOG(INFO) << j2.dump(2);

  } catch (json::exception &e) {
    LOG(ERROR) << "parse error: " << e.what();
  }
}
