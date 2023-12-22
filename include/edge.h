/*
 * edge.h
 *
 * Copyright (c) 2023 Syrius Robotics
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */
#pragma once

#include <memory>

#include <geos/geom/Geometry.h>

#include "ptr.h"

FORWARD_DEC_WPTR(CellBoundary)
FORWARD_DEC_WPTR(Node)

namespace indoor_json {

struct Edge {
  geos::geom::Geometry::Ptr geom;
  CellBoundaryWPtr boundary;
  std::vector<NodeWPtr> nodes;
  double weight;
};

DEFINE_PTR(Edge)

}  // namespace indoor_json