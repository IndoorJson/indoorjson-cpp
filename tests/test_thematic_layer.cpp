/*
 * File Name: test_thematic_layer.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/25
 *
 */
#include <geos/io/WKTReader.h>
#include <glog/logging.h>
#include <serialization.h>
#include <thematic_layer.h>

#include "test_entry.h"

using nlohmann::json;
using namespace indoor_json;

// *----3-----*----7-----*
// |          |          |
// |          |          |
// 4  space1  2  space2  6
// |          |          |
// |          |          |
// *----1-----*----5-----*

TEST(INDOOR_JSON, THEMATIC_LAYER) {
  ThematicLayerPtr layer;
  layer.reset(new ThematicLayer());
  layer->primal_space.reset(new PrimalSpaceLayer());
  layer->dual_space.reset(new DualSpaceLayer());

  geos::io::WKTReader reader;

  CellSpacePtr space1;
  space1.reset(new CellSpace());
  space1->id = "space1";
  space1->geom = reader.read("POLYGON((0 0, 1 0, 1 1, 0 1, 0 0))");
  layer->primal_space->spaces.emplace_back(space1);

  CellSpacePtr space2;
  space2.reset(new CellSpace());
  space2->id = "space2";
  space2->geom = reader.read("POLYGON((1 0, 2 0, 2 1, 1 1, 1 0))");

  layer->primal_space->spaces.emplace_back(space2);

  CellBoundaryPtr b1;
  b1.reset(new CellBoundary());
  b1->id = "b1";
  b1->geom = reader.read("LINESTRING (0 0, 1 0)");

  CellBoundaryPtr b2;
  b2.reset(new CellBoundary());
  b2->id = "b2";
  b2->geom = reader.read("LINESTRING (1 0, 1 1)");

  CellBoundaryPtr b3;
  b3.reset(new CellBoundary());
  b3->id = "b3";
  b3->geom = reader.read("LINESTRING (1 1, 0 1)");

  CellBoundaryPtr b4;
  b4.reset(new CellBoundary());
  b4->id = "b4";
  b4->geom = reader.read("LINESTRING (0 1, 0 0)");

  CellBoundaryPtr b5;
  b5.reset(new CellBoundary());
  b5->id = "b5";
  b5->geom = reader.read("LINESTRING (1 0, 2 0)");

  CellBoundaryPtr b6;
  b6.reset(new CellBoundary());
  b6->id = "b6";
  b6->geom = reader.read("LINESTRING (2 0, 2 1)");

  CellBoundaryPtr b7;
  b7.reset(new CellBoundary());
  b7->id = "b7";
  b7->geom = reader.read("LINESTRING (2 1, 1 1)");

  layer->primal_space->boundaries.emplace_back(b1);
  layer->primal_space->boundaries.emplace_back(b2);
  layer->primal_space->boundaries.emplace_back(b3);
  layer->primal_space->boundaries.emplace_back(b4);
  layer->primal_space->boundaries.emplace_back(b5);
  layer->primal_space->boundaries.emplace_back(b6);
  layer->primal_space->boundaries.emplace_back(b7);

  space1->boundaries.emplace_back(b1);
  space1->boundaries.emplace_back(b2);
  space1->boundaries.emplace_back(b3);
  space1->boundaries.emplace_back(b4);

  space2->boundaries.emplace_back(b2);
  space2->boundaries.emplace_back(b5);
  space2->boundaries.emplace_back(b6);
  space2->boundaries.emplace_back(b7);

  b1->spaces.emplace_back(space1);
  b2->spaces.emplace_back(space1);
  b3->spaces.emplace_back(space1);
  b4->spaces.emplace_back(space1);

  b2->spaces.emplace_back(space2);
  b5->spaces.emplace_back(space2);
  b6->spaces.emplace_back(space2);
  b7->spaces.emplace_back(space2);

  NodePtr node1;
  node1.reset(new Node());
  node1->id = "n1";
  node1->geom = reader.read("POINT (0.5 0.5)");

  NodePtr node2;
  node2.reset(new Node());
  node2->id = "n2";
  node2->geom = reader.read("POINT (1.5 0.5)");

  EdgePtr edge;
  edge.reset(new Edge());
  edge->id = "e";
  edge->geom = reader.read("LINESTRING (0.5 0.5, 1.5 0.5)");

  node1->edges.emplace_back(edge);
  node2->edges.emplace_back(edge);

  edge->nodes.emplace_back(node1);
  edge->nodes.emplace_back(node2);

  space1->node = node1;
  node1->space = space1;

  space2->node = node2;
  node2->space = space2;

  edge->boundary = b2;
  b2->edge = edge;

  layer->dual_space->nodes.emplace_back(node1);
  layer->dual_space->nodes.emplace_back(node2);

  layer->dual_space->edges.emplace_back(edge);

  json j;
  to_json(j, layer);
  LOG(INFO) << j.dump(2);
}
