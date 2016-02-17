from graphutils import Vector


class Drawer:
    def __init__(self, viewport, da, ctx):
        self.viewport = viewport
        self.drawing_area = da
        self.ctx = ctx

    def world2d_to_screen(self, point):
        screen_width = self.drawing_area.get_allocated_width()
        screen_height = self.drawing_area.get_allocated_height()
        return (screen_width / self.viewport.width() * (point.x - self.viewport.xmin),
                screen_height / self.viewport.height() * (self.viewport.ymax - point.y))

    def draw_line(self, start, end):
        self.ctx.new_path()
        self.ctx.line_to(*self.world2d_to_screen(start))
        self.ctx.line_to(*self.world2d_to_screen(end))
        self.ctx.close_path()
        self.ctx.stroke()

    def draw_polyhedron(self, polyhedron):
        for poly in polyhedron.polygons:
            self.draw_polygon(poly)

    def draw_polygon(self, polygon):
        self.ctx.new_path()
        for point in polygon.points:
            self.ctx.line_to(*self.world2d_to_screen(self.viewport.camera.project(point)))
        self.ctx.close_path()
        self.ctx.stroke()

    def draw_mesh(self):
        for i in range(-5, 6):
            self.draw_line(self.viewport.camera.project(Vector(i, -5, 0)),
                           self.viewport.camera.project(Vector(i, 5, 0)))
            self.draw_line(self.viewport.camera.project(Vector(-5, i, 0)),
                           self.viewport.camera.project(Vector(5, i, 0)))
