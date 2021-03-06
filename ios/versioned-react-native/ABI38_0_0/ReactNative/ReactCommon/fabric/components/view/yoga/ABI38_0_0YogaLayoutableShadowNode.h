/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include <vector>

#include <ABI38_0_0yoga/ABI38_0_0YGNode.h>

#include <ABI38_0_0React/components/view/YogaStylableProps.h>
#include <ABI38_0_0React/core/LayoutableShadowNode.h>
#include <ABI38_0_0React/core/Sealable.h>
#include <ABI38_0_0React/core/ShadowNode.h>
#include <ABI38_0_0React/debug/DebugStringConvertible.h>
#include <ABI38_0_0React/graphics/Geometry.h>

namespace ABI38_0_0facebook {
namespace ABI38_0_0React {

class YogaLayoutableShadowNode : public LayoutableShadowNode,
                                 public virtual DebugStringConvertible,
                                 public virtual Sealable {
 public:
  using UnsharedList = better::small_vector<
      YogaLayoutableShadowNode *,
      kShadowNodeChildrenSmallVectorSize>;

#pragma mark - Constructors

  YogaLayoutableShadowNode(bool isLeaf);

  YogaLayoutableShadowNode(
      YogaLayoutableShadowNode const &layoutableShadowNode);

#pragma mark - Mutating Methods

  /*
   * Connects `measureFunc` function of Yoga node with
   * `LayoutableShadowNode::measure()` method.
   */
  void enableMeasurement();

  /*
   * Appends `child`'s Yoga node to the own Yoga node.
   * Complements `ShadowNode::appendChild(...)` functionality from Yoga
   * perspective.
   */
  void appendChild(YogaLayoutableShadowNode *child);

  /*
   * Sets Yoga children based on collection of `YogaLayoutableShadowNode`
   * instances. Complements `ShadowNode::setChildren(...)` functionality from
   * Yoga perspective.
   */
  void setChildren(YogaLayoutableShadowNode::UnsharedList children);

  /*
   * Sets Yoga styles based on given `YogaStylableProps`.
   */
  void setProps(const YogaStylableProps &props);

  /*
   * Sets layoutable size of node.
   */
  void setSize(Size size) const;

  void setPadding(RectangleEdges<Float> padding) const;

  /*
   * Sets position type of Yoga node (relative, absolute).
   */
  void setPositionType(ABI38_0_0YGPositionType positionType) const;

#pragma mark - LayoutableShadowNode

  void cleanLayout() override;
  void dirtyLayout() override;
  bool getIsLayoutClean() const override;

  void setHasNewLayout(bool hasNewLayout) override;
  bool getHasNewLayout() const override;

  /*
   * Computes layout using Yoga layout engine.
   * See `LayoutableShadowNode` for more details.
   */
  void layout(LayoutContext layoutContext) override;

  void layoutChildren(LayoutContext layoutContext) override;

  LayoutableShadowNode::UnsharedList getLayoutableChildNodes() const override;

 protected:
  /*
   * Yoga config associated (only) with this particular node.
   */
  ABI38_0_0YGConfig yogaConfig_;

  /*
   * All Yoga functions only accept non-const arguments, so we have to mark
   * Yoga node as `mutable` here to avoid `static_cast`ing the pointer to this
   * all the time.
   */
  mutable ABI38_0_0YGNode yogaNode_;

  /*
   * Forces associated ABI38_0_0YGNode to be a leaf.
   * Adding a child `ShadowNode` will not add `ABI38_0_0YGNode` associated with it as a
   * child to the stored `ABI38_0_0YGNode`.
   */
  bool const isLeaf_;

 private:
  static ABI38_0_0YGConfig &initializeYogaConfig(ABI38_0_0YGConfig &config);
  static ABI38_0_0YGNode *yogaNodeCloneCallbackConnector(
      ABI38_0_0YGNode *oldYogaNode,
      ABI38_0_0YGNode *parentYogaNode,
      int childIndex);
  static ABI38_0_0YGSize yogaNodeMeasureCallbackConnector(
      ABI38_0_0YGNode *yogaNode,
      float width,
      ABI38_0_0YGMeasureMode widthMode,
      float height,
      ABI38_0_0YGMeasureMode heightMode);
};

} // namespace ABI38_0_0React
} // namespace ABI38_0_0facebook
