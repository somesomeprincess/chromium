// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_RECT_H_
#define PPAPI_CPP_RECT_H_

#include "ppapi/c/pp_rect.h"
#include "ppapi/cpp/point.h"
#include "ppapi/cpp/size.h"

/// @file
/// This file defines the APIs for creating a 2 dimensional rectangle.

namespace pp {

/// A 2 dimensional rectangle. A rectangle is represented by x and y (which
/// identifies the upper-left corner of the rectangle), width, and height.
class Rect {
 public:

  /// The default constructor. Creates a Rect in the upper-left starting
  /// coordinate at 0,0 and height and width of 0.
  Rect() {
    rect_.point.x = 0;
    rect_.point.y = 0;
    rect_.size.width = 0;
    rect_.size.height = 0;
  }

  /// A constructor accepting a reference to a PP_Rect and converting the
  /// PP_Rect to a Rect. This is an implicit conversion constructor.
  /// @param[in] rect A pointer to a PP_Rect.
  Rect(const PP_Rect& rect) {  // Implicit.
    set_x(rect.point.x);
    set_y(rect.point.y);
    set_width(rect.size.width);
    set_height(rect.size.height);
  }

  /// A constructor accepting two int32_t values for width and height and
  /// converting them to a Rect in the upper-left starting coordinate of
  /// 0,0.
  /// @param[in] w An int32_t value representing a width.
  /// @param[in] h An int32_t value representing a height.
  Rect(int32_t w, int32_t h) {
    set_x(0);
    set_y(0);
    set_width(w);
    set_height(h);
  }

  /// A constructor accepting four int32_t values for width, height, x, and y.
  /// @param[in] x An int32_t value representing a horizontal coordinate
  /// of a point, starting with 0 as the left-most coordinate.
  /// @param[in] y An int32_t value representing a vertical coordinate
  /// of a point, starting with 0 as the top-most coordinate.
  /// @param[in] w An int32_t value representing a width.
  /// @param[in] h An int32_t value representing a height.
  Rect(int32_t x, int32_t y, int32_t w, int32_t h) {
    set_x(x);
    set_y(y);
    set_width(w);
    set_height(h);
  }

  /// A constructor accepting a pointer to a Size and converting the Size to a
  /// Rect in the upper-left starting coordinate of 0,0.
  /// @param[in] s A pointer to a Size.
  explicit Rect(const Size& s) {
    set_x(0);
    set_y(0);
    set_size(s);
  }

  /// A constructor accepting a pointer to a Point representing the origin
  /// of the rectangle and a pointer to a Size representing the height and
  /// width.
  /// @param[in] origin A pointer to a Point representing the upper-left
  /// starting coordinate.
  /// @param[in] size A pointer to a Size representing the height and width.
  Rect(const Point& origin, const Size& size) {
    set_point(origin);
    set_size(size);
  }

  /// Destructor.
  ~Rect() {
  }

  /// A function allowing implicit conversion of a Rect to a PP_Rect.
  /// @return A Point.
  operator PP_Rect() const {
    return rect_;
  }

  /// Getter function for returning the internal PP_Rect struct.
  /// @return A const reference to the internal PP_Rect struct.
  const PP_Rect& pp_rect() const {
    return rect_;
  }

  /// Getter function for returning the internal PP_Rect struct.
  /// @return A mutable reference to the PP_Rect struct.
  PP_Rect& pp_rect() {
    return rect_;
  }


  /// Getter function for returning the value of x.
  /// @return The value of x for this Point.
  int32_t x() const {
    return rect_.point.x;
  }

  /// Setter function for setting the value of x.
  /// @param[in] in_x A new x value.
  void set_x(int32_t in_x) {
    rect_.point.x = in_x;
  }

  /// Getter function for returning the value of y.
  /// @return The value of y for this Point.
  int32_t y() const {
    return rect_.point.y;
  }

  /// Setter function for setting the value of y.
  /// @param[in] in_y A new y value.
  void set_y(int32_t in_y) {
    rect_.point.y = in_y;
  }

  /// Getter function for returning the value of width.
  /// @return The value of width for this Rect.
  int32_t width() const {
    return rect_.size.width;
  }

