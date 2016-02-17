from graphutils import Vector


class Drawer:
    def __init__(self, viewport, da, ctx):
        self.viewport = viewport
        self.da = da
        self.ctx = ctx

    def world_to_screen(self, point):
        screen_width = self.da.get_allocated_width()
        screen_height = self.da.get_allocated_height()
        return (screen_width / self.viewport.width() * (point.x - self.viewport.xmin),
                screen_height / self.viewport.height() * (self.viewport.ymax - point.y))

    def draw_line(self, start, end):
        self.ctx.new_path()
        self.ctx.line_to(*self.world_to_screen(start))
        self.ctx.line_to(*self.world_to_screen(end))
        self.ctx.close_path()
        self.ctx.stroke()

    def draw_axes(self):
        self.draw_line(Vector(self.viewport.xmin, 0), Vector(self.viewport.xmax, 0))
        self.draw_line(Vector(0, self.viewport.ymin), Vector(0, self.viewport.ymax))

    def draw_polygon(self, polygon):
        self.ctx.new_path()
        for point in polygon.points:
            self.ctx.line_to(*self.world_to_screen(point))
        self.ctx.close_path()
        self.ctx.stroke()