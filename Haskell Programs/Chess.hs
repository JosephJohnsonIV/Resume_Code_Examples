-- Joseph Johnson IV
-- Course: COP 4020 - Programming Languages Spring 2016
-- Program to determine whether or not a chess move is legal
-- Takes a peice color, type, starting position, and ending position as input
-- Assumes that this peice is the only peice on the board

module Chess where

-- Necessary in order to convert Char type to Int
import Data.Ord
import Data.Char

type File     = Char         -- column index
                             -- valid files are 'a','b',...,'h'
type Rank     = Int          -- row index
                             -- valid ranks are 1,2,...8
type Position = (File,Rank)

data Color =
  Black | White
  deriving (Eq,Show)

data Piece =
  King | Queen | Rook | Bishop | Knight | Pawn
  deriving (Eq,Show)

-- Function to convert a single char to an int
charToInt :: Char -> Int

charToInt c = (ord c) - 96

----------------------------------------------------------------------
 -- Function to test a position
isLegalPosition :: Position -> Bool

isLegalPosition (f,r)
    | (pos >= 1) && (pos <= 8) && (r >= 1) && (r <= 8) = True
    | otherwise = False
    where pos = charToInt(f)

----------------------------------------------------------------------

isLegalMove :: Color -> Piece -> Position -> Position -> Bool

