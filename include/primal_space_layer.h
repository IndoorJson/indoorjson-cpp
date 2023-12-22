/*
 * primal_space_layer.h
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/22
 *
 */
#pragma once

#include <memory>
#include <vector>

#include "ptr.h"
#include "cell_space.h"
#include "cell_boundary.h"

namespace indoor_json {

struct PrimalSpaceLayer {
  std::vector<CellSpacePtr> cell_spaces;
  std::vector<CellBoundaryPtr> cell_boundaries;
};

DEFINE_PTR(PrimalSpaceLayer)

}  // namespace indoor_json
