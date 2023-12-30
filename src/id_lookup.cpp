/*
 * File Name: id_lookup.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/20
 *
 */

#include <id_lookup.h>

namespace indoor_json {

template <>
IdLookup<IndoorFeatures>* IdLookup<IndoorFeatures>::instance_ = nullptr;
template <>
IdLookup<Connection>* IdLookup<Connection>::instance_ = nullptr;
template <>
IdLookup<ThematicLayer>* IdLookup<ThematicLayer>::instance_ = nullptr;
template <>
IdLookup<PrimalSpaceLayer>* IdLookup<PrimalSpaceLayer>::instance_ = nullptr;
template <>
IdLookup<DualSpaceLayer>* IdLookup<DualSpaceLayer>::instance_ = nullptr;
template <>
IdLookup<CellSpace>* IdLookup<CellSpace>::instance_ = nullptr;
template <>
IdLookup<CellBoundary>* IdLookup<CellBoundary>::instance_ = nullptr;
template <>
IdLookup<Node>* IdLookup<Node>::instance_ = nullptr;
template <>
IdLookup<Edge>* IdLookup<Edge>::instance_ = nullptr;

void IdLookupClearAll() {
  IdLookup<IndoorFeatures>::Ins().Clear();
  IdLookup<Connection>::Ins().Clear();
  IdLookup<ThematicLayer>::Ins().Clear();
  IdLookup<PrimalSpaceLayer>::Ins().Clear();
  IdLookup<DualSpaceLayer>::Ins().Clear();
  IdLookup<CellSpace>::Ins().Clear();
  IdLookup<CellBoundary>::Ins().Clear();
  IdLookup<Node>::Ins().Clear();
  IdLookup<Edge>::Ins().Clear();
}

}  // namespace indoor_json