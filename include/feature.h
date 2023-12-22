/*
 * feature.h
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */
#pragma once

#include <geos/geom/Envelope.h>
#include <geos/geom/Point.h>

#include <cstddef>
#include <string>

#include "ptr.h"

namespace indoor_json {

struct Feature {
  std::string id;
  std::string name;
  std::string description;
  std::string external_ref;
  geos::geom::Envelope::Ptr envelope;
};

DEFINE_PTR(Feature)

}  // namespace indoor_json
