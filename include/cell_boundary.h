/*
 * cell_boundary.h
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */
#pragma once

#include <geos/geom/Geometry.h>

#include "feature.h"
#include "ptr.h"

FORWARD_DEC_WPTR(CellSpace)
FORWARD_DEC_WPTR(Edge)

namespace indoor_json {

struct CellBoundary : Feature {
  geos::geom::Geometry::Ptr geom;
  EdgeWPtr edge;
  std::vector<CellSpaceWPtr> spaces;
};

DEFINE_PTR(CellBoundary)

}  // namespace indoor_json
