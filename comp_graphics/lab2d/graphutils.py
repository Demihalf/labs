from numpy.matlib import math, matrix


class Viewport:
    def __init__(self, xmin, xmax, ymin, ymax):
        self.xmin = xmin
        self.xmax = xmax
        self.ymin = ymin
        self.ymax = ymax

    def width(self):
        return self.xmax - self.xmin

    def height(self):
        return self.ymax - self.ymin


class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __neg__(self):
        return Vector(-self.x, -self.y)

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return self + (-other)

    def __str__(self):
        return "Vector ({0} {1})".format(self.x, self.y)

    def vec(self):
        return matrix([[self.x], [self.y], [1]])

    @staticmethod
    def from_vec(vec):
        arr = vec.A
        return Vector(arr[0][0], arr[1][0])


class Transformation:
    def __init__(self, m):
        self.matrix = matrix(m)

    def __mul__(self, other):
        return Transformation(self.matrix * other.matrix)

    def apply(self, vector):
        return Vector.from_vec(self.matrix * vector.vec())

    def inv(self):
        return Transformation(self.matrix.I)

    def move_to(self, origin):
        translate = Transformation.translate(origin)
        return translate * self * translate.inv()

    @staticmethod
    def rotate(angle, origin=Vector(0, 0)):
        around_zero = Transformation([[math.cos(angle), - math.sin(angle), 0.0],
                                      [math.sin(angle), math.cos(angle), 0.0],
                                      [0.0, 0.0, 1.0]])
        return around_zero.move_to(origin)

    @staticmethod
    def translate(vector):
        return Transformation([[1.0, 0.0, vector.x],
                               [0.0, 1.0, vector.y],
                               [0.0, 0.0, 1.0]])

    @staticmethod
    def scale(kx, ky, origin=Vector(0, 0)):
        around_zero = Transformation([[kx, 0.0, 0.0],
                                      [0.0, ky, 0.0],
                                      [0.0, 0.0, 1.0]])
        return around_zero.move_to(origin)

    @staticmethod
    def shear(mx, my):
        return Transformation([[1.0, mx,   0.0],
                               [my,  1.0,  0.0],
                               [0.0, 0.0,  1.0]])


class Polygon:
    def __init__(self, points):
        self.points = points

    def rotate(self, angle, origin=Vector(0, 0)):
        return self.transform(Transformation.rotate(angle, origin))

    def transform(self, transformation):
        return Polygon(list(map(transformation.apply, self.points)))