-- Pattern for the Black King
isLegalMove Black King (f0,r0) (f1,r1)
    | not (pos0) = False                                                                -- Check for invalid pos
    | not (pos1) = False                                                                -- Check for invalid pos
    | (fNum0 == fNum1) && (r0 == r1) = False                                            -- Check for same pos
    | (fNum1 > (fNum0 + 1)) || (fNum1 < (fNum0 - 1)) = False                            -- Invalid if moving by more than one file
    | (r1 > (r0 + 1)) || (r1 < (r0 - 1)) = False                                        -- Invalid if moving by more than one row
    | otherwise = True                                                                  -- Valid move otherwise
    where pos0 = isLegalPosition (f0,r0)                                                -- Using where to help with guards
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Same pattern as the Black King
isLegalMove White King (f0,r0) (f1,r1)
    | not (pos0) = False
    | not (pos1) = False
    | (fNum0 == fNum1) && (r0 == r1) = False
    | (fNum1 > (fNum0 + 1)) || (fNum1 < (fNum0 - 1)) = False
    | (r1 > (r0 + 1)) || (r1 < (r0 - 1)) = False
    | otherwise = True
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Pattern for the Black Rook
isLegalMove Black Rook (f0,r0) (f1,r1)
    | not (pos0) = False                                                                -- Check for invalid pos
    | not (pos1) = False                                                                -- Check for invalid pos
    | (fNum0 == fNum1) && (r0 == r1) = False                                            -- Check for same pos
    | (fNum1 /= fNum0) && (r1 /= r0) = False                                            -- Invalid if both the file and the row changed
    | otherwise = True                                                                  -- Valid move otherwise
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Same pattern as the Black Rook
isLegalMove White Rook (f0,r0) (f1,r1)
    | not (pos0) = False
    | not (pos1) = False
    | (fNum0 == fNum1) && (r0 == r1) = False
    | (fNum1 /= fNum0) && (r1 /= r0) = False
    | otherwise = True
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Pattern for the Black Bishop
isLegalMove Black Bishop (f0,r0) (f1, r1)
    | not (pos0) = False                                                                -- Check for invalid pos
    | not (pos1) = False                                                                -- Check for invalid pos
    | (fNum0 == fNum1) || (r0 == r1) = False                                            -- False if either the file or row have not changed
    | (fNum1 - fNum0) == (r1 - r0) = True                                               -- Valid if moving diagonally upward and to the right, or downward and to the left
    | (fNum1 - fNum0) == ((r1 - r0) * (-1)) = True                                      -- Valid if moving diagonally downward and to the right
    | ((fNum1 - fNum0) * (-1)) == (r1 - r0) = True                                      -- Valid if moving diagonally upward and to the left
    | otherwise = False                                                                 -- Invalid move otherwise
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Same pattern as the Black Bishop
isLegalMove White Bishop (f0,r0) (f1, r1)
    | not (pos0) = False
    | not (pos1) = False
    | (fNum0 == fNum1) || (r0 == r1) = False
    | (fNum1 - fNum0) == (r1 - r0) = True
    | (fNum1 - fNum0) == ((r1 - r0) * (-1)) = True
    | ((fNum1 - fNum0) * (-1)) == (r1 - r0) = True
    | otherwise = False
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Pattern for the Black Queen
isLegalMove Black Queen (f0,r0) (f1,r1)
    | not (pos0) = False                                                                -- Check for invalid pos
    | not (pos1) = False                                                                -- Check for invalid pos
    | (fNum0 == fNum1) && (r0 == r1) = False                                            -- Check for same pos
    | (fNum1 - fNum0) == (r1 - r0) = True                                               -- Valid if moving diagonally upward and to the right, or downward and to the left
    | (fNum1 - fNum0) == ((r1 - r0) * (-1)) = True                                      -- Valid if moving diagonally downward and to the right
    | ((fNum1 - fNum0) * (-1)) == (r1 - r0) = True                                      -- Valid if moving diagonally upward and to the left
    | ((fNum1 /= fNum0) && (r1 == r0)) || ((fNum1 == fNum0) && (r1 /= r0)) = True       -- Valid if either the file or the row has not changed
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Same pattern as the Black Queen
isLegalMove White Queen (f0,r0) (f1,r1)
    | not (pos0) = False
    | not (pos1) = False
    | (fNum0 == fNum1) && (r0 == r1) = False
    | (fNum1 - fNum0) == (r1 - r0) = True
    | (fNum1 - fNum0) == ((r1 - r0) * (-1)) = True
    | ((fNum1 - fNum0) * (-1)) == (r1 - r0) = True
    | ((fNum1 /= fNum0) && (r1 == r0)) || ((fNum1 == fNum0) && (r1 /= r0)) = True
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Pattern for the Black Knight
isLegalMove Black Knight (f0,r0) (f1,r1)
    | not (pos0) = False                                                                -- Check for invalid pos
    | not (pos1) = False                                                                -- Check for invalid pos
    | (fNum0 == fNum1) || (r0 == r1) = False                                            -- Invalid if either the file or the row have not changed
    | (fNum1 == fNum0 + 1) && (r1 == r0 + 1) = False                                    -- Invalid if witin the circle or outside of the circle
    | (fNum1 == fNum0 + 1) && (r1 == r0 - 1) = False
    | (fNum1 == fNum0 - 1) && (r1 == r0 + 1) = False
    | (fNum1 == fNum0 - 1) && (r1 == r0 - 1) = False
    | (fNum1 > fNum0 + 2) || (r1 > r0 + 2) = False
    | (fNum1 < fNum0 - 2) || (r1 < r0- 2) = False
    | otherwise = True                                                                  -- Valid otherwise
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Same as the Black Knight
isLegalMove White Knight (f0,r0) (f1,r1)
    | not (pos0) = False
    | not (pos1) = False
    | (fNum0 == fNum1) || (r0 == r1) = False
    | (fNum1 == fNum0 + 1) && (r1 == r0 + 1) = False
    | (fNum1 == fNum0 + 1) && (r1 == r0 - 1) = False
    | (fNum1 == fNum0 - 1) && (r1 == r0 + 1) = False
    | (fNum1 == fNum0 - 1) && (r1 == r0 - 1) = False
    | (fNum1 > fNum0 + 2) || (r1 > r0 + 2) = False
    | (fNum1 < fNum0 - 2) || (r1 < r0 - 2) = False
    | otherwise = True
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Pattern for the Black Pawn
isLegalMove Black Pawn (f0,r0) (f1,r1)
    | not (pos0) = False                                                                -- Check for invalid pos
    | not (pos1) = False                                                                -- Check for invalid pos
    | (r1 == r0) = False                                                                -- Invalid if the row has not changed
    | (fNum1 /= fNum0) = False                                                          -- Invalid if the file has changed
    | (r1 > r0) = False                                                                 -- Invalid if moving upward
    | (r0 == 7) && (r1 < (r0 - 2)) = False                                              -- Invalid if on row 7 and moving more than two rows
    | (r0 /= 7) && (r1 < (r1 - 1)) = False                                              -- Invalid if not on row 7 and moving more than one row
    | otherwise = True                                                                  -- Valid otherwise
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)

-- Pattern for the White Pawn
isLegalMove White Pawn (f0,r0) (f1,r1)
    | not (pos0) = False                                                                -- Check for invalid pos
    | not (pos1) = False                                                                -- Check for invalid pos
    | (r1 == r0) = False                                                                -- Invalid if the row has not changed
    | (fNum1 /= fNum0) = False                                                          -- Invalid if the file has changed
    | (r1 < r0) = False                                                                 -- Invalid if moving downward
    | (r0 == 2) && (fNum1 > (fNum0 + 2)) = False                                        -- Invalid if on row 2 and moving more than two rows
    | (r0 /= 2) && (fNum1 > (fNum0 + 1)) = False                                        -- Invalid if not on row 2 and moving more than one row
    | otherwise = True
    where pos0 = isLegalPosition (f0,r0)
          pos1 = isLegalPosition (f1,r1)
          fNum0 = charToInt(f0)
          fNum1 = charToInt(f1)