  /// Setter function for setting the value of width.
  /// @param[in] w A new width value.
  void set_width(int32_t w) {
    if (w < 0) {
      PP_DCHECK(w >= 0);
      w = 0;
    }
    rect_.size.width = w;
  }

  /// Getter function for returning the value of height.
  /// @return The value of height for this Rect.
  int32_t height() const {
    return rect_.size.height;
  }

  /// Setter function for setting the value of height.
  /// @param[in] h A new width height.
  void set_height(int32_t h) {
    if (h < 0) {
      PP_DCHECK(h >= 0);
      h = 0;
    }
    rect_.size.height = h;
  }

  /// Getter function for returning the Point.
  /// @return A Point.
  Point point() const {
    return Point(rect_.point);
  }

  /// Setter function for setting the value of the Point.
  /// @param[in] origin A Point representing the upper-left
  /// starting coordinate.
  void set_point(const Point& origin) {
    rect_.point = origin;
  }

  /// Getter function for returning the Size.
  /// @return The size of the rectangle.
  Size size() const {
    return Size(rect_.size);
  }

  /// Setter function for setting the Size.
  /// @param[in] s A pointer to a Size representing the height and width.
  void set_size(const Size& s) {
    rect_.size.width = s.width();
    rect_.size.height = s.height();
  }

  /// Getter function to get the upper-bound for the x-coordinates of the
  /// rectangle.  Note that this coordinate value is one past the highest x
  /// value of pixels in the rectangle.  This loop will access all the pixels
  /// in a horizontal line in the rectangle:
  /// <code>for (int32_t x = rect.x(); x < rect.right(); ++x) {}</code>
  ///
  /// @return The value of x + width for this point.
  int32_t right() const {
    return x() + width();
  }

  /// Getter function to get the upper-bound for the y-coordinates of the
  /// rectangle.  Note that this coordinate value is one past the highest xy
  /// value of pixels in the rectangle.  This loop will access all the pixels
  /// in a horizontal line in the rectangle:
  /// <code>for (int32_t y = rect.y(); y < rect.bottom(); ++y) {}</code>
  ///
  /// @return The value of y + height for this point.
  int32_t bottom() const {
    return y() + height();
  }

  /// Setter function for setting the value of the Rect.
  /// @param[in] x A new x value.
  /// @param[in] y A new y value.
  /// @param[in] w A new width value.
  /// @param[in] h A new height value.
  void SetRect(int32_t x, int32_t y, int32_t w, int32_t h) {
    set_x(x);
    set_y(y);
    set_width(w);
    set_height(h);
  }

  /// Setter function for setting the value of the Rect.
  /// @param[in] rect A pointer to a PP_Rect.
  void SetRect(const PP_Rect& rect) {
    rect_ = rect;
  }

  /// A function used to shrink the rectangle by a horizontal and vertical
  /// distance on all sides.
  /// @param[in] horizontal An int32_t value representing a horizontal
  /// shrinking distance.
  /// @param[in] vertical An int32_t value representing a vertical
  /// shrinking distance.
  void Inset(int32_t horizontal, int32_t vertical) {
    Inset(horizontal, vertical, horizontal, vertical);
  }

  /// A function used to shrink the rectangle by the specified amount on each
  /// side.
  /// @param[in] left An int32_t value representing a left
  /// shrinking distance.
  /// @param[in] top An int32_t value representing a top
  /// shrinking distance.
  /// @param[in] right An int32_t value representing a right
  /// shrinking distance.
  /// @param[in] bottom An int32_t value representing a bottom
  /// shrinking distance.
  void Inset(int32_t left, int32_t top, int32_t right, int32_t bottom);

  /// A function used to move the rectangle by a horizontal and vertical
  /// distance.
  /// @param[in] horizontal An int32_t value representing a horzontal
  /// move distance.
  /// @param[in] vertical An int32_t value representing a vertical
  /// move distance.
  void Offset(int32_t horizontal, int32_t vertical);

  /// A function used to move the rectangle by a horizontal and vertical
  /// distance.
  /// @param[in] point A pointer to a Point representing the horizontal and
  /// vertical move distances.
  void Offset(const Point& point) {
    Offset(point.x(), point.y());
  }

