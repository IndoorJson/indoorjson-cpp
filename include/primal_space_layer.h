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

#include <vector>

#include "cell_boundary.h"
#include "cell_space.h"
#include "feature.h"
#include "ptr.h"

namespace indoor_json {

struct PrimalSpaceLayer : Feature {
  std::vector<CellSpacePtr> spaces;
  std::vector<CellBoundaryPtr> boundaries;
};

DEFINE_PTR(PrimalSpaceLayer)

}  // namespace indoor_json
