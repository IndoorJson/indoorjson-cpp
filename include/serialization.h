/*
 * serialization.h
 *
 * Copyright (c) 2023 Syrius Robotics
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */

#pragma once

#include <nlohmann/json.hpp>

#include "cell_space.h"
#include "indoor_features.h"

using json = nlohmann::json;

namespace indoor_json {

// feature
void to_json(json &j, const Feature &feature);
void from_json(const json &j, Feature &feature);

// cell space
void to_json(json &j, const CellSpace &space);
void to_json(json &j, const CellSpacePtr &space);
void to_json(json &j, const CellSpaceWPtr &space);

void from_json(const json &j, CellSpace &space);
void from_json(const json &j, CellSpacePtr &space);
void from_json(const json &j, CellSpaceWPtr &space);

// cell boundary
void to_json(json &j, const CellBoundary &boundary);
void to_json(json &j, const CellBoundaryPtr &boundary);
void to_json(json &j, const CellBoundaryWPtr &boundary);

void from_json(const json &j, CellBoundary &boundary);
void from_json(const json &j, CellBoundaryPtr &boundary);
void from_json(const json &j, CellBoundaryWPtr &boundary);

// node
void to_json(json &j, const Node &node);
void to_json(json &j, const NodePtr &node);
void to_json(json &j, const NodeWPtr &node);

void from_json(const json &j, Node &node);
void from_json(const json &j, NodePtr &node);
void from_json(const json &j, NodeWPtr &node);

// edge
void to_json(json &j, const Edge &edge);
void to_json(json &j, const EdgePtr &edge);
void to_json(json &j, const EdgeWPtr &edge);

void from_json(const json &j, Edge &edge);
void from_json(const json &j, EdgePtr &edge);
void from_json(const json &j, EdgeWPtr &edge);

// thematic layer
void to_json(json &j, const ThematicLayer &layer);
void to_json(json &j, const ThematicLayerPtr &layer);
void to_json(json &j, const ThematicLayerWPtr &layer);
void from_json(const json &j, ThematicLayer &layer);
void from_json(const json &j, ThematicLayerPtr &layer);
void from_json(const json &j, ThematicLayerWPtr &layer);

// dual space layer
void to_json(json &j, const DualSpaceLayer &layer);
void to_json(json &j, const DualSpaceLayerPtr &layer);
void from_json(const json &j, DualSpaceLayer &layer);
void from_json(const json &j, DualSpaceLayerPtr &layer);

// primal space layer
void to_json(json &j, const PrimalSpaceLayer &layer);
void to_json(json &j, const PrimalSpaceLayerPtr &layer);
void from_json(const json &j, PrimalSpaceLayer &layer);
void from_json(const json &j, PrimalSpaceLayerPtr &layer);

// connection
void to_json(json &j, const Connection &connection);
void to_json(json &j, const ConnectionPtr &connection);
void from_json(const json &j, Connection &connection);
void from_json(const json &j, ConnectionPtr &connection);

// indoor features
void to_json(json &j, const IndoorFeatures &indoor_features);
void to_json(json &j, const IndoorFeaturesPtr &indoor_features);
void from_json(const json &j, IndoorFeatures &indoor_features);
void from_json(const json &j, IndoorFeaturesPtr &indoor_features);

}  // namespace indoor_json


#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>

NLOHMANN_JSON_NAMESPACE_BEGIN

template <>
struct adl_serializer<geos::geom::Geometry::Ptr> {
  static void to_json(json &j, const geos::geom::Geometry::Ptr &geom) {
    geos::io::WKTWriter writer;
    std::string wkt_str = writer.write(geom.get());
    j = wkt_str;
  }

  static void from_json(const json &j, geos::geom::Geometry::Ptr &geom) {
    std::string wkt_str = j.get<std::string>();
    geos::io::WKTReader reader;
    geom = reader.read(wkt_str);
  }
};

NLOHMANN_JSON_NAMESPACE_END