  /// A function used to determine if the area of a rectangle is zero.
  ///  Returns true if the area of the rectangle is zero.
  /// @return True if the area of the rectangle is zero.
  bool IsEmpty() const {
    return rect_.size.width == 0 && rect_.size.height == 0;
  }

  /// A function used to determine if the point identified by point_x and
  /// point_y falls inside this rectangle. The point (x, y) is inside the
  /// rectangle, but the point (x + width, y + height) is not.
  /// @param[in] point_x An int32_t value representing a x value.
  /// @param[in] point_y An int32_t value representing a y value.
  /// @return True if the point_x and point_y fall inside the rectangle.
  bool Contains(int32_t point_x, int32_t point_y) const;

  /// A function used to determine if the specified point is contained by this
  /// rectangle.
  /// @param[in] point A pointer to a Point representing a 2D coordinate.
  /// @return True if the point_x and point_y fall inside the rectangle.
  bool Contains(const Point& point) const {
    return Contains(point.x(), point.y());
  }

  /// A function used to determine if this rectangle contains the specified
  /// rectangle.
  /// @param[in] rect A pointer to a Rect.
  /// @return True if the rectangle fall inside this rectangle.
  bool Contains(const Rect& rect) const;

  /// A function used to determine if this rectangle intersects the specified
  /// rectangle.
  /// @param[in] rect A pointer to a Rect.
  /// @return True if the rectangle intersects  this rectangle.
  bool Intersects(const Rect& rect) const;

  /// A function used to compute the intersection of this rectangle with the
  /// given rectangle.
  /// @param[in] rect A pointer to a Rect.
  /// @return A Rect representing the intersection.
  Rect Intersect(const Rect& rect) const;

  /// A function used to compute the union of this rectangle with the given
  /// rectangle.  The union is the smallest rectangle containing both
  /// rectangles.
  /// @param[in] rect A pointer to a Rect.
  /// @return A Rect representing the union.
  Rect Union(const Rect& rect) const;

  /// A function used to compute the rectangle resulting from subtracting
  /// |rect| from |this|.  If |rect| does not intersect completely in either
  /// the x- or y-direction, then |*this| is returned. If |rect| contains
  /// |this|, then an empty Rect is returned.
  /// @param[in] rect A pointer to a Rect.
  /// @return A Rect representing the subtraction.
  Rect Subtract(const Rect& rect) const;

  /// A function used to fit as much of the receiving rectangle within the
  /// supplied rectangle as possible, returning the result. For example, if the
  /// receiver had a x-location of 2 and a width of 4, and the supplied
  /// rectangle had an x-location of 0 with a width of 5, the returned
  /// rectangle would have an x-location of 1 with a width of 4.
  /// @param[in] rect A pointer to a Rect.
  /// @return A Rect representing the difference between this rectangle and the
  /// receiving rectangle.
  Rect AdjustToFit(const Rect& rect) const;

  /// A function used to determine the center of this rectangle.
  /// @return A Point representing the center of this rectangle.
  Point CenterPoint() const;

  /// A function used to determine if this rectangle shares an entire edge
  /// (same width or same height) with the given rectangle, and the
  /// rectangles do not overlap.
  /// @param[in] rect A pointer to a Rect.
  /// @return TRUE if this rectangle and supplied rectangle share an edge.
  bool SharesEdgeWith(const Rect& rect) const;

 private:
  PP_Rect rect_;
};

}  // namespace pp

/// Determines whether the x, y, width, and height values of two rectangles and
/// are equal.
/// @param[in] lhs The Rect on the left-hand side of the equation.
/// @param[in] rhs The Rect on the right-hand side of the equation.
/// @return true if they are equal, false if unequal.
inline bool operator==(const pp::Rect& lhs, const pp::Rect& rhs) {
  return lhs.x() == rhs.x() &&
         lhs.y() == rhs.y() &&
         lhs.width() == rhs.width() &&
         lhs.height() == rhs.height();
}

/// Determines whether two Rects are not equal.
/// @param[in] lhs The Rect on the left-hand side of the equation.
/// @param[in] rhs The Rect on the right-hand side of the equation.
/// @return true if the given Rects are equal, otherwise false.
inline bool operator!=(const pp::Rect& lhs, const pp::Rect& rhs) {
  return !(lhs == rhs);
}

#endif

