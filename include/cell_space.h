/*
 * cell_space.h
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */
#pragma once

#include <geos/geom/Geometry.h>

#include <memory>
#include <vector>

#include "ptr.h"

namespace indoor_json {

FORWARD_DEC_WPTR(CellBoundary)
FORWARD_DEC_WPTR(Node)

struct CellSpace {
  geos::geom::Geometry::Ptr geom;
  std::vector<CellBoundaryWPtr> boundaries;
  NodeWPtr node;
};

DEFINE_PTR(CellSpace)

}  // namespace indoor_json
