-- Joseph Johnson IV
-- Course: COP 4020 - Programming Languages Spring 2016
-- Program to compute the area of a polygon specified using a list of tuples of type Double, each specifying a vertex.

module PolygonArea where

-- Will take in a list of touples of doubles and returns
-- a double representing the area
computeArea :: [(Double,Double)] -> Double

-- Display errors if the list is either empty or holds only one point
computeArea [] = error "The list is empty"
computeArea [_] = error "List only contains one point"

-- Have to append the first point to the end of the list in order to calculate the function correctly
computeArea  (x:xs) =
    recursiveCompute ((x:xs)++[x])

----------------------------------------------------

-- This will actually do the recursive determinate calculation
-- Takes a list of tuples of doubles and returns a double representing the area
recursiveCompute :: [(Double,Double)] -> Double

-- Base case of only two pairs in the list
recursiveCompute ((x0,x1) : (x2,x3) : []) =
    det(x0,x1) (x2,x3)

-- Base case of three pairs left in the list
recursiveCompute ((x0,x1) : (x2,x3) : (x4,x5) : []) =
    det(x0,x1) (x2,x3) + det(x2,x3) (x4,x5)

-- If the input is two points and the rest of a list, recursively calculate the determinate of the rest of the list
recursiveCompute ((x0,x1) : (x2,x3) : xs) =
    (det(x0,x1) (x2,x3)) + recursiveCompute((x2,x3) : xs)

---------------------------------------------------

det :: (Double,Double) -> (Double,Double) -> Double

-- If given two points, return the determinate
det (y0, y1) (y2, y3) =
    ((y0 * y3) - (y2 * y1)) * 0.5
