/*
 * File Name: test_edge.cpp
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

TEST(INDOOR_JSON, EDGE) {
  auto factory = geos::geom::GeometryFactory::create();
  std::initializer_list<geos::geom::Coordinate> coordList = {
      {1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}};
  geos::geom::CoordinateSequence cs(coordList);

  indoor_json::Edge edge;
  edge.weight = 3.0f;
  edge.id = "$123";
  edge.name = "my edge";
  edge.description = "description of edge";
  edge.external_ref = "https://indoorgml.org/";
  edge.geom = factory->createLineString(cs);
  auto env = edge.geom->getEnvelopeInternal();
  edge.envelope.reset(new geos::geom::Envelope(env->getMinX(), env->getMaxX(),
                                               env->getMinY(), env->getMaxY()));

  indoor_json::NodePtr node;
  node.reset(new indoor_json::Node());
  node->id = "@node_id";
  edge.nodes.emplace_back(indoor_json::NodeWPtr(node));

  indoor_json::CellBoundaryPtr boundary;
  boundary.reset(new indoor_json::CellBoundary());
  boundary->id = "$boundary_id";
  edge.boundary = indoor_json::CellBoundaryWPtr(boundary);

  json j;
  to_json(j, edge);
  std::string json_str = j.dump(2);

  std::string exp_str = R"_({
  "boundary": "$boundary_id",
  "description": "description of edge",
  "envelope": "Env[1:7,2:8]",
  "external_ref": "https://indoorgml.org/",
  "geom": "LINESTRING (1 2, 4 5, 7 8)",
  "id": "$123",
  "name": "my edge",
  "nodes": [
    "@node_id"
  ],
  "weight": 3.0
})_";
  EXPECT_EQ(json_str, exp_str);

  json j2;
  j2 = json::parse(json_str);
  indoor_json::Edge edge2 = j2.get<indoor_json::Edge>();
  EXPECT_EQ(edge2.weight, 3.0f);
}
