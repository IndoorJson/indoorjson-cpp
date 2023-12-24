/*
 * File Name: geometry.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/24
 *
 */
#include <geos/geom/Geometry.h>
#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>
#include <serialization.h>

namespace indoor_json {

using json = nlohmann::json;

void to_json(json &j, const geos::geom::Geometry::Ptr &geom) {
}

void from_json(const json &j, geos::geom::Geometry::Ptr &geom) {

}

}  // namespace indoor_json
