
from numpy.matlib import math, matrix, hstack, vstack


class Camera:
    def __init__(self, normal, origin, d, top):
        self.normal = normal
        self.origin = origin
        self.focal_length = d
        self.top = top

    def world_to_view(self, point):
        i = self.top.cross(self.normal).normalize()
        k = self.normal.normalize()
        j = k.cross(i)

        s = hstack([i.vec3d(), j.vec3d(), k.vec3d()])
        p1 = s.T * point.vec3d()
        or1 = s.T * self.origin.vec3d()
        return p1 - or1

    def project(self, point):
        v = Vector.from_vec(self.world_to_view(point))
        k = self.focal_length / (self.focal_length - v.z)
        res = v.scale(k)
        return Vector2D(res.x, res.y)


class Viewport:
    def __init__(self, camera, xmin, xmax, ymin, ymax):
        self.camera = camera
        self.xmin = xmin
        self.xmax = xmax
        self.ymin = ymin
        self.ymax = ymax

    def width(self):
        return self.xmax - self.xmin

    def height(self):
        return self.ymax - self.ymin


class Vector2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __neg__(self):
        return Vector2D(-self.x, -self.y)

    def __add__(self, other):
        return Vector2D(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return self + (-other)

    def __str__(self):
        return "Vector2D ({0} {1})".format(self.x, self.y)

    def vec(self):
        return matrix([[self.x], [self.y], [1]])

    @staticmethod
    def from_vec(vec):
        arr = vec.A
        return Vector2D(arr[0][0], arr[1][0])


class Vector:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __neg__(self):
        return Vector(-self.x, -self.y, -self.z)

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y, self.z + other.z)

    def __sub__(self, other):
        return self + (-other)

    def __str__(self):
        return "Vector ({0} {1} {2})".format(self.x, self.y, self.z)

    def scale(self, k):
        return Vector(self.x * k, self.y * k, self.z * k)

    def vec(self):
        return matrix([[self.x], [self.y], [self.z], [1]])

    def vec3d(self):
        return matrix([[self.x], [self.y], [self.z]])

    def cross(self, other):
        return Vector(self.y * other.z - self.z * other.y,
                      -self.x * other.z + self.z * other.x,
                      self.x * other.y - self.y * other.x)

    def dot(self, other):
        return self.x * other.x + self.y * other.y + self.z * other.z

    def norm(self):
        return math.sqrt(self.dot(self))

    def normalize(self):
        return self.scale(1 / self.norm())

    @staticmethod
    def from_vec(vec):
        arr = vec.A
        return Vector(arr[0][0], arr[1][0], arr[2][0])


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
    def translate(vector):
        return Transformation([[1.0, 0.0, 0.0, vector.x],
                               [0.0, 1.0, 0.0, vector.y],
                               [0.0, 0.0, 1.0, vector.z],
                               [0.0, 0.0, 0.0, 1.0]])

    @staticmethod
    def scale(kx, ky, kz, origin=Vector(0, 0, 0)):
        around_zero = Transformation([[kx, 0.0, 0.0, 0.0],
                                      [0.0, ky, 0.0, 0.0],
                                      [0.0, 0.0, kz, 0.0],
                                      [0.0, 0.0, 0.0, 1.0]])
        return around_zero.move_to(origin)


class Polyhedron:
    def __init__(self, polygons):
        self.polygons = polygons

    def transform(self, transformation):
        return Polyhedron(list(map(lambda p: p.transform(transformation), self.polygons)))


class Polygon:
    def __init__(self, points):
        self.points = points

    def transform(self, transformation):
        return Polygon(list(map(transformation.apply, self.points)))
