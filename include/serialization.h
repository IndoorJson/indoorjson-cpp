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

// indoor features
void to_json(json &j, const IndoorFeatures &indoor_features);
void from_json(const json &j, IndoorFeatures &indoor_features);

// connection
void to_json(json &j, const Connection &connection);
void from_json(const json &j, Connection &connection);

// thematic layer
void to_json(json &j, const ThematicLayer &layer);
void from_json(const json &j, ThematicLayer &layer);

// primal space layer
void to_json(json &j, const PrimalSpaceLayer &layer);
void from_json(const json &j, PrimalSpaceLayer &layer);

// dual space layer
void to_json(json &j, const DualSpaceLayer &layer);
void from_json(const json &j, DualSpaceLayer &layer);

// cell space
void to_json(json &j, const CellSpace &space);
void from_json(const json &j, CellSpace &space);

// cell boundary
void to_json(json &j, const CellBoundary &boundary);
void from_json(const json &j, CellBoundary &boundary);

// node
void to_json(json &j, const Node &node);
void from_json(const json &j, Node &node);

// edge
void to_json(json &j, const Edge &edge);
void from_json(const json &j, Edge &edge);

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

template <typename T>
struct adl_serializer<std::shared_ptr<T>> {
  static void to_json(json &j, const std::shared_ptr<T> &ptr) {
    indoor_json::to_json(j, *ptr.get());
  }

  static void from_json(const json &j, std::shared_ptr<T> &ptr) {
    ptr = std::make_shared<T>();
    indoor_json::from_json(j, *ptr.get());
  }
};

template <typename T>
struct adl_serializer<std::weak_ptr<T>> {
  static void to_json(json &j, const std::weak_ptr<T> &wptr) {
    if (auto feature = wptr.lock())
      j = feature->id;
    else
      j = nullptr;
  }

  static void from_json(const json &j, std::weak_ptr<T> &wptr) {
  }
};

NLOHMANN_JSON_NAMESPACE_END