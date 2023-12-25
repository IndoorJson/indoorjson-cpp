/*
 * File Name: test_feature.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/24
 *
 */

#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>
#include <glog/logging.h>
#include <serialization.h>

#include "test_entry.h"

using nlohmann::json;

TEST(INDOOR_JSON, CASE1) {
  std::string polygon_str =
      "POLYGON((30        10, 40 40, 20 40, 10 20, 30 10))";
  geos::io::WKTReader reader;
  auto geom = reader.read(polygon_str);

  json j;
  indoor_json::to_json(j, geom);
  std::string dump_json = j.dump();
  EXPECT_EQ("\"POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))\"", dump_json);

  json j2 = json::parse(dump_json);
  // geos::geom::Geometry::Ptr geom2 = j2.get<geos::geom::Geometry::Ptr>();
  geos::geom::Geometry::Ptr geom2;
  indoor_json::from_json(j2, geom2);

  geos::io::WKTWriter writer;
  EXPECT_EQ("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))",
            writer.write(geom2.get()));
}
