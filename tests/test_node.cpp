/*
 * File Name: test_node.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */
#include <geos/geom/GeometryFactory.h>
#include <glog/logging.h>
#include <serialization.h>

#include "test_entry.h"

using nlohmann::json;

TEST(INDOOR_JSON, NODE) {
  auto factory = geos::geom::GeometryFactory::create();
  std::initializer_list<geos::geom::Coordinate> coordList = {
      {1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}};
  geos::geom::CoordinateSequence cs(coordList);

  indoor_json::Node node;
  node.id = "$123";
  node.name = "my node";
  node.description = "description of node";
  node.external_ref = "https://indoorgml.org/";
  node.envelope.reset(new geos::geom::Envelope(0.1, 1.04, 2.05, 3.06));
  node.geom = factory->createLineString(cs);

  indoor_json::EdgePtr edge;
  edge.reset(new indoor_json::Edge());
  edge->id = "@edge_id";
  node.edges.emplace_back(indoor_json::EdgeWPtr(edge));

  indoor_json::CellSpacePtr space;
  space.reset(new indoor_json::CellSpace());
  space->id = "$space_id";
  node.space = indoor_json::CellSpaceWPtr(space);

  json j;
  to_json(j, node);
  std::string json_str = j.dump(2);

  std::string exp_str = R"_({
  "description": "description of node",
  "edges": [
    "@edge_id"
  ],
  "envelope": "Env[0.1:1.04,2.05:3.06]",
  "external_ref": "https://indoorgml.org/",
  "geom": "LINESTRING (1 2, 4 5, 7 8)",
  "id": "$123",
  "name": "my node",
  "space": "$space_id"
})_";
  EXPECT_EQ(json_str, exp_str);
}
