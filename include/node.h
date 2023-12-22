/*
 * node.h
 *
 * Copyright (c) 2023 Syrius Robotics
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */
#pragma once

#include <geos/geom/Geometry.h>

#include <vector>

#include "feature.h"
#include "ptr.h"

namespace indoor_json {

FORWARD_DEC_WPTR(CellSpace)
FORWARD_DEC_WPTR(Edge)

struct Node : Feature {
  geos::geom::Geometry::Ptr geom;
  CellSpaceWPtr space;
  std::vector<EdgeWPtr> edges;
};

DEFINE_PTR(Node)

}  // namespace indoor